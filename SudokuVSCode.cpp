#include<opencv2/objdetect.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>
#include<utility>
#define vvs vector<vector<pair<short, bool>>>
#define N 9

using namespace std;
using namespace cv;

void buildSudoku(Mat&, Rect, Scalar);

vvs takeinput(void);

bool SolveSudoku(vvs&);

void fillSudoku(Mat&, Rect, const vvs);

void printSudoku(const vvs);

int main()
{
	unsigned w = 720, h = 720, indent = 60; /*Indent is the indentation space*/
	Scalar bgcolor(255, 255, 255), linecolor(0, 0, 0);
	Mat sudoku(w, h, CV_8UC3, bgcolor);

	Point2f stpt(indent, indent), endpt(w-indent, h - indent);

	/*Object storing the border rectangle of Sudoku*/
	Rect border_rect(stpt, endpt);

	buildSudoku(sudoku, border_rect, linecolor);

	/*Calling the function to take input*/
	//vvs vec = takeinput();

	/*Declaring and initializing the Sudoku*/
	vvs vec = {
					{{2, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 1}, {0, 0}, {0, 0}, {7, 1}},
					{{0, 0}, {0, 0}, {0, 0}, {8, 1}, {0, 0}, {9, 1}, {4, 1}, {2, 1}, {0, 0}},
					{{0, 0}, {0, 0}, {3, 1}, {6, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
					{{0, 0}, {7, 1}, {2, 1}, {0, 0}, {3, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
					{{9, 1}, {3, 1}, {0, 0}, {0, 0}, {0, 0}, {2, 1}, {1, 1}, {5, 1}, {0, 0}},
					{{8, 1}, {6, 1}, {0, 0}, {0, 0}, {9, 1}, {0, 0}, {7, 1}, {0, 0}, {0, 0}},
					{{5, 1}, {0, 0}, {0, 0}, {9, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
					{{0, 0}, {1, 1}, {0, 0}, {2, 1}, {0, 0}, {3, 1}, {6, 1}, {0, 0}, {8, 1}},
					{{0, 0}, {8, 1}, {0, 0}, {0, 0}, {6, 1}, {7, 1}, {2, 1}, {0, 0}, {0, 0}},
	};


	if(!SolveSudoku(vec))
	{
		cout << endl << "The solution for this Sudoku doesn't exist" << endl << endl;
		return 0;
	}

	printSudoku(vec);

	fillSudoku(sudoku, border_rect, vec);

	imshow("Sudoku", sudoku);
	waitKey(0);

	return 0;
}

/*Fills the Sudoku with the digits i.e., fills the boxes of Sudoku with the initial and filled values*/
void fillSudoku(Mat& img, Rect border,const vvs vec)
{
	/*Width and height of each box of Sudoku*/
	unsigned horzgap = border.width / 9;
	unsigned vertgap = border.height / 9;

	/*Color of digits*/
	Scalar initcolor(0, 0, 0);  //Color of initial given digits --> black
	Scalar rescolor(255, 0, 0); //Color of found digits --> blue

	/*Adjusting the coordinates of bottom-left corner of text box*/
	int xcoord = border.x+20;	
	int ycoord = border.y+vertgap-13;

	for (unsigned i = 0; i < 9; i++)
	{
		for (unsigned j = 0; j < 9; j++)
		{
			/*putText function puts the digit in every box*/
			if (vec[i][j].second == 1)	putText(img, to_string(vec[i][j].first), Point(xcoord + j * horzgap, ycoord + i * vertgap), FONT_HERSHEY_PLAIN, 3, initcolor, 3);
			else
			{
				putText(img, to_string(vec[i][j].first), Point(xcoord + j * horzgap, ycoord + i * vertgap), FONT_HERSHEY_PLAIN, 3, rescolor, 3);
			}
		}
	}
	return;
}

/*Draws the layout of the Sudoku*/
void buildSudoku(Mat& imgsrc, Rect border, Scalar color)
{
	Point titlept(border.x+(border.width/3), border.y-20);
	double titlescale = getFontScaleFromHeight(FONT_HERSHEY_DUPLEX, 40, 5);
	Scalar titlecolor(127, 0, 255);

	/*Putting the Title on image*/
	putText(imgsrc, "SUDOKU", titlept, FONT_HERSHEY_DUPLEX, titlescale, titlecolor, 5);
	rectangle(imgsrc, border, color, 3);
	double wid = border.width, height = border.height;

	double slopex = wid / N;
	double slopey = height / N;

	for (short i = 1; i <= (N-1); i++)
	{
		Point vertsrc(border.x + (slopex * i), border.y);
		Point vertdest(border.x + (slopex * i), border.y+height);
		
		Point horsrc(border.x , border.y + (slopey*i));
		Point hordest(border.x + wid, border.y + (slopey * i));

		if (i % 3 == 0)
		{
			line(imgsrc, horsrc, hordest, color, 2);
			line(imgsrc, vertsrc, vertdest, color, 2);
		}
		else
		{
			line(imgsrc, horsrc, hordest, color, 1.5);
			line(imgsrc, vertsrc, vertdest, color, 1.5);
		}
	}

	return;
}

/*Prints instructions on console*/
void instructions(void)
{
	cout << endl << "---INSTRUCTIONS---"<<endl
		<<"Enter the initial contents of sudoku row-wise" << endl
		<<"For every row, enter the digits as space seperated"<<endl
		<< "If there is a blank, enter it as '0' (without quotes)" << endl<<endl;
	return;
}

/*Takes input into a 2D vector and returns it*/
vvs takeinput(void)
{
	/*Declaring a 2D vector of pairs*/
	vvs arr(N, vector<pair<short, bool>>(N, {0, 0}));
	
	/*Taking input from the user*/
	instructions();
	for (short i = 0; i < N; i++)
	{
		cout << "Enter the row " << (i + 1) << " content: ";
		for (short j = 0; j < N; j++)
		{
			cin >> arr[i][j].first;
			if(arr[i][j].first!=0)
				arr[i][j].second = 1;	/*This digit has been given as input*/
		}
	}

	arr.shrink_to_fit(); //destroys any extra space allotted
	return arr;
}

/* Returns whether any assigned entry in the specified row matches the given number */
bool UsedInRow(vvs vec, short row, short num)
{
	for (short col = 0; col < N; col++)
		if (vec[row][col].first == num)
			return true;
	return false;
}

/* Returns whether any assigned entry in the specified column matches the given number */
bool UsedInCol(vvs vec, short col, short num)
{
	for (short row = 0; row < N; row++)
		if (vec[row][col].first == num)
			return true;
	return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches the given number. */
bool UsedInBox(vvs vec, short boxStartRow, short boxStartCol, short num)
{
	for (short row = 0; row < 3; row++)
		for (short col = 0; col < 3; col++)
			if (vec[row + boxStartRow][col + boxStartCol].first == num)
				return true;
	return false;
}

/* Returns whether it will be allowed to assign num to the given row,col location */
bool isSafe(vvs vec, short row, short col, short num)
{
	return !UsedInRow(vec, row, num) && !UsedInCol(vec, col, num) &&
		!UsedInBox(vec, row - row % 3, col - col % 3, num);

}

/*Searches to find whether any unassigned location exists in Sudoku*/
bool FindUnassignedLocation(vvs &arr, short& i, short& j)
{
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (arr[i][j].first == 0)
				return true;
	return false;
}

/*Solves the Sudoku*/
bool SolveSudoku(vvs &arr)
{
	short row, col;
	if (!FindUnassignedLocation(arr, row, col))
		return true;
	for (short num = 1; num <= N; num++)
	{
		if (isSafe(arr, row, col, num))
		{
			arr[row][col].first = num;
			if (SolveSudoku(arr))
				return true;
			arr[row][col].first = 0;
		}
	}
	return false;
}

/*Prints the sudoku on console*/
void printSudoku(const vvs sudoku)
{
	cout << endl << "Printing the sudoku" << endl;
	for (short row = 0; row < N; row++)
	{
		for (short col = 0; col < N; col++)
			cout << sudoku[row][col].first << "  ";
		cout << endl;
	}
	cout << endl;
	return;
}
