##### Author: Richard Fernando Heise Ferreira
##### Registration Number: 201900121214
##### Date: 09/2024
##### Institution: Federal University of Paraná
##### Course: Graduate Program in Computer Security
##### Reason: Assignment for the Database Management System Performance Course

# Cuckoo Hashing

The cuckoo hashing algorithm is a well-known hashing strategy used usually in popular commercial databases.
This repo is an example of a simple cuckoo hash without rehashing.

### Objective

Cuckoo Hashing is a hashing technique that efficiently resolves collisions, ensuring searches, insertions, and deletions in O(1) time. It uses two hash tables and two independent hash functions, relocating elements when a collision occurs, which avoids chaining or long probing. This offers a deterministic and space-efficient solution, ideal for applications requiring low latency and predictability.

The objective of this work is to implement cuckoo hashing in C/C++ without rehashing and to observe the behavior of the algorithm for some test cases, aiding in learning the hashing method.

### Hypothesis

It is possible to guarantee efficient collision resolution in a hash table and ensure O(1) time operations.

### Implementation

The program is divided into:

- `main.cpp`, which contains the function call and input processing, as well as the processing function itself.

- `cuckoo.hpp`, which contains the function headers used in the hash, as well as the structures and macros for the HASH functions.

- `cuckoo.cpp`, which contains the API implementations defined in `cuckoo.hpp`.

An entry in the table is defined as a value-state tuple.

- State describes whether the table cell is empty, deleted, or filled.

- Value is the actual value stored in the table.

The hash structure consists of two pointers, T1 and T2, for entries. These are dynamically allocated at the start of the program.

There is also a size variable that can be redefined using the `SIZE` variable, described via a `#define`.

When the program starts, `main` reads the input operation and calls the respective function for that operation.

- Insertion: a value is added to T1 if the position is empty or deleted. If it is filled, the value is searched in T2; if it does not exist there, it is added.

- Removal: the value is searched for in T1 and T2; if found, its position is marked as deleted.

- Search: returns the index of a value in the hash or returns -1.

### Experiments
Use 

```bash
./execTests.sh
```

To run every test in the tests/ dir. There reulsts are then write into results/ dir and a diff is made between each result and each input.

### Conclusion

The C++ implementation was sufficient to demonstrate the conflict resolution behavior and the O(1) runtime of operations, as well as the correctness of the hash table.
