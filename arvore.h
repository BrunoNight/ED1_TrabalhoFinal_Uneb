// 1. Inicialização da inclusão do header
#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>

// 3. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
class ListaContCad;
class ListaContRec;

// 4. Classe do nó da árvore
class NodoA { public:
    std::string texto;
    NodoA* sim; // Para a esquerda
    NodoA* nao; // Para a direita
    bool folha; // Identificar se é o última nível ou não
};

// 5. Classe da árvore
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
