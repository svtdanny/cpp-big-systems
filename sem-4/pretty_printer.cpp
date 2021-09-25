#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

struct Printer {
    std::string str() const {
        return (this->buff_stream).str();
    }; // возвращает строковое представление
    
    // далее перегруженные/шаблонные функции вида:

    template <typename NestedType>
    Printer& format(const std::vector<NestedType> & obj) {
        buff_stream << '['; 
        this->_iterative_print(obj);
        buff_stream << ']';

        return *this;
    }

    template <typename NestedType>
    Printer& format(const std::set<NestedType> & obj) {
        buff_stream << '{'; 
        this->_iterative_print(obj);
        buff_stream << '}';

        return *this;
    }

    template <typename... InternalType, template<typename...> typename ComprehType>
    Printer& format(const ComprehType<InternalType...> & obj) {
        std::apply
        (   
            [this](const InternalType&... tupleArgs)
            {
                buff_stream << '(';
                std::size_t n{0};
                ((buff_stream << tupleArgs << (++n != sizeof...(InternalType) ? ", " : "")), ...);
                buff_stream << ')';
            }, 
            obj
        );
        
        return *this;
    }

    template <typename Type>
    void _iterative_print(const Type& obj) {
        bool first = true;
        for (typename Type::const_iterator nested_obj  = obj.begin() ; nested_obj != obj.end(); ++nested_obj){
            if (first) {
                first = false;
            } else {
                buff_stream << ", ";
            }
                
            
            this->format(*nested_obj);
        }

    }

    template <typename BaseType>
    Printer& format(const BaseType&  obj) {

        buff_stream << obj;

        return *this;
    }


    protected:
        std::stringstream buff_stream;
};

template<typename T>
std::string format(const T& t) {
    return Printer().format(t).str();
}


int main() {
std::tuple<std::string, int, int> t = {"xyz", 1, 2};
std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
std::string s1 = Printer().format(" vector: ").format(v).str();
std::cout << s1 << std::endl;
// " vector: [ (1, 4), (5, 6) ]"


std::string s2 = Printer().format(t).format(" ! ").format(0).str();
std::cout << s2 << std::endl;
// "( xyz, 1, 2 ) ! 0"


std::vector<int> my_v = {1, 4, 5, 6};
std::string s3 = Printer().format(" vector: ").format(std::vector<int>({1,2,3})).str();
std::cout << s3<< std::endl;

std::set s{1, 2, 3, 4};
std::string s4 = Printer().format(" set: ").format(s).str();
std::cout << s4  << std::endl;

return 0;
}
