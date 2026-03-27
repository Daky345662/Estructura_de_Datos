#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;

    Nodo(T dato) : dato(dato), anterior(nullptr), siguiente(nullptr) {}
};

#endif