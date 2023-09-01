# TOP 7 - Problem description 

Write a program to manage a chart of hits. The tracks, which are subject to voting, are numbered with integers in the range from $1$ to $99999999$. The program reads data from standard input. Each line contains a vote or an instruction to execute.

A valid vote is a non-empty list of song numbers from the range $1$ to **MAX**, where **MAX** is the maximum song number that can be voted for in a given chart. A valid vote cannot include a song number that has dropped off the chart. In a valid vote, song numbers must be distinct.

The program handles individual chart rankings and summary of rankings. Both the chart ranking and the summary include at most the top $7$ highest ranked songs.

If a song was listed in a particular chart ranking and doesn't appear in the subsequent ranking, it falls off the chart and can no longer be voted for.

There are two commands:

- **NEW MAX** <br>
The NEW command finalizes the previous chart ranking (if one was ongoing) and initiates a new ranking with the provided MAX value, which ranges from 1 to 99999999. It must be greater than or equal to the MAX value from the previous (closing) voting. This command prints the closing ranking to the standard output.


- **TOP** <br>
The **TOP** command prints a summary of all the previous chart rankings to the standard output. The summary is determined by summing up the points obtained in the past rankings. A song that ranked first receives 7 points, the second-ranked song receives 6 points, and so on, down to 1 point for the seventh-ranked song. This command doesn't interrupt the ongoing voting for the current chart ranking.
```

Both commands output at most 7 song numbers for the ranking or summary, providing the song number and the position change compared to the previous ranking or summary. If a song is a newcomer to the list or the summary, it's represented by a '-' (hyphen, minus) symbol.

If two songs receive the same number of votes or points, the song with the lower number takes the higher position.

Individual elements in the input data line are separated by whitespace, which can occur in any number and can also appear at the beginning or end of a line. The program ignores empty lines and lines consisting solely of whitespace.

The program constantly checks whether the input data contains errors. For each erroneous line, the program prints the following diagnostic message to the standard output:

Error in line N: <original form of the erroneous line>

Here, N represents the line number. Lines are numbered starting from 1, including ignored and erroneous lines. Pay attention to the space after the colon and preserving the original form of the erroneous line in the message.

An example usage, along with the required format for the output, can be found in the **files test_1.in, test_1.out, and test_1.err**.

The expected solution should not include the definition of custom structures and classes, or at least those that store data. Instead, you should heavily utilize the containers and algorithms provided by the standard C++ library. Input and output handling should be implemented using streams.

Your solution should be placed in a file named top7.cc.

The solution will be compiled on the "students" machine using the command:

```
g++ -Wall -Wextra -O2 -std=c++20 top7.cc -o top7
```
