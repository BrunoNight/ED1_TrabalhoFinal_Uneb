// 1. Inicialização da inclusão do header
#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>

// 3. Inclusão de bibliotecas criadas
#include "conteudo.h"

// 4. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
class ListaDupla;
class ListaSimples;

// 5. Classe do nó da árvore
class NodoA { 
    public:
        std::string texto;
        NodoA* sim; // Para a esquerda
        NodoA* nao; // Para a direita
        bool folha; // Identificar se é o última nível ou não
        TipoConteudo tipoFiltro;
        GeneroConteudo generoFiltro;
        FiltroCronologico cronologiaFiltro;
        // Construtor para inicializar de forma segura os ponteiros sem risco de lixo de memória
        NodoA() : texto(""), sim(nullptr), nao(nullptr), folha(false), tipoFiltro(QUALQUER_TIPO), generoFiltro(QUALQUER_GENERO), cronologiaFiltro(QUALQUER_ANO) {}
};

// 6. Classe da árvore
class Arvore { 
    public:
        NodoA* raiz;
        Arvore(); // Construtor da árvore
        ~Arvore(); // Destrutor da árvore
        void apagarArvore(NodoA* atual);
        void inserirPorCaminho(const std::string& caminho, const std::string& filtro, bool folha, int pTipo = 0, int pGenero = 0, int pCrono = 0);
        void gerarArvoreDecisao();
        void inserirFiltrar(NodoA* atual, ListaDupla& listaCad, ListaSimples& listaRec);
};

#endif // ARVORE_H_INCLUDED
