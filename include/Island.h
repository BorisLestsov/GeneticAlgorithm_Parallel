#ifndef GEN_ENVIROMENT_H
#define GEN_ENVIROMENT_H

#include <vector>

#include "Indiv.h"
#include "Exception.h"
#include <ctime>

using namespace std;

class Island {

    constexpr static const float p_mut = 0.05;
    constexpr static const float p_cross = 0.85;

    volatile uint seed;
    uint knapsack_max_weigth;
    const vector<uint> items_value;
    const vector<uint> items_weight;

    vector<Indiv> indivs;
    vector<Indiv> parents_pool;

    uint pop_size;
    uint chromosome_size;
    uint generation;   // Generation

    double tot_fit;

    // Private methods
    Chromosome generate_random_chromosome();
    void calculate_fitness();
    double calculate_indiv_fitness(const Indiv &a); //always non negative

    void perform_selection();
    void perform_crossover();
    void perform_mutation();

    uint roulette_select();


public:
    Island(uint knapsack_size, const vector<uint>& values,  const vector<uint>& weights, uint seed = 0);

    void start(uint max_gen, uint max_indivs);
    const Indiv& get_fittest();
    uint cacl_indiv_value(const Indiv& ind) const;
};

#endif //GEN_ENVIROMENT_H
