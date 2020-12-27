/* ... */
// =======================================================================
// Copyright 2020 by Chen
// Author: Chen Chen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <stdlib.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <iostream>

using namespace boost;

struct Short_path{
    std::vector<int> path;
    int routing_cost;

};

struct VertexProperty{
    int id;
    int cpu;
    int mem;
    int domain;
    int tier;
    int border;
};
    
// edge property in boost graph
struct EdgeProperty{
    int id;
    int bw;
    int latency;
    int inter_domain; // equals 1 if it is interdomain edge.
    
    int get_weight(){
        return latency;
    }

    int get_interdomain(){
        return inter_domain;
    }
};


typedef boost::adjacency_list<
vecS, //使用数组来存储 edge边
vecS, //使用数组来存储 vecS
bidirectionalS, //申明为有向图，可以访问其out-edge,若要都能访问
            //则需要定义为bidirectionalS directedS
VertexProperty,
EdgeProperty //定义边的属性
> Graph;