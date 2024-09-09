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
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm> 
#include <tuple>     

using namespace std;

#ifndef __CUCKOO__
#define __CUCKOO__

#define MEM_ERROR -1

enum EntryStatus {
    FILLED,    // Espaço preenchido
    EMPTY,    // Entrada válida
    EXCLUDED   // Entrada excluída
};

// Definições das macros para funções hash
#define HASH1(k, m) ((k) % (m))
#define HASH2(k, m) (static_cast<int>(floor((m) * (fmod((k) * 0.9, 1.0)))))

struct entry {
    int value;
    int tag;
};

struct hash_table {
    int size;
    entry* T1;
    entry* T2;
};

const char* tag_to_string(int tag) {
    switch (tag) {
        case FILLED: return "FILLED";
        case EMPTY: return "EMPTY";
        case EXCLUDED: return "EXCLUDED";
        default: return "UNKNOWN";
    }
}

void print_hash_table_debug(const hash_table* h) {
    cout << "Table T1:" << endl;
    for (int i = 0; i < h->size; ++i) {
        const entry& e = h->T1[i];
        cout << "Position " << i << ": "
                  << "Value = " << e.value << ", "
                  << "Status = " << tag_to_string(e.tag) << endl;
    }

    cout << "Table T2:" << endl;
    for (int i = 0; i < h->size; ++i) {
        const entry& e = h->T2[i];
        cout << "Position " << i << ": "
        << "Value = " << e.value << ", "
        << "Status = " << tag_to_string(e.tag) << endl;
    }
}

void print_hash_table(const hash_table* h) {
    vector<tuple<int, string, int>> entries;  // (valor, tabela, índice)

    // Adiciona entradas de T1
    for (int i = 0; i < h->size; ++i) {
        const entry& e = h->T1[i];
        if (e.tag == FILLED) {
            entries.emplace_back(e.value, "T1", i);
        }
    }

    // Adiciona entradas de T2
    for (int i = 0; i < h->size; ++i) {
        const entry& e = h->T2[i];
        if (e.tag == FILLED) {
            entries.emplace_back(e.value, "T2", i);
        }
    }

    // Ordena entradas pelo valor
    sort(entries.begin(), entries.end(), [](const tuple<int, string, int>& a, const tuple<int, string, int>& b) {
        return get<0>(a) < get<0>(b);
    });

    // Imprime entradas ordenadas
    for (const auto& entry : entries) {
        cout << get<0>(entry) << "," << get<1>(entry) << "," << get<2>(entry) << endl;
    }
}

int init_hash(hash_table* h, uint size);
void destroy_hash(hash_table* h);
int lookup(hash_table* h, int value);
void insert(hash_table* h, int value);
void exclude(hash_table* h, int value);

#endif