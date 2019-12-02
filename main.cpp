#include <iostream>
#include <random>
#include <iomanip>
#include "Tour.hpp"

using namespace std;

void swapToFront(vector<Tour *> &population, int index) {
    Tour *tmp = population[0];
    population.assign(0, population[index]);
    population.assign(index, tmp);
}

size_t getFittest(vector<Tour *> population) {
    Tour *fittestTour = population[0];
    size_t fittestTourIndex = 0;
    for (size_t i = 1; i < population.size(); ++i)
        if (population[i]->getFitnessRating() > fittestTour->getFitnessRating()) {
            fittestTour = population[i];
            fittestTourIndex = i;
        }
    return fittestTourIndex;
}

vector<Tour *> select_parents(vector<Tour *> &population) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<> num(0, POPULATION_SIZE - 1);

    size_t fittest = 0;

    vector<Tour *> parents{NUMBER_OF_PARENTS};
    vector<Tour *> parent_pool{PARENT_POOL_SIZE};

    for (int i = 0; i < NUMBER_OF_PARENTS; ++i) {
        for (int j = 0; j < PARENT_POOL_SIZE; ++j) {
            int k = num(rng);
            parent_pool[j] = population[k];
        }
        fittest = getFittest(parent_pool);
        parents[i] = parent_pool[fittest];
    }
    return parents;
}

bool containsCity(Tour *candidate_tour, int boundary, City *city) {
    for (int i = 0; i < boundary; ++i) {
        if (candidate_tour->cities[i]->getSeqNumber() == city->getSeqNumber() &&
            candidate_tour->cities[i]->getX() == city->getX() &&
            candidate_tour->cities[i]->getY() == city->getY()) {
            return true;
        }
    }
    return false;
}

Tour *crossover(vector<Tour *> &parents) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<> num(0, CITIES_IN_TOUR - 1);
    Tour *child = new Tour;
    int boundaryIndex = num(rng);

    for (int i = 0; i < boundaryIndex; ++i) {
        child->cities[i] = parents[0]->cities[i];
    }

    while (boundaryIndex < CITIES_IN_TOUR) {
        for (int i = 0; i < CITIES_IN_TOUR; ++i) {
            if (!containsCity(child, boundaryIndex, parents[1]->cities[i])) {
                child->cities[boundaryIndex] = parents[1]->cities[i];
                boundaryIndex++;
            }
        }
    }
    return child;
}

void mutate(vector<Tour *> &population) {
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<> dRand(0, 1);
    uniform_int_distribution<> iRand(0, CITIES_IN_TOUR - 1);

    for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
        for (int j = 0; j < CITIES_IN_TOUR; ++j) {
            if (dRand(rng) <= MUTATION_RATE) {
                int rand = iRand(rng);
                City *temp = population[i]->cities[j];
                population[i]->cities[j] = population[i]->cities[rand];
                population[i]->cities[rand] = temp;
            }
        }
    }
}

int main() {
    vector<City *> cities{CITIES_IN_TOUR};
    vector<Tour *> population{POPULATION_SIZE};
    vector<Tour *> cross{POPULATION_SIZE - NUMBER_OF_ELITES};

    for (int i = 0; i < CITIES_IN_TOUR; ++i)
        cities[i] = new City(MAP_BOUNDARY);

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Tour *tour = new Tour(cities);
        for (int j = 0; j < SHUFFLES; ++j)
            tour->shuffleCities();
        tour->determineFitness();
        population[i] = tour;
    }

    size_t fittestTourIndex = getFittest(population);
    Tour *fittestTour = population.at(fittestTourIndex);

    double baseDistance = fittestTour->getTourDistance();
    double bestDistance = 0.0;

    cout << "Initial Shortest Distance: " << fixed << setprecision(3) << baseDistance << endl;
    cout << "=============================================================" << endl;

    int i = 0;

    for (i = 0; i < ITERATIONS && baseDistance / bestDistance > IMPROVEMENT_FACTOR; ++i) {
        if (fittestTourIndex != 0)
            swapToFront(population, fittestTourIndex);

        for (int j = 0; j < (POPULATION_SIZE - NUMBER_OF_ELITES); ++j) {
            vector<Tour *> parents = select_parents(population);
            cross[j] = crossover(parents);
        }

        for (int k = NUMBER_OF_ELITES; k < POPULATION_SIZE; ++k) {
            population[k] = cross[k - NUMBER_OF_ELITES];
            population[k]->determineFitness();
        }

        mutate(population);

        fittestTourIndex = getFittest(population);
        fittestTour = population[fittestTourIndex];
        bestDistance = fittestTour->getTourDistance();

        cout << "Iteration: " << i << " Best Distance: " << fixed << setprecision(3) << bestDistance << endl;
    }

    cout << "=============================================================" << endl;
    cout << "Iterations: " << i << endl;
    cout << "Base distance: " << baseDistance << " Best Distance: " << bestDistance << endl;
    cout << "Achieved improvement factor" << (baseDistance / bestDistance > IMPROVEMENT_FACTOR) << endl;

    for (City *city : cities)
        delete city;

    for (Tour *tour : population)
        delete tour;
}
