#include "CorrectionSet.h"

int Correction::scan_Correction(FILE *correctionFile)
{
	if(5 != fscanf(correctionFile, "%d %x %d %d %x", &round, &stateDiff, &shift, &correctionType, &functionFlagToTest))
	{
		return EOF;
	}
	else
	{
		if(correctionType==1)
		{
			stateDiff = (stateDiff << (shift+5));
		}
		else
		{
			stateDiff = (stateDiff << shift);
		}
	}
	return 0;
}

void Correction::print_Correction(FILE* fp)
{
	fprintf(fp, "%2d 0x%04x  %2d  %2d  %x    ", round, stateDiff, shift, correctionType, functionFlagToTest);
}

int CorrectionSet::scan_CorrectionSet(FILE *correctionFile)
{
	int nextCorrectionSet;
	while((nextCorrectionSet = fgetc(correctionFile)) != EOF)
	{
		if(nextCorrectionSet == '*')
			break;
	}
	if(nextCorrectionSet == EOF)return EOF;
	if(1 != fscanf(correctionFile, "%d", &numOfCorrections))return EOF;
	correctionArray = (Correction *)calloc(numOfCorrections, sizeof(Correction));
	for(int i = 0; i < numOfCorrections; i++)
		correctionArray[i].scan_Correction(correctionFile);
	return 1;
}

void CorrectionSet::print_CorrectionSet(FILE* fp)
{
	fprintf(fp, "* %d  ", numOfCorrections);
	for(int i = 0; i < numOfCorrections; ++i)
	{
		correctionArray[i].print_Correction(fp);
	}
	s.print_statistics(fp);
	fprintf(fp, "\n");
}

void read_CorrectionSet(CorrectionSet **equationCorrections, int numOfEquations, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead)
{
	for(int i = 0; i < numOfEquations; i++)
	{
		equationCorrections[i] = NULL;
		numberOfCorrections[i] = 0;
	}
	FILE* correctionFile;
	char correctionsToRead[100];
	sprintf(correctionsToRead, "%s", pathToCorrections);
	int len = strlen(correctionsToRead);
	int equationID;
	for(int equNum = 0; equNum < numOfEquations; ++equNum)
	{
		equationID = equationsToRead[equNum];
		correctionFile = NULL;
		sprintf(correctionsToRead + len, "%d", equationID);
//		fprintf(stderr,"%s\n",correctionsToRead);
		if (NULL != (correctionFile = fopen(correctionsToRead, "r")))
		{
			numberOfCorrections[equNum] = star_and_hash_counter(correctionFile);
			equationCorrections[equNum] = (CorrectionSet*)calloc(numberOfCorrections[equNum], sizeof(CorrectionSet));
			for(int i = 0; i < numberOfCorrections[equNum]; i++)
			{
				assert(EOF != equationCorrections[equNum][i].scan_CorrectionSet(correctionFile));
			}
			fclose(correctionFile);
		}
		else
		{
			fprintf(stderr, "cannot find file %d\n", equationID);
			continue;
		}
	}
}

void write_CorrectionSet(CorrectionSet **equationCorrections, int numOfEquations, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead)
{
	FILE* correctionFile;
	char correctionsToRead[100];
	sprintf(correctionsToRead, "%s", pathToCorrections);
	int len = strlen(correctionsToRead);
	int equationID;
	for(int equNum = 0; equNum < numOfEquations; ++equNum)
	{
		equationID = equationsToRead[equNum];
		correctionFile = NULL;
		sprintf(correctionsToRead + len, "/statistics/%d", equationID);
//		fprintf(stderr,"%s\n",correctionsToRead);
		if (NULL != (correctionFile = fopen(correctionsToRead, "w")))
		{
			for(int i = 0; i < numberOfCorrections[equNum]; i++)
			{
				equationCorrections[equNum][i].print_CorrectionSet(correctionFile);
			}
			fclose(correctionFile);
		}
	}
}
