#include "manipulaOBJ.h"
#include <fstream>
#include <sstream>
#include <string>

/*VEJA A DOCUMENTAÇÃO NO ARQUIVO .h*/
int contaParametro(char parametro, std::string filepath)//OK
{
	std::fstream file(filepath);
	std::string linha;
	int contador = 0;

	while (getline(file, linha))
	{
		if (linha[0] == parametro)
		{
			contador++;
		}
	}
	file.close();

	return contador;
}

int contaParametro(std::string parametro, std::string filepath)//OK
{
	std::fstream file(filepath);
	std::string linha;
	int contador = 0;

	while (getline(file, linha))
	{
		if (linha.substr(0,2) == parametro)
		{
			contador++;
		}
	}
	file.close();

	return contador;
}

void preencheMatrizDeTipo3(char tipo, PONTO* matrizDePontos, std::string filepath)
{
	std::fstream file(filepath);
	std::string linha;
	int i = 0;

	while (getline(file, linha))
	{
		if (linha[0] == tipo)
		{
			linha.erase(0, 2);
			std::istringstream ss(linha);
			ss >> matrizDePontos->x >> matrizDePontos->y >> matrizDePontos->z;
			matrizDePontos++;
		}

	}
	file.close();

	
}
