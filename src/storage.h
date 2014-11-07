#include <string>
#include <vector>

struct File {
    std::string name, filename;
    std::vector<std::string> coords;
    std::vector<double> ax, ay, az; // lattice constants
    std::vector<int> atom_counts, bin_counts;
    std::vector<double> data;
    
    File () {
        name = filename = "none";
        ax.resize(3);
        ay.resize(3);
        az.resize(3);
        bin_counts.resize(3);
    }
    
    int natoms() {
        int sum = 0;
        for (auto& a : atom_counts) {
            sum += a;
        }
        return sum;
    }
    int nbins() {
        int sum = 1;
        for (auto& n : bin_counts) {
            sum *= n;
        }
        return sum;
    }
    

};
typedef std::vector<File> Files;

struct Storage {
    std::string filename1, filename2, operation; // two file names 
    Files files;   
    Storage() {
        filename1 = filename2 = operation = "none";
    }
};