#ifndef PERSISTENCIA_H_INCLUDED
#define PERSISTENCIA_H_INCLUDED

#include <string>

class ListaDupla;
class ListaUsuarios;
class ListaSimples;
struct Estatisticas;

// ── Catalogo (listaCad) ──────────────────────────────────────
// Grava listaCad em disco; cria o arquivo se nao existir
bool salvarCatalogo(ListaDupla& listaCad, const std::string& nomeArq = "data/catalogo.csv");

// Carrega catalogo do disco e popula listaCad E listaAssist
// Retorna o numero de titulos carregados (0 se arquivo nao existe)
int  carregarCatalogo(ListaDupla& listaCad, ListaDupla& listaAssist,
                      const std::string& nomeArq = "data/catalogo.csv");

// ── Ranking (listaAssist) ────────────────────────────────────
// Salva apenas as views atualizadas de cada titulo em listaAssist
bool salvarRanking(ListaDupla& listaAssist, const std::string& nomeArq = "data/ranking.csv");

// Atualiza numViews em listaCad com os valores persistidos no ranking
// (chamado apos carregarCatalogo para restaurar o estado do ranking)
int  carregarRanking(ListaDupla& listaCad, ListaDupla& listaAssist, const std::string& nomeArq = "data/ranking.csv");

// ── Estatisticas ─────────────────────────────────────────────
bool salvarEstatisticas(Estatisticas& est, const std::string& nomeArq = "data/estatisticas.csv");

bool carregarEstatisticas(Estatisticas& est, const std::string& nomeArq = "data/estatisticas.csv");

bool salvarUsuarios(ListaUsuarios& listaUsuarios, const std::string& nomeArq = "data/usuarios.csv");
int carregarUsuarios(ListaUsuarios& listaUsuarios, const std::string& nomeArq = "data/usuarios.csv");

// ── Funcao conveniente: salva tudo de uma vez ─────────────────
// Chamada ao fechar o programa
void salvarTudo(ListaDupla& listaCad, ListaDupla& listaAssist, Estatisticas& est, ListaUsuarios& listaUsuarios);

// Funcao conveniente: carrega tudo ao iniciar o programa
// Retorna numero de titulos carregados
int carregarTudo(ListaDupla& listaCad, ListaDupla& listaAssist, Estatisticas& est, ListaUsuarios& listaUsuarios);

#endif // PERSISTENCIA_H_INCLUDED
