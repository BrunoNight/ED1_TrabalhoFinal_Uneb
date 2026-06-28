// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 2. Inclusão de bibliotecas criadas
#include "menu.h"
#include "estetica.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função para limpar mensagens de erro por digitação inválida no cin
void limparBufferEntrada() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// 6. Função para exibição e funcionamento do menu inicial do sistema
void executarSistema() { //** Dentro dos parênteses terá as listas e funcionalidades de outras partes do sistema
    int opcao = 0;

    while(opcao != 3) {
        esteticaCabeçalhoSistema();
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
                esteticaCabeçalhoSistema();
                string login, senha;
                centralizarTexto(Estetica::YELLOW + " (> " + bordaB + Estetica::YELLOW + " <) ");
                centralizarTexto(Estetica::YELLOW + "TELA DE LOGIN");
                centralizarTexto(Estetica::RED + "Digite o Login: ");
                cin >> login;
                centralizarTexto(Estetica::RED + "Digite a Senha: ");
                cin >> senha;

                // Busca o usuário na lista de usuários cadastrados
                Usuario* usuarioLogado = logarUsuario(listaUsuarios, login, senha);

                if(usuarioLogado == nullptr) {
                    centralizarTexto("\n[Aviso] Credenciais incorretas ou usuário inexistente! [Aviso]");
                } else {
                    centralizarTexto("\n[Sucesso] Bem-vindo(a), " + usuarioLogado -> login + "! [Sucesso]");

                    // Redireciona conforme o nível de permissão
                    if(usuarioLogado -> tipo == ADMINISTRADOR) {
                        povAdministrador(); //** Dentro dos parênteses terá as listas e funcionalidades de outras partes do sistema
                    } else {
                        povUsuarioComum(); //** Dentro dos parênteses terá as listas e funcionalidades de outras partes do sistema
                    }
                }

                break;
            }
            case 2: {
                esteticaCabeçalhoSistema();
                string login, senha;
                centralizarTexto(Estetica::YELLOW + " (> " + bordaB + Estetica::YELLOW + " <) ");
                centralizarTexto(Estetica::YELLOW + "TELA DE CADASTRO");
                centralizarTexto(Estetica::RED + "Digite o Login: ");
                cin >> login;
                centralizarTexto(Estetica::RED + "Digite a Senha: ");
                cin >> senha;

                cadastrarUsuario(listaUsuarios, login, senha, COMUM);

                centralizarTexto("\n[Sucesso] Sua conta foi criada com sucesso! [Sucesso]");

                break;
            }
            case 3: {
                esteticaCabeçalhoSistema();
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

