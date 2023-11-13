#include "PopulationGen.hpp"

using namespace std;

const int CHROMOSOMES_NUM = 100;
const int GENES_NUM = 15;
const int KNAPSACK_CAPACITY = 750;

int main(){
    Population<int> population(CHROMOSOMES_NUM, GENES_NUM, KNAPSACK_CAPACITY);
    cout << "INITIAL POPULATION: \n"; population.display_population(population.population);
    
    population.set_weights("weights.txt");
    population.set_profits("profits.txt");
    population.get_repaired_population();
    population.set_fitness(population.repaired_population);
    cout << "\nREPAIRED POPULATION:\n"; population.display_population(population.repaired_population);
    cout << "WEIGHTS:\n"; population.display_vector(population.weights);
    cout << "PROFITS:\n"; population.display_vector(population.profits);
    cout << "FITNESS:\n"; population.display_vector(population.fitness);

    return 0;
}