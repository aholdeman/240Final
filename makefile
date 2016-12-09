# make file for 240 Final Project, written by Abby Holdeman, Phoebe Ngo, and Lauren Nix
# to run, make the make file, and execute the 240GeneFinal program like you would an a.out file.
# Usage for 240GeneFinal: <inputFile name> <outputFile name> <minimum # overlap>

all: 
	g++ main.cpp Gene.cpp Sequence.cpp -o 240GeneFinal
clean:
	rm -f 240GeneFinal
