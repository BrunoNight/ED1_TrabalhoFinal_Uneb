#include "listas.h"
#include <iomanip>
 
// ─────────────────────────────────────────────────────────────
//  Construtor / Destrutor
// ─────────────────────────────────────────────────────────────
ListaSimples::ListaSimples() {
	cabeca = nullptr; 
	tamanho = 0;
}
    
 
ListaSimples::~ListaSimples() {
    limpar();
}
 
// ─────────────────────────────────────────────────────────────
//  inserirOrdenado
//
//  Percorre a lista até encontrar o ponto onde a avaliação do
//  novo nó é maior que o próximo elemento, garantindo ordem
//  DECRESCENTE. Em caso de empate, o novo nó fica depois.
//
//  Casos tratados:
//    1. Lista vazia          → novo vira a cabeça
//    2. Maior que a cabeça   → novo vira a nova cabeça
//    3. Meio / cauda         → percorre até a posição correta
// ─────────────────────────────────────────────────────────────
void ListaSimples::inserirOrdenado(Conteudo& c) {
    NodoSimples* novo = new NodoSimples(c);
 
    // Caso 1 e 2
    if (cabeca == nullptr || c.avaliacao > cabeca->conteudo.avaliacao) {
        novo->proximo = cabeca;
        cabeca = novo;
    } else {
        // Caso 3: avança enquanto o próximo ainda tem avaliação >= c.avaliacao
        NodoSimples* atual = cabeca;
        while (atual->proximo != nullptr &&
               atual->proximo->conteudo.avaliacao >= c.avaliacao) {
            atual = atual->proximo;
        }
        novo->proximo  = atual->proximo;
        atual->proximo = novo;
    }
    tamanho++;
}
 
// ─────────────────────────────────────────────────────────────
//  remover
//
//  Remove o primeiro nó cujo nome corresponde ao parâmetro.
//  Libera a memória com delete.
//  Retorna true em caso de sucesso, false se não encontrado.
// ─────────────────────────────────────────────────────────────
bool ListaSimples::remover(string& nome) {
    if (cabeca == nullptr) return false;
 
    // Remoção na cabeça
    if (cabeca->conteudo.titulo == nome) {
        NodoSimples* temp = cabeca;
        delete temp;
        tamanho--;
        return true;
    }
 
    // Remoção no meio/cauda
    NodoSimples* atual = cabeca;
    while (atual->proximo != nullptr) {
        if (atual->proximo->conteudo.titulo == nome) {
            NodoSimples* temp  = atual->proximo;
            atual->proximo   = temp->proximo;
            delete temp;
            tamanho--;
            return true;
        }
        atual = atual->proximo;
    }
    return false; // não encontrado
}
 
// ─────────────────────────────────────────────────────────────
//  buscar
// ─────────────────────────────────────────────────────────────
NodoSimples* ListaSimples::buscar(string& nome){
    NodoSimples* atual = cabeca;
    while (atual != nullptr) {
        if (atual->conteudo.titulo == nome) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}
 
// ─────────────────────────────────────────────────────────────
//  exibir  –  formata em colunas para leitura clara no terminal
// ─────────────────────────────────────────────────────────────
void ListaSimples::exibir(){
    if (cabeca == nullptr) {
        cout << "  [Lista vazia]\n";
        return;
    }
 
   cout << left
              << "  " << std::setw(4)  << "Pos"
              << setw(32) << "Nome"
              << setw(14) << "Tipo"
              << setw(18) << "Genero"
              << setw(6)  << "Ano"
              << "Avaliacao\n";
   	cout << "  " << string(78, '-') << "\n";
 
    int pos = 1;
    NodoSimples* atual = cabeca;
    while (atual != nullptr) {
        Conteudo& c = atual->conteudo;
        cout << "  " << std::left
                  <<setw(4)  << pos++
                  << setw(32) << c.titulo
                  << setw(14) << c.tipo
                  << setw(18) << c.genero
                  << setw(6)  << c.ano;
        atual = atual->proximo;
    }
}
 
// ─────────────────────────────────────────────────────────────
//  Utilitários
// ─────────────────────────────────────────────────────────────
int  ListaSimples::getTamanho() { return tamanho; }
bool ListaSimples::estaVazia() { return cabeca == nullptr; }
 
void ListaSimples::limpar() {
    NodoSimples* atual = cabeca;
    while (atual != nullptr) {
        NodoSimples* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    cabeca  = nullptr;
    tamanho = 0;
}

// Lista Duplamente Encadeada

ListaDupla::ListaDupla() {
    cabeca = nullptr; 
    cauda = nullptr;
    tamanho = 0;
}

ListaDupla::~ListaDupla() {
    limpar();
}
 

void ListaDupla::desvincular(NodoDuplo* no) {
    // Reconecta o anterior ao próximo
    if (no->anterior != nullptr){
        no->anterior->proximo = no->proximo;
    }else{
        cabeca = no->proximo;   // era a cabeça
 	}
    // Reconecta o próximo ao anterior
    if (no->proximo != nullptr) {
        no->proximo->anterior = no->anterior;
    }else {
        cauda = no->anterior;   // era a cauda
 	}
    // Isola o nó
    no->proximo  = nullptr;
    no->anterior = nullptr;
}
 
// ─────────────────────────────────────────────────────────────
//  inserirNo (auxiliar privado)
//
//  Insere um nó (já alocado) na posição correta da lista,
//  mantendo ordem DECRESCENTE por visualizações.
//
//  Casos tratados:
//    1. Lista vazia          → nó vira cabeça e cauda
//    2. Maior/igual à cabeça → nó vira nova cabeça
//    3. Meio / cauda         → percorre até posição correta
// ─────────────────────────────────────────────────────────────
void ListaDupla::inserirNo(NodoDuplo* no) {
    // Caso 1
    if (cabeca == nullptr) {
        cabeca = cauda = no;
        return;
    }
 
    // Caso 2
    if (no->conteudo.numViews >= cabeca->conteudo.numViews) {
        no->proximo    = cabeca;
        cabeca->anterior = no;
        cabeca         = no;
        return;
    }
 
    // Caso 3: avança enquanto o próximo tem visualizações maiores
    NodoDuplo* atual = cabeca;
    while (atual->proximo != nullptr &&
           atual->proximo->conteudo.numViews > no->conteudo.numViews) {
        atual = atual->proximo;
    }
 
    // Insere após 'atual'
    no->proximo  = atual->proximo;
    no->anterior = atual;
 
    if (atual->proximo != nullptr)
        atual->proximo->anterior = no;
    else
        cauda = no;             // novo nó virou cauda
 
    atual->proximo = no;
}
 
// ─────────────────────────────────────────────────────────────
//  reposicionar (auxiliar privado)
//
//  Chamado após incrementarVisualizacoes. Só reposiciona se o
//  nó atual violou a ordem (visualizacoes > anterior->visualizacoes).
//  Usa desvincular + inserirNo para recolocar na posição exata,
//  evitando múltiplas trocas de bubble.
// ─────────────────────────────────────────────────────────────
void ListaDupla::reposicionar(NodoDuplo* no) {
    // Verifica se saiu de ordem (só pode subir, pois acabou de incrementar)
    bool fora_de_ordem = (no->anterior != nullptr &&
                          no->conteudo.numViews > no->anterior->conteudo.numViews);
 
    if (!fora_de_ordem) return; // já está na posição correta
 
    desvincular(no);
    inserirNo(no);
}
 
// ─────────────────────────────────────────────────────────────
//  inserirOrdenado  (público)
// ─────────────────────────────────────────────────────────────
void ListaDupla::inserirOrdenado(Conteudo& c) {
    NodoDuplo* novo = new NodoDuplo(c);
    inserirNo(novo);
    tamanho++;
}
 
// ─────────────────────────────────────────────────────────────
//  remover  (público)
// ─────────────────────────────────────────────────────────────
bool ListaDupla::remover(string& nome) {
    NodoDuplo* no = buscar(nome);
    if (no == nullptr) return false;
 
    desvincular(no);
    delete no;
    tamanho--;
    return true;
}
 
// ─────────────────────────────────────────────────────────────
//  buscar  (público)
// ─────────────────────────────────────────────────────────────
NodoDuplo* ListaDupla::buscar(string& nome){
    NodoDuplo* atual = cabeca;
    while (atual != nullptr) {
        if (atual->conteudo.titulo == nome) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}
 
// ─────────────────────────────────────────────────────────────
//  exibirFrente  –  cabeça → cauda  (ranking global)
// ─────────────────────────────────────────────────────────────
void ListaDupla::exibirFrente(){
    if (cabeca == nullptr) {
        cout << "  [Lista vazia]\n";
        return;
    }
 
    cout << std::left
              << "  " << setw(5)  << "Rank"
              << setw(32) << "Nome"
              << setw(14) << "Tipo"
              << setw(18) << "Genero"
              << right << "Visualizacoes\n";
    cout << "  " << string(78, '-') << "\n";
 
    int pos = 1;
    NodoDuplo* atual = cabeca;
    while (atual != nullptr) {
        const Conteudo& c = atual->conteudo;
        cout << "  " << left
                  << setw(5)  << ("#" + to_string(pos++))
                  << setw(32) << c.titulo
                  << setw(14) << c.tipo
                  << setw(18) << c.genero
                  << right << std::setw(8) << c.numViews << "\n";
        atual = atual->proximo;
    }
}
 
// ─────────────────────────────────────────────────────────────
//  exibirReverso  –  cauda → cabeça  (via ponteiro anterior)
// ─────────────────────────────────────────────────────────────
void ListaDupla::exibirReverso() {
    if (cauda == nullptr) {
        cout << "  [Lista vazia]\n";
        return;
    }
 
    cout << left
              << "  " << setw(5)  << "Rank"
              << setw(32) << "Nome"
              << right << "Visualizacoes\n";
    cout << "  " << string(50, '-') << "\n";
 
    int pos = tamanho;
    NodoDuplo* atual = cauda;
    while (atual != nullptr) {
        Conteudo& c = atual->conteudo;
        cout << "  " << left
                  << setw(5)  << ("#" + to_string(pos--))
                  << setw(32) << c.titulo
                  << right << setw(8) << c.numViews << "\n";
        atual = atual->anterior;
    }
}
 
// ─────────────────────────────────────────────────────────────
//  incrementarVisualizacoes  –  botão "Assistir"
// ─────────────────────────────────────────────────────────────
bool ListaDupla::incrementarVisualizacoes(string& nome) {
    NodoDuplo* no = buscar(nome);
    if (no == nullptr) return false;
 
    no->conteudo.numViews++;
    reposicionar(no);
    return true;
}
 
// ─────────────────────────────────────────────────────────────
//  Utilitários
// ─────────────────────────────────────────────────────────────
int  ListaDupla::getTamanho() { return tamanho; }
bool ListaDupla::estaVazia()  { return cabeca == nullptr; }
 
void ListaDupla::limpar() {
    NodoDuplo* atual = cabeca;
    while (atual != nullptr) {
        NodoDuplo* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    cabeca  = nullptr;
    cauda   = nullptr;
    tamanho = 0;
}
