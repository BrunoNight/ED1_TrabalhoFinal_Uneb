// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>
#include <windows.h> // Necessário para getLarguraTerminal

// 2. Inclusão de bibliotecas criadas
#include "estetica.h"

// 3. Evitar escrever "std::" toda vez que aparece casos que envolvem string
using namespace std;

// 4. Visual: Bordas do sistema
static const string bordaA(50, '-');

// 5. Função para pegar largura do terminal para centralizar texto
int getLarguraTerminal() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// 6. Função para centralizar texto
void centralizarTexto(const string& texto) {
    int larguraTerminal = getLarguraTerminal();
    int tamanhoTexto = static_cast<int>(texto.length());

    int espacos = (larguraTerminal - tamanhoTexto) / 2;

    if (espacos < 0) espacos = 0; // Proteção para textos muito longos

    for(int i = 0; i < espacos; i++) {
        cout << " ";
    }
    cout << texto << endl;
}

// 7. Função para gerar o cabeçalho com o nome do sistema durante seu funcionamento
void esteticaCabeçalhoSistema() {
    // Limpa a tela do terminal a cada transição
    system("cls");

    int largura = getLarguraTerminal();

    // Logo impressa
    cout << endl;
    centralizarTexto(Estetica::RED + "+[" + bordaA + "]+" + Estetica::RESET, largura);
    centralizarTexto(Estetica::RED + " (>  " + Estetica::YELLOW + "MEUFLIX" + Estetica::RED + "  |  SISTEMA DE STREAMING" + Estetica::RESET, largura);
    centralizarTexto(Estetica::RED + "+[" + bordaA + "]+" + Estetica::RESET, largura);
    cout << endl;
}
