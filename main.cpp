// 1. Inclusão de bibliotecas existentes
#include <iostream>

// 2. Inclusão de bibliotecas criadas
#include "listas.h"
#include "arvore.h"
#include "estatisticas.h"
#include "menu.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Execução do main
int main() {
    // 4.1. Instanciação das Estruturas de Dados do Sistema
    ListaUsuarios listaUsuarios;  // Lista Simples de usuários (usuario.h / usuario.cpp)
    ListaDupla listaCad;          // Catálogo Geral de Conteúdos (Mais Assistidos / Ordem de Views)
    ListaDupla listaAssist;       // Cópia para Ordenação Paralela / Ranking
    ListaSimples listaRec;        // Lista Simples Ordenada por Avaliação (Para recomendações da Árvore)
    Arvore arvoreDecisao;         // Árvore Binária de Decisão
    Estatisticas est;             // Bloco de contadores estatísticos

    // 4.2. Pré-carregamento de Dados (Garante Persistência)
    // Inicializa a árvore a partir do arquivo de texto txt
    arvoreDecisao.gerarArvoreDecisao();
    // Cadastrar um Administrador padrão
    cadastrarUsuario(listaUsuarios, "admin", "uneb123", ADMINISTRADOR);
    // Cadastrar um Utilizador Comum padrão
    cadastrarUsuario(listaUsuarios, "bruno", "1234", COMUM);

    // 4.3. Disparar o Loop Principal do Sistema
    // Passar todas as estruturas essenciais
    executarSistema(listaUsuarios, listaCad, listaAssist, listaRec, arvoreDecisao, est);

    return 0;
}
