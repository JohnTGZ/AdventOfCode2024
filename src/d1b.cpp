// Day 1 b

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

    int total_sim_score = 0;

    // <key, value> is <idx, value>
    std::multiset<int> multiset_a;
    std::multiset<int> multiset_b;

    // iterate and add to hash map
    for (int i = 0; i < (int)a.size(); i++)
    {
        multiset_a.insert(a[i]);
        multiset_b.insert(b[i]);
    }

    // Iterate through hashmap
    for (auto a_it = multiset_a.begin(), b_it = multiset_b.begin(); 
        a_it != multiset_a.end(); a_it++, b_it++)
    {
        // std::cout << *a_it << " - " << *b_it << std::endl;
        // int diff = std::abs(*a_it - *b_it); 
        int num_copies = multiset_b.count(*a_it); 
        if (num_copies >= 1){
            int sim_score = num_copies * *a_it;
            total_sim_score += sim_score;
        }
    }

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    std::cout << "total_sim_score: " << total_sim_score << std::endl;

    std::cout << "runtime in microseconds: " << duration.count() << std::endl;

    return 0;
}