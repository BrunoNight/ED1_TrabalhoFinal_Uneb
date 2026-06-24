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
 
// ── Nó para Lista Duplamente Encadeada ──────────────────────
struct NodoDuplo {
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
	    // ── Construtores / Destrutores ───────────────────────────
	    ListaSimples();
	    ~ListaSimples();
	 
	    // ── Inserção ─────────────────────────────────────────────
	    // Insere mantendo ordem decrescente por avaliação
	    void inserirOrdenado(Conteudo& c);
	 
	    // ── Remoção ──────────────────────────────────────────────
	    // Remove o primeiro nó com conteudo.nome == nome
	    // Retorna true se encontrado e removido, false caso contrário
	    bool remover(string& nome);
	 
	    // ── Busca ────────────────────────────────────────────────
	    // Retorna ponteiro para o nó ou nullptr se não encontrado
	    NodoSimples* buscar(string& nome);
	 
	    // ── Exibição ─────────────────────────────────────────────
	    void exibir();
	 
	    // ── Utilitários ──────────────────────────────────────────
	    int  getTamanho();
	    bool estaVazia();
	    void limpar();
 
	private:
	    NodoSimples* cabeca;
	    int tamanho;
};

class ListaDupla {
	public:
	    // ── Construtores / Destrutores ───────────────────────────
	    ListaDupla();
	    ~ListaDupla();
	 
	    // ── Inserção ─────────────────────────────────────────────
	    // Insere mantendo ordem decrescente por visualizações
	    void inserirOrdenado(Conteudo& c);
	 
	    // ── Remoção ──────────────────────────────────────────────
	    bool remover(string& nome);
	 
	    // ── Busca ────────────────────────────────────────────────
	    NodoDuplo* buscar(string& nome);
	 
	    // ── Exibição bidirecional ─────────────────────────────────
	    void exibirFrente();   // cabeça → cauda (ranking normal)
	    void exibirReverso();   // cauda → cabeça (via ponteiro anterior)
	 
	    // ── Funcionalidade "Assistir" ─────────────────────────────
	    // Incrementa visualizações em +1 e reposiciona o nó
	    // Retorna false se o título não existir
	    bool incrementarVisualizacoes(string& nome);
	 
	    // ── Utilitários ──────────────────────────────────────────
	    int  getTamanho();
	    bool estaVazia();
	    void limpar();
 
	private:
	    NodoDuplo* cabeca;
	    NodoDuplo* cauda;
	    int      tamanho;
	 
	    // ── Auxiliares internos ───────────────────────────────────
	    // Desvincula o nó da lista sem deletar (mantém o ponteiro)
	    void desvincular(NodoDuplo* no);
	 
	    // Insere um nó já existente na posição correta da lista
	    void inserirNo(NodoDuplo* no);
	 
	    // Verifica se o nó está fora de ordem e o reposiciona
	    void reposicionar(NodoDuplo* no);
};

#endif // LISTAS_H_INCLUDED
