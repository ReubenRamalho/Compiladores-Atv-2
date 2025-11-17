# Integrantes
- LUIZ MANOEL BARBOSA RAMALHO - 20220096614
- REUBEN LISBOA RAMALHO CLAUDINO - 20210024602
- VICTOR PESSOA OLIVEIRA ORTINS - 20210024667

# Como rodar:

Primeiro, compile o ci_compiler com o comando do gcc:

```bash
gcc ci_compiler.c -o ci_compiler
```

Rode o executável gerado com o arquivo que você quer:

```bash
./ci_compiler constane_ci.ci
```

O executável irá gerar um .s que pode ser compilado e linkado no assembly:

```bash
as -o output.o output.s
as -o runtime.o runtime.s
ld -o programa output.o runtime.o
./programa
```
