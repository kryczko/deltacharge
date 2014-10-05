#include <iostream>
#include <string>
#include <array>

#include "storage.h"
#include "analysis.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "You must enter TWO CHGCAR file names, not 0, not 1, TWO!\nSyntax: ./deltacharge CHGCAR1 CHGCAR2\n\nexiting...\n\n";
        return 0;
    }
    Storage s;
    
    s.filename1 = (string) argv[1];
    s.filename2 = (string) argv[2];
    run_main(s);
    return 0;
}