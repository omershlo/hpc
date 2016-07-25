#include "sha1.h"
#include "duplicates.h"
#include "sha_utils.h"
#include "mod_spec.h"
#include <math.h>
#define TEST_DUPLICATES
#undef TEST_DUPLICATES
#define NUM_OF_EQU 42

int numberOfNB;
int conformanceToWrite;
char pathToMessages[] = "../sha_common_files/messages/";
int conformanceCounter[143];

ModSpec *NB;
ModSpec *globalModifications;
int numOfCorr[NUM_OF_EQU];

ModStat *correctionsIndices[NUM_OF_EQU];
int numberOfCorrections[NUM_OF_EQU];
int* pNumberOfCorrections;

int equation84Condition;
linear_equation linearEquations[NUM_OF_LINEAR_EQUATIONS];

std::chrono::duration<double> elapsedSeconds;
std::chrono::duration<double> elapsedSecondsTotal;

int *gNumberOfCorrections;
correctionSet **gEquationCorrections;

// int *gNuMOfCorr;
// correctionSet **gEquCorr;

int compareNB(const void *nb1, const void *nb2){
	double p1 =	(double)((*(ModSpec*)nb1).stat.success)/(
			((*(ModSpec*)nb1).stat.success) +
			((*(ModSpec*)nb1).stat.neutral) +
			((*(ModSpec*)nb1).stat.fail) +
			((*(ModSpec*)nb1).stat.failedInFirst15Rounds));
	double p2 =	(double)((*(ModSpec*)nb2).stat.success)/(
			((*(ModSpec*)nb2).stat.success) +
			((*(ModSpec*)nb2).stat.neutral) +
			((*(ModSpec*)nb2).stat.fail) +
			((*(ModSpec*)nb2).stat.failedInFirst15Rounds));

	if(p1 > p2) return -1;
	if(p1 == p2) return 0;
	if(p1 < p2) return 1;
	return 0;
}

int compareStatistics(const void *s1, const void *s2){
	double p1 =	(double)((*(ModStat*)s1).success)/(
			((*(ModStat*)s1).success) +
			((*(ModStat*)s1).neutral) +
			((*(ModStat*)s1).fail) +
			((*(ModStat*)s1).failedInFirst15Rounds));
	double p2 =	(double)((*(ModStat*)s2).success)/(
			((*(ModStat*)s2).success) +
			((*(ModStat*)s2).neutral) +
			((*(ModStat*)s2).fail) +
			((*(ModStat*)s2).failedInFirst15Rounds));

	if(p1 > p2) return -1;
	if(p1 == p2) return 0;
	if(p1 < p2) return 1;
	return 0;
}

const int equationsToRead[] = {49, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 67,	68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,	86, 87, 88, 89 };
const int indicesOfCorrectionsToRead[] = {89, 90};
const int numOfCorrectionsToRead =2;

void readIndices(ModStat** correctionsIndices, int* pNumberOfCorrections, const int indicesOfCorrectionsToRead[]){
	for(int idx = 0; idx < numOfCorrectionsToRead; ++idx){
		char fileName[100];
		FILE* fileToRead;
		int numOfIndices = 0;
		int corrToRead = indicesOfCorrectionsToRead[idx];
		sprintf(fileName, "../sha_common_files/global_corrections/%d", corrToRead);
		assert((fileToRead = fopen(fileName, "r")) != NULL);
		int scanNum;
		while((EOF != fscanf(fileToRead, "%d\n", &scanNum))){numOfIndices++;}
		rewind(fileToRead);
		correctionsIndices[corrToRead-49] = (ModStat*)calloc(numOfIndices, sizeof(ModStat));
		pNumberOfCorrections[corrToRead] = numOfIndices;
		numOfIndices = 0;
		while((EOF != fscanf(fileToRead, "%d\n", &(correctionsIndices[corrToRead-49][numOfIndices].index)))){
			correctionsIndices[corrToRead-49][numOfIndices++].init();
		};
//		fprintf(stderr, "pNumberOfCorrections[%d] = %d\n", corrToRead, pNumberOfCorrections[corrToRead]);rs_pause();
	}
}

