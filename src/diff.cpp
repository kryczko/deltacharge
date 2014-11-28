#include <fstream>
#include <iostream>
#include <cmath>
#include "storage.h"

using namespace std;


void diff1D(Storage& s) {
    File& f1 = s.files[0];
    File& f2 = s.files[1];
    ofstream output;
    output.open("output/1D_chgdiff.dat");
    double sum1 = 0;
    double sum2 = 0;
    
    vector<double> zsum1(f1.bin_counts[2]);
    vector<double> zsum2(f1.bin_counts[2]);
    for (int i = 0; i < zsum1.size(); i ++) {
        zsum1[i] = 0;
        zsum2[i] = 0;
    }
    int counter = 0;
    double vol = f1.ax[0]*f1.ay[1]*f1.az[2];
    double vox = (f1.ax[0] / f1.bin_counts[0])*(f1.ay[1] / f1.bin_counts[1])*(f1.az[2] / f1.bin_counts[2]);
    for (int i = 0; i < f1.data.size(); i ++) {
        zsum1[counter] += f1.data[i];
        zsum2[counter] += f2.data[i];
        sum1 += (f1.data[i] / vol) * vox;
        sum2 += (f2.data[i] / vol) * vox;
        if (i % (f1.bin_counts[0]*f1.bin_counts[1]) == 0 && i > 0) {
            zsum1[counter] /= (f1.bin_counts[0]*f1.bin_counts[1]);
            zsum2[counter] /= (f1.bin_counts[0]*f1.bin_counts[1]);
            
            counter ++;
        }
    }
    cout << "Electrons found in first file = " << sum1 << "\nElectrons found in second file = " << sum2 << "\n";
    double int_LHS = 0, int_RHS = 0;
    if (s.int_val != -1) {
        for (int i = 1; i < zsum1.size() - 1; i ++) {
            if ((double) i * f1.az[2] / (double) f1.bin_counts[2] < s.int_val) {
                int_LHS += (zsum1[i] - zsum2[i]) / vol * vox;
            } else {
                int_RHS += (zsum1[i] - zsum2[i]) / vol * vox;
            }
        }
        cout << "Integral of LHS = " << int_LHS << "\n";
        cout << "Integral of RHS = " << int_RHS << "\n";
    }
    if (s.operation == "-") {
        for (int i = 0; i < zsum1.size() - 1; i ++) {
            output << (double) i * f1.az[2] / (double) f1.bin_counts[2] << "\t" << zsum1[i] - zsum2[i] << "\n";
        }
        
    } else if (s.operation == "+") {
        for (int i = 0; i < zsum1.size() - 1; i ++) {
            output << (double) i * f1.az[2] / (double) f1.bin_counts[2] << "\t" << zsum1[i] + zsum2[i] << "\n";
        }
        
    }
    output.close();
}

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
                output << f1.data[i] - f2.data[i] << "  ";
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