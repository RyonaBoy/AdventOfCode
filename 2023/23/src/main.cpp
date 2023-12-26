//
//  main.cpp
//  AOC
//
//  Created by Yu Zhao on 23.12.23.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <utility>

int main(int argc, const char * argv[]) {
    std::ifstream infile("./../aoc.txt");
    std::string line;
    
    //scan grid
    std::vector<std::vector<char>> grid;
    while(std::getline(infile, line)){
        std::vector<char> row;
        for(auto c: line){ row.push_back(c); }
        grid.push_back(row);
    }
    int h = grid.size();
    int w = grid.front().size();
    int col_start = 0, col_end = 0;
    while(grid.at(0).at(col_start) != '.'){ col_start++; }
    while(grid.at(h-1).at(col_end) != '.'){ col_end++; }
    
    //graph contraction
    std::set<std::pair<int, int>> nodes;
    nodes.insert({0, col_start});
    nodes.insert({h-1, col_end});
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++)if('#' != grid.at(y).at(x)){
            int num_neigh = 0;
            if(y-1 >= 0 && grid.at(y-1).at(x) != '#' && grid.at(y).at(x) != 'v'){ num_neigh++; }
            if(y+1 < h && grid.at(y+1).at(x) != '#' && grid.at(y).at(x) != '^'){ num_neigh++; }
            if(x-1 >= 0 && grid.at(y).at(x-1) != '#' && grid.at(y).at(x) != '>'){ num_neigh++; }
            if(x+1 < w && grid.at(y).at(x+1) != '#' && grid.at(y).at(x) != '<'){ num_neigh++; }
            if(num_neigh >= 3){ nodes.insert({y, x}); }
        }
    }
    std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>> contracted_graph;
    struct Node{
        int y;
        int x;
        int d;
    };
    for(const auto& node: nodes){
        std::stack<Node> s;
        std::set<std::pair<int, int>> seen;
        s.push({node.first, node.second, 0});
        seen.insert(node);
        while(!s.empty()){
            int y = s.top().y;
            int x = s.top().x;
            int d = s.top().d;
            s.pop();
            if(0 != d && nodes.count({y, x})){
                contracted_graph[{node.first, node.second}][{y, x}] = d;
                continue;
            }
            if(y-1 >= 0 && grid.at(y-1).at(x) != '#' && !seen.count({y-1, x})){
                s.push({y-1, x, d+1});
                seen.insert({y-1, x});
            }
            if(y+1 < h && grid.at(y+1).at(x) != '#' && !seen.count({y+1, x})){
                s.push({y+1, x, d+1});
                seen.insert({y+1, x});
            }
            if(x-1 >= 0 && grid.at(y).at(x-1) != '#' && !seen.count({y, x-1})){
                s.push({y, x-1, d+1});
                seen.insert({y, x-1});
            }
            if(x+1 < w && grid.at(y).at(x+1) != '#' && !seen.count({y, x+1})){
                s.push({y, x+1, d+1});
                seen.insert({y, x+1});
            }
        }
    }
    
    //dfs
    std::set<std::pair<int, int>> seen;
    std::function<int(std::pair<int, int>)> dfs = [&](std::pair<int, int> node){
        if(node.first == h-1){ return 0; }
        int max_dist = std::numeric_limits<int>::min();
        seen.insert(node);
        for(auto neighbor: contracted_graph[node]) if(!seen.count(neighbor.first)) {
            max_dist = std::max(max_dist, contracted_graph[node][neighbor.first] + dfs(neighbor.first));
        }
        seen.erase(node);
        return max_dist;
    };
    
    std::cout << dfs({0, col_start}) << std::endl;
    
    return 0;
}
