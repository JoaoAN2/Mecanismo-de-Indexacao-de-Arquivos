# 📚 Sistema de Indexação de Arquivos

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

Aplicação de linha de comando que simula um mecanismo de busca para documentos de texto utilizando **índice invertido**.

## 🎓 Contexto Acadêmico

Projeto desenvolvido para a disciplina de **Estruturas de Dados II**, ministrada pelo **Prof. Dr. Juliano Henrique Foleiss** na **Universidade Tecnológica Federal do Paraná (UTFPR)**.

Os principais objetivos pedagógicos incluem:

- Implementação de estruturas de dados complexas (`unordered_map` e `sets`).
- **Serialização Binária Customizada** e I/O de baixo nível.
- Gerenciamento de memória e otimização de performance.

## 🎯 Características

- ✅ **Índice Invertido** para busca eficiente em documentos
- ✅ **Processamento de texto** com normalização e remoção de stop words
- ✅ **Serialização binária** para persistência do índice
- ✅ **Busca multi-palavra** com operador AND implícito
- ✅ **Interface CLI** simples e intuitiva
- ✅ **Alta performance**: ~4μs por busca em corpus de 10 romances

## 🚀 Quick Start

```bash
# Compilar
make

# Indexar diretório com arquivos .txt
./indice construir textos/

# Realizar busca
./indice buscar amor
./indice buscar capitu bentinho
```

## 📋 Requisitos

- Compilador C++ com suporte a **C++17** ou superior
- Make
- Sistema operacional: Linux/Unix/MacOS

## 🏗️ Arquitetura

O sistema é composto por 6 classes principais:

```
┌─────────────────┐
│     main.cpp    │  ← Interface CLI
└────────┬────────┘
         │
    ┌────┴──────────────────────┐
    │                           │
┌───▼──────┐            ┌───────▼────────┐
│ Indexer  │            │ QueryProcessor │
└───┬──────┘            └───────┬────────┘
    │                           │
┌───▼──────────┐         ┌──────▼─────┐
│TextProcessor │         │   Index    │
└──────────────┘         └──────┬─────┘
                                │
                         ┌──────▼─────┐
                         │ Serializer │
                         └────────────┘
```

### Componentes

- **Index**: Estrutura de índice invertido (`unordered_map<string, set<int>>`)
- **TextProcessor**: Normalização de texto e filtragem de stop words
- **Indexer**: Leitura de arquivos e construção do índice
- **QueryProcessor**: Processamento de consultas com interseção de conjuntos
- **Serializer**: Persistência binária do índice
- **StringTools**: Utilitários para manipulação de strings

## 📁 Estrutura do Projeto

```
indexacaoArquivos/
├── src/
│   ├── Index.cpp
│   ├── TextProcessor.cpp
│   ├── Indexer.cpp
│   ├── QueryProcessor.cpp
│   ├── Serializer.cpp
│   ├── main.cpp
│   └── helpers/
│       └── StringTools.cpp
├── include/
│   ├── Index.hpp
│   ├── TextProcessor.hpp
│   ├── Indexer.hpp
│   ├── QueryProcessor.hpp
│   ├── Serializer.hpp
│   └── helpers/
│       └── StringTools.hpp
├── stopwords.txt
├── Makefile
├── LEIAME.txt
└── README.md
```

## 🔧 Compilação

```bash
# Compilar programa principal
make

# Limpar binários
make clean
```

## 💡 Uso

### Construir Índice

```bash
./indice construir <diretório>
```

Exemplo:

```bash
./indice construir textos/
```

Este comando:

1. Lê todos os arquivos `.txt` do diretório
2. Processa o texto (lowercase, remove pontuação, filtra stop words)
3. Constrói o índice invertido
4. Salva em `indice.dat`

### Realizar Busca

```bash
./indice buscar <palavra1> [palavra2] [palavra3] ...
```

Exemplos:

```bash
# Busca simples
./indice buscar amor

# Busca com múltiplas palavras (AND implícito)
./indice buscar capitu bentinho
```

A busca com múltiplas palavras retorna apenas documentos que contêm **todas** as palavras.

## 📊 Performance

Resultados com corpus de 10 romances de Machado de Assis:

| Operação     | Tempo  |
| ------------ | ------ |
| Indexação    | 107 ms |
| Salvamento   | 7 ms   |
| Carregamento | 20 ms  |
| Busca        | 4 μs   |

**Tamanho do índice**: 952 KB

### Exemplo de Teste Real

```cpp
// Busca por personagens em Dom Casmurro
indexer.construir("testes");
auto resultados = qp.buscar("capitu bentinho");
// Resultado: [machado/romance/domCasmurro.txt]
```

## 🔍 Detalhes Técnicos

### Índice Invertido

Três estruturas principais:

```cpp
unordered_map<string, set<int>> indiceInvertido;  // palavra → IDs
unordered_map<int, string> idParaArquivo;          // ID → arquivo
unordered_map<string, int> arquivoParaID;          // arquivo → ID
```

### Pipeline de Processamento

```
Texto bruto → Lowercase → Remove pontuação → Tokeniza → Remove stop words → Índice
```

### Serialização

Formato binário customizado:

```
[tamanho][chave][valor][tamanho][chave][valor]...
```

Para mapas com sets:

```
[tamanho_mapa][chave][tamanho_set][elem1][elem2]...[chave][tamanho_set]...
```

## 🎓 Contexto Acadêmico

Projeto desenvolvido para a disciplina de **Estruturas de Dados II** com os seguintes objetivos pedagógicos:

- Implementação de estruturas de dados complexas (índice invertido)
- Uso de containers da STL (`unordered_map`, `set`)
- Gerenciamento manual de memória em C++
- Serialização binária customizada
- Desenvolvimento de interface CLI
- Testes e validação com dados reais

## 📝 Exemplo Completo

```bash
# 1. Compilar
make

# 2. Criar corpus de teste
mkdir textos
echo "o amor é eterno enquanto dura" > textos/doc1.txt
echo "a vida é bela" > textos/doc2.txt
echo "o amor e a vida são importantes" > textos/doc3.txt

# 3. Indexar
./indice construir textos/
# Output: Índice construído e salvo com sucesso!

# 4. Buscar palavra única
./indice buscar amor
# Output:
# Documentos encontrados (2):
#   - textos/doc1.txt
#   - textos/doc3.txt

# 5. Buscar múltiplas palavras (interseção)
./indice buscar amor vida
# Output:
# Documentos encontrados (1):
#   - textos/doc3.txt
```

## 📄 Licença

Este projeto é fornecido como material educacional. Sinta-se livre para usar e modificar para fins acadêmicos.

## 👥 Autor

Feito com ❤️ por [João Augusto do Nascimento](https://github.com/joaoan2)

---

⭐ **Se este projeto foi útil para você, considere dar uma estrela!**
