#ifndef NODOSIMPLE_H
#define NODOSIMPLE_H

using namespace std;

template <typename T>
struct NodoSimple {
    T info;                // Dato que almacena el nodo
    NodoSimple<T>* sig;   // Puntero al siguiente nodo

    // Constructor
    NodoSimple(T valor) {
        info = valor;
        sig = NULL;
    }
};

#endif