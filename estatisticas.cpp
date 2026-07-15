#include "listas.h"        // contem ListaDupla, ListaSimples, Conteudo
#include "estatisticas.h"
#include "estetica.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>       // Para std::transform
#include <cctype>          // Para std::tolower
#include <climits>         // INT_MAX para menor valor inicial

using namespace std;

// ─────────────────────────────────────────────────────────────
//  Helper interno: separador visual
// ─────────────────────────────────────────────────────────────
static void separador(const string& titulo) {
    centralizarTexto("\n  \033[1;33m" + string(50, '-') + "\033[0m\n");
    centralizarTexto("  \033[1;33m  " + titulo + "\033[0m\n");
    centralizarTexto("  \033[1;33m" + string(50, '-') + "\033[0m\n");
}

// ─────────────────────────────────────────────────────────────
//  Helper interno: Converte uma string para minúsculas
// ─────────────────────────────────────────────────────────────
static string paraMinusculo(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return str;
}

// ─────────────────────────────────────────────────────────────
//  Helper interno: retorna o nome do tipo com maior contagem
// ─────────────────────────────────────────────────────────────
static string tipoComMaiorContagem(Estatisticas& est) {
    int vals[5] = { est.recFilme, est.recSerie, est.recDocumentario,
                    est.recAnime, est.recCartoon };
    string nomes[5] = { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };

    // Se todos forem zero, evita destacar um sem uso
    bool todosZero = true;
    for(int v : vals) if (v > 0) todosZero = false;
    if (todosZero) return "Nenhum (sem dados)";

    int idxMax = 0;
    for (int i = 1; i < 5; i++) {
        if (vals[i] > vals[idxMax]) {
            idxMax = i;
        }
    }
    return nomes[idxMax];
}

static string tipoComMenorContagem(Estatisticas& est) {
    int vals[5] = { est.recFilme, est.recSerie, est.recDocumentario,
                    est.recAnime, est.recCartoon };
    string nomes[5] = { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };

    // Se todos forem zero
    bool todosZero = true;
    for(int v : vals) if (v > 0) todosZero = false;
    if (todosZero) return "Nenhum (sem dados)";

    int idxMin = 0;
    // Encontra o menor valor real (usando <= para atualizar caso existam outros zeros)
    for (int i = 1; i < 5; i++) {
        if (vals[i] <= vals[idxMin]) {
            idxMin = i;
        }
    }
    return nomes[idxMin];
}

static string generoComMaiorContagem(Estatisticas& est) {
    int vals[6] = { est.recAcao, est.recComedia, est.recDrama,
                    est.recTerror, est.recFicCientifica, est.recFantasia };
    string nomes[6] = { "Acao", "Comedia", "Drama",
                        "Terror", "Ficcao Cientifica", "Fantasia" };

    bool todosZero = true;
    for(int v : vals) if (v > 0) todosZero = false;
    if (todosZero) return "Nenhum (sem dados)";

    int idxMax = 0;
    for (int i = 1; i < 6; i++) {
        if (vals[i] > vals[idxMax]) idxMax = i;
    }
    return nomes[idxMax];
}

static string generoComMenorContagem(Estatisticas& est) {
    int vals[6] = { est.recAcao, est.recComedia, est.recDrama,
                    est.recTerror, est.recFicCientifica, est.recFantasia };
    string nomes[6] = { "Acao", "Comedia", "Drama",
                        "Terror", "Ficcao Cientifica", "Fantasia" };

    bool todosZero = true;
    for(int v : vals) if (v > 0) todosZero = false;
    if (todosZero) return "Nenhum (sem dados)";

    int idxMin = 0;
    for (int i = 1; i < 6; i++) {
        if (vals[i] <= vals[idxMin]) idxMin = i;
    }
    return nomes[idxMin];
}

// =============================================================
//  REGISTRO EM TEMPO REAL (CORRIGIDO CASE-INSENSITIVE)
// =============================================================
void registrarRecomendacao(Estatisticas& est,
                            const string& tipo,
                            const string& genero) {
    est.totRecomendacoes++;
    est.totVisualizacoes++;

    // Normaliza para minúsculas antes de testar
    string tipoBusca = paraMinusculo(tipo);
    string generoBusca = paraMinusculo(genero);

    // ── Tipo (Busca Segura) ──────────────────────────────────
    if      (tipoBusca.find("filme")        != string::npos) est.recFilme++;
    else if (tipoBusca.find("serie")        != string::npos ||
             tipoBusca.find("série")        != string::npos) est.recSerie++;
    else if (tipoBusca.find("documentario") != string::npos ||
             tipoBusca.find("documentário") != string::npos) est.recDocumentario++;
    else if (tipoBusca.find("anime")        != string::npos) est.recAnime++;
    else if (tipoBusca.find("cartoon")      != string::npos) est.recCartoon++;

    // ── Genero (Busca Segura com tratamento de acentuação) ────
    if      (generoBusca.find("acao")       != string::npos ||
             generoBusca.find("ação")       != string::npos) est.recAcao++;
    else if (generoBusca.find("comedia")    != string::npos ||
             generoBusca.find("comédia")    != string::npos) est.recComedia++;
    else if (generoBusca.find("drama")       != string::npos) est.recDrama++;
    else if (generoBusca.find("terror")      != string::npos) est.recTerror++;
    else if (generoBusca.find("ficcao")     != string::npos ||
             generoBusca.find("ficção")     != string::npos) est.recFicCientifica++;
    else if (generoBusca.find("fantasia")    != string::npos) est.recFantasia++;
}

// =============================================================
//  TOTAIS GERAIS
// =============================================================
int recomendacoesTotais(Estatisticas& est) {
    return est.totRecomendacoes;
}

int visualizacoesTotais(Estatisticas& est) {
    return est.totVisualizacoes;
}

// =============================================================
//  TIPO MAIS / MENOS RECOMENDADO
// =============================================================
void tipoMaisRecomendado(Estatisticas& est) {
    separador("TIPO MAIS RECOMENDADO");

    int vals[5]    = { est.recFilme, est.recSerie, est.recDocumentario,
                       est.recAnime, est.recCartoon };
    string nomes[5]= { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };

    cout << "  " << left << setw(18) << "Tipo"
         << right << setw(12) << "Recomendacoes\n";
    cout << "  " << string(32, '-') << "\n";
    for (int i = 0; i < 5; i++) {
        cout << "  " << left  << setw(18) << nomes[i]
             << right << setw(12) << vals[i] << "\n";
    }

    string mais = tipoComMaiorContagem(est);
    cout << "\n  \033[1;32m>>> Mais recomendado: " << mais << "\033[0m\n";
}

void tipoMenosRecomendado(Estatisticas& est) {
    separador("TIPO MENOS RECOMENDADO");
    string menos = tipoComMenorContagem(est);
    cout << "  \033[1;31m>>> Menos recomendado: " << menos << "\033[0m\n";
}

// =============================================================
//  GENERO MAIS / MENOS RECOMENDADO
// =============================================================
void generoMaisRecomendado(Estatisticas& est) {
    separador("GENERO MAIS RECOMENDADO");

    int vals[6]    = { est.recAcao, est.recComedia, est.recDrama,
                       est.recTerror, est.recFicCientifica, est.recFantasia };
    string nomes[6]= { "Acao", "Comedia", "Drama",
                       "Terror", "Ficcao Cientifica", "Fantasia" };

    cout << "  " << left << setw(20) << "Genero"
         << right << setw(12) << "Recomendacoes\n";
    cout << "  " << string(34, '-') << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "  " << left  << setw(20) << nomes[i]
             << right << setw(12) << vals[i] << "\n";
    }

    string mais = generoComMaiorContagem(est);
    cout << "\n  \033[1;32m>>> Mais recomendado: " << mais << "\033[0m\n";
}

void generoMenosRecomendado(Estatisticas& est) {
    separador("GENERO MENOS RECOMENDADO");
    string menos = generoComMenorContagem(est);
    cout << "  \033[1;31m>>> Menos recomendado: " << menos << "\033[0m\n";
}

// =============================================================
//  TITULO MAIS ASSISTIDO POR TIPO
// =============================================================
void tipoMaisAssistido(ListaDupla& listaCad, Estatisticas& est) {
    (void)est;
    separador("TITULO MAIS ASSISTIDO POR TIPO");

    string tipos[5] = { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };

    cout << "  " << left << setw(16) << "Tipo"
         << setw(32) << "Titulo"
         << right << setw(10) << "Views\n";
    cout << "  " << string(60, '-') << "\n";

    for (int t = 0; t < 5; t++) {
        string   melhorTitulo = "(nenhum)";
        int      melhorViews  = -1;

        NodoDuplo* atual = listaCad.getCabeca();
        while (atual != nullptr) {
            // Conversão de segurança para comparar os tipos de mídia de forma case-insensitive
            if (paraMinusculo(atual->conteudo.tipo) == paraMinusculo(tipos[t]) &&
                atual->conteudo.numViews > melhorViews) {
                melhorViews  = atual->conteudo.numViews;
                melhorTitulo = atual->conteudo.titulo;
            }
            atual = atual->proximo;
        }

        cout << "  " << left
             << setw(16) << tipos[t]
             << setw(32) << melhorTitulo
             << right << setw(10)
             << (melhorViews < 0 ? 0 : melhorViews) << "\n";
    }
}

// =============================================================
//  TITULO MAIS ASSISTIDO POR GENERO
// =============================================================
void generoMaisAssistido(ListaDupla& listaCad, Estatisticas& est) {
    (void)est;
    separador("TITULO MAIS ASSISTIDO POR GENERO");

    string generos[6] = { "Acao", "Comedia", "Drama",
                          "Terror", "Ficcao Cientifica", "Fantasia" };

    cout << "  " << left << setw(20) << "Genero"
         << setw(32) << "Titulo"
         << right << setw(10) << "Views\n";
    cout << "  " << string(64, '-') << "\n";

    for (int g = 0; g < 6; g++) {
        string melhorTitulo = "(nenhum)";
        int    melhorViews  = -1;

        NodoDuplo* atual = listaCad.getCabeca();
        while (atual != nullptr) {
            // Conversão de segurança para comparar os gêneros de forma case-insensitive
            if (paraMinusculo(atual->conteudo.genero) == paraMinusculo(generos[g]) &&
                atual->conteudo.numViews > melhorViews) { // Ops: melhorViews corrigido
                melhorViews  = atual->conteudo.numViews;
                melhorTitulo = atual->conteudo.titulo;
            }
            atual = atual->proximo;
        }

        cout << "  " << left
             << setw(20) << generos[g]
             << setw(32) << melhorTitulo
             << right << setw(10)
             << (melhorViews < 0 ? 0 : melhorViews) << "\n";
    }
}

// =============================================================
//  TITULOS NUNCA SELECIONADOS
// =============================================================
void titulosNaoSelecionados(ListaDupla& listaCad) {
    separador("TITULOS NUNCA SELECIONADOS (Views = 0)");

    int contagem = 0;
    NodoDuplo* atual = listaCad.getCabeca();

    cout << "  " << left << setw(4)  << "Pos"
         << setw(32) << "Titulo"
         << setw(14) << "Tipo"
         << setw(16) << "Genero"
         << right << setw(6) << "Ano\n";
    cout << "  " << string(72, '-') << "\n";

    while (atual != nullptr) {
        if (atual->conteudo.numViews == 0) {
            contagem++;
            cout << "  " << left
                 << setw(4)  << contagem
                 << setw(32) << atual->conteudo.titulo
                 << setw(14) << atual->conteudo.tipo
                 << setw(16) << atual->conteudo.genero
                 << right << setw(6) << atual->conteudo.ano << "\n";
        }
        atual = atual->proximo;
    }

    if (contagem == 0)
        cout << "  \033[1;32mTodos os titulos foram assistidos ao menos uma vez!\033[0m\n";
    else
        cout << "\n  Total: \033[1;31m" << contagem
             << " titulo(s) nunca assistido(s)\033[0m\n";
}

// =============================================================
//  PAINEL CONSOLIDADO
// =============================================================
void exibirEstatisticas(ListaDupla& listaCad, Estatisticas& est) {
    cout << "\n\033[1;34m";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║            ESTATISTICAS DO SISTEMA               ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
    cout << "\033[0m";

    // Totais gerais
    separador("TOTAIS GERAIS");
    cout << "  Total de recomendacoes realizadas : "
         << est.totRecomendacoes << "\n";
    cout << "  Total de visualizacoes registradas: "
         << est.totVisualizacoes << "\n";
    cout << "  Titulos no catalogo               : "
         << listaCad.getTamanho() << "\n";

    // Mais/menos recomendado
    tipoMaisRecomendado(est);
    tipoMenosRecomendado(est);
    generoMaisRecomendado(est);
    generoMenosRecomendado(est);

    // Mais assistido por categoria
    tipoMaisAssistido(listaCad, est);
    generoMaisAssistido(listaCad, est);

    // Nunca selecionados
    titulosNaoSelecionados(listaCad);

    cout << "\n";
}
