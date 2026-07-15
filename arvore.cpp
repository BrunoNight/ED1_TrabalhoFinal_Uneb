// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

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

// 5. Função auxiliar interna para comparar strings ignorando maiúsculas e acentos básicos
static bool compararTiposOuGeneros(string s1, string s2) {
    // Converte para minúsculas
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    return (s1 == s2 || s1.find(s2) != string::npos || s2.find(s1) != string::npos);
}

// 6. Função auxiliar para converter string para int
int converterParaInt(const std::string& valor, int valorPadrao) {
    if (valor.empty()) {
        return valorPadrao;
    }

    int resultado;
    std::stringstream ss(valor);

    // Tenta extrair o valor. Se falhar, retorna o valor padrão.
    if (!(ss >> resultado)) {
        return valorPadrao;
    }

    return resultado;
}

// 7. Função de construtor da Árvore
Arvore::Arvore() {
    raiz = nullptr;
}

// 8. Função de destrutor da Árvore
Arvore::~Arvore() {
    apagarArvore(raiz);
}

// 9. Função para limpar memória da árvore
void Arvore::apagarArvore(NodoA* atual) {
    if (atual != nullptr) {
        apagarArvore(atual->sim);
        apagarArvore(atual->nao);
        delete atual;
    }
}

// 10. Função para montagem da árvore a partir da string de caminho do arquivo txt (Ex: "1-1-2")
void Arvore::inserirPorCaminho(const string& caminho, const string& texto, bool folha, int pTipo, int pGenero, int pCrono) {
    if (caminho.empty()) return;

    // Garante que a raiz exista
    if (raiz == nullptr) {
        raiz = new NodoA();
    }

    // Se o caminho for apenas "1", apenas está sendo configurado a raiz de tudo
    if (caminho == "1") {
        raiz->texto = texto;
        raiz->folha = folha;
        raiz->tipoFiltro = static_cast<TipoConteudo>(pTipo);
        raiz->generoFiltro = static_cast<GeneroConteudo>(pGenero);
        raiz->cronologiaFiltro = static_cast<FiltroCronologico>(pCrono);
        return;
    }

    // Navega caractere por caractere (pulando os hífens) a partir da raiz
    NodoA* atual = raiz;
    for (size_t i = 2; i < caminho.length(); i += 2) {
        char direcao = caminho[i]; // '1' = Sim (Esquerda), '2' = Não (Direita)
        bool ehUltimoPasso = (i == caminho.length() - 1);

        if (direcao == '1') {
            if (atual->sim == nullptr) {
                atual->sim = new NodoA();
            }
            atual = atual->sim;
        } else if (direcao == '2') {
            if (atual->nao == nullptr) {
                atual->nao = new NodoA();
            }
            atual = atual->nao;
        }

        // Se chegamos no nó destino exato deste caminho, grava-se os dados
        if (ehUltimoPasso) {
            atual->texto = texto;
            atual->folha = folha;
            atual->tipoFiltro = static_cast<TipoConteudo>(pTipo);
            atual->generoFiltro = static_cast<GeneroConteudo>(pGenero);
            atual->cronologiaFiltro = static_cast<FiltroCronologico>(pCrono);
        }
    }
}

