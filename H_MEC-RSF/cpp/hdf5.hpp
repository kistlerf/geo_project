#ifndef HDF5_H
#define HDF5_H

#include <string>
#include <eigen3/Eigen/Eigen>
#include <H5Cpp.h>

using namespace std;
using namespace Eigen;
using namespace H5;

typedef VectorXd VecXd;
typedef MatrixXd MatXd;

void create_file(const string &filename);
void add_group(const string &filename, const string &groupname);
void add_matrix(const string &filename, const string &groupname, const MatXd& data, const string &dataset_name, hsize_t* dims);
void add_vector(const string &filename, const string &groupname, const VecXd& data, const string &dataset_name, hsize_t* dims);
MatXd read_matrix(const string &filename, const string &groupname, const string &dataset_name, hsize_t* dims);
VecXd read_vector(const string &filename, const string &groupname, const string &dataset_name, hsize_t* dims);

#endif