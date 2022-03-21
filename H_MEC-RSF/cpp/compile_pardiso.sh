#!/bin/sh

bkill -J hmec_cpp

rm -rf EVO*
rm -rf lsf*
rm -rf *txt

printf "0" >> file.txt

export OMP_NUM_THREADS=1

module load intel/19.1.0 eigen/3.3.9

icpc -std=c++11 -O3 -I/usr/include/eigen3 -DEIGEN_USE_MKL_ALL -DMKL_LP64 -I/intel/mkl/include h_mec_rsf_v3.cpp -L/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl -o h_mec_cpp_pardiso

bsub -W "24:00" -R 'rusage[mem=10000]' -J hmec_cpp -o output.txt ./h_mec_cpp_pardiso
