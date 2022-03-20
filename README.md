# geo_project
Rewriting a geology simulation in c++

=====================================================

This project uses the Eigen library.
Install it on Linux/WSL with:
```
sudo apt install libeigen3-dev
```
To run the c++ version use:
```
g++ -std=gnu++11 -O3 h_mec_rsf_<version_number>.cpp -I/usr/include/eigen3 -o <filename.out>
```
flags to include Eigen:
  -std=gnu++11
  -I/usr/include/eigen3
other flags:
  -O3 (to activate optimizer -> greatly increases speed)

=====================================================

To run the code on EULER use the
```
env2lmod
```
and the .sh script provided in the corresponding folder of this project.
