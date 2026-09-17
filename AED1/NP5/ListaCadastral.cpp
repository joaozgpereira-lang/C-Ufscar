#include "ListaCadastral.hpp"
#include <cstddef>

using namespace std;

void Cria(Lista& L) {
    L.primeiro = NULL;
    L.atual = NULL;
}

bool Vazia(const Lista& L) {
    return (L.primeiro == NULL);
}

bool Cheia(const Lista& L) {
    No* aux = new (nothrow) No;
    if (aux == NULL) {
        return true;
    }
    delete aux;
    return false;
}

bool EstaNaLista(const Lista &L, char X) {
    No* aux = L.primeiro;
    while (aux != NULL) {
        if (aux->dado == X) {
            return true;
        }
        aux = aux->proximo;
    }
    return false;
}

void Insere(Lista& L, char X, bool& ok) {
    if (EstaNaLista(L, X)) {
        ok = false;
        return;
    }
    No* novo = new No;
    novo->dado = X;
    novo->proximo = L.primeiro;
    L.primeiro = novo;
    ok = true;
}

void Remove(Lista& L, char X, bool& ok) {
    if (Vazia(L)) {
        ok = false;
        return;
    }
    No* aux = L.primeiro;
    No* anterior = NULL;
    while (aux != NULL && aux->dado != X) {
        anterior = aux;
        aux = aux->proximo;
    }
    if (aux == NULL) {
        ok = false;
        return;
    }
    if (anterior == NULL) {
        L.primeiro = aux->proximo;
    } else {
        anterior->proximo = aux->proximo;
    }
    delete aux;
    ok = true;
}

void PegaOPrimeiro(Lista& L, char& X, bool& temElemento) {
    if (Vazia(L)) {
        temElemento = false;
        return;
    }
    L.atual = L.primeiro;
    X = L.atual->dado;
    temElemento = true;
}

void PegaOProximo(Lista& L, char& X, bool& temElemento) {
    if (L.atual == NULL || L.atual->proximo == NULL) {
        temElemento = false;
        return;
    }
    L.atual = L.atual->proximo;
    X = L.atual->dado;
    temElemento = true;
}