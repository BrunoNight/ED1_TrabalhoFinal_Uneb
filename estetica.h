// 1. Inicialização da inclusão do header
#ifndef ESTETICA_H_INCLUDED
#define ESTETICA_H_INCLUDED

// 2. Incluir bibliotecas existentes
#include <string>

// 3. Função para cores de texto do sistema
namespace Estetica {
    const std::string RED = "\033[1;31m";
    const std::string YELLOW = "\033[1;33m";
    const std::string GREEN = "\033[1;32m";
    const std::string RESET = "\033[0m";
}

// 4. Outras funções para o estetica.cpp
// // 4.1. EXTRAIR LARGURA DO TERMINAL
int getLarguraTerminal();
// // 4.2. CENTRALIZAR TEXTO
void centralizarTexto(const string& texto);
// // 4.3. CABEÇALHO DO SISTEMA
void esteticaCabeçalhoSistema();

#endif // ESTETICA_H_INCLUDED
