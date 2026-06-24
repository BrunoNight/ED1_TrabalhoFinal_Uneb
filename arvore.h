// 1. Inicializa��o da inclus�o do header
#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

// 2. Inclus�o de bibliotecas existentes
#include <string>

// 3. Declara��o de classes e structs das bibliotecas criadas para evitar inclus�o c�clica
class ListaContCad;
class ListaContRec;

// 4. Classe do n� da �rvore
class NodoA { public:
    std::string texto;
    NodoA* sim; // Para a esquerda
    NodoA* nao; // Para a direita
    bool folha; // Identificar se � o �ltima n�vel ou n�o
};

// 5. Classe da �rvore
class Arvore { public:
    NodoA* raiz;
    Arvore() {
        raiz = nullptr;
    }
    ~Arvore() {
        apagarArvore(raiz);
    }
    NodoA* inserirNo(std::string texto, bool folha);
    void gerarArvoreDecisao();
    void inserirFiltrar(NodoA* atual, ListaContCad& listaCad, ListaContRec& listaRec);
    void apagarArvore(NodoA *atual);
};

#endif // ARVORE_H_INCLUDED
