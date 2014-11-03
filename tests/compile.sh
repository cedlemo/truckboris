#!/usr/bin/bash
clang++ -o libtest_headerParser_ptr $(pkg-config --libs --cflags truckboris) libtest_headerParser_ptr.cpp
clang++ -o libtest_headerParser_obj $(pkg-config --libs --cflags truckboris) libtest_headerParser_obj.cpp

