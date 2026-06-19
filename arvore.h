// 1. Inicialização da inclusão do header
#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 3. Libera o uso direto dos tipos da biblioteca padrão (como string)
using namespace std;

// 4. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
typedef struct Conteudo Conteudo;
class ListaContCad;
class ListaContRec;

// 5. Classe do nó da árvore
class NodoA { public:
    string filtro;
    NodoA* sim; // Para a esquerda
    NodoA* nao; // Para a direita
    bool folha; // Identificar se é o última nível ou não
};

// 6. Classe da árvore
class Arvore { public:
    NodoA* raiz;
    Arvore() {
        raiz = nullptr;
    }
    NodoA* inserirNo(string texto, bool folha);
    void gerarArvoreDecisao();
    void inserirFiltrar(NodoA* atual, ListaContCad& listaCad, ListaContRec& listaRec);
    void apagarArvore(NodoA *atual);
};

#endif // ARVORE_H_INCLUDED
