#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <list>

int num_threads = 2;
int num_linhas = 0;

struct Posicao{
	int linha;
	int coluna;
};

struct Linha{
	std::string texto;
	int num;
	
};

std::list<Posicao> buscarString(std::ifstream &file, std::string str, int linha);
std::list<Linha>* extrairArquivo(std::ifstream &file);

int main(){
	std::ifstream file("exemplo.txt");
	std::string str;	
	while (!file.eof()){          //OBTENDO O NÚMERO DE LINHAS DO ARQUIVO
		std::getline(file, str);
		num_linhas++;
	}
	file.close();

	file.open("exemplo.txt",std::ifstream::in); //O JEITO QUE ENCONTREI DE LIMPAR O BUFFER GETLINE	

	std::list<Linha> *ptr = extrairArquivo(file); //EXECUÇÃO DO TESTE
	std::list<Linha>::iterator it;
	int x = 0;
	while (x < num_threads){
		it = (*(ptr + x)).begin();
		while(it != (*(ptr + x)).end()){
			std::cout<<"Linha: " <<(*it).num <<" Texto: " <<(*it).texto <<std::endl;
			it++;
		}
		x++;
	}
	delete[] ptr;		
	
}

std::list<Posicao> buscarString(std::ifstream &file, std::string str, int linha){
	std::list<Posicao> lista;
	int count = linha;
	std::string aux = "";
	unsigned int pos = 0;
	while(count < linha + (num_linhas/num_threads)){
		std::getline(file, aux);
		pos = aux.find(str);		
		if(pos != -1){
			Posicao p;
			p.linha = count;
			p.coluna = pos; 
			lista.push_back(p);
		}
		count++;
	}

	return lista;
}

std::list<Linha>* extrairArquivo(std::ifstream &file){
	std::list<Linha>* lista = new std::list<Linha>[num_threads]; //VETOR DE LISTAS; O NÚMERO DE LISTAS É IGUAL AO NÚMERO DE THREADS
	std::string str;
	int lpt = num_linhas/num_threads; //CONSTANTE
	int linhaAtual = 0; //MARCADOR DE LINHA
	int thread = 0; //MARCADOR DE THREAD
	int aux = 0; 
	while (thread < num_threads){ //ENQUANTO O THREAD ATUAL NÃO ALCANÇAR O NÚMERO TOTAL DE THREADS
		linhaAtual = lpt * thread; //LINHA ATUAL É INICIADA NA PRIMEIRA LINHA QUE DEVERÁ SER PROCESSADA POR CADA THREAD
		aux = linhaAtual + lpt; //O LIMITE PARA O CONTADOR
		while (linhaAtual < aux){
			std::getline(file, str); //PEGA CADA LINHA, JUNTA NUMA INSTÂNCIA DA STRUCT 'Linha' E ARMAZENA NA LISTA REFERENTE AO THREAD ATUAL
			Linha l;
			l.num = linhaAtual;
			l.texto = str;
			(*(lista + thread)).push_back(l);
			linhaAtual++;
		}
		thread++;
	}
	return lista;
}
