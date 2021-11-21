#ifndef CPP_COURSE_MSU_GENERATOR_FABRIC_H
#define CPP_COURSE_MSU_GENERATOR_FABRIC_H

#include <unordered_map>
#include "Creators/Generator_creator.h"

class RandomGenFabric{
private:
    using FactoryMap = std::unordered_map<std::string, std::unique_ptr<CreatorGenBase>>;
    FactoryMap _factory;
public:
    RandomGenFabric(){
        _factory = FactoryMap();

        _factory["poisson"] =  std::make_unique<ConcreteCreator<PoissonRandomGenerator>>();
        _factory["bernoulli"] = std::make_unique<ConcreteCreator<BernoulliRandomGenerator>>();
        _factory["geometric"] = std::make_unique<ConcreteCreator<GeometricRandomGenerator>>();
        _factory["finite"] = std::make_unique<ConcreteCreator<FiniteRandomGenerator>>();

    }

    std::unique_ptr<BaseRandomGenerator> create_obj(const std::string & obj){
        FactoryMap::iterator it = _factory.find(obj);
        if (it != _factory.end()){
            std::cout << "created" << std::endl;
            return it->second->create();
        }
        return nullptr;
    }
};


#endif //CPP_COURSE_MSU_GENERATOR_FABRIC_H
