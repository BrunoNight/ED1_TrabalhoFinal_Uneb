// 1. Inclusão de bibliotecas existentes
#include <iostream>
#include <string>
#include <windows.h> // Necessário para getLarguraTerminal
#include <regex> // Necessário para a limpeza das tags

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

// 6. Função para obter o tamanho real, ignorando códigos ANSI
size_t tamanhoReal(const string& texto) {
// O modificador static garante que o objeto regex seja criado apenas na primeira chamada
    static const regex ansi_regex("\033\\[[0-9;]*m");
    string textoLimpo = regex_replace(texto, ansi_regex, "");
    return textoLimpo.length();
}

// 6. Função para centralizar texto
void centralizarTexto(const string& texto) {
    int larguraTerminal = getLarguraTerminal(); // Sua função existente
    int tamanhoTexto = static_cast<int>(tamanhoReal(texto));
    int espacos = (larguraTerminal - tamanhoTexto) / 2;

    if(espacos < 0) {
        espacos = 0;
    }

    for(int i = 0; i < espacos; i++) {
        cout << " ";
    }

    cout << texto << endl;
}

// 7. Função para gerar o cabeçalho com o nome do sistema durante seu funcionamento
void esteticaCabecalhoSistema() {
    // Limpa a tela do terminal a cada transição
    system("cls");

    int largura = getLarguraTerminal();

    // Logo impressa
    cout << endl;
    centralizarTexto(Estetica::RED + "+[" + bordaA + "]+" + Estetica::RESET); 
    centralizarTexto(Estetica::RED + " (> " + "--- MEUFLIX ---" + " <)" + Estetica::RESET);
    centralizarTexto(Estetica::RED + "+[" + bordaA + "]+" + Estetica::RESET); 
    cout << endl;
}

// 8. Função para limpar mensagens de erro por digitação inválida no cin
void limparBufferEntrada() {
    cin.clear();
    cin.ignore(256, '\n');
}
