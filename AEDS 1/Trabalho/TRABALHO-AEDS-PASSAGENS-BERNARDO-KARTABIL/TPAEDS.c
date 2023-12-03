#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} DATE;

typedef struct {
    int horas;
    int minutos;
} TIME;

typedef struct Passagem {
    int ID;
    char aeroportoOrigem[4];  // 3 letras + terminador o \0
    char aeroportoDestino[4];
    char cidadeOrigem[20];
    char cidadeDestino[20];
    DATE data;
    TIME horarioSaida;
    TIME horarioChegada;
    float preco;
} Passagem;

int verificarDiasMes(int mes, int ano);
bool validarData(int dia, int mes, int ano);
bool validarHorario(int horas, int minutos);
bool validarCodigoAeroporto(const char *codigo);
void corrigirCodigoAeroporto(char *codigo);
void verificarDataPassagem(int dia, int mes, int ano);
void cadastrarPassagem();

int main() {
    int respostaRegistrada;

    puts("Ol�! Obrigado por escolher a Ultrafast Airlines! Por favor, escolha "
         "uma das op��es abaixo:");

    while (respostaRegistrada != 6) {
        puts("1) Ver todas as passagens no sistema;");
        puts("2) Pesquisar uma passagem;");
        puts("3) Cadastrar uma passagem");
        puts("4) Editar uma passagem");
        puts("5) Excluir uma passagem");
        puts("6) Sair do programa");

        scanf("%d", &respostaRegistrada);

        switch (respostaRegistrada) {
            case 3:
                cadastrarPassagem();
                break;

            case 6:
                exit(1);
                break;

            default:
                printf("Op��o inv�lida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}

void cadastrarPassagem() {
    FILE *arquivo;
    Passagem pass;
    int IDtotal = 0;


    arquivo = fopen("Passagens.txt", "a");

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
    fprintf(arquivo,"%d; \n", IDtotal);

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

void corrigirCodigoAeroporto(char *codigo) {
    // Converte todas as letras do c�digo para mai�sculas
    for (int i = 0; i < 3; ++i) {
        codigo[i] = toupper(codigo[i]);
    }
}

bool validarHorario(int horas, int minutos) {
    // Verifica se as horas e minutos est�o dentro dos limites v�lidos
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59) {
        return false;
    }

    return true;
}

bool validarData(int dia, int mes, int ano) {
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        diasNoMes[2] = 29;  // Ano bissexto, fevereiro tem 29 dias
    }

    if (mes < 1 || mes > 12 || dia < 1 || dia > diasNoMes[mes]) {
        return false;
    }

    return true;
}

bool validarCodigoAeroporto(const char *codigo) {
    // Verifica se o c�digo tem exatamente 3 letras
    if (strlen(codigo) != 3) {
        return false;
    } else{

    return true;
    }
}
