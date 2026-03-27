#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include "NodoDoble.h"

using namespace std;

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* primero;
    NodoDoble<T>* ultimo;

public:
    ListaDoble() {
        primero = NULL;
        ultimo = NULL;
    }

    void insertarInicio(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);

        if (primero == NULL) {
            primero = ultimo = nuevo;
        } else {
            nuevo->sig = primero;
            primero->ant = nuevo;
            primero = nuevo;
        }
    }

    void insertarFinal(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);

        if (primero == NULL) {
            primero = ultimo = nuevo;
        } else {
            ultimo->sig = nuevo;
            nuevo->ant = ultimo;
            ultimo = nuevo;
        }
    }

    void mostrarAdelante() {
        NodoDoble<T>* aux = primero;
        while (aux != NULL) {
            cout << aux->info << " <-> ";
            aux = aux->sig;
        }
        cout << "NULL" << endl;
    }

    void mostrarAtras() {
        NodoDoble<T>* aux = ultimo;
        while (aux != NULL) {
            cout << aux->info << " <-> ";
            aux = aux->ant;
        }
        cout << "NULL" << endl;
    }

    bool buscar(T valor) {
        NodoDoble<T>* aux = primero;
        while (aux != NULL) {
            if (aux->info == valor) return true;
            aux = aux->sig;
        }
        return false;
    }

    void eliminar(T valor) {
        NodoDoble<T>* aux = primero;

        while (aux != NULL && aux->info != valor) {
            aux = aux->sig;
        }

        if (aux == NULL) return;

        if (aux == primero) {
            primero = aux->sig;
            if (primero != NULL)
                primero->ant = NULL;
        } else {
            aux->ant->sig = aux->sig;
        }

        if (aux == ultimo) {
            ultimo = aux->ant;
        } else if (aux->sig != NULL) {
            aux->sig->ant = aux->ant;
        }

        delete aux;
    }

    T obtenerPrimero() {
        return primero->info;
    }

    T obtenerUltimo() {
        return ultimo->info;
    }
};

#endif