#include <iostream>
#include <set>
#include <list>
#include <unistd.h>
#include "undirectedgraph.h"
#include "exceptions.h"
//#include "matrix.h"
#include "pybind11/pybind11.h"
#include "pybind11/eigen.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"
#include <eigen3/Eigen/Dense>

namespace py = pybind11;

// Ref: pybind11 doc page 92
typedef Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> MatrixXb_t;
typedef Eigen::Matrix<unsigned, Eigen::Dynamic, 1> VectorXu_t;
typedef Eigen::Ref<const MatrixXb_t> ConMat_t;
typedef Eigen::Ref<const VectorXu_t> NoWeight_t;

void Matrix2UndirectedGraph(const ConMat_t &c_mat, 
                            const NoWeight_t &w_mat,
                            UndirectedGraph &g){

    unsigned r = c_mat.rows();
    unsigned c = c_mat.cols();

    for (unsigned i = 0; i < r; i++){
        g.add_vertex(i, w_mat(i,0));
        for (unsigned j = 0; j < c; j++){
            if (c_mat(i,j))
                g.add_edge(i, j);
        }
    }

    return ;
}

std::list<unsigned> mwis(const ConMat_t &connection, const NoWeight_t &weights){
    UndirectedGraph g1;
    Matrix2UndirectedGraph(connection, weights, g1);

    UndirectedGraph g2 = g1;

    // Run two different greedy algorithms to solve the NP-hard MWIS problem,
    // and return the better one.

    std::list<unsigned> gwmin_is = g1.mwis_greedy_gwmin();
    unsigned gmin_weight = g1.weight_of_set(gwmin_is);

    std::list<unsigned> gwmax_is = g2.mwis_greedy_gwmax();
    unsigned gmax_weight = g2.weight_of_set(gwmax_is);

    return gmin_weight > gmax_weight ? gwmin_is : gwmax_is;
}


PYBIND11_MODULE(mwis, m){
    m.doc() = "A C++ library for an approximation of solving Maximum Weighted"
              "Independent Set (MWIS) problem.";
    m.def("mwis", &mwis, "Takes an undirected graph, and solve it as a MWIS"
                         "problem.",
            py::arg("connection"),
            py::arg("weights"));
}

