#include "QueryProcessor.hpp"

#include <sstream>

#include "helpers/StringTools.hpp"

// Construtor
QueryProcessor::QueryProcessor(Index& idx) : index(idx) {
    // Inicialização na lista de inicialização
}

// Faz interseção de dois conjuntos (implementação manual)
set<int> QueryProcessor::intersecao(const set<int>& a, const set<int>& b) const {
    set<int> res;

    // 1. Iterar pelo menor conjunto
    const set<int>* menor = &a;
    const set<int>* maior = &b;

    if (a.size() > b.size()) {
        menor = &b;
        maior = &a;
    }

    for (int valorA : *menor) {
        // 2. Verificar se elemento existe no outro conjunto
        bool existe = maior->find(valorA) != maior->end();

        // 3. Adicionar ao resultado se existir em ambos
        if (existe)
            res.insert(valorA);
    }

    return res;
}

// Busca por termos
set<string> QueryProcessor::buscar(const string& consulta) const {
    StringTools st;
    set<string> arquivos;

    // 1. Dividir consulta em palavras (tokens)
    vector<string> palavras = st.split(consulta, " ");

    // 2. Para cada palavra, buscar set de IDs no índice
    if (palavras.size() < 1) {
        return arquivos;
    }

    set<int> res = this->index.getArquivosPorPalavra(st.toLowerCase(palavras[0]));

    // 3. Se múltiplas palavras, fazer interseção dos sets
    for (size_t i = 1; i < palavras.size(); i++) {
        string minuscula = st.toLowerCase(palavras[i]);
        set<int> novoSet = this->index.getArquivosPorPalavra(minuscula);
        res = this->intersecao(res, novoSet);
    }

    // 4. Converter IDs para nomes de arquivos
    for (size_t arquivoId : res) {
        arquivos.insert(this->index.getNomeArquivoPorId(arquivoId));
    }

    // 5. Retornar set de nomes de arquivos
    return arquivos;
}
