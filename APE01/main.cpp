#include <iostream>
#include "ListaSimple.h"
#include "ListaDoble.h"

using namespace std;

int main() {

    cout << "===== LISTA SIMPLE (int) =====" << endl;
    ListaSimple<int> lista1;

    lista1.insertarInicio(10);
    lista1.insertarFinal(20);
    lista1.insertarFinal(30);

    lista1.mostrar();

    cout << "Buscar 20: " << lista1.buscar(20) << endl;

    lista1.eliminar(20);
    lista1.mostrar();

    cout << "Primero: " << lista1.obtenerPrimero() << endl;
    cout << "Ultimo: " << lista1.obtenerUltimo() << endl;


    cout << "\n===== LISTA DOBLE (string) =====" << endl;
    ListaDoble<string> lista2;

    lista2.insertarInicio("Juan");
    lista2.insertarFinal("Maria");
    lista2.insertarFinal("Pedro");

    lista2.mostrarAdelante();
    lista2.mostrarAtras();

    cout << "Buscar Maria: " << lista2.buscar("Maria") << endl;

    lista2.eliminar("Maria");

    lista2.mostrarAdelante();

    cout << "Primero: " << lista2.obtenerPrimero() << endl;
    cout << "Ultimo: " << lista2.obtenerUltimo() << endl;

    return 0;
}