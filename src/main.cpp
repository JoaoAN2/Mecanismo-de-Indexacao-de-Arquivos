#include <filesystem>
#include <iostream>
#include <string>

#include "Index.hpp"
#include "Indexer.hpp"
#include "QueryProcessor.hpp"
#include "Serializer.hpp"

using namespace std;
namespace fs = std::filesystem;

/**
 * Exibe instruções de uso do programa
 */
void exibirUso() {
    cout << "Uso:" << endl;
    cout << "  indice construir <caminho_do_diretorio>" << endl;
    cout << "  indice buscar <termo1> [termo2] ... [termoN]" << endl;
    cout << endl;
    cout << "Exemplos:" << endl;
    cout << "  indice construir ./documentos" << endl;
    cout << "  indice buscar gato" << endl;
    cout << "  indice buscar gato cachorro" << endl;
}

/**
 * Executa o comando de construção do índice
 */
int comandoConstruir(const string& caminho) {
    // 1. Verificar se diretório existe
    filesystem::path diretorio(caminho);

    if (!filesystem::exists(diretorio)) {
        cout << "Caminho não existe" << endl;
        return 1;
    }

    if (!fs::is_directory(diretorio)) {
        cout << "O caminho não é um diretório" << endl;
        return 2;
    }

    // 2. Criar objeto Indexer
    Indexer indexer;

    // 3. Construir índice
    Index index = indexer.construir(caminho);

    // 4. Criar objeto Serializer
    Serializer serializer;

    // 5. Salvar índice
    serializer.salvar(index, "index.dat");

    // 6. Exibir mensagem de sucesso
    cout << "Realizado o processo de construção do index com sucesso!" << endl;

    return 0;
}

/**
 * Executa o comando de busca
 */
int comandoBuscar(int argc, char* argv[]) {
    // 1. Verificar se index.dat existe
    filesystem::path arquivo("index.dat");

    if (!filesystem::exists(arquivo)) {
        cout << "Index não existe, tente indexar utilizando o comando: " << argv[0] << " construir caminho/do/diretorio" << endl;
        return 1;
    }

    if (!fs::is_regular_file(arquivo)) {
        cout << "Arquivo não identificado, tente indexar utilizando o comando: " << argv[0] << " construir caminho/do/diretorio" << endl;
        return 2;
    }

    // 2. Criar objeto Serializer
    Serializer serializer;

    // 3. Carregar índice
    Index index = serializer.carregar("index.dat");

    // 4. Montar string de consulta com todos os termos
    string query = "";
    for (int i = 2; i < argc; i++) {
        query += argv[i];
        query += ' ';
    }

    // 5. Criar QueryProcessor: QueryProcessor qp(index)
    QueryProcessor qp(index);

    // 6. Buscar
    set<string> resultados = qp.buscar(query);

    // 7. Exibir resultados ou mensagem "Nenhum documento encontrado"
    if (resultados.empty()) {
        cout << "Nenhum documento encontrado" << endl;
        return 3;
    }

    cout << "Documentos encontrados: " << endl;
    for (string resultado : resultados) {
        cout << resultado << " ";
    }

    cout << endl;
    return 0;
}

/**
 * Ponto de entrada do programa
 */
int main(int argc, char* argv[]) {
    // 1. Verificar número de argumentos
    if (argc < 2) {
        exibirUso();
        return 1;
    }

    // 2. Verificar primeiro argumento (comando)
    string comando = argv[1];
    int cod = 0;

    if (comando == "construir") {
        // 3. Se "construir": chamar comandoConstruir()
        cod = comandoConstruir(argv[2]);
    } else if (comando == "buscar") {
        // 4. Se "buscar": chamar comandoBuscar()
        comandoBuscar(argc, argv);
    } else {
        // 5. Caso contrário: exibir uso e retornar erro
        cout << "Comando inválido: " << comando << endl;
        exibirUso();
        return 1;
    }

    return cod;
}
