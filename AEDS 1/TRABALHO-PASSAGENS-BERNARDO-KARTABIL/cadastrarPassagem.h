#ifndef CADASTRAR_PASSAGEM_H
#define CADASTRAR_PASSAGEM_H


#include <stdbool.h>
#include <stdio.h>
#include "Passagem.h"
#include "validacoes.h"

void cadastrarPassagem(){
    FILE *arquivo;
    Passagem pass;
    int IDtotal = 0, auxID = 0;
    pass.ID = 0;


    arquivo = fopen("Passagens.txt", "a+");

    if (arquivo == NULL) {
        puts("Erro ao abrir o arquivo,programa encerrado.");
        exit(2);
    }

    // Solicita��o do c�digo de aeroporto de origem com valida��o e corre��o para letras mai�scula //
    do {
        printf("Digite o codigo do aeroporto de origem (3 letras mai�sculas):\n");
        scanf(" %[^\n]", pass.aeroportoOrigem);
        fflush(stdin);

        // Corrigir c�digo para letras mai�sculas //

        corrigirCodigoAeroporto(pass.aeroportoOrigem);

        if (!validarCodigoAeroporto(pass.aeroportoOrigem)) {
            printf("C�digo de aeroporto inv�lido. Por favor, insira um c�digo v�lido.\n");
        }

    } while (!validarCodigoAeroporto(pass.aeroportoOrigem));

    // Solicita��o do c�digo de aeroporto de destino com valida��o e corre��o
    do {
        printf("Digite o codigo do aeroporto de destino (3 letras mai�sculas):\n");
        scanf(" %[^\n]", pass.aeroportoDestino);
        fflush(stdin);

        corrigirCodigoAeroporto(pass.aeroportoDestino);

        if (!validarCodigoAeroporto(pass.aeroportoDestino)) {
            printf("C�digo de aeroporto inv�lido. Por favor, insira um c�digo v�lido.\n");
        }

    } while (!validarCodigoAeroporto(pass.aeroportoDestino));

    printf("Digite a cidade de origem:\n");
    scanf(" %[^\n]", pass.cidadeOrigem);
    fflush(stdin);
    printf("Digite a cidade de destino:\n");
    scanf(" %[^\n]", pass.cidadeDestino);
    fflush(stdin);

    // Solicita��o da data com valida��o
  do {
    printf("Digite o dia do seu voo:\n");
    scanf(" %d", &pass.data.dia);
    fflush(stdin);
    printf("Digite o mes do seu voo:\n");
    scanf("%d", &pass.data.mes);
    fflush(stdin);
    printf("Digite o ano do seu voo (4 d�gitos):\n");
    scanf("%d", &pass.data.ano);
    fflush(stdin);

    if (!validarData(pass.data.dia, pass.data.mes, pass.data.ano)) {
        printf("Data inv�lida. Por favor, insira uma data v�lida.\n");
    }

} while (!validarData(pass.data.dia, pass.data.mes, pass.data.ano) || pass.data.ano < 1000 || pass.data.ano > 9999);


    // Solicita��o do hor�rio de sa�da com valida��o
    do {
        printf("Digite o hora de saida do seu voo:\n");
        scanf("%d", &pass.horarioSaida.horas);
        fflush(stdin);
        printf("Digite o minuto de saida do seu voo:\n");
        scanf("%d", &pass.horarioSaida.minutos);
        fflush(stdin);

        if (!validarHorario(pass.horarioSaida.horas, pass.horarioSaida.minutos)) {
            printf("Hor�rio de sa�da inv�lido. Por favor, insira um hor�rio v�lido.\n");
        }

    } while (!validarHorario(pass.horarioSaida.horas, pass.horarioSaida.minutos));

    // Solicita��o do hor�rio de chegada com valida��o
    do {
        printf("Digite o hora de chegada do seu voo:\n");
        scanf("%d", &pass.horarioChegada.horas);
        fflush(stdin);
        printf("Digite o minuto de chegada do seu voo:\n");
        scanf("%d", &pass.horarioChegada.minutos);
        fflush(stdin);

        if (!validarHorario(pass.horarioChegada.horas, pass.horarioChegada.minutos)) {
            printf("Hor�rio de chegada inv�lido. Por favor, insira um hor�rio v�lido.\n");
        }

    } while (!validarHorario(pass.horarioChegada.horas, pass.horarioChegada.minutos));



    printf("Digite o preco da sua passagem:\n");
    scanf("%f", &pass.preco);
    fflush(stdin);

    IDtotal++;
    fseek(arquivo, 0, SEEK_SET); // Move o indicador de posi��o para o in�cio do arquivo.
    fprintf(arquivo, "%d", IDtotal); // Atualiza o n�mero total de passagens.

    fseek(arquivo, 0, SEEK_END); // Move o indicador de posi��o para o final do arquivo.
    pass.ID++;
    pass.ID = pass.ID + auxID;
    auxID = pass.ID;




    fprintf(arquivo,"%d;", auxID);
    fprintf(arquivo,"%s;", pass.aeroportoOrigem);
    fprintf(arquivo, "%s;", pass.aeroportoDestino);
    fprintf(arquivo, "%s;", pass.cidadeOrigem);
    fprintf(arquivo, "%s;", pass.cidadeDestino);
    fprintf(arquivo, "%02d/%02d/%04d;", pass.data.dia, pass.data.mes, pass.data.ano);
    fprintf(arquivo, "%02d:%02d;", pass.horarioSaida.horas, pass.horarioSaida.minutos);
    fprintf(arquivo, "%02d:%02d;", pass.horarioChegada.horas, pass.horarioChegada.minutos);
    fprintf(arquivo, "%.2f\n", pass.preco);

    fclose(arquivo);

}

#endif // CADASTRAR_PASSAGEM_H
