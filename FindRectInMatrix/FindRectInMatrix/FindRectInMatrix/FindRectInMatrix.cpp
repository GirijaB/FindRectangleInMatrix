// FindRectInMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <assert.h> 
#include <string>

// FindRectangle.cpp : This file contains the 'main' function. Program execution begins and ends there.
	using namespace std;

	class FindRectangle {
	public:
		typedef struct rect
		{
			int upBound;
			int lowBound;
			int rightBound;
			int leftBound;
		}rectangle;

		rectangle FindRect(vector<vector<int>> &matrix);
		rectangle MapRect(multimap<int, pair<int, int>>& mapof_Rect);
		void DisplayRect(rectangle);
	};

	int main()
	{
		vector<vector<int> > matrix{{1 } };

		FindRectangle findRectObject;
		findRectObject.FindRect(matrix);
		return 0;
	}

	FindRectangle::rectangle FindRectangle::FindRect(vector<vector<int>>& matrix)
	{
		//get row size of matrix
		int row = matrix.size();
		//get column size of matrix
		int col = matrix[0].size();

		//initalize the struct values of rectangle to zero.
		FindRectangle::rectangle rect;
		rect.leftBound = 0; rect.lowBound = 0; rect.rightBound = 0; rect.upBound = 0;

		//if row and col are both zero there exists no matrix so no rect found
		if (row == 0 && col == 0)
			return rect;


		//use the vector of size equal to the size of column 
		vector<int> trackRect(col, 0);

		//I am using this to map the rect with indexes so i can return the indexes of rectangle found
		multimap<int, pair<int, int>>  rectWithIndexes;

		for (int i = 0; i < row; i++)
		{
			pair<int, pair<int, int>>  pairWithIndexes;
			int leftBound = -1;
			for (int j = 0; j < col; j++)
			{
				//check if element of matrix is equal to 1 ,if yes then check if upbound is set or not set

				if (matrix[i][j] == 1)
				{
					trackRect[j] = trackRect[j]++;
					if (leftBound < 0)
					{
						leftBound = j;
					}

					pair<int, int> indexes = { leftBound,j };
					pairWithIndexes = { trackRect[j],indexes };

					//if yes then check if upbound is set or not set
				}
				else
					trackRect[j] = 0;


			}
			rectWithIndexes.insert(pairWithIndexes);
		}

		rect = MapRect(rectWithIndexes);
		if (rect.lowBound == 0 && rect.leftBound == -1)
			std::cout << "No Rectangle Found!";
		else
			DisplayRect(rect);

		return rect;
	}

	FindRectangle::rectangle FindRectangle::MapRect(multimap<int, pair<int, int>>& mapof_Rect)
	{
		FindRectangle::rectangle rect;
		rect.leftBound = 0; rect.lowBound = 0; rect.rightBound = 0; rect.upBound = 0;
		int maxRectSize = 0;
		int pos = 0;
		for (const auto&x : mapof_Rect)
		{
			if (x.first > maxRectSize)
			{
				maxRectSize = x.first;
				rect.leftBound = x.second.first;
				rect.rightBound = x.second.second;
				rect.lowBound = pos;
				rect.upBound = rect.lowBound - maxRectSize;
			}
			pos++;
		}
		return rect;
	}


	//This is just to display the result of rectangle found
	void FindRectangle::DisplayRect(FindRectangle::rectangle rect) {

		//calculate the height of the rectangle;
		int height = rect.lowBound - rect.upBound;
		int width = rect.rightBound - rect.leftBound + 1;
		assert(height >= 1);   // Height has to be at least 1 for a top and bottom side
		assert(width >= 1);  // Width has to be at least 1 for a left and right side

		int i;
		cout << char(218);
		for (i = 0; i < width - 2; i++)
			cout << char(196);
		cout << char(191) << endl;

		for (i = 0; i < height - 2; i++)
		{
			cout << char(179);
			for (int j = 0; j < width - 2; j++)
				cout << "-";
			cout << char(179) << endl;
		}
		cout << char(192);

		for (i = 0; i < width - 2; i++)
			cout << char(196);
		cout << char(217) << endl;
	}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
