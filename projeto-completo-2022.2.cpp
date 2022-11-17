#include <iostream> // Entradas e Saidas
#include <climits> // INT_MAX

using namespace std;

int main()
{
	//entradas

	int carro; //carro disponível p/ corrida
	int custo[100][100]; //custo[i][j] = custo de ir do local 'i' para o local 'j'
	int n; //numero de locais
	int condutor[100]; //custo de cada condutor de sair do ponto inicial até o local_partida
	int e; //numero de condutores
	int local_partida; //lugar do local_partida
	int pessoas[100]; //quantidade de pessoas em cada endereço
	int capacidade; //quantidade de lugares em que o carro 
	int entrega;
	
	//fazendo a leitura dos locais de entrega
	cout << "Quantos lugares os condutores precisam deixar os passageiros?" << endl;
	cin >> n;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
		{
			cout << "Entre com o custo de ir do local " << i << " para o local " << j << endl;
			cin >> custo[i][j];
			custo[j][i] = custo[i][j]; //custo de i->j = custo de j->i
		}

	cout << "Entre com o local de partida" << endl;
	cin >> local_partida;

	//fazendo a leitura dos pontos iniciais dos condutores estão até o local de partida
	cout << "Entre com o numero de condutores" << endl;
	cin >> e;

	for(int i = 1; i <= e; i++)
	{
		cout << "Entre com o custo de locomocao do condutor " << i << " para ir ate o local de partida " << endl;
		cin >> condutor[i];
	}

	// fazendo a leitura da quantidade de pessoass
	for(int i = 1; i <= n ; i++)
	{
		if (i != local_partida)
		{
			cout << "Entre com a quantidade de pessoas que estão no local " << i << endl;
			cin >> pessoas[i];
		}
		else
		{
			pessoas[i] = -1;
		}

	}

	// entrada da capacidade do carro do condutor
	cout << "Entre com a capacidade do carro do condutor " << endl;
	cin >> capacidade;

	int condutor_proximo; // condutor mais próximo
	int aux;
	int local_atual;
	int proximo_local;
	int menor_custo;
	int custo_at;
	int entregou[100][100]; // pessoa que o condutor "i" entregou
	int vis [100][100]; // local final da pessoa

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			entregou[i][j] = -1; // não entregou nenhuma pessoa ainda
			vis[i][j] = -1;
		}


	entrega = 0;
	proximo_local = local_partida;

	while(entrega < n - 1) // enquanto não terminar de fazer todas as entregas
	{
		local_atual = local_partida;
		aux = INT_MAX;
		menor_custo = 0;

		// verificando o condutor mais proximo do local de partida
		for (int i = 1; i <= e; i++)
		{
			if (aux > condutor[i])
			{
				aux = condutor[i];
				condutor_proximo = i;
			}
		}

		cout << "Condutor " << condutor_proximo << " vai fazer a entrega." << endl;
		carro = 0;

		// verificando pessoas para entregar
		for(int i = 1; i <= n ; i++)
			if(pessoas[i] != -1)
				if(carro + pessoas[i] <= capacidade)
				{
					carro += pessoas[i];
					pessoas[i] = -1;
					cout << "Pessoa " <<  i << " entregue." << endl;
					entregou[condutor_proximo][i] = 1;
					entrega ++;
				}
				
		// verificando rota
		menor_custo = condutor[condutor_proximo];
		cout << "Rota: ";

		if(vis[condutor_proximo][proximo_local] == 1)
		{
			cout << "Local " << proximo_local << " ";
			cout << "-> local de partida ";
		}
		else
		{
			cout <<  "Local de partida";
		}


		for(int i = 1; i <= n - 1; i++) // n-1 vezes = qnt de caminhos (exceto a volta para o local de partida)
		{
			vis[condutor_proximo][local_atual] = 1; // marco que ja passou pelo local atual
			// encontrar qual o local mais proximo
			custo_at = INT_MAX;
			for(int j = 1 ; j <= n; j++)
			{
				if(entregou[condutor_proximo][j] == 1)
					if(vis[condutor_proximo][j] == -1 && custo_at > custo[local_atual][j])
					{
						proximo_local = j;
						custo_at = custo[local_atual][j];
						menor_custo += custo_at;
						vis[condutor_proximo][j] == 1;
						cout << "-> Local " << j;
						aux = j;
					}
			}
			local_atual = proximo_local;
		}
		condutor[condutor_proximo] = custo[aux][local_partida];
		cout << endl;
		cout << "Tempo total percorrido: " << menor_custo << endl;
		cout << "________________________________________________" << endl;
	}
	return 0;
}