#ifndef RPA_HPP
#define RPA_HPP

#include <iostream>
#include <vector>
#include <omp.h>
#include "support.hpp"

class Node {
    public:
        int id;
        std::vector<std::vector<int> > chromosome;
        Node * next;

        Node(const int id, std::vector<std::vector<int> > chromosome) {
            this->id = id;
            this->chromosome = chromosome;
        }
};

template <typename T>
std::vector<std::vector<int> > repair_population(std::vector<std::vector<int> >& population, std::vector<T> weights, T knapsack_capacity) {
    bool knapsack_full = false;
    int solutions = population.size();
    int alleles_num = population[0].size();
    std::vector<std::vector<int> > population_repaired = population; 

    #pragma omp parallel
    {
        for (int i = 0; i < solutions; i++) {
            #pragma omp task
            {
                if (sum(i, population, weights) > knapsack_capacity) {
                    knapsack_full = true;
                }

                while (knapsack_full) {
                    for (int j = 0; j < alleles_num; j++) {
                        population[i][j] = 0;
                        if (sum(i, population, weights) < knapsack_capacity) {
                            knapsack_full = false;
                            population_repaired = replace_chromosome(i, population_repaired, population);
                            break;
                        }
                    }
                }

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
        } 
    }
    return population_repaired;
}

#endif

Node * init_list(Node* p, std::vector<std::vector<int> >& population){
    int i;
    Node* head = NULL; Node* temp = NULL;
    head = Node(0, population[0]);
    p = head;
    for (i = 1; i < population.size(); i++) {
        temp = Node(i, population[i])
        p.n
    }
    
}