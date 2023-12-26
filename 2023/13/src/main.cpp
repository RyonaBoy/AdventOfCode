//
//  main.cpp
//  AOC13
//
//  Created by Yu Zhao on 24.12.23.
//

#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, const char * argv[]) {
    std::ifstream infile("./../aoc.txt");
    std::string line;
    
    auto getMirrIdx = [](const std::vector<std::vector<char>> &grid) -> int{
        int h = grid.size();
        for(int row_mirr = 1; row_mirr < h; row_mirr++){
            std::vector<std::vector<char>> upper;
            std::vector<std::vector<char>> lower;
            for(int i = 0; i < row_mirr; i++){ upper.push_back(grid.at(i)); }
            for(int i = row_mirr; i < 2*row_mirr && i < h; i++){ lower.push_back(grid.at(i)); }
            std::reverse(upper.begin(), upper.end());
            while(upper.size() > lower.size()){ upper.pop_back(); }
            int diff = 0;
            for(int row = 0; row < upper.size(); row++){
                for(int col = 0; col < upper.front().size(); col++) if(upper.at(row).at(col) != lower.at(row).at(col)) {
                    diff++;
                }
            }
            if(diff == 1){ return row_mirr; }
        }
        return 0;
    };
    
    auto transpose = [](const std::vector<std::vector<char>> &grid){
        std::vector<std::vector<char>> transposed(grid.front().size(), std::vector<char>(grid.size(), ' '));
        for(int row = 0; row < grid.size(); row++){
            for(int col = 0; col < grid.front().size(); col++){
                transposed.at(col).at(grid.size()-1-row) = grid.at(row).at(col);
            }
        }
        return transposed;
    };
    
    int res = 0;
    std::vector<std::vector<char>> grid;
    while(std::getline(infile, line)){
        if(line.size() == 0){
            //find mirror and clear grid for next scan
            int idx = getMirrIdx(grid);
            res += 100*idx;
            auto transposed = transpose(grid);
            idx = getMirrIdx(transposed);
            res += idx;
            grid.clear();
            continue;
        }
        std::vector<char> row;
        for(auto c: line){ row.push_back(c); }
        grid.push_back(row);
    }
    //find mirror and clear grid for next scan
    int idx = getMirrIdx(grid);
    res += 100*idx;
    auto transposed = transpose(grid);
    idx = getMirrIdx(transposed);
    res += idx;
    
    std::cout << res << std::endl;
    
    
    return 0;
}
