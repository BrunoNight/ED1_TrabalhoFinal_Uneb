#include "listas.h"
#include "admin.h"
#include <iostream>
#include <iomanip>

using namespace std;

Admin::Admin(string n, string s) {
	nome = n;
	senha = s;
}

bool Admin::login(string tentativa) {
    if (tentativa == senha) {
        cout << "  [ACESSO LIBERADO] Bem-vindo, " << nome << "!\n";
        return true;
    }
    cout << "  [ACESSO NEGADO] Senha incorreta.\n";
    return false;
}

string Admin::getNome() { return nome; }

void Admin::cadastrarTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, Conteudo& titulo) {
    NodoDuplo* existente = listaCad.buscar(titulo.titulo);
    if (existente) {
        cout << "  [!] Titulo ja cadastrado: \"" << titulo.titulo << "\"\n";
        return;
    }

    // PONTO UNICO de geracao de ID: gerarNovoId() em conteudo.cpp
    if (titulo.id <= 0) titulo.id = gerarNovoId();

    listaCad.inserirOrdenado(titulo);     // insere no catalogo
    listaAssist.inserirOrdenado(titulo);  // insere no ranking 

    cout << "  [+] Cadastrado: \"" << titulo.titulo
         << "\"  (ID: " << titulo.id << ")\n";
}

Conteudo Admin::buscarTitulo(ListaDupla& lista, string nomeTitulo) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (no) {
        const Conteudo& c = no->conteudo;
        cout << "  [Encontrado]\n"
             << "  ID       : " << c.id       << "\n"
             << "  Titulo   : " << c.titulo   << "\n"
             << "  Tipo     : " << c.tipo     << "\n"
             << "  Genero   : " << c.genero   << "\n"
             << "  Ano      : " << c.ano      << "\n"
             << "  Views    : " << c.numViews << "\n"
             << "  Avaliacao: " << fixed << setprecision(1)
             << c.avaliacao << "\n";
        return c;
    }
    cout << "  [!] \"" << nomeTitulo << "\" nao encontrado.\n";
    Conteudo vazio;
    vazio.id = -1; 
    return vazio;
}


void Admin::listarTitulos(ListaDupla& lista) {
    cout << "=== CATALOGO (Admin: " << nome << ") ===\n";
    listaCadastrados(lista);  // delega — sem logica duplicada
}

void Admin::atualizarTitulo(ListaDupla& lista, string nomeTitulo,
                             string novoTitulo) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { 
    	cout << "  [!] Nao encontrado: \"" << nomeTitulo << "\"\n"; return; 
    }
    cout << "  [~] Titulo: \"" << no->conteudo.titulo << "\" -> \"" << novoTitulo << "\"\n";
    no->conteudo.titulo = novoTitulo;
}

void Admin::atualizarTituloTipo(ListaDupla& lista, string nomeTitulo, string tipo) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { cout << "  [!] Nao encontrado: \"" << nomeTitulo << "\"\n"; return; }
    cout << "  [~] Tipo de \"" << nomeTitulo << "\": \"" << no->conteudo.tipo << "\" -> \"" << tipo << "\"\n";
    no->conteudo.tipo = tipo;
}

void Admin::atualizarTituloGenero(ListaDupla& lista, string nomeTitulo, string genero) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { cout << "  [!] Nao encontrado: \"" << nomeTitulo << "\"\n"; return; }
    cout << "  [~] Genero de \"" << nomeTitulo << "\": \""  << no->conteudo.genero << "\" -> \"" << genero << "\"\n";
    no->conteudo.genero = genero;
}

void Admin::atualizarTituloAno(ListaDupla& lista, string nomeTitulo, int ano) {
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { cout << "  [!] Nao encontrado: \"" << nomeTitulo << "\"\n"; return; }
    cout << "  [~] Ano de \"" << nomeTitulo << "\": "
         << no->conteudo.ano << " -> " << ano << "\n";
    no->conteudo.ano = ano;
}

void Admin::atualizarAvaliacao(ListaDupla& lista, string nomeTitulo, float novaAvaliacao) {
    if (novaAvaliacao < 0.0f || novaAvaliacao > 10.0f) {
        cout << "  [!] Avaliacao invalida (" << novaAvaliacao
             << "). Use 0.0 a 10.0.\n";
        return;
    }
    NodoDuplo* no = lista.buscar(nomeTitulo);
    if (!no) { cout << "  [!] Nao encontrado: \"" << nomeTitulo << "\"\n"; return; }
    cout << "  [~] Avaliacao de \"" << nomeTitulo << "\": "
         << fixed << setprecision(1) << no->conteudo.avaliacao
         << " -> " << novaAvaliacao << "\n";
    no->conteudo.avaliacao = novaAvaliacao;
}

void Admin::removerTitulo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, string nomeTitulo) {
    removerConteudo(listaCad, listaAssist, listaRec, nomeTitulo); 
}

void Admin::assistir(ListaDupla& listaCad, ListaDupla& listaAssist, string nomeTitulo) {
    assistirConteudo(listaCad, listaAssist, nomeTitulo);
}
