#ifndef CNF_BUILDER_H
#define CNF_BUILDER_H
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

using namespace std;

typedef set<int> clause;
typedef set<clause> CNF;

class signal {
   public:
    static int var_cnt;
    int var;
    CNF formula;

    signal();
    void set_zero();
    void set_one();
    signal operator~();
    signal operator|(signal signal_b);
    signal operator&(signal signal_b);
    signal operator^(signal signal_b);
    void print();
};

void sat_solve(CNF formula, int var_cnt, string filename);

#endif