#include <iostream>
#include <thread>
#include "storage.h"
#include "readfile.h"
#include "diff.h"

using namespace std;

void run_main(Storage& s) {
    cout << "\nNow reading \"" << s.filename1 << "\" and \"" << s.filename2 << "\".\n\n"; 
    File file1, file2;
    s.files.push_back(file1);
    s.files.push_back(file2);
    s.files[0].filename = s.filename1;
    s.files[1].filename = s.filename2;
    read_file(s.files[0]);
    read_file(s.files[1]);
    diff3D(s);  
    diff1D(s); 
}