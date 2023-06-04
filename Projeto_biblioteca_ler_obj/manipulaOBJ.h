#pragma once
#include <string>
struct PONTO
{
	float x;
	float y;
	float z;
};
/******************************************************
* função contaParametro
* recebe um parêmetro em char - para definições de um caractere.
* retorna a quantidade de ocorrências, para definir um tamanho de matriz.
*********************************************************/
int contaParametro(char parametro, std::string filepath);//IT IS ALIVE!

/******************************************************
* função contaParametro
* recebe um parêmetro em string - para definições de mais de um caractere.
* retorna a quantidade de ocorrências, para definir um tamanho de matriz.
*********************************************************/
int contaParametro(std::string parametro,std::string filepath);//IT IS ALIVE!

void preencheMatrizDeTipo3(char tipo, PONTO* matrizDePontos, std::string filepath);
