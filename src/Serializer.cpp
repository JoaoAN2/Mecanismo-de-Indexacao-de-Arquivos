#include "Serializer.hpp"

#include <fstream>

// Construtor
Serializer::Serializer() {}

// Sobrecarga para unordered_map<int, string>
void Serializer::escreverMapa(ofstream& arquivo, const unordered_map<int, string>& mapa) {
    size_t tamanho = mapa.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(size_t));

    for (const auto& par : mapa) {
        arquivo.write(reinterpret_cast<const char*>(&par.first), sizeof(int));
        escreverString(arquivo, par.second);
    }
}

// Sobrecarga para unordered_map<string, int>
void Serializer::escreverMapa(ofstream& arquivo, const unordered_map<string, int>& mapa) {
    size_t tamanho = mapa.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(size_t));

    for (const auto& par : mapa) {
        escreverString(arquivo, par.first);
        arquivo.write(reinterpret_cast<const char*>(&par.second), sizeof(int));
    }
}

// Sobrecarga para unordered_map<string, set<int>> (índice invertido)
void Serializer::escreverMapa(ofstream& arquivo, const unordered_map<string, set<int>>& mapa) {
    size_t tamanho = mapa.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(size_t));

    for (const auto& par : mapa) {
        // Escrever a palavra (chave)
        escreverString(arquivo, par.first);

        // Escrever o set de IDs
        size_t tamanhoSet = par.second.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoSet), sizeof(size_t));

        for (int id : par.second) {
            arquivo.write(reinterpret_cast<const char*>(&id), sizeof(int));
        }
    }
}

// Escreve uma string em formato binário
void Serializer::escreverString(ofstream& arquivo, const string& str) {
    // 1. Escrever tamanho da string
    const char* buffer = str.data();
    size_t tamanho = str.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(size_t));

    // 2. Escrever conteúdo da string
    arquivo.write(buffer, tamanho);
}

// Lê uma string em formato binário
string Serializer::lerString(ifstream& arquivo) {
    // 1. Ler tamanho da string
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));

    if (arquivo.fail()) {
        return "";
    }

    string buffer;
    buffer.resize(tamanho);

    // 2. Ler conteúdo da string
    arquivo.read(buffer.data(), tamanho);
    return buffer;
}

// Lê um mapa int->string
void Serializer::lerMapa(ifstream& arquivo, unordered_map<int, string>& mapa) {
    // Ler tamanho do mapa
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(size_t));

    // Ler cada par (int, string)
    for (size_t i = 0; i < tamanho; i++) {
        int chave;
        arquivo.read(reinterpret_cast<char*>(&chave), sizeof(int));

        string valor = lerString(arquivo);

        mapa[chave] = valor;
    }
}

// Lê um mapa string->int
void Serializer::lerMapa(ifstream& arquivo, unordered_map<string, int>& mapa) {
    // Ler tamanho do mapa
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(size_t));

    // Ler cada par (string, int)
    for (size_t i = 0; i < tamanho; i++) {
        string chave = lerString(arquivo);

        int valor;
        arquivo.read(reinterpret_cast<char*>(&valor), sizeof(int));

        mapa[chave] = valor;
    }
}

// Lê um mapa string->set<int> (índice invertido)
void Serializer::lerMapa(ifstream& arquivo, unordered_map<string, set<int>>& mapa) {
    // Ler tamanho do mapa
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(size_t));

    // Ler cada par (string, set<int>)
    for (size_t i = 0; i < tamanho; i++) {
        // Ler a palavra (chave)
        string palavra = lerString(arquivo);

        // Ler o set de IDs
        size_t tamanhoSet = 0;
        arquivo.read(reinterpret_cast<char*>(&tamanhoSet), sizeof(size_t));

        set<int> ids;
        for (size_t j = 0; j < tamanhoSet; j++) {
            int id;
            arquivo.read(reinterpret_cast<char*>(&id), sizeof(int));
            ids.insert(id);
        }

        mapa[palavra] = ids;
    }
}

// Salva o índice em arquivo binário
void Serializer::salvar(const Index& index, const string& nomeArquivo) {
    // 1. Abrir arquivo em modo binário
    ofstream arquivo(nomeArquivo, ios::out | ios::binary);
    if (arquivo.is_open()) {
        // 2. Salvar mapeamento ID <-> nome arquivo
        const unordered_map<int, string>* idParaArquivo = index.getIdParaArquivo();
        escreverMapa(arquivo, *idParaArquivo);

        // 3. Salvar nome <-> ID
        const unordered_map<string, int>* arquivoParaID = index.getArquivoParaID();
        escreverMapa(arquivo, *arquivoParaID);

        // 4. Salvar índice invertido (palavra -> set de IDs)
        const unordered_map<string, set<int>>* indiceInvertido = index.getIndiceInvertido();
        escreverMapa(arquivo, *indiceInvertido);

        // 5. Fechar arquivo
        arquivo.close();
    }
}

// Carrega o índice de arquivo binário
Index Serializer::carregar(const string& nomeArquivo) {
    Index index;

    // 1. Abrir arquivo em modo binário
    ifstream arquivo(nomeArquivo, ios::in | ios::binary);

    if (arquivo.is_open()) {
        // 2. Ler mapeamento ID <-> nome arquivo
        unordered_map<int, string> idParaArquivo;
        lerMapa(arquivo, idParaArquivo);

        // 3. Ler nome <-> ID
        unordered_map<string, int> arquivoParaId;
        lerMapa(arquivo, arquivoParaId);

        // 4. Ler índice invertido
        unordered_map<string, set<int>> indiceInvertido;
        lerMapa(arquivo, indiceInvertido);

        // 5. Reconstruir objeto Index
        index.setIdParaArquivo(idParaArquivo);
        index.setArquivoParaID(arquivoParaId);
        index.setIndiceInvertido(indiceInvertido);

        // 6. Fechar arquivo
        arquivo.close();
    }

    return index;
}
