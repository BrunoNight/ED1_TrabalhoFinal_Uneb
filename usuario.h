// 1. Inicialização da inclusão do header
#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 3. Declaração de classes das bibliotecas criadas para evitar inclusão cíclica
class ListaUsuarios;

// 4. Definição dos tipos de perfis de usuário
enum perfil {ADMINISTRADOR, COMUM};

// 5. Classe para definir usuario
class Usuario { public:
    int id;
    std::string login;
    std::string senha;
    perfil tipo;
    Usuario* prox;
};

// 6. Funções que serão executadas no sistema
// // 6.1. ADMINISTRADOR E COMUM
Usuario* logarUsuario(ListaUsuarios& listaUsuarios, const std::string login, const std::string senha);
void cadastrarUsuario(ListaUsuarios& listaUsuarios, const std::string login, const std::string senha, perfil tipo);
void alterarLogin(ListaUsuarios& listaUsuarios, const std::string login, const std::string nvLogin);
void alterarSenha(ListaUsuarios& listaUsuarios, const std::string login, const std::string nvSenha);
// // 6.2. ADMINISTRADOR
void listarUsuarios(ListaUsuarios& listaUsuarios);
void excluirUsuario(ListaUsuarios& listaUsuarios, const std::string login);

#endif // USUARIO_H_INCLUDED

