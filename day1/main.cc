#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

const std::unordered_map<std::string, int> dict = 
{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

void parse(std::vector<std::string> &input)
{
    std::ifstream file;
    std::string line;
    file.open("data.txt", std::ios::in);

    if(!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }
    
    while(std::getline(file, line))
    {
        input.push_back(line);
    }

    file.close();
}

int part1(const std::vector<std::string> &input)
{
    int sum = 0;

    for(const auto &line : input)
    {
        int index_1 = -1;
        int index_2 = -1;

        for(size_t i = 0; i < line.size(); ++i)
        {
            if(line[i] >= '0' && line[i] <= '9')
            {
                if(index_1 == -1)
                    index_1 = i;
                index_2 = i;
            }     
        }
        
        if(index_1 != -1 && index_2 != -1)
            sum += 10 * (line[index_1] - '0') + (line[index_2] - '0');
    }

    return sum;
}

int part2(const std::vector<std::string> &input)
{
    int sum = 0;

    for(const auto &line : input)
    {
        int index_1 = -1, index_2 = -1;
        int digit_1 = 0, digit_2 = 0;

        for(size_t i = 0; i < line.size(); ++i)
        {
            if(line[i] >= '0' && line[i] <= '9')
            {
                if(index_1 == -1)
                {
                    index_1 = i;
                    digit_1 = line[i] - '0';
                }
        
                index_2 = i;
                digit_2 = line[i] - '0';
            }     
        }

        for(const auto &p : dict)
        {
            size_t index = line.find(p.first);
            while(index != std::string::npos)
            {
                if(index_1 == -1 || static_cast<int>(index) < index_1)
                {
                    index_1 = index;
                    digit_1 = p.second;
                }
                
                if(index_2 == -1 || static_cast<int>(index) > index_2)
                {
                    index_2 = index;
                    digit_2 = p.second;
                }

                index = line.find(p.first, index + 1);     
            }
        }
        sum += 10 * digit_1 + digit_2;
    }

    return sum;   
}

int main()
{
    std::vector<std::string> input;
    parse(input);
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}