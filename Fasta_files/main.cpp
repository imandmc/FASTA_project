//
// Created by Juan Salazar on 30/09/22.
//
#include <iostream>
#include "ArchivoSecuencia.cpp"

int main() {

    std::cout << "Hello World! FESTER" << std::endl;
    std::string nombrees;
    std::cin >> nombrees;
    archivo_secuencia::ArchivoSecuencia<_secuencia::Secuencia<int>, int> Archivo1(nombrees);
    Archivo1.ExportarTxt("Holap11.txt");
    Archivo1.HuffmanEncodder();
    Archivo1.alistadorSaveFile("Holap.bin");
    archivo_secuencia::ArchivoSecuencia<_secuencia::Secuencia<int>, int> Archivo2("Holap.bin", 1);
    Archivo2.ExportarTxt("HolapELDOS.txt");
}