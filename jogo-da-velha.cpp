#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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

//função para limpar
int limpar()
{
	cin.clear();
	string lixo;
	getline(cin, lixo);
	return 0;
}

// Coloca os números de 1 a 9 dentro do tabuleiro, preparando para um novo jogo
// '&t' permite modificar o tabuleiro real, não uma cópia.
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

// função para mostrar o tabuleiro no formato do jogo da velha
int jogo(Tabuleiro t)
{
	cout << endl;
	int i;
	int j;
	
	
    // organiza as linhas e colunas para ficar visualmente melhor
	for(i = 0;i < 3;i++)
	{
		cout << " ";
		for(j = 0;j < 3;j++)
		{
			// adicionando cores no tabuleito e nos marcadores X e O 
			char c = t.casas[i][j];

    		if (c == 'X')
        		cout << " \033[31m" << c << "\033[0m ";
    		else if (c == 'O')
        	   	cout << " \033[34m" << c << "\033[0m ";
    		else
        		cout << " \033[33m" << c << "\033[0m ";
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

//funçao para posiçao livre no tabuleiro
int Posicao(Tabuleiro t, int linha, int coluna)
{
	// se tiver um número, significa que ainda ninguém jogou ali
	if(t.casas[linha][coluna] >= '1' && t.casas[linha][coluna] <= '9')
	{
		return 1;
	}
	return 0;
}

// função para trocar nomes dos jogadores
int Nomes(Jogador &jogador1, Jogador &jogador2)
{
    int opcao;
    cout << endl;
    cout << "---- Trocar Nomes ----" << endl;
    cout << "1 - Trocar nome do Jogador 1" << endl;
    cout << "2 - Trocar nome do Jogador 2" << endl;
    cout << "3 - Trocar ambos os nomes" << endl;
    cout << "4 - Cancelar" << endl;
    cout << "Escolha uma opcao: ";
    
	// O '!' inverte o resultado: aqui significa "se não conseguiu ler o número".
    if (!(cin >> opcao))
    {
        limpar();
        return 0;
    }
    limpar();

    if (opcao == 1 || opcao == 3)
    {
        cout << "Novo nome do Jogador 1: " << endl;
        
        getline(cin >> ws, jogador1.nome);
        
        if (jogador1.nome.size() == 0)
		{
			jogador1.nome = "Jogador1";
		}
    }

    if (opcao == 2 || opcao == 3)
    {
        cout << "Novo nome do Jogador 2: " << endl;
        
        getline(cin >> ws, jogador2.nome);
        
        if (jogador2.nome.size() == 0)
		{
			jogador2.nome = "Jogador2";
		}
    }

    return 1;
}

//função para realizar jogadas
int jogadas(Tabuleiro &t, int posicao, char marcador)
{
	int linha;
	int coluna;
	
	if(posicao < 1 || posicao > 9)
	{
		return 0;
	}
	
	linha = (posicao -1) / 3;
	coluna = (posicao - 1) % 3;
	
	if(Posicao(t, linha, coluna) == 1)
	{
		t.casas[linha][coluna] = marcador;
		return 1;
	}
	return 0;
}

//funçao para verificar quem é o vencedor
int Vencedor(Tabuleiro t)
{
	int i;
	int j;
	int livres;
	
	// retorna quem venceu: 1 para X, 2 para O, 3 para empate e 0 caso ninguém venceu ainda
	
	//linhas
	for(i = 0; i < 3; i++)
	{
		if(t.casas[i][0] == t.casas[i][1] && t.casas[i][1] == t.casas[i][2])
		{
			if (t.casas[i][0] == 'X')
			{
				return 1;
			}
			if (t.casas[i][0] == 'O') 
			{
				return 2;
			}
		}
	}
	
	//colunas
	for (j = 0; j < 3; j++) {
        if (t.casas[0][j] == t.casas[1][j] && t.casas[1][j] == t.casas[2][j])
		{
			if (t.casas[0][j] == 'X')
			{
				return 1;
			}
			if (t.casas[0][j] == 'O')
			{
				return 2;
			}
		}
	}
	
	//diagonais
    if (t.casas[0][0] == t.casas[1][1] && t.casas[1][1] == t.casas[2][2])
	{
        if (t.casas[0][0] == 'X')
		{
			return 1;
		}
        if (t.casas[0][0] == 'O')
		{
			return 2;
		}
    }
    
    if (t.casas[0][2] == t.casas[1][1] && t.casas[1][1] == t.casas[2][0])
	{
        if (t.casas[0][2] == 'X')
		{
			return 1;
		}
        if (t.casas[0][2] == 'O')
		{
			return 2;
		}
    }
	
	//empate
	livres = 0;
	
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(Posicao(t, i, j) == 1)
			{
				livres++;
			}
		}
	}
	if (livres == 0)
	{
		return 3;
	}
	
	return 0;
	
}

//funçao para salvar no arquivo txt
int Resultado(string arquivo, Jogador jogador1, Jogador jogador2, int resultado)
{
    ofstream saida(arquivo.c_str(), ios::app);
    if (!saida.is_open())
	{
		return 0;
	}

	saida << jogador1.nome << " = " << jogador1.pontuacao << " X " 
          << jogador2.nome << " = " << jogador2.pontuacao
          << endl;
    saida.close();
    return 1;
}

// funçao para o arquivo que mostrara o historico do jogo
int Historico(string arquivo)
{
	int contador = 0;
	//.c_str() = converte a string para abrir o arquivo.
    ifstream entrada(arquivo.c_str());
    if (!entrada.is_open())
	{
        cout << "(Nenhum historico encontrado)" << endl;
        return 0;
    }

	cout << endl;
    cout << " ---- Historico de Partidas ----" << endl;
    cout << endl;
    string linha;
    
    while (getline(entrada, linha) && contador < 10)
	{
        cout << "  " << linha << endl;
        contador++;
    }
    entrada.close();
    return 1;
}






//onde sera feito a leituras de todas as structs e funções acima
int main()
{
		
	Tabuleiro tabuleiro;
	Jogador jogador1, jogador2;
	int jogar_novamente = 1;
	string arq = "historico_jogo_da_velha.txt";
	int atual;
	
	cout << "----------- Jogo da Velha -----------" << endl;
	cout << endl;
	
    Historico(arq);
    
    cout << endl;
    cout << endl;

	
    cout << "Nome do Jogador 1 (X): ";
    getline(cin >> ws, jogador1.nome);
    // .size() diz quantas letras tem no nome.
    if (jogador1.nome.size() == 0)
    {
		jogador1.nome = "Jogador1";
	}
	
    jogador1.marcador = 'X';
    jogador1.pontuacao = 0;

    cout << "Nome do Jogador 2 (O): ";
    getline(cin >> ws, jogador2.nome);
    // .size() diz quantas letras tem no nome.
    if (jogador2.nome.size() == 0)
	{
		jogador2.nome = "Jogador2";
	}
    
    jogador2.marcador = 'O';
    jogador2.pontuacao = 0;

	// controla se o jogo deve continuar repetindo partidas ou encerrar
    while (jogar_novamente == 1)
	{
		
        iniciar(tabuleiro);
        int turno = 1; // alterna entre jogador 1 e jogador 2, de acordo com o turno
        int acabou = 0;
		
		
        while (acabou == 0)
		{
            jogo(tabuleiro);
            Jogador &atual = (turno == 1 ? jogador1 : jogador2);

            cout << atual.nome << " (" << atual.marcador << "), escolha uma posicao (1-9): ";
            
            
            int posicao;
            if (!(cin >> posicao))
			{
                limpar();
                cout << "Entrada invalida!" << endl;
                
                // 'continue' faz o programa pular o restante deste turno do loop e voltar para o começo, pedindo a jogada novamente.
                continue;
            }
            limpar();

            if (jogadas(tabuleiro, posicao, atual.marcador) == 0)
			{
                cout << "Posicao invalida ou ocupada!" << endl;
                continue; 
            }

            int resultado = Vencedor(tabuleiro);
            
            if (resultado == 1)
			{
                jogo(tabuleiro);
                cout << ">>> " << jogador1.nome << " (X) venceu! <<<" << endl;
                jogador1.pontuacao++;
                Resultado(arq, jogador1, jogador2, 1);
                acabou = 1;
            } 
            else if (resultado == 2)
			{
                jogo(tabuleiro);
                cout << ">>> " << jogador2.nome << " (O) venceu! <<< " << endl;
                jogador2.pontuacao++;
                Resultado(arq, jogador1, jogador2, 2);
                acabou = 1;
            } 
            else if (resultado == 3)
			{
                jogo(tabuleiro);
                cout << ">>> Empate! <<< " << endl;
                Resultado(arq, jogador1, jogador2, 3);
                acabou = 1;
            } 
            else{
                if (turno == 1)
				{
					turno = 2;
				} else{
					turno = 1;
				}
            }
        }

		cout << endl;
        cout << "Placar Atual: " << endl;
        // setw(15) define que o nome será impresso ocupando 15 espaços
        cout << setw(15) << left << jogador1.nome << " : " << jogador1.pontuacao << endl;
        cout << setw(15) << left << jogador2.nome << " : " << jogador2.pontuacao << endl;
        
        int trocar;
        
		cout << endl;
		cout << "Deseja trocar os nomes? (1 = sim / 0 = nao): " << endl;
		
		if (!(cin >> trocar))
		{
    		limpar();
    		trocar = 0;
		}
		limpar();

		if (trocar == 1)
		{
    		Nomes(jogador1, jogador2);
		}
       
        cout << endl;
        cout << "Jogar novamente? (1 = sim / 0 = nao): " << endl;
        if (!(cin >> jogar_novamente))
		{
            limpar();
            jogar_novamente = 0;
        }
        limpar();
    }

	cout << endl;
    cout << "Fim de jogo!" << endl;
    // setw(15) define que o nome será impresso ocupando 15 espaços
    cout << setw(15) << left << jogador1.nome << " : " << jogador1.pontuacao << endl;
    cout << setw(15) << left << jogador2.nome << " : " << jogador2.pontuacao << endl;
	
	
	
	return 0;
}
