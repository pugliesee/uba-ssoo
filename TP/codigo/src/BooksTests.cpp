#include <filesystem>
#include <vector>
#include "lib/littletest.hpp"

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

LT_BEGIN_SUITE(TestLoadBooksSingleThread)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadBooksSingleThread)

LT_BEGIN_TEST(TestLoadBooksSingleThread, CargarLibrosUnThread)
    cargarArchivo(hM, "data/books/alice");
    cargarArchivo(hM, "data/books/frankenstein");
    cargarArchivo(hM, "data/books/dorian");
    cargarArchivo(hM, "data/books/jekyll_hyde");
    cargarArchivo(hM, "data/books/metamorphosis");
    cargarArchivo(hM, "data/books/prejudice");
    cargarArchivo(hM, "data/books/montecristo");
    cargarArchivo(hM, "data/books/karenina");
    cargarArchivo(hM, "data/books/cities");
LT_END_TEST(CargarLibrosUnThread)


LT_BEGIN_SUITE(TestLoadBooksTwoThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadBooksTwoThreads)

LT_BEGIN_TEST(TestLoadBooksTwoThreads, CargarLibrosDosThreads)
    cargarMultiplesArchivos(hM, 2, get_paths_to_files(std::filesystem::path{"./data/books"}));
    hM.maximoParalelo(2);
LT_END_TEST(CargarLibrosDosThreads)


LT_BEGIN_SUITE(TestLoadBooksFourThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadBooksFourThreads)

LT_BEGIN_TEST(TestLoadBooksFourThreads, CargarLibrosCuatroThreads)
    cargarMultiplesArchivos(hM, 4, get_paths_to_files(std::filesystem::path{"./data/books"}));
    hM.maximoParalelo(4);
LT_END_TEST(CargarLibrosCuatroThreads)

LT_BEGIN_SUITE(TestLoadBooksEightThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadBooksEightThreads)

LT_BEGIN_TEST(TestLoadBooksEightThreads, CargarLibrosOchoThreads)
    cargarMultiplesArchivos(hM, 8, get_paths_to_files(std::filesystem::path{"./data/books"}));
    hM.maximoParalelo(8);
LT_END_TEST(CargarLibrosOchoThreads)

LT_BEGIN_SUITE(TestLoadBooksTwelveThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadBooksTwelveThreads)

LT_BEGIN_TEST(TestLoadBooksFourThreads, CargarLibrosDoceThreads)
    cargarMultiplesArchivos(hM, 12, get_paths_to_files(std::filesystem::path{"./data/books"}));
    hM.maximoParalelo(12);
LT_END_TEST(CargarLibrosDoceThreads)

// Ejecutar tests
LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()
