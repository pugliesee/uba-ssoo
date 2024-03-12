#ifndef CHM_CPP
#define CHM_CPP

#include <filesystem>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <filesystem>

#include "CargarArchivos.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }

    while (file >> palabraActual) {
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

std::vector<std::string> get_paths_to_files(const std::filesystem::path fp)
{
    std::vector<std::string> filepaths;

    for(const auto& entry : std::filesystem::directory_iterator(fp))
    {
        filepaths.push_back(entry.path());

    }

    return filepaths;
}


int cargarArchivoThread(
    HashMapConcurrente &hashMap,
    std::vector<std::string> &filePath,
    std::atomic<int> &idx
) {
    for (size_t count{}; (count = idx++) < filePath.size();)
    {
        std::fstream file;
        int cant = 0;
        std::string palabraActual;

        // Abro el archivo.
        file.open(filePath[count], file.in);

        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo '" << filePath[count] << "'" << std::endl;
            return -1;
        }
        while (file >> palabraActual) {
            hashMap.incrementar(palabraActual);
            cant++;
        }
        // Cierro el archivo.
        if (!file.eof()) {
            std::cerr << "Error al leer el archivo" << std::endl;
            file.close();
            return -1;
        }
        file.close();
    }
    return 0;
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    std::atomic<int> idx;
    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < cantThreads; i++) 
    {
        threads.emplace_back(std::thread(&cargarArchivoThread, std::ref(hashMap), std::ref(filePaths), std::ref(idx)));
    }

    for (unsigned int i = 0; i < cantThreads; i++) 
    {
        threads[i].join();
    }
}

#endif
