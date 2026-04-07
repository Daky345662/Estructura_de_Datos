#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <stack>

using namespace std;

struct Solicitud {
    string cedula;
    string nombre;
    string motivo;
};

// 1. Agregar a la cola de espera
void registrarSolicitud(queue<Solicitud>& cola, const Solicitud& s) {
    cola.push(s);          
    cout << ">> [REGISTRO] Ingresado a la fila: " << s.nombre << "\n";
}

// 2. Atender (Verificar FIFO en pendientes)
void atenderSolicitud(queue<Solicitud>& cola, list<Solicitud>& historialList, stack<Solicitud>& historialStack) {
    // CASO DE PRUEBA: Cola vacía
    if (cola.empty()) {
        cout << ">> [ALERTA - Cola vacia] No hay estudiantes en la fila para atender.\n";
        return;
    }

    // CASO DE PRUEBA: FIFO (Se atiende al primero que llego)
    Solicitud atendida = cola.front();
    cola.pop(); 

    // Guardamos en ambos historiales para las pruebas
    historialList.push_back(atendida); // List: Orden completo (cronológico)
    historialStack.push(atendida);     // Stack: Recientes (LIFO)

    cout << "\n========================================\n";
    cout << ">>> ATENDIENDO A: " << atendida.nombre << "\n";
    cout << "    C.I: " << atendida.cedula << "\n";
    cout << "    Motivo: " << atendida.motivo << "\n";
    cout << "========================================\n";
}

// 3. Revisar orden completo en list
void mostrarHistorialList(const list<Solicitud>& historialList) {
    cout << "\n--- CASO: HISTORIAL COMPLETO (List) ---\n";
    if (historialList.empty()) {
        cout << "El historial esta vacio.\n";
        return;
    }
    
    // Imprime en el orden exacto en el que fueron atendidos
    int contador = 1;
    for (const auto& s : historialList) {
        cout << contador++ << ". " << s.nombre << " (C.I: " << s.cedula << ")\n";
    }
}

// 4. Confirmar que el ultimo atendido queda arriba en stack
void mostrarRecientesStack(stack<Solicitud> historialStack) {
    cout << "\n--- CASO: RECIENTES (Stack) ---\n";
    if (historialStack.empty()) {
        cout << "No hay recientes.\n";
        return;
    }
    
    cout << "[ARRIBA - ULTIMO ATENDIDO]\n";
    while (!historialStack.empty()) {
        Solicitud s = historialStack.top();
        cout << "-> " << s.nombre << " (C.I: " << s.cedula << ")\n";
        historialStack.pop();
    }
    cout << "[FONDO - PRIMER ATENDIDO]\n";
}

int main() {
    queue<Solicitud> colaEspera;
    list<Solicitud> historialList;
    stack<Solicitud> historialStack;

    int opcion;

    do {
        cout << "\n--- MENU DE CASOS DE PRUEBA ---\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Intentar atender \n";
        cout << "3. Revisar orden completo\n";
        cout << "4. Revisar recientes\n";
        cout << "5. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1: {
                Solicitud nuevaSol;
                cout << "Cedula: ";
                getline(cin, nuevaSol.cedula);
                cout << "Nombre: ";
                getline(cin, nuevaSol.nombre);
                cout << "Motivo: ";
                getline(cin, nuevaSol.motivo);

                registrarSolicitud(colaEspera, nuevaSol);
                break;
            }
            case 2:
                atenderSolicitud(colaEspera, historialList, historialStack);
                break;
            case 3:
                mostrarHistorialList(historialList);
                break;
            case 4:
                mostrarRecientesStack(historialStack);
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);

    return 0;
}