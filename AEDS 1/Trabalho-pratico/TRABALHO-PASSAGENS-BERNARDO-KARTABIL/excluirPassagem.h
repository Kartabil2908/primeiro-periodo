#ifndef EXCLUIRPASSAGEM_H
#define EXCLUIRPASSAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void excluirPassagem()
{

    FILE *arquivo, *novoArquivo;
    char linha[80], confirmacao;
    int IdUser, IdLinha, qtd, lastId, cont = 0;

//----------------------------------------------- PEDINDO O ID DA PASSAGEM -------------------------------------------- //

    printf("Digite o id da passagem: ");
    scanf("%d", &IdUser);

    // Pedir confirma��o do usu�rio
    printf("Tem certeza que deseja excluir a passagem (Y/N)? ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 'Y' && confirmacao != 'y')
    {
        printf("A exclusao foi cancelada.\n");
        return;
    }

//----------------------------------------------- PEDINDO O ID DA PASSAGEM -------------------------------------------- //

//----------------------------------------------- OPERA��O COM QTD E �LTIMO ID -------------------------------------------- //

    arquivo = fopen("Passagens.txt", "r");
    novoArquivo = fopen("Temporario.txt", "w"); // abrindo um arquivo tempor�rio

    fscanf(arquivo, "%d", &qtd); // lendo a quantidade de passagens cadastradas

    qtd--;

    fprintf(novoArquivo, "%d\n", qtd); //printando a nova quantidade de passagens no arquivo tempor�rio


    fscanf(arquivo, "%d", &lastId); // escaneando o �ltimo ID cadastrado do arquivo principal

    fprintf(novoArquivo, "%d\n", lastId); // printando o �ltimo ID cadastrado no arquivo tempor�rio.

//----------------------------------------------- OPERA��O COM QTD E �LTIMO ID -------------------------------------------- //

//----------------------------------------------- PRINTANDO AS NOVAS LINHAS NO NOVO ARQUIVO -------------------------------------------- //

    while (fscanf(arquivo, " %[^\n]", linha) != EOF)
    {
        sscanf(linha, "%d", &IdLinha);

        if (IdLinha != IdUser)
        {
            fprintf(novoArquivo, "%s\n", linha);
        }

        cont++;
    }

    fclose(arquivo);
    fclose(novoArquivo);

//----------------------------------------------- PRINTANDO AS NOVAS LINHAS NO NOVO ARQUIVO -------------------------------------------- //

//----------------------------------------------- PRINTANDO AS NOVAS LINHAS NO ARQUIVO ORIGINAL -------------------------------------------- //

    arquivo = fopen("Passagens.txt", "w");
    novoArquivo = fopen("Temporario.txt", "r");

    while (fscanf(novoArquivo, " %[^\n]", linha) != EOF)
    {
        fprintf(arquivo, "%s\n", linha);
    }

    fclose(arquivo);
    fclose(novoArquivo);
}

//----------------------------------------------- PRINTANDO AS NOVAS LINHAS NO ARQUIVO ORIGINAL -------------------------------------------- //

#endif
