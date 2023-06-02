#pragma once
#include <string>
struct PONTO
{
	float x;
	float y;
	float z;
};
int contaParametro(char parametro, std::string filepath);//IT IS ALIVE!
int contaParametro(std::string parametro,std::string filepath);
void preencheMatrizDeTipo(char tipo, PONTO* matrizDePontos, std::string filepath);
