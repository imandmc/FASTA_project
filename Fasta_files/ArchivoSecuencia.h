//
// Created by Juan Salazar on 30/09/22.
//

#ifndef FASTA_PROJECT_ARCHIVOSECUENCIA_H
#define FASTA_PROJECT_ARCHIVOSECUENCIA_H


#include <iostream>
#include <list>
#include <fstream>
#include "Secuencia.h"

namespace archivo_secuencia {

    template<class T, class V>
    class ArchivoSecuencia {
    private:
        std::list<T> lista_archivo_secuencias_;
        int cantidad_sec_{};
        std::string nombre_archivo_;
        bool archivo_vacio = true;

    public:
        ArchivoSecuencia();

        void ExportarFa();

        std::string NombreArchivo();

        ~ArchivoSecuencia();

        void Imprimir();

        void ExportarTxt(std::string nombre_archivo);

        int EsSubsecuencia(std::string subsecuencia);

        int Enmascarar(std::string mascara);

        explicit ArchivoSecuencia(const std::string &nombre_archivo);

    };


} // archivo_secuencia

#endif //FASTA_PROJECT_ARCHIVOSECUENCIA_H