// 11. Função para leitura do arquivo txt e geração da Árvore
void Arvore::gerarArvoreDecisao() {
    ifstream arq("arvore_dados.txt");
    if (!arq.is_open()) {
        // Tenta abrir o arquivo alternativo caso o primeiro não exista
        arq.open("arvore_dados2.txt");
        if (!arq.is_open()) {
            cout << Estetica::RED << " [ERRO CRÍTICO] Arquivo 'arvore_dados.txt' não encontrado!" << Estetica::RESET << endl;
            return;
        }
    }

    string linha;
    while (getline(arq, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        string campos[6];
        int i = 0;
        stringstream ss(linha);
        string token;

        // Separa os dados por ponto e vírgula (;)
        while (getline(ss, token, ';') && i < 6) {
            campos[i++] = token;
        }

        if (i < 2) continue;

        string caminho = campos[0];
        string texto = campos[1];
        bool folha = (i > 2 && campos[2] == "1");
        int pTipo = QUALQUER_TIPO;
        int pGenero = QUALQUER_GENERO;
        int pCrono = QUALQUER_ANO;

        if (i > 3) {
            pTipo = converterParaInt(campos[3], QUALQUER_TIPO);
        }
        if (i > 4) {
            pGenero = converterParaInt(campos[4], QUALQUER_GENERO);
        }
        if (i > 5) {
            pCrono = converterParaInt(campos[5], QUALQUER_ANO);
        }

        inserirPorCaminho(caminho, texto, folha, pTipo, pGenero, pCrono);
    }
    arq.close();
}

// 12. Navegação Interativa da Árvore com Pilha (100% Funcional e com opção Voltar)
void Arvore::inserirFiltrar(NodoA* atual, ListaDupla& listaCad, ListaSimples& listaRec, Estatisticas& est) {
    if (atual == nullptr) {
        centralizarTexto(Estetica::RED + " [Erro] A árvore de recomendação não foi carregada corretamente." + Estetica::RESET);
        cout << "\nPressione [Enter] para continuar...";
        cin.get();
        return;
    }

    Pilha historico;
    bool fimDoCaminho = false;

    while (atual != nullptr) {
        esteticaCabecalhoSistema();


        // Verificando se chegou ao fim do caminho
        if (atual->folha == true || fimDoCaminho == true) {
            centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
            centralizarTexto(Estetica::GREEN + " PERFIL IDENTIFICADO: ");
            centralizarTexto(atual->texto);
            centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) \n");

            listaRec.limpar();
            NodoDuplo* nav = listaCad.getCabeca();

            string stringTipo = "";
            string stringGenero = "";

            switch(atual->tipoFiltro) {
                case FILME: stringTipo = "Filme"; break;
                case SERIE: stringTipo = "Série"; break;
                case DOCUMENTARIO: stringTipo = "Documentário"; break;
                case ANIME: stringTipo = "Anime"; break;
                case CARTOON: stringTipo = "Cartoon"; break;
                default: stringTipo = ""; break;
            }

            switch(atual->generoFiltro) {
                case ACAO: stringGenero = "Ação"; break;
                case COMEDIA: stringGenero = "Comédia"; break;
                case DRAMA: stringGenero = "Drama"; break;
                case TERROR: stringGenero = "Terror"; break;
                case FIC_CIENTIFICA: stringGenero = "Ficção Científica"; break;
                case FANTASIA: stringGenero = "Fantasia"; break;
                default: stringGenero = ""; break;
            }

            // Varre o catálogo buscando conteúdos compatíveis com o perfil identificado
            while (nav != nullptr) {
                Conteudo& c = nav->conteudo;

                // Tolerância para acentos e variações de maiúsculas/minúsculas
                bool tipoOK = (atual->tipoFiltro == QUALQUER_TIPO) ||
                              (c.tipo == stringTipo) ||
                              (atual->tipoFiltro == FILME && (c.tipo == "Filme" || c.tipo == "filme")) ||
                              (atual->tipoFiltro == SERIE && (c.tipo == "Serie" || c.tipo == "serie" || c.tipo == "Série" || c.tipo == "série")) ||
                              (atual->tipoFiltro == DOCUMENTARIO && (c.tipo == "Documentario" || c.tipo == "documentario" || c.tipo == "Documentário" || c.tipo == "documentário")) ||
                              (atual->tipoFiltro == ANIME && (c.tipo == "Anime" || c.tipo == "anime")) ||
                              (atual->tipoFiltro == CARTOON && (c.tipo == "Cartoon" || c.tipo == "cartoon"));

                bool generoOK = (atual->generoFiltro == QUALQUER_GENERO) ||
                                (c.genero == stringGenero) ||
                                (atual->generoFiltro == ACAO && (c.genero == "Acao" || c.genero == "acao" || c.genero == "Ação" || c.genero == "ação")) ||
                                (atual->generoFiltro == COMEDIA && (c.genero == "Comedia" || c.genero == "comedia" || c.genero == "Comédia" || c.genero == "comédia")) ||
                                (atual->generoFiltro == DRAMA && (c.genero == "Drama" || c.genero == "drama")) ||
                                (atual->generoFiltro == TERROR && (c.genero == "Terror" || c.genero == "terror")) ||
                                (atual->generoFiltro == FIC_CIENTIFICA && (c.genero == "Ficcao Cientifica" || c.genero == "ficcao cientifica" || c.genero == "Ficção Científica" || c.genero == "ficção científica")) ||
                                (atual->generoFiltro == FANTASIA && (c.genero == "Fantasia" || c.genero == "fantasia"));

                bool cronoOK = true;
                if (atual->cronologiaFiltro == RECENTE) cronoOK = (c.ano >= 2000);
                else if (atual->cronologiaFiltro == ANTIGO) cronoOK = (c.ano < 2000);

                if (tipoOK && generoOK && cronoOK) {
                    listaRec.inserirOrdenado(c);
                }
                nav = nav->proximo;
            }

            // Registra a estatística da recomendação gerada para o admin
            registrarRecomendacao(est, stringTipo.empty() ? "Geral" : stringTipo, stringGenero.empty() ? "Geral" : stringGenero);

            // Exibe os resultados na tela
            if (listaRec.estaVazia()) {
                centralizarTexto(Estetica::RED + " [!] Nenhum título cadastrado corresponde a este perfil exato." + Estetica::RESET);
                centralizarTexto("Tente cadastrar novos conteúdos ou refazer o teste com outras escolhas.\n");
            } else {
                centralizarTexto(Estetica::GREEN + "=== TÍTULOS RECOMENDADOS PARA VOCÊ ===" + Estetica::RESET);
                listaRec.exibir();

                cout << endl;
                centralizarTexto("Deseja assistir a algum dos títulos recomendados agora? (s/n): ");
                char esc;
                cin >> esc;
                limparBufferEntrada();

                if (esc == 's' || esc == 'S') {
                    string tituloEscolhido;
                    centralizarTexto("Digite o nome exato do título: ");
                    getline(cin, tituloEscolhido);
                    assistirConteudo(listaCad, listaCad, tituloEscolhido);
                }
            }

            cout << "\nPressione [Enter] para voltar ao menu...";
            cin.get();
            break; // Encerra a árvore após dar a recomendação
        }

        // Se não for folha, exiba a pergunta e tente avançar
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
        centralizarTexto(Estetica::GREEN + " PERGUNTA: ");
        centralizarTexto(atual->texto);
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) \n");

        centralizarTexto("1 - Sim");
        centralizarTexto("2 - Não");
        centralizarTexto(Estetica::YELLOW + "3 - Voltar (Pergunta Anterior)" + Estetica::RESET);
        centralizarTexto(Estetica::RED + "0 - Cancelar e Sair" + Estetica::RESET);
        cout << endl;
        centralizarTexto("Escolha uma opção: ");

        int opcao = -1;
        if (!(cin >> opcao)) {
            cin.clear();
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada(); // IMPEDE QUE PERGUNTAS SEJAM PULADAS

        switch (opcao) {
            case 1: // SIM -> Desce para a esquerda
                if (atual->sim != nullptr) {
                    historico.empilhar(atual);
                    atual = atual->sim;
                } else {
                    fimDoCaminho = true;
                    continue;
                }
                break;

            case 2: // NÃO -> Desce para a direita
                if (atual->nao != nullptr) {
                    historico.empilhar(atual);
                    atual = atual->nao;
                } else {
                    fimDoCaminho = true;
                    continue;
                }
                break;

            case 3: // VOLTAR: Desempilha a última pergunta respondida
                if (historico.estaVazio()) {
                    cout << endl;
                    centralizarTexto(Estetica::RED + " [!] Você já está na primeira pergunta!" + Estetica::RESET);
                    cout << "\nPressione [Enter] para continuar...";
                    cin.get();
                } else {
                    NodoA* anterior = historico.desempilhar();
                    if (anterior != nullptr) {
                        atual = anterior; // Retorna ao nó anterior
                        fimDoCaminho = false; // Garante que ao voltar, a flag de fim de caminho seja resetada
                    }
                }
                break;

            case 0: // SAIR
                centralizarTexto(" [~] Cancelando recomendação...");
                return;

            default:
                centralizarTexto(Estetica::RED + " [!] Opção inválida! Escolha 1, 2, 3 ou 0." + Estetica::RESET);
                cout << "\nPressione [Enter] para continuar...";
                cin.get();
                break;
        }
    }
}
