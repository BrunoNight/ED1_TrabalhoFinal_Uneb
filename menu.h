// 1. Inicialização da inclusão do header
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

// 2. Incluir bibliotecas existentes
//#include <windows.h>

// 3. Declaração de classes das bibliotecas criadas para evitar inclusão cíclica
struct Usuario;
class ListaUsuarios;
class ListaSimples;
class ListaDupla;
class Arvore;
struct Estatisticas;

// 4. Funções que serão executadas no sistema
// // 4.1. INICIALIZAR SISTEMA (TELA INICIAL), COM AS FUNÇÕES DE LOGIN E CADASTRO DE USUÁRIO
void executarSistema(ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est);
// // 4.2. NAVEGAÇÃO PELO SISTEMA NA PERSPECTIVA DO ADMINISTRADOR
void povAdministrador(Usuario* usuarioLogado, ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est);
// // 4.3. NAVEGAÇÃO PELO SISTEMA NA PERSPECTIVA DO USUÁRIO COMUM
void povUsuarioComum(Usuario* usuarioLogado, ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est);
void login(ListaUsuarios& ListaU, ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, Arvore& arv, Estatisticas& est);
void cadastro(ListaUsuarios& ListaU);

#endif // MENU_H_INCLUDED
