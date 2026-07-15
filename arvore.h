// 1. Inicialização da inclusão do header
#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 3. Inclusão de bibliotecas criadas
#include "conteudo.h"
#include "estatisticas.h"

// 4. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
class ListaDupla;
class ListaSimples;

// 5. Classe do nó da árvore
class NodoA {
public:
    std::string texto;
    NodoA* sim;         // Para a esquerda
    NodoA* nao;         // Para a direita
    bool folha;         // Identificar se é o último nível ou não
    TipoConteudo tipoFiltro;
    GeneroConteudo generoFiltro;
    FiltroCronologico cronologiaFiltro;

    // Construtor para inicializar de forma segura os ponteiros sem risco de lixo de memória
    NodoA() : texto(""), sim(nullptr), nao(nullptr), folha(false),
              tipoFiltro(QUALQUER_TIPO), generoFiltro(QUALQUER_GENERO), cronologiaFiltro(QUALQUER_ANO) {}
};

// 6. Classe da árvore
class Arvore {
public:
    NodoA* raiz;

    Arvore(); // Construtor da árvore
    ~Arvore(); // Destrutor da árvore

    void apagarArvore(NodoA* atual);
    void inserirPorCaminho(const std::string& caminho, const std::string& texto, bool folha,int pTipo = QUALQUER_TIPO, int pGenero = QUALQUER_GENERO, int pCrono = QUALQUER_ANO);
    void gerarArvoreDecisao();
    void navegarArvore(ListaSimples& listaRec, ListaDupla& listaCad, ListaDupla& listaAssist, Estatisticas& est);
};

#endif // ARVORE_H_INCLUDED
