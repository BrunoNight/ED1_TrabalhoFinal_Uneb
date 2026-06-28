// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>
#include <cstdio>  // Equivalente ao <stdio.h> em C++
#include <cstring> // Necessário para usar funções de string, como o strtok para reconhecimento do arquivo de texto da árvore

// 2. Inclusão de bibliotecas criadas
#include "arvore.h"
#include "menu.h"
#include "estetica.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função de construção da Árvore
Arvore::Arvore() {
    raiz = nullptr;
}

// 6. Função de desconstrução da Árvore
Arvore::~Arvore() {
    apagarArvore(raiz);
}

// 7. Função de apagar a árvore para limpar memória após fechar sistema ou sair da árvore de recomendação
void Arvore::apagarArvore(NodoA *atual) {
    if(atual != nullptr) {
        apagarArvore(atual -> sim);
        apagarArvore(atual -> nao);
        delete atual;
    }
}

// 8. Função para inserir novos nós conforme árvore de recomendação é usada
void Arvore::inserirPorCaminho(const string& caminho, const string& filtro, bool folha) {
    if(caminho.empty()) { // Garantir que, durante o percurso da árvore, o sistema não processe áreas vazias
        return;
    }

    if(raiz == nullptr) { // Se a árvore estiver vazia, cria a raiz primeiro
        raiz = new NodoA();
        raiz -> texto = filtro;
        raiz -> folha = folha;
        raiz->sim = nullptr;
        raiz->nao = nullptr;
    }

    NodoA* atual = raiz; // Ponteiro auxiliar para navegar na árvore sem perder a referência da raiz durante a inserção

    for(size_t i = 0; i < caminho.length(); i++) { // Percorre o caminho (exemplo: 1-2-1-1-2) para construir ou localizar os nós na árvore de decisão
        if (caminho[i] == '-') {
            continue; // Pula os separadores
        }

        if(caminho[i] == '1') {
            if(atual -> sim == nullptr) { // Se o nó filho à esquerda não existe, aloca-o dinamicamente
                atual -> sim = new NodoA();
            }
            atual = atual -> sim; // Vai para o nó filho
        } else if (caminho[i] == '2') {
            if (atual -> nao == nullptr) { // Se o nó filho à direita não existe, aloca-o dinamicamente
                atual -> nao = new NodoA();
            }
            atual = atual -> nao; // Vai para o nó filho
        }
    }

    // Após percorrer o caminho, preenche os dados do nó de destino
    atual -> texto = filtro;
    atual -> folha = folha;

    // Garante que novos nós de folha não tenham filhos
    if(folha) {
        atual -> sim = nullptr;
        atual -> nao = nullptr;
    }
}

// 9. Função para ir lendo os dados da árvore de recomendação, separar suas partes (na linha) e prepará-las para serem inseridas
void Arvore::gerarArvoreDecisao() { // Abrir e reconhecer dados do arquivo txt para inserir nós da árvore de recomendação
    FILE* arquivo = fopen("arvore_dados.txt", "r");

    if(arquivo == nullptr) { // Se não conseguiu abrir arquivo
        centralizarTexto("\n[Aviso] Arquivo arvore_dados.txt não pôde ser aberto! [Aviso]");
        return;
    }

    char linha[300]; // Buffer para ler cada linha do arquivo

    // Lendo linha a linha do arquivo
    while(fgets(linha, sizeof(linha), arquivo) != nullptr) {
        linha[strcspn(linha, "\n")] = 0; // Elimina o espaço de pular linhar após o texto da linha

        // Pula linhas vazias
        if(strlen(linha) == 0) {
            continue;
        }

        // Para extração de campos por um delimitador ";"
        char* parteCaminho = strtok(linha, ";"); // Ex.: 1-2-1
        char* partePergunta = strtok(nullptr, ";"); // Ex.: Você prefere produções em formato longo de historia única?
        char* parteFolha = strtok(nullptr, ";"); // Ex.: 0

        if (parteCaminho != nullptr && partePergunta != nullptr && parteFolha != nullptr) {
            bool folha = (parteFolha[0] == '1');
            // Chama a função inserirPorCaminho para inserir baseada no caminho das coordenadas
            // Ex: "1-1-2" -> insere
            inserirPorCaminho(parteCaminho, partePergunta, folha);
        }
    }

    fclose(arquivo);
}

void Arvore::inserirFiltrar(NodoA* atual, ListaContCad& listaCad, ListaContRec& listaRec) {
    if(atual == nullptr) {
        centralizarTexto("\n[Aviso] Nó inválido alcançado ou árvore de decisão não gerada [Aviso]");
        return;
    }

    if(!atual -> folha) {
        int opcao = 0;
        while(true) {
            centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
            centralizarTexto(Estetica::GREEN + atual -> texto); // Exibe a pergunta armazenada no nó
            centralizarTexto(Estetica::YELLOW + " (> " + bordaB + Estetica::YELLOW + " <) ");
            centralizarTexto(Estetica::RED + "1 - Sim");
            centralizarTexto(Estetica::RED + "2 - Não");
            ccentralizarTexto(Estetica::RED + "Escolha uma opção (1 ou 2): ");
            cin >> opcao;
            limparBufferEntrada();

            if(opcao < 1 || opcao > 2) {
                cin.clear();
                cin.ignore(10000, '\n');
                centralizarTexto("\n[Aviso] Opção inválida! Digite apenas 1 (Sim) ou 2 (Não) [Aviso]");
            } else {
                break;
            }
        }

        if(opcao == 1) {
            inserirFiltrar(atual -> sim, listaCad, listaRec);
        } else {
            inserirFiltrar(atual -> nao, listaCad, listaRec);
        }
    } else {
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
        centralizarTexto(Estetica::RED + "  RECOMENDAÇÃO BASEADA NO SEU PERFIL: " << atual -> texto << endl;
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");








    }
}

