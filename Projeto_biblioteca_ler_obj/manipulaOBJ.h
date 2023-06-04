#pragma once
#include <string>
struct PONTO
{
	float x;
	float y;
	float z;
};
/******************************************************
* fun��o contaParametro
* recebe um par�metro em char - para defini��es de um caractere.
* retorna a quantidade de ocorr�ncias, para definir um tamanho de matriz.
*********************************************************/
int contaParametro(char parametro, std::string filepath);//IT IS ALIVE!

/******************************************************
* fun��o contaParametro
* recebe um par�metro em string - para defini��es de mais de um caractere.
* retorna a quantidade de ocorr�ncias, para definir um tamanho de matriz.
*********************************************************/
int contaParametro(std::string parametro,std::string filepath);//IT IS ALIVE!

void preencheMatrizDeTipo3(char tipo, PONTO* matrizDePontos, std::string filepath);
