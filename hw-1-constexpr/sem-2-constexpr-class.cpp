

constexpr int square(const int x)
{
    int result = 0;
    for (int counter = 0; counter < x; ++counter) result += x;
    return result;
}

class ComplexNumber{
    double Re = 0;
    double Im = 0;

    public:
    constexpr ComplexNumber(const double _re, const double _im) :
        Re (_re),
        Im (_im)
    {};

    constexpr ComplexNumber(){};

    constexpr double GetRe() const {return this->Re;};
    constexpr double GetIm() const {return this->Im;}; 
    constexpr void SetIm(const double _Im) {this->Im = _Im; return;};

    constexpr bool operator==(const ComplexNumber& el) const {return (square(this->Re)) == (square(el.Re));}
};




constexpr ComplexNumber Conjugate(const ComplexNumber& x) {
    ComplexNumber res;
    res.SetRe(x.GetRe());
    res.SetIm(-x.GetIm());
return res;
}

int main() {
    constexpr ComplexNumber a(1, 2);
    constexpr ComplexNumber b(1, -2);
    constexpr auto c = Conjugate(a);
    static_assert(b == c, "failed");
}