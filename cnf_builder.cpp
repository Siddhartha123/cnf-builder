#include "cnf_builder.h"

int signal::var_cnt = 0;

signal::signal() { var = ++var_cnt; }

void signal::set_zero() { formula.insert({-var}); }

void signal::set_one() { formula.insert({var}); }

signal signal::operator~() {
    signal v;
    int a = var;
    int y = v.var;
    v.formula.insert(formula.begin(), formula.end());
    v.formula.insert({y, a});
    v.formula.insert({-y, -a});
    return v;
}

signal signal::operator|(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    v.formula.insert(formula.begin(), formula.end());
    v.formula.insert(signal_b.formula.begin(), signal_b.formula.end());
    v.formula.insert({-y, a, b});
    v.formula.insert({y, -a});
    v.formula.insert({y, -b});
    return v;
}

signal signal::operator&(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    v.formula.insert(formula.begin(), formula.end());
    v.formula.insert(signal_b.formula.begin(), signal_b.formula.end());
    v.formula.insert({y, -a, -b});
    v.formula.insert({-y, a});
    v.formula.insert({-y, b});
    return v;
}

signal signal::operator^(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    v.formula.insert(formula.begin(), formula.end());
    v.formula.insert(signal_b.formula.begin(), signal_b.formula.end());
    v.formula.insert({y, a, -b});
    v.formula.insert({y, -a, b});
    v.formula.insert({-y, a, b});
    v.formula.insert({-y, -a, -b});
    return v;
}

void signal::print() {
    for (CNF::iterator i = formula.begin(); i != formula.end(); i++) {
        clause c = *i;
        cout << "( ";
        for (clause::iterator j = c.begin(); j != c.end(); j++) cout << *j << " ";
        cout << ")";
    }
}

void sat_solve(CNF formula, int var_cnt, string filename) {
    ostringstream ss;
    ofstream infile;
    infile.open(filename);
    infile << "p cnf " << var_cnt << " " << formula.size();
    clause c;
    for (CNF::iterator i = formula.begin(); i != formula.end(); i++) {
        infile << "\n";
        c = *i;
        for (clause::iterator j = c.begin(); j != c.end(); j++) infile << *j << " ";
        infile << " 0";
    }
    infile.close();
    ss << "minisat_static " << filename << " " << filename << ".out";
    system(ss.str().c_str());
}