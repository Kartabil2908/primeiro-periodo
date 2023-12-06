/* Implemente um programa que leia um arquivo texto e imprima, linha a linha, o seu conte�do na tela. Imprima
tamb�m a quantidade de linhas que este arquivo possui */

#include <stdio.h>

int main()
{

    FILE *arquivo;
    char string[15];
    int contadorLinha = 0;

    arquivo = fopen("arquivoteste.txt", "r");

    while(fgets(string, sizeof(string), arquivo) != NULL)
    {

        printf("%s", string);
        contadorLinha++;

    }

    printf("O n�mero de linhas no arquivo �: %d", contadorLinha);

    return 0;
}
