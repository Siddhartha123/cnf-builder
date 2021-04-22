#ifndef CNF_BUILDER_H
#define CNF_BUILDER_H
#include <sstream>
#include <string>

using namespace std;

class signal {
   public:
    static int var_cnt;
    int var;
    string cnf;

    signal();
    // signal(bool create_var);
    signal set_zero();
    signal set_one();
    signal operator~();
    signal operator|(signal signal_b);
    signal operator&(signal signal_b);
    signal operator^(signal signal_b);
    void print();
};
#endif