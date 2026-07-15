// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cctype>

// 2. Inclusão de bibliotecas criadas
#include "arvore.h"
#include "menu.h"
#include "estetica.h"
#include "listas.h"
#include "pilha.h"
#include "estatisticas.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função para comparar tipos ou gêneros com verificação de casos nas palavras
static bool compararTiposOuGeneros(string s1, string s2) {
    if(s1.empty() || s2.empty()) {
        return false;
    }

    // Converte para minúsculas
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    // Verificação direta ou por substring
    if(s1 == s2 || s1.find(s2) != string::npos || s2.find(s1) != string::npos) {
        return true;
    }

    // Compatibilidade com termos acentuados no catálogo
    if ((s2 == "serie" && s1.find("série") != string::npos) || (s1 == "serie" && s2.find("série") != string::npos)) {
        return true;
    }
    if ((s2 == "acao" && s1.find("ação") != string::npos) || (s1 == "acao" && s2.find("ação") != string::npos)) {
        return true;
    }
    if ((s2 == "comedia" && s1.find("comédia") != string::npos) || (s1 == "comedia" && s2.find("comédia") != string::npos)) {
        return true;
    }
    if ((s2 == "documentario" && s1.find("documentário") != string::npos) || (s1 == "documentario" && s2.find("documentário") != string::npos)) {
        return true;
    }
    if ((s2 == "ficcao" && (s1.find("ficção") != string::npos || s1.find("fic") != string::npos))) {
        return true;
    }
    if ((s2 == "fantasia" && s1.find("fantasia") != string::npos)) {
        return true;
    }

    return false;
}

// 6. Funções auxiliares para converter Enums da Árvore para string
static string tipoParaString(TipoConteudo t) {
    switch(t) {
        case FILME: return "Filme";
        case SERIE: return "Serie";
        case DOCUMENTARIO: return "Documentario";
        case ANIME: return "Anime";
        case CARTOON: return "Cartoon";
        default: return "";
    }
}

static string generoParaString(GeneroConteudo g) {
    switch(g) {
        case ACAO: return "Acao";
        case COMEDIA: return "Comedia";
        case DRAMA: return "Drama";
        case TERROR: return "Terror";
        case FIC_CIENTIFICA: return "Ficcao";
        case FANTASIA: return "Fantasia";
        default: return "";
    }
}

// 7. Função principal de validação do filtro
static bool conteudoAtendeFiltro(const Conteudo& c, NodoA* no) {
    if(no == nullptr) {
        return false;
    }

    // Validação de Tipo
    if(no -> tipoFiltro != QUALQUER_TIPO) {
        string strTipo = tipoParaString(no -> tipoFiltro);
        if(!compararTiposOuGeneros(c.tipo, strTipo)) {
            return false;
        }
    }

    // Validação de Gênero
    if(no -> generoFiltro != QUALQUER_GENERO) {
        string strGenero = generoParaString(no -> generoFiltro);
        if(!compararTiposOuGeneros(c.genero, strGenero)) {
            return false;
        }
    }

    // Validação Cronológica
    if(no -> cronologiaFiltro != QUALQUER_ANO) {
        if(no -> cronologiaFiltro == RECENTE && c.ano < 2000) {
            return false;
        }
        if(no -> cronologiaFiltro == ANTIGO && c.ano >= 2000) {
            return false;
        }
    }

    return true;
}

// 8. Função auxiliar para converter string para int em segurança
static int converterParaInt(const string& valor, int valorPadrao) {
    if(valor.empty()) {
        return valorPadrao;
    }

    int resultado;
    stringstream ss(valor);

    if(!(ss >> resultado)) {
        return valorPadrao;
    }

    return resultado;
}

// 9. Função de construtor da Árvore
Arvore::Arvore() {
    raiz = nullptr;
}

// 10. Função de destrutor da Árvore
Arvore::~Arvore() {
    apagarArvore(raiz);
}

