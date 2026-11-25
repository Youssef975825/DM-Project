cmake_minimum_required(VERSION 4.4)
project(DataMining)

set(CMAKE_CXX_STANDARD 26)

add_executable(DataMining main.cpp
        Algorithm/DataSet.cpp
        Algorithm/DataSet.h
        Algorithm/ECLAT.cpp
        Algorithm/ECLAT.h
        Algorithm/AssociationRules.cpp
        Algorithm/AssociationRules.h)
configure_file(${CMAKE_SOURCE_DIR}/data.csv ${CMAKE_BINARY_DIR}/data.csv COPYONLY)