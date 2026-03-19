#ifndef NODOBLE_H
#define NODOBLE_H

// Plantilla genérica para el nodo de una lista doblemente enlazada
template <typename T>
class NodoDoble {
public:
    T info;             // Dato almacenado en el nodo
    NodoDoble<T>* sig;  // Puntero al nodo siguiente
    NodoDoble<T>* ant;  // Puntero al nodo anterior

    // Constructor: inicializa el dato y ambos punteros a nullptr
    NodoDoble(T valor) {
        info = valor;
        sig  = nullptr;
        ant  = nullptr;
    }
};

#endif // NODOBLE_H