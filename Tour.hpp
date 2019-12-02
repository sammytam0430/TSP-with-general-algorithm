//
// Created by sammy on 11/29/2019.
//

#ifndef ASSIGNMENT2_TOUR_HPP
#define ASSIGNMENT2_TOUR_HPP

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include "City.hpp"

using namespace std;

class Tour {
private:
public:
    double fitnessRating;

    vector<City *> cities;

    Tour();

    Tour(const vector<City *> &);

    double getFitnessRating();

    void shuffleCities();

    static double getDistanceBetweenCities(City *, City *);

    double getTourDistance();

    void determineFitness();

    void print();

    ~Tour();
};

#endif //AS&SIGNMENT2_TOUR_HPP
