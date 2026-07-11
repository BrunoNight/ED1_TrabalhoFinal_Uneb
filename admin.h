// 1. Inicializa��o da inclus�o do header
#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

// 2. Inclus�o de bibliotecas existentes
#include <string>

// 3. Inclus�o de bibliotecas criadas
#include "listas.h"
#include "conteudo.h"
#include "usuario.h"

// 4. Declara��o de classes e structs das bibliotecas criadas para evitar inclus�o c�clica // ACRESCENTADO
class ListaDupla;
class ListaSimples;
class Conteudo;

// 5. Classe do admin
class Admin {
    private:
        static std::string nome;
        static std::string senha;

    public:
        Admin(std::string nome, std::string senha);
        bool login(std::string tentativaSenha);
        std::string getNome();

        static void cadastrarTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, Conteudo& titulo);

        static Conteudo buscarTitulo(ListaDupla& lista, std::string nomeTitulo);

        static void listarTitulos(ListaDupla& lista);

        static void atualizarTitulo(ListaDupla& lista, std::string nomeTitulo, std::string novoTitulo);
        static void atualizarTituloTipo(ListaDupla& lista, std::string nomeTitulo, std::string tipo);
        static void atualizarTituloGenero(ListaDupla& lista, std::string nomeTitulo, std::string genero);
        static void atualizarTituloAno(ListaDupla& lista, std::string nomeTitulo, int ano);
        static void atualizarAvaliacao(ListaDupla& lista, std::string nomeTitulo, float novaAvaliacao);

        static void removerTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, std::string nomeTitulo);

        static void assistir(ListaDupla& listaCad, ListaDupla& listaAssist, std::string nomeTitulo);
};

#endif // ADMIN_H_INCLUDED
