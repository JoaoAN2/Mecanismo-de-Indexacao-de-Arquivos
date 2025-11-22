#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <set>
#include <string>
#include <vector>

#include "Index.hpp"

using namespace std;

/**
 * Classe QueryProcessor - Processa consultas de busca
 *
 * Responsabilidades:
 * - Buscar por palavra única
 * - Buscar por múltiplas palavras (AND)
 * - Implementar interseção manual de conjuntos
 */
class QueryProcessor {
   private:
    // Agregação: usa referência a um Index existente
    Index& index;

    /**
     * Faz interseção de dois conjuntos de IDs (implementação manual)
     * @param a Primeiro conjunto
     * @param b Segundo conjunto
     * @return Conjunto com elementos presentes em ambos
     */
    set<int> intersecao(const set<int>& a, const set<int>& b) const;

   public:
    /**
     * Construtor
     * @param idx Referência ao índice a ser usado nas buscas
     */
    QueryProcessor(Index& idx);

    /**
     * Busca por termos (uma ou múltiplas palavras)
     * @param consulta String com termos separados por espaço
     * @return Set com nomes dos arquivos que contêm os termos
     */
    set<string> buscar(const string& consulta) const;
};

#endif  // QUERYPROCESSOR_H
