#include <vector>
#include <int2.hpp>
#include "../../graphics/tilemap.h"

// Source : <https://www.geeksforgeeks.org/a-search-algorithm/>

/// <summary>
/// Find a path from start to goal on a tilemap.
/// </summary>
template <size_t WIDTH, size_t HEIGHT>
std::vector<int2> find_path(std::shared_ptr<Tilemap> map, int2 start, int2 goal) {
    bool closedList[WIDTH][HEIGHT];
    memset(closedList, false, sizeof(closedList));
}


// A* Search Algorithm 
/*
    1.  Initialize the open list
    2.  Initialize the closed list
    put the starting node on the open
    list(you can leave its f at zero)

    3.  while the open list is not empty
    a) find the node with the least f on
    the open list, call it "q"

    b) pop q off the open list

    c) generate q's 8 successors and set their 
    parents to q

    d) for each successor
    i) if successor is the goal, stop search

    ii) else, compute both gand h for successor
    successor.g = q.g + distance between
    successor and q
    successor.h = distance from goal to
    successor(This can be done using many
        ways, we will discuss three heuristics -
        Manhattan, Diagonaland Euclidean
        Heuristics)

        successor.f = successor.g + successor.h

        iii) if a node with the same position as
        successor is in the OPEN list which has a
        lower f than successor, skip this successor

        iV) if a node with the same position as
        successor  is in the CLOSED list which has
        a lower f than successor, skip this successor
        otherwise, add  the node to the open list
        end(for loop)

        e) push q on the closed list
        end(while loop)
*/