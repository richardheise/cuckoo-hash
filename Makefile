# Makefile

# Variáveis
CXX = g++
CXXFLAGS = -Wall
TARGET = myht
OBJECTS = main.o cuckoo.o

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compilação de main.cpp
main.o: main.cpp cuckoo.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compilação de cuckoo.cpp
cuckoo.o: cuckoo.cpp cuckoo.hpp
	$(CXX) $(CXXFLAGS) -c cuckoo.cpp

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets
.PHONY: all clean
