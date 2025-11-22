#include "Indexer.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

// Construtor
Indexer::Indexer() {}

// Processa um único arquivo
void Indexer::processarArquivo(const string& caminhoArquivo, Index& index) {
    // 1. Abrir e ler arquivo
    ifstream meuArquivo(caminhoArquivo);

    if (!meuArquivo.is_open()) {
        // Não consegui abrir o arquivo
        return;
    }

    // 2. Processar conteúdo com textProcessor
    string linha;
    while (getline(meuArquivo, linha)) {
        vector<string> resultado = this->textProcessor.processar(linha);

        // 3. Adicionar palavras ao índice
        for (string palavra : resultado) {
            index.adicionar(palavra, caminhoArquivo);
        }
    }

    meuArquivo.close();
}

// Constrói o índice a partir de um diretório
Index Indexer::construir(const string& diretorio) {
    // 1. Criar objeto Index
    Index index = Index();

    // 2. Listar todos arquivos .txt no diretório
    filesystem::path caminho(diretorio);

    if (filesystem::exists(caminho) && filesystem::is_directory(caminho)) {
        for (const auto& arquivo : filesystem::directory_iterator(caminho)) {
            if (arquivo.is_regular_file() && arquivo.path().extension() == ".txt") {
                // 3. Para cada arquivo, chamar processarArquivo()
                processarArquivo(arquivo.path().string(), index);
            }
        }
    }

    // 4. Retornar índice populado
    return index;
}
