#include "cnf_builder.h"

#include <iostream>

int signal::var_cnt = 0;

signal::signal() {
    var = ++var_cnt;
    cnf = "";
}

signal signal::set_zero() {
    ostringstream ss;
    ss << cnf << "(" << -var << ")";
    cnf = ss.str();
}

signal signal::set_one() {
    ostringstream ss;
    ss << cnf << "(" << var << ")";
    cnf = ss.str();
}

signal signal::operator~() {
    signal v;
    int a = var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << "(" << y << " " << a << ")(" << -y << " " << -a << ")";
    v.cnf = ss.str();
    return v;
}

signal signal::operator|(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << signal_b.cnf << "(" << y << " " << a << " " << b << ")(" << y << " " << -a << ")("
       << y << " " << -b << ")";
    v.cnf = ss.str();
    return v;
}

signal signal::operator&(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << signal_b.cnf << "(" << -y << " " << -a << " " << -b << ")(" << y << " " << a
       << ")(" << y << " " << b << ")";
    v.cnf = ss.str();
    return v;
}

signal signal::operator^(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    ostringstream ss;
    ss << cnf << signal_b.cnf << "(" << y << " " << a << " " << -b << ")(" << y << " " << -a << " "
       << b << ")(" << -y << " " << a << " " << b << ")(" << -y << " " << -a << " " << -b << ")";
    v.cnf = ss.str();
    return v;
}

void signal::print() {
    // print the cnf array as PoS string
}