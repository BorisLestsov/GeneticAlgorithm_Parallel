
#include <cmath>
#include "Island.h"

Island::Island(uint knapsack_size, const vector<uint> &values, const vector<uint> &weights, uint seed):
        seed(seed),
        knapsack_max_weigth(knapsack_size),
        items_value(values),
        items_weight(weights),
        chromosome_size((uint) values.size()),
        generation(0)
{
    srand(seed);
    if (items_value.size() != items_weight.size())
        throw Exception("Wrong size of values and weights vectors");
}



void Island::start(uint max_gen, uint max_indivs) {
    uint i;
    pop_size = max_indivs;
    indivs = vector<Indiv>(pop_size);

    for (i = 0; i < pop_size; ++i){
        indivs[i] = Indiv(generate_random_chromosome());
    }

    for (generation = 0; generation < max_gen; ++generation){

        calculate_fitness();
        Indiv fittest = get_fittest();
        //cout << fittest << endl;
        perform_selection();
        perform_crossover();
        perform_mutation();
        indivs = parents_pool;
    }
    calculate_fitness();
}


void Island::perform_selection() {
    uint i;
    double tmp = 0;

    for (i = 0; i < pop_size; ++i){
        tmp += indivs[i].getFitness();
    }
    tot_fit = tmp;

    parents_pool.clear();
    for (i = 0; i < pop_size; ++i){
        parents_pool.push_back(indivs[roulette_select()]);
    }
    indivs = parents_pool;
}

void Island::calculate_fitness() {
    uint i;

    for (i = 0; i < pop_size; ++i){
        indivs[i].setFitness(calculate_indiv_fitness(indivs[i]));
    }
}


double Island::calculate_indiv_fitness(const Indiv &indiv) {
    uint i;
    uint tot_value = 0, tot_weight = 0, max_value=0;

    for(i = 0; i < items_value.size(); ++i){
        tot_value += indiv.get_gen(i) * items_value[i];
        tot_weight += indiv.get_gen(i) * items_weight[i];

        max_value +=  items_value[i];
    }

    if (tot_weight > knapsack_max_weigth)
        return 0;
    else
        return tot_weight/std::fabs(tot_value - max_value);
}

uint Island::roulette_select() {
    double r = rand() * tot_fit/RAND_MAX;
    uint i;
    for (i = 0; i < pop_size; ++i){
        r -= indivs[i].getFitness();
        if (r <= 0)
            return i;
    }
    throw Exception("Error in roulette select");
}

void Island::perform_crossover() {
    for (uint i = 0; i < pop_size; ++i){
        if (rand() <= RAND_MAX * p_cross){
            uint pos = rand() * (uint) parents_pool[i].size() / RAND_MAX;
            uint j = rand() * pop_size / RAND_MAX;

            Indiv tmp = parents_pool[i];
            parents_pool[i] = Indiv(parents_pool[i], parents_pool[j], pos);
            parents_pool[j] = Indiv(parents_pool[j], tmp, pos);
        }
    }
}

void Island::perform_mutation() {
    uint i;
    for (i = 0; i < pop_size; ++i)
        if (rand() <= RAND_MAX * p_mut){
            indivs[i].mutate();
        }
}


const Indiv& Island::get_fittest() {
    uint i, max_i = 0;
    double max_fitness = indivs[0].getFitness();

    for (i = 1; i < pop_size; ++i){
        if (indivs[i].getFitness() > max_fitness){
            max_i = i;
            max_fitness = indivs[i].getFitness();
        }
    }

    return indivs[max_i];
}



Chromosome Island::generate_random_chromosome() {
    uint i;
    Chromosome c(chromosome_size);
    for (i = 0; i < chromosome_size; ++i) {
        c[i] = rand() < (RAND_MAX / 2);     //TODO: think about distribution
    }
    return c;
}

uint Island::cacl_indiv_value(const Indiv &ind) const {
    uint i;
    uint tot_value = 0;

    for(i = 0; i < items_value.size(); ++i){
        tot_value += ind.get_gen(i) * items_value[i];
    }

    return tot_value;
}



