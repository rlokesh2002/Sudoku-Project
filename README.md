Objective:
•	To fill a 9 x 9 sudoku by assigning 1-9 digits to each unassigned cell such that each row, column, and 3 x 3 sub-grid contains exactly one instance of each digits.

Motivation:
In childhood, filling Sudoku which appears on the last page of Eenadu Weekly Magazine was a weekly hobby. Most of the times I successfully filled it, but it used to take nearly half-an-hour and so. Sometimes, I used to make wrong choices at an instance and had to erase the whole grid and restart.
As I have gained the knowledge of programming and algorithms, I thought to implement backtracking algorithm and basic OpenCV to fill the standard 9x9 Sudoku.

Tools used:
•	OpenCV
•	Visual Studio
•	C++ Programming language

Description:
This is a self-project carried out to implement backtracking algorithm and basic OpenCV library to complete the Sudoku. 
Input of Sudoku is given as row-wise space separated digits which will be stored into a 2D vector of pairs or Sudoku values can be initialised in the code.
The program uses backtracking and checks if the Sudoku can be filled under given conditions and if successful, displays the filled Sudoku as an image.

Algorithm:
•	Check for the first unassigned cell in the grid and if found start filling it up with any of the 1 to 9 digits (whichever comes first) such that the primary condition is not violated and recursively check the assignment leads to solution. If not, fill the cell with next digit.
•	If there is no unassigned location, return true (i.e., Sudoku has been filled). If a cell cannot be assigned with any of the digits, then return false.
•	Finally display the Sudoku image.

Complexity:
	Time Complexity – O(N^(N^2 ) )
	Number of unassigned cells will be O(N2) and every unassigned cell has to be checked with worst case O(N) digits to fill it up with.
	Space Complexity – O(N^2 ) 
	For 2D vector of pairs
Here N = 9

Future Scope:
	To train a model which will recognize digits and empty spaces from image of Sudoku so that input will be given as image and output will be filled image.
	The time complexity of the solution is exponential. Its better to search for polynomial complexity solution at least.
	Extend the algorithm to suit for large values of N.
Reference: GeeksforGeeks

Conclusion:
A good project to learn about Backtracking and OpenCV.

