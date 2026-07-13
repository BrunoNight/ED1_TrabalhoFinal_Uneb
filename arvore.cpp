// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>
#include <cstdio>  // Equivalente ao <stdio.h> em C++
#include <cstring> // Necessário para usar funções de string, como o strtok para reconhecimento do arquivo de texto da árvore
#include <limits>
#include <cstdlib>

// 2. Inclusão de bibliotecas criadas
#include "arvore.h"
#include "menu.h"
#include "estetica.h"
#include "listas.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');
static const string bordaB(20, '=');

// 5. Função de construção da Árvore
Arvore::Arvore() {
    raiz = nullptr;
}

// 6. Função de desconstrução da Árvore
Arvore::~Arvore() {
    apagarArvore(raiz);
}

// 7. Função de apagar a árvore para limpar memória após fechar sistema ou sair da árvore de recomendação
void Arvore::apagarArvore(NodoA* atual) {
    if(atual != nullptr) {
        apagarArvore(atual -> sim);
        apagarArvore(atual -> nao);
        delete atual;
    }
}

// 8. Função para inserir novos nós conforme árvore de recomendação é usada
void Arvore::inserirPorCaminho(const string& caminho, const string& filtro, bool folha, int pTipo, int pGenero, int pCrono) {
    if(caminho.empty()) { 
        return;
    }

    if(raiz == nullptr) { 
        raiz = new NodoA();
        raiz->sim = nullptr; 
        raiz->nao = nullptr;
    }

    NodoA* atual = raiz; 

    size_t inicioTraco = caminho.find('-');
    
    if(inicioTraco != string::npos) {
        for(size_t i = inicioTraco + 1; i < caminho.length(); i++) { 
            if (caminho[i] == '-') {
                continue; 
            }

            if(caminho[i] == '1') {
                if(atual->sim == nullptr) { 
                    atual->sim = new NodoA();
                    atual->sim->sim = nullptr; 
                    atual->sim->nao = nullptr; 
                }
                atual = atual->sim; 
                
            } else if (caminho[i] == '2') {
                if (atual->nao == nullptr) { 
                    atual->nao = new NodoA();
                    atual->nao->sim = nullptr; 
                    atual->nao->nao = nullptr; 
                }
                atual = atual->nao; 
            }
        }
    }

    // Após percorrer o caminho, preenche os dados do nó de destino
    atual->texto = filtro;
    atual->folha = folha;

    // Se for folha, garante que não tem filhos e guarda os filtros numéricos
    if(folha) {
        atual->sim = nullptr;
        atual->nao = nullptr;
        
        // Conversão segura dos inteiros lidos do TXT para os Enums
        atual->tipoFiltro = static_cast<decltype(atual->tipoFiltro)>(pTipo);
        atual->generoFiltro = static_cast<decltype(atual->generoFiltro)>(pGenero);
        atual->cronologiaFiltro = static_cast<decltype(atual->cronologiaFiltro)>(pCrono);
    }
}

// 9. Função para ir lendo os dados da árvore (Atualizada para extrair os filtros das folhas)
void Arvore::gerarArvoreDecisao() { 
    FILE* arquivo = fopen("arvore_dados2.txt", "r");

    if(arquivo == nullptr) { 
        centralizarTexto("\n[Aviso] Arquivo arvore_dados.txt não pôde ser aberto! [Aviso]");
        return;
    }

    char linha[300]; 

    while(fgets(linha, sizeof(linha), arquivo) != nullptr) {
        linha[strcspn(linha, "\r\n")] = 0; // Limpa as quebras de linha com segurança

        if(strlen(linha) == 0) {
            continue;
        }

        char* parteCaminho = strtok(linha, ";"); 
        char* partePergunta = strtok(nullptr, ";"); 
        char* parteFolha = strtok(nullptr, ";"); 

        if (parteCaminho != nullptr && partePergunta != nullptr && parteFolha != nullptr) {
            bool folha = (parteFolha[0] == '1');
            
            int tFiltro = 0, gFiltro = 0, cFiltro = 0;

            // Só tenta ler mais dados da linha se for um nó final (folha)
            if (folha) {
                char* pTipo = strtok(nullptr, ";");
                char* pGenero = strtok(nullptr, ";");
                char* pCrono = strtok(nullptr, ";");

                if (pTipo && pGenero && pCrono) {
                    tFiltro = atoi(pTipo); 
                    gFiltro = atoi(pGenero);
                    cFiltro = atoi(pCrono);
                }
            }

            // Chama a inserção passando os filtros também
            inserirPorCaminho(parteCaminho, partePergunta, folha, tFiltro, gFiltro, cFiltro);
        }
    }

    fclose(arquivo);
}

