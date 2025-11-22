#ifndef INDEX_H
#define INDEX_H

#include <set>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * Classe Index - Gerencia o índice invertido
 *
 * Responsabilidades:
 * - Manter índice invertido (palavra -> conjunto de IDs)
 * - Gerenciar mapeamento de documentos (ID <-> nome arquivo)
 */
class Index {
   private:
    // Índice invertido: palavra -> conjunto de IDs de documentos
    unordered_map<string, set<int>>* indiceInvertido;

    // Mapeamento de ID para nome de arquivo
    unordered_map<int, string>* idParaArquivo;

    // Mapeamento de nome de arquivo para ID
    unordered_map<string, int>* arquivoParaID;

    // Contador para gerar IDs únicos
    int proximoID;

   public:
    // Construtor
    Index();

    // Destrutor
    ~Index();

    // Copy constructor
    Index(const Index& other);

    // Copy assignment operator
    Index& operator=(const Index& other);

    /**
     * Adiciona uma palavra ao índice, associando-a ao arquivo
     * @param palavra Palavra a ser indexada
     * @param nome_arquivo Nome do arquivo onde a palavra aparece
     */
    void adicionar(const string& palavra, const string& nome_arquivo);

    /**
     * Retorna conjunto de IDs dos documentos que contêm a palavra
     * @param palavra Palavra a ser buscada
     * @return Set com IDs dos documentos
     */
    set<int> getArquivosPorPalavra(const string& palavra) const;

    /**
     * Converte ID numérico para nome do arquivo
     * @param id ID do documento
     * @return Nome do arquivo
     */
    string getNomeArquivoPorId(int id) const;

    // Métodos auxiliares para serialização
    const unordered_map<string, set<int>>* getIndiceInvertido() const;
    const unordered_map<int, string>* getIdParaArquivo() const;
    const unordered_map<string, int>* getArquivoParaID() const;

    void setIndiceInvertido(const unordered_map<string, set<int>>& indice);
    void setIdParaArquivo(const unordered_map<int, string>& mapa);
    void setArquivoParaID(const unordered_map<string, int>& mapa);
};

#endif  // INDEX_H
