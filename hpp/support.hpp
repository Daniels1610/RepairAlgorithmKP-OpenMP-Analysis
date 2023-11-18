#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <vector>

template <typename T>
T sum(int chromosome_ID, std::vector<std::vector<int> > initial_population, std::vector<T> weights){
    T sum = 0;
    for (int i = 0; i < initial_population[0].size(); i++){
        sum += weights[i] * initial_population[chromosome_ID][i];
    }
    return sum;
}

std::vector<std::vector<int> > replace_chromosome(int chromosome_ID, std::vector<std::vector<int> > population_repaired, std::vector<std::vector<int> > population){
    for (int i = 0; i < population[0].size(); i++){
        population_repaired[chromosome_ID][i] = population[chromosome_ID][i];
    }
    return population_repaired;
}

#endif