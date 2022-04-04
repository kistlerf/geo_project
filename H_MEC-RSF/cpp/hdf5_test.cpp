#include <iostream>
#include <string>
#include <eigen3/Eigen/Eigen>
#include <hdf5/serial/H5Cpp.h>

using namespace std;
using namespace Eigen;
using namespace H5;

const int RANK = 2;

/*
inputs:
    string filename
*/
void create_file(const string &filename) {
    H5File *file = new H5File(filename, H5F_ACC_TRUNC);

    delete file;
}

/*
inputs:
    string filename
    string groupname
*/
void add_group(const string &filename, const string &groupname) {
    H5File *file = new H5File(filename, H5F_ACC_RDWR);
    Group* group = new Group(file->createGroup("/" + groupname));

    delete group;
    delete file;
}

/*
inputs:
    string filename
    string groupname
    MatrixXd data -> pointer to matrix to store
    string dataset_name -> name the stored data
    int* dims -> 2 dimensional array with dimensions (x and y) of stored data
*/
void add_data(const string &filename, const string &groupname, MatrixXd& data, const string &dataset_name, hsize_t* dims) {
    H5File *file = new H5File(filename, H5F_ACC_RDWR);
    Group* group = new Group(file->openGroup(groupname));

    DataSpace *dataspace = new DataSpace(RANK, dims);
    DataSet* dataset = new DataSet(file->createDataSet("/" + groupname + "/" + dataset_name, PredType::NATIVE_DOUBLE, *dataspace));

    dataset->write(&data, PredType::NATIVE_DOUBLE);

    delete dataset;
    delete dataspace;
    delete group;
    delete file;
}

/*
inputs:
    string filename
    string groupname
    string dataset_name -> name the stored data
    int* dims -> 2 dimensional array with dimensions (x and y) of stored data
output:
    MatrixXd data_out -> data saved in "dataset_name"
*/
MatrixXd read_data(const string &filename, const string &groupname, const string &dataset_name, hsize_t* dims) {
    MatrixXd data_out(dims[0], dims[1]);
    
    H5File *file = new H5File(filename, H5F_ACC_RDONLY);
    Group* group = new Group(file->openGroup(groupname));
    DataSpace *dataspace = new DataSpace(RANK, dims);
    DataSet* dataset = new DataSet(group->openDataSet(dataset_name));

    dataset->read(&data_out, PredType::NATIVE_DOUBLE, *dataspace);

    delete dataset;
    delete dataspace;
    delete group;
    delete file;

    return data_out;
}

int main() {
    MatrixXd A(2, 2), B(3, 3);
    A << 1, 2,
         3, 4;
    B << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    string filename = "hdf5_test.txt";
    string groupname = "Data";

    create_file(filename);
    add_group(filename, groupname);

    hsize_t dims2[2] = {2, 2};
    add_data(filename, groupname, A, "A", dims2);
    hsize_t dims3[2] = {3, 3};
    add_data(filename, groupname, B, "B", dims3);

    MatrixXd A_out = read_data(filename, groupname, "A", dims2);
    MatrixXd B_out = read_data(filename, groupname, "B", dims3);

    cout << "Matrix A:\n" << A_out << endl;
    cout << "Matrix B:\n" << B_out << endl;

    return 0;
}