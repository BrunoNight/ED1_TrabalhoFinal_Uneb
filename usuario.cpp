// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 2. Inclusão de bibliotecas criadas
#include "usuario.h"
#include "estetica.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função de login do usuário no sistema
Usuario* logarUsuario(ListaUsuarios& listaUsuarios, string login, string senha) {
    Usuario* atual = listaUsuarios.inicio;

    // Varre a lista comparando as strings
    while(atual != nullptr) {
        if(atual -> login == login && atual -> senha == senha) {
            return atual;
        }
        atual = atual -> prox;
    }

    return nullptr; // Retorna nulo se o usuário não for encontrado ou a senha for inválida
}

// 6. Função de cadastro de usuário no sistema
void cadastrarUsuario(ListaUsuarios& listaUsuarios, string login, string senha, perfil tipo) {
    Usuario* atual = listaUsuarios.inicio;
    int novoId = 1;

    // Varre a lista para impedir duplicação de logins e buscar novo ID
    while(atual != nullptr) {
        if(atual -> login == login) {
            centralizarTexto("\n[Aviso] O login informado já está em uso! [Aviso]");
            return;
        }
        if(atual -> id >= novoId) {
            novoId = atual -> id + 1;
        }
        atual = atual -> prox;
    }

    // Alocação do novo nó (usuário)
    Usuario* novoUsuario = new Usuario;
    novoUsuario -> id = novoId;
    novoUsuario -> login = login;
    novoUsuario -> senha = senha;
    novoUsuario -> tipo = tipo;
    novoUsuario -> prox = nullptr;

    // Inserção do nó no final da lista
    if(listaUsuarios.inicio == nullptr) {
        listaUsuarios.inicio = novoUsuario;
    } else {
        atual = listaUsuarios.inicio;
        while(atual->prox != nullptr) {
            atual = atual -> prox;
        }
        atual -> prox = novoUsuario;
    }
}

// 7. Função para alteração do login
void alterarLogin(ListaUsuarios& listaUsuarios, string login, string nvLogin) {
    Usuario* atual = listaUsuarios.inicio;

    // Verificar se o novo login desejado ainda não está sendo usado por outra pessoa
    while(atual != nullptr) {
        if(atual -> login == nvLogin) {
            centralizarTexto("\n[Aviso] O novo login '" << nvLogin << "' já está sendo usado! [Aviso]");
            return;
        }
        atual = atual -> prox;
    }

    // Varredura para encontrar o usuário autenticado e efetuar a troca de login
    atual = listaUsuarios.inicio;
    while(atual != nullptr) {
        if(atual -> login == login) {
            atual -> login = nvLogin;
            return;
        }
        atual = atual -> prox;
    }
}

// 8. Função para alteração da senha
void alterarSenha(ListaUsuarios& listaUsuarios, string login, string nvSenha) {
    Usuario* atual = listaUsuarios.inicio;

    // Varredura para encontrar o usuário e efetuar a troca de senha
    while(atual != nullptr) {
        if (atual -> login == login) {
            atual -> senha = nvSenha;
            return;
        }
        atual = atual -> prox;
    }
}

// 8. Função para listar usuários do sistema
void listarUsuarios(ListaUsuarios& listaUsuarios) {
    Usuario* atual = listaUsuarios.inicio;

    if(atual == nullptr) {
        centralizarTexto("\n[Aviso] Nenhum usuário cadastrado no sistema. [Aviso]");
        return;
    }

    // Percorre a lista, imprimindo as informações
    while(atual != nullptr) {
        cout << Estetica::RED << "ID: " << atual -> id << " | Login: " << atual -> login << " | Perfil: " << (atual -> tipo == ADMINISTRADOR ? "Administrador" : "Comum") << endl;
        atual = atual -> prox;
    }
}

// 8. Função para excluir usuário do sistema
void excluirUsuario(ListaUsuarios& listaUsuarios, string login) {
    Usuario* atual = listaUsuarios.inicio;
    Usuario* anterior = nullptr;

    // Varredura para encontrar o nó a ser removido e mantendo o anterior logo atrás enquanto não encontra
    while(atual != nullptr) {
        if (atual -> login == login) {
            // Deslocamento de ponteiros para desconectar o nó da lista
            if(anterior == nullptr) {
                listaUsuarios.inicio = atual -> prox;
            } else {
                anterior -> prox = atual -> prox;
            }

            delete atual;
            return;
        }

        anterior = atual;
        atual = atual -> prox;
    }
}
