#include "listas.h"        // contem ListaDupla, ListaSimples, Conteudo
#include "estatisticas.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <climits>         // INT_MAX para menor valor inicial
 
using namespace std;
 
// ─────────────────────────────────────────────────────────────
//  Helper interno: separador visual
// ─────────────────────────────────────────────────────────────
static void separador(const string& titulo) {
    cout << "\n  \033[1;33m" << string(50, '-') << "\033[0m\n";
    cout << "  \033[1;33m  " << titulo << "\033[0m\n";
    cout << "  \033[1;33m" << string(50, '-') << "\033[0m\n";
}
 
// ─────────────────────────────────────────────────────────────
//  Helper interno: retorna o nome do tipo com maior contagem
// ─────────────────────────────────────────────────────────────
static string tipoComMaiorContagem(Estatisticas& est) {
    int vals[5] = { est.recFilme, est.recSerie, est.recDocumentario,
                    est.recAnime, est.recCartoon };
    string nomes[5] = { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };
    int idxMax = 0;
    for (int i = 1; i < 5; i++)
        if (vals[i] > vals[idxMax]) idxMax = i;
    return nomes[idxMax];
}
 
static string tipoComMenorContagem(Estatisticas& est) {
    int vals[5] = { est.recFilme, est.recSerie, est.recDocumentario,
                    est.recAnime, est.recCartoon };
    string nomes[5] = { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };
    int idxMin = 0;
    for (int i = 1; i < 5; i++)
        if (vals[i] < vals[idxMin]) idxMin = i;
    return nomes[idxMin];
}
 
static string generoComMaiorContagem(Estatisticas& est) {
    int vals[6] = { est.recAcao, est.recComedia, est.recDrama,
                    est.recTerror, est.recFicCientifica, est.recFantasia };
    string nomes[6] = { "Acao", "Comedia", "Drama",
                        "Terror", "Ficcao Cientifica", "Fantasia" };
    int idxMax = 0;
    for (int i = 1; i < 6; i++)
        if (vals[i] > vals[idxMax]) idxMax = i;
    return nomes[idxMax];
}
 
static string generoComMenorContagem(Estatisticas& est) {
    int vals[6] = { est.recAcao, est.recComedia, est.recDrama,
                    est.recTerror, est.recFicCientifica, est.recFantasia };
    string nomes[6] = { "Acao", "Comedia", "Drama",
                        "Terror", "Ficcao Cientifica", "Fantasia" };
    int idxMin = 0;
    for (int i = 1; i < 6; i++)
        if (vals[i] < vals[idxMin]) idxMin = i;
    return nomes[idxMin];
}
 
// =============================================================
//  REGISTRO EM TEMPO REAL
// =============================================================
 
// ─────────────────────────────────────────────────────────────
//  registrarRecomendacao
//
//  Deve ser chamado sempre que o usuario assiste um titulo
//  (botao "Assistir"). Incrementa:
//    - totRecomendacoes (contagem geral)
//    - totVisualizacoes (espelha numViews da lista)
//    - contador de tipo e genero correspondentes
//
//  Comparacao case-insensitive via find() para tolerar
//  variacoes como "filme" vs "Filme".
// ─────────────────────────────────────────────────────────────
void registrarRecomendacao(Estatisticas& est,
                            const string& tipo,
                            const string& genero) {
    est.totRecomendacoes++;
    est.totVisualizacoes++;
 
    // ── Tipo ──────────────────────────────────────────────────
    if      (tipo.find("Filme")        != string::npos ||
             tipo.find("filme")        != string::npos)  est.recFilme++;
    else if (tipo.find("Serie")        != string::npos ||
             tipo.find("serie")        != string::npos)  est.recSerie++;
    else if (tipo.find("Documentario") != string::npos ||
             tipo.find("documentario") != string::npos)  est.recDocumentario++;
    else if (tipo.find("Anime")        != string::npos ||
             tipo.find("anime")        != string::npos)  est.recAnime++;
    else if (tipo.find("Cartoon")      != string::npos ||
             tipo.find("cartoon")      != string::npos)  est.recCartoon++;
 
    // ── Genero ────────────────────────────────────────────────
    if      (genero.find("Acao")        != string::npos ||
             genero.find("acao")        != string::npos)  est.recAcao++;
    else if (genero.find("Comedia")     != string::npos ||
             genero.find("comedia")     != string::npos)  est.recComedia++;
    else if (genero.find("Drama")       != string::npos ||
             genero.find("drama")       != string::npos)  est.recDrama++;
    else if (genero.find("Terror")      != string::npos ||
             genero.find("terror")      != string::npos)  est.recTerror++;
    else if (genero.find("Ficcao")      != string::npos ||
             genero.find("ficcao")      != string::npos)  est.recFicCientifica++;
    else if (genero.find("Fantasia")    != string::npos ||
             genero.find("fantasia")    != string::npos)  est.recFantasia++;
}
 
// =============================================================
//  TOTAIS GERAIS
// =============================================================
 
int recomendacoesTotais(Estatisticas& est) {
    return est.totRecomendacoes;
}
 
int visualizacoesTotais(Estatisticas& est) {
    return est.totVisualizacoes;
}
 
// =============================================================
//  TIPO MAIS / MENOS RECOMENDADO
// =============================================================
 
// ─────────────────────────────────────────────────────────────
//  tipoMaisRecomendado
//  Exibe uma tabela com todos os tipos e destaca o primeiro.
// ─────────────────────────────────────────────────────────────
void tipoMaisRecomendado(Estatisticas& est) {
    separador("TIPO MAIS RECOMENDADO");
 
    int vals[5]    = { est.recFilme, est.recSerie, est.recDocumentario,
                       est.recAnime, est.recCartoon };
    string nomes[5]= { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };
 
    // Exibe tabela de contagens
    cout << "  " << left << setw(18) << "Tipo"
         << right << setw(12) << "Recomendacoes\n";
    cout << "  " << string(32, '-') << "\n";
    for (int i = 0; i < 5; i++) {
        cout << "  " << left  << setw(18) << nomes[i]
             << right << setw(12) << vals[i] << "\n";
    }
 
    string mais = tipoComMaiorContagem(est);
    cout << "\n  \033[1;32m>>> Mais recomendado: " << mais << "\033[0m\n";
}
 
// ─────────────────────────────────────────────────────────────
//  tipoMenosRecomendado  (FIX: ausente no original)
// ─────────────────────────────────────────────────────────────
void tipoMenosRecomendado(Estatisticas& est) {
    separador("TIPO MENOS RECOMENDADO");
    string menos = tipoComMenorContagem(est);
    cout << "  \033[1;31m>>> Menos recomendado: " << menos << "\033[0m\n";
}
 
// =============================================================
//  GENERO MAIS / MENOS RECOMENDADO
// =============================================================
 
void generoMaisRecomendado(Estatisticas& est) {
    separador("GENERO MAIS RECOMENDADO");
 
    int vals[6]    = { est.recAcao, est.recComedia, est.recDrama,
                       est.recTerror, est.recFicCientifica, est.recFantasia };
    string nomes[6]= { "Acao", "Comedia", "Drama",
                       "Terror", "Ficcao Cientifica", "Fantasia" };
 
    cout << "  " << left << setw(20) << "Genero"
         << right << setw(12) << "Recomendacoes\n";
    cout << "  " << string(34, '-') << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "  " << left  << setw(20) << nomes[i]
             << right << setw(12) << vals[i] << "\n";
    }
 
    string mais = generoComMaiorContagem(est);
    cout << "\n  \033[1;32m>>> Mais recomendado: " << mais << "\033[0m\n";
}
 
void generoMenosRecomendado(Estatisticas& est) {
    separador("GENERO MENOS RECOMENDADO");
    string menos = generoComMenorContagem(est);
    cout << "  \033[1;31m>>> Menos recomendado: " << menos << "\033[0m\n";
}
 
// =============================================================
//  TITULO MAIS ASSISTIDO POR TIPO
// =============================================================
 
// ─────────────────────────────────────────────────────────────
//  tipoMaisAssistido
//
//  Para cada tipo cadastrado, varre a listaCad e encontra
//  o titulo com maior numViews dentro daquele tipo.
//  Complexidade: O(T * N) onde T = num tipos, N = num titulos.
// ─────────────────────────────────────────────────────────────
void tipoMaisAssistido(ListaDupla& listaCad, Estatisticas& est) {
    (void)est; // est nao e usado aqui — a informacao vem da varredura da lista
    separador("TITULO MAIS ASSISTIDO POR TIPO");
 
    string tipos[5] = { "Filme", "Serie", "Documentario", "Anime", "Cartoon" };
 
    cout << "  " << left << setw(16) << "Tipo"
         << setw(32) << "Titulo"
         << right << setw(10) << "Views\n";
    cout << "  " << string(60, '-') << "\n";
 
    for (int t = 0; t < 5; t++) {
        string   melhorTitulo = "(nenhum)";
        int      melhorViews  = -1;
 
        // Percorre a lista procurando o maior numViews do tipo atual
        NodoDuplo* atual = listaCad.getCabeca();
        while (atual != nullptr) {
            if (atual->conteudo.tipo == tipos[t] &&
                atual->conteudo.numViews > melhorViews) {
                melhorViews  = atual->conteudo.numViews;
                melhorTitulo = atual->conteudo.titulo;
            }
            atual = atual->proximo;
        }
 
        cout << "  " << left
             << setw(16) << tipos[t]
             << setw(32) << melhorTitulo
             << right << setw(10)
             << (melhorViews < 0 ? 0 : melhorViews) << "\n";
    }
}
 
// =============================================================
//  TITULO MAIS ASSISTIDO POR GENERO
// =============================================================
 
void generoMaisAssistido(ListaDupla& listaCad, Estatisticas& est) {
    (void)est;
    separador("TITULO MAIS ASSISTIDO POR GENERO");
 
    string generos[6] = { "Acao", "Comedia", "Drama",
                          "Terror", "Ficcao Cientifica", "Fantasia" };
 
    cout << "  " << left << setw(20) << "Genero"
         << setw(32) << "Titulo"
         << right << setw(10) << "Views\n";
    cout << "  " << string(64, '-') << "\n";
 
    for (int g = 0; g < 6; g++) {
        string melhorTitulo = "(nenhum)";
        int    melhorViews  = -1;
 
        NodoDuplo* atual = listaCad.getCabeca();
        while (atual != nullptr) {
            if (atual->conteudo.genero == generos[g] &&
                atual->conteudo.numViews > melhorViews) {
                melhorViews  = atual->conteudo.numViews;
                melhorTitulo = atual->conteudo.titulo;
            }
            atual = atual->proximo;
        }
 
        cout << "  " << left
             << setw(20) << generos[g]
             << setw(32) << melhorTitulo
             << right << setw(10)
             << (melhorViews < 0 ? 0 : melhorViews) << "\n";
    }
}
 
// =============================================================
//  TITULOS NUNCA SELECIONADOS
// =============================================================
 
// ─────────────────────────────────────────────────────────────
//  titulosNaoSelecionados
//
//  Varre listaCad e exibe todos os titulos com numViews == 0.
//  Util para o admin identificar conteudo sem audiencia.
// ─────────────────────────────────────────────────────────────
void titulosNaoSelecionados(ListaDupla& listaCad) {
    separador("TITULOS NUNCA SELECIONADOS (Views = 0)");
 
    int contagem = 0;
    NodoDuplo* atual = listaCad.getCabeca();
 
    cout << "  " << left << setw(4)  << "Pos"
         << setw(32) << "Titulo"
         << setw(14) << "Tipo"
         << setw(16) << "Genero"
         << right << setw(6) << "Ano\n";
    cout << "  " << string(72, '-') << "\n";
 
    while (atual != nullptr) {
        if (atual->conteudo.numViews == 0) {
            contagem++;
            cout << "  " << left
                 << setw(4)  << contagem
                 << setw(32) << atual->conteudo.titulo
                 << setw(14) << atual->conteudo.tipo
                 << setw(16) << atual->conteudo.genero
                 << right << setw(6) << atual->conteudo.ano << "\n";
        }
        atual = atual->proximo;
    }
 
    if (contagem == 0)
        cout << "  \033[1;32mTodos os titulos foram assistidos ao menos uma vez!\033[0m\n";
    else
        cout << "\n  Total: \033[1;31m" << contagem
             << " titulo(s) nunca assistido(s)\033[0m\n";
}
 
// =============================================================
//  PAINEL CONSOLIDADO
// =============================================================
 
// ─────────────────────────────────────────────────────────────
//  exibirEstatisticas
//  Exibe todas as metricas em sequencia — usado pelo menu Admin.
// ─────────────────────────────────────────────────────────────
void exibirEstatisticas(ListaDupla& listaCad, Estatisticas& est) {
    cout << "\n\033[1;34m";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║            ESTATISTICAS DO SISTEMA               ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
    cout << "\033[0m";
 
    // Totais gerais
    separador("TOTAIS GERAIS");
    cout << "  Total de recomendacoes realizadas : "
         << est.totRecomendacoes << "\n";
    cout << "  Total de visualizacoes registradas: "
         << est.totVisualizacoes << "\n";
    cout << "  Titulos no catalogo               : "
         << listaCad.getTamanho() << "\n";
 
    // Mais/menos recomendado
    tipoMaisRecomendado(est);
    tipoMenosRecomendado(est);
    generoMaisRecomendado(est);
    generoMenosRecomendado(est);
 
    // Mais assistido por categoria
    tipoMaisAssistido(listaCad, est);
    generoMaisAssistido(listaCad, est);
 
    // Nunca selecionados
    titulosNaoSelecionados(listaCad);
 
    cout << "\n";
}
