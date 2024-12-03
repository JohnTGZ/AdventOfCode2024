// Day 3 b

#include <iostream>
#include <vector>

#include <regex>

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

    std::ifstream input_file("../actual_cases/d3a.txt");
    // std::ifstream input_file("../test_cases/d3b.txt");

    // Vector of reports
    std::vector<std::pair<int, int>> mul_instr;

    std::string line;
    while (std::getline(input_file, line, '\n')) {

        // Replace everything that could conceivably terminate a don't()
        //      1. do()
        //      2. \n
        //      3. don't()

        // Only the most recent do() or don't() instruction applies
        std::regex replace_regex("((don't\\(\\)).*(don't\\(\\)))|((don't\\(\\)).*(do\\(\\)))|((don't\\(\\)).*(\n*))");

        std::string line2 = std::regex_replace(line, replace_regex, "");

        std::cout << line2 << std::endl;

        // Use REGEX
        // std::regex mul_regex("\Bmul\B\(\d[\^,]\d\)");
        std::regex mul_regex("(mul)\\((\\d)+\\,(\\d)+\\)");
        // std::regex mul_regex("(don't()).*(do())");

        auto mul_begin = std::sregex_iterator(line2.begin(), line2.end(), mul_regex);
        auto mul_end = std::sregex_iterator();

        for (std::sregex_iterator i = mul_begin; i != mul_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();

            std::regex num_regex("(\\d)+");
            auto num_begin = std::sregex_iterator(match_str.begin(), match_str.end(), num_regex);
            auto num_end = std::sregex_iterator();

            std::sregex_iterator j = num_begin;
            int a = std::stoi((*j).str());
            ++j;
            int b = std::stoi((*j).str());
            mul_instr.push_back(std::make_pair(a,b));
        }
    }

    auto start = high_resolution_clock::now();

    // /************ */
    // /* Algorithm */
    // /************ */

    int answer = 0;
    for (auto const& instr : mul_instr)
    {
        answer += instr.first * instr.second;     
    }

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    std::cout << "answer: " << answer << std::endl;

    std::cout << "runtime in microseconds: " << duration.count() << std::endl;

    return 0;
}