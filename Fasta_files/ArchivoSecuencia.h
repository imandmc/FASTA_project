//
// Created by Juan Salazar on 30/09/22.
//

#ifndef FASTA_PROJECT_ARCHIVOSECUENCIA_H
#define FASTA_PROJECT_ARCHIVOSECUENCIA_H


#include <iostream>
#include <list>
#include <fstream>
#include "Secuencia.h"
#include <map>
#include "Huffman.h"

namespace archivo_secuencia {

    template<class T, class V>
    class ArchivoSecuencia {
    private:
        std::list<T> lista_archivo_secuencias_;
        int cantidad_sec_{};
        std::string nombre_archivo_;
        bool archivo_vacio = true;
        std::list<char> lista_bases_ = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N',
                                        'X', '-'};
        int cantidad_bases_archivo_ = 0;
        std::map<char, std::vector<int>> mapa_;
        std::map<char, int> mapa_freq_;

    public:
        ArchivoSecuencia();


        std::string NombreArchivo();

        ~ArchivoSecuencia();

        void Imprimir();

        void ExportarTxt(std::string nombre_archivo);

        int EsSubsecuencia(std::string subsecuencia);

        int Enmascarar(std::string mascara);

        int Enmascarar(std::string mascara, std::string enmascara);

        explicit ArchivoSecuencia(const std::string &nombre_archivo);

        explicit ArchivoSecuencia(const std::string &nombre_archivo, const int &bin_opcion);

        void HuffmanEncodder();

        std::map<char, int> Mapeo();

        void alistadorSaveFile(std::string nombre_archivo);

        void HuffmanEncodder(std::map<char, int> mapa);
    };


} // archivo_secuencia

#endif //FASTA_PROJECT_ARCHIVOSECUENCIA_H
