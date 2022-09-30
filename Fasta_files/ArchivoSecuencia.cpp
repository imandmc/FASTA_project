//
// Created by Juan Salazar on 30/09/22.
//

#include "ArchivoSecuencia.h"

#include <utility>


namespace archivo_secuencia {


    template<class T, class U>
    ArchivoSecuencia<T, U>::ArchivoSecuencia() {
        int cantidad_sec = 0;
    }

    template<class T, class U>
    ArchivoSecuencia<T, U>::ArchivoSecuencia(std::string nombre_archivo) {
        nombre_archivo_ = std::move(nombre_archivo);
        int cantidad_sec = 5;
        std::ifstream archivo_lectura(nombre_archivo_.c_str());
        std::string linea2;
        getline(archivo_lectura, linea2);
        std::cout << linea2 << std::endl;
        bool check_pass = archivo_lectura.good();
        std::cout << check_pass << std::endl;
        if (check_pass) {
            std::string linea_lectura;
            while (getline(archivo_lectura, linea_lectura)) {
                char check_secuencia = linea_lectura[0];
                if (check_secuencia == '>') {
                    std::cout << "Si!" << std::endl;
                }
            }
            std::cout << linea_lectura << std::endl;
        } else {
            std::cout << "No existe el archivo " << std::endl;
            nombre_archivo_.clear();
        }
    }

} // archivo_secuencia