#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class MemoryGameFinal {
protected:
    int points = 0;
    string firstName;
    int row1Value, column1Value, row2Value, column2Value;
    int menu;
    bool again = true;
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    vector<vector<int>> matrix;
    vector<vector<bool>> matrix2;

public:
    void display(int size) {
        cout << " ";
        for (int i = 0; i < size; ++i) {
            cout << " " << i + 1;
        }
        cout << endl;
        for (int row = 0; row < size; row++) {
            cout << row + 1 << "|";
            for (int column = 0; column < size; column++) {
                if (matrix2[row][column]) {
                    cout << matrix[row][column] << " ";
                }
                else {
                    cout << "* ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void start() {
        SetConsoleTextAttribute(color, 9);
        cout << "Welcome to Memory - The Card Game" << endl << endl;

        SetConsoleTextAttribute(color, 7);
        cout << "Please enter your first name" << endl;
        cin >> firstName;

        while (again) {
            cout << "Welcome, " << firstName << "!" << endl;
            cout << endl << endl;
            cout << "Game Menu" << endl;
            cout << " ********************" << endl;
            cout << "Select 1 for a New Game and 2 to Exit Game" << endl;
            cout << "1. New Game" << endl;
            cout << "2. Exit Game" << endl;
            cout << " ********************" << endl;
            cin >> menu;

            if (menu == 2) {
                cout << endl;
                cout << "Would you like to play Memory - The Card Game again?" << endl;
                cout << "Type '1' to play again and '0' to leave" << endl;
                cin >> again;
                cout << endl;
            }
            else if (menu == 1) {
                cout << "Select the level:" << endl;
                cout << "1. Level 1 (2x2 grid)" << endl;
                cout << "2. Level 2 (4x4 grid)" << endl;
                cout << "3. Level 3 (6x6 grid)" << endl;
                cout << "4. Level 4 (8x8 grid)" << endl;
                int level;
                cin >> level;

                switch (level) {
                case 1:
                    initializeMatrix(2);
                    break;
                case 2:
                    initializeMatrix(4);
                    break;
                case 3:
                    initializeMatrix(6);
                    break;
                case 4:
                    initializeMatrix(8);
                    break;
                default:
                    cout << "Invalid level selected. Please try again." << endl;
                    break;
                }
            }
        }
    }

    void initializeMatrix(int size) {
        srand((unsigned int)time(NULL));

        vector<int> nums;
        for (int i = 1; i <= size * size / 2; ++i) {
            nums.push_back(i);
            nums.push_back(i);
        }
        random_shuffle(nums.begin(), nums.end());

        matrix.clear();
        matrix2.clear();
        for (int i = 0; i < size; ++i) {
            matrix.push_back(vector<int>());
            matrix2.push_back(vector<bool>());
            for (int j = 0; j < size; ++j) {
                matrix[i].push_back(nums[i * size + j]);
                matrix2[i].push_back(false);
            }
        }

        cout << "Level " << size / 2 << " (" << size << "x" << size << " grid)" << endl;
        cout << "Points: " << points << endl;
        display(size);
        Loop(size);
    }

    void Loop(int size) {
        while (points != size * size) {
            cout << firstName << ", please enter a row value for first card: " << endl;
            cin >> row1Value;

            cout << firstName << ", please enter a column value for first card: " << endl;
            cin >> column1Value;

            cout << firstName << ", please enter a row value for second card: " << endl;
            cin >> row2Value;

            cout << firstName << ", please enter a column value for second card: " << endl;
            cin >> column2Value;
            cout << endl;

            row1Value--;
            column1Value--;
            row2Value--;
            column2Value--;

            matrix2[row1Value][column1Value] = true;
            matrix2[row2Value][column2Value] = true;

            display(size);
            Match(row1Value, column1Value, row2Value, column2Value);
        }

        system("cls");
        cout << "Thank you for completing my game " << firstName << "!" << endl << endl;
    }

    void Match(int row1, int col1, int row2, int col2) {
        if (matrix[row1][col1] == matrix[row2][col2]) {
            points = points + 2;
            SetConsoleTextAttribute(color, 4);
            cout << "Congratulations!" << endl;
            cout << "Your Two Cards Match!" << endl << endl;
            SetConsoleTextAttribute(color, 7);
            cout << "Points: " << points << endl << endl;
        }
        else {
            SetConsoleTextAttribute(color, 4);
            cout << "Oh No!" << endl;
            cout << "Your Two Cards Do Not Match!" << endl << endl;
            SetConsoleTextAttribute(color, 7);
            cout << "Points: " << points << endl << endl;

            matrix2[row1][col1] = false;
            matrix2[row2][col2] = false;
        }
    }
};

int main() {
    MemoryGameFinal Game;
    Game.start();
}
