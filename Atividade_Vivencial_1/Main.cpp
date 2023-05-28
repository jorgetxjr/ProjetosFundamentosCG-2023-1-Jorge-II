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
//#include<vector>
using namespace std;

string lerArquivoV(const string filepath);
string lerArquivoF(const string filepath);
//string* normalizaConteudoV(const string conteudo);

int main(void)
{
	string vConteudo;
	string fConteudo;
	string conteudo = "arquivo.obj";
	string pontos[3];
	string fragmentos[2];
	int j = 0;
	int k = 0;
	
	vConteudo = lerArquivoV(conteudo);
	fConteudo = lerArquivoF(conteudo);

	
	/*trocando espaços por vírgulas*/
	/*podemos começar aqui uma função 'normaliza pontos'*/
	for (int i = 0; i < vConteudo.length(); i++)
	{
		if (vConteudo[i] == ' ')
		{
			vConteudo[i] = ',';
		}
	}
	/*splitting nos \n*/
	for (int i = 0; i < vConteudo.length(); i++)
	{
		if (vConteudo[i] == '\n')
		{
			pontos[j] = vConteudo.substr(k, i);
			j++;
			k = i + 1;
		}
	}
	
	for (int i = 0; i < size(pontos); i++)
	{
		pontos[i] = pontos[i] + "," ;
	}
	cout << "pontos na posicao zero full:\n" << pontos[0] << endl;
	/*fim 'normaliza pontos'*/
		
	//cout << "pontos:\n" << pontos[0] << endl;

	j = 0;
	k = 0;
	/*posso começar uma nova função aqui...*/
	cout << "f:\n" << fConteudo << endl;
	/*splitting nos \n*/
	for (int i = 0; i < fConteudo.length(); i++)
	{
		if (fConteudo[i] == '\n')
		{
			fragmentos[j] = fConteudo.substr(k, i);
			j++;
			k = i + 1;
		}
	}
	cout << "uma linha de fragmento: \n" << fragmentos[0] << endl;
	/*cada ponto tem uma relação com um elemento no fragmento. Não sei ainda como fazer isso!*/
	
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

//string* normalizaConteudoV(const string conteudo)
//{
//	string vConteudo = lerArquivoV(conteudo);
//	int k = 0,j=0;
//	string pontos[3];
//
//	for (int i = 0; i < vConteudo.length(); i++)
//	{
//		if (vConteudo[i] == ' ')
//		{
//			vConteudo[i] = ',';
//		}
//	}
//
//	for (int i = 0; i < vConteudo.length(); i++)
//	{
//		if (vConteudo[i] == '\n')
//		{
//			pontos[j] = vConteudo.substr(k, i);
//			j++;
//			k = i + 1;
//		}
//	}
//
//	for (int i = 0; i < size(pontos); i++)
//	{
//		pontos[i] = pontos[i] + ",";
//	}
//
//	return pontos;
//}
