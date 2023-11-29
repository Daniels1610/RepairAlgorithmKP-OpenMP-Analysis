#ifndef RPA_HPP
#define RPA_HPP

#include <vector>
#include <omp.h>
#include "support.hpp"

template <typename T>
std::vector<std::vector<int> > repair_population(std::vector<std::vector<int> > &population, std::vector<T> weights, T knapsack_capacity) {
    
    std::vector<std::vector<int> > population_repaired = population;

    #pragma omp parallel num_threads(4)
    {   
        int i=0;
        int solutions = population.size();
        int alleles_num = population[0].size();
        bool knapsack_full = false;
        int NUM_THREADS = omp_get_num_threads();

        #pragma omp parallel for firstprivate(population_repaired)
        for (i = 0; i < solutions; i+=NUM_THREADS) { 
            if (sum(i, population, weights) > knapsack_capacity) {
                knapsack_full = true;
            }

            #pragma omp flush (knapsack_full)
            while (knapsack_full) {
                #pragma omp parallel for firstprivate(i)
                for (int j = 0; j < alleles_num; j+=NUM_THREADS) {
                    population[i][j] = 0;
                    if (sum(i, population, weights) < knapsack_capacity) {
                        knapsack_full = false;
                        #pragma omp critical
                        population_repaired = replace_chromosome(i, population_repaired, population);
                    }
                }
                break;
            }

            while (!knapsack_full) {
                #pragma omp parallel for firstprivate(i)
                {
                    for (int h = 0; h < alleles_num; h+=NUM_THREADS) {
                        population[i][h] = 1;
                        if (sum(i, population, weights) > knapsack_capacity) {
                            population[i][h] = 0;
                        }
                    }
                }

                #pragma omp critical
                population_repaired = replace_chromosome(i, population_repaired, population);
                break;
            }
        }

    }
    return population_repaired;
}
#endif