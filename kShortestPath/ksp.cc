#include "ksp.h"



#include <boost/graph/adjacency_list.hpp>
// #include <boost/test/unit_test.hpp>

#include <algorithm>
#include <iostream>
#include <list>


// Check whether there is a given result.
bool
check_result(const results &rs, const result &r)
{
  return std::find(rs.begin(), rs.end(), r) != rs.end();
}
