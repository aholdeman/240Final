/* make file for 240 Final Project, written by Abby Holdeman, Phoebe Ngo, and Lauren Nix
* to run, make the make file, and execute the 240GeneFinal program like you would an a.out file.
* Usage for 240GeneFinal: <inputFile name> <outputFile name> <minimum # overlap>
*/
all:
	g++ main.cpp Gene.h Sequence.h Gene.cpp Sequence.cpp 240GeneFinal
clean:
	rm 240GeneFinal
