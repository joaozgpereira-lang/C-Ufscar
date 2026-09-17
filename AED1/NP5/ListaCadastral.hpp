#ifndef LISTA_CADASTRAL_HPP
#define LISTA_CADASTRAL_HPP

#include <iostream>

struct No {
    char dado;
    No* proximo;
};

struct Lista {
    No* primeiro;
    No* atual;
};

void Cria(Lista& L);
bool Vazia(const Lista& L);
bool Cheia(const Lista& L);
bool EstaNaLista(const Lista &L, char c);
void Insere(Lista& L, char X, bool& ok);
void Remove(Lista& L, char X, bool& ok);
void PegaOPrimeiro(Lista& L, char& X, bool& temElemento);
void PegaOProximo(Lista& L, char& X, bool& temElemento);

#endif