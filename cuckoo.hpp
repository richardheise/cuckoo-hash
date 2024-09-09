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

// Literalmente ninguém deixa de fazer isso
using namespace std;

/*********************************************************************
 * Estruturas do código
*********************************************************************/

// Controle de inclusão
#ifndef __CUCKOO__
#define __CUCKOO__

// Códigos de retorno de erro
#define MEM_ERROR -1

// Estados possíveis das entradas das tabelas
enum EntryStatus {
    FILLED,    // Espaço preenchido
    EMPTY,    // Entrada vazia
    EXCLUDED   // Entrada excluída
};

// Definições das macros para funções hash
#define HASH1(k, m) ((k) % (m))
#define HASH2(k, m) (static_cast<int>(floor((m) * (fmod((k) * 0.9, 1.0)))))

// Uma entrada na tabela possui valor e estado (vazio, preenchido, excluído)
struct entry {
    int value;
    int tag;
};

// Nossa hash table tem duas tabelas T1 e T2, além de um tamanho compartilhado
struct hash_table {
    int size;
    entry* T1;
    entry* T2;
};


/*********************************************************************
 * Depuração
*********************************************************************/

// Função que transforma um estado em string, usada para debug
const char* tag_to_string(int tag);

// Função para printar a tabela hash
// Faz uma tupla de posição, valor e estado
void print_hash_table_debug(const hash_table* h);

/*********************************************************************
 * Funções de hash
*********************************************************************/

// Printa a tabela hash no formato exigido pelo trabalho (valor, tabela, posição)
void print_hash_table(const hash_table* h);

// Inicializa uma estrutura hash
int init_hash(hash_table* h, uint size);

// Libera memória e de zera o tamanho de uma estrutura hash
void destroy_hash(hash_table* h);

// Função de busca do elemento value na tabela hash
int lookup(hash_table* h, int value);

// Função de inserção do elemento value na tabela hash
void insert(hash_table* h, int value);

// Função de exclusão do elemento value na tabela hash
void exclude(hash_table* h, int value);

#endif