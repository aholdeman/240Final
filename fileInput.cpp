//takes in an input file and reads its contents to a string array
//just making this edit to see if i know how to use github
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	//if the user does not input an input text file
	if (argc != 3) {
		cout << "Usage: " << argv[0] << "inputfile.txt" << "outputfile.txt"; //correct usage
		exit(1);
	}

	ifstream ifs; //initializes the file reader

	ifs.open(argv[1]); //opens the specified file

	if(ifs.fail()){ //if there's an error
		cout << "Error opening the file" << argv[1] << "\n";
		exit(1);
	}

	string Input = " ";

	int sequenceIndex = 0;
	
	while(!ifs.eof()) { //while the scanner is not at the end of the file
		getline(ifs, Input); //skips the first line that will be an ID
		getline (ifs, Input); //reads line and assigns it to the string Input
		sequenceIndex++;
	}

	Sequence sequenceArray[sequenceIndex];
	
	//ifs.close(); //closes input file to prevent memory leak

	//prints the array to see if it works
	int newSequenceIndex = 0;
	
	while(!ifs.eof()){
		getline(ifs, Input);
		getline (ifs, Input); // this is the actual sequence info
		sequenceArray[sequenceIndex];
		sequenceIndex++;
	}
}