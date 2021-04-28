#include "cnf_builder.h"

#include <iostream>

int signal::var_cnt = 0;

signal::signal() {
    var = ++var_cnt;
    cnf = "\n";
}

void signal::set_zero() {
    ostringstream ss;
    ss << cnf << "\n" << -var;
    cnf = ss.str();
}

void signal::set_one() {
    ostringstream ss;
    ss << cnf << "\n" << var;
    cnf = ss.str();
}

signal signal::operator~() {
    signal v;
    int a = var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << "\n" << y << " " << a << "\n" << -y << " " << -a;
    v.cnf = ss.str();
    return v;
}

signal signal::operator|(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << signal_b.cnf << "\n"
       << -y << " " << a << " " << b << "\n"
       << y << " " << -a << "\n"
       << y << " " << -b;
    v.cnf = ss.str();
    return v;
}

signal signal::operator&(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << signal_b.cnf << "\n"
       << y << " " << -a << " " << -b << "\n"
       << -y << " " << a << "\n"
       << -y << " " << b;
    v.cnf = ss.str();
    return v;
}

signal signal::operator^(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << signal_b.cnf << "\n"
       << y << " " << a << " " << -b << "\n"
       << y << " " << -a << " " << b << "\n"
       << -y << " " << a << " " << b << "\n"
       << -y << " " << -a << " " << -b;
    v.cnf = ss.str();
    return v;
}

void signal::print() {
    // print the cnf array as PoS string
}

// void sat_solve(){
//     // write the cnf to <var>.cnf
//     // run minisat_static
//     // read <var>.out and parse results
// }