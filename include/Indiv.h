#ifndef GEN_INDIV_H
#define GEN_INDIV_H

#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

typedef vector<bool> Chromosome;

class Indiv {

    Chromosome chromosome;
    double fitness;

public:
    Indiv();
    Indiv(const vector<bool>& v);
    Indiv(const initializer_list<bool>& list);
    Indiv(const Indiv& indiv_p);
    Indiv(const Indiv& par1, const Indiv& par2, uint pos);    // Crossover constructor, LOL

    bool get_gen(uint i) const;
    uint size() const;

    double getFitness() const;
    void setFitness(double fitness);

    void mutate();

    friend ostream& operator<<(ostream& o, const Indiv& indiv);
};


#endif //GEN_INDIV_H
