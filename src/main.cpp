#include <iostream>
#include <string>
#include <array>

#include "storage.h"
#include "analysis.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "\nYou must enter an operation i.e. + or - and TWO CHGCAR file names, not 0, not 1, TWO!\nSyntax: ./deltacharge +/- CHGCAR1 CHGCAR2\n\nexiting...\n\n";
        cout << "You can also enter a value from which you would like to integrate the difference function of z to see if there is charge transfer.\n\nUsage: ./deltacharge +/- CHGCAR1 CHGCAR2 -some number-";
        return 0;
    }
    Storage s;
    
    s.operation = (string) argv[1];
    s.filename1 = (string) argv[2];
    s.filename2 = (string) argv[3];
    
    if (argc == 5) {
        s.int_val = stod(argv[4]);
    }
    run_main(s);
    return 0;
}