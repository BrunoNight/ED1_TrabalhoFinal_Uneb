// 1. Inicialização da inclusão do header
#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

// 2. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
class NodoA;

// 3. Classe do nó da pilha
class NodoP { public:
    NodoA* noArvore;
    NodoP* prox;
};

// 4. Classe da Pilha
class Pilha {
    private:
        NodoP* topo;
    public:
        Pilha(); // Construtor da pilha
        ~Pilha(); // Desconstrutor da pilha
        void empilhar(NodoA* no); // Armazenar perguntas respondidas durante execução da árvore de recomendação
        NodoA* desempilhar(); // Voltar para perguntas respondidas anteriormente na árvore de recomendação
        bool estaVazio(); // Verificar se há histórico de perguntas respondidas na pilha
        void apagarPilha(); // Apagar pilha para liberar memória
};

#endif // PILHA_H_INCLUDED
