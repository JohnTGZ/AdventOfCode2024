// Day 2 b

#include <iostream>
#include <vector>

#include <fstream> // read file
#include <sstream>
#include <cstring> // strtok

#include <chrono> // Measure runtime

using namespace std::chrono;


bool isReportSafe(std::vector<int>& report, int& unsafe_idx)
{
    //  not safe && unsafe_idx == -1 : Level is unsafe even with removal
    //  safe && unsafe_idx == -1 : Safe
    //  not safe && unsafe_idx == x : removing a single level makes it safe
    unsafe_idx = -1;

    bool is_inc = true; // is_increasing
    bool prev_is_inc = true;

    bool is_unsafe = false;

    for (int j = 1; j < (int)report.size(); j++)
    {
        int diff = report[j] - report[j-1];
        int abs_diff = std::abs(diff);

        is_inc = diff > 0 ? true : false;

        if (j == 1){ // start of report
            prev_is_inc = is_inc;
        }

        // Check 1: absolute difference
        if (abs_diff < 1 || abs_diff > 3)
        {
            is_unsafe = true;
        }
        // Check 2: strictly inc/dec
        if (is_inc != prev_is_inc){
            is_unsafe = true;
        }

        if (is_unsafe)
        {
            if (j == 1){ // Start of report
                // remove 1st element (0)
                int diff1 = report[2] - report[1];
                int abs_diff1 = std::abs(diff1);

                if (abs_diff1 >= 1 && abs_diff1 <= 3) // within tolerance
                {
                    unsafe_idx = 0;
                    break;
                }

                // remove 2nd element (1)
                int diff2 = report[2] - report[0];
                int abs_diff2 = std::abs(diff2);
                if (abs_diff2 >= 1 && abs_diff2 <= 3) // within tolerance
                {
                    unsafe_idx = 1;
                    break;
                }
            }
            else if (j == (int)report.size() - 1) // end of report
            {
                // Last element is unsafe
                unsafe_idx = (int)report.size() - 1;
                break;
            }
            else { // rest of report
                // remove j-th element 
                int diff2 = report[j+1] - report[j-1];
                int abs_diff2 = std::abs(diff2);
                if (abs_diff2 >= 1 && abs_diff2 <= 3) // within tolerance
                {
                    unsafe_idx = j;
                    break;
                }
            }
        }

        prev_is_inc = is_inc;
    }

    return !is_unsafe;
}


int main()
{

    /************ */
    /* Parse input */
    /************ */

    std::ifstream input_file("../actual_cases/d2a.txt");
    // std::ifstream input_file("../test_cases/d2a_2.txt");

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

    // Problem dampener
    //  safe if there is a single level that can be removed to make it safe

    int unsafe_reports = 0;

    for (int i = 0; i < (int)reports.size(); i++)
    {
        int unsafe_idx;
        bool original_report_safe = isReportSafe(reports[i], unsafe_idx);
        if (!original_report_safe){
            if (unsafe_idx == -1){
                // no way to remove level to make it safe
                std::cout << "Report " << i << " ABSOLUTELY UNSAFE" << std::endl;
                unsafe_reports++;
            }
            else {
                std::cout << "Report " << i << ": removing " << unsafe_idx << std::endl;
                reports[i].erase(reports[i].begin()+unsafe_idx);
                int placeholder;
                bool modified_report_safe = isReportSafe(reports[i], placeholder);
                if (!modified_report_safe){
                    std::cout << "  Report " << i << ": ABSOLUTELY UNSAFE even after removing " << unsafe_idx << std::endl;
                    // no way to remove a single level to make it safe
                    unsafe_reports++;
                }
                else{
                    std::cout << "  Report " << i << ": SAFE after removing " << unsafe_idx << std::endl;
                }
            }
        }
        else {
            std::cout << "Report " << i << ": SAFE! " << std::endl;
        }


    }

    int safe_reports = (int)reports.size() -  unsafe_reports;

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    std::cout << "safe_reports: " << safe_reports << std::endl;

    std::cout << "runtime in microseconds: " << duration.count() << std::endl;

    return 0;
}