// 1. Inicialização da inclusão do header
#ifndef ESTATISTICAS_H_INCLUDED
#define ESTATISTICAS_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>

// 3. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
class ListaContCad;

// 4. Struct para definir estatísticas
typedef struct Estatisticas {
// // 4.1. ESTATÍSTICAS GERAIS
    int totRecomendacoes = 0;
    int totVisualizacoes = 0;
// // 4.2. ESTATÍSTICAS TIPO
    int recFilme = 0;
    int recSerie = 0;
    int recDocumentario = 0;
    int recAnime = 0;
    int recCartoon = 0;
// // 4.3. ESTATISTICAS GENERO
    int recAcao = 0;
    int recComedia = 0;
    int recDrama = 0;
    int recTerror = 0;
    int recFicCientifica = 0;
    int recFantasia = 0;
} Estatisticas;

// 5. Funções que serão executadas no sistema
// // 5.1. TOTAIS GERAIS
int recomendacoesTotais(Estatisticas& estatistica);
int visualizacoesTotais(Estatisticas& estatistica);
// // 5.2. TIPO E GÊNERO MAIS RECOMENDADO
void tipoMaisRecomendado(Estatisticas& estatistica);
void generoMaisRecomendado(Estatisticas& estatistica);
// // 5.3. TIPO E GÊNERO MAIS ASSISTIDO
void tipoMaisAssistido(ListaContCad& listaCad, Estatisticas& estatistica);
void generoMaisAssistido(ListaContCad& listaCad, Estatisticas& estatistica);
// // 5.4. NÃO SELECIONADOS
void titulosNaoSelecionados(ListaContCad& listaCad, Estatisticas& estatistica);

#endif // ESTATISTICAS_H_INCLUDED
