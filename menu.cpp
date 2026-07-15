// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>
#include <iomanip>

// 2. Inclusão de bibliotecas criadas
#include "menu.h"
#include "arvore.h"
#include "estetica.h"
#include "estatisticas.h"
#include "usuario.h"
#include "conteudo.h"
#include "listas.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função para exibição e funcionamento do menu inicial do sistema
void executarSistema(ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est) {
    int opcao = 0;

    while(opcao != 3) {
        esteticaCabecalhoSistema();
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
        centralizarTexto(Estetica::RED + "1 - Fazer Login");
        centralizarTexto(Estetica::RED + "2 - Cadastre-se");
        centralizarTexto(Estetica::RED + "3 - Sair do Sistema");
        centralizarTexto(Estetica::RED + "Escolha uma opção: ");
        cin >> opcao;
        limparBufferEntrada();
        cout << endl;
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");

        switch(opcao) {
            case 1: {
                login(ListaU, listaCad, listaAssist, listaRec, arv, est);
                break;
            }
            case 2: {
                cadastro(ListaU);
                break;
            }
            case 3: {
                esteticaCabecalhoSistema();
                centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
                centralizarTexto("\n[Saindo] Saindo do sistema... [Saindo]");
                centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");

                break;
            }
            default: {
                centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
                centralizarTexto("\n[Aviso] Opção inválida! Tente novamente! [Aviso]");
                centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");

                break;
            }
        }

        cout << "\nPressione [Enter] para continuar...\n";
        cin.get();
    }
}

void login(ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est) {
    esteticaCabecalhoSistema();
    string login, senha;
    centralizarTexto(Estetica::YELLOW + " (> " + bordaB + Estetica::YELLOW + " <) ");
    centralizarTexto(Estetica::YELLOW + "TELA DE LOGIN");
    centralizarTexto(Estetica::RED + "Digite o Login: ");
    cin >> login;
    limparBufferEntrada();
    centralizarTexto(Estetica::RED + "Digite a Senha: ");
    cin >> senha;
    limparBufferEntrada();

    // Busca o usuário na lista de usuários cadastrados
    Usuario* usuarioLogado = logarUsuario(ListaU, login, senha);

    if(usuarioLogado == nullptr) {
        centralizarTexto("\n[Aviso] Credenciais incorretas ou usuário inexistente! [Aviso]");
    } else {
        centralizarTexto("\n[Sucesso] Bem-vindo(a), " + usuarioLogado -> login + "! [Sucesso]");

        // Redireciona conforme o nível de permissão
        if(usuarioLogado -> tipo == ADMINISTRADOR) {
            povAdministrador(usuarioLogado, ListaU, listaCad, listaAssist, listaRec, arv, est);
        } else {
            povUsuarioComum(usuarioLogado, ListaU, listaCad, listaAssist, listaRec, arv, est);
        }
    }
}

void cadastro(ListaUsuarios& ListaU) {
    esteticaCabecalhoSistema();
    string login, senha;
    centralizarTexto(Estetica::YELLOW + " (> " + bordaB + Estetica::YELLOW + " <) ");
    centralizarTexto(Estetica::YELLOW + "TELA DE CADASTRO");
    centralizarTexto(Estetica::RED + "Digite o Login: ");
    cin >> login;
    limparBufferEntrada();
    centralizarTexto(Estetica::RED + "Digite a Senha: ");
    cin >> senha;
    limparBufferEntrada();

    if(cadastrarUsuario(ListaU, login, senha, COMUM) == 1) {
        centralizarTexto("\n[Sucesso] Sua conta foi criada com sucesso! [Sucesso]");
    }
}

// 6. Função para perspectiva do administrador do sistema
void povAdministrador(Usuario* usuarioLogado, ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est) {
    int opcao = 0;

    while(opcao != 6) {
        esteticaCabecalhoSistema();
        centralizarTexto(Estetica::YELLOW + "--- MENU ADMINISTRADOR ---");
        centralizarTexto("1 - Cadastrar Título");
        centralizarTexto("2 - Remover Título");
        centralizarTexto("3 - Listar Conteúdos");
        centralizarTexto("4 - Ver Estatísticas");
        centralizarTexto("5 - Gerenciar Usuários");
        centralizarTexto("6 - Voltar ao Menu Inicial");

        centralizarTexto("\nEscolha uma opção: ");
        cin >> opcao;
        limparBufferEntrada();

        switch(opcao) {
            case 1: {
                esteticaCabecalhoSistema();
                centralizarTexto(Estetica::YELLOW + "CADASTRO DE NOVO TÍTULO" + Estetica::RESET);

                string titulo, tipo, genero;
                int ano;

                // Solicitação dos dados do novo título
                centralizarTexto("Título: ");
                getline(cin, titulo);
                centralizarTexto("Tipo: ");
                getline(cin, tipo);
                centralizarTexto("Gênero: ");
                getline(cin, genero);
                centralizarTexto("Ano: ");
                cin >> ano;
                limparBufferEntrada();

                cadastrarConteudo(listaCad, listaAssist, titulo, tipo, genero, ano);
                break;
            }
            case 2: {
                esteticaCabecalhoSistema();
                string titulo;
                centralizarTexto("Digite o título para remover: ");
                getline(cin, titulo);

                removerConteudo(listaCad, listaAssist, listaRec, titulo);
                break;
            }
            case 3: {
                listaCadastrados(listaCad);
                break;
            }
            case 4: {
                tipoMaisRecomendado(est);
                generoMaisRecomendado(est);
                break;
            }
            case 5: {
                listarUsuarios(ListaU);
                break;
            }
            case 6: {
                centralizarTexto("Voltando...");
                return;
            }
            default: {
                centralizarTexto("Opção inválida!");
                break;
            }
        }
        cout << "\nPressione [Enter] para continuar...\n";
        cin.get();
    }
}

