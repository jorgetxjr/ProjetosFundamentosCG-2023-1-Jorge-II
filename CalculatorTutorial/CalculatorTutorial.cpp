// CalculatorTutorial.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Calculadora.h"
using namespace std;

int main()
{
    double x = 0.0;
    double y = 0.0;
    double resultado = 0.0;
    char operador = '+';

    cout << "Calculator Console Application" << endl << endl;
    cout << "Please enter the operation to perform. Format: a+b | a-b | a*b | a/b"
        << endl;
    Calculadora c;
    while (true)
    {
        cin >> x >> operador >> y;
        if (operador == '/' && y == 0.0)
        {
            cout << "impossível dividir por zero!" << endl;
            continue;
        }
        else
        {
            resultado = c.calcular(x, operador, y);
        }
        cout << "Resultado " << "de " << x << operador << y << " eh: " << resultado << endl;
    }
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
