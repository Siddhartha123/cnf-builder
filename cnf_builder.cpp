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

signal signal::cofactor(int x, int flag) {
    signal f_x;
    clause c;
    bool zero, one = false;
    set<int> single_literals;

    int loi = x * flag;
    for (CNF::iterator i = formula.begin(); i != formula.end(); i++) {
        c = *i;
        // if c is present in x.formula then ignore c
        // if (x.formula.find(c) != x.formula.end()) continue;

        // replace var with f_x.var
        if (c.find(var) != c.end()) {
            c.erase(c.find(var));
            c.insert(f_x.var);
        } else if (c.find(-var) != c.end()) {
            c.erase(c.find(-var));
            c.insert(-f_x.var);
        }

        // if c contains loi then ignore c
        if (c.find(loi) != c.end()) continue;

        if (c.find(-loi) != c.end()) {
            c.erase(c.find(-loi));
            if (c.empty()) zero = true;
        }
        // if c contains x.var, and flag==-1 then form a new clause with all literals of c except
        // x.var if c contains -x.var, and flag==1 then form a new clause with all literals of c
        // except -x.var

        if (c.size() == 1) {
            if (*(c.begin()) == f_x.var) {
                one = true;
                break;
            } else if (*(c.begin()) == -f_x.var) {
                zero = true;
                break;
            }
            single_literals.insert(*(c.begin()));
        }
        if (!c.empty()) f_x.formula.insert(c);
    }

    if (zero) {
        f_x.formula.clear();
        f_x.set_zero();
        return f_x;
    }
    if (one) {
        f_x.formula.clear();
        f_x.set_one();
        return f_x;
    }
    if (single_literals.size() == 0) return f_x;

    loi = *(single_literals.begin());
    int f = loi / abs(loi);
    return f_x.cofactor(loi, f);
}