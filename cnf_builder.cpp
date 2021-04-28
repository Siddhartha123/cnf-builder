#include "cnf_builder.h"

#include <iostream>

int signal::var_cnt = 0;

signal::signal() {
    var = ++var_cnt;
}

void signal::set_zero() {
    ostringstream ss;
    ss << -var;
    cnf.insert(ss.str());
}

void signal::set_one() {
    ostringstream ss;
    ss << var;
    cnf.insert(ss.str());
}

signal signal::operator~() {
    signal v;
    int a = var;
    int y = v.var;
    v.cnf.insert(cnf.begin(), cnf.end());
    ostringstream ss;
    ss << y << " " << a;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << -y << " " << -a;
    v.cnf.insert(ss.str());
    return v;
}

signal signal::operator|(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    v.cnf.insert(cnf.begin(), cnf.end());
    v.cnf.insert(signal_b.cnf.begin(), signal_b.cnf.end());
    ostringstream ss;
    ss << -y << " " << a << " " << b;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << y << " " << -a;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << y << " " << -b;
    v.cnf.insert(ss.str());
    return v;
}

signal signal::operator&(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    v.cnf.insert(cnf.begin(), cnf.end());
    v.cnf.insert(signal_b.cnf.begin(), signal_b.cnf.end());
    ostringstream ss;
    ss << y << " " << -a << " " << -b;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << -y << " " << a;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << -y << " " << b;
    v.cnf.insert(ss.str());
    return v;
}

signal signal::operator^(signal signal_b) {
    signal v;
    int a = var;
    int b = signal_b.var;
    int y = v.var;
    v.cnf.insert(cnf.begin(), cnf.end());
    v.cnf.insert(signal_b.cnf.begin(), signal_b.cnf.end());
    ostringstream ss;
    ss << y << " " << a << " " << -b;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << y << " " << -a << " " << b;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << -y << " " << a << " " << b;
    v.cnf.insert(ss.str());
    ss.str("");
    ss.clear();
    ss << -y << " " << -a << " " << -b;
    v.cnf.insert(ss.str());
    return v;
}

void signal::print() {
    for (set<string>::iterator i = cnf.begin(); i != cnf.end(); i++)
        cout << "(" << *i << ")";
}