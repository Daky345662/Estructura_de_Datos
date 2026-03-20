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
    // Constructor
    ListaDoble() : primero(nullptr), ultimo(nullptr) {}

    // Destructor para liberar memoria
    ~ListaDoble() {
        while (primero != nullptr) {
            eliminar(primero->info);
        }
    }

    void insertarInicio(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        if (primero == nullptr) {
            primero = ultimo = nuevo;
        } else {
            nuevo->sig = primero;
            primero->ant = nuevo;
            primero = nuevo;
        }
    }

    void insertarFinal(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        if (primero == nullptr) {
            primero = ultimo = nuevo;
        } else {
            ultimo->sig = nuevo;
            nuevo->ant = ultimo;
            ultimo = nuevo;
        }
    }

    void mostrarAdelante() {
        NodoDoble<T>* aux = primero;
        cout << "Lista (Adelante): ";
        while (aux != nullptr) {
            cout << aux->info << " <-> ";
            aux = aux->sig;
        }
        cout << "nullptr" << endl;
    }

    void mostrarAtras() {
        NodoDoble<T>* aux = ultimo;
        cout << "Lista (Atrás): ";
        while (aux != nullptr) {
            cout << aux->info << " <-> ";
            aux = aux->ant;
        }
        cout << "nullptr" << endl;
    }

    bool buscar(T valor) {
        NodoDoble<T>* aux = primero;
        while (aux != nullptr) {
            if (aux->info == valor) return true;
            aux = aux->sig;
        }
        return false;
    }

    void eliminar(T valor) {
        NodoDoble<T>* aux = primero;
        while (aux != nullptr && aux->info != valor) {
            aux = aux->sig;
        }

        if (aux == nullptr) return;

        if (aux == primero) {
            primero = aux->sig;
            if (primero != nullptr) primero->ant = nullptr;
        } else {
            aux->ant->sig = aux->sig;
        }

        if (aux == ultimo) {
            ultimo = aux->ant;
            if (ultimo != nullptr) ultimo->sig = nullptr;
        } else if (aux->sig != nullptr) {
            aux->sig->ant = aux->ant;
        }

        delete aux;
    }

    T obtenerPrimero() {
        if (primero != nullptr) return primero->info;
        return T(); 
    }

    T obtenerUltimo() {
        if (ultimo != nullptr) return ultimo->info;
        return T();
    }
};

#endif