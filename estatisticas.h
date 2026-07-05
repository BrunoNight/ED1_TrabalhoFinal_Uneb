#ifndef ESTATISTICAS_H_INCLUDED
#define ESTATISTICAS_H_INCLUDED

#include <string>

// FIX: era "class ListaContCad" -- tipo inexistente no projeto
class ListaDupla;

// Struct de contadores acumulados em tempo real
typedef struct Estatisticas {
    // Totais gerais
    int totRecomendacoes = 0;
    int totVisualizacoes = 0;
    // Contagem por TIPO (recomendacoes)
    int recFilme        = 0;
    int recSerie        = 0;
    int recDocumentario = 0;
    int recAnime        = 0;
    int recCartoon      = 0;
    // Contagem por GENERO (recomendacoes)
    int recAcao          = 0;
    int recComedia       = 0;
    int recDrama         = 0;
    int recTerror        = 0;
    int recFicCientifica = 0;
    int recFantasia      = 0;
} Estatisticas;

// Chamado ao assistir um titulo: incrementa contadores corretos
void registrarRecomendacao(Estatisticas& est,
                            const std::string& tipo,
                            const std::string& genero);

// Totais gerais
int recomendacoesTotais(Estatisticas& est);
int visualizacoesTotais(Estatisticas& est);

// Tipo mais/menos recomendado (por contagem de recomendacoes)
void tipoMaisRecomendado (Estatisticas& est);
void tipoMenosRecomendado(Estatisticas& est);  // FIX: ausente no original

// Genero mais/menos recomendado
void generoMaisRecomendado (Estatisticas& est);
void generoMenosRecomendado(Estatisticas& est); // FIX: ausente no original

// Titulo mais assistido por tipo / por genero (varre listaCad)
// FIX: eram "ListaContCad" -- tipo inexistente
void tipoMaisAssistido  (ListaDupla& listaCad, Estatisticas& est);
void generoMaisAssistido(ListaDupla& listaCad, Estatisticas& est);

// Titulos nunca selecionados (numViews == 0)
void titulosNaoSelecionados(ListaDupla& listaCad);

// Exibe todas as metricas de uma vez (painel de estatisticas)
void exibirEstatisticas(ListaDupla& listaCad, Estatisticas& est);

#endif // ESTATISTICAS_H_INCLUDED