// 7. Função para perspectiva do usuário comum
void povUsuarioComum(Usuario* usuarioLogado, ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est) {
    int opcao = 0;

    while(opcao != 4) {
        esteticaCabecalhoSistema();
        centralizarTexto(Estetica::GREEN + "--- BEM-VINDO AO MEUFLIX ---");
        centralizarTexto("1 - Iniciar Recomendação (Árvore)");
        centralizarTexto("2 - Ver Ranking Mais Assistidos");
        centralizarTexto("3 - Listar Conteúdos");
        centralizarTexto("4 - Sair");

        centralizarTexto("\nEscolha uma opção: ");
        cin >> opcao;
        limparBufferEntrada();

        switch(opcao) {
            case 1: {
                arv.inserirFiltrar(arv.raiz, listaCad, listaRec, est);
                break;
            }
            case 2: {
                listaMaisAssistidos(listaAssist);
                break;
            }
            case 3: {
                if (listaCad.getCabeca() == nullptr) {
                    centralizarTexto("  [Lista vazia]\n");
                    break;
                }

                cout << left << " "
                    << setw(4) << "Id"
                    << setw(32) << "Titulo"
                    << setw(14) << "Visualizações\n";
                    cout << " " + string(78, '-') + "\n";

                NodoDuplo* atual = listaCad.getCabeca();

                while (atual != nullptr) {
                    Conteudo& c = atual->conteudo;
                    cout << " " << left
                        << setw(4) << c.id
                        << setw(32) << c.titulo
                        << setw(14) << c.numViews
                        << "\n";

                    atual = atual->proximo;
                }

                centralizarTexto("Selecione conteúdo (digite o título): ");
                string titulo;
                getline(cin, titulo);

                atual = listaCad.getCabeca();
                Conteudo c;
                bool encontrado = false; 

                while (atual != nullptr) {
                    if(atual->conteudo.titulo == titulo) {
                        c = atual->conteudo;
                        encontrado = true;
                        break;
                    }
                    atual = atual->proximo;
                }



                if (!encontrado) {
                    centralizarTexto("\n[Erro] Título não encontrado!\n");
                    break; 
                }

                system("clear || cls");

                cout << left << " " << setw(5) << "ID"
                    << setw(32) << "Nome"
                    << setw(14) << "Tipo"
                    << setw(18) << "Gênero"
                    << right << "Visualizações\n";

                    cout << " " + string(78, '-') + "\n";

                    cout << " " << left << setw(5) << ("#" + to_string(c.id))
                        << setw(32) << c.titulo
                        << setw(14) << c.tipo
                        << setw(18) << c.genero
                        << right << std::setw(8) << c.numViews << "\n";

                int opc = 0;

                centralizarTexto("1. Assistir");
                centralizarTexto("2. Voltar ao menu");

                while(opc != 2) {
                    cout << "Selecione uma das opções: ";
                    cin >> opc;
                    limparBufferEntrada();

                    switch(opc) {
                        case 1: {
                            assistirConteudo(listaCad, listaAssist, titulo);
                            registrarRecomendacao(est, c.tipo, c.genero);

                            float nota = -1.0f;
                            cout << "\n";
                            centralizarTexto("Avalie o filme (Digite de 0 a 5): ");
                            cin >> nota;
                            limparBufferEntrada();
                            
                            if (nota >= 0.0f && nota <= 5.0f) {
                                avaliarConteudo(listaCad, listaAssist, titulo, nota);
                            } else {
                                avaliarConteudo(listaCad, listaAssist, titulo, 3);
                            }

                            opc = 2; 
                            continue;
                        }
                        case 2:
                            continue;
                        default:
                            cout << "Opção Inválida!\n";
                    }
                }
                
                break;
            }
            case 4: {
                cout << "\n[Saindo do sistema...]";
                return;
            }
            default: {
                centralizarTexto("Opção inválida!");
                break;
            }
        }

        cout << "\nPressione [Enter] para continuar...\n";
        cin.get();
    }
}

