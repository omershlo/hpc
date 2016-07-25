#ifndef WBS__H
#define WBS__H

#include <assert.h>
#include "types1.h"
#include "compare.h"

#define COLUMNS 6

using namespace std;
struct specificationOfDifference //describes the required subtraction differences in the state
{
	int rnd;
	u32 diff;
	int roundToTest;
	u32 BitToTest;
	int testMessageOrState; //0-message 1-state
	u32 IFDifferences[3];//0 - no diff, 1 - diff is required, 2 - diff is optional
	u32 correctionsFlags[5];//0 - do not correct, 1 - correct, 2 - correct if possible
	u32 expansionFlags[4];//indicates that corrections are required for the differences at w[16],...,w[19]
	void init()
	{
		rnd = diff = roundToTest = BitToTest = testMessageOrState = 0;
		IFDifferences[0] = IFDifferences[1] = IFDifferences[2] = 2;
		correctionsFlags[0] =1; correctionsFlags[1] = correctionsFlags[2] = correctionsFlags[3] = 2;correctionsFlags[4] = 1;
		expansionFlags[0] = expansionFlags[1] = expansionFlags[2] = expansionFlags[3] = 0;
	}
	void print_specificationOfDifference(FILE* fp)
	{
		fprintf(fp, "{%2d, 0x%08x, %2d, 0x%08x, %d, {%d, %d, %d}, {%d, %d, %d, %d, %d}, {%d, %d, %d, %d}}\n",
				rnd, diff,
				roundToTest, BitToTest,
				testMessageOrState,
				IFDifferences[0],IFDifferences[1],IFDifferences[2],
				correctionsFlags[0],correctionsFlags[1],correctionsFlags[2],correctionsFlags[3],correctionsFlags[4],
				expansionFlags[0],expansionFlags[1],expansionFlags[2],expansionFlags[3]);
	}
	bool scan_specificationOfDifference(FILE* fp)
	{
		if(17 != fscanf(fp,
				"%d "
				"%08x "
				"%d "
				"%08x  "
				"%d"
				"%x %x %x "
				"%x %x %x %x %x "
				"%x %x %x %x\n",
				&rnd,
				&diff,
				&roundToTest,
				&BitToTest,
				&testMessageOrState,
				&(IFDifferences[0]), &(IFDifferences[1]), &(IFDifferences[2]),
				&(correctionsFlags[0]), &(correctionsFlags[1]), &(correctionsFlags[2]), &(correctionsFlags[3]), &(correctionsFlags[4]),
				&(expansionFlags[0]), &(expansionFlags[1]), &(expansionFlags[2]), &(expansionFlags[3])))
			return false;
		return true;
	}
} ;

struct  nonLinearCorrection
{
	u32 word:16;
	u32 bit:16;
	u32 carry:8;
	u32 corr_a5:8;
	u32 corr_f:8;
	u32 corr_a30:8;
	void init()
	{
		word = bit = carry = corr_a5 = corr_f = corr_a30 = 0;
	}
	void copy(nonLinearCorrection p){
		word = p.word;
		bit = p.bit;
		carry = p.carry;
		corr_a5 = p.corr_a5;
		corr_f = p.corr_f;
		corr_a30 = p.corr_a30;
	}
 	bool operator==(const nonLinearCorrection& second)const{
		if((word^second.word) || (bit^second.bit) || (corr_a5^second.corr_a5) || (corr_f^second.corr_f) || (corr_a30^second.corr_a30) || (carry^second.carry))
		{
			return false;
		}
		return true;
	}
	void print_nonLinearCorrection(FILE* fp)
	{
		fprintf(fp, "%2d  %2d  %2d    %2x   %2x  %2x  ", word, bit, carry, corr_a5, corr_f, corr_a30);
	}
	int scan_nonLinearCorrection(FILE* fp)
	{
		int tmpWord;
		int tmpBit = 0;
		int tmpCarry = 0;
		u32 tmpCorr_a5 = 0;
		u32 tmpCorr_f = 0;
		u32 tmpCorr_a30 = 0;

		if(EOF == fscanf(fp, "%d", &tmpWord))
		{
			return EOF;
		}
		else
		{
			if(EOF == fscanf(fp, "%d %d %x %x %x\n", &tmpBit, &tmpCarry, &tmpCorr_a5, &tmpCorr_f, &tmpCorr_a30))
			{
				return EOF;
			}
			else
			{
				word     = tmpWord;
				bit      = tmpBit;
				carry    = tmpCarry;
				corr_a5  = tmpCorr_a5;
				corr_f   = tmpCorr_f;
				corr_a30 = (tmpCorr_a30) ? 1 : 0;
				return 1;
			}
		}
		return 1;
	}
};


