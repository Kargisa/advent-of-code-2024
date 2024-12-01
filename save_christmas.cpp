#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <math.h>
#include <vector>

#define LOG(X) std::cout << X << "\n";

void day1_1(){

    std::cout << "Day 1 :3 \n";

    const std::string path = "./inputs/input1_1";
    std::ifstream stream(path);

    if (!stream.is_open()){
        LOG("file can not be opened");
        return;   
    }

    std::multiset<int> left;
    std::multiset<int> right;

    int l, r;
    while (stream >> l >> r){
        left.insert(l);
        right.insert(r);
    }

    auto literator = left.begin();
    auto riterator = right.begin();

    int result = 0;
    while (literator != left.end() && riterator != right.end()){
        int lv = *literator;
        int rv = *riterator;

        result += std::abs(lv - rv);

        riterator++;
        literator++;
    }

    LOG(result);
}

void day1_2(){
    const std::string path = "./inputs/input1_2";
    std::ifstream stream(path);

    if (!stream.is_open()){
        LOG("file can not be opened");
        return;   
    }

    std::vector<int> left;
    std::unordered_map<int, int> right;


    int l, r;
    while (stream >> l >> r){
        left.emplace_back(l);
        
        if (!right.contains(r)){
            right[r] = 1;
            continue;
        }

        right[r]++;
    }

    int result = 0;
    for (size_t i = 0; i < left.size(); i++)
    {
        int lvalue = left[i];
        int rvalue = right[lvalue];

        result += (lvalue * rvalue);
    }

    LOG(result);
    
