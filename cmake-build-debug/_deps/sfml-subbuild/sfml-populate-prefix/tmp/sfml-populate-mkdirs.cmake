# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-src"
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-build"
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix"
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix/tmp"
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix/src"
  "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/chaewoneom/Desktop/CS3307/Fire-Fighter/cmake-build-debug/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
