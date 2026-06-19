// 1. Inicialização da inclusão do header
#ifndef CONTEUDO_H_INCLUDED
#define CONTEUDO_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 3. Libera o uso direto dos tipos da biblioteca padrão (como string)
using namespace std;

// 4. Declaração de classes das bibliotecas criadas para evitar inclusão cíclica
class ListaContCad;
class ListaContRec;
class ListaContMaisAssist;

// 5. Struct para definir conteúdo
typedef struct Conteudo {
    int id;
    string titulo;
    string tipo;
    string genero;
    int ano;
    int numViews;
} Conteudo;

// 6. Funções que serão executadas no sistema
// // 6.1. CADASTRAR E REMOVER
void cadastrarConteudo(ListaContCad& listaCad, string titulo, string tipo, string genero, int ano);
void removerConteudo(ListaContCad& listaCad, int id);
// // 6.2. LISTAGEM
void listaCadastrados(ListaContCad& listaCad);
void listaRecomendados(ListaContRec& listaRec);
void listaMaisAssistidos(ListaContMaisAssist& listaAssist);
// // 6.3. ASSISTIR
void assistirConteudo(ListaContCad& listaCad, int id);

#endif // CONTEUDO_H_INCLUDED