// 10. Função para inserção das perguntas e filtração dos resultados
void Arvore::inserirFiltrar(NodoA* atual, ListaDupla& listaCad, ListaSimples& listaRec) {
    if(atual == nullptr) {
        centralizarTexto(Estetica::RED + "\n[Aviso] Beco sem saída alcançado! [Aviso]");
        centralizarTexto("O caminho que você escolheu ainda não foi cadastrado no arquivo TXT.");
        return;
    }

    if(!(atual->folha)) {
        int opcao = 0;
        while(true) {
            centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
            centralizarTexto(Estetica::GREEN + atual->texto); 
            centralizarTexto(Estetica::YELLOW + " (> " + bordaB + Estetica::YELLOW + " <) ");
            centralizarTexto(Estetica::RED + "1 - Sim");
            centralizarTexto(Estetica::RED + "2 - Não");
            centralizarTexto(Estetica::RED + "Escolha uma opção (1 ou 2): ");
            
            cin >> opcao;

            if(cin.fail() || opcao < 1 || opcao > 2) {
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                centralizarTexto("\n[Aviso] Opção inválida! Digite apenas 1 (Sim) ou 2 (Não) [Aviso]");
            } else {
                limparBufferEntrada(); 
                break;
            }
        }

        if(opcao == 1) {
            inserirFiltrar(atual->sim, listaCad, listaRec);
        } else {
            inserirFiltrar(atual->nao, listaCad, listaRec);
        }
        
    } else {
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");
        centralizarTexto(Estetica::RED + "  RECOMENDAÇÃO BASEADA NO SEU PERFIL: " + atual->texto);
        centralizarTexto(Estetica::YELLOW + " (> " + bordaA + Estetica::YELLOW + " <) ");

        listaRec.limpar();

        NodoDuplo* nav = listaCad.getCabeca();

        while(nav != nullptr) {
            Conteudo& c = nav->conteudo;
            bool tipoBool = false;
            bool generoBool = false;
            bool anoBool = false;

            switch(atual->tipoFiltro) {
                case FILME:         tipoBool = (c.tipo == "Filme"); break;
                case SERIE:         tipoBool = (c.tipo == "Série"); break;
                case DOCUMENTARIO:  tipoBool = (c.tipo == "Documentário"); break;
                case ANIME:         tipoBool = (c.tipo == "Anime"); break;
                case CARTOON:       tipoBool = (c.tipo == "Cartoon"); break;
                case QUALQUER_TIPO: tipoBool = true; break;
                default: break;
            }

            switch (atual->generoFiltro) {
                case ACAO:            generoBool = (c.genero == "Ação"); break;
                case COMEDIA:         generoBool = (c.genero == "Comédia"); break;
                case DRAMA:           generoBool = (c.genero == "Drama"); break;
                case TERROR:          generoBool = (c.genero == "Terror"); break;
                case FIC_CIENTIFICA:  generoBool = (c.genero == "Ficção Científica"); break;
                case FANTASIA:        generoBool = (c.genero == "Fantasia"); break;
                case QUALQUER_GENERO: generoBool = true; break;
                default: break;
            }

            switch (atual->cronologiaFiltro) {
                case RECENTE:      anoBool = (c.ano >= 2000); break;
                case ANTIGO:       anoBool = (c.ano < 2000); break;
                case QUALQUER_ANO: anoBool = true; break;
                default: break;
            }

            if (tipoBool && generoBool && anoBool) {
                listaRec.inserirOrdenado(c);
            }

            nav = nav->proximo; 
        }

        listaRecomendados(listaRec);
    }
}

