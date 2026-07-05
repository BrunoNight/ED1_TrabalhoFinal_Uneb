// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 2. Inclusão de bibliotecas criadas
#include "pilha.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função de Construtor da pilha
Pilha::Pilha() {
    topo = nullptr;
}

// 6. Função de Desconstrutor da pilha
Pilha::~Pilha() {
    apagarPilha();
}

// 7. Função de empilhamento
void Pilha::empilhar(NodoA* no) {
    NodoP* novoP = new NodoP;
    novoP -> noArvore = no;
    novoP -> prox = topo;
    topo = novoP;
    return;
}

// 8. Função de desempilhamento
NodoA* Pilha::desempilhar() {
    if(estaVazio()) {
        return nullptr; // Retorna nulo se não houver elementos para remover
    }

    NodoP* temp = topo; // Guarda o nó atual do topo
    NodoA* noRetorno = temp -> noArvore; // Salva o ponteiro do nó da árvore

    topo = topo -> prox; // Move o topo para o próximo elemento
    delete temp; // Libera a memória do nó da pilha

    return noRetorno; // Retorna o ponteiro do nó da árvore recuperado
}

// 9. Função para verificar se a pilha está vazia
bool Pilha::estaVazio() {
    return (topo == nullptr);
}

// 10. Função para apagar toda a pilha (liberar memória)
void Pilha::apagarPilha() {
    while (!estaVazio()) {
        desempilhar(); // Reutiliza a lógica do desempilhar para limpar cada nó
    }
}
