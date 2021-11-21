#include <iostream>
#include "../Generators/Random_generators.h"
#include "../Creators/Generator_creator.h"
#include "../Generator_fabric.h"

void test_poisson(){
    PoissonRandomGenerator g;
    for (int i=0; i<10; i++) {
        std::cout << g.generate() << std::endl;
    }
    return;
}

void test_bernoulli(){
    BernoulliRandomGenerator g;
    for (int i=0; i<10; i++) {
        std::cout << g.generate() << std::endl;
    }
    return;
}

void test_geometric(){
    GeometricRandomGenerator g;
    for (int i=0; i<10; i++) {
        std::cout << g.generate() << std::endl;
    }
    return;
}

void test_finite(){
    FiniteRandomGenerator g;
    for (int i=0; i<10; i++) {
        std::cout << g.generate() << std::endl;
    }
    return;
}

void test_custom(const std::unique_ptr<BaseRandomGenerator> &g){
    for (int i=0; i<10; i++) {
        std::cout << g->generate() << std::endl;
    }
    return;
}

int main(){
    //test_poisson();
    //test_bernoulli();
    //test_geometric();
    //test_finite();

    //ConcreteCreator<PoissonRandomGenerator> c;
    //c.create(0.5);

    RandomGenFabric f;
    auto g = f.create_obj("poisson");

    std::cout << g << std::endl;
    //std::cout << g->generate() << std::endl;

    //test_custom(g);

    return 0;
};