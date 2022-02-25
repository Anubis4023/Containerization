#include <iostream>
#include <fstream>

using namespace std;

int main () {
    ofstream outfile ("manifest.txt");

    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 13; j++) {
            outfile << "[0" << i << ",";
            if (j < 10) { //Output , for example, 01 instead of 1 for numbers lower than 10
                outfile << "0";
            }
            outfile << j << "], {00000}, UNUSED" << endl;
        }
    }
    outfile.close();
}