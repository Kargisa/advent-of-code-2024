#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <math.h>
#include <vector>
#include <regex>
#include <array>
#include <unordered_set>
#include <tuple>

#define LOG(X) std::cout << X << "\n";

template<typename T>
std::string strigifyVector(const std::vector<T>& vec, char delimiter = ' '){
    std::string str = "";
    for (size_t i = 0; i < vec.size(); i++)
    {
        str += std::to_string(vec[i]) + delimiter;
    }
    return str;
}


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
    stream.close();
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
    stream.close();
}

int xmasCheck(size_t y, size_t x, int dirY, int dirX, const std::vector<std::string>& content, const std::array<char, 4> xmas){
    size_t yNow;
    size_t xNow;
    for (size_t i = 0; i < xmas.size(); i++)
    {
        yNow = y + dirY * i;
        xNow = x + dirX * i;

        if (yNow >= content.size()){
            return 0;
        }
        if (xNow >= content[yNow].size()){
            return 0;
        }

        char cha = content[yNow][xNow];

        if (cha != xmas[i]){
            return 0;
        }
    }
    return 1;
}

void day4_1(){
    const std::string path = "./inputs/input4_1";

    std::ifstream stream(path);
    if (!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    const std::array<char, 4> XMAS = {'X', 'M', 'A', 'S'}; 
    std::vector<std::string> fileContent;

    std::string line;
    while(std::getline(stream, line)){
        fileContent.emplace_back(line);
    }

    int result = 0;

    for (size_t y = 0; y < fileContent.size(); y++)
    {
        for (size_t x = 0; x < fileContent[y].size(); x++)
        {
            for (int dirY = -1; dirY < 2; dirY++)
            {
                for (int dirX = -1; dirX < 2; dirX++)
                {
                    if (dirY == 0 && dirX == 0){
                        continue;
                    }
                    result += xmasCheck(y, x, dirY, dirX, fileContent, XMAS);
                }
            }
        }
    }

    LOG("amount of XMAS: " << result);
    stream.close();
}

bool masCheck(size_t y, size_t x, int dirY, int dirX, const std::vector<std::string>& content){

    bool hasM = false;
    bool hasS = false;

    for (int i = -1; i < 2; i++)
    {
        if (i == 0){
            continue;
        }

        size_t yNow = y + dirY * i;
        size_t xNow = x + dirX * i;

        if (yNow >= content.size()){
            return false;
        }

        if (xNow >= content[yNow].size()){
            return false;
        }

        char cha = content[yNow][xNow];
        if (cha == 'M'){
            hasM = true;
        }
        else if (cha == 'S'){
            hasS = true;
        }
    }

    return hasM && hasS;
}

void day4_2(){
    const std::string path = "./inputs/input4_2";
    
    std::ifstream stream(path);
    if (!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    std::vector<std::string> fileContent;

    std::string line;
    while(std::getline(stream, line)){
        fileContent.emplace_back(line);
    }

    int result = 0;
    for (size_t y = 0; y < fileContent.size(); y++)
    {
        for (size_t x = 0; x < fileContent[y].size(); x++)
        {
            if (fileContent[y][x] != 'A'){
                continue;
            }

            bool check1 = masCheck(y, x, 1, 1, fileContent);
            bool check2 = masCheck(y, x, 1, -1, fileContent);
            result += ((check1 && check2) ? 1 : 0);
        }
    }    

    LOG("amount of X-MAS: " << result);
    stream.close();
}

void day5_1(){
    const std::string path = "./inputs/input5_1";

    std::ifstream stream(path);
    if(!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    std::string line;
    std::vector<std::tuple<int, int>> rules;

    int l;
    int r;
    char delimiter = '|';
    while(std::getline(stream, line)){
        std::istringstream lineStream(line);
        if (lineStream >> l >> delimiter >> r){
            rules.emplace_back(l, r);
            continue;
        }
        break;
    }

    int result = 0;

    std::unordered_set<int> lineSet;
    std::vector<int> numbersInLine;
    while (std::getline(stream, line))
    {
        std::string currentSegment = "";
        for (size_t i = 0; i < line.size(); i++)
        {
            if (line[i] != ','){
                currentSegment += line[i];
                if (line.size() - 1 != i){
                    continue;
                }
            }

            int number = std::stoi(currentSegment);
            numbersInLine.emplace_back(number);
            lineSet.emplace(number);
            currentSegment = "";
        }

        for (size_t i = 0; i < rules.size(); i++)
        {
            int first = std::get<0>(rules[i]);
            int second = std::get<1>(rules[i]);

            if (!lineSet.contains(first) || !lineSet.contains(second)){
                continue;
            }

            for (size_t i = 0; i < numbersInLine.size(); i++)
            {
                if (numbersInLine[i] == first){
                    break;
                }
                else if (numbersInLine[i] == second){
                    //breaks outer loop and skips result addition!
                    goto WRONG;
                }
            }
        }

        result += numbersInLine[(numbersInLine.size()) / 2];

    WRONG:
        numbersInLine.clear();
        lineSet.clear();
    }
    
    LOG("result: " << result);
    stream.close();
}

bool swapCondition(int a, int b, std::unordered_map<int, std::unordered_set<int>>& rules){
    if (rules.contains(b)){
        if (rules[b].contains(a)){
            return true;
        }
    }
    return false;
}

bool isCorrect(const std::vector<int>& numbersInLine, std::unordered_map<int, std::unordered_set<int>>& rules){
    auto begin = numbersInLine.begin();
    auto end = numbersInLine.end();
    for (size_t i = 0; i < numbersInLine.size(); i++)
    {
        if (!rules.contains(numbersInLine[i])){
            continue;
        }

        for (auto &&rule : rules[numbersInLine[i]])
        {
            auto iterator = std::find(begin, end, rule);
            int index = std::distance(begin, iterator);

            if (index < i){
                return false;
            }                                
        }
    }

    return true;
}

//TODO: look into this:
void day5_2(){
    const std::string path = "./inputs/input5_2";

    std::ifstream stream(path);
    if(!stream.is_open()){
        LOG("file could not be opened!");
        return;
    }

    std::string line;
    std::unordered_map<int, std::unordered_set<int>> rules;

    int l;
    int r;
    char delimiter = '|';
    while(std::getline(stream, line)){
        std::istringstream lineStream(line);
        if (lineStream >> l >> delimiter >> r){
            if (rules.contains(l)){
                rules[l].emplace(r);
            }
            else{
                rules[l] = {r};
            }

            continue;
        }
        break;
    }

    int result = 0;

    std::unordered_set<int> lineSet;
    std::vector<int> numbersInLine;
    while (std::getline(stream, line))
    {
        std::string currentSegment = "";
        for (size_t i = 0; i < line.size(); i++)
        {
            if (line[i] != ','){
                currentSegment += line[i];
                if (line.size() - 1 != i){
                    continue;
                }
            }

            int number = std::stoi(currentSegment);
            numbersInLine.emplace_back(number);
            lineSet.emplace(number);
            currentSegment = "";
        }

        bool correct = isCorrect(numbersInLine, rules);

        if (!correct){
            int n = numbersInLine.size();

            // ASS
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (swapCondition(numbersInLine[j], numbersInLine[j + 1], rules)){
                        std::swap(numbersInLine[j], numbersInLine[j + 1]);
                    }
                }
                
            }

            // LOG(strigifyVector(numbersInLine));
            result += numbersInLine[(numbersInLine.size()) / 2];

        }

        numbersInLine.clear();
        lineSet.clear();
    }
    
    LOG("result: " << result);
    stream.close();
}








