//
// Created by sammy on 11/29/2019.
//

#ifndef ASSIGNMENT2_CITY_HPP
#define ASSIGNMENT2_CITY_HPP

#include <string>

const int CITIES_IN_TOUR = 32; //user
const int POPULATION_SIZE = 32; //user
const int SHUFFLES = 64;
const int ITERATIONS = 1000;
const int MAP_BOUNDARY = 1000;
const int PARENT_POOL_SIZE = 10;
const double MUTATION_RATE = 0.3; //user
const int NUMBER_OF_PARENTS = 2;
const int NUMBER_OF_ELITES = 1;
const double IMPROVEMENT_FACTOR = 0.1;
const int FITNESS_SCALAR = 320000;

using namespace std;

class City {
private:
    static int counter;
    double x;
    double y;
    int sequenceNumber;
public:
    explicit City(int);

    double getX();

    double getY();

    int getSeqNumber();

    string getCoordinate();

    ~City();
};


#endif //ASSIGNMENT2_CITY_HPP
