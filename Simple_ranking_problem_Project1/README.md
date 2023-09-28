# TOP 7 -  Short problem description 
Develop a program to manage a chart of hits where songs are voted on, numbered from 1 to 99999999. The program reads commands from standard input: "NEW MAX" for starting a new chart, and "TOP" for summarizing rankings. Songs with the same votes/points are ranked by their lower number. The program verifies input data and reports errors.

# Full description

You can find full description in [full_description.md](ttps://github.com/MrRuper/Languages-and-tools-for-programming-I/blob/main/Simple_ranking_problem_Project1/full_description.md).

# How to use this program?
You can compile **top_7.cpp** with the command: 
```
g++ -Wall -Wextra -O2 -std=c++20 top7.cc -o top7
```

and nextly using 

```
./top7
```

run this program. It will wait on your input. You can type **TOP**, **NEW MAX** (here MAX is some number) or **array of votes** (see full description of the problem). In the case of invalid input the program will print out the error line.

# What is the goal of that project?

The goal of this project is to show how standard containers work in C++ i.e. to show what are maps, vectors, sets and very important for working with input - regex. Regex allows to match patterns with input string and to work with them.

# How this project could be improved?

For sure some interactive mode with a nice interface is needed here. It could be done with the **ncurses** library.



