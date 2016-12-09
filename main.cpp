/* 
 * File:   main.cpp
 * Author: PhoebeNgo
 *
 * Created on December 3, 2016, 5:53 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "Gene.h"
#include "Sequence.h"

using namespace std;

int main(int argc, char** argv) {
  clock_t executionTime = clock(); // calculates execution time
  //if the user does not input an input text file
    if (argc != 4) {
        cout << argc << endl;
            cout << "Usage: " << argv[0] << " <inputfile.txt> " << " <outputfile.txt> " << " <size of overlap>"; //correct usage
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
    myGene.search(atoi(argv[3]));
    outfile.open(argv[2]);
    if (outfile.fail()) {
        cout << "Error: print out not successful" << endl;
        exit(1);
    }
    myGene.print(outfile);
    
    infile.close();
    outfile.close();
    printf("Execution time: %.4fs\n", (double)(clock() - executionTime)/CLOCKS_PER_SEC);
    return 0;
}