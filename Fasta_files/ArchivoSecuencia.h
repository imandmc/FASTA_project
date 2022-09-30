//
// Created by Juan Salazar on 30/09/22.
//

#ifndef FASTA_PROJECT_ARCHIVOSECUENCIA_H
#define FASTA_PROJECT_ARCHIVOSECUENCIA_H


#include <iostream>
#include <list>
#include <fstream>

namespace archivo_secuencia {

    template<class T, class U>
    class ArchivoSecuencia {
    private:
        std::list<T> lista_archivo_secuencias_;
        std::list<U> lista_archivo_grafos_;
        int cantidad_sec_;
        std::string nombre_archivo_;

        bool ExisteArchivoBool(std::string const &name);

    public:
        ArchivoSecuencia();

        ArchivoSecuencia(std::string nombre_archivo);

    };


} // archivo_secuencia

#endif //FASTA_PROJECT_ARCHIVOSECUENCIA_H
