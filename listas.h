// 1. Inicialização da inclusão do header
#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>
#include <iostream>

// 3. Inclusão de bibliotecas criadas
#include "conteudo.h"
#include "usuario.h"

// 4. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace::std;

// 5. Classe do nó da lista simples
class NodoSimples {
    public:
    	Conteudo conteudo;
        NodoSimples* proximo;

    	NodoSimples(Conteudo c) {
    		conteudo = c;
    		proximo = nullptr;
    	}
};

// 6. Classe do nó da lista dupla
class NodoDuplo {
	public:
	    Conteudo conteudo;
	    NodoDuplo* proximo;
	    NodoDuplo* anterior;

	    NodoDuplo(Conteudo c) {
	    	conteudo = c;
	    	proximo = nullptr;
	    	anterior = nullptr;
	    }
};

// 7. Classe da lista simples
class ListaSimples {
	public:
	    ListaSimples();

	    void inserirOrdenado(Conteudo& c);

	    bool remover(const string& nome);

	    NodoSimples* buscar(const string& nome);
	    void exibir();

	    int getTamanho();
	    bool estaVazia();
	    void limpar();

	private:
	    NodoSimples* cabeca;
	    int tamanho;
};

// 8. Classe da lista dupla
class ListaDupla {
	public:
	    ListaDupla();

	    void inserirOrdenado(Conteudo& c);

	    bool remover(string nome);

	    NodoDuplo* buscar(string nome);

	    void exibirFrente();
	    void exibirReverso();

	    bool incrementarVisualizacoes(string nome);

	    int  getTamanho();
	    bool estaVazia();
	    void limpar();

	private:
	    NodoDuplo* cabeca;
	    NodoDuplo* cauda;
	    int tamanho;

	    void desvincular(NodoDuplo* no);

	    void inserirNo(NodoDuplo* no);

	    void reposicionar(NodoDuplo* no);
};

// 9. Classe da lista de usuários do sistema
class ListaUsuarios { public:
    Usuario* inicio;
    ListaUsuarios() : inicio(nullptr) {}
    ~ListaUsuarios() {
        Usuario* atual = inicio;
        while (atual != nullptr) {
            Usuario* temp = atual;
            atual = atual->prox;
            delete temp;
        }
    }
};

#endif // LISTAS_H_INCLUDED
