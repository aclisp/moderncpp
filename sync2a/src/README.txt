How to build libgtest.a
-----------------------

clang++ -Wall -g -std=c++1y -pthread -c /usr/src/gtest/src/gtest-all.cc -o gtest-all.o -I/usr/src/gtest
ar -rv libgtest.a gtest-all.o

