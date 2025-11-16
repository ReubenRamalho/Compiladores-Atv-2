#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void erro_sintaxe() {
    fprintf(stderr, "Erro de sintaxe: apenas dígitos (0-9) são permitidos.\n");
    exit(1);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo.ci>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Erro abrindo arquivo");
        return 1;
    }

    // Lê arquivo inteiro
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), f)) {
        fprintf(stderr, "Arquivo vazio ou erro de leitura.\n");
        return 1;
    }
    fclose(f);

    // Remove quebra de linha
    buffer[strcspn(buffer, "\n")] = 0;

    // Verifica sintaxe
    for (int i = 0; buffer[i]; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            erro_sintaxe();
        }
    }

    // Geração do código assembly CI
    FILE *out = fopen("output.s", "w");
    if (!out) {
        perror("Erro criando output.s");
        return 1;
    }

    fprintf(out,
        "    .section .data\n"
        "msg:    .string \"%s\\n\"\n\n"
        "    .section .text\n"
        "    .globl main\n"
        "main:\n"
        "    leaq msg(%%rip), %%rdi\n"
        "    xor %%rax, %%rax\n"
        "    call printf@PLT\n"
        "    ret\n",
        buffer
    );

    fclose(out);

    printf("Compilação concluída. Rode:\n");
    printf("  gcc output.s -o programa\n");
    printf("  ./programa\n");

    return 0;
}
