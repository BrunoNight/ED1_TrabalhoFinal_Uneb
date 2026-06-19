// 1. Inicialização da inclusão do header
#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 3. Libera o uso direto dos tipos da biblioteca padrão (como string)
using namespace std;

// 4. Declaração de classes das bibliotecas criadas para evitar inclusão cíclica
class listarUsuarios;

// 5. Definição dos tipos de perfis de usuário
enum perfil {ADMINISTRADOR, COMUM};

// 6. Struct para definir usuario
typedef struct Usuario {
    int id;
    string login;
    string senha;
    perfil tipo;
} Usuario;

// 7. Funções que serão executadas no sistema
// // 7.1. ADMINISTRADOR E COMUM
Usuario* logarUsuario(ListaUsuarios& listaUsuarios, string login, string senha);
void cadastrarUsuario(ListaUsuarios& listaUsuarios, string login, string senha, perfil tipo);
void alterarLogin(ListaUsuarios& listaUsuarios, string login, string nvLogin);
void alterarSenha(ListaUsuarios& listaUsuarios, string login, string nvSenha);
// // 7.2. ADMINISTRADOR
void listarUsuarios(ListaUsuarios& listaUsuarios);
void excluirUsuario(ListaUsuarios& listaUsuarios, string login);

#endif // USUARIO_H_INCLUDED
