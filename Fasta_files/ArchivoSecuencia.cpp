//
// Created by Juan Salazar on 30/09/22.
//

#include "ArchivoSecuencia.h"
#include <utility>
#include <list>
#include <regex>


namespace archivo_secuencia {


    template<class T, class V>
    ArchivoSecuencia<T, V>::ArchivoSecuencia() = default;

    template<class T, class V>
    ArchivoSecuencia<T, V>::ArchivoSecuencia(const std::string &nombre_archivo) {
        nombre_archivo_ = nombre_archivo;
        std::cout << this->nombre_archivo_ << std::endl;
        std::ifstream archivo_lectura(nombre_archivo_);
        bool check_pass = archivo_lectura.good();
        if (check_pass) {
            std::string linea_lectura;
            this->cantidad_sec_ = 0;
            std::list<T> lista_entrada;
            std::list<std::string> lista_lineas_entrada;
            while (getline(archivo_lectura, linea_lectura)) {
                char check_secuencia = linea_lectura[0];
                if (check_secuencia == '>') {
                    bool secuencia_vacia = true;
                    _secuencia::Secuencia<V> secuencia_entrada;
                    secuencia_entrada.AsignarNombre(linea_lectura.substr(1));
                    std::string linea_lectura_lineas;
                    int position = archivo_lectura.tellg();
                    while (getline(archivo_lectura, linea_lectura_lineas)) {
                        check_secuencia = linea_lectura_lineas[0];
                        if (check_secuencia != '>') {
                            secuencia_entrada.AgregarLinea(linea_lectura_lineas);
                            secuencia_vacia = false;
                            position = archivo_lectura.tellg();
                        } else {
                            if (secuencia_entrada.SecuenciaCorrecta() && !secuencia_vacia) {
                                secuencia_entrada.CrearGrafo();
                                lista_entrada.push_back(secuencia_entrada);
                                this->cantidad_sec_ += 1;
                            } else {
                                secuencia_entrada.clear();
                            }
                            archivo_lectura.seekg(position);
                            break;
                        }
                    }
                }
            }
            if (this->cantidad_sec_ > 0) {
                this->lista_archivo_secuencias_ = lista_entrada;
                this->archivo_vacio = false;
            }
        } else {
            std::cout << "No existe el archivo " << std::endl;
            nombre_archivo_.clear();
            return;
        }

        std::cout << "Archivo " << this->nombre_archivo_ << " leído, " << this->cantidad_sec_
                  << " secuencias encontradas." << std::endl;
    }

    template<class T, class V>
    void ArchivoSecuencia<T, V>::ExportarFa() {
        std::ofstream file_obj;
        file_obj.open("export.fa", std::ios::binary);
        file_obj.write((char *) this, sizeof(this));
    }

    template<class T, class V>
    std::string ArchivoSecuencia<T, V>::NombreArchivo() {
        return this->nombre_archivo_;
    }

    template<class T, class V>
    ArchivoSecuencia<T, V>::~ArchivoSecuencia() {
        this->nombre_archivo_.clear();
        this->lista_archivo_secuencias_.clear();
    }

    template<class T, class V>
    void ArchivoSecuencia<T, V>::Imprimir() {
        std::list<_secuencia::Secuencia<int>>::iterator it;
        it = this->lista_archivo_secuencias_.begin();
        for (; it != this->lista_archivo_secuencias_.end(); ++it) {
            std::cout << it->NombreSecuencia() << std::endl;
            it->Lineas();
        }
    }

    template<class T, class V>
    void ArchivoSecuencia<T, V>::ExportarTxt(std::string nombre_archivo) {
        if (this->archivo_vacio) std::cout << "Archivo vacío! No hay secuencias para guardar." << std::endl;
        std::ofstream file_obj;
        std::string check_nombre_archivo;
        check_nombre_archivo = nombre_archivo.substr(nombre_archivo.size() - 4);
        if (check_nombre_archivo != ".txt") {
            nombre_archivo += ".txt";
        }
        file_obj.open(nombre_archivo, std::ofstream::out);
        std::list<_secuencia::Secuencia<int>>::iterator it;
        it = this->lista_archivo_secuencias_.begin();
        std::list<std::string>::iterator its;
        for (it; it != this->lista_archivo_secuencias_.end(); ++it) {
            file_obj << ">";
            file_obj << it->NombreSecuencia();
            file_obj << std::endl;
            std::list<std::string> lista_string;
            lista_string = it->ListaSecuencia();
            for (its = lista_string.begin(); its != lista_string.end(); ++its) {
                file_obj << *its;
                file_obj << std::endl;
            }
        }
        file_obj.close();
        std::cout << "Escritura exitosa en " << nombre_archivo << std::endl;
    }

    template<class T, class V>
    int ArchivoSecuencia<T, V>::EsSubsecuencia(std::string subsecuencia) {
        if (this->archivo_vacio) {
            return 0;
        }
        int contador = 0;
        typename std::list<_secuencia::Secuencia<V>>::iterator it;
        it = this->lista_archivo_secuencias_.begin();
        std::list<std::string>::iterator its;
        for (; it != this->lista_archivo_secuencias_.end(); ++it) {
            std::list<std::string> lista_string;
            lista_string = it->ListaSecuencia();
            for (its = lista_string.begin(); its != lista_string.end(); ++its) {
                int N = its->length();
                int M = subsecuencia.length();
                for (int i = 0; i <= N - M; i++) {
                    int j;
                    for (j = 0; j < M; j++) {
                        std::string check = *its;
                        if (check[i + j] != subsecuencia[j]) break;
                    }
                    if (j == M) {
                        contador++;
                    }
                }
            }
        }
        return contador;
    }

    template<class T, class V>
    int ArchivoSecuencia<T, V>::Enmascarar(std::string mascara) {
        int contador = EsSubsecuencia("X");
        typename std::list<_secuencia::Secuencia<V>>::iterator it;
        std::list<std::string>::iterator its;
        for (it = this->lista_archivo_secuencias_.begin();
             it != this->lista_archivo_secuencias_.end(); ++it) {
            std::list<std::string> lista_string;
            lista_string = it->ListaSecuencia();
            for (its = lista_string.begin(); its != lista_string.end(); ++its) {
                std::string aux;
                aux = (std::regex_replace(*its, std::regex(mascara), "X"));
                *its = aux;
            }
            it->ActualizarListaSecuencia(lista_string);
        }
        contador = EsSubsecuencia("X") - contador;
        return contador;
    }


} // archivo_secuencia