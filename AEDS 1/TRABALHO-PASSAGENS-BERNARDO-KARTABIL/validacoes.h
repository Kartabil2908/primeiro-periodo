#ifndef VALIDACOES_H
#define VALIDACOES_H

#include <ctype.h>
#include "Passagem.h"
#include <stdlib.h>
#include <stdbool.h>



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


bool validarHorario(int horas, int minutos) {
    // Verifica se as horas e minutos est�o dentro dos limites v�lidos
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59) {
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



void corrigirCodigoAeroporto(char *codigo) {
    // Converte todas as letras do c�digo para mai�sculas
    for (int i = 0; i < 3; ++i) {
        codigo[i] = toupper(codigo[i]);
    }
}


#endif // VALIDACOES_H
