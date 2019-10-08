#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <omp.h>
static unsigned int num_linhas = 0;

void encontrarNumLinhas(std::ifstream &file);
std::string  *extrairArquivo(std::ifstream &file);


int main()
{ 

    std::ifstream file("exemplo.txt");
    encontrarNumLinhas(file);
    std::string* ptr = extrairArquivo(file);
    unsigned int x = 0;
    std::string palavra="sou";
    int palavra_size=palavra.size();
    
     while (x < num_linhas){ //IMPRIMINDO O TREIM
        std::cout<<*(ptr + x) <<std::endl;
        x++;
    }
    std::string aux="";
    int quantidade=0,i=0,aux_size=0;
    #pragma omp parallel for reduction(+:quantidade) private(aux,aux_size)
    for ( i = 0; i < num_linhas; i++)
    {
            aux=*(ptr+i);
            std::cout<<aux <<std::endl;
            aux_size=aux.length();
            for(int j=0;j<aux_size+1-palavra_size;j++){
                if(aux.substr(j,palavra_size)==palavra)
                    quantidade++;
            std::cout<<quantidade <<std::endl;
            } 
    }

std::cout<<"quantidade de palavras "<<palavra<<": "<<quantidade<<std::endl;

    delete[] ptr;
    return 0;
}

std::string* extrairArquivo(std::ifstream &file){ //ARMAZENA CADA LINHA DO ARQUIVO NUM VETOR DE LINHAS
    std::string* vet = new std::string[num_linhas];
    std::string str;
    unsigned int linhaAtual = 0;
    while (linhaAtual < num_linhas){
        std::getline(file, str);
        *(vet + linhaAtual) = str;
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
