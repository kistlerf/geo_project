#!/bin/sh

CPU_TYPE="XeonGold_6150"
MAIN_FILE="h_mec_rsf_v6.cpp"

echo "Terminate running job..."
bkill -J hmec_cpp

rm -rf EVO*
rm -rf lsf*
rm -rf *txt

printf "0" >> file.txt

export OMP_NUM_THREADS=1

echo "Load Intel Compiler and Eigen Library..."
module load intel/19.1.0 eigen/3.3.9 hdf5/1.10.7 libszip/2.1.1

echo "Compiling Program..."
icpc -std=c++17 -O3 -I/usr/include/eigen3 -I/cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_BSD_SOURCE -ftree-vectorize -march=corei7-avx -mavx -DEIGEN_USE_MKL_ALL -DMKL_LP64 -I/intel/mkl/include $MAIN_FILE -L/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl -L/cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/lib /cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/lib/libhdf5_hl_cpp.a /cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/lib/libhdf5_cpp.a /cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/lib/libhdf5_hl.a /cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/lib/libhdf5.a -lhdf5 -lsz -lz -lrt -Wl,-rpath -Wl,/cluster/apps/hdf5/1.8.13/x86_64/gcc_4.8.2/serial/lib -o cpp_pardiso.out

echo "Submitting Job..."
if [ -z "$CPU_TYPE" ]
then
	echo "No CPU Type specified..."
	bsub -W "24:00" -R "rusage[mem=10000]" -J hmec_cpp -o output.txt ./cpp_pardiso.out
else
	echo "Only using $CPU_TYPE"
	bsub -W "24:00" -R "rusage[mem=10000]" -R "select[model=$CPU_TYPE]" -J hmec_cpp -o output.txt ./cpp_pardiso.out
fi
