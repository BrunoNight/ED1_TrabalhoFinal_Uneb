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
    NodoA() : texto(""), sim(nullptr), nao(nullptr), folha(false) {} // Construtor para inicializar de forma segura os ponteiros sem risco de lixo de memória
};

// 5. Classe da árvore
class Arvore { public:
    NodoA* raiz;
    Arvore(); // Construtor da árvore
    ~Arvore(); // Destrutor da árvore
    void apagarArvore(NodoA *atual);
    void inserirPorCaminho(const std::string& caminho, const std::string& filtro, bool folha);
    void gerarArvoreDecisao();
    void inserirFiltrar(NodoA* atual, ListaContCad& listaCad, ListaContRec& listaRec);
};

#endif // ARVORE_H_INCLUDED
