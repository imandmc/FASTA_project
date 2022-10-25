//
// Created by Juan Salazar on 30/09/22.
//
#include <iostream>
#include "ArchivoSecuencia.cpp"

int main() {

    std::cout << "Hello World! Zarzamora  .... " << std::endl;
    std::list<std::string> lista_nombres_;
    std::list<archivo_secuencia::ArchivoSecuencia<_secuencia::Secuencia<int>, int>> lista_archivos_;
    std::cout << R"(
________ ________  ________  _________  ________          ________  ________  ________        ___  _______   ________ _________
|\  _____\\   __  \|\   ____\|\___   ___\\   __  \        |\   __  \|\   __  \|\   __  \      |\  \|\  ___ \ |\   ____\\___   ___\
\ \  \__/\ \  \|\  \ \  \___|\|___ \  \_\ \  \|\  \       \ \  \|\  \ \  \|\  \ \  \|\  \     \ \  \ \   __/|\ \  \___\|___ \  \_|
 \ \   __\\ \   __  \ \_____  \   \ \  \ \ \   __  \       \ \   ____\ \   _  _\ \  \\\  \  __ \ \  \ \  \_|/_\ \  \       \ \  \
  \ \  \_| \ \  \ \  \|____|\  \   \ \  \ \ \  \ \  \       \ \  \___|\ \  \\  \\ \  \\\  \|\  \\_\  \ \  \_|\ \ \  \____   \ \  \
   \ \__\   \ \__\ \__\____\_\  \   \ \__\ \ \__\ \__\       \ \__\    \ \__\\ _\\ \_______\ \________\ \_______\ \_______\  \ \__\
    \|__|    \|__|\|__|\_________\   \|__|  \|__|\|__|        \|__|     \|__|\|__|\|_______|\|________|\|_______|\|_______|   \|__|
                      \|_________|
)" << '\n';

    std::cout << R"(
*****************************************************************************************************************************************
$$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\
\____|\____|\____|\____|\____|\____|\____|\____|\____|\____|\____|
$$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\ $$$$\
\____|\____|\____|\____|\____|\____|\____|\____|\____|\____|\____|
******************************************************************************************************************************************
)" << '\n';

    std::cout << "Elija una opción .... " << std::endl;
    std::cout << R"(
+───────+─────────────────────────────────────────────────────────────────+
| |\/| _  _                                                               |
| |  |(/_| ||_|                                                           |
+───────+─────────────────────────────────────────────────────────────────+
| 1.    | Cargar un archivo .txt con información genetica.                |
| 2.    | Cargar un archivo .bin con información genética comprimida.     |
| 3.    | Ver archivos genéticos cargados en memoria                      |
| 4.    | Exportar un archivo genético cargado en memoria                 |
| 5.    | Imprimir información de un archivo genético cargado en memoria  |
| 6.    | Comprimir y exportar .bin de archivo en memoria.                |
| 7.    | Realizar Encodding In-Memory (no se puede deshacer).            |
| 8.    | EXIT                                                            |
|       |                                                                 |
+───────+─────────────────────────────────────────────────────────────────+

)" << std::endl;
    char eleccion = 0;
    while (eleccion != '8') {
        std::cout << "¿Qué desea hacer?" << std::endl;
        std::cin >> eleccion;
        switch (eleccion) {

            case '2': {
                std::cout << "Para cargar un archivo comprimido, digite el nombre del archivo." << std::endl;
                std::string nombre_temp;
                std::cin >> nombre_temp;
                std::cout << "Analizando... " << std::endl;
                lista_nombres_.push_back(nombre_temp);
                archivo_secuencia::ArchivoSecuencia<_secuencia::Secuencia<int>, int> ArchivoTemp(nombre_temp, 1);
                std::cout << "Archivo decodificado con éxito" << std::endl;
                lista_archivos_.push_back(ArchivoTemp);
                std::cout << "Archivo cargado con éxito en la memoria!" << std::endl;
                break;
            }

            case '1': {
                std::cout << "Para cargar un archivo por favor digite el nombre del archivo." << std::endl;
                std::string nombre_temp;
                std::cin >> nombre_temp;
                std::cout << "Creando información..." << std::endl;
                lista_nombres_.push_back(nombre_temp);
                archivo_secuencia::ArchivoSecuencia<_secuencia::Secuencia<int>, int> ArchivoTemp(nombre_temp);
                lista_archivos_.push_back(ArchivoTemp);
                std::cout << "Archivo cargado con éxito!" << std::endl;
                break;
            }
            case '3': {
                std::cout << "Los archivos cargados en memoria son ... " << std::endl;
                for (auto &iter: lista_nombres_) {
                    std::cout << "================" << std::endl;
                    std::cout << iter << std::endl;
                }
                break;
            }
            case '4': {
                std::cout << "Cual archivo cargado quiere Exportar (.txt)?" << std::endl;
                std::string nombre_temp;
                std::cin >> nombre_temp;
                for (auto &archivo: lista_archivos_) {
                    if (archivo.NombreArchivo() == nombre_temp) {
                        nombre_temp = nombre_temp + "_export";
                        archivo.ExportarTxt(nombre_temp);
                        std::cout << "Archivo exportado con éxito!" << std::endl;
                        break;
                    }
                }
                break;
            }
            case '5': {
                std::cout << "Cual archivo cargado quiere informar?" << std::endl;
                std::string nombre_temp;
                std::cin >> nombre_temp;
                for (auto &archivo: lista_archivos_) {
                    if (archivo.NombreArchivo() == nombre_temp) {
                        archivo.Imprimir();
                        break;
                    }
                }
                break;
            }
            case '6': {
                std::cout << "Cual archivo cargado quiere comprimir?" << std::endl;
                std::string nombre_temp;
                std::cin >> nombre_temp;
                for (auto &archivo: lista_archivos_) {
                    if (archivo.NombreArchivo() == nombre_temp) {
                        nombre_temp = nombre_temp + "_BIN_EXPORT";
                        archivo_secuencia::ArchivoSecuencia<_secuencia::Secuencia<int>, int> ArchivoTemp(archivo);
                        ArchivoTemp.HuffmanEncodder();
                        ArchivoTemp.alistadorSaveFile(nombre_temp);
                        std::cout << "Archivo comprimido y exportado!" << std::endl;
                        break;
                    }
                }
                break;
            }

            case '8': {
                std::cout << "Hasta luego ... " << std::endl;
                break;
            }

            case '7': {
                std::cout << "Cual archivo cargado quiere comprimir en memoria?" << std::endl;
                std::string nombre_temp;
                std::cin >> nombre_temp;
                for (auto &archivo: lista_archivos_) {
                    if (archivo.NombreArchivo() == nombre_temp) {
                        std::cout << "Comprimiendo en memoria... " << std::endl;
                        std::cout
                                << "Esto solo sirve para exportar parte del codigo binario como string, ver el mapa huffman y las frecuencias, si quiere comprimir use la opción 6."
                                << std::endl;
                        std::cout << "Para volver al estado anterior reinicie el programa y vuelva a cargar el archivo"
                                  << std::endl;
                        archivo.HuffmanEncodder();

                    }
                }

            }
        }
    }
    return 0;
}