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
    int contador2 = Archivo1.Enmascarar("A");
    Archivo1.ExportarTxt("Holap11.txt");
    int contador = Archivo1.EsSubsecuencia("CUANADDDVMMDVHRS");
    std::cout << contador << std::endl;
    std::cout << contador2 << std::endl;
    char arr[] = {'A', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    Huffman huff;
    huff.HuffmanEncoding(arr, freq, size);
}