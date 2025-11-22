#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Classe TextProcessor - Processa e normaliza texto
 *
 * Responsabilidades:
 * - Converter texto para minúsculas
 * - Remover pontuações
 * - Tokenizar (quebrar em palavras)
 * - Remover stop words
 */
class TextProcessor {
   private:
    // Conjunto de stop words
    unordered_set<string> stopWords;

    /**
     * Carrega stop words de um arquivo
     * @param arquivo Caminho do arquivo stopwords.txt
     */
    void carregarStopWords(const string& arquivo);

    /**
     * Verifica se uma palavra é stop word
     * @param palavra Palavra a verificar
     * @return true se é stop word
     */
    bool isStopWord(const string& palavra) const;

   public:
    // Construtor
    TextProcessor();

    /**
     * Processa texto e retorna vetor de palavras normalizadas
     * @param texto Texto bruto a ser processado
     * @return Vector com palavras normalizadas (tokens)
     */
    vector<string> processar(const string& texto) const;
};

#endif  // TEXTPROCESSOR_H
