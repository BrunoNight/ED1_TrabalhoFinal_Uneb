// 1. Inicialização da inclusão do header
#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>

// 3. Inclusão de bibliotecas criadas
#include "listas.h"
#include "conteudo.h"

// 4. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica // ACRESCENTADO
class ListaDupla;
class ListaSimples;
class Conteudo;

// 5. Classe do admin
class Admin {
    private:
        std::string nome;
        std::string senha;

    public:
        Admin(std::string nome, std::string senha);
        bool login(std::string tentativaSenha);
        std::string getNome();

        void cadastrarTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, Conteudo& titulo);

        Conteudo buscarTitulo(ListaDupla& lista, std::string nomeTitulo);

        void listarTitulos(ListaDupla& lista);

        void atualizarTitulo(ListaDupla& lista, std::string nomeTitulo, std::string novoTitulo);
        void atualizarTituloTipo(ListaDupla& lista, std::string nomeTitulo, std::string tipo);
        void atualizarTituloGenero(ListaDupla& lista, std::string nomeTitulo, std::string genero);
        void atualizarTituloAno(ListaDupla& lista, std::string nomeTitulo, int ano);
        void atualizarAvaliacao(ListaDupla& lista, std::string nomeTitulo, float novaAvaliacao);

        void removerTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, std::string nomeTitulo);

        void assistir(ListaDupla& listaCad, ListaDupla& listaAssist, std::string nomeTitulo);
};

#endif // ADMIN_H_INCLUDED
