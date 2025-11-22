#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>

#include "Index.hpp"

using namespace std;

/**
 * Classe Serializer - Persiste e carrega o índice
 *
 * Responsabilidades:
 * - Salvar índice em formato binário
 * - Carregar índice de arquivo binário
 * - Garantir reconstrução exata do estado
 */
class Serializer {
   private:
    /**
     * Escreve uma string em formato binário
     * @param arquivo Stream de saída
     * @param str String a ser escrita
     */
    void escreverString(ofstream& arquivo, const string& str);

    /**
     * Escreve um mapa int->string em formato binário
     * @param arquivo Stream de saída
     * @param mapa Mapa a ser escrito
     */
    void escreverMapa(ofstream& arquivo, const unordered_map<int, string>& mapa);

    /**
     * Escreve um mapa string->int em formato binário
     * @param arquivo Stream de saída
     * @param mapa Mapa a ser escrito
     */
    void escreverMapa(ofstream& arquivo, const unordered_map<string, int>& mapa);

    /**
     * Escreve um mapa string->set<int> em formato binário (índice invertido)
     * @param arquivo Stream de saída
     * @param mapa Mapa a ser escrito
     */
    void escreverMapa(ofstream& arquivo, const unordered_map<string, set<int>>& mapa);

    /**
     * Lê uma string em formato binário
     * @param arquivo Stream de entrada
     * @return String lida
     */
    string lerString(ifstream& arquivo);

    /**
     * Lê um mapa int->string em formato binário
     * @param arquivo Stream de entrada
     * @param mapa Referência para o mapa de destino
     */
    void lerMapa(ifstream& arquivo, unordered_map<int, string>& mapa);

    /**
     * Lê um mapa string->int em formato binário
     * @param arquivo Stream de entrada
     * @param mapa Referência para o mapa de destino
     */
    void lerMapa(ifstream& arquivo, unordered_map<string, int>& mapa);

    /**
     * Lê um mapa string->set<int> em formato binário (índice invertido)
     * @param arquivo Stream de entrada
     * @param mapa Referência para o mapa de destino
     */
    void lerMapa(ifstream& arquivo, unordered_map<string, set<int>>& mapa);

   public:
    // Construtor
    Serializer();

    /**
     * Salva o índice em arquivo binário
     * @param index Índice a ser salvo
     * @param nomeArquivo Nome do arquivo (ex: "index.dat")
     */
    void salvar(const Index& index, const string& nomeArquivo);

    /**
     * Carrega o índice de arquivo binário
     * @param nomeArquivo Nome do arquivo (ex: "index.dat")
     * @return Objeto Index reconstruído
     */
    Index carregar(const string& nomeArquivo);
};

#endif  // SERIALIZER_H
