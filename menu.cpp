// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 2. Inclusão de bibliotecas criadas
#include "menu.h"
#include "arvore.h"
#include "estetica.h"
#include "admin.h"
#include "estatisticas.h"
#include "usuario.h"

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

                break;
            }
            case 2: {
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

                cadastrarUsuario(ListaU, login, senha, COMUM);

                centralizarTexto("\n[Sucesso] Sua conta foi criada com sucesso! [Sucesso]");

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
                Conteudo novo;

                // Solicitação dos dados do novo título
                centralizarTexto("Título: ");
                getline(cin, novo.titulo);
                centralizarTexto("Tipo: ");
                getline(cin, novo.tipo);
                centralizarTexto("Gênero: ");
                getline(cin, novo.genero);
                centralizarTexto("Ano: ");
                cin >> novo.ano;
                limparBufferEntrada();

                Admin::cadastrarTitulo(listaCad, listaAssist, novo);
                break;
            }
            case 2: {
                esteticaCabecalhoSistema();
                string titulo;
                centralizarTexto("Digite o título para remover: ");
                getline(cin, titulo);

                Admin::removerTitulo(listaCad, listaAssist, listaRec, titulo);
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
                break;
            }
            default: {
                centralizarTexto("Opção inválida!");
                break;
            }
        }
        //system("pause");
        cout << "\nPressione [Enter] para continuar...";
    }
}

// 7. Função para perspectiva do usuário comum
void povUsuarioComum(Usuario* usuarioLogado, ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est) {
    int opcao = 0;

    while(opcao != 3) {
        esteticaCabecalhoSistema();
        centralizarTexto(Estetica::GREEN + "--- BEM-VINDO AO MEUFLIX ---");
        centralizarTexto("1 - Iniciar Recomendação (Árvore)");
        centralizarTexto("2 - Ver Ranking Mais Assistidos");
        centralizarTexto("3 - Sair");

        centralizarTexto("\nEscolha uma opção: ");
        cin >> opcao;
        limparBufferEntrada();

        switch(opcao) {
            case 1: {
                arv.inserirFiltrar(arv.raiz, listaCad, listaRec);
                break;
            }
            case 2: {
                listaMaisAssistidos(listaAssist);
                break;
            }
            case 3: {
                break;
            }
            default: {
                centralizarTexto("Opção inválida!");
                break;
            }
        }
        system("pause");
    }
}

