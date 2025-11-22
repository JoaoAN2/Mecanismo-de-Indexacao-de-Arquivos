#include "helpers/StringTools.hpp"

#include <string>
#include <vector>

using namespace std;

// Remover espaços, tabulações e quebra de linha
string StringTools::trim(const string& str) {
    // Encontrar primeiro caractere não-espaço
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == string::npos)
        return "";  // String só tem espaços

    // Encontrar último caractere não-espaço
    size_t fim = str.find_last_not_of(" \t\r\n");

    return str.substr(inicio, fim - inicio + 1);
}

vector<string> StringTools::split(const string& str, const string& splitter) {
    vector<string> resultado;
    if (splitter.empty()) {
        resultado.push_back(str);
        return resultado;
    }

    size_t start = 0;
    size_t pos = 0;
    while ((pos = str.find(splitter, start)) != string::npos) {
        string token = str.substr(start, pos - start);
        if (!token.empty()) {  // Só adiciona se não for vazio
            resultado.emplace_back(token);
        }
        start = pos + splitter.length();
    }

    // Adicionar o último token (apenas se não for vazio)
    string ultimo = str.substr(start);
    if (!ultimo.empty()) {
        resultado.emplace_back(ultimo);
    }

    return resultado;
}

string StringTools::toLowerCase(const string& str) {
    string resultado = str;
    for (char& c : resultado) {
        c = tolower(c);
    }
    return resultado;
}
