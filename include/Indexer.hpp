#ifndef INDEXER_H
#define INDEXER_H

#include <filesystem>
#include <string>

#include "Index.hpp"
#include "TextProcessor.hpp"

using namespace std;

/**
 * Classe Indexer - Constrói o índice invertido
 *
 * Responsabilidades:
 * - Varrer diretório de arquivos
 * - Ler arquivos .txt
 * - Processar texto usando TextProcessor
 * - Popular objeto Index
 */
class Indexer {
   private:
    // Composição: Indexer possui um TextProcessor
    TextProcessor textProcessor;

    /**
     * Processa um único arquivo
     * @param caminhoArquivo Caminho completo do arquivo
     * @param index Referência ao índice a ser populado
     */
    void processarArquivo(const string& caminhoArquivo, Index& index);

   public:
    // Construtor
    Indexer();

    /**
     * Constrói o índice a partir de um diretório
     * @param diretorio Caminho do diretório contendo arquivos .txt
     * @return Objeto Index completamente populado
     */
    Index construir(const filesystem::path diretorio);
};

#endif  // INDEXER_H