struct linearCorrection
{
	u32 n;//:5;
	u32 worda;//:4;
	u32 wordb;//:4;
	u32 wordc;//:4;
	u32 bita;//:5;
	u32 bitb;//:5;
	u32 bitc;//:5;
	void copy(linearCorrection p){
		n = p.n;
		worda = p.worda;
		wordb = p.wordb;
		wordc = p.wordc;
		bita = p.bita;
		bitb = p.bitb;
		bitc = p.bitc;
	}
	void print_linearCorrection(FILE* fp)
	{
		switch(n)
		{
		case 3:
			fprintf(fp,"3  %2d %2d  %2d %2d  %2d %2d                                      ",(int)worda,(int)bita,(int)wordb,(int)bitb,(int)wordc,(int)bitc);
			break;
		case 2:
			fprintf(fp,"2  %2d %2d  %2d %2d                                          ",(int)worda,(int)bita,(int)wordb,(int)bitb);
			break;
		default:
			break;
		}
	}
	void scan_linearCorrection(FILE* fp, int n)
	{
	int wa, wb, wc, ba, bb, bc;
	wa = wb = wc = ba = bb = bc = 0;
		switch(n)
		{
		case 3:
			if(6 != fscanf(fp,"%d %d  %d %d  %d %d",&wa,&ba,&wb,&bb,&wc,&bc))exit(1);
			break;
		case 2:
			if(4 != fscanf(fp,"%d %d  %d %d",&wa,&ba,&wb,&bb))exit(1);
			break;
		default:
			break;
		}
		worda = wa; wordb = wb; wordc = wc;
		bita = ba; bitb = bb; bitc = bc;
	}
};

typedef union
{
	nonLinearCorrection wbnl;
	linearCorrection wbl;
} wbcorr;

struct correctionSet
{
	int nl;
	int l;
	wbcorr *wb;
#if MEASURE_CORRECTIONS_PROBABILITY > 0
	int    success;
	int    fail;
	int    neutral1;
	int    neutral;
	double pn;
	double pn1;
	double pc;
#endif
	void copy(correctionSet p){
		nl = p.nl;
		l = p.l;;
		wb = (wbcorr *)calloc(nl, sizeof(wbcorr));
		for(int i = 0; i < nl; i++){
			wb[i].wbnl.copy(p.wb[i].wbnl);
			wb[i].wbl.copy(p.wb[i].wbl);
		}
		success = p.success;
		fail = p.fail;
		neutral1 = p.neutral1;
		neutral = p.neutral;
		pn = p.pn;
		pn1 = p.pn1;
		pc = p.pc;
	}
	void init()
	{
		nl = l = 0;
#if MEASURE_CORRECTIONS_PROBABILITY > 0
	success = fail = neutral1 = neutral = 0;
	pn = pn1 = pc = 0;
#endif
	}

	void print_correctionSet(FILE* fp)
	{
		if(nl)
		{
			fprintf(fp,"%d  ",nl);
			for(int i = 0; i < nl; i++)
			{
				wb[i].wbnl.print_nonLinearCorrection(fp);
				if(i < nl-1)
					fprintf(fp, " ");
			}
		}
		if(l)
		{
			wb[nl].wbl.print_linearCorrection(fp);
		}
		if(nl)
		{
			for(int i = nl; i < 3; i++)
				fprintf(fp,"                            ");
		}
		if(l==2)
			fprintf(fp,"                             ");
		if(l==3)
			fprintf(fp,"                          ");

#if STATISTICS > 0
	fprintf(fp, "%10d  %6d  %6d  %6d   %8.3g %8.3g %8.3g", success, neutral1, neutral, fail, pn, pn1, pc);
#endif
		fprintf(fp,"\n");
	}

	int scan_wbset(FILE *correctionFile)
	{
		int n = 0;
		int nextCorrectionSet;
		init();
		while((nextCorrectionSet = fgetc(correctionFile)) != EOF)
		{
			if((nextCorrectionSet == '*')||(nextCorrectionSet == '#'))
				break;
		}
		if(nextCorrectionSet == EOF)return EOF;
		if(1 != fscanf(correctionFile, "%d", &n))return EOF;
		wb = (wbcorr *)calloc(n, sizeof(wbcorr));
		if (nextCorrectionSet == '*')
		{
			nl = n;
			for(int i = 0; i < n; i++)
				wb[i].wbnl.scan_nonLinearCorrection(correctionFile);
		}
		else if (nextCorrectionSet == '#')
		{
			l = n;
			wb[0].wbl.n = n;
			wb[0].wbl.scan_linearCorrection(correctionFile, n);
		}
		else
			exit(1);
		return 1;
	}
};

//linear equation
#define NUM_OF_LINEAR_EQUATIONS 54
struct linear_equation
{
	u32 w[16];
	char solution;
	char pivotWordIndex;
	char pivotBitIndex;
	void init()
	{
		for(int i = 0; i < 16; i++)
			w[i] = 0;
	}
};

typedef std::array<int, 6> correctionsArray;


int  read_linear_equations(char *file_name, linear_equation  *equ);
void scan_wbset_from_keyboard(correctionSet *correction);
int star_and_hash_counter(FILE *fp);
void prob_compute(correctionSet *cand, int num_of_cand);
void compute_and_print_corrections_statistics(const char *statcorrfilename, correctionSet **correction, int *num_of_corr, bool sortAndWriteCorrections);
void compute_and_print_corrections_statistics_(correctionSet **wbcorr, int *num_of_corr,
		bool sortAndWriteCorrections, int secondCorrOf, int numOfFiles, const int secondEquations[]);
void read_corrections(correctionSet **equationCorrections, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead);
void read_corrections_(correctionSet **equationCorrections, int numOfEquations, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead);
/* void initialize_listOfDiff(equation_and_solutions &listOfDiff); */
void read_correction_file(correctionSet **equationCorrections, int *numberOfCorrections, const char* pathToFile);
void compute_and_print_corrections_statistics_test(correctionSet *wbcorr, int num_of_corr, bool sortAndWriteCorrections);
#endif /*WBS__H*/
