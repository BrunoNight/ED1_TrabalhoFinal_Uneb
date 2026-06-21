// 1. Inicialização da inclusão do header
#ifndef CONTEUDO_H_INCLUDED
#define CONTEUDO_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>

// 3. Declaração de classes das bibliotecas criadas para evitar inclusão cíclica
class ListaContCad;
class ListaContRec;
class ListaContMaisAssist;

// 4. Struct para definir conteúdo
typedef struct Conteudo {
    int id;
    std::string titulo;
    std::string tipo;
    std::string genero;
    int ano;
    int numViews;
} Conteudo;

// 5. Funções que serão executadas no sistema
// // 5.1. CADASTRAR E REMOVER
void cadastrarConteudo(ListaContCad& listaCad, ListaContMaisAssist& listaAssist, std::string titulo, std::string tipo, std::string genero, int ano);
void removerConteudo(ListaContCad& listaCad, ListaContMaisAssist& listaAssist, ListaContRec& listaRec, int id);
// // 5.2. LISTAGEM
void listaCadastrados(ListaContCad& listaCad);
void listaRecomendados(ListaContRec& listaRec);
void listaMaisAssistidos(ListaContMaisAssist& listaAssist);
// // 5.3. ASSISTIR
void assistirConteudo(ListaContCad& listaCad, ListaContMaisAssist& listaAssist, int id);

#endif // CONTEUDO_H_INCLUDED
