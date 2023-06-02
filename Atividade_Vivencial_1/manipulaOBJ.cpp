#include "manipulaOBJ.h"
#include <fstream>
#include <sstream>
#include <string>

int contaParametro(char parametro, std::string filepath)
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

int contaParametro(std::string parametro, std::string filepath)
{
	std::fstream file(filepath);
	std::string linha;
	int contador = 0;

	while (getline(file, linha))
	{
		if (linha.substr(0,1) == parametro)
		{
			contador++;
		}
	}
	file.close();

	return contador;
}

void preencheMatrizDeTipo(char tipo, PONTO* matrizDePontos, std::string filepath)
{
	std::fstream file(filepath);
	std::stringstream ss;
	std::string linha;

	while (getline(file, linha))
	{
		if (linha[0] == tipo)
		{
			linha.erase(0, 2);
			ss << linha;
		}
	}
	file.close();

	
}
