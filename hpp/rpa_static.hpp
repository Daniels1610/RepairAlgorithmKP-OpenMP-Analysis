#ifndef RPA_HPP
#define RPA_HPP

#include <vector>
#include <omp.h>
#include "support.hpp"

template <typename T>
std::vector<std::vector<int> > repair_population(std::vector<std::vector<int> > &population, std::vector<T> weights, T knapsack_capacity) {
    
    std::vector<std::vector<int> > population_repaired = population;
        int i;
        int solutions = population.size();
        int alleles_num = population[0].size();
        bool knapsack_full = false;

        #pragma omp parallel for private(i) firstprivate(knapsack_full) schedule(static)
        for (i = 0; i < solutions; i+=omp_get_num_threads()) {
            bool knapsack_full = sum(i, population, weights) > knapsack_capacity;

            #pragma omp flush(knapsack_full)
            while (knapsack_full) {
                for (int j = 0; j < alleles_num; j++) {
                    population[i][j] = 0;
                    if (sum(i, population, weights) < knapsack_capacity) {
                        knapsack_full = false;
                        #pragma omp flush(knapsack_full)
                        population_repaired = replace_chromosome(i, population_repaired, population);
                        break;
                    }
                }
            }

            #pragma omp flush(knapsack_full)
            while (!knapsack_full) {
                for (int h = 0; h < alleles_num; h++) {
                    population[i][h] = 1;
                    if (sum(i, population, weights) > knapsack_capacity) {
                        population[i][h] = 0;
                    }
                }
                population_repaired = replace_chromosome(i, population_repaired, population);
                break;
            }
        }
    return population_repaired;
}
#endif