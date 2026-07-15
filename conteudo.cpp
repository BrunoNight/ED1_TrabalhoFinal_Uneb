// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <iomanip>

// 2. Inclusão de bibliotecas criadas
#include "listas.h"
#include "estetica.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Declaração para inicialização do ID de conteúdos
static int proximoId = 1;

// 5. Função para cadastrar conteúdo
void cadastrarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, string titulo, string tipo, string genero, int ano) {
    NodoDuplo* existente = listaCad.buscar(titulo);
    if (existente) {
        centralizarTexto("  [!] Título já cadastrado: \"" + titulo + "\"\n");
        return;
    }

    Conteudo c;
    c.id = gerarNovoId(); // id único e sequencial // CONSERTADO
    c.titulo = titulo;
    c.tipo = tipo;
    c.genero = genero;
    c.ano = ano;
    c.numViews = 0;
    c.avaliacao = 0.0f;

    listaCad.inserirOrdenado(c);
    listaAssist.inserirOrdenado(c);

    centralizarTexto("  [+] Cadastrado: \"" + titulo + "\"  (ID: " + to_string(c.id) + ")\n");
}

// 6. Função para gerar novo ID
int gerarNovoId() {
    return proximoId++;
}

void atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}

// 7. Função para remover conteúdo
void removerConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, string titulo) {
    bool okCad = listaCad.remover(titulo);
    bool okAssist = listaAssist.remover(titulo);
    bool okRec = listaRec.remover(titulo);

    if (!okCad && !okAssist && !okRec) {
        centralizarTexto("  [!] \"" + titulo + "\" não encontrado em nenhuma lista.\n");
    } else {
        centralizarTexto("  [-] Removido: \"" + titulo + "\"");
        if(!okRec) centralizarTexto("  (Não estava nos recomendados)");
        centralizarTexto("\n");
    }
}

// 8. Função para listar conteúdos cadastrados
void listaCadastrados(ListaDupla& listaCad) {
    centralizarTexto("\n=== CATALOGO COMPLETO ===\n");
    if (listaCad.estaVazia()) {
        centralizarTexto("  [Catálogo vazio]\n");
        return;
    }
    listaCad.exibirFrente();
}

// 9. Função para listar conteúdos recomendados
void listaRecomendados(ListaSimples& listaRec) {
    centralizarTexto("\n=== TITULOS RECOMENDADOS ===\n");
    if (listaRec.estaVazia()) {
        centralizarTexto("  [Sem recomendações para este perfil]\n");
        return;
    }
    listaRec.exibir();
}

// 10. Função para listar conteúdos mais assistidos
void listaMaisAssistidos(ListaDupla& listaAssist) {
    centralizarTexto("\n=== RANKING: MAIS ASSISTIDOS ===\n");
    if (listaAssist.estaVazia()) {
        centralizarTexto("  [Nenhuma visualização registrada]\n");
        return;
    }
    listaAssist.exibirFrente();
}

// 11. Função para assistir conteúdos
void assistirConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, string titulo) {
    bool okCad    = listaCad.incrementarVisualizacoes(titulo);
    bool okAssist = listaAssist.incrementarVisualizacoes(titulo);

    if (!okCad || !okAssist) {
        centralizarTexto("  [ERRO] \"" + titulo + "\" não encontrado.\n");
        return;
    }

    NodoDuplo* no = listaCad.buscar(titulo);
    if (no) {
        centralizarTexto("  >> Assistindo: \"" + titulo + "\"  |  Views totais: " + to_string(no->conteudo.numViews) + "\n"); // AJUSTADO PARA CENTRALIZAÇÃO DE TEXTO
    }
}

void avaliarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, string titulo, float nota) {
    // Buscamos o título em ambas as listas para manter as informações sincronizadas
    NodoDuplo* noCad = listaCad.buscar(titulo);
    NodoDuplo* noAssist = listaAssist.buscar(titulo);

    if (noCad != nullptr) {
        // Calcula a nova média: ((Média Antiga * Avaliações Antigas) + Nova Nota) / Novas Avaliações Totais
        float somaNotas = (noCad->conteudo.avaliacao * (noCad->conteudo.numViews- 1)) + nota;
        noCad->conteudo.avaliacao = somaNotas / noCad->conteudo.numViews;

        // Como a lista de Assistidos possui cópias dos nós, precisamos espelhar o valor nela
        if (noAssist != nullptr) {
            noAssist->conteudo.avaliacao = noCad->conteudo.avaliacao;
        }

        cout << "\n";
        centralizarTexto("  [Sucesso] Avaliação registrada! A média atual é " + to_string(noCad->conteudo.avaliacao).substr(0,3) + " estrelas.\n");
    }
}
