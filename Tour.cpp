//
// Created by sammy on 11/29/2019.
//

#include "Tour.hpp"
#include <random>

Tour::Tour() {
    fitnessRating = 0;
    cities = vector<City *>{CITIES_IN_TOUR};
}

Tour::Tour(const vector<City *> &cityList) {
    fitnessRating = 0;
    for (City *city : cityList) {
        this->cities.push_back(city);
    }
}

double Tour::getFitnessRating() {
    return fitnessRating;
}

void Tour::shuffleCities() {
    shuffle(cities.begin(), cities.end(), mt19937(random_device()()));
}

double Tour::getDistanceBetweenCities(City *c1, City *c2) {
    double distanceX = c2->getX() - c1->getX();
    double distanceY = c2->getY() - c1->getY();
    return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
}

double Tour::getTourDistance() {
    double totalDistance = 0;
    for (size_t i = 1; i < cities.size(); ++i) {
        totalDistance += getDistanceBetweenCities(cities[i], cities[i - 1]);
    }
    return totalDistance;
}

void Tour::determineFitness() {
    fitnessRating =  FITNESS_SCALAR / getTourDistance();
}

void Tour::print() {
    cout << fitnessRating << endl;
}

Tour::~Tour() = default;