void printStatistics(ModStat** correctionsIndices, int* pNumberOfCorrections, const int indicesOfCorrectionsToRead[]){
	char fileName[100];
	FILE* fileToWrite;
	sprintf(fileName, "../sha_common_files/global_corrections/statistics");
	assert((fileToWrite = fopen(fileName, "w")) != NULL);
	for(int idx = 0; idx < numOfCorrectionsToRead; ++idx){
		int corrToWrite = indicesOfCorrectionsToRead[idx];
		fprintf(fileToWrite, "%d\n", corrToWrite);
		for(int i = 0; i < pNumberOfCorrections[corrToWrite]; ++i){
			correctionsIndices[corrToWrite-49][i].print(fileToWrite);
		}
		fprintf(fileToWrite, "\n");
	}
	fclose(fileToWrite);
}


int main(int argc, char* argv[]) {
	conformanceToWrite = 130;

	//read nb 90_105
	FILE *fp_NB;
	assert((fp_NB = fopen("../sha_common_files/global_corrections/nb_sorted", "r")) != NULL);
	numberOfNB = 0;
	ModSpec tmp;
	while(tmp.read_spec(fp_NB))numberOfNB++;
	rewind(fp_NB);
	NB = (ModSpec*)calloc(numberOfNB, sizeof(ModSpec));
	for(int i = 0; i < numberOfNB; i++){
		NB[i].read_spec(fp_NB);
		NB[i].modIndex = i;
	}
	fclose(fp_NB);
	//read modifications up to 89
	assert((fp_NB = fopen("../sha_common_files/global_corrections/gm_rafi", "r")) != NULL);
	int numberOfModifications = 0;
	while(tmp.read_spec(fp_NB))numberOfModifications++;
	rewind(fp_NB);
	globalModifications = (ModSpec*)calloc(numberOfModifications, sizeof(ModSpec));
	for(int i = 0; i < numberOfModifications; i++){
		globalModifications[i].read_spec(fp_NB);
		globalModifications[i].modIndex = i;
	}
	fclose(fp_NB);

	//read indices
	for(int i = 0; i < NUM_OF_EQU; i++){
		correctionsIndices[i] = NULL;
		pNumberOfCorrections = numberOfCorrections - 49;
	}
	readIndices(correctionsIndices, pNumberOfCorrections, indicesOfCorrectionsToRead);

	for(int i = 0; i < 143; i++)
		conformanceCounter[i] = 0;
	int numOfMessages = 100000;
	int lastEquToCorrect = 89;
	if (argc >= 2) {
		numOfMessages = atoi(argv[1]);
	}
	if (argc >= 3) {
		lastEquToCorrect = atoi(argv[2]);
	}
//	 gNuMOfCorr = (int *) calloc(1, sizeof(int));
//	 gEquCorr = (correctionSet **) calloc(1, sizeof(correctionSet*));
//	 read_correction_file(gEquCorr, gNuMOfCorr, "../sha_common_files/test");

	assert((read_linear_equations((char* )"../sha_common_files/files/linear", linearEquations)));

	gNumberOfCorrections = (int *) calloc(LAST_EQUATION_TO_CORRECT + 1,	sizeof(int));
	gEquationCorrections = (correctionSet **) calloc(LAST_EQUATION_TO_CORRECT + 1, sizeof(correctionSet*));
	read_corrections(gEquationCorrections, gNumberOfCorrections,"../sha_common_files/corrections/24052016/", equationsToRead);

	mStack newStack;
	bool continueSearch = true;
	int returnedValue = 0;
	int numberOfConformingMsg = 0;
	int numberOfProcessedMessages = 0;
	int duplicatesCounter = 0;
	std::chrono::time_point<std::chrono::system_clock> start, end, tmpTime;
	start = std::chrono::system_clock::now();
	int randomMsgCounter = 0;
	int newMessageCounter = 0;

	FILE *fp_random;
//	assert((fp_random = fopen("../sha_common_files/fixRandom1", "r")) != NULL);
	assert((fp_random = fopen("/dev/urandom", "r")) != NULL);

	while (continueSearch && (numberOfConformingMsg < numOfMessages)) {
	//while (continueSearch) {
		while (newStack.empty()) {
			SHA1 newMessage;
			if (!initialize_random_message(newMessage, fp_random)) {
				continueSearch = false;
				break;
			} else {
				randomMsgCounter++;
			}
			//generate a message that conforms to the first 16 rounds and then continue and fix the message up to equation 79
			if (0 < (returnedValue = test_and_fix_till_round_15(newMessage, 5, linearEquations))) {
//				if(!(newMessage.a_getter(11) & B5))continue;

				if (newMessage.correct_message_up_to_equation(79)) {
					newMessageCounter++;
					newMessage.derive_delta_linear(newMessageCounter,linearEquations, newStack);
				}
			}
		}
		if (!continueSearch)
			break;
//#ifdef TEST_DUPLICATES
//		mHashTable baseHashTable;
//		messageID alreadyInID; //if the message we want to insert is already in, alreadyInID will be updated with the id of the colliding message
//#endif
		SHA1 s;
		s.set_messageMask();
		while (!newStack.empty()) {
			numberOfProcessedMessages++;
			messageInStack m = newStack.top();
			newStack.pop();
			s.id = m.id;
			for (int i = 5; i < 16; i++)
				s.w_setter(i) = m.message[i - 5];

//			s.mW[5] = m.message[0];
//			s.mA[6] = s.mW[5] + 0xc61972aa;//K_00_19 + 0x0fe00902 + 0x12db780e + 0x48db7801;
//			s.mW[6] = m.message[1];
//			s.mA[7] = s.mW[6] + ROTATE(s.mA[6], 5) + 0xcd7ef153;//K_00_19 + 0x62a0ff8c + 0x105b782e;
//			s.mW[7] = m.message[2];
//			s.mA[8] = s.mW[7] + K_00_19 + ROTATE(s.mA[7], 5) + F_00_19(s.mA[6], 0x041fc012, 0x42a0000c) + 0x62ffffc4;
//			s.mW[8] = m.message[3];
//			s.mA30[6] = ROTATE(s.mA[6], 30);
//			s.mA[9] = s.mW[8] + K_00_19 + ROTATE(s.mA[8], 5) + F_00_19(s.mA[7], s.mA30[6], 0x041fc012) + 0x42a0000c;
//			s.mW[9] = m.message[4];
//			s.mA30[7] = ROTATE(s.mA[7], 30);
//			s.mA[10] = s.mW[9] + K_00_19 + ROTATE(s.mA[9], 5) + F_00_19(s.mA[8], s.mA30[7], s.mA30[6]) + 0x041fc012;
//			s.mW[10] = m.message[5];
//			s.mA30[8] = ROTATE(s.mA[8], 30);
//			s.mA[11] = s.mW[10] + K_00_19 + ROTATE(s.mA[10], 5) + F_00_19(s.mA[9], s.mA30[8], s.mA30[7]) + s.mA30[6];
//			s.mW[11] = m.message[6];
//			s.mA30[9] = ROTATE(s.mA[9], 30);
//			s.mA[12] = s.mW[11] + K_00_19 + ROTATE(s.mA[11], 5) + F_00_19(s.mA[10], s.mA30[9], s.mA30[8]) + s.mA30[7];
//			s.mW[12] = m.message[7];
//			s.mA30[10] = ROTATE(s.mA[10], 30);
//			s.mA[13] = s.mW[12] + K_00_19 + ROTATE(s.mA[12], 5) + F_00_19(s.mA[11], s.mA30[10], s.mA30[9]) + s.mA30[8];
//			s.mW[13] = m.message[8];
//			s.mA30[11] = ROTATE(s.mA[11], 30);
//			s.mA[14] = s.mW[13] + K_00_19 + ROTATE(s.mA[13], 5) + F_00_19(s.mA[12], s.mA30[11], s.mA30[10]) + s.mA30[9];
//			s.mW[14] = m.message[9];
//			s.mA30[12] = ROTATE(s.mA[12], 30);
//			s.mA[15] = s.mW[14] + K_00_19 + ROTATE(s.mA[14], 5) + F_00_19(s.mA[13], s.mA30[12], s.mA30[11]) + s.mA30[10];
//			s.mW[15] = m.message[10];
//			s.mA30[13] = ROTATE(s.mA[13], 30);
//			s.mA[16] = s.mW[15] + K_00_19 + ROTATE(s.mA[15], 5) + F_00_19(s.mA[14], s.mA30[13], s.mA30[12]) + s.mA30[11];
//			c_check_conformance(s, 70);

			s.check_conformance(70);

			if (s.firstUnsatisfiedEquation_getter() > lastEquToCorrect){
				numberOfConformingMsg++;
				continue;
			}

//#ifdef TEST_DUPLICATES
//			int returnedValue = s.correct_message_up_to_equation(lastEquToCorrect+1, baseHashTable, alreadyInID);
//			if (returnedValue == 1) {
//				numberOfConformingMsg++;
//				continue;
//			} else if (returnedValue == 2) {
//				duplicatesCounter++;
//				continue;
//			}
//#else
			for(int corrIdx = 0; corrIdx < numberOfNB; ++corrIdx){
				NB[corrIdx].used = false;;
			}
			int returnedValue = s.correct_message_up_to_equation1(lastEquToCorrect+1);//, baseHashTable, alreadyInID);
			if (returnedValue == 1) {
//				if(s.firstUnsatisfiedEquation_getter()>97){
//					fprintf(stderr, "%d %d %x\n", s.mFirstUnsatisfiedEquation, s.mWindowWeight, s.mWindowWeightMask);
//					rs_pause();
//				}
				solve_90_105(s);
//				if(s.firstUnsatisfiedEquation_getter()>105){fprintf(stderr, "%d\n",s.firstUnsatisfiedEquation_getter());rs_pause();}
//				if(s.firstUnsatisfiedEquation_getter()>105)
//					conformanceCounter[s.firstUnsatisfiedEquation_getter()]++;
				if((numberOfConformingMsg & 0xfffff) == 0xfffff){
					tmpTime = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = tmpTime - start;
					std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
					int counterNormalized = 0;
					for(int i = 106; i < 143; i++){
						if(conformanceCounter[i]){
							counterNormalized += conformanceCounter[i] * pow(2, i-106);
							fprintf(stderr, "%3d:  %6d\n", i, conformanceCounter[i]);
						}
					}
					fprintf(stderr,"\n");
				}
				numberOfConformingMsg++;
				continue;
			}
//#endif
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	fprintf(stderr, "%d %d\n", numberOfConformingMsg, duplicatesCounter);

//	for(int i = 0; i < NUM_OF_NEUTRALS; i++){
//		fprintf(stderr, "%2d: %8d %8d %8d %8d %8d\n",
//				i, NB[i].stat.total, NB[i].stat.failedInFirst15Rounds, NB[i].stat.fail,
//				NB[i].stat.neutral, NB[i].stat.success);
//	}

	qsort(NB, numberOfNB, sizeof(ModSpec), compareNB);

//	FILE *fp_soretdNB;
//	assert((fp_soretdNB = fopen("../sha_common_files/corrections/neutarl_bits_sorted", "w")) != NULL);
//	fflush(fp_soretdNB);
//	fclose(fp_soretdNB);
#if STATISTICS & MEASURE_CORRECTIONS_PROBABILITY
	char statcorrfilename[100] = { 0 };
	char host[50];
	pid_t pid = 0;
	gethostname(host, 50);
	pid = getpid();
	sprintf(statcorrfilename,"../sha_common_files/corr_prob/actual_correction:%s:%d", host,(unsigned) pid);
	compute_and_print_corrections_statistics(statcorrfilename, gEquationCorrections, gNumberOfCorrections, false);

	for(int idx = 0; idx < numOfCorrectionsToRead; ++idx){
		int corrToSort = indicesOfCorrectionsToRead[idx];
		qsort(correctionsIndices[corrToSort-49], pNumberOfCorrections[corrToSort], sizeof(ModStat), compareStatistics);
	}
	printStatistics(correctionsIndices, pNumberOfCorrections, indicesOfCorrectionsToRead);

	//	compute_and_print_corrections_statistics_test(gEquCorr[0], gNuMOfCorr[0],true);
	int counterNormalized = 0;
	for(int i = 106; i < 143; i++){
		if(conformanceCounter[i]){
			counterNormalized += conformanceCounter[i] * pow(2, i-106);
			fprintf(stderr, "%3d:  %6d\n", i, conformanceCounter[i]);
		}
	}
	fprintf(stderr, "counterNormalized = %d\n", counterNormalized);
#endif
	//release mem
	for (int i = 0; i <= LAST_EQUATION_TO_CORRECT; i++) {
		if (gEquationCorrections[i] != NULL) {
			for (int j = 0; j < gNumberOfCorrections[i]; j++)
				free(gEquationCorrections[i][j].wb);
		}
		free(gEquationCorrections[i]);
	}
	free(gNumberOfCorrections);
	free(gEquationCorrections);
	fclose(fp_random);
}

