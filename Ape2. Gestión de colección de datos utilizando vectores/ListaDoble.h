#ifndef LISTADOBLEH
#define LISTADOBLEH

#include "Nodo.h"
#include <stdexcept>

template <typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tam;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr), tam(0) {}

    ~ListaDoble() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    // Insertar al final
    void insertar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = cola = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tam++;
    }

    // Eliminar por índice (0-based)
    void eliminar(int indice) {
        if (indice < 0 || indice >= tam)
            throw std::out_of_range("Indice fuera de rango");

        Nodo<T>* actual = obtenerNodo(indice);

        if (actual->anterior != nullptr)
            actual->anterior->siguiente = actual->siguiente;
        else
            cabeza = actual->siguiente;

        if (actual->siguiente != nullptr)
            actual->siguiente->anterior = actual->anterior;
        else
            cola = actual->anterior;

        delete actual;
        tam--;
    }

    // Obtener elemento por índice (0-based)
    T& obtener(int indice) {
        return obtenerNodo(indice)->dato;
    }

    const T& obtener(int indice) const {
        return obtenerNodo(indice)->dato;
    }

    int tamano() const { return tam; }

    bool estaVacia() const { return tam == 0; }

private:
    Nodo<T>* obtenerNodo(int indice) const {
        if (indice < 0 || indice >= tam)
            throw std::out_of_range("Indice fuera de rango");

        Nodo<T>* actual;
        if (indice <= tam / 2) {
            actual = cabeza;
            for (int i = 0; i < indice; i++)
                actual = actual->siguiente;
        } else {
            actual = cola;
            for (int i = tam - 1; i > indice; i--)
                actual = actual->anterior;
        }
        return actual;
    }
};

#endif
