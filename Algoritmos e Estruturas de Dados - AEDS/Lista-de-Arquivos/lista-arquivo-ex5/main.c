/* Escreva um programa que concatene o conte�do de dois arquivos. O conte�do dos dois arquivos dever� ser
adicionado em um terceiro arquivo. */


#include <stdio.h>

int main()
{

    FILE *arquivo;
    char string [15];

    // abrindo o primeiro arquivo para leitura //

    arquivo = fopen("arquivo1.txt", "r");


    // lendo o primeiro arquivo e colocando o conte�do no terceiro arquivo//

    fgets(string, sizeof(string), arquivo);
    fclose(arquivo);

    arquivo = fopen("arquivo3.txt", "w");

    fputs(string,arquivo);

    fclose(arquivo);


    // lendo o segundo arquivo e colocando o conte�do no terceiro //

    arquivo = fopen("arquivo2.txt", "r");

    fgets(string, sizeof(string), arquivo);
    fclose(arquivo);

    fopen("arquivo3.txt","a");

    fputs(string,arquivo);

    fclose(arquivo);

    return 0;
}
