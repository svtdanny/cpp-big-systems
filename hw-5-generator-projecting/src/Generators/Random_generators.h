#include <map>
#include <vector>
#include <random>

#ifndef CPP_COURSE_MSU_RANDOM_GENERATORS_H
#define CPP_COURSE_MSU_RANDOM_GENERATORS_H

class BaseRandomGenerator{
public:
    BaseRandomGenerator();
    BaseRandomGenerator(const BaseRandomGenerator&) = default;

    virtual double generate() = 0;
    virtual ~BaseRandomGenerator() {};

    std::mt19937 gen;
};

class PoissonRandomGenerator: BaseRandomGenerator{
public:
    PoissonRandomGenerator();
    PoissonRandomGenerator(double);
    double generate();
protected:
    std::poisson_distribution<> distro;
};

class BernoulliRandomGenerator: BaseRandomGenerator{
public:
    BernoulliRandomGenerator();
    BernoulliRandomGenerator(double);
    double generate();
protected:
    std::bernoulli_distribution distro;
};

class GeometricRandomGenerator: BaseRandomGenerator{
public:
    GeometricRandomGenerator();
    GeometricRandomGenerator(double);
    double generate();
protected:
    std::geometric_distribution<> distro;
};

class FiniteRandomGenerator: BaseRandomGenerator{
public:
    FiniteRandomGenerator();
    FiniteRandomGenerator(std::vector<double>, std::vector<double>);
    double generate();
protected:
    std::discrete_distribution<> distro;
    std::vector<double> values;
    std::vector<double> probas;
};

#endif //CPP_COURSE_MSU_RANDOM_GENERATORS_H
