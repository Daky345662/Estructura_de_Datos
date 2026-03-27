#include "GestorEstudiantes.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

// ============================================================
// Menú principal ...
// ============================================================
void GestorEstudiantes::ejecutar() {
    int opcion;
    do {
        std::cout << "\n=== GESTOR DE ESTUDIANTES ===\n";
        std::cout << "1. Estudiantes\n";
        std::cout << "2. Registro de calificaciones\n";
        std::cout << "3. Determinar el promedio de notas de un estudiante\n";
        std::cout << "4. Determinar el promedio de notas del curso\n";
        std::cout << "0. Salir\n";
        std::cout << "Teclee su opcion (0-4): ";
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: menuEstudiantes();    break;
            case 2: menuCalificaciones(); break;
            case 3: promedioEstudiante(); break;
            case 4: promedioCurso();      break;
            case 0: std::cout << "Hasta luego.\n"; break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

// ============================================================
// Opción 1 — Submenú de estudiantes
// ============================================================
void GestorEstudiantes::menuEstudiantes() {
    int opcion;
    do {
        std::cout << "\n--- GESTION DE ESTUDIANTES ---\n";
        listarEstudiantes();
        std::cout << "\n1. Ingresar estudiante\n";
        std::cout << "2. Modificar estudiante\n";
        std::cout << "3. Eliminar estudiante\n";
        std::cout << "0. Volver al menu principal\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: ingresarEstudiante();   break;
            case 2: modificarEstudiante();  break;
            case 3: eliminarEstudiante();   break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void GestorEstudiantes::listarEstudiantes() {
    if (estudiantes.estaVacia()) {
        std::cout << "(No hay estudiantes registrados)\n";
        return;
    }
    std::cout << "\n"
              << std::left
              << std::setw(4)  << "#"
              << std::setw(14) << "Cedula"
              << std::setw(22) << "Nombres"
              << std::setw(22) << "Apellidos"
              << std::setw(12) << "Nacimiento"
              << "Notas\n";
    std::cout << std::string(80, '-') << "\n";

    for (int i = 0; i < estudiantes.tamano(); i++) {
        const Estudiante& e = estudiantes.obtener(i);
        std::cout << std::left
                  << std::setw(4)  << (i + 1)
                  << std::setw(14) << e.cedula
                  << std::setw(22) << e.nombres
                  << std::setw(22) << e.apellidos
                  << std::setw(12) << e.fechaNacimiento
                  << e.notas.tamano() << "/" << Estudiante::MAX_NOTAS
                  << "\n";
    }
}

void GestorEstudiantes::ingresarEstudiante() {
    char repetir;
    do {
        if (estudiantes.tamano() >= MAX_ESTUDIANTES) {
            std::cout << "Se alcanzo el cupo maximo de " << MAX_ESTUDIANTES << " estudiantes.\n";
            return;
        }

        Estudiante e;
        std::cout << "\n-- Ingreso de nuevo estudiante --\n";
        std::cout << "Cedula     : "; std::getline(std::cin, e.cedula);
        std::cout << "Nombres    : "; std::getline(std::cin, e.nombres);
        std::cout << "Apellidos  : "; std::getline(std::cin, e.apellidos);
        std::cout << "Nacimiento (DD/MM/YYYY): "; std::getline(std::cin, e.fechaNacimiento);

        estudiantes.insertar(e);
        std::cout << "Estudiante registrado correctamente.\n";

        repetir = pedirSiNo("Desea ingresar otro estudiante? (s/n): ");
    } while (repetir == 's' || repetir == 'S');
}

void GestorEstudiantes::modificarEstudiante() {
    if (estudiantes.estaVacia()) {
        std::cout << "No hay estudiantes registrados para modificar.\n";
        return;
    }
    char repetir;
    do {
        listarEstudiantes();
        int idx = pedirIndiceValido("Ingrese el # del estudiante a modificar (0 para cancelar): ");
        if (idx == 0) return;

        Estudiante& e = estudiantes.obtener(idx - 1);
        std::cout << "\nDeje en blanco para conservar el valor actual.\n";

        std::string tmp;
        std::cout << "Cedula [" << e.cedula << "]: ";
        std::getline(std::cin, tmp);
        if (!tmp.empty()) e.cedula = tmp;

        std::cout << "Nombres [" << e.nombres << "]: ";
        std::getline(std::cin, tmp);
        if (!tmp.empty()) e.nombres = tmp;

        std::cout << "Apellidos [" << e.apellidos << "]: ";
        std::getline(std::cin, tmp);
        if (!tmp.empty()) e.apellidos = tmp;

        std::cout << "Nacimiento [" << e.fechaNacimiento << "]: ";
        std::getline(std::cin, tmp);
        if (!tmp.empty()) e.fechaNacimiento = tmp;

        std::cout << "Estudiante modificado.\n";
        repetir = pedirSiNo("Desea modificar otro estudiante? (s/n): ");
    } while (repetir == 's' || repetir == 'S');
}

void GestorEstudiantes::eliminarEstudiante() {
    if (estudiantes.estaVacia()) {
        std::cout << "No hay estudiantes registrados para eliminar.\n";
        return;
    }
    char repetir;
    do {
        listarEstudiantes();
        int idx = pedirIndiceValido("Ingrese el # del estudiante a eliminar (0 para cancelar): ");
        if (idx == 0) return;

        std::cout << "Se eliminara: " << estudiantes.obtener(idx - 1).nombreCompleto() << "\n";
        char conf = pedirSiNo("Confirma la eliminacion? (s/n): ");
        if (conf == 's' || conf == 'S') {
            estudiantes.eliminar(idx - 1);
            std::cout << "Estudiante eliminado.\n";
        }

        if (estudiantes.estaVacia()) {
            std::cout << "No quedan estudiantes registrados.\n";
            return;
        }
        repetir = pedirSiNo("Desea eliminar otro estudiante? (s/n): ");
    } while (repetir == 's' || repetir == 'S');
}

// ============================================================
// Opción 2 — Registro de calificaciones
// ============================================================
void GestorEstudiantes::menuCalificaciones() {
    std::string cedula;
    bool continuar = true;

    while (continuar) {
        std::cout << "\n-- REGISTRO DE CALIFICACIONES --\n";
        std::cout << "Cedula del estudiante (0 para volver): ";
        std::getline(std::cin, cedula);
        if (cedula == "0") return;

        int idx = buscarPorCedula(cedula);
        if (idx == -1) {
            std::cout << "No se encontro un estudiante con cedula: " << cedula << "\n";
            char op = pedirSiNo("Desea ingresar otra cedula? (s/n): ");
            continuar = (op == 's' || op == 'S');
            continue;
        }

        Estudiante& e = estudiantes.obtener(idx);
        mostrarDatosEstudiante(e);

        // Submenú de notas
        int opcion;
        bool salirNotas = false;
        while (!salirNotas) {
            std::cout << "\nCalificaciones actuales (" << e.notas.tamano() << "/" << Estudiante::MAX_NOTAS << "):\n";
            if (e.notas.estaVacia()) {
                std::cout << "  (Ninguna registrada)\n";
            } else {
                for (int i = 0; i < e.notas.tamano(); i++)
                    std::cout << "  " << (i + 1) << ". " << std::fixed << std::setprecision(2) << e.notas.obtener(i) << "\n";
            }

            if (e.notasCompletas()) {
                std::cout << "Se han ingresado todas las calificaciones posibles.\n";
                salirNotas = true;
                break;
            }

            std::cout << "\n1. Insertar calificacion\n";
            std::cout << "2. Modificar calificacion\n";
            std::cout << "3. Eliminar calificacion\n";
            std::cout << "0. Volver\n";
            std::cout << "Opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    double nota = pedirNota();
                    e.notas.insertar(nota);
                    std::cout << "Calificacion registrada.\n";
                    if (e.notasCompletas())
                        std::cout << "Se han ingresado todas las calificaciones posibles.\n";
                    break;
                }
                case 2: {
                    if (e.notas.estaVacia()) { std::cout << "No hay calificaciones para modificar.\n"; break; }
                    int ni = pedirIndiceValido("# de calificacion a modificar: ");
                    if (ni < 1 || ni > e.notas.tamano()) { std::cout << "Indice invalido.\n"; break; }
                    double nota = pedirNota();
                    e.notas.obtener(ni - 1) = nota;
                    std::cout << "Calificacion modificada.\n";
                    break;
                }
                case 3: {
                    if (e.notas.estaVacia()) { std::cout << "No hay calificaciones para eliminar.\n"; break; }
                    int ni = pedirIndiceValido("# de calificacion a eliminar: ");
                    if (ni < 1 || ni > e.notas.tamano()) { std::cout << "Indice invalido.\n"; break; }
                    e.notas.eliminar(ni - 1);
                    std::cout << "Calificacion eliminada.\n";
                    break;
                }
                case 0: salirNotas = true; break;
                default: std::cout << "Opcion invalida.\n";
            }
        }
        continuar = false; // volver al menú principal después de gestionar un estudiante
    }
}

// ============================================================
// Opción 3 — Promedio individual
// ============================================================
void GestorEstudiantes::promedioEstudiante() {
    std::cout << "\n-- PROMEDIO DE UN ESTUDIANTE --\n";
    std::cout << "Cedula: ";
    std::string cedula;
    std::getline(std::cin, cedula);

    int idx = buscarPorCedula(cedula);
    if (idx == -1) {
        std::cout << "No se encontro un estudiante con cedula: " << cedula << "\n";
        return;
    }

    const Estudiante& e = estudiantes.obtener(idx);
    mostrarDatosEstudiante(e);

    if (e.notas.estaVacia()) {
        std::cout << "El estudiante no tiene calificaciones registradas.\n";
    } else {
        std::cout << "Promedio de calificaciones: "
                  << std::fixed << std::setprecision(2) << e.calcularPromedio() << "\n";
    }
}

// ============================================================
// Opción 4 — Promedio del curso
// ============================================================
void GestorEstudiantes::promedioCurso() {
    std::cout << "\n-- PROMEDIO GENERAL DEL CURSO --\n";

    double suma = 0.0;
    int totalNotas = 0;

    for (int i = 0; i < estudiantes.tamano(); i++) {
        const Estudiante& e = estudiantes.obtener(i);
        for (int j = 0; j < e.notas.tamano(); j++) {
            suma += e.notas.obtener(j);
            totalNotas++;
        }
    }

    if (totalNotas == 0) {
        std::cout << "No se han registrado calificaciones de estudiantes.\n";
    } else {
        std::cout << "Promedio general del curso: "
                  << std::fixed << std::setprecision(2) << (suma / totalNotas) << "\n";
        std::cout << "(Calculado sobre " << totalNotas << " calificacion(es) de "
                  << estudiantes.tamano() << " estudiante(s))\n";
    }
}

// ============================================================
// Utilidades privadas
// ============================================================
int GestorEstudiantes::buscarPorCedula(const std::string& cedula) {
    for (int i = 0; i < estudiantes.tamano(); i++) {
        if (estudiantes.obtener(i).cedula == cedula)
            return i;
    }
    return -1;
}

void GestorEstudiantes::mostrarDatosEstudiante(const Estudiante& e) {
    std::cout << "\nEstudiante: " << e.nombreCompleto()
              << " | Edad: " << e.calcularEdad() << " anios"
              << " | Cedula: " << e.cedula << "\n";
}

int GestorEstudiantes::pedirIndiceValido(const std::string& mensaje) {
    int idx;
    std::cout << mensaje;
    while (!(std::cin >> idx)) {
        std::cout << "Valor invalido. Intente de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    limpiarBuffer();
    return idx;
}

double GestorEstudiantes::pedirNota() {
    double nota;
    std::cout << "Ingrese la calificacion (0.0 - 10.0): ";
    while (!(std::cin >> nota) || nota < 0.0 || nota > 10.0) {
        std::cout << "Valor invalido. Ingrese un numero entre 0.0 y 10.0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    limpiarBuffer();
    return nota;
}

char GestorEstudiantes::pedirSiNo(const std::string& pregunta) {
    char c;
    std::cout << pregunta;
    std::cin >> c;
    limpiarBuffer();
    return c;
}

void GestorEstudiantes::limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void GestorEstudiantes::pausar() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}
