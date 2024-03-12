#ifndef CHM_CPP
#define CHM_CPP

#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

#include "HashMapConcurrente.hpp"
#include "ListaAtomica.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int index = hashIndex(clave);

    _lock_lists[index].lock();  

    ListaAtomica<hashMapPair> *lista_tabla = tabla[index];

    bool found = false;
    for(auto it = lista_tabla->begin(); it != lista_tabla->end(); it++)
    {
        if ((*it).first == clave) {
            (*it).second++;
            found = true;
        }; 
    }

    if (!found)
    {
        tabla[index]->insertar(std::make_pair(clave, 1));
    }

    _lock_lists[index].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    
    std::vector<std::string> strings;

    for(auto &locks : _lock_lists) {
        locks.lock();
    }

    for(int i = 0; i < cantLetras; i++)
    {
        for(auto a : *tabla[i]){
            strings.push_back(a.first);
        }

        _lock_lists[i].unlock();
    }

    return strings;
}

unsigned int HashMapConcurrente::valor(std::string clave) {

    unsigned int clave_idx = hashIndex(clave);
    _lock_lists[clave_idx].lock();
    
    unsigned int value = 0;
    for(auto it = tabla[clave_idx]->begin(); it != tabla[clave_idx]->end(); it++)
    {
        if (clave == (*it).first)
        {
            value = (*it).second;
            break;
        }
    }

    _lock_lists[clave_idx].unlock();

    return value;
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for(auto &locks : _lock_lists) {
        locks.lock();
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
        _lock_lists[index].unlock();
    }

    return *max;
}


void HashMapConcurrente::maximo_thread(std::vector<hashMapPair>& max_values, std::vector<int> &index)
{
    for(auto idx : index)
    {
        _lock_lists[idx].lock();

        for (auto &p : *tabla[idx]){
            if (p.second > max_values[idx].second) {
                max_values[idx] = p;
            }
        }

        _lock_lists[idx].unlock();
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    std::vector<std::thread> threads;
    std::vector<hashMapPair> max(26);

    // Distribuyo el trabajo en cierta cantidad de threads.
    
    std::vector<std::vector<int>> indices(cant_threads, std::vector<int>(0, 0));

    for(int i = 0; i < cantLetras; i++)
    {
        indices[i % cant_threads].push_back(i);    
    }


    for (unsigned int i = 0; i < cant_threads; i++) 
    {
        threads.emplace_back(std::thread(&HashMapConcurrente::maximo_thread, this, std::ref(max), std::ref(indices[i])));
    }

    for (unsigned int i = 0; i < cant_threads; i++) 
    {
        threads[i].join();
    }

    hashMapPair _global_max = max[0];
    for(auto t : max)
    {
        _global_max = t.second > _global_max.second ? t : _global_max;
    }

    return _global_max;
}

#endif
