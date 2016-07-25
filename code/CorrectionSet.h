#ifndef CORRECTIONSET__H
#define CORRECTIONSET__H

#include <string.h>
#include "types1.h"
#include "compare.h"

using namespace std;

struct Correction
{
	int round;
	u32 stateDiff;
	int shift;
	int correctionType;
	u32 functionFlagToTest;
	int scan_Correction(FILE *correctionFile);
	void print_Correction(FILE* fp);
};

struct CorrectionSet
{
	int numOfCorrections;
	Correction* correctionArray;
	int scan_CorrectionSet(FILE *correctionFile);
	void print_CorrectionSet(FILE* fp);
};
void read_CorrectionSet(CorrectionSet **equationCorrections, int numOfEquations, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead);
void write_CorrectionSet(CorrectionSet **equationCorrections, int numOfEquations, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead);
#endif /*CORRECTIONSET__H*/
