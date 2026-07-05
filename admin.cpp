// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <iomanip>

// 2. Inclusão de bibliotecas criadas
#include "listas.h"
#include "admin.h"
#include "estetica.h"
#include "conteudo.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Função de construção do admin
Admin::Admin(string n, string s) {
	nome = n;
	senha = s;
}

// 5. Função de login do admin
bool Admin::login(string tentativa) {
    if (tentativa == senha) {
        centralizarTexto("  [ACESSO LIBERADO] Bem-vindo, " + nome + "!\n");
        return true;
    }
    centralizarTexto("  [ACESSO NEGADO] Senha incorreta.\n");
    return false;
}

// 6. Função getter do nome do admin cadastrado
string Admin::getNome() { return nome; }

// 7. Função do admin de cadastro de conteúdo
void Admin::cadastrarTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, Conteudo& titulo) {
    NodoDuplo* existente = listaCad.buscar(titulo.titulo);
    if (existente) {
        centralizarTexto("  [!] Título já cadastrado: \"" + titulo.titulo + "\"\n");
        return;
    }

    // PONTO ÚNICO de geração de ID: gerarNovoId() em conteudo.cpp
    if (titulo.id <= 0) titulo.id = gerarNovoId();

    listaCad.inserirOrdenado(titulo);     // insere no catálogo
    listaAssist.inserirOrdenado(titulo);  // insere no ranking

    centralizarTexto("  [+] Cadastrado: \"" + titulo.titulo + "\"  (ID: " + titulo.id + ")\n");
}

// 8. Função do admin de busca de conteúdo
Conteudo Admin::buscarTitulo(ListaDupla& lista, string nomeTitulo) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (no) {
        const Conteudo& c = no->conteudo;
        centralizarTexto("  [Encontrado]\n"
             + "  ID       : " + c.id       + "\n"
             + "  Titulo   : " + c.titulo   + "\n"
             + "  Tipo     : " + c.tipo     + "\n"
             + "  Genero   : " + c.genero   + "\n"
             + "  Ano      : " + c.ano      + "\n"
             + "  Views    : " + c.numViews + "\n"
             + "  Avaliacao: " + fixed << setprecision(1)
             + c.avaliacao + "\n");
        return c;
    }
    centralizarTexto("  [!] \"" + nomeTitulo + "\" nao encontrado.\n");
    Conteudo vazio;
    vazio.id = -1;
    return vazio;
}

// 9. Função do admin de listagem de conteúdos
void Admin::listarTitulos(ListaDupla& lista) {
    centralizarTexto("=== CATALOGO (Admin: " + nome + ") ===\n");
    listaCadastrados(lista);  // delega — sem lógica duplicada
}

// 10. Função do admin de atualização de título de conteúdo // VERIFICAR
void Admin::atualizarTitulo(ListaDupla& lista, string nomeTitulo, string novoTitulo) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) {
    	centralizarTexto("  [!] Nao encontrado: \"" + nomeTitulo + "\"\n"); return;
    }
    centralizarTexto("  [~] Titulo: \"" + no->conteudo.titulo + "\" -> \"" + novoTitulo + "\"\n");
    no->conteudo.titulo = novoTitulo;
}

// 11. Função do admin de atualização de tipo do conteúdo
void Admin::atualizarTituloTipo(ListaDupla& lista, string nomeTitulo, string tipo) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { centralizarTexto("  [!] Nao encontrado: \"" + nomeTitulo + "\"\n"); return; }
    centralizarTexto("  [~] Tipo de \"" + nomeTitulo + "\": \"" + no->conteudo.tipo + "\" -> \"" + tipo + "\"\n");
    no->conteudo.tipo = tipo;
}

// 12. Função do admin de atualização de gênero do conteúdo
void Admin::atualizarTituloGenero(ListaDupla& lista, string nomeTitulo, string genero) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { centralizarTexto("  [!] Nao encontrado: \"" + nomeTitulo + "\"\n"); return; }
    centralizarTexto("  [~] Genero de \"" + nomeTitulo + "\": \""  + no->conteudo.genero + "\" -> \"" + genero + "\"\n");
    no->conteudo.genero = genero;
}

// 13. Função do admin de atualização de ano do conteúdo
void Admin::atualizarTituloAno(ListaDupla& lista, string nomeTitulo, int ano) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { centralizarTexto("  [!] Nao encontrado: \"" + nomeTitulo + "\"\n"); return; }
    centralizarTexto("  [~] Ano de \"" + nomeTitulo + "\": " + no->conteudo.ano + " -> " + ano + "\n");
    no->conteudo.ano = ano;
}

// 14. Função do admin de avaliação do conteúdo
void Admin::atualizarAvaliacao(ListaDupla& lista, string nomeTitulo, float novaAvaliacao) {
    if (novaAvaliacao < 0.0f || novaAvaliacao > 10.0f) {
        centralizarTexto("  [!] Avaliacao invalida (" + novaAvaliacao + "). Use 0.0 a 10.0.\n");
        return;
    }
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { centralizarTexto("  [!] Nao encontrado: \"" + nomeTitulo + "\"\n"); return; }
    centralizarTexto("  [~] Avaliacao de \"" + nomeTitulo + "\": "
         + fixed + setprecision(1) + no->conteudo.avaliacao
         + " -> " + novaAvaliacao + "\n");
    no->conteudo.avaliacao = novaAvaliacao;
}

// 15. Função do admin de remoção do conteúdo
void Admin::removerTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, string nomeTitulo) {
    removerConteudo(listaCad, listaAssist, listaRec, nomeTitulo);
}

// 16. Função do admin de assistir o conteúdo
void Admin::assistir(ListaDupla& listaCad, ListaDupla& listaAssist, string nomeTitulo) {
    assistirConteudo(listaCad, listaAssist, nomeTitulo);
}
