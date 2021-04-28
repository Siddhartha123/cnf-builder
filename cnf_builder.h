#ifndef CNF_BUILDER_H
#define CNF_BUILDER_H
#include <iterator>
#include <set>
#include <sstream>
#include <string>

using namespace std;

class signal {
   public:
    static int var_cnt;
    int var;
    set<string> cnf;

    signal();
    void set_zero();
    void set_one();
    signal operator~();
    signal operator|(signal signal_b);
    signal operator&(signal signal_b);
    signal operator^(signal signal_b);
    void print();
    // void sat_solve();
};
#endif