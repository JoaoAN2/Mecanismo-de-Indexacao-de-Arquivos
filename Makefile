# Makefile para o projeto de Indexação de Arquivos
# Algoritmos e Estruturas de Dados II

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Nome do executável
TARGET = indice

# Encontrar todos os arquivos .cpp no diretório src (incluindo subdiretórios)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp' ! -name 'teste*.cpp')

# Gerar lista de objetos (.o) mantendo estrutura de diretórios
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Regra padrão (all)
all: $(TARGET)

# Criar o executável linkando todos os objetos
$(TARGET): $(OBJECTS)
	@echo "Linkando $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Compilação concluída com sucesso!"

# Compilar cada arquivo .cpp em um .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretório obj se não existir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Limpar arquivos gerados
clean:
	@echo "Removendo arquivos gerados..."
	rm -rf $(OBJ_DIR) $(TARGET) index.dat
	@echo "Limpeza concluída!"

# Limpar apenas os objetos (mantém o executável)
clean-obj:
	@echo "Removendo objetos..."
	rm -rf $(OBJ_DIR)

# Recompilar tudo do zero
rebuild: clean all

# Executar o programa (modo construir)
run-construir:
	./$(TARGET) construir .

# Executar o programa (modo buscar - exemplo)
run-buscar:
	./$(TARGET) buscar exemplo
	
# Exibir informações de debug
debug:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"

# Indicar que estes alvos não são arquivos
.PHONY: all clean clean-obj rebuild run-construir run-buscar test debug
