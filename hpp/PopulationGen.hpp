#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include "rpa_serial.hpp"

using namespace std;

string DATASETS_DIR = "datasets/";

template<typename T>
class Population {
    public:
        int chromosomes_num;
        int genes_num;
        vector<vector<int> > population;
        T knapsack_capacity;
        vector<T> weights;
        vector<T> profits;
        vector<vector<int> > repaired_population;
        vector<T> fitness;

        Population(const int chromosomes_num, const int genes_num, const T knapsack_capacity) {
            this->chromosomes_num = chromosomes_num;
            this->genes_num = genes_num;
            this->population = this->generate_population(chromosomes_num, genes_num);
            this->knapsack_capacity = knapsack_capacity;
        }

        // GETTERS
        void get_repaired_population(){
            this->repaired_population = repair_population(
                this->population,
                this->weights,
                this->knapsack_capacity
            );
        }

        vector<T> get_fitness(){
            for (int i = 0; i < this->chromosomes_num; i++){
                this->fitness.push_back(sum(i, this->population, this->profits));
            }
            return this->fitness;
        }

        // SETTERS
        void set_fitness(vector<vector<int> >& repaired_population){
            for (int i = 0; i < this->chromosomes_num; i++){
                this->fitness.push_back(sum(i, this->repaired_population, this->profits));
            }
        }

        void set_weights(string filename) {
            ifstream file(DATASETS_DIR + filename);
            istream_iterator<T> start(file), end;
            vector<T> w(start, end);
            this->weights = w;
        }

        void set_profits(string filename) {
            ifstream file(DATASETS_DIR + filename);
            istream_iterator<T> start(file), end;
            vector<T> p(start, end);
            this->profits = p;
        }

        void set_population(vector<vector<int> >& new_population){
            this->population = new_population;
        }

        // DISPLAYERS
        void display_population(vector<vector<int> >& population){
            for(int i = 0; i < this->chromosomes_num; i++){
                for(int j = 0; j < this->genes_num; j++){
                    cout << population[i][j] << " ";
                }
                cout << "\n";
            }
        }

        void display_vector(vector<T>& vec){
            for (int i = 0; i < vec.size(); i++){
                cout << vec[i] << " ";
            }
            cout << "\n";
        }

    private:
        // GENERATORS
        vector<vector<int> > generate_population(int chromosomes, int genes){
            vector<vector<int> > population(chromosomes, vector<int>(genes));
            srand(time(0));
            for (int i = 0; i < chromosomes; i++){
                for (int j = 0; j < genes; j++){
                    (population[i])[j] = rand() % 2;
                }
            }
            return population;
        }
};