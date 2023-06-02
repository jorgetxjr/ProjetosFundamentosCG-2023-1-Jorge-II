/*
* THANKS:
* https://www.techiedelight.com/pt/remove-first-character-from-string-in-cpp/
* https://www.geeksforgeeks.org/stdstringerase-in-cpp/
* https://www.geeksforgeeks.org/substring-in-cpp/
* https://www.delftstack.com/pt/howto/cpp/how-to-find-length-of-an-array-in-cpp/
* 
*/
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>
#include "ManipulaOBJ.h"
//#include<vector>
using namespace std;

string lerArquivoV(const string filepath);
string lerArquivoF(const string filepath);
//string* normalizaConteudoV(const string conteudo);

//struct PONTO 
//{
//	float x;
//	float y;
//	float z;
//};

int main(void)
{
	unsigned int n = 0;
	string caminho = "arquivo.obj";
	n = contaParametro('v', caminho);
	cout << "Tamanho do n: " << n << endl;

	return 0;
}

string lerArquivoV(const string filepath)
{
	fstream file(filepath);
	stringstream ss;
	string linha;

	while (getline(file, linha))
	{
		if (linha[0] == 'v' || linha[0] == 'V')
		{
			linha.erase(0, 2);
			ss << linha << "\n";
		}
	}
	file.close();

	return ss.str();
}

string lerArquivoF(const string filepath)
{
	fstream file(filepath);
	stringstream ss;
	string linha;

	while (getline(file, linha))
	{
		if (linha[0] == 'f' || linha[0] == 'F')
		{
			linha.erase(0, 2);
			ss << linha << "\n";
		}
	}
	file.close();

	return ss.str();
}

