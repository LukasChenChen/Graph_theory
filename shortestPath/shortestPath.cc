#include "shortestPath.h"
#include "stdlib.h"
#include <iostream>

using namespace boost;

// find shortest path from a to b. directed graph, no loop
//notice that how to find a vertex.  e.g. vertex(src,graph)
Short_path get_short_path(Graph& graph, int src, int dst){
    //add source & target
    boost::graph_traits<Graph>::vertex_descriptor startV = boost::vertex( src, graph );
    
    boost::graph_traits<Graph>::vertex_descriptor endV = boost::vertex( dst, graph );
    
    //predecessors
    // Output for predecessors of each node in the shortest path tree result
    std::vector<int>  predMap(boost::num_vertices(graph));
    
    //distMap
    // Output for distances for each node with initial size
    // of number of vertices
    std::vector<int>  distMap(boost::num_vertices(graph));
    
    
    //solve shortest path problem
    boost::dijkstra_shortest_paths(graph, startV,
    weight_map(boost::get(&EdgeProperty::latency, graph)) //arc costs from bundled properties
    .predecessor_map(boost::make_iterator_property_map(predMap.begin(),//property map style
                                                        boost::get(boost::vertex_index, graph)))
    .distance_map(boost::make_iterator_property_map(distMap.begin(),//property map style
                                                        boost::get(boost::vertex_index, graph)))
    );
    
    std::vector<int> path;
    graph_traits<Graph>::vertex_descriptor current = endV;
    while (startV != current)
    {
        path.push_back(current);
        current = predMap[current];
    }
    // add start as last element (=start node) to path
    path.push_back(startV);
    
    //print out the path with reverse iterator
    std::vector< int >::reverse_iterator rit;
    std::cout <<"Path from "<< startV << " to "<< endV << " is: "<< std::endl;
    int totalCost = distMap[endV];

    // the real path is reversed.
    std::vector<int> path_result;

    for (rit = path.rbegin(); rit != path.rend(); ++rit){
        std::cout << *rit << " -> ";
        path_result.push_back(*rit);
    }
        
    
    std::cout << std::endl;
    std::cout << "short path cost is : "<< totalCost << std::endl;



    Short_path short_path = {path_result,totalCost};

    return short_path;

}