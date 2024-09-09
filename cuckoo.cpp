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

int init_hash(hash_table* h, uint size) {
    h->size = size;
    h->T1 = new entry[h->size];

    if (!h->T1) {
        cerr << "Couldn't allocate memory for T1." << endl;
        exit(MEM_ERROR);
    }

    h->T2 = new entry[h->size];
    if (!h->T2) {
        cerr << "Couldn't allocate memory for T2." << endl;
        exit(MEM_ERROR);
    }

    for (uint i = 0; i < size; i++) {
        h->T1[i].tag = EMPTY;
        h->T2[i].tag = EMPTY;
        h->T1->value = 0;
        h->T2->value = 0;
    }

    return 1;
}

void destroy_hash(hash_table* h) {
    h->size = 0;

    delete[] h->T1;
    h->T1 = nullptr;

    delete[] h->T2;
    h->T2 = nullptr;
}

int lookup(hash_table* h, int value) {
    int index = HASH1(value, h->size);

    if (!h->T1[index].tag == FILLED) return -1;

    if (!(h->T1[index].value == value)) {
        index = HASH2(value, h->size);
    }
    return index;
}

void insert(hash_table* h, int value) {

    int index = HASH1(value, h->size);

    if (h->T1[index].tag == FILLED) {
        // Move o valor existente de T1 para T2 usando a função hash2
        int new_index = HASH2(h->T1[index].value, h->size);
        h->T2[new_index].value = h->T1[index].value;
        h->T2[new_index].tag = FILLED;
    }

    // Insere o novo valor em T1
    h->T1[index].value = value;
    h->T1[index].tag = FILLED;
}

void exclude(hash_table* h, int value) {
    int index = lookup(h, value);  // Usa lookup para encontrar o valor

    if (index == -1) {
        cout << "Value not found, cannot exclude." << endl;
        return;  // Valor não encontrado, não faz nada
    }

    // Verifica se está em T1 ou T2 e marca como excluído
    if (index == HASH1(value, h->size) && h->T1[index].value == value) {
        h->T1[index].tag = EXCLUDED;
    } else if (index == HASH2(value, h->size) && h->T2[index].value == value) {
        h->T2[index].tag = EXCLUDED;
    }
}

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