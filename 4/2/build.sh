g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
g++ -c --std=c++20 -fmodules-ts internals.cxx A.cxx B.cxx Example.cxx main.cpp
g++ --std=c++20 internals.o A.o B.o Example.o main.o -o result