// 1. Inclusão de bibliotecas existentes
#include <iomanip>

// 2. Inclusão de bibliotecas criadas
#include "listas.h"
#include "estetica.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// // // LISTA SIMPLESMENTE ENCADEADA

// 4. Função de construtor da lista simples
ListaSimples::ListaSimples() {
	cabeca = nullptr;
	tamanho = 0;
}

// 5. Função de inserir de forma ordenada um conteúdo na lista simples
void ListaSimples::inserirOrdenado(Conteudo& c) {
    NodoSimples* novo = new NodoSimples(c);

    // Casos 1 e 2
    if (cabeca == nullptr || c.avaliacao > cabeca->conteudo.avaliacao) {
        novo->proximo = cabeca;
        cabeca = novo;
    } else {
        // Caso 3: avança enquanto o próximo ainda tem avaliação >= c.avaliacao
        NodoSimples* atual = cabeca;
        while (atual->proximo != nullptr && atual->proximo->conteudo.avaliacao >= c.avaliacao) {
            atual = atual->proximo;
        }
        novo->proximo  = atual->proximo;
        atual->proximo = novo;
    }
    tamanho++;
}

// 6. Função de remoção de um conteúdo na lista simples
bool ListaSimples::remover(const string& nome) {
    if (cabeca == nullptr) return false;

    // Remoção na cabeça
    if (cabeca->conteudo.titulo == nome) {
        NodoSimples* temp = cabeca;
        cabeca = cabeca->proximo;
        delete temp;
        tamanho--;
        return true;
    }

    // Remoção no meio/cauda
    NodoSimples* atual = cabeca;
    while (atual->proximo != nullptr) {
        if (atual->proximo->conteudo.titulo == nome) {
            NodoSimples* temp = atual->proximo;
            atual->proximo = temp->proximo;
            delete temp;
            tamanho--;
            return true;
        }
        atual = atual->proximo;
    }
    return false; // Não encontrado
}

// 7. Função de buscar um conteúdo na lista simples
NodoSimples* ListaSimples::buscar(const string& nome){
    NodoSimples* atual = cabeca;
    while (atual != nullptr) {
        if (atual->conteudo.titulo == nome) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}

// 8. Função de exibir o conteúdo na lista simples
void ListaSimples::exibir(){
    if (cabeca == nullptr) {
        centralizarTexto("  [Lista vazia]\n");
        return;
    }

    cout << left << "  " << std::setw(4) << "Pos"
              << setw(32) << "Nome"
              << setw(14) << "Tipo"
              << setw(18) << "Genero"
              << setw(6)  << "Ano"
              << "Avaliacao\n";
   	cout << "  " + string(78, '-') + "\n";

    /*centralizarTexto(string("  ") + "Pos"
              + "Nome"
              + "Tipo"
              + "Genero"
              + "Ano"
              + "Avaliacao\n");*/
   	cout << "  " + string(78, '-') + "\n";

    int pos = 1;
    NodoSimples* atual = cabeca;
    while (atual != nullptr) {
        Conteudo& c = atual->conteudo;
        cout << "  " << left << setw(4) << pos++
                  << setw(32) << c.titulo
                  << setw(14) << c.tipo
                  << setw(18) << c.genero
                  << setw(6)  << c.ano
                  << fixed << setprecision(1) << c.avaliacao << "\n";
        
        /*centralizarTexto(string("  ")+ to_string(pos++)
                  + c.titulo
                  + c.tipo
                  + c.genero
                  + to_string(c.ano)
                  + to_string(c.avaliacao) + "\n");*/
        atual = atual->proximo;
    }
}

// 9. Função para pegar o tamanho da lista simples
int  ListaSimples::getTamanho() { return tamanho; } // NÃO É USADO

// 10. Função para verificar se lista simples está vazia
bool ListaSimples::estaVazia() { return cabeca == nullptr; } // NÃO É USADO

// 11. Função para limpar lista simples
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

// // // LISTA DUPLAMENTE ENCADEADA

// 12. Função de construtor da lista dupla
ListaDupla::ListaDupla() {
    cabeca = nullptr;
    cauda = nullptr;
    tamanho = 0;
}

// 13. Função de desvinculação de nó na lista dupla
void ListaDupla::desvincular(NodoDuplo* no) {
    // Reconecta o anterior ao próximo
    if (no->anterior != nullptr){
        no->anterior->proximo = no->proximo;
    } else {
        cabeca = no->proximo;   // Era a cabeça
 	}
    // Reconecta o próximo ao anterior
    if (no->proximo != nullptr) {
        no->proximo->anterior = no->anterior;
    } else {
        cauda = no->anterior;   // Era a cauda
 	}
    // Isola o nó
    no->proximo  = nullptr;
    no->anterior = nullptr;
}

// 14. Função de inserção de nó na lista dupla
void ListaDupla::inserirNo(NodoDuplo* no) {
    // Caso 1
    if (cabeca == nullptr) {
        cabeca = cauda = no;
        return;
    }

    // Caso 2
    if (no->conteudo.numViews > cabeca->conteudo.numViews) {
        no->proximo    = cabeca;
        cabeca->anterior = no;
        cabeca         = no;
        return;
    }

    // Caso 3: avança enquanto o próximo tem visualizações maiores
    NodoDuplo* atual = cabeca;
    while (atual->proximo != nullptr && atual->proximo->conteudo.numViews >= no->conteudo.numViews) {
        atual = atual->proximo;
    }

    if (atual->proximo != nullptr) {
        no->proximo  = atual->proximo;
        no->anterior = atual;
        atual->proximo->anterior = no;
    } else {
        no->proximo  = nullptr;
        no->anterior = atual;
        cauda = no; // novo nó virou cauda
    }

    atual->proximo = no;
}

// 15. Função de reposição de nó na lista dupla
void ListaDupla::reposicionar(NodoDuplo* no) {
    // Verifica se saiu de ordem (só pode subir, pois acabou de incrementar)
    bool fora_de_ordem = (no->anterior != nullptr && no->conteudo.numViews > no->anterior->conteudo.numViews);

    if (!fora_de_ordem) return; // já está na posição correta

    desvincular(no);
    inserirNo(no);
}

// 16. Função de inserção ordendada do conteúdo na lista dupla
void ListaDupla::inserirOrdenado(Conteudo& c) {
    NodoDuplo* novo = new NodoDuplo(c);
    inserirNo(novo);
    tamanho++;
}

// 17. Função de remoção do conteúdo na lista dupla
bool ListaDupla::remover(string nome) {
    NodoDuplo* no = buscar(nome);
    if (no == nullptr) return false;

    desvincular(no);
    delete no;
    tamanho--;
    return true;
}

// 18. Função de busca de conteúdo na lista dupla
NodoDuplo* ListaDupla::buscar(string nome){
    NodoDuplo* atual = cabeca;
    while (atual != nullptr) {
        if (atual->conteudo.titulo == nome) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}

// 19. Função de exibir conteúdos da lista dupla
void ListaDupla::exibirFrente(){
    if (cabeca == nullptr) {
        centralizarTexto("  [Lista vazia]\n");
        return;
    }

    cout << left << "  " << setw(5) << "Rank"
              << setw(32) << "Nome"
              << setw(14) << "Tipo"
              << setw(18) << "Gênero"
              << right << "Visualizações\n";

    /*centralizarTexto(string("  ")+ "Rank"
              + "Nome"
              + "Tipo"
              + "Gênero"
              + "Visualizações\n");*/
    cout << "  " + string(78, '-') + "\n";

    int pos = 1;
    NodoDuplo* atual = cabeca;
    while (atual != nullptr) {
        const Conteudo& c = atual->conteudo;
        cout << "  " << left << setw(5) << ("#" + to_string(pos++))
                  << setw(32) << c.titulo
                  << setw(14) << c.tipo
                  << setw(18) << c.genero
                  << right << std::setw(8) << c.numViews << "\n";
        
        /*centralizarTexto("  " + ("#" + to_string(pos++))
                  + c.titulo
                  + c.tipo
                  + c.genero
                  + to_string(c.numViews) + "\n");*/
        atual = atual->proximo;
    }
}

// 20. Função de exibir conteúdos da lista dupla de forma reversa
void ListaDupla::exibirReverso() {
    if (cauda == nullptr) {
        centralizarTexto("  [Lista vazia]\n");
        return;
    }

    cout << left << "  " << setw(5) << "Rank"
              << setw(32) << "Nome"
              << right << "Visualizações\n";

    /*centralizarTexto(string("  ")+ "Rank"
              + "Nome"
              + "Visualizações\n");*/
    cout << "  " + string(50, '-') + "\n";

    int pos = tamanho;
    NodoDuplo* atual = cauda;
    while (atual != nullptr) {
        Conteudo& c = atual->conteudo;
        cout << "  " << left << setw(5) << ("#" + to_string(pos--))
                  << setw(32) << c.titulo
                  << right << setw(8) << c.numViews << "\n";
        
        /*centralizarTexto("  " + ("#" + to_string(pos--))
                              + c.titulo
                              + to_string(c.numViews) + "\n");*/
        atual = atual->anterior;
    }
}

// 21. Função de assistir conteúdo na lista dupla
bool ListaDupla::incrementarVisualizacoes(string nome) {
    NodoDuplo* no = buscar(nome);
    if (no == nullptr) return false;

    no->conteudo.numViews++;
    reposicionar(no);
    return true;
}

// 22. Função para pegar o tamanho da lista dupla
int  ListaDupla::getTamanho() { return tamanho; } // NÃO É USADO

// 23. Função para verificar se lista dupla está vazia
bool ListaDupla::estaVazia()  { return cabeca == nullptr; } // NÃO É USADO

// 24. Função para limpar lista dupla
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

NodoDuplo* ListaDupla::getCabeca() {
    return cabeca;
}

