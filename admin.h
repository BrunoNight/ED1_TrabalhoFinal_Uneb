#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include <string>
#include "conteudo.h"

using namespace std;

class Admin {
    private:
        string nome;
        string senha;

    public:
        Admin(string nome, string senha);
        bool   login(string tentativaSenha);
        string getNome();
        
        void cadastrarTitulo(ListaDupla& listaCad, ListaDupla& listaAssist,
                             Conteudo& titulo);

        Conteudo buscarTitulo(ListaDupla& lista, string nomeTitulo);

        void listarTitulos(ListaDupla& lista);

        void atualizarTitulo(ListaDupla& lista, string nomeTitulo, string novoTitulo);
        void atualizarTituloTipo(ListaDupla& lista, string nomeTitulo, string tipo);
        void atualizarTituloGenero(ListaDupla& lista, string nomeTitulo, string genero);
        void atualizarTituloAno(ListaDupla& lista, string nomeTitulo, int ano);
        void atualizarAvaliacao(ListaDupla& lista, string nomeTitulo, float novaAvaliacao);

        void removerTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, string nomeTitulo);

        void assistir(ListaDupla& listaCad, ListaDupla& listaAssist, string nomeTitulo);
};

#endif // ADMIN_H_INCLUDED
