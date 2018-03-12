#include <queue>
#include "graph1.h"
#include <algorithm>
#include <numeric>


const long long MAX_COST = std::numeric_limits<long long>::max()/2;


std::vector<long long> shortest_paths(EdgeList<List_Edge> &g, unsigned long long start)
{
    std::vector<long long> costs(g.size(), MAX_COST);
    costs[start] = 0;
    std::vector<unsigned long long> prev(g.size());
    std::iota(begin(prev), end(prev), 0);
    
    for(unsigned long long i = 1; i < g.size(); ++i)
    {
        bool updated = false;
        
        for(auto edge: g.edges)
        {
            if(costs[edge.from]!=MAX_COST){
                long long cost = costs[edge.from] + edge.cost;
                if(cost < costs[edge.dest])
                {
                    updated = true;
                    costs[edge.dest] = cost;
                    prev[edge.dest] = edge.from;
                }
            }
        }
        if(!updated) break;
    }
    for(unsigned long long i = 1; i < g.size(); ++i)
    {
        bool updated = false;
        for(auto edge: g.edges)
        {
            if(costs[edge.from] != MAX_COST){
                long long cost = costs[edge.from] + edge.cost;
                cost = cost >= -MAX_COST ? cost : -MAX_COST;
                if(cost < costs[edge.dest])
                {
                    updated = true;
                    costs[edge.dest] = - MAX_COST;
                }
            }
        }
        if(!updated) break;
    }
    
    return costs;
    
}