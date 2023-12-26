//
//  main.cpp
//  AOC15
//
//  Created by Yu Zhao on 25.12.23.
//

#include <iostream>
#include <fstream>
#include <map>

int main(int argc, const char * argv[]) {
    auto isDigit = [](char c){ return c >= '0' && c <= '9'; };
    //auto isOperation = [](char c){ return c == '-' || c == '='; };
    auto hash = [](int cur, char c){
        cur += static_cast<int>(c);
        cur *= 17;
        cur %= 256;
        return cur;
    };
    
    std::vector<std::vector<std::pair<std::string, int>>> lenses(256);
    
    std::ifstream infile("./../aoc.txt");
    std::string line;
    std::getline(infile, line);
    int idx = 0;
    std::string label;
    char operation;
    int focal_len;
    for(auto c: line){
        if(c == ','){
            auto it = lenses.at(idx).begin();
            while(it != lenses.at(idx).end()){
                if(it->first == label){ break; }
                it++;
            }
            if(operation == '=' && it == lenses.at(idx).end()){ lenses.at(idx).push_back({label, focal_len}); }
            else if(operation == '=' && it != lenses.at(idx).end()){ it->second = static_cast<int>(focal_len); }
            else if(operation == '-' && it != lenses.at(idx).end()){ lenses.at(idx).erase(it); }
            label.clear();
            idx = 0;
        } else if (isDigit(c)){
            focal_len = static_cast<int>(c - '0');
        }
        else if (c=='='||c=='-') {
            operation = c;
        } else {
            label.push_back(c);
            idx = hash(idx, c);
        }
    }
    
    int res = 0;
    for(int box = 0; box < lenses.size(); box++){
        for(int i = 0; i < lenses.at(box).size(); i++){
            res += (box+1) * (i+1) * lenses.at(box).at(i).second;
        }
    }
    std::cout << res << std::endl;
    return 0;
}
