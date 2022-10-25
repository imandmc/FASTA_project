//
// Created by Juan Salazar on 30/09/22.
//

#include "ArchivoSecuencia.h"
#include <utility>
#include <list>
#include <regex>
#include <sstream>
#include <string>


namespace archivo_secuencia {


    template<class T, class V>
    ArchivoSecuencia<T, V>::ArchivoSecuencia() = default;

    template<class T, class V>
    ArchivoSecuencia<T, V>::ArchivoSecuencia(std::string &nombre_archivo) {
        nombre_archivo_ = nombre_archivo;
        std::string check_nombre_archivo;
        check_nombre_archivo = nombre_archivo.substr(nombre_archivo.size() - 4);
        if (check_nombre_archivo != ".txt") {
            nombre_archivo += ".txt";
        }
        std::cout << this->nombre_archivo_ << std::endl;
        std::ifstream archivo_lectura(nombre_archivo);
        _secuencia::Secuencia<V> secuencia_entrada2;
        bool last = false;
        bool check_pass = archivo_lectura.good();
        if (check_pass) {
            std::string linea_lectura;
            this->cantidad_sec_ = 0;
            std::list<T> lista_entrada;
            std::list<std::string> lista_lineas_entrada;
            while (getline(archivo_lectura, linea_lectura)) {
                last = false;
                char check_secuencia = linea_lectura[0];
                if (check_secuencia == '>') {
                    bool secuencia_vacia = true;
                    _secuencia::Secuencia<V> secuencia_entrada;
                    secuencia_entrada.AsignarNombre(linea_lectura.substr(1));
                    std::string linea_lectura_lineas;
                    int position = archivo_lectura.tellg();
                    while (getline(archivo_lectura, linea_lectura_lineas)) {
                        check_secuencia = linea_lectura_lineas[0];
                        if (check_secuencia != '>' && check_secuencia != '\0') {
                            secuencia_entrada.AgregarLinea(linea_lectura_lineas);
                            secuencia_vacia = false;
                            position = archivo_lectura.tellg();
                        } else {
                            if (secuencia_entrada.SecuenciaCorrecta() && !secuencia_vacia) {
                                secuencia_entrada.CrearGrafo();
                                lista_entrada.push_back(secuencia_entrada);
                                this->cantidad_sec_ += 1;
                                last = true;
                            } else {
                                secuencia_entrada.clear();
                            }
                            archivo_lectura.seekg(position);
                            break;
                        }
                    }
                    if (position == -1 || !last) {
                        if (secuencia_entrada.SecuenciaCorrecta() && !secuencia_vacia) {
                            secuencia_entrada.CrearGrafo();
                            lista_entrada.push_back(secuencia_entrada);
                            this->cantidad_sec_ += 1;
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
        std::cout << "Archivo: " << nombre_archivo_ << std::endl;
        std::cout << "Cantidad de secuencias en el archivo: " << cantidad_sec_ << std::endl;
        std::cout << "N distintas bases que contiene el archivo (de 18): " << cantidad_bases_archivo_ << std::endl;
        std::cout << "Huffman cargado: " << std::endl;
        for (auto huffmap: mapa_) {
            std::vector<int> vec_huff;
            vec_huff = huffmap.second;
            std::cout << huffmap.first << " : ";
            for (auto veciter: vec_huff) {
                std::cout << veciter;
            }
            std::cout << std::endl;
        }
        std::cout << "Frecuencias cargadas: " << std::endl;
        for (auto freqmap: mapa_freq_) {
            std::cout << freqmap.first << " : " << freqmap.second << std::endl;
        }
    }

    template<class T, class V>
    void ArchivoSecuencia<T, V>::ExportarTxt(std::string nombre_archivo) {
        int cantidad = this->cantidad_sec_;
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
            cantidad--;
            int cantidad2 = -1;
            if (cantidad == 0) {
                cantidad2 = lista_string.size();
            }
            for (its = lista_string.begin(); its != lista_string.end(); ++its) {
                file_obj << *its;
                file_obj << std::endl;
                cantidad2--;
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

    template<class T, class V>
    int ArchivoSecuencia<T, V>::Enmascarar(const std::string &mascara, std::string enmascara) {
        int contador = EsSubsecuencia(enmascara);
        typename std::list<_secuencia::Secuencia<V>>::iterator it;
        std::list<std::string>::iterator its;
        for (it = this->lista_archivo_secuencias_.begin();
             it != this->lista_archivo_secuencias_.end(); ++it) {
            std::list<std::string> lista_string;
            lista_string = it->ListaSecuencia();
            for (its = lista_string.begin(); its != lista_string.end(); ++its) {
                std::string aux;
                aux = (std::regex_replace(*its, std::regex(mascara), enmascara));
                *its = aux;
            }
            it->ActualizarListaSecuencia(lista_string);
        }
        contador = EsSubsecuencia("X") - contador;
        return contador;
    }

    template<class T, class V>
    void ArchivoSecuencia<T, V>::HuffmanEncodder(std::map<char, int> mapa) {
        typename std::list<_secuencia::Secuencia<V>>::iterator it;
        std::list<std::string>::iterator its;
        int sizes = mapa.size() + 1;
        char char_array[sizes - 1];
        int frecuencia_array[sizes - 1];
        for (it = this->lista_archivo_secuencias_.begin();
             it != this->lista_archivo_secuencias_.end(); ++it) {
            std::list<std::string> lista_string;
            lista_string = it->ListaSecuencia();
            for (its = lista_string.begin(); its != lista_string.end(); ++its) {
                std::string aux;
                auto iter = mapa.begin();
                while (iter != mapa.end()) {
                    for (int i = 0; i < (sizes - 1); i++, iter++) {
                        char_array[i] = iter->first;
                        frecuencia_array[i] = iter->second;
                    }
                }
            }
        }
        Huffman huff;
        huff.HuffmanEncoding(char_array, frecuencia_array, sizeof(char_array) / sizeof(char_array[0]));
        std::map<char, std::vector<int>> HuffmanOutMap = huff.MapHuffman();
        auto iterHuff = HuffmanOutMap.begin();
        while (iterHuff != HuffmanOutMap.end()) {
            std::stringstream result;
            std::copy(iterHuff->second.begin(), iterHuff->second.end(), std::ostream_iterator<int>(result, ""));
            std::string mascara_imput = result.str();
            std::string enmasca_imput(1, iterHuff->first);
            std::cout << mascara_imput << " : " << enmasca_imput << std::endl;
            int contador = this->Enmascarar(enmasca_imput, mascara_imput);
            ++iterHuff;
        }
        this->mapa_ = HuffmanOutMap;
    }

    template<class T, class V>
    void ArchivoSecuencia<T, V>::HuffmanEncodder() {
        std::map<char, int> mapa = this->Mapeo();
        HuffmanEncodder(mapa);
    }


    template<class T, class V>
    std::map<char, int> ArchivoSecuencia<T, V>::Mapeo() {
        //Bases Básicas
        std::map<char, int> mapa;
        int freq_contador;
        std::list<char>::iterator it;
        for (it = this->lista_bases_.begin(); it != this->lista_bases_.end(); ++it) {
            std::string entrada(1, *it);
            freq_contador = EsSubsecuencia(entrada);
            if (freq_contador > 0) {
                this->cantidad_bases_archivo_++;
                mapa.emplace(*it, freq_contador);
            }
        }
        this->mapa_freq_ = mapa;
        return mapa;
    }


    template<class T, class V>
    void ArchivoSecuencia<T, V>::alistadorSaveFile(std::string nombre_archivo) {
        std::string check_nombre_archivo;
        check_nombre_archivo = nombre_archivo.substr(nombre_archivo.size() - 4);
        if (check_nombre_archivo != ".bin") {
            nombre_archivo += ".bin";
        }
        std::ofstream outputBIN(nombre_archivo, std::ios::out | std::ios::binary);
        int16_t bases_int_ = this->cantidad_bases_archivo_;
        outputBIN.write(reinterpret_cast<const char *>(&bases_int_), sizeof(bases_int_));
        std::map<char, int> mapa_frecuencias = this->mapa_freq_;
        std::map<int, int> mapa_frecuencias_ascii;
        auto iter1 = mapa_frecuencias.begin();
        while (iter1 != mapa_frecuencias.end()) {
            mapa_frecuencias_ascii.emplace(int(iter1->first), iter1->second);
            iter1++;
        }
        auto iter2 = mapa_frecuencias_ascii.begin();
        while (iter2 != mapa_frecuencias_ascii.end()) {
            int8_t ascii_code = iter2->first;
            int64_t frec_code = iter2->second;
            outputBIN.write(reinterpret_cast<const char *>(&ascii_code), sizeof(ascii_code));
            outputBIN.write(reinterpret_cast<const char *>(&frec_code), sizeof(frec_code));
            iter2++;
        }
        int32_t cantidad_secuencias_ = this->cantidad_sec_;
        outputBIN.write(reinterpret_cast<const char *>(&cantidad_secuencias_), sizeof(cantidad_secuencias_));
        auto listiterator = this->lista_archivo_secuencias_.begin();
        for (listiterator; listiterator != this->lista_archivo_secuencias_.end(); ++listiterator) {
            std::string nombre_temp = listiterator->NombreSecuencia();
            int longitud_nombre = nombre_temp.length();
            int16_t longitud_nombre_ = longitud_nombre;
            outputBIN.write(reinterpret_cast<const char *>(&longitud_nombre_), sizeof(longitud_nombre_));
            for (char char_nombre: nombre_temp) {
                outputBIN.write(reinterpret_cast<const char *>(&char_nombre), sizeof(char_nombre));
            }
            int64_t longitud_ = listiterator->longitud_max();
            int16_t identation_ = listiterator->identation();
            outputBIN.write(reinterpret_cast<const char *>(&longitud_), sizeof(longitud_));
            outputBIN.write(reinterpret_cast<const char *>(&identation_), sizeof(identation_));
            std::list<std::string> lista_i = listiterator->ListaSecuencia();
            auto secuenciait = lista_i.begin();
            for (secuenciait; secuenciait != lista_i.end(); secuenciait++) {
                int16_t contador_ = 0;
                int16_t ceros_ = 0;
                std::string linea_in = *secuenciait;
                int N = linea_in.size();
                int j = 0;
                std::vector<std::string> result;
                std::string res;
                while (j < N) {
                    res += linea_in[j];
                    if (res.size() == 63) {
                        result.push_back(res);
                        contador_++;
                        res = "";
                    }
                    j++;
                }
                if (!res.empty()) {
                    while (res.size() < 63) {
                        res += "0";
                        ceros_++;
                    }
                    result.push_back(res);
                    contador_++;
                }
                outputBIN.write(reinterpret_cast<const char *>(&contador_), sizeof(contador_));
                outputBIN.write(reinterpret_cast<const char *>(&ceros_), sizeof(ceros_));
                for (auto i_: result) {
                    i_.insert(0, "1");
                    std::bitset<sizeof(unsigned long) * 8> bits(i_);
                    unsigned long binary_value = bits.to_ulong();
                    outputBIN.write(reinterpret_cast<const char *>(&binary_value), sizeof(unsigned long));
                }
            }
        }
        outputBIN.close();
    }

    template<class T, class V>
    ArchivoSecuencia<T, V>::ArchivoSecuencia(std::string &nombre_archivo, const int &bin_opcion) {
        nombre_archivo_ = nombre_archivo;
        std::string check_nombre_archivo;
        check_nombre_archivo = nombre_archivo.substr(nombre_archivo.size() - 4);
        if (check_nombre_archivo != ".bin") {
            nombre_archivo += ".bin";
        }
        std::ifstream infile(nombre_archivo, std::ios::in | std::ios::binary);
        int16_t cantidad_bases_in = 0;
        infile.read((char *) &cantidad_bases_in, sizeof(cantidad_bases_in));
        this->cantidad_bases_archivo_ = cantidad_bases_in;
        std::map<int, int> mapa_frecuencias_ascii;
        for (int i = 1; i <= cantidad_bases_in; i++) {
            int8_t ascii_code_in = 0;
            int64_t code_freq_in = 0;
            infile.read((char *) &ascii_code_in, sizeof(ascii_code_in));
            infile.read((char *) &code_freq_in, sizeof(code_freq_in));
            mapa_frecuencias_ascii.emplace(int(ascii_code_in), int(code_freq_in));
        }
        auto iter_map = mapa_frecuencias_ascii.begin();
        int size_map = mapa_frecuencias_ascii.size();
        char char_array[size_map];
        int frecuencia_array[size_map];
        while (iter_map != mapa_frecuencias_ascii.end()) {
            for (int i = 0; i < (size_map); i++, iter_map++) {
                char_array[i] = char(iter_map->first);
                frecuencia_array[i] = iter_map->second;
            }
        }
        Huffman huff_2;
        huff_2.HuffmanEncoding(char_array, frecuencia_array, sizeof(char_array) / sizeof(char_array[0]));
        int32_t cantidad_sec_in = 0;
        infile.read((char *) &cantidad_sec_in, sizeof(cantidad_sec_in));
        std::list<_secuencia::Secuencia<V>> list_secuencias_in;
        typename std::list<_secuencia::Secuencia<V>>::iterator it_ls;
        this->cantidad_sec_ = cantidad_sec_in;
        for (int j = 1; j <= cantidad_sec_in; j++) {
            _secuencia::Secuencia<V> secuencia_in;
            std::string nombre_sec_in;
            int16_t longitud_nombre_in = 0;
            infile.read((char *) &longitud_nombre_in, sizeof(longitud_nombre_in));
            for (int k = 1; k <= longitud_nombre_in; k++) {
                char char_in;
                infile.read((char *) &char_in, sizeof(char_in));
                nombre_sec_in.push_back(char_in);
            }
            secuencia_in.AsignarNombre(nombre_sec_in);
            int64_t longitud_lineas;
            infile.read((char *) &longitud_lineas, sizeof(longitud_lineas));
            int16_t identation_lineas;
            infile.read((char *) &identation_lineas, sizeof(identation_lineas));
            std::list<std::string> lista_filas;
            for (int x = 1; x <= identation_lineas; x++) {
                std::string linea_final_in = "";
                int16_t lineas_packs = 0;
                int16_t ceros_pack = 0;
                infile.read((char *) &lineas_packs, sizeof(lineas_packs));
                infile.read((char *) &ceros_pack, sizeof(ceros_pack));
                for (int i_ = 1; i_ <= lineas_packs; i_++) {
                    unsigned long bin_value;
                    infile.read((char *) &bin_value, sizeof(bin_value));
                    std::string binary_line = std::bitset<sizeof(unsigned long) * 8>(bin_value).to_string();
                    binary_line = binary_line.substr(1, binary_line.size());
                    linea_final_in += binary_line;
                }
                linea_final_in = linea_final_in.substr(0, linea_final_in.size() - ceros_pack);
                std::map<char, std::vector<int>> HuffmanOutMap = huff_2.MapHuffman();
                auto iterHuff = HuffmanOutMap.begin();
                std::string fin_aux = linea_final_in;
                std::string fin_real;
                std::map<std::string, char> map_reversed;
                for (auto &it__: HuffmanOutMap) {
                    std::vector<int> vect_temp;
                    vect_temp = it__.second;
                    auto it_vec = vect_temp.begin();
                    std::string new_trace;
                    while (it_vec != vect_temp.end()) {
                        new_trace += std::to_string(*it_vec);
                        ++it_vec;
                    }
                    map_reversed[new_trace] = it__.first;
                }
                while (!fin_aux.empty()) {
                    std::string check_str;
                    bool bandera = false;
                    while (!bandera) {
                        check_str += fin_aux.substr(0, 1);
                        fin_aux = fin_aux.substr(1, fin_aux.size());
                        if (map_reversed.count(check_str)) {
                            fin_real.push_back(map_reversed[check_str]);
                            bandera = true;
                            check_str = "";
                        }
                    }
                }
                linea_final_in = fin_real;
                lista_filas.push_back(linea_final_in);
            }
            secuencia_in.ActualizarListaSecuencia(lista_filas);
            secuencia_in.ActualizarLongitud(longitud_lineas);
            list_secuencias_in.push_back(secuencia_in);
            archivo_vacio = false;
        }
        lista_archivo_secuencias_ = list_secuencias_in;
    }


} // archivo_secuencia