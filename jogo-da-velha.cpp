#include <iostream>
#include <string>

using namespace std;


// struct para nome dos jogadores e letras do jogo
struct Jogador
{
	string nome; // jogador1 e jogador2
	char marcador; // X ou O
	int pontuacao;
	
};

// struct para o tabuleiro
struct Tabuleiro
{
	char casas[3][3]; //matriz 3x3 do tabuleiro 
};

//função para preecher a matriz 1 ao 9
int iniciar(Tabuleiro &t)
{
	char num = '1';
	int i;
	int j;
	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 3;j++)
		{
			t.casas[i][j] = num;
			num++;
		}
	}
	return 1;
}

// função para mostrar o tabuleiro 
int jogo(Tabuleiro t)
{
	cout << endl;
	int i;
	int j;
	
	for(i = 0;i < 3;i++)
	{
		cout << " ";
		for(j = 0;j < 0;j++)
		{
			cout << " " << t.casas[i][j] << " ";
			if(j<2)
			{
				cout << "|";
			}
		}
		cout << endl;
		if(i < 2)
		{
			cout << "---+---+---" << endl;
		}
	}
	cout << endl;
	return 1;
}








//onde sera feito a leituras de todas as structs e funções acima
int main()
{
	cout <<"----------- Jogo da Velha -----------" << endl;
	
	Tabuleiro tabuleiro;
	
	jogo(tabuleiro);
	
	
	return 0;
}

