
#include <iostream>
#include <fstream>
using namespace std;

ifstream inputFile("plantatie.in");
ofstream outputFile("plantatie.out");

int plantation[12][512][512], k, queryCount, gridSizeX, gridSizeY;

inline int maximum(int x, int y) {
    return x > y ? x : y;
}

int main() {
    inputFile >> gridSizeX >> gridSizeY;

    for (int i = 0; i < gridSizeX; ++i) {
        for (int j = 0; j < gridSizeY; ++j) {
            inputFile >> plantation[0][i][j];
        }
    }

    for (int level = 1; (1 << level) <= gridSizeX; ++level) {
        for (int i = 0; i + (1 << level) <= gridSizeX; ++i) {
            for (int j = 0; j + (1 << level) <= gridSizeY; ++j) {
                plantation[level][i][j] = maximum(maximum(plantation[level - 1][i][j], plantation[level - 1][i + (1 << (level - 1))][j]),
                                                 maximum(plantation[level - 1][i][j + (1 << (level - 1))], plantation[level - 1][i + (1 << (level - 1))][j + (1 << (level - 1))]));
            }
        }
    }

    inputFile >> queryCount;

    for (int i = 0; i < queryCount; ++i) {
        int x, y, length;
        inputFile >> x >> y >> length;
        int q = 1;
        x--; y--;
        int level = 0;

        while (q * 2 <= length) {
            q *= 2;
            level++;
        }

        int result = maximum(maximum(plantation[level][x][y], plantation[level][x + length - q][y]),
                             maximum(plantation[level][x][y + length - q], plantation[level][x + length - q][y + length - q]));
        outputFile << result << '\n';
    }

    return 0;
}
