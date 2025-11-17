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

    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), f)) {
        fprintf(stderr, "Arquivo vazio ou erro de leitura.\n");
        return 1;
    }
    fclose(f);

    buffer[strcspn(buffer, "\n")] = 0;

    for (int i = 0; buffer[i]; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            erro_sintaxe();
        }
    }

    FILE *out = fopen("output.s", "w");
    if (!out) {
        perror("Erro criando output.s");
        return 1;
    }

    fprintf(out,
        ".section .text\n"
        ".globl _start\n"
        "_start:\n"
        "    movabs $%s, %%rax\n"
        "    call imprime_num\n"
        "    call sair\n"
        ".include \"runtime.s\"\n",
        buffer
    );

    fclose(out);

    printf("Compilação CI concluída.\n");
    printf("Agora rode:\n");
    printf("  as -o output.o output.s\nas -o runtime.o runtime.s\nld -o programa output.o runtime.o\n./programa\n");

    return 0;
}
