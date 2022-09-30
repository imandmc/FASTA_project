//
// Created by Juan Salazar on 30/09/22.
//
#include <iostream>
#include "ArchivoSecuencia.cpp"

int main() {

    std::cout << "Hello World! FESTER" << std::endl;
    std::string nombrees;
    std::cin >> nombrees;
    archivo_secuencia::ArchivoSecuencia<int, int> Archivo1(nombrees);


    return 0;
}