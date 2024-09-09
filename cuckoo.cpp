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

/***********************************************************************/

int init_hash(hash_table* h, uint size) {
    h->size = size;
    h->T1 = new entry[h->size]; // aloca memória de tamanho size

    if (!h->T1) {
        cerr << "Couldn't allocate memory for T1." << endl; // erro se falhar a alocação
        exit(MEM_ERROR);
    }

    h->T2 = new entry[h->size];
    if (!h->T2) {
        cerr << "Couldn't allocate memory for T2." << endl; // erro se falhar a alocação
        exit(MEM_ERROR);
    }

    // Inicializa todas as entradas como vazias e valores como 0
    for (uint i = 0; i < size; i++) {
        h->T1[i].tag = EMPTY;
        h->T2[i].tag = EMPTY;
        h->T1->value = 0;
        h->T2->value = 0;
    }

    return 1;
}

/***********************************************************************/

void destroy_hash(hash_table* h) {
    h->size = 0; // zera o tamanho
    
    // Desaloca memória e nulifica ponteiro
    delete[] h->T1;
    h->T1 = nullptr;

    delete[] h->T2;
    h->T2 = nullptr;
}

/***********************************************************************/

int lookup(hash_table* h, int value) {
    int index = HASH1(value, h->size);

    // Se a posição não está preenchida, então ela está deletada
    // ou vazia, de toda forma, o valor não está na tabela.
    if (h->T1[index].tag == EMPTY) return -1;  

    // Se o valor não está em T1 e o valor não foi excluído...
    if (!(h->T1[index].value == value) && h->T1[index].tag != EXCLUDED) {
        
        // ele está em T2
        index = HASH2(value, h->size);
    }

    // Retorna o índice
    return index;
}

/***********************************************************************/

void insert(hash_table* h, int value) {

    int index = HASH1(value, h->size);

    if (h->T1[index].tag == FILLED && h->T1[index].value != value) {
        // Move o valor existente de T1 para T2 usando a função hash2
        int new_index = HASH2(h->T1[index].value, h->size);
        h->T2[new_index].value = h->T1[index].value;
        h->T2[new_index].tag = FILLED;
    }

    // Insere o novo valor em T1
    h->T1[index].value = value;
    h->T1[index].tag = FILLED;
}

/***********************************************************************/

void exclude(hash_table* h, int value) {
    int index = lookup(h, value);  // Usa lookup para encontrar o valor

    if (index == -1) {
        //cerr << "Value " << value << " not found, cannot exclude." << endl;
        return;  // Valor não encontrado, não faz nada
    }

    // Verifica se está em T1 ou T2 e marca como excluído
    if (index == HASH2(value, h->size) && h->T2[index].value == value) {
        h->T2[index].tag = EXCLUDED;
    } else if (index == HASH1(value, h->size) && h->T1[index].value == value) {
        h->T1[index].tag = EXCLUDED;
    }
}

/***********************************************************************/

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

/***********************************************************************/

const char* tag_to_string(int tag) {
    switch (tag) {
        case FILLED: return "FILLED";
        case EMPTY: return "EMPTY";
        case EXCLUDED: return "EXCLUDED";
        default: return "UNKNOWN";
    }
}

/***********************************************************************/

// Função para printar a tabela hash
// Faz uma tupla de posição, valor e estado
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