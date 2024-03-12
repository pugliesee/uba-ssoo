#include <filesystem>
#include <vector>
#include "lib/littletest.hpp"

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

LT_BEGIN_SUITE(TestLoadUniformFourThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformFourThreads)

LT_BEGIN_TEST(TestLoadUniformFourThreads, UniformDataFourThreads)
    cargarMultiplesArchivos(hM, 4, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataFourThreads)

LT_BEGIN_TEST(TestLoadUniformFourThreads, MaxFourThreads)
    hM.maximoParalelo(4);
LT_END_TEST(MaxFourThreads)


LT_BEGIN_SUITE(TestLoadUniformEightThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformEightThreads)

LT_BEGIN_TEST(TestLoadUniformEightThreads, UniformDataEightThreads)
    cargarMultiplesArchivos(hM, 8, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataEightThreads)

LT_BEGIN_TEST(TestLoadUniformFourThreads, MaxEightThreads)
    hM.maximoParalelo(8);
LT_END_TEST(MaxEightThreads)

LT_BEGIN_SUITE(TestLoadUniformTwelveThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformTwelveThreads)

LT_BEGIN_TEST(TestLoadUniformTwelveThreads, UniformDataTwelveThreads)
    cargarMultiplesArchivos(hM, 12, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataTwelveThreads)

LT_BEGIN_TEST(TestLoadUniformTwelveThreads, MaxTwelveThreads)
    hM.maximoParalelo(12);
LT_END_TEST(MaxTwelveThreads)

LT_BEGIN_SUITE(TestLoadUniformSixteenThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformSixteenThreads)

LT_BEGIN_TEST(TestLoadUniformSixteenThreads, UniformDataSixteenThreads)
    cargarMultiplesArchivos(hM, 16, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataSixteenThreads)

LT_BEGIN_TEST(TestLoadUniformSixteenThreads, MaxSixteenThreads)
    hM.maximoParalelo(16);
LT_END_TEST(MaxSixteenThreads)

LT_BEGIN_SUITE(TestLoadUniformTwentyThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformTwentyThreads)

LT_BEGIN_TEST(TestLoadUniformTwentyThreads, UniformDataTwentyThreads)
    cargarMultiplesArchivos(hM, 20, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataTwentyThreads)

LT_BEGIN_TEST(TestLoadUniformTwentyThreads, MaxTwentyThreads)
    hM.maximoParalelo(20);
LT_END_TEST(MaxTwentyThreads)

LT_BEGIN_SUITE(TestLoadUniformTwentyfourThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformTwentyfourThreads)

LT_BEGIN_TEST(TestLoadUniformTwentyfourThreads, UniformDataTwentyfourThreads)
    cargarMultiplesArchivos(hM, 24, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataTwentyfourThreads)

LT_BEGIN_TEST(TestLoadUniformTwentyfourThreads, MaxTwentyFourThreads)
    hM.maximoParalelo(24);
LT_END_TEST(MaxTwentyFourThreads)



LT_BEGIN_SUITE(TestLoadUniformMaxThreads)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestLoadUniformMaxThreads)

LT_BEGIN_TEST(TestLoadUniformMaxThreads, UniformDataMaxThreads)
    cargarMultiplesArchivos(hM, 26, get_paths_to_files(std::filesystem::path{"./data/random_data/uniform"}));
LT_END_TEST(UniformDataMaxThreads)
 

// Ejecutar tests
LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()
