#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "rpa.hpp"

using namespace std;

template<typename T>
class FromPopulation {
    public:
        vector<vector<int> > population;
        vector<T> profits;
        vector<T> fitness;

        FromPopulation(vector<vector<int>> repaired_population, vector<T> profits) {
            this->population = repaired_population;
            this->profits = profits;

        }
    
    private:
        vector<T> get_fitness(){
            for (int i = 0; i < this->population.size(); i++){
                this->fitness.push_back(sum(i, this->population, this->profits));
            }
        }
};