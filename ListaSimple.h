#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>
#include "nodoSimple.h"
using namespace std;

template <typename T>
class ListaSimple {
private:
    NodoSimple<T>* primero;
    NodoSimple<T>* ultimo;

public:
    ListaSimple() {
        primero = NULL;
        ultimo = NULL;
    }

    // Insertar al inicio
    void insertarInicio(T dato) {
        NodoSimple<T>* nuevo = new NodoSimple<T>(dato);

        if (primero == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            nuevo->sig = primero;
            primero = nuevo;
        }
    }

    // Insertar al final
    void insertarFinal(T dato) {
        NodoSimple<T>* nuevo = new NodoSimple<T>(dato);

        if (primero == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->sig = nuevo;
            ultimo = nuevo;
        }
    }

    // Buscar elemento
    bool buscar(T dato) {
        NodoSimple<T>* aux = primero;

        while (aux != NULL) {
            if (aux->info == dato) {
                return true;
            }
            aux = aux->sig;
        }
        return false;
    }

    // Eliminar elemento
    void eliminar(T dato) {
        if (primero == NULL) return;

        NodoSimple<T>* aux = primero;
        NodoSimple<T>* anterior = NULL;

        while (aux != NULL && aux->info != dato) {
            anterior = aux;
            aux = aux->sig;
        }

        if (aux == NULL) return;

        if (aux == primero) {
            primero = primero->sig;
            if (primero == NULL) {
                ultimo = NULL;
            }
        } else {
            anterior->sig = aux->sig;
            if (aux == ultimo) {
                ultimo = anterior;
            }
        }

        delete aux;
    }

    // Mostrar lista
    void mostrar() {
        NodoSimple<T>* aux = primero;

        while (aux != NULL) {
            cout << aux->info << " -> ";
            aux = aux->sig;
        }
        cout << "NULL" << endl;
    }

    // Consultar primero
    T obtenerPrimero() {
        return primero->info;
    }

    // Consultar ultimo
    T obtenerUltimo() {
        return ultimo->info;
    }
};

#endif