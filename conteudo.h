// 1. Inicializa��o da inclus�o do header
#ifndef CONTEUDO_H_INCLUDED
#define CONTEUDO_H_INCLUDED

// 2. Inclus�o de bibliotecas existentes
#include <string>

// 3. Declara��o de classes das bibliotecas criadas para evitar inclus�o c�clica
class ListaSimples;
class ListaDupla;

// 4. Struct para definir conte�do
typedef struct Conteudo {
    int id;
    std::string titulo;
    std::string tipo;
    std::string genero;
    int ano;
    int numViews;
    float avaliacao;
} Conteudo;

// 5. Fun��es que ser�o executadas no sistema
// // 5.1. CADASTRAR E REMOVER
void cadastrarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo, std::string tipo, std::string genero, int ano);

// Ajustado para receber 'titulo' em vez de 'id', pois listas.h busca pela string do nome
void removerConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, std::string titulo);

// 5.2. LISTAGEM
void listaCadastrados(ListaDupla& listaCad);
void listaRecomendados(ListaSimples& listaRec);
void listaMaisAssistidos(ListaDupla& listaAssist);

// 5.3. ASSISTIR
// Ajustado para receber 'titulo' para linkar diretamente com incrementarVisualizacoes(string& nome)
void assistirConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo);

#endif // CONTEUDO_H_INCLUDED
