#ifndef CONTEUDO_H_INCLUDED
#define CONTEUDO_H_INCLUDED

#include <string>

class ListaSimples;
class ListaDupla;

typedef struct Conteudo {
    int id;
    std::string titulo;
    std::string tipo;
    std::string genero;
    int ano;
    int numViews;
    float avaliacao;
} Conteudo;

void cadastrarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo, std::string tipo, std::string genero, int ano);

void removerConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, std::string titulo);

void listaCadastrados(ListaDupla& listaCad);
void listaRecomendados(ListaSimples& listaRec);
void listaMaisAssistidos(ListaDupla& listaAssist);

void assistirConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo);

int gerarNovoId();

#endif // CONTEUDO_H_INCLUDED