// 11. Função para limpar memória da árvore
void Arvore::apagarArvore(NodoA* atual) {
    if(atual != nullptr) {
        apagarArvore(atual -> sim);
        apagarArvore(atual -> nao);
        delete atual;
    }
}

// 12. Função para montagem da árvore a partir da string de caminho do arquivo txt (Ex: "1-1-2")
void Arvore::inserirPorCaminho(const string& caminho, const string& texto, bool folha, int pTipo, int pGenero, int pCrono) {
    if(caminho.empty()) {
        return;
    }

    // Garante que a raiz exista
    if(raiz == nullptr) {
        raiz = new NodoA();
    }

    // Se o caminho for apenas "1", apenas está sendo configurado a raiz de tudo
    if(caminho == "1") {
        raiz -> texto = texto;
        raiz -> folha = folha;
        raiz -> tipoFiltro = static_cast<TipoConteudo>(pTipo);
        raiz -> generoFiltro = static_cast<GeneroConteudo>(pGenero);
        raiz -> cronologiaFiltro = static_cast<FiltroCronologico>(pCrono);
        return;
    }

    // Navega caractere por caractere (pulando os hífens) a partir da raiz
    NodoA* atual = raiz;
    for(size_t i = 2; i < caminho.length(); i += 2) {
        char direcao = caminho[i]; // '1' = Sim (Esquerda), '2' = Não (Direita)
        bool ehUltimoPasso = (i == caminho.length() - 1);

        if(direcao == '1') {
            if(atual -> sim == nullptr) {
                atual -> sim = new NodoA();
            }
            atual = atual -> sim;
        } else if(direcao == '2') {
            if(atual -> nao == nullptr) {
                atual -> nao = new NodoA();
            }
            atual = atual -> nao;
        }

        // Se chegamos no nó destino exato deste caminho, grava-se os dados
        if(ehUltimoPasso) {
            atual -> texto = texto;
            atual -> folha = folha;
            atual -> tipoFiltro = static_cast<TipoConteudo>(pTipo);
            atual -> generoFiltro = static_cast<GeneroConteudo>(pGenero);
            atual -> cronologiaFiltro = static_cast<FiltroCronologico>(pCrono);
        }
    }
}

// 13. Função para leitura do arquivo txt e geração da Árvore
void Arvore::gerarArvoreDecisao() {
    ifstream arq("arvore_dados.txt");
    if(!arq.is_open()) {
        // Tenta abrir o arquivo alternativo caso o primeiro não exista
        arq.open("arvore_dados2.txt");
        if(!arq.is_open()) {
            centralizarTexto(Estetica::RED + " [ERRO CRÍTICO] Arquivo 'arvore_dados.txt' não encontrado!" + Estetica::RESET);
            return;
        }
    }

    string linha;
    while(getline(arq, linha)) {
        if(linha.empty() || linha[0] == '#') {
            continue;
        }

        string campos[6];
        int i = 0;
        stringstream ss(linha);
        string token;

        // Separa os dados por ponto e vírgula (;)
        while(getline(ss, token, ';') && i < 6) {
            campos[i++] = token;
        }

        if(i < 2) {
            continue;
        }

        string caminho = campos[0];
        string texto = campos[1];
        bool folha = (i > 2 && campos[2] == "1");
        int pTipo = QUALQUER_TIPO;
        int pGenero = QUALQUER_GENERO;
        int pCrono = QUALQUER_ANO;

        if(i > 3) {
            pTipo = converterParaInt(campos[3], QUALQUER_TIPO);
        }
        if(i > 4) {
            pGenero = converterParaInt(campos[4], QUALQUER_GENERO);
        }
        if(i > 5) {
            pCrono = converterParaInt(campos[5], QUALQUER_ANO);
        }

        inserirPorCaminho(caminho, texto, folha, pTipo, pGenero, pCrono);
    }
    arq.close();
}

// 14. Navegação Interativa da Árvore com Pilha
void Arvore::navegarArvore(ListaSimples& listaRec, ListaDupla& listaCad, ListaDupla& listaAssist, Estatisticas& est) {
    if (raiz == nullptr) {
        centralizarTexto(Estetica::RED + "\n [Erro] A árvore de recomendação está vazia!" + Estetica::RESET);
        return;
    }

    Pilha historico;
    NodoA* atual = raiz;
    bool navegando = true;
    bool fimDoCaminho = false; // Variável de controle local para não alterar a estrutura da árvore

    while (navegando && atual != nullptr) {
        system("clear || cls");
        esteticaCabecalhoSistema();
        cout << endl;
        centralizarTexto(Estetica::YELLOW + " (> " + "--------------------------------------------------" + " <) " + Estetica::RESET);
        centralizarTexto(Estetica::GREEN + " --- MEUFLIX: RECOMENDAÇÃO --- " + Estetica::RESET);
        centralizarTexto(Estetica::YELLOW + " (> " + "--------------------------------------------------" + " <) " + Estetica::RESET);
        cout << endl;

        // Verifica se chegou ao fim ou se é uma folha real
        if (fimDoCaminho || atual->folha || (atual->sim == nullptr && atual->nao == nullptr)) {
            centralizarTexto(Estetica::YELLOW + "★ RESULTADO DA SUA PESQUISA ★" + Estetica::RESET);
            cout << endl;
            centralizarTexto("Critério selecionado: " + Estetica::GREEN + atual->texto + Estetica::RESET);
            cout << endl;

            // Filtra e exibe conteúdos
            bool encontrouAlgum = false;
            NodoDuplo* noAux = listaCad.getCabeca();

            cout << left << "  " << setw(5) << "ID" << setw(32) << "Título" << setw(14) << "Tipo" << setw(16) << "Gênero" << right << "Ano\n";
            while (noAux != nullptr) {
                // Lógica de comparação (aqui assumimos uma função de filtro existente no seu sistema)
                if (conteudoAtendeFiltro(noAux->conteudo, atual)) {
                    cout << "  " << left << setw(5) << ("#" + to_string(noAux->conteudo.id))
                         << setw(32) << noAux->conteudo.titulo
                         << setw(14) << noAux->conteudo.tipo
                         << setw(16) << noAux->conteudo.genero
                         << right << setw(4) << noAux->conteudo.ano << "\n";
                    encontrouAlgum = true;
                }
                noAux = noAux->proximo;
            }

            if (!encontrouAlgum) {
                centralizarTexto(Estetica::RED + "Nenhum título corresponde a esses filtros." + Estetica::RESET);
            }

            cout << endl;
            centralizarTexto("1 - Assistir a um título | 2 - Voltar | 0 - Menu Principal");
            int opc; cin >> opc; limparBufferEntrada();

            if (opc == 1) {
                // Lógica de assistir...
            } else if (opc == 2) {
                if (!historico.estaVazio()) {
                    atual = historico.desempilhar();
                    fimDoCaminho = false; // Volta atrás e limpa a flag
                }
            } else if (opc == 0) {
                navegando = false;
            }
            continue;
        }

        // Caso contrário, mostra a pergunta
        centralizarTexto("PERGUNTA: " + atual->texto);
        centralizarTexto("1 - Sim | 2 - Não | 3 - Voltar | 0 - Sair");
        int opcao; cin >> opcao; limparBufferEntrada();

        switch (opcao) {
            case 1:
                if (atual->sim != nullptr) {
                    historico.empilhar(atual);
                    atual = atual->sim;
                } else { fimDoCaminho = true; }
                break;
            case 2:
                if (atual->nao != nullptr) {
                    historico.empilhar(atual);
                    atual = atual->nao;
                } else { fimDoCaminho = true; }
                break;
            case 3:
                if (!historico.estaVazio()) atual = historico.desempilhar();
                break;
            case 0:
                navegando = false;
                break;
        }
    }
}
