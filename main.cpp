#include <iostream>
#include <fstream>
#include <string>

static unsigned int num_linhas = 0;

struct Linha{
    unsigned int num;
    std::string texto;
};

void encontrarNumLinhas(std::ifstream &file);
Linha *extrairArquivo(std::ifstream &file);

int main(){
    std::ifstream file("exemplo.txt");
    encontrarNumLinhas(file);
    Linha* ptr = extrairArquivo(file);
    unsigned int x = 0;
    while (x < num_linhas){ //IMPRIMINDO O TREIM
        std::cout<<"Linha: " <<(ptr + x)->num <<" Texto: " <<(ptr + x)->texto <<std::endl;
        x++;
    }

    delete[] ptr;
}

Linha* extrairArquivo(std::ifstream &file){ //ARMAZENA CADA LINHA DO ARQUIVO NUM VETOR DE LINHAS
    Linha* vet = new Linha[num_linhas];
    std::string str;
    unsigned int linhaAtual = 0;
    while (linhaAtual < num_linhas){
        std::getline(file, str);
        (vet + linhaAtual)->num = linhaAtual;
        (vet + linhaAtual)->texto = str;
        linhaAtual++;
    }
    return vet;
}

void encontrarNumLinhas(std::ifstream &file){ //CONTA O NUM DE LINHAS DO ARQUIVO
    std::string str;
    while (!file.eof()){
        std::getline(file, str);
        num_linhas++;
    }
    file.close();
    file.open("exemplo.txt",std::ifstream::in); //FECHANDO O ARQUIVO E ABRINDO NOVAMENTE PARA LIMPAR O BUFFER GETLINE
}
