#ifndef GESTOR_ESTUDIANTES_H
#define GESTOR_ESTUDIANTES_H

#include "ListaDoble.h"
#include "Estudiante.h"

class GestorEstudiantes {
public:
    static const int MAX_ESTUDIANTES = 20;

    ListaDoble<Estudiante> estudiantes;

    // --- Menú principal ---
    void ejecutar();

private:
    // Submenú opción 1: gestión de estudiantes
    void menuEstudiantes();
    void listarEstudiantes();
    void ingresarEstudiante();
    void modificarEstudiante();
    void eliminarEstudiante();

    // Submenú opción 2: registro de calificaciones
    void menuCalificaciones();

    // Opción 3: promedio individual
    void promedioEstudiante();

    // Opción 4: promedio del curso
    void promedioCurso();

    // Utilidades  -
    int  buscarPorCedula(const std::string& cedula);
    void mostrarDatosEstudiante(const Estudiante& e);
    int  pedirIndiceValido(const std::string& mensaje);
    double pedirNota();
    std::string pedirCedula();
    char pedirSiNo(const std::string& pregunta);
    void limpiarBuffer();
    void pausar();
};

#endif
