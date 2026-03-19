#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>
using namespace std;

template <typename T>
class ListaSimple {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;

public:
    ListaSimple() {
        primero = NULL;
        ultimo = NULL;
    }

    // Insertar al inicio
    void insertarInicio(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);

        if (primero == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            nuevo->next = primero;
            primero = nuevo;
        }
    }

    // Insertar al final
    void insertarFinal(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);

        if (primero == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->next = nuevo;
            ultimo = nuevo;
        }
    }

    // Buscar elemento
    bool buscar(T dato) {
        Nodo<T>* aux = primero;

        while (aux != NULL) {
            if (aux->info == dato) {
                return true;
            }
            aux = aux->next;
        }
        return false;
    }

    // Eliminar elemento
    void eliminar(T dato) {
        if (primero == NULL) return;

        Nodo<T>* aux = primero;
        Nodo<T>* anterior = NULL;

        while (aux != NULL && aux->info != dato) {
            anterior = aux;
            aux = aux->next;
        }

        if (aux == NULL) return;

        if (aux == primero) {
            primero = primero->next;
            if (primero == NULL) {
                ultimo = NULL;
            }
        } else {
            anterior->next = aux->next;
            if (aux == ultimo) {
                ultimo = anterior;
            }
        }

        delete aux;
    }

    // Mostrar lista
    void mostrar() {
        Nodo<T>* aux = primero;

        while (aux != NULL) {
            cout << aux->info << " -> ";
            aux = aux->next;
        }
        cout << "NULL" << endl;
    }

    // Consultar primero
    T getPrimero() {
        return primero->info;
    }

    // Consultar ultimo
    T getUltimo() {
        return ultimo->info;
    }
};

#endif