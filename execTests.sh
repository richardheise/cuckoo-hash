#!/bin/bash

# Diretórios de entrada, saída e resultados
TEST_DIR="tests"
RESULT_DIR="results"

# Executa o make
echo "Compiling with make..."
make

# Verifica se o make foi bem-sucedido
if [ $? -ne 0 ]; then
    echo "Make failed. Exiting."
    exit 1
fi

# Cria o diretório de resultados se não existir
mkdir -p $RESULT_DIR

# Itera pelos arquivos de entrada (teste*.in)
for input_file in $TEST_DIR/teste*.in; do
    # Pega o nome base do arquivo (ex: teste1, teste2)
    base_name=$(basename $input_file .in)
    
    # Executa o programa compilado usando o arquivo de entrada e salva no diretório results
    ./myht < $input_file > $RESULT_DIR/$base_name.res

    # Compara o resultado gerado com o esperado usando diff
    diff $TEST_DIR/$base_name.out $RESULT_DIR/$base_name.res > /dev/null
    if [ $? -eq 0 ]; then
        echo "$base_name: OK"
    else
        echo "$base_name: Mismatch"
        diff $TEST_DIR/$base_name.out $RESULT_DIR/$base_name.res
    fi
done
