#include <filesystem>
#include <vector>
#include "lib/littletest.hpp"

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

LT_BEGIN_SUITE(TestLoadNormalFourThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadNormalFourThreads)

LT_BEGIN_TEST(TestLoadNormalFourThreads, NormalDataFourThreads)
    cargarMultiplesArchivos(hM, 4, get_paths_to_files(std::filesystem::path{"./data/random_data/normal"}));
LT_END_TEST(NormalDataFourThreads)

LT_BEGIN_TEST(TestLoadNormalFourThreads, MaxFourThreads)
    hM.maximoParalelo(4);
LT_END_TEST(MaxFourThreads)


LT_BEGIN_SUITE(TestLoadNormalEightThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadNormalEightThreads)

LT_BEGIN_TEST(TestLoadNormalEightThreads, NormalDataEightThreads)
    cargarMultiplesArchivos(hM, 8, get_paths_to_files(std::filesystem::path{"./data/random_data/normal"}));
LT_END_TEST(NormalDataEightThreads)

LT_BEGIN_TEST(TestLoadNormalFourThreads, MaxEightThreads)
    hM.maximoParalelo(8);
LT_END_TEST(MaxEightThreads)

LT_BEGIN_SUITE(TestLoadNormalTwelveThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadNormalTwelveThreads)

LT_BEGIN_TEST(TestLoadNormalTwelveThreads, NormalDataTwelveThreads)
    cargarMultiplesArchivos(hM, 12, get_paths_to_files(std::filesystem::path{"./data/random_data/normal"}));
LT_END_TEST(NormalDataTwelveThreads)

LT_BEGIN_TEST(TestLoadNormalTwelveThreads, MaxTwelveThreads)
    hM.maximoParalelo(12);
LT_END_TEST(MaxTwelveThreads)

LT_BEGIN_SUITE(TestLoadNormalTwentyThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadNormalTwentyThreads)

LT_BEGIN_TEST(TestLoadNormalTwentyThreads, NormalDataTwentyThreads)
    cargarMultiplesArchivos(hM, 20, get_paths_to_files(std::filesystem::path{"./data/random_data/normal"}));
LT_END_TEST(NormalDataTwentyThreads)

LT_BEGIN_TEST(TestLoadNormalTwentyThreads, MaxTwentyThreads)
    hM.maximoParalelo(20);
LT_END_TEST(MaxTwentyThreads)

LT_BEGIN_SUITE(TestLoadNormalMaxThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadNormalMaxThreads)

LT_BEGIN_TEST(TestLoadNormalMaxThreads, NormalDataMaxThreads)
    cargarMultiplesArchivos(hM, 26, get_paths_to_files(std::filesystem::path{"./data/random_data/normal"}));
LT_END_TEST(NormalDataMaxThreads)

LT_BEGIN_TEST(TestLoadNormalMaxThreads, MaxMaxThreads)
    hM.maximoParalelo(26);
LT_END_TEST(MaxMaxThreads)

// Ejecutar tests
LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()
