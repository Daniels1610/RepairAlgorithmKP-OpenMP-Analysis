#include <omp.h>
#include "hpp/PopulationGen.hpp"

using namespace std;

const int CHROMOSOMES_NUM = 1000;
const int GENES_NUM = 15;
const int KNAPSACK_CAPACITY = 750;
double start_time, run_time;


int main(int argc, char *argv[]){
    
    Population<int> population(CHROMOSOMES_NUM, GENES_NUM, KNAPSACK_CAPACITY);
    // cout << "INITIAL POPULATION: \n"; population.display_population(population.population);
    
    population.set_weights("weights30.txt");
    population.set_profits("profits30.txt");

    omp_set_num_threads(atoi(argv[1]));
    start_time = omp_get_wtime();
    population.get_repaired_population();
    run_time = omp_get_wtime() - start_time;

    population.set_fitness(population.repaired_population);

    printf("%f", run_time);
    // cout << "\nREPAIRED POPULATION:\n"; population.display_population(population.repaired_population);
    // cout << "WEIGHTS:\n"; population.display_vector(population.weights);
    // cout << "PROFITS:\n"; population.display_vector(population.profits);
    // cout << "FITNESS:\n"; population.display_vector(population.fitness);

    return 0;
}