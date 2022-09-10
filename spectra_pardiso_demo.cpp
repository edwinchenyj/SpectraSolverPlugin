#include "src/pardiso_spd_solver.h"
#include "src/SparseGenRealShiftSolvePardiso.h"
#include "Spectra/GenEigsRealShiftSolver.h"
#include "Spectra/MatOp/SparseGenRealShiftSolve.h"

#include "unsupported/Eigen/SparseExtra"
#include <Eigen/Sparse>
#include <chrono>

int main(){
    Eigen::SparseMatrix<double> A;
    Eigen::loadMarket(A, "A.mtx");
    std::cout<<"A size: "<<A.rows()<<"x"<<A.cols()<<std::endl;
    size_t eigen_space_dimension = 5;
    
    std::chrono::steady_clock::time_point begin_pardiso = std::chrono::steady_clock::now();
    Spectra::SparseGenRealShiftSolvePardiso<double> op_pardiso(A);
    Spectra::GenEigsRealShiftSolver<Spectra::SparseGenRealShiftSolvePardiso<double>> eigs_pardiso(op_pardiso, eigen_space_dimension, 2*eigen_space_dimension, 0.01);
    std::chrono::steady_clock::time_point end_pardiso = std::chrono::steady_clock::now();

    std::cout << "Spectra pardiso time = " << std::chrono::duration_cast<std::chrono::microseconds>(end_pardiso - begin_pardiso).count() << "[µs]" << std::endl;

    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // Spectra::SparseGenRealShiftSolve<double> op(A);
    // Spectra::GenEigsRealShiftSolver<Spectra::SparseGenRealShiftSolve<double>> eigs(op, eigen_space_dimension, 2*eigen_space_dimension, 0.01);
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    // std::cout << "Spectra time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return 0;
}