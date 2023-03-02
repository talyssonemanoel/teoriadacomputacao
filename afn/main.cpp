#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef struct dado
{
	char value;
	bool final;
	bool ini;
}dado;

// void MostrarAlfabeto(dado** mat, int col) {
// 	for(int i=1;i<col;i++)
// 	{
// 		if(i==col-1)
// 			cout<<mat[0][i].value;
// 		else
// 			cout<<mat[0][i].value<<", ";
// 	}
// }
// 
// void MostrarEstados(dado** mat, int lin)
// {
// 	for(int i=1;i<lin;i++)
// 	{
// 		if(i==lin-1)
// 			cout<<"q"<<mat[i][0].value;
// 		else
// 			cout<<"q"<<mat[i][0].value<<", ";
// 	}
// }
// 

//
dado LocalizaEstadoInicial(dado **mat, int linha, dado estado)
{
	for(int i=0;i<linha;i++)
	{
		if(mat[i][0].ini==true)
		{
			return mat[i][0];
		}
	}
	return estado;
}

//
 dado VerificarChar(dado **mat, int linha, int coluna, char c, dado estado) {
	for(int i=1; i<linha; i++){ 
		for(int j=1; j<coluna; j++){ 
			if(mat[i][0].value==estado.value && c==mat[0][j].value) 
			{
				return mat[i][j];
			}
		}
	}
	return estado;
 }
 

dado VerificarCadeia(dado **mat, int linha, int coluna, char* c, int tam)
 {
 	dado est=LocalizaEstadoInicial(mat,linha,est); 
 	for(int i=0;i<tam;i++)
	 {
		 est=VerificarChar(mat, linha, coluna, c[i], est); 
	 }
	 return est;
 }

int main()
{
	int i,j,in,cont=0;
	char cadeia[50];
	dado estadoAtual;
	dado** mat;
	cout<<"Informe a quantidade de elementos contidos no alfabeto: ";
	cin>>j;
	system("cls");
	cout<<"Informe a quantidade de estados possiveis do AFD: ";
	cin>>i;
	cout<<"Os estados do seu AFD sao: ";
	

	for(int n=0;n<i;n++)
	{
		if(n!=i-1)
		{
			cout<<"q"<<n<<", ";
		}
		else
		{
			cout<<"q"<<n<<".";
		}
	}
	cout<<endl<<endl;
	system("pause");
	system("cls");
	
	mat=(dado**)malloc(i+1*sizeof(dado*));
	for(int n=0; n<i+1; n++)
		mat[n]=(dado*)malloc(sizeof(dado)*j+1);
	for(int linha=0;linha<i+1;linha++)
	{
		for(int coluna=0;coluna<j+1;coluna++)
		{
			mat[linha][coluna].value=NULL;
			mat[linha][coluna].ini=false;
			mat[linha][coluna].final=false;
		}
		if(linha>0)
		{
			mat[linha][0].value=48+linha-1;
		}
	}
	cout<<"Informe os elementos do alfabeto\n";

	for(int coluna=1;coluna<j+1;coluna++)
	{
		cout<<coluna<<" Elemento: ";
		cin.ignore(); 
		cin>>mat[0][coluna].value;
	}
	
	cout<<"\nInforme o estado inicial.\n";
	for(int linha=0;linha<i;linha++)
	{
		cout<<linha<<"- q"<<linha<<endl;
	}
	scanf("%d",&in); 
	mat[in+1][0].ini=true;

	while(cont<i) {
		cout<<"Informe o(s) estado(s) finais(s).\n";
		for(int linha=0;linha<i;linha++)
		{
			if(mat[linha+1][0].final==false)
				cout<<linha<<"- q"<<linha<<endl;
		}
		scanf("%d",&in);
		if(mat[in+1][0].final==true) {
			cout<<"O estado informado ja e estado final!\nInsira outro estado diferente ou continue!\n";
			cont--;
		}
		else
		{
			mat[in+1][0].final=true;
		}
		cout<<"1- Adicionar estado final\n2- Continuar\n";
		scanf("%d",&in);
		if(in==2)
			cont=i;
		cont++;
	}; 
	
	for(int linha=1; linha<i+1;linha++)
	{
		for(int coluna=1;coluna<j+1;coluna++)
		{
			//system("cls");
			cout<<"Indique a ligacao do estado q"<<linha-1<<" ao ler o elemento "<<mat[0][coluna].value<<endl;
			cout<<"Selecione uma das opcoes a seguir:\n";
			for(int y=1;y<=i+1;y++)
			{
				 if(y==i+1)
				{
				 	cout<<y-1<<"- Morte"<<endl;
				}
				else{
					cout<<y-1<<"- q"<<y-1<<endl;
				}
				
			}
			scanf("%d",&in);
			//atribuindo matriz
			if(in>=0 && in<i)
			{
				mat[linha][coluna]=mat[in+1][0];
			}
			else if(in==i) {
				mat[linha][coluna].value='#';
			}
			else
			{
				cout<<"Opcao invalida";
				coluna=coluna-1;
			}
		}
	}
	//IMPRIMINDO A MATRIZ
	//system("cls");
	for(int linha=0;linha<i+1;linha++)
	{
		for(int coluna=0;coluna<j+1;coluna++)
		{
			if(linha>0 && mat[linha][coluna].value!='#')
				cout<<"q"<<mat[linha][coluna].value<<"\t";
			else
				cout<<mat[linha][coluna].value<<"\t";
		}
		cout<<endl;
	}
	cout<<"\nAFD concluido!!!\n";
	cout<<"Obs: O simbolo # representa estado de morte."<<endl<<endl;
	//system("pause");
	int escolha=1;
	while(escolha!=2){
		//system("cls");
		cout<<"insira uma cadeia de elementos:";
		cin>>cadeia;
		estadoAtual=VerificarCadeia(mat,i+1,j+1,cadeia,strlen(cadeia));
		if(estadoAtual.final)
		{
			cout<<"\nCadeia reconhecida!!!";
		}
		else
		{
			cout<<"\nCadeia nao reconhecida!!!";
		}
		cout<<"\n\n1- Testar outra cadeia\n2- Fechar"<<endl;
		scanf("%d",&escolha);
		switch(escolha)
		{
			case 1:
				break;
			case 2:
				escolha=2;
				break;
			default:
				cout<<"Erro: Escolha uma opcao valida!";
		}
	}
		
	free(mat);
	
}