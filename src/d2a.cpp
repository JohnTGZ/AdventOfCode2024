// Day 2 a

#include <iostream>
#include <vector>

#include <fstream> // read file
#include <sstream>
#include <cstring> // strtok

#include <chrono> // Measure runtime

using namespace std::chrono;

int main()
{

    /************ */
    /* Parse input */
    /************ */

    std::ifstream input_file("../actual_cases/d2a.txt");
    // std::ifstream input_file("../test_cases/d2a.txt");

    // Vector of reports
    std::vector<std::vector<int>> reports;

    std::string line;
    while (std::getline(input_file, line, '\n')) {
        
        std::vector<int> level;

        for (char *num_char = strtok(line.data(), " ");
            num_char != NULL;
            num_char = strtok(NULL, " "))
        {
            level.push_back(std::stoi(std::string(num_char)));
        }

        reports.push_back(level);
    }

    auto start = high_resolution_clock::now();

    /************ */
    /* Algorithm */
    /************ */

    // each line is a report
    // each report contains levels

    // 1. Levels are either all increasing or all decreasing
    // 2. Any 2 adjacent levels differ by at least 1 or at most 3

    int unsafe_reports = 0;

    for (int i = 0; i < (int)reports.size(); i++)
    {
        bool increasing = reports[i][1] > reports[i][0] ? true : false;

        for (int j = 1; j < (int)reports[i].size(); j++)
        {
            int diff = reports[i][j] - reports[i][j-1];
            int abs_diff = std::abs(diff);
            if (abs_diff < 1 || abs_diff > 3)
            {
                unsafe_reports++;
                break;
            }
            if (increasing) // diff should be >0
            {
                if (diff < 0){
                    unsafe_reports++;
                    break;
                }
            }
            else{ // diff should be < 0
                if (diff > 0){
                    unsafe_reports++;
                    break;
                }
            }
        }

    }

    int safe_reports = (int)reports.size() -  unsafe_reports;

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    std::cout << "safe_reports: " << safe_reports << std::endl;

    std::cout << "runtime in microseconds: " << duration.count() << std::endl;

    return 0;
}