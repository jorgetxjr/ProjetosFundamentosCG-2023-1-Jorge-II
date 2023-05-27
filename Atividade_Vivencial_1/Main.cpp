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

int main(void)
{
	string vConteudo;
	string fConteudo;
	string conteudo = "arquivo.obj";
	array<string,3> pontos;
	int fragmentos[2][9] = {};
	string triânguloTeste;
	int j = 0;
	int k = 0;
	string tmp;

	vConteudo = lerArquivoV(conteudo);
	fConteudo = lerArquivoF(conteudo);

	//cout << "v:\n" << vConteudo << endl;
	/*trocando espaços por vírgulas*/
	/*podemos começar aqui uma função 'normaliza pontos'*/
	for (int i = 0; i < vConteudo.length(); i++)
	{
		if (vConteudo[i] == ' ')
		{
			vConteudo[i] = ',';
		}
	}
	
	//cout << "v apos manipulacao: \n" << vConteudo << endl;
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
	//cout << "pontos na posicao zero:\n" << pontos[0] << endl;
	for (int i = 0; i < size(pontos); i++)
	{
		pontos[i] = pontos[i] + "," ;
	}
	//cout << "pontos na posicao zero full:\n" << pontos[0] << endl;
	/*fim 'normaliza pontos'*/

	/*posso começar uma nova função aqui...*/
	cout << "f:\n" << fConteudo << endl;
	for (int i = 0; i < fConteudo.length(); i++)
	{
		if (fConteudo[i] == ' ')
		{
			fConteudo[i] = '/';
		}
	}
	cout << "f normalizado:\n" << fConteudo << endl;
	j = 0;
	k = 0;
	for (int i = 0; i < fConteudo.length(); i++)
	{
		if (fConteudo[i] == '/') 
		{
			try {
				fragmentos[j][k] =stoi(tmp) ;
				k++;
				tmp = "";
			}
			catch (std::invalid_argument const& e) {
				//std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
			}
			catch (std::out_of_range const& e) {
				std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
			}
		}
		if (fConteudo[i] == '\n') 
		{
			j++;
			k = 0;
			tmp = "";
		}
		else 
		{
			tmp = tmp + fConteudo[i];
		}
	}
	for(int i=0;i<2;i++)
		for(int l=0;l<9;l++)
			cout << "Posição do fragmento: " << fragmentos[0][0] <<"\n"<< endl;
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