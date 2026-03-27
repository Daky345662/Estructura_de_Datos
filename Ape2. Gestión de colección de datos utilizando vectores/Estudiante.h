#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <ctime>
#include "ListaDoble.h"

class Estudiante {
public:
    static const int MAX_NOTAS = 7;

    std::string cedula;
    std::string nombres;
    std::string apellidos;
    std::string fechaNacimiento; // formato DD/MM/YYYY

    ListaDoble<double> notas;

    Estudiante() {}

    Estudiante(const std::string& cedula,
               const std::string& nombres,
               const std::string& apellidos,
               const std::string& fechaNacimiento)
        : cedula(cedula), nombres(nombres),
          apellidos(apellidos), fechaNacimiento(fechaNacimiento) {}

    // Calcula la edad en años a partir de fechaNacimiento (DD/MM/YYYY)
    int calcularEdad() const {
        if (fechaNacimiento.size() < 10) return 0;
        try {
            int dia  = std::stoi(fechaNacimiento.substr(0, 2));
            int mes  = std::stoi(fechaNacimiento.substr(3, 2));
            int anio = std::stoi(fechaNacimiento.substr(6, 4));

            time_t t  = time(nullptr);
            tm* hoy   = localtime(&t);
            int aAct  = hoy->tm_year + 1900;
            int mAct  = hoy->tm_mon + 1;
            int dAct  = hoy->tm_mday;

            int edad = aAct - anio;
            if (mAct < mes || (mAct == mes && dAct < dia))
                edad--;
            return edad;
        } catch (...) {
            return 0;
        }
    }

    double calcularPromedio() const {
        if (notas.estaVacia()) return 0.0;
        double suma = 0.0;
        for (int i = 0; i < notas.tamano(); i++)
            suma += notas.obtener(i);
        return suma / notas.tamano();
    }

    bool notasCompletas() const {
        return notas.tamano() >= MAX_NOTAS;
    }

    std::string nombreCompleto() const {
        return nombres + " " + apellidos;
    }
};

#endif
