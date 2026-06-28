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

}
