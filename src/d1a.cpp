// Day 1 a

#include <iostream>
#include <vector>
// #include <map>
#include <set>

#include <fstream> // read file
#include <sstream>
#include <cstring> // strtok

#include <chrono> // Measure runtime

using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();

    // Parse input
    std::ifstream input_file("../actual_cases/d1a.txt");
    // std::ifstream input_file("../test_cases/d1a.txt");

    std::string line;

    // given 2 lists a and b
    std::vector<int> a, b;

    // std::vector<int> a{3, 4, 2, 1, 3, 3};
    // std::vector<int> b{4, 3, 5, 3, 9, 3};

    while (std::getline(input_file, line, '\n')) {
        // Output the text from the file

        char *num_char = strtok(line.data(), " ");

        if (num_char != NULL){
            a.push_back(std::stoi(std::string(num_char)));
        }
        num_char = strtok(NULL, " ");

        if (num_char != NULL){
            b.push_back(std::stoi(std::string(num_char)));
        }

        std::cout << "(" << a.back() << ", " << b.back() << ")" << std::endl;
        
        // std::string(num )
        // a.push_back(std::stoi(num_str));
        
        // std::getline(line_ss, num_str, ' ');
        // std::cout << "num_str: " << num_str << std::endl;
        // b.push_back(std::stoi(num_str));
    }

    int total_dist = 0;

    // <key, value> is <idx, value>
    std::multiset<int> hashmap_a;
    std::multiset<int> hashmap_b;

    // iterate and add to hash map
    for (int i = 0; i < (int)a.size(); i++)
    {
        hashmap_a.insert(a[i]);
        hashmap_b.insert(b[i]);
    }

    // Iterate through hashmap
    for (auto a_it = hashmap_a.begin(), b_it = hashmap_b.begin(); 
        a_it != hashmap_a.end(); a_it++, b_it++)
    {
        // std::cout << *a_it << " - " << *b_it << std::endl;
        int diff = std::abs(*a_it - *b_it); 
        total_dist += diff;
    }

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    std::cout << "total_dist: " << total_dist << std::endl;

    std::cout << "runtime in microseconds: " << duration.count() << std::endl;

    return 0;
}