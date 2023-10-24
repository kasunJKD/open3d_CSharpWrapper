# open3d_CSharpWrapper
open3D csharp wrapper for stl reader and rendering

platform windows - c++ recreation building from source

Step 1: Compile and install Open3D
Follow the Open3D compilation guide, compile and install Open3D in your preferred location. You can specify the installation path with CMAKE_INSTALL_PREFIX and the number of parallel jobs to speed up compilation.

git clone --recursive https://github.com/intel-isl/Open3D.git
cd Open3D
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=C:\open3d_install ..
cmake --build . --config Release --parallel 12 --target install
cd ..\..

Step 2: Use Open3D in this example project

git clone https://github.com/intel-isl/open3d-cmake-find-package.git
cd open3d-cmake-find-package
mkdir build
cmake -DOpen3D_ROOT=C:\open3d_install ..
cmake --build . --config Release --parallel 12
Release\Draw


