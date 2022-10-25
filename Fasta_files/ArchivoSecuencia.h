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

        int Enmascarar(const std::string &mascara, std::string enmascara);

        explicit ArchivoSecuencia(std::string &nombre_archivo);

        explicit ArchivoSecuencia(std::string &nombre_archivo, const int &bin_opcion);

        void HuffmanEncodder();

        std::map<char, int> Mapeo();

        void alistadorSaveFile(std::string nombre_archivo);

        void HuffmanEncodder(std::map<char, int> mapa);

        ArchivoSecuencia &operator=(ArchivoSecuencia<T, V> const &obj) {
            this->lista_archivo_secuencias_ = obj.lista_archivo_secuencias_;
            this->mapa_freq_ = obj.mapa_freq_;
            this->mapa_ = obj.mapa_;
            this->nombre_archivo_ = obj.nombre_archivo_;
            this->archivo_vacio = false;
            this->cantidad_bases_archivo_ = obj.cantidad_bases_archivo_;
            this->cantidad_sec_ = obj.cantidad_sec_;
            return *this;
        }

        ArchivoSecuencia(const ArchivoSecuencia<T, V> &obj) {
            this->lista_archivo_secuencias_ = obj.lista_archivo_secuencias_;
            this->mapa_freq_ = obj.mapa_freq_;
            this->mapa_ = obj.mapa_;
            this->nombre_archivo_ = obj.nombre_archivo_;
            this->archivo_vacio = false;
            this->cantidad_bases_archivo_ = obj.cantidad_bases_archivo_;
            this->cantidad_sec_ = obj.cantidad_sec_;
        }
    };


} // archivo_secuencia

#endif //FASTA_PROJECT_ARCHIVOSECUENCIA_H
