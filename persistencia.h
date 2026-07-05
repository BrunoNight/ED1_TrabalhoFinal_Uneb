#ifndef PERSISTENCIA_H_INCLUDED
#define PERSISTENCIA_H_INCLUDED

#include <string>

class ListaDupla;
class ListaSimples;
struct Estatisticas;

// ── Catalogo (listaCad) ──────────────────────────────────────
// Grava listaCad em disco; cria o arquivo se nao existir
bool salvarCatalogo(ListaDupla& listaCad,
                    const std::string& nomeArq = "catalogo.csv");

// Carrega catalogo do disco e popula listaCad E listaAssist
// Retorna o numero de titulos carregados (0 se arquivo nao existe)
int  carregarCatalogo(ListaDupla& listaCad, ListaDupla& listaAssist,
                      const std::string& nomeArq = "catalogo.csv");

// ── Ranking (listaAssist) ────────────────────────────────────
// Salva apenas as views atualizadas de cada titulo em listaAssist
bool salvarRanking(ListaDupla& listaAssist,
                   const std::string& nomeArq = "ranking.csv");

// Atualiza numViews em listaCad com os valores persistidos no ranking
// (chamado apos carregarCatalogo para restaurar o estado do ranking)
int  carregarRanking(ListaDupla& listaCad, ListaDupla& listaAssist,
                     const std::string& nomeArq = "ranking.csv");

// ── Estatisticas ─────────────────────────────────────────────
bool salvarEstatisticas(Estatisticas& est,
                        const std::string& nomeArq = "estatisticas.csv");

bool carregarEstatisticas(Estatisticas& est,
                          const std::string& nomeArq = "estatisticas.csv");

// ── Funcao conveniente: salva tudo de uma vez ─────────────────
// Chamada ao fechar o programa
void salvarTudo(ListaDupla& listaCad, ListaDupla& listaAssist,
                Estatisticas& est);

// Funcao conveniente: carrega tudo ao iniciar o programa
// Retorna numero de titulos carregados
int  carregarTudo(ListaDupla& listaCad, ListaDupla& listaAssist,
                  Estatisticas& est);

#endif // PERSISTENCIA_H_INCLUDED
