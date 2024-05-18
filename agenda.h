#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include <fstream>
#include <cstring>

#define TAMANHO_NOME 50
#define TAMANHO_NUMERO 11

//lista circular duplamente encadeada com alocacao dinamica de memoria e persistencia dos dados

using namespace std;

struct agenda
{
   char nome[TAMANHO_NOME], email[TAMANHO_NOME];
   unsigned telefone, endereco;
   struct agenda *proximo,*anterior;
};

bool nomeValido(const char *nome, const char *valChars);
void removerNome(agenda *&nome, agenda *&primeiroNome);
void removerNomeMenu(agenda *&nome, agenda *&primeiroNome);
void inserirNome(agenda *&novo, agenda *&primeiroNome);
void inserirNomeMenu(agenda *&primeiroNome);
void modificarNome(agenda *&nome, agenda *&primeiroNome);
void percorrerNomes(agenda *&primeiroNome);
void buscarPorNome(agenda *&primeiroNome);
void buscarPorEmail(agenda *&primeiroNome);
void buscarPorTelefone(agenda *&primeiroNome);
void modificarRemoverNomeMenu(agenda *&primeiroNome);
void inicializar(agenda *&primeiroNome);
void finalizar(agenda *&primeiroNome);

#endif
