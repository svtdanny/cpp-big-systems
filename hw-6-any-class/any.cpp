#include <iostream>
#include <string>

class Any{
public:
    template<typename T>
    Any(const T& _v){
        v = std::unique_ptr<BaseHolder>(static_cast<BaseHolder*>(new Holder<T>(_v)));
    };

    template<typename T>
    T get(){
        auto holder = static_cast<Holder<T>*>(v.get());
        if (typeid(T) != holder->type_info()){
            throw std::runtime_error("Bad cast");
        }

        return holder->_value;
    }

private:
    struct BaseHolder{
        virtual ~ BaseHolder(){};
        virtual const std::type_info& type_info() const = 0;
    };
    template<typename T> struct Holder: Any::BaseHolder{
        Holder(const T & value): _value(value){};
        const std::type_info& type_info() const {
            return typeid(_value);
        }
        T _value;
    };

    std::unique_ptr<BaseHolder> v;
};

int main(){
    Any a(3);
    auto value1 = a.get<int>();
    //auto value2 = a.get<unsigned int>(); // Bad cast

    std::cout << value1 << std::endl;

    return 0;
}