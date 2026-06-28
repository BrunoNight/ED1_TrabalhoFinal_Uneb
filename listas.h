#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include "conteudo.h"
#include <string>
#include <iostream>

using namespace::std;

class NodoSimples {
    public:
    	Conteudo   conteudo;
        NodoSimples* proximo;
        
    	NodoSimples(Conteudo c){
    		conteudo = c;
    		proximo = nullptr;
    	}
};

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

class ListaSimples {
	public:
	    ListaSimples();

	    void inserirOrdenado(Conteudo& c);
	 
	    bool remover(const string& nome);

	    NodoSimples* buscar(const string& nome);
	    void exibir();
	 
	    int  getTamanho();
	    bool estaVazia();
	    void limpar();
 
	private:
	    NodoSimples* cabeca;
	    int tamanho;
};

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
	    int      tamanho;
	 
	    void desvincular(NodoDuplo* no);

	    void inserirNo(NodoDuplo* no);

	    void reposicionar(NodoDuplo* no);
};

#endif // LISTAS_H_INCLUDED
