//
// Created by Juan Salazar on 30/09/22.
//

#ifndef FASTA_PROJECT_SECUENCIA_H
#define FASTA_PROJECT_SECUENCIA_H

#include <iostream>
#include <list>
#include "Huffman.h"

namespace _secuencia {
    template<class V>
    class Secuencia {
    private:
        std::list<std::string> lista_secuencia_;
        std::list<V> lista_grafos_;
        std::string nombre_secuencia_;
        bool secuencia_correcta = true;
    public:
        Secuencia();

        explicit Secuencia(const std::string &nombre_secuencia);

        ~Secuencia();

        void AgregarLinea(std::string linea);

        void AsignarNombre(std::string nombre_secuencia);

        bool CodigoValido(const char c);

        bool SecuenciaCorrecta();

        void clear();

        void CrearGrafo();

        void Lineas();

        std::string NombreSecuencia();

        std::list<std::string> ListaSecuencia();

        void ActualizarListaSecuencia(std::list<std::string> nueva_lista);
    };

    template<class V>
    Secuencia<V>::Secuencia() = default;

    template<class V>
    Secuencia<V>::Secuencia(const std::string &nombre_secuencia) {
        this->nombre_secuencia_ = nombre_secuencia;
    }

    template<class V>
    void Secuencia<V>::AgregarLinea(std::string linea) {
        std::string::const_iterator it = linea.begin();
        while (it != linea.end() && CodigoValido(*it)) {
            ++it;
        }
        if (!linea.empty() && it == linea.end()) {
            lista_secuencia_.push_back(linea);
        }
    }

    template<class V>
    void Secuencia<V>::AsignarNombre(std::string nombre_secuencia) {
        this->nombre_secuencia_ = nombre_secuencia;
    }

    template<class V>
    bool Secuencia<V>::CodigoValido(const char c) {
        if (c == 'A' || c == 'C' || c == 'G' || c == 'T' ||
            c == 'U' || c == 'R' || c == 'Y' || c == 'K' || c == 'M'
            || c == 'S' || c == 'W' || c == 'B' || c == 'D' || c == 'H' || c == 'N'
            || c == 'X' || c == 'V' || c == '-') {
            return true;
        }
        this->secuencia_correcta = false;
        return false;
    }

    template<class V>
    bool Secuencia<V>::SecuenciaCorrecta() {
        return this->secuencia_correcta;
    }

    template<class V>
    Secuencia<V>::~Secuencia() {
        this->lista_secuencia_.clear();
        this->lista_grafos_.clear();
        this->nombre_secuencia_.clear();
    }

    template<class V>
    void Secuencia<V>::clear() {
        this->lista_secuencia_.clear();
        this->lista_grafos_.clear();
        this->nombre_secuencia_.clear();
    }

    template<class V>
    void Secuencia<V>::CrearGrafo() {
    }

    template<class V>
    void Secuencia<V>::Lineas() {
        std::list<std::string>::iterator it;
        it = this->lista_secuencia_.begin();
        for (; it != this->lista_secuencia_.end(); ++it) {
            std::cout << *it << std::endl;
        }

    }

    template<class V>
    std::string Secuencia<V>::NombreSecuencia() {
        return this->nombre_secuencia_;
    }

    template<class V>
    std::list<std::string> Secuencia<V>::ListaSecuencia() {
        return this->lista_secuencia_;
    }

    template<class V>
    void Secuencia<V>::ActualizarListaSecuencia(std::list<std::string> nueva_lista) {
        this->lista_secuencia_ = nueva_lista;
    }


}

#endif //FASTA_PROJECT_SECUENCIA_H
