#include <fstream>
#include <iostream>
#include <cmath>
#include "storage.h"

using namespace std;

void diff3D(Storage& s) {
    File& f1 = s.files[0];
    File& f2 = s.files[1];
    ofstream output;
    output.open("output/3D_diff_CHGCAR");
    output << "diff-" << f1.name << "-" << f2.name << "\n   1.00000\n";
    output << "   " <<  f1.ax[0] << "\t" << f1.ax[1] << "\t" << f1.ax[2] << "\n";
    output << "   " << f1.ay[0] << "\t" << f1.ay[1] << "\t" << f1.ay[2] << "\n";
    output << "   " << f1.az[0] << "\t" << f1.az[1] << "\t" << f1.az[2] << "\n";
    for (auto& a : f1.atom_counts) {
        output << "   " << a;
    }
    output << "\nDirect" << "\n";
    
    for (auto& line : f1.coords) {
        output << line << "\n";
    }
    output << "\n";
    for (auto& n : f1.bin_counts) {
        output << n << "  ";
    }
    output << "\n";
    if (s.operation == "-") {
        for (int i = 0; i < f1.data.size(); i ++) {
                output << abs(f1.data[i] - f2.data[i]) << "  ";
                if ((i + 1) % 5 == 0) {
                    output << "\n";
                }
        }
    } else if (s.operation == "+") {
        for (int i = 0; i < f1.data.size(); i ++) {
            output << f1.data[i] + f2.data[i] << "  ";
            if ((i + 1) % 5 == 0) {
                output << "\n";
            }
        }
        
    }
    output.close();
}