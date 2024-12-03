# Advent Of Code 2024

## Run a particular day's code
```bash
cd build 
cmake .. && make && ./d1a
```

## Problems

1. Day 1
    - a: Solved using multiset. Hashtable with repetition
    - b: Solved using multiset. Hashtable with repetition
2. Day 2
    - a: Solved by checking the conditions for strictly increasing or decreasing and bounds on the absolute difference between 2 consecutive levels.
    - b: Not solved. 
3. Day 3
    - a: Use regular expressions
    - b: Replace everything between a "don't()" and anything that could conceivably terminate it: "do()", "\n" and "don't()" with nothing. Then work on the remaining string as you would in day 3 part 1.
4. Day 4