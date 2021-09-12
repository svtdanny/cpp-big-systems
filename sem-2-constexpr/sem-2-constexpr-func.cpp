
#include <array>
#include <iostream>

constexpr int get_cofactor(const int i, const int j){
    return (i+j) % 2 == 0? 1 : -1;
}

template<int N>
constexpr std::array<std::array<int, N - 1>, N - 1> get_submatrix(const std::array<std::array<int, N>, N>& a, int i, int j) {
    std::array<std::array<int, N - 1>, N - 1> r{};
    for (int ii = 0; ii != N - 1; ++ii)
        for (int jj = 0; jj != N - 1; ++jj)
            (&std::get<0>(((&std::get<0>(r))[ii])))[jj] = a[ii + (ii >= i ? 1 : 0)][jj + (jj >= j ? 1 : 0)];
    return r;
}

template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a) {
    int det_agg = 0;

    for (int row = 0; row < N; row++) {
            det_agg += get_cofactor(row, 0) * a[row][0] * det<N-1>(get_submatrix<N>(a, row, 0));
        }

    return det_agg;
}

template <>
constexpr int det<2>(const std::array<std::array<int, 2>, 2>& a) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

template <>
constexpr int det<1>(const std::array<std::array<int, 1>, 1>& a) {
    return a[0][0];
}



int main() {
constexpr std::array<std::array<int, 3>, 3> A = {{
{0, 1, 2}
,{1, 2, 3}
,{2, 3, 7}
}};
constexpr int res = det<3>(A);
}









/*
constexpr int get_cofactor_coef(int i, int j) {
    return (i + j) % 2 == 0 ? 1 : -1;
}

template <int N>
constexpr int determinant(const std::array<std::array<int, N>, N>& a) {
    int det = 0;

    for (size_t i = 0u; i < N; ++i) {
        det += get_cofactor_coef(i, 1) * a[i][0] * determinant<N-1>(GET_SUBMATRIX_OF_A<N-1, I, J>(a);
    }

    return det;
}

template <>
constexpr int determinant<2>(const std::array<std::array<int, 2>, 2>& a) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

template <>
constexpr int determinant<1>(const std::array<std::array<int, 1>, 1>& a) {
    return a[0][0];
}
*/