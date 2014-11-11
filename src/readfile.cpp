#include <fstream>
#include <iostream>
#include <string>
#include "storage.h"

using namespace std;

void read_file(File& f) {
    ifstream input;
    input.open(f.filename.c_str());
    string stuff;    
    int counter = 0;
    int datacount = 0;
    while(!input.eof()) {
        input >> stuff;
        
        if (!counter) {
            f.name = stuff;
            counter ++;
            
        } else if (counter == 1) {
            input >> f.ax[0] >> f.ax[1] >> f.ax[2]
                  >> f.ay[0] >> f.ay[1] >> f.ay[2]
                  >> f.az[0] >> f.az[1] >> f.az[2];  
            counter ++;
                    
        } else if (counter == 2) {
            if (stuff.find("Direct") == string::npos) {
                f.atom_counts.push_back(atoi(stuff.c_str()));
            } else {
                counter ++;
            }
        } else if (counter == 3) {
            string old = stuff;
            for (int i = 0; i < f.natoms(); i ++) {
                getline(input, stuff);
                if (i == 0) {
                    f.coords.push_back("  " + old + stuff);
                } else {
                    f.coords.push_back(stuff);
                }
            }
            getline(input, stuff);
            counter ++;    
        } else if (counter == 4) {
            string a,b;
            input >> a >> b;
            f.bin_counts[0] = atoi(stuff.c_str());
            f.bin_counts[1] = atoi(a.c_str());
            f.bin_counts[2] = atoi(b.c_str());
            counter ++;
        } else if (datacount < f.nbins()){
            f.data.push_back(stod(stuff.c_str()));
            datacount ++;
        }                
    }
}