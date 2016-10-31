#include <iostream>
#include <fstream>

#include "Island.h"
#include "mpi.h"

using namespace std;

#define MAX_GEN 100
#define POPUL_SIZE 500
#define SEED 0  // Zero for time(0)

int main(int argc, char* argv[]){
    MPI::Init(argc, argv);
    MPI::COMM_WORLD.Set_errhandler(MPI::ERRORS_THROW_EXCEPTIONS);

    uint comm_size = MPI::COMM_WORLD.Get_size();
    uint rank = MPI::COMM_WORLD.Get_rank();

    if (argc != 2)
        throw Exception("No input file");
    ifstream f(argv[1]);
    if (f.bad())
        throw Exception("Could not open input file");

    uint size, n_items;
    vector<uint> items_value, items_weight;

    f >> size >> n_items;
    for (uint i = 0; i < n_items; ++i){
        uint value, weight;
        f >> value >> weight;
        items_value.push_back(value);
        items_weight.push_back(weight);
    }

    Island isl(size, items_value, items_weight, SEED?SEED*rank:rank*time(0));

    isl.start(MAX_GEN, POPUL_SIZE/comm_size);

    Indiv fittest = isl.get_fittest();
    cout << "Island " << rank << ": " << fittest << endl << isl.cacl_indiv_value(fittest) << endl;

    MPI::Finalize();
    return 0;
}