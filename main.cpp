/***********************************************************************
*
* Autor: Richard Fernando Heise Ferreira
* Matrícula: 201900121214
* Data: 09/2024
* Instituição: Universidade Federal do Paraná
* Curso: Ciência da Computação
* Motivo: Trabalho da Disciplina de Desempenho de SGBD
*
************************************************************************/
#include "cuckoo.hpp"

#define SIZE 11

void process_commands(hash_table* h) {
    char operation;
    int value;

    while (scanf(" %c %d", &operation, &value) == 2) {
        switch (operation) {
            case 'i':  // Inserir
                insert(h, value);
                break;
            case 'r':  // Remover
                exclude(h, value);
                break;
            case 'l':  // Buscar
                int output = lookup(h, value);

                if (output == -1) {
                    cerr << "Value not found." << endl;
                }
                break;
        }
    }
    print_hash_table(h);
}

int main() {
    hash_table cuckoo;
    
    init_hash(&cuckoo, SIZE);

    process_commands(&cuckoo);

    destroy_hash(&cuckoo);

    return 0;
}