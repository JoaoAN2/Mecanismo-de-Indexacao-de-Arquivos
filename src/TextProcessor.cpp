#include "TextProcessor.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

#include "helpers/StringTools.hpp"

using namespace std;

// Construtor
TextProcessor::TextProcessor() {
    carregarStopWords("stopwords.txt");
}

// Carrega stop words de um arquivo
void TextProcessor::carregarStopWords(const string& arquivo) {
    ifstream stopWordsFile(arquivo);
    StringTools st;

    if (!stopWordsFile.is_open()) {
        // Arquivo não existe - pode ignorar ou lançar erro
        return;
    }

    string linha;

    while (getline(stopWordsFile, linha)) {
        linha = st.trim(linha);

        if (!linha.empty()) {
            this->stopWords.insert(linha);
        }
    }

    stopWordsFile.close();
}

// Verifica se uma palavra é stop word
bool TextProcessor::isStopWord(const string& palavra) const {
    return this->stopWords.find(palavra) != this->stopWords.end();
}

// Processa texto e retorna vetor de palavras normalizadas
vector<string> TextProcessor::processar(const string& texto) const {
    string pontos = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    string textoProcessado = texto;
    string palavra = "";
    vector<string> resultado;

    for (char& c : textoProcessado) {
        // 1. Converter para minúsculas
        c = tolower(c);

        // 2. Remover pontuações
        if (pontos.find(c) != string::npos) {
            c = ' ';
        }

        // 3. Tokenizar por espaços
        if (c != ' ') {
            palavra += c;
        } else {
            // 4. Remover stop words
            if (!palavra.empty() && !isStopWord(palavra)) {
                resultado.push_back(palavra);
            }

            palavra = "";
        }
    }

    // Validando última palavra
    if (!palavra.empty() && !isStopWord(palavra)) {
        resultado.push_back(palavra);
    }

    return resultado;
}
