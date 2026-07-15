// 1. Inicializacao da inclusao do header
#ifndef CONTEUDO_H_INCLUDED
#define CONTEUDO_H_INCLUDED

// 2. Inclusao de bibliotecas existentes
#include <string>

// 3. Declaracao de classes e structs das bibliotecas criadas para evitar inclusao ciclica
class ListaSimples;
class ListaDupla;

// 4. Definicao dos tipos, generos e periodo dos conteudos
enum TipoConteudo{FILME, SERIE, DOCUMENTARIO, ANIME, CARTOON, QUALQUER_TIPO};
enum GeneroConteudo{ACAO, COMEDIA, DRAMA, TERROR, FIC_CIENTIFICA, FANTASIA, QUALQUER_GENERO};
enum FiltroCronologico {RECENTE, ANTIGO, QUALQUER_ANO};

// 5. Struct para definir conte�do
typedef struct Conteudo {
    int id;
    std::string titulo;
    std::string tipo;
    std::string genero;
    int ano;
    int numViews;
    float avaliacao;
} Conteudo;

// 6. Funcoes que serao executadas no sistema
// // 6.1. CADASTRAR CONTE�DOS
void cadastrarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo, std::string tipo, std::string genero, int ano);
int gerarNovoId();
void atualizarProximoId(int maiorId);
// // 6.2. REMOVER CONTE�DOS
void removerConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, std::string titulo);
// // 6.3. LISTAR CONTE�DOS
void listaCadastrados(ListaDupla& listaCad);
void listaRecomendados(ListaSimples& listaRec);
void listaMaisAssistidos(ListaDupla& listaAssist);
// // 6.4. ASSISTIR CONTE�DOS
void assistirConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo);
void avaliarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo, float nota);

#endif // CONTEUDO_H_INCLUDED

