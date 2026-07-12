// 1. Inclusão de bibliotecas existentes
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

// 2. Inclusão de bibliotecas criadas
#include "listas.h"
#include "arvore.h"
#include "estatisticas.h"
#include "menu.h"
#include "persistencia.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Execução do main
int main() {
#ifdef _WIN32
    // Define texto do terminal para UTF-8 caso o SO seja Windows
    SetConsoleOutputCP(CP_UTF8);
#endif
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
    // Carrega o catálogo, o ranking e as estatísticas
    carregarTudo(listaCad, listaAssist, est);
    // Cadastrar um Administrador padrão
    cadastrarUsuario(listaUsuarios, "admin", "uneb123", ADMINISTRADOR);
    // Cadastrar um Utilizador Comum padrão
    cadastrarUsuario(listaUsuarios, "bruno", "1234", COMUM);

    // 4.3. Disparar o Loop Principal do Sistema
    // Passar todas as estruturas essenciais
    executarSistema(listaUsuarios, listaCad, listaAssist, listaRec, arvoreDecisao, est);
    // Salva o estado atual do catálogo, ranking e estatísticas ao encerrar o sistema
    salvarTudo(listaCad, listaAssist, est);

    return 0;
}
