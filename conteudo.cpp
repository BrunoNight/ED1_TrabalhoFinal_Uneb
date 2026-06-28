#include "listas.h"
#include <iostream>
#include <iomanip>

using namespace std;

static int proximoId = 1;

void cadastrarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist,
                        string titulo, string tipo, string genero, int ano) {
    Conteudo c;
    c.id         = proximoId++;   // id único e sequencial
    c.titulo     = titulo;
    c.tipo       = tipo;
    c.genero     = genero;
    c.ano        = ano;
    c.numViews   = 0;
    c.avaliacao  = 0.0f;          // padrão; atualizado pela árvore/admin

    listaCad.inserirOrdenado(c);
    listaAssist.inserirOrdenado(c);

    cout << "  [+] Cadastrado: \"" << titulo << "\"  (ID: " << c.id << ")\n";
}

void removerConteudo(ListaDupla& listaCad, ListaDupla& listaAssist,
                      ListaSimples& listaRec, string titulo) {
    bool okCad    = listaCad.remover(titulo);
    bool okAssist = listaAssist.remover(titulo);
    bool okRec    = listaRec.remover(titulo);

    if (!okCad && !okAssist && !okRec) {
        cout << "  [!] \"" << titulo << "\" nao encontrado em nenhuma lista.\n";
    } else {
        cout << "  [-] Removido: \"" << titulo << "\"";
        if (!okRec) cout << "  (nao estava nos recomendados)";
        cout << "\n";
    }
}

void listaCadastrados(ListaDupla& listaCad) {
    cout << "\n=== CATALOGO COMPLETO ===\n";
    if (listaCad.estaVazia()) {
        cout << "  [Catalogo vazio]\n";
        return;
    }
    listaCad.exibirFrente();
}

void listaRecomendados(ListaSimples& listaRec) {
    cout << "\n=== TITULOS RECOMENDADOS ===\n";
    if (listaRec.estaVazia()) {
        cout << "  [Sem recomendacoes para este perfil]\n";
        return;
    }
    listaRec.exibir();
}


void listaMaisAssistidos(ListaDupla& listaAssist) {
    cout << "\n=== RANKING: MAIS ASSISTIDOS ===\n";
    if (listaAssist.estaVazia()) {
        cout << "  [Nenhuma visualizacao registrada]\n";
        return;
    }
    listaAssist.exibirFrente();
}


void assistirConteudo(ListaDupla& listaCad, ListaDupla& listaAssist,
                       string titulo) {
    bool okCad    = listaCad.incrementarVisualizacoes(titulo);
    bool okAssist = listaAssist.incrementarVisualizacoes(titulo);

    if (!okCad || !okAssist) {
        cout << "  [ERRO] \"" << titulo << "\" nao encontrado.\n";
        return;
    }

    NodoDuplo* no = listaCad.buscar(titulo);
    if (no) {
        cout << "  >> Assistindo: \""
             << titulo << "\"  |  Views totais: "
             << no->conteudo.numViews << "\n";
    }
}

int gerarNovoId() {
    return proximoId++;
}
