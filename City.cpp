//
// Created by sammy on 11/29/2019.
//
#include <random>
#include <iostream>
#include "City.hpp"

int City::counter = 1;

City::City(int boundary) {
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<> num(0.0,boundary);
    x = num(rng);
    y = num(rng);
    sequenceNumber = counter++;
}

double City::getX() {
    return x;
}

double City::getY() {
    return y;
}

int City::getSeqNumber() {
    return sequenceNumber;
}

string City::getCoordinate() {
    return to_string(x) + " " + to_string(y);
}

City::~City() = default;
