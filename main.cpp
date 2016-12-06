/* 
 * File:   main.cpp
 * Author: PhoebeNgo
 *
 * Created on December 3, 2016, 5:53 PM
 */

#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char** argv) {
    clock_t executionTime = clock(); // calculates execution time
   
    //if the user does not input an input text file
    if (argc != 3) {
            cout << "Usage: " << argv[0] << "<inputfile.txt>" << "<outputfile.txt>" << "<size of overlap>"; //correct usage
            exit(1);
    }

    ifstream infile; //initializes file reader
    ofstream outfile;
    infile.clear();
    infile.open(argv[1]); //opens the specified file

    if(infile.fail()){ //if there's an error
            cout << "Error opening the file" << argv[1] << "\n";
            exit(1);
    }
    
    Gene myGene(infile);
    
    infile.close();
    outfile.close();
    printf("Execution time: %.2fs\n", (double)(clock() - executionTime)/CLOCKS_PER_SEC);
    return 0;
}

