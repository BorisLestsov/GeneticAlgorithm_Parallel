#ifndef GEN_ENVIROMENT_H
#define GEN_ENVIROMENT_H

#include <vector>

#include "Indiv.h"
#include "Exception.h"
#include <ctime>

using namespace std;

class Island {
    int rank;
    int comm_size;

    const float p_mut;
    const float p_cross;

    volatile uint seed;
    uint knapsack_max_weigth;
    const vector<uint> items_value;
    const vector<uint> items_weight;

    vector<Indiv> indivs;
    vector<Indiv> parents_pool;

    uint max_gen;
    uint popul_size;
    uint chromosome_size;
    uint generation;   // Generation
    float migr_rate;
    uint migr_size;

    double tot_fit;
    char* buf_recv;

    // Private methods
    Chromosome generate_random_chromosome();
    void calculate_fitness();
    double calculate_indiv_fitness(const Indiv &a); //always non negative

    void perform_selection();
    void perform_crossover();
    void perform_mutation();
    void perform_migration();

    uint roulette_select();

public:
    Island(uint knapsack_size, const vector<uint>& values,
           const vector<uint>& weights, uint max_gen, uint popul_size,
           float mut_rate = 0.05, float cross_rate = 0.85,  float migr_rate = 0.05, uint seed = 0);

    void start();
    const Indiv& get_fittest();
    uint cacl_indiv_value(const Indiv& ind) const;

    ~Island();
};

#endif //GEN_ENVIROMENT_H
