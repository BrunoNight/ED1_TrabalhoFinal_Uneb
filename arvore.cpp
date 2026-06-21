// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>

// 2. Inclusão de bibliotecas criadas
#include "arvore.h"

// 3. Função de inserir nó na árvore de recomendação
NodoA* Arvore::inserirNo(std::string texto, bool folha) {
    NodoA* novo = new Nodo;
    novo -> texto = texto;
    novo -> folha = folha;
    novo -> sim = nullptr;
    novo -> nao = nullptr;
    return novo;
}

