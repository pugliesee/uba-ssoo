#ifndef HMC_ARCHIVOS_HPP
#define HMC_ARCHIVOS_HPP

#include <ctype.h>
#include <vector>
#include <string>
#include <filesystem>

#include "HashMapConcurrente.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
);

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
);

int cargarArchivoThread(
    HashMapConcurrente &hashMap,
    std::vector<std::string> &filePath,
    std::atomic<int> &idx
);

std::vector<std::string> get_paths_to_files(std::filesystem::path fp);

#endif /* HMC_ARCHIVOS_HPP */
