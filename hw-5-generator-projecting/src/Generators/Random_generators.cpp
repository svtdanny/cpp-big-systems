#include "Random_generators.h"

//Base
BaseRandomGenerator::BaseRandomGenerator() {
    std::random_device rd;
    gen = std::mt19937(rd());
}

//Poisson
PoissonRandomGenerator::PoissonRandomGenerator(): distro(1){};
PoissonRandomGenerator::PoissonRandomGenerator(double _lambda): distro(_lambda) {};

double PoissonRandomGenerator::generate() {
    return distro(gen);
}

//Bernoulli
BernoulliRandomGenerator::BernoulliRandomGenerator(): distro(0.5) {};
BernoulliRandomGenerator::BernoulliRandomGenerator(double _p): distro(_p) {};

double BernoulliRandomGenerator::generate() {
    return distro(gen);
}

//Geometric
GeometricRandomGenerator::GeometricRandomGenerator(): distro(0.5) {};
GeometricRandomGenerator::GeometricRandomGenerator(double _p): distro(_p) {};

double GeometricRandomGenerator::generate() {
    return distro(gen);
}

//Finite
FiniteRandomGenerator::FiniteRandomGenerator(): values{1, 2, 3, 4, 5}, distro({10, 20, 40, 20, 10}) {};
FiniteRandomGenerator::FiniteRandomGenerator(std::vector<double> _values, std::vector<double> _probas):
values(_values), probas(_probas), distro(_probas.begin(), _probas.end())
{};

double FiniteRandomGenerator::generate() {
    int _rand_index = distro(gen);
    return values[_rand_index];
}