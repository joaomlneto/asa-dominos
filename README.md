asa-dominos
===========

Project assignment for the Analysis and Synthesis of Algorithms course @ IST 2013

- Problem
Dominos are lots of fun. Children like to stand the tiles on their side in long lines.
When one domino falls, it knocks down the next one, which knocks down the one after that, all the way down the line. However, sometimes a domino fails to knock the next one down. In that case, we have to knock it down by hand to get the dominos falling again.
Your task is to determine, given the layout of some domino tiles, the minimum number of dominos that must be knocked down by hand in order for all of the dominos to fall.

- Input
First line of input contains one integer specifying the number of test cases to follow.
Each test case begins with a line containing two integers, each no larger than 1.000.000.
The first integer N is the number of domino tiles and the second integer M is the number of lines to follow in the test case.
The domino tiles are numbered from 1 to N.
Each of the following lines contains two integers X and Y indicating that if domino number X falls, it will cause domino number Y to fall as well.
Any two integers in a line are separated by one white space. The lines contain no other characters, aside from the finishing new line.

- Output
For each test case, output a line containing one integer, the minimum number of dominos that must be knocked over by hand in order for all the dominos to fall.

- Examples

Input 1
1
3 2
1 2
2 3

Output 1
1

Input 2
1
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10

Output 2
1