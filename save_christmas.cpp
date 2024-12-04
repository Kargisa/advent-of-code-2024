#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <math.h>
#include <vector>
#include <regex>

#define LOG(X) std::cout << X << "\n";

void day1_1(){
    LOG("Day1_1 :3");

    const std::string path = "./inputs/input1_1";
    std::ifstream stream(path);

    if (!stream.is_open()){
        LOG("file can not be opened");
        return;   
    }

    std::multiset<int> left;    // O(log(n)) time complexity
    std::multiset<int> right;   // O(log(n)) time complexity

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

    LOG("result: " << result);
    stream.close();
}

void day1_2(){
    LOG("Day1_2 :3");

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

    LOG("result: " << result);
    stream.close();
}
    
void day2_1(){
    const std::string path = "./inputs/input2_1";

    std::ifstream stream(path);
    if(!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    uint numOfSaveReports = 0;
    std::string line;
    while(std::getline(stream, line)){
        std::vector<int> numbersInLine;
        std::string currentSegment = "";
        int8_t report = 0;
        bool save = true;

        for (size_t i = 0; i < line.size(); i++)
        {

            if (line[i] != ' '){
                currentSegment += line[i];
                if (line.size() - 1 != i){
                    continue;
                }
            }

            int number = std::stoi(currentSegment);
            size_t vectorSize = numbersInLine.size();

            if (vectorSize != 0){
                int numbersDiffAbs = std::abs(number - numbersInLine[vectorSize - 1]);
                int numbersDiff = number - numbersInLine[vectorSize - 1];
                
                if (numbersDiffAbs < 1 || numbersDiffAbs > 3){
                    save = false;
                    break;
                }

                if (report == 0){
                    if (numbersDiff > 0){
                        report = 1;
                    }
                    else {
                        report = -1;
                    }
                    numbersInLine.emplace_back(number);
                    currentSegment = "";
                    continue;
                }

                if ((numbersDiff < 0 && report > 0) || (numbersDiff > 0 && report < 0)){
                    save = false;
                    break;
                }
            }

            numbersInLine.emplace_back(number);
            currentSegment = "";
        }

        if (save){
            numOfSaveReports++;
        }
    }

    LOG("save reports: " << numOfSaveReports);
    stream.close();
}

int safetyCheck(const std::vector<int>& levels, size_t ignoreIndex){
    int8_t direction = 0;
    for (size_t i = 0; i < levels.size() - 1; i++)
    {
        if (i == ignoreIndex)
            continue;

        int val1 = levels[i];
        size_t nextIndex = ((i + 1) == ignoreIndex) ? (i + 2) : (i + 1);
        if (nextIndex >= levels.size()){
            break;
        }
        int val2 = levels[nextIndex];

        int diff = val2 - val1;
        int diffAbs = std::abs(val2 - val1);

        if (diffAbs < 1 || diffAbs > 3){
            return 0;
        }

        if (direction == 0){
            if (diff > 0){
                direction = 1;
            }
            else {
                direction = -1;
            }
            continue;
        }

        if ((diff > 0 && direction < 0) || (diff < 0 && direction > 0)){
            return 0;
        }
    }
    return 1;
}

void day2_2(){
    const std::string path = "./inputs/input2_2";

    std::ifstream stream(path);
    if(!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    uint numOfSaveReports = 0;
    std::string line;
    size_t lol = 1;
    while(std::getline(stream, line)){
        std::vector<int> levels;

        std::string currentSegment = "";
        for (size_t i = 0; i < line.size(); i++)
        {

            if (line[i] != ' '){
                currentSegment += line[i];
                if (line.size() - 1 != i){
                    continue;
                }
            }

            int number = std::stoi(currentSegment);
            levels.emplace_back(number);
            currentSegment = "";
        }

        for (size_t i = 0; i <= levels.size(); i++)
        {
            int result = safetyCheck(levels, i - 1);
            if (lol < 100){
                LOG(lol << ") " << " ignore: " << i - 1 << " save: " << result)
            }
            if (result == 1){
                numOfSaveReports += result;
                break;
            }
        }
        lol++;
    }
    LOG("save reports: " << numOfSaveReports);
    stream.close();
}

void day3_1(){
    const std::string path = "./inputs/input3_1";

    std::ifstream stream(path);

    if (!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();

    const std::string& fileContent = buffer.str();

    std::regex regex("mul\\(\\d{1,3},\\d{1,3}\\)");
    auto begin = std::sregex_iterator(fileContent.begin(), fileContent.end(), regex);
    auto end = std::sregex_iterator();

    std::regex numRegex("\\d{1,3}");

    int result = 0;
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();

        int mulResult = 1;
        auto numBegin = std::sregex_iterator(match_str.begin(), match_str.end(), numRegex);
        auto numEnd = std::sregex_iterator();
        for (auto it = numBegin; it != numEnd; it++)
        {
            std::smatch numMatch = *it;
            mulResult *= std::stoi(numMatch.str());
        }
        result += mulResult;
    }

    LOG("result: " << result);
}

void day3_2(){
    const std::string path = "./inputs/input3_2";

    std::ifstream stream(path);

    if (!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();

    const std::string& fileContent = buffer.str();

    std::regex regex("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don't\\(\\)");
    auto begin = std::sregex_iterator(fileContent.begin(), fileContent.end(), regex);
    auto end = std::sregex_iterator();

    std::regex numRegex("\\d{1,3}");

    int result = 0;
    bool enable = true;
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();

        bool mul = true;
        if (match_str == "do()"){
            mul = false;
            enable = true;
        }
        else if (match_str == "don't()"){
            mul = false;
            enable = false;
        }

        if (!enable || !mul){
            continue;
        }

        int mulResult = 1;
        auto numBegin = std::sregex_iterator(match_str.begin(), match_str.end(), numRegex);
        auto numEnd = std::sregex_iterator();

        for (auto it = numBegin; it != numEnd; it++)
        {
            std::smatch numMatch = *it;
            mulResult *= std::stoi(numMatch.str());
        }
        result += mulResult;
    }

    LOG("result: " << result);
}

void day4_1(){
    
}