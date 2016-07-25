#include "wbs.h"
#include "sha_utils.h"
void read_corrections(correctionSet **equationCorrections, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead)
{
	for(int i = 0; i <= LAST_EQUATION_TO_CORRECT; i++)
	{
		equationCorrections[i] = NULL;
	}
	FILE* correctionFile;
	char correctionsToRead[100];
	sprintf(correctionsToRead, "%s", pathToCorrections);
	int len = strlen(correctionsToRead);
	int equationID;
	for(int equNum = 0; equNum < NUM_OF_EQUATION_TO_CORRECT; ++equNum)
	{
		equationID = equationsToRead[equNum];
		correctionFile = NULL;
		sprintf(correctionsToRead + len, "%d", equationID);
		if (NULL != (correctionFile = fopen(correctionsToRead, "r")))
		{
			numberOfCorrections[equationID] = star_and_hash_counter(correctionFile);
			equationCorrections[equationID] = (correctionSet*)calloc(numberOfCorrections[equationID], sizeof(correctionSet));
			for(int i = 0; i < numberOfCorrections[equationID]; i++)
			{
				assert(EOF != equationCorrections[equationID][i].scan_wbset(correctionFile));
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

void read_correction_file(correctionSet **equationCorrections, int* numberOfCorrections, const char* pathToFile)
{
	FILE* correctionFile;
	char correctionsToRead[100];
	sprintf(correctionsToRead, "%s", pathToFile);
	if (NULL != (correctionFile = fopen(correctionsToRead, "r")))
	{
		numberOfCorrections[0] = star_and_hash_counter(correctionFile);
		equationCorrections[0] = (correctionSet*)calloc(numberOfCorrections[0], sizeof(correctionSet));
		for(int i = 0; i < numberOfCorrections[0]; i++)
		{
			assert(EOF != equationCorrections[0][i].scan_wbset(correctionFile));
		}
		fclose(correctionFile);
	}
	else
	{
		fprintf(stderr, "cannot find file\n");
	}
}


void read_corrections_(correctionSet **equationCorrections, int numOfEquations, int *numberOfCorrections, const char* pathToCorrections, const int* equationsToRead)
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
			equationCorrections[equNum] = (correctionSet*)calloc(numberOfCorrections[equNum], sizeof(correctionSet));
			for(int i = 0; i < numberOfCorrections[equNum]; i++)
			{
				assert(EOF != equationCorrections[equNum][i].scan_wbset(correctionFile));
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


void scan_wbset_from_keyboard(correctionSet *correction)
{
	int n = 0;
	correction->l = 0;
	printf("enter n\n");
	if(1!=scanf("%d", &n))exit(0);
	correction->nl = n;
	int i;
	for(i = 0; i < n; i++)
	{
		printf("enter: word bit carry corr_a5 corr_f corr_a30\n");
		int word = 0;
		int bit = 0;
		int carry = 0;
		u32 corr_a5 = 0;
		u32 corr_f = 0;
		u32 corr_a30 = 0;
		if(6!=scanf("%d %d %d %x %x %x", &word, &bit, &carry, &corr_a5, &corr_f, &corr_a30)){printf("correction was not read correctly\n");exit(0);};
		correction->wb[i].wbnl.word = word;
		correction->wb[i].wbnl.bit = bit;
		correction->wb[i].wbnl.carry = carry;
		correction->wb[i].wbnl.corr_a5 = corr_a5;
		correction->wb[i].wbnl.corr_f = corr_f;
		correction->wb[i].wbnl.corr_a30 = (corr_a30) ? 1 : 0;
	}
	return;
}

int star_and_hash_counter(FILE *fp)
{
	int cnt = 0;
	int nextsd;
	while((nextsd = fgetc(fp)) != EOF)
	{
		if((nextsd == '*')||(nextsd == '#'))
			cnt++;
	}
	rewind(fp);
	return cnt;
}

#if STATISTICS & 1
void prob_compute(correctionSet *cand, int num_of_cand)
{
	int sum;
	for(int k = 0; k < num_of_cand; k++)
	{
		sum = cand[k].success + cand[k].fail;
		if(sum)
		{
			cand[k].pn = (double)cand[k].neutral / sum;
			cand[k].pn1 = (double)cand[k].neutral1 / sum;
			cand[k].pc = (double)cand[k].success / sum;
		}
		else
		{
			cand[k].pn = 0;
			cand[k].pn1 = 0;
			cand[k].pc = 0;
		}
		switch(cand[k].nl)
		{
		case 1:
			break;
		case 2:
			cand[k].pc *= 0.98;
			cand[k].pn1 *= 0.98;
			cand[k].pn *= 0.98;
			break;
		case 3:
			cand[k].pc *= 0.96;
			cand[k].pn1 *= 0.96;
			cand[k].pn *= 0.96;
			break;
		case 4:
			cand[k].pc *= 0.94;
			cand[k].pn1 *= 0.94;
			cand[k].pn *= 0.94;
			break;
		default:
			cand[k].pc *= 0.92;
			cand[k].pn1 *= 0.92;
			cand[k].pn *= 0.92;
			break;
		}
	}
}

void compute_and_print_corrections_statistics(const char *statcorrfilename, correctionSet **wbcorr, int *num_of_corr, bool sortAndWriteCorrections)
{
	FILE *fpstat = NULL;
	FILE *fpcorr = NULL;
	char corr2write[100] = "../sha_common_files/corrections/new/";
	int len = strlen(corr2write);
	int(*compare)(const void *, const void *);

	if ((fpstat = fopen(statcorrfilename, "w")) == NULL)
	{
		printf("cannot open %s for writing\n", statcorrfilename);
		exit(1);
	}
	for(int i = 49; i <= 90; i++)
	{
		if((i==50) || (i==51) || (i==52) || (i==53) || (i==54) || (i==55) || (i==66))continue;
		if(num_of_corr[i])
		{
			compare = compare_corr_success;
//			compare = compare_corr_success_probability;
			fprintf(fpstat, "\n@%d\n", i);
			prob_compute(wbcorr[i], num_of_corr[i]);
			qsort(wbcorr[i], num_of_corr[i], sizeof(correctionSet), compare);
			for(int j = 0; j < num_of_corr[i]; j++)
			{
				if(wbcorr[i][j].l)fprintf(fpstat,"# ");
				if(wbcorr[i][j].nl)fprintf(fpstat,"* ");
				wbcorr[i][j].print_correctionSet(fpstat);
			}
			if((sortAndWriteCorrections) || (i==85))
			{
				sprintf(corr2write+len, "%d", i);
				if ((fpcorr = fopen(corr2write, "w")) == NULL)
				{
					printf("couldn't print to %s\n", corr2write);
					exit(0);
				}
				for(int j = 0; j < num_of_corr[i]; j++)
				{
					fprintf(fpcorr, "* ");
					wbcorr[i][j].print_correctionSet(fpcorr);
				}
				fclose(fpcorr);
			}
		}
	}
	fclose(fpstat);
}
void compute_and_print_corrections_statistics_(correctionSet **wbcorr, int *num_of_corr, bool sortAndWriteCorrections, int secondCorrOf, int numOfFiles, const int secondEquations[])
{
	if(!sortAndWriteCorrections)return;
	FILE *fpcorr = NULL;
	char corr2write[100] = "../sha_common_files/corrections/new/2nd";
	int len = strlen(corr2write);
	sprintf(corr2write+len,"%d/",secondCorrOf);
	len = strlen(corr2write);
	int(*compare)(const void *, const void *);
	compare = compare_corr_success;
//	compare = compare_corr_success_probability;

	for(int i = 0; i < numOfFiles; i++)
	{
		if(num_of_corr[i])
		{
			prob_compute(wbcorr[i], num_of_corr[i]);
			qsort(wbcorr[i], num_of_corr[i], sizeof(correctionSet), compare);
			sprintf(corr2write+len, "%d", secondEquations[i]);
			if ((fpcorr = fopen(corr2write, "w")) == NULL)
			{
				printf("couldn't print to %s\n", corr2write);
				exit(0);
			}
			for(int j = 0; j < num_of_corr[i]; j++)
			{
				fprintf(fpcorr, "* ");
				wbcorr[i][j].print_correctionSet(fpcorr);
			}
			fclose(fpcorr);
		}
	}
}

void compute_and_print_corrections_statistics_test(correctionSet *wbcorr, int num_of_corr, bool sortAndWriteCorrections)
{
	if(!sortAndWriteCorrections)return;
	FILE *fpcorr = NULL;
	char corr2write[100] = "../sha_common_files/test";
	int(*compare)(const void *, const void *);
	compare = compare_corr_success;
	prob_compute(wbcorr, num_of_corr);
	qsort(wbcorr, num_of_corr, sizeof(correctionSet), compare);
	if ((fpcorr = fopen(corr2write, "w")) == NULL)
	{
		printf("couldn't print to %s\n", corr2write);
		exit(0);
	}
	for(int j = 0; j < num_of_corr; j++)
	{
		fprintf(fpcorr, "* ");
		wbcorr[j].print_correctionSet(fpcorr);
	}

	fclose(fpcorr);
}
#endif
