#include "allShortestPath.h"
#include "stdlib.h"
#include <iostream>
#include <vector>

using namespace boost;

// A recursive function to get all paths from 'src' to 'dst'. 
    // visited[] keeps track of vertices in current path. 
    // path[] stores actual vertices and path_index is current 
    // index in path[] 
void get_all_paths_util(int src, int dst, bool visited[], 
                            int path[], int& path_index, Graph g, All_paths_vec& all_paths ) { 
    // Mark the current node and store it in path[] 
    visited[src] = true; 
    path[path_index] = src; 
    path_index++; 

    // If current vertex is same as destination, then print 
    // current path[] 
    
    if (src == dst) { 

        std::vector<int> temp_path;
        for (int i = 0; i < path_index; i++){
            std::cout << path[i] << " "; 
            temp_path.push_back(path[i]);
        }

        

        All_paths_vec::iterator ret;
        
        ret= std::find(all_paths.begin(),all_paths.end(), temp_path);

        if (ret == all_paths.end())
        {
            all_paths.push_back(temp_path);
            std::cout << std::endl; 
        }

        
    } 
    else // If current vertex is not destination 
    { 
        // Recur for all the vertices adjacent to current vertex 
        boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

        for (boost::tie(ei, ei_end) = boost::out_edges(src, g); ei != ei_end; ++ei )
        {
            auto target = boost::target(*ei, g);

            // std::cout <<"----The adj vertex for " << src <<" is " << (int) target <<std::endl;

            if (!visited[(int) target])
            {
                get_all_paths_util((int) target, dst, visited, path, path_index, g, all_paths); 
            }
            
        }
        
    } 

    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[src] = false; 
} 

All_paths_vec get_all_paths(Graph g, int src, int dst) { 

    All_paths_vec all_paths;
    
    auto num = boost::num_vertices(g);

    int V = (int) num;

        // Mark all the vertices as not visited 
    bool* visited = new bool[V]; 

    // Create an array to store paths 
    int* path = new int[V]; 

    int path_index = 0; // Initialize path[] as empty 

    // Initialize all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 

    // Call the recursive helper function to print all paths 
    get_all_paths_util(src, dst, visited, path, path_index, g, all_paths);

    return all_paths;
} 