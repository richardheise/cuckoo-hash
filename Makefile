# Makefile

# Variáveis
CXX = g++
CXXFLAGS = -Wall
TARGET = cuckoo
OBJECTS = cuckoo.o

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compilação dos arquivos .cpp
cuckoo.o: cuckoo.cpp cuckoo.hpp
	$(CXX) $(CXXFLAGS) -c cuckoo.cpp

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets
.PHONY: all clean