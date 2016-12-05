//takes in an input file and reads its contents to a string array
//just making this edit to see if i know how to use github
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	//if the user does not input an input text file
	if (argc != 2) {
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
	int counter = sequenceIndex - 2;

	sequenceIndex = 0;
	ifs.clear();
	ifs.seekg(0);
	while(sequenceIndex <= counter){
		getline(ifs, Input);
		getline (ifs, Input); // this is the actual sequence info
		int i = 0;
		while(Input[i] != '\0') {
			if(Input[i] == 'C' || Input[i] == 'A' || Input[i] == 'G' || Input[i] == 'T') {
				i++;
			}
			else {
				cout << "Invalid input. Sequences must contain ONLY A, G, C, or T." << endl;
				exit(1);
			}
		}
		sequenceArray[sequenceIndex] = Input;
		sequenceIndex++;
	}
	ifs.close();

}
