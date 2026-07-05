// 1. Inicialização da inclusão do header
#ifndef CONTEUDO_H_INCLUDED
#define CONTEUDO_H_INCLUDED

// 2. Inclusão de bibliotecas existentes
#include <string>

// 3. Declaração de classes e structs das bibliotecas criadas para evitar inclusão cíclica
class ListaSimples;
class ListaDupla;

// 4. Definição dos tipos, gêneros e período dos conteúdos
enum TipoConteudo{FILME, SERIE, DOCUMENTARIO, ANIME, CARTOON, QUALQUER_TIPO};
enum GeneroConteudo{ACAO, COMEDIA, DRAMA, TERROR, FIC_CIENTIFICA, FANTASIA, QUALQUER_GENERO};
enum FiltroCronologico {RECENTE, ANTIGO, QUALQUER_ANO};

// 5. Struct para definir conteúdo
typedef struct Conteudo {
    int id;
    std::string titulo;
    std::string tipo;
    std::string genero;
    int ano;
    int numViews;
    float avaliacao;
} Conteudo;

// 6. Funções que serão executadas no sistema
// // 6.1. CADASTRAR CONTEÚDOS
void cadastrarConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo, std::string tipo, std::string genero, int ano);
int gerarNovoId();
// // 6.2. REMOVER CONTEÚDOS
void removerConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, ListaSimples& listaRec, std::string titulo);
// // 6.3. LISTAR CONTEÚDOS
void listaCadastrados(ListaDupla& listaCad);
void listaRecomendados(ListaSimples& listaRec);
void listaMaisAssistidos(ListaDupla& listaAssist);
// // 6.4. ASSISTIR CONTEÚDOS
void assistirConteudo(ListaDupla& listaCad, ListaDupla& listaAssist, std::string titulo);

#endif // CONTEUDO_H_INCLUDED

