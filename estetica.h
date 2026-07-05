// 1. Inicialização da inclusão do header
#ifndef ESTETICA_H_INCLUDED
#define ESTETICA_H_INCLUDED

// 2. Incluir bibliotecas existentes
#include <string>
#include <cstddef> // Para size_t

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
// // 4.2. PEGAR TAMANHO REAL DO TEXTO
size_t tamanhoReal(const std::string& texto);
// // 4.3. CENTRALIZAR TEXTO
void centralizarTexto(const std::string& texto);
// // 4.4. CABEÇALHO DO SISTEMA
void esteticaCabeçalhoSistema();
// // 4.5. LIMPAR BUFFERS
void limparBufferEntrada();

#endif // ESTETICA_H_INCLUDED
