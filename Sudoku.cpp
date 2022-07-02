#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

//takes unsolved sudoku from the user
void take_grid(int grid[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		cout <<  "-------------------------------------" << endl;
		cout << " Enter " << i + 1 << " row elements: \n";
		for (int j = 0; j < 9; j++)
        	cin >> grid[i][j];
	}
	cout << endl << "-------------------------------------" << endl << endl;;
}

// Prints the Soduko grid
void print_grid(int grid[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		cout << endl << "-------------------------------------" << endl;
		for (int j = 0; j < 9; j++)
		{
			cout << " ";
			if (grid[i][j]==0)
			{
				cout << " ";
			}
			else
			{
				cout << grid[i][j];
			}
			cout << " ";
			cout << "|";
		}
	}
	cout << endl << "-------------------------------------" << endl << endl;;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified row matches the given number. 
bool used_in_row(int grid[9][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified column matches the given number. 
bool used_in_col(int grid[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which indicates whether any assigned entry
// within the specified 3x3 box matches the given number. 
bool used_in_box(int grid[9][9], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col] == num)
			{
				return true;
			}
	return false;
}

// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.
bool is_safe(int grid[9][9], int row, int col, int num)
{
	// Check if 'num' is not already placed in current row,
	// current column and current 3x3 box 
	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

// Searches the grid to find an entry that is still unassigned. If
// found, the reference parameters row, col will be set the location
// that is unassigned, and true is returned. If no unassigned entries
// remain, false is returned. 
std::pair<int, int> get_unassigned_location(int grid[9][9])
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (grid[row][col] == 0)
			{
				return std::make_pair(row, col);
			}
	return std::make_pair(9, 9);
}

// Takes a partially filled-in grid and attempts to assign values to
// all unassigned locations in such a way to meet the requirements
// for Sudoku solution (non-duplication across rows, columns, and boxes) 
bool solve_soduko(int grid[9][9])
{
	// If the Soduko grid has been filled, we are done
	if (std::make_pair(9, 9) == get_unassigned_location(grid))
	{
		return true;
	}

	// Get an unassigned Soduko grid location
	std::pair<int, int> row_and_col = get_unassigned_location(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;

	// Consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		// If placing the current number in the current
		// unassigned location is valid, go ahead
		if (is_safe(grid, row, col, num))
		{
			// Make tentative assignment
			grid[row][col] = num;

			// Do the same thing again recursively. If we go 
			// through all of the recursions, and in the end 
			// return true, then all of our number placements 
			// on the Soduko grid are valid and we have fully
			// solved it
			if (solve_soduko(grid))
			{
				return true;
			}

			// As we were not able to validly go through all 
			// of the recursions, we must have an invalid number
			// placement somewhere. Lets go back and try a 
			// different number for this particular unassigned location
			grid[row][col] = 0;
		}
	}

	// If we have gone through all possible numbers for the current unassigned
	// location, then we probably assigned a bad number early. Lets backtrack 
	// and try a different number for the previous unassigned locations.
	return false;
}

int main()
{
	cout << "********************************\n\n\tSudoku Solver\n\n********************************" << endl << endl;

	int grid[9][9] = { { 0, 9, 0, 0, 0, 0, 8, 5, 3 },
						   { 0, 0, 0, 8, 0, 0, 0, 0, 4 },
						   { 0, 0, 8, 2, 0, 3, 0, 6, 9 },
						   { 5, 7, 4, 0, 0, 2, 0, 0, 0 },
						   { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						   { 0, 0, 0, 9, 0, 0, 6, 3, 7 },
						   { 9, 4, 0, 1, 0, 8, 5, 0, 0 },
						   { 7, 0, 0, 0, 0, 6, 0, 0, 0 },
						   { 6, 8, 2, 0, 0, 0, 0, 9, 0 } };

	cout << " Default Sudoku: \n";
	print_grid(grid);

	int n = 0;
	cout << "\n Press 1 to enter the unsolved sudoku. \n";
	cout << " Press 2 to view the solution of default sudoku. \n";
	cout << " Press 3 to exit. \n";
	cin >> n;
	if (n == 1)
	{
		take_grid(grid);
		if (true == solve_soduko(grid))
		{
			cout << "\n The solution is: \n";
			print_grid(grid);
		}
		else
		{
			cout << "No solution exists for the given Soduko" << endl << endl;
		}
	}
	else if (n == 2)
	{
		if (true == solve_soduko(grid))
		{
			cout << "\n The solution is: \n";
			print_grid(grid);
		}
		else
		{
			cout << "No solution exists for the given Soduko" << endl << endl;
		}
	}
	else if (n == 3)
		return 0;

	return 0;
}