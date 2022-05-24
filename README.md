# geo_project
Rewriting a geology simulation in c++

=====================================================

This project uses the Eigen library.
Install it on Linux/WSL with:
```
sudo apt install libeigen3-dev
```
Install it on Mac OS X with:
```
brew install eigen
```
Additionally this project uses the intel compiler (icpc) to make use the Pardiso solver that uses MKL.
Be aware that you need a valid intel licence to use those.

=====================================================

The c++ version of this simulation works on the EULER cluster only.
To run it on a local device or another cluster, the flags would need to be changed accordingly

libraries used:

 - Eigen
 - OpenMP
 - Libszip (similar libraries might work too)
 - HDF5
  
some important flags:

  -O3 (to activate optimizer -> greatly increases speed)

=====================================================

To run the code on EULER use the
```
env2lmod
```
and the .sh script provided in the corresponding folder of this project.

=====================================================

Please use the newest version.
Older versions can be found int the folder H_MEC_RSF/cpp/old_versions. Be careful using these as not all of them work nor guarantee correct results.
