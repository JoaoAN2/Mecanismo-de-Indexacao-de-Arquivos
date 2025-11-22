#include "Index.hpp"

#include <set>
#include <unordered_map>

// Construtor
Index::Index() {
    this->indiceInvertido = new unordered_map<string, set<int>>();
    this->idParaArquivo = new unordered_map<int, string>();
    this->arquivoParaID = new unordered_map<string, int>();
    this->proximoID = 1;
}

// Destrutor
Index::~Index() {
    delete this->indiceInvertido;
    delete this->idParaArquivo;
    delete this->arquivoParaID;
}

// Copy constructor
Index::Index(const Index& other) {
    this->indiceInvertido = new unordered_map<string, set<int>>(*other.indiceInvertido);
    this->idParaArquivo = new unordered_map<int, string>(*other.idParaArquivo);
    this->arquivoParaID = new unordered_map<string, int>(*other.arquivoParaID);
    this->proximoID = other.proximoID;
}

// Copy assignment operator
Index& Index::operator=(const Index& other) {
    if (this != &other) {
        delete this->indiceInvertido;
        delete this->idParaArquivo;
        delete this->arquivoParaID;

        this->indiceInvertido = new unordered_map<string, set<int>>(*other.indiceInvertido);
        this->idParaArquivo = new unordered_map<int, string>(*other.idParaArquivo);
        this->arquivoParaID = new unordered_map<string, int>(*other.arquivoParaID);
        this->proximoID = other.proximoID;
    }
    return *this;
}

// Adiciona uma palavra ao índice
void Index::adicionar(const string& palavra, const string& nome_arquivo) {
    int idArquivo;

    auto it = this->arquivoParaID->find(nome_arquivo);

    if (it != this->arquivoParaID->end()) {
        idArquivo = it->second;
    } else {
        idArquivo = this->proximoID++;
        this->arquivoParaID->insert({nome_arquivo, idArquivo});
        this->idParaArquivo->insert({idArquivo, nome_arquivo});
    }

    (*this->indiceInvertido)[palavra].insert(idArquivo);
}

// Retorna conjunto de IDs dos documentos que contêm a palavra
set<int> Index::getArquivosPorPalavra(const string& palavra) const {
    auto it = this->indiceInvertido->find(palavra);

    if (it != this->indiceInvertido->end()) {
        return it->second;  // Retorna o set de IDs
    }

    return set<int>();  // Palavra não encontrada: retorna set vazio
}

// Converte ID para nome do arquivo
string Index::getNomeArquivoPorId(int id) const {
    auto it = this->idParaArquivo->find(id);

    if (it != this->idParaArquivo->end()) {
        return it->second;  // Retorna o nome do arquivo
    }

    return "";  // ID não encontrado: retorna string vazia
}

// Getters para serialização
const unordered_map<string, set<int>>* Index::getIndiceInvertido() const {
    return indiceInvertido;
}

const unordered_map<int, string>* Index::getIdParaArquivo() const {
    return idParaArquivo;
}

const unordered_map<string, int>* Index::getArquivoParaID() const {
    return arquivoParaID;
}

// Setters para desserialização
void Index::setIndiceInvertido(const unordered_map<string, set<int>>& indice) {
    *this->indiceInvertido = indice;
}

void Index::setIdParaArquivo(const unordered_map<int, string>& mapa) {
    *this->idParaArquivo = mapa;
}

void Index::setArquivoParaID(const unordered_map<string, int>& mapa) {
    *this->arquivoParaID = mapa;
    this->proximoID = 1;
    for (const auto& par : mapa) {
        if (par.second >= this->proximoID) {
            this->proximoID = par.second + 1;
        }
    }
}
