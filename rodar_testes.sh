#!/bin/bash

# --- Configuração ---
# O programa que você quer testar. Passe o caminho dele como o primeiro argumento do script.
# Exemplo: ./executa_testes.sh ./meu_programa
if [ -z "$1" ]; then
    echo "Erro: Forneça o caminho para o seu executável como argumento."
    echo "Uso: $0 ./seu_programa"
    exit 1
fi
PROGRAMA_A_TESTAR=$1

# --- Cores para o terminal ---
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AMARELO='\033[1;33m'
CINZA='\033[0;90m'
SEM_COR='\033[0m' # Reseta a cor

# --- Loop Principal de Testes ---
for arquivo_entrada in $(ls test_input*.txt | sort -V 2>/dev/null); do
    num_teste=$(echo "$arquivo_entrada" | sed 's/test_input\([0-9]*\).txt/\1/')
    arquivo_saida_esperada="test_output${num_teste}.txt"

    if [ ! -f "$arquivo_saida_esperada" ]; then
        echo -e "${AMARELO}--- Teste ${num_teste} ---${SEM_COR}"
        echo -e "${AMARELO}Aviso: Teste pulado. Arquivo de saída esperada não encontrado: ${arquivo_saida_esperada}${SEM_COR}"
        echo ""
        continue
    fi

    echo "--- Teste ${num_teste} ---"

    saida_esperada=$(cat "$arquivo_saida_esperada")
    saida_programa=$($PROGRAMA_A_TESTAR < "$arquivo_entrada")

    # --- Verificação do Resultado com diff ---
    # Usamos a substituição de processo <() para tratar as variáveis como arquivos.
    # A flag '-u' cria uma saída unificada, fácil de ler.
    # Redirecionamos a saída do diff para /dev/null porque só nos importamos com o status de saída (0 ou 1) no 'if'.
    if diff -u --color=always <(echo -n "$saida_esperada") <(echo -n "$saida_programa") >/dev/null; then
        echo -e "Entrada: $(cat $arquivo_entrada)"
        echo -e "${VERDE}Resultado: OK ✔️${SEM_COR}"
    else
        echo -e "Entrada: $(cat $arquivo_entrada)"
        echo -e "${VERMELHO}Resultado: FALHOU ${SEM_COR}"
        echo ""
        echo "--- Detalhes da Diferença (diff) ---"

        # Agora executamos o diff novamente, mas desta vez mostramos a saída para o usuário.
        # Linhas que começam com '-' são da SAÍDA ESPERADA.
        # Linhas que começam com '+' são da SAÍDA DO SEU PROGRAMA.
        diferenca=$(diff -u --color=always <(echo -n "$saida_esperada") <(echo -n "$saida_programa"))
        echo -e "${CINZA}${diferenca}${SEM_COR}"
        echo "------------------------------------"
    fi

    echo ""
done

echo "Fim da execução dos testes."
