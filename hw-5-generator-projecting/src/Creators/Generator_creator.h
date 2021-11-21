//
// Created by Сивцов Данил on 21.11.2021.
//

#ifndef CPP_COURSE_MSU_GENERATOR_CREATOR_H
#define CPP_COURSE_MSU_GENERATOR_CREATOR_H

#include <memory>
#include "../Generators/Random_generators.h"

class CreatorGenBase {
protected:
    using BaseGen = std::unique_ptr<BaseRandomGenerator>;
public:

    virtual BaseGen create(){
        std::cout << "dummy" << std::endl;
        return nullptr;};

};

template<typename T>
class ConcreteCreator:public CreatorGenBase {
public:
    using Gen = std::unique_ptr<T>;

    template<typename... Args>
    BaseGen create(Args... args){
        return Gen(new T(args...));
    }
};


/*
class CreatorGenBernoulli:CreatorGenBase {
    using BernoulliGen = std::unique_ptr<BernoulliRandomGenerator>

    BernoulliGen create(double lambda){
        return BernoulliGen(std::move(BernoulliRandomGenerator(lambda)));
    }
};
 */



#endif //CPP_COURSE_MSU_GENERATOR_CREATOR_H
