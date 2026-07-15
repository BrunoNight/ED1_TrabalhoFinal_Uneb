#include "listas.h"         // ListaDupla, ListaSimples, Conteudo, NodoDuplo
#include "estatisticas.h"
#include "persistencia.h"
#include "usuario.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

// ─────────────────────────────────────────────────────────────
//  Helper: converte string para float de forma segura
// ─────────────────────────────────────────────────────────────
static float strToFloat(const string& s) {
    try { return stof(s); } catch (...) { return 0.0f; }
}

static int strToInt(const string& s) {
    try { return stoi(s); } catch (...) { return 0; }
}

// ─────────────────────────────────────────────────────────────
//  Helper: divide linha CSV pelo separador ';'
// ─────────────────────────────────────────────────────────────
static void splitCSV(const string& linha, string campos[], int maxCampos) {
    stringstream ss(linha);
    string token;
    int i = 0;
    while (getline(ss, token, ';') && i < maxCampos) {
        campos[i++] = token;
    }
}

// =============================================================
//  CATALOGO
// =============================================================

// ─────────────────────────────────────────────────────────────
//  salvarCatalogo
//
//  Grava todos os titulos de listaCad no formato:
//    id;titulo;tipo;genero;ano;numViews;avaliacao
//
//  O arquivo e recriado a cada chamada (truncado).
//  Retorna true se gravacao bem-sucedida.
// ─────────────────────────────────────────────────────────────
bool salvarCatalogo(ListaDupla& listaCad, const string& nomeArq) {
    ofstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [ERRO] Nao foi possivel abrir \"" << nomeArq << "\" para escrita.\n";
        return false;
    }

    // Cabecalho (comentario para legibilidade do arquivo)
    arq << "# Sistema de Streaming MEUFLIX - Catalogo\n";
    arq << "# id;titulo;tipo;genero;ano;numViews;avaliacao\n";

    NodoDuplo* atual = listaCad.getCabeca();
    int gravados = 0;
    while (atual != nullptr) {
        const Conteudo& c = atual->conteudo;
        arq << c.id     << ";"
            << c.titulo << ";"
            << c.tipo   << ";"
            << c.genero << ";"
            << c.ano    << ";"
            << c.numViews << ";"
            << fixed << c.avaliacao << "\n";
        gravados++;
        atual = atual->proximo;
    }

    arq.close();
    cout << "  [OK] Catalogo salvo em \"" << nomeArq
         << "\" (" << gravados << " titulo(s))\n";
    return true;
}

// ─────────────────────────────────────────────────────────────
//  carregarCatalogo
//
//  Le o arquivo CSV e insere cada titulo em listaCad E listaAssist.
//  Linhas com '#' sao ignoradas.
//  Retorna o numero de titulos carregados com sucesso.
// ─────────────────────────────────────────────────────────────
int carregarCatalogo(ListaDupla& listaCad, ListaDupla& listaAssist, const string& nomeArq) {
    ifstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [Aviso] \"" << nomeArq
             << "\" nao encontrado — iniciando com catalogo vazio.\n";
        return 0;
    }

    string linha;
    int carregados = 0;
    int maiorIdEncontrado = 0; // [+] Variável para rastrear o maior ID

    while (getline(arq, linha)) {
        // Pular linhas vazias e comentarios
        if (linha.empty() || linha[0] == '#') continue;

        string campos[7];
        splitCSV(linha, campos, 7);

        // Validacao minima: precisa de pelo menos 7 campos
        if (campos[4].empty()) continue;

        Conteudo c;
        c.id        = strToInt(campos[0]);
        c.titulo    = campos[1];
        c.tipo      = campos[2];
        c.genero    = campos[3];
        c.ano       = strToInt(campos[4]);
        c.numViews  = strToInt(campos[5]);
        c.avaliacao = strToFloat(campos[6]);

        if (c.id > maiorIdEncontrado) {
            maiorIdEncontrado = c.id;
        }

        // Verificar duplicata antes de inserir
        if (listaCad.buscar(c.titulo) == nullptr) {
            listaCad.inserirOrdenado(c);
            listaAssist.inserirOrdenado(c);
            carregados++;
        }
    }

    arq.close();
    
    // [+] Sincroniza a variável de geração de ID
    atualizarProximoId(maiorIdEncontrado);

    cout << "  [OK] Catalogo carregado de \"" << nomeArq
         << "\" (" << carregados << " titulo(s))\n";
    return carregados;
}

// =============================================================
//  RANKING (listaAssist — persistencia das views atualizadas)
// =============================================================

// ─────────────────────────────────────────────────────────────
//  salvarRanking
//
//  Grava apenas o estado atual das views de listaAssist.
//  Formato identico ao catalogo (facilita re-uso do parser).
// ─────────────────────────────────────────────────────────────
bool salvarRanking(ListaDupla& listaAssist, const string& nomeArq) {
    ofstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [ERRO] Nao foi possivel abrir \"" << nomeArq << "\" para escrita.\n";
        return false;
    }

    arq << "# Sistema de Streaming MEUFLIX - Ranking\n";
    arq << "# id;titulo;tipo;genero;ano;numViews;avaliacao\n";

    NodoDuplo* atual = listaAssist.getCabeca();
    int gravados = 0;
    while (atual != nullptr) {
        const Conteudo& c = atual->conteudo;
        arq << c.id     << ";"
            << c.titulo << ";"
            << c.tipo   << ";"
            << c.genero << ";"
            << c.ano    << ";"
            << c.numViews << ";"
            << fixed << c.avaliacao << "\n";
        gravados++;
        atual = atual->proximo;
    }

    arq.close();
    cout << "  [OK] Ranking salvo em \"" << nomeArq
         << "\" (" << gravados << " titulo(s))\n";
    return true;
}

// ─────────────────────────────────────────────────────────────
//  carregarRanking
//
//  Le o ranking salvo e atualiza numViews em listaCad e
//  listaAssist para restaurar o estado anterior.
//  Retorna o numero de registros atualizados.
// ─────────────────────────────────────────────────────────────
int carregarRanking(ListaDupla& listaCad, ListaDupla& listaAssist,
                     const string& nomeArq) {
    ifstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [Aviso] \"" << nomeArq
             << "\" nao encontrado — ranking iniciado do zero.\n";
        return 0;
    }

    string linha;
    int atualizados = 0;

    while (getline(arq, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        string campos[7];
        splitCSV(linha, campos, 7);
        if (campos[5].empty()) continue;

        string titulo   = campos[1];
        int    numViews = strToInt(campos[5]);

        // Atualiza numViews em listaCad (loop ate o valor correto)
        NodoDuplo* noCad = listaCad.buscar(titulo);
        if (noCad != nullptr) {
            int diff = numViews - noCad->conteudo.numViews;
            for (int i = 0; i < diff; i++)
                listaCad.incrementarVisualizacoes(titulo);
        }

        // Atualiza em listaAssist
        NodoDuplo* noAss = listaAssist.buscar(titulo);
        if (noAss != nullptr) {
            int diff = numViews - noAss->conteudo.numViews;
            for (int i = 0; i < diff; i++)
                listaAssist.incrementarVisualizacoes(titulo);
            atualizados++;
        }
    }

    arq.close();
    cout << "  [OK] Ranking carregado de \"" << nomeArq
         << "\" (" << atualizados << " titulo(s) atualizados)\n";
    return atualizados;
}

// =============================================================
//  ESTATISTICAS
// =============================================================

// ─────────────────────────────────────────────────────────────
//  salvarEstatisticas
//
//  Grava todos os contadores do struct em uma unica linha CSV.
// ─────────────────────────────────────────────────────────────
bool salvarEstatisticas(Estatisticas& est, const string& nomeArq) {
    ofstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [ERRO] Nao foi possivel abrir \"" << nomeArq << "\" para escrita.\n";
        return false;
    }

    arq << "# totRec;totViews;Filme;Serie;Doc;Anime;Cartoon;"
        << "Acao;Comedia;Drama;Terror;FicCient;Fantasia\n";

    arq << est.totRecomendacoes  << ";"
        << est.totVisualizacoes  << ";"
        << est.recFilme          << ";"
        << est.recSerie          << ";"
        << est.recDocumentario   << ";"
        << est.recAnime          << ";"
        << est.recCartoon        << ";"
        << est.recAcao           << ";"
        << est.recComedia        << ";"
        << est.recDrama          << ";"
        << est.recTerror         << ";"
        << est.recFicCientifica  << ";"
        << est.recFantasia       << "\n";

    arq.close();
    cout << "  [OK] Estatisticas salvas em \"" << nomeArq << "\"\n";
    return true;
}

// ─────────────────────────────────────────────────────────────
//  carregarEstatisticas
//
//  Le os contadores salvos e restaura o struct.
// ─────────────────────────────────────────────────────────────
bool carregarEstatisticas(Estatisticas& est, const string& nomeArq) {
    ifstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [Aviso] \"" << nomeArq
             << "\" nao encontrado — estatisticas zeradas.\n";
        return false;
    }

    string linha;
    while (getline(arq, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        string campos[13];
        splitCSV(linha, campos, 13);

        est.totRecomendacoes = strToInt(campos[0]);
        est.totVisualizacoes = strToInt(campos[1]);
        est.recFilme         = strToInt(campos[2]);
        est.recSerie         = strToInt(campos[3]);
        est.recDocumentario  = strToInt(campos[4]);
        est.recAnime         = strToInt(campos[5]);
        est.recCartoon       = strToInt(campos[6]);
        est.recAcao          = strToInt(campos[7]);
        est.recComedia       = strToInt(campos[8]);
        est.recDrama         = strToInt(campos[9]);
        est.recTerror        = strToInt(campos[10]);
        est.recFicCientifica = strToInt(campos[11]);
        est.recFantasia      = strToInt(campos[12]);
        break; // so uma linha de dados
    }

    arq.close();
    cout << "  [OK] Estatisticas carregadas de \"" << nomeArq << "\"\n";
    return true;
}

bool salvarUsuarios(ListaUsuarios& listaU, const string& nomeArq) {
    ofstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [ERRO] Nao foi possivel abrir \"" << nomeArq << "\" para escrita.\n";
        return false;
    }

    arq << "# id;login;senha;tipo\n"; // Cabeçalho do CSV
    Usuario* atual = listaU.inicio;
    int gravados = 0;
    
    while (atual != nullptr) {
        arq << atual->id << ";"
            << atual->login << ";"
            << atual->senha << ";"
            << atual->tipo << "\n";
        gravados++;
        atual = atual->prox;
    }

    arq.close();
    cout << "  [OK] Usuarios salvos em \"" << nomeArq << "\" (" << gravados << " conta(s))\n";
    return true;
}

int carregarUsuarios(ListaUsuarios& listaU, const string& nomeArq) {
    ifstream arq(nomeArq);
    if (!arq.is_open()) {
        cout << "  [Aviso] \"" << nomeArq << "\" nao encontrado — iniciando sem usuarios salvos.\n";
        return 0;
    }

    string linha;
    int carregados = 0;

    while (getline(arq, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        string campos[4];
        splitCSV(linha, campos, 4);

        if (campos[1].empty()) continue; // Evita linhas zumbis

        Usuario* novo = new Usuario;
        novo->id    = strToInt(campos[0]);
        novo->login = campos[1];
        novo->senha = campos[2];
        novo->tipo  = static_cast<decltype(novo->tipo)>(strToInt(campos[3])); // Converte int de volta para Enum
        novo->prox  = nullptr;

        // Insere o usuário recuperado no final da lista encadeada
        if (listaU.inicio == nullptr) {
            listaU.inicio = novo;
        } else {
            Usuario* aux = listaU.inicio;
            while (aux->prox != nullptr) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
        carregados++;
    }

    arq.close();
    cout << "  [OK] Usuarios carregados de \"" << nomeArq << "\" (" << carregados << " conta(s))\n";
    return carregados;
}

// =============================================================
//  CONVENIENCIA: salvar/carregar tudo de uma vez
// =============================================================

void salvarTudo(ListaDupla& listaCad, ListaDupla& listaAssist, Estatisticas& est, ListaUsuarios& listaUsuarios) {
    cout << "\n  [Persistencia] Salvando estado do sistema...\n";
    salvarCatalogo(listaCad);
    salvarRanking(listaAssist);
    salvarEstatisticas(est);
    salvarUsuarios(listaUsuarios);
}

int carregarTudo(ListaDupla& listaCad, ListaDupla& listaAssist, Estatisticas& est, ListaUsuarios& listaUsuarios) {
    cout << "\n  [Persistencia] Carregando estado do sistema...\n";
    int n = carregarCatalogo(listaCad, listaAssist);
    if (n > 0) carregarRanking(listaCad, listaAssist);
    carregarEstatisticas(est);
    carregarUsuarios(listaUsuarios);
    return n;
}
