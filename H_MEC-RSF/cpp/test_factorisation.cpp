#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace std;
using namespace Eigen;

int main() {
    int N = 5;
    SparseMatrix<double> L(N, N);
    VectorXd R(N);
    VectorXd S(N);

    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    tripletList.reserve(N + 1);

    for (int i = 0; i < N - 1; i++) tripletList.push_back(T(i, i, 1));

    tripletList.push_back(T(2, 0, 9));
    tripletList.push_back(T(3, 4, 7));
    tripletList.push_back(T(4, 0, 1));


    L.setFromTriplets(tripletList.begin(), tripletList.end());

    /*
    L.insert(1, 1) = 10;
    L.insert(2, 0) = 9;
    L.insert(3, 4) = 7;
    */
    R << 0, 2, 1, 5, 0;

    cout << L << endl;

    SparseLU<SparseMatrix<double>> solver;
    // L.makeCompressed();
    solver.analyzePattern(L);
    solver.factorize(L);
    S = solver.solve(R);

    cout << S << endl;

    return 0;
}