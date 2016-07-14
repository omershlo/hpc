#include "sha1.h"
#include "duplicates.h"
#include "sha_utils.h"
#include "rounds_90_105.h"
#include <sstream>
#include <unistd.h>

#define TEST_DUPLICATES
#undef TEST_DUPLICATES
#define RAND_MAX 2^^32;
extern const int NUM_OF_NEUTRALS;
extern ModStat neutralBitsStat[];

int equation84Condition;
linear_equation linearEquations[NUM_OF_LINEAR_EQUATIONS];

std::chrono::duration<double> elapsedSeconds;
std::chrono::duration<double> elapsedSecondsTotal;
std::chrono::seconds secs(30);
int *gNumberOfCorrections;
correctionSet **gEquationCorrections;
//setlogmask (LOG_UPTO (LOG_NOTICE));

// int *gNuMOfCorr;
// correctionSet **gEquCorr;

const int equationsToRead[] = {49, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 67,	68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,	86, 87, 88, 89 };
int main(int argc, char* argv[]) {
	int pid = getpid();
	srand(time(NULL)+pid*1000);
	char host[50];
	gethostname(host, 50);
	u32 M5to15[11];
	FILE *results_fp;
	time_t t = time(0);   // get time now
	struct tm tm = *localtime( & t );
	char datum[128];
	sprintf(datum, "../sha_common_files/files/results-pid:%d-%d-%d-%dT%d:%d:%d", pid, tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("%s\n", datum);
	const char* results_file_name = datum;//"../sha_common_files/files/results-" + tts;
	cout << results_file_name << endl;
	int threshold1_print_level = 120;
	//int numOfMessages = 100000;
	int lastEquToCorrect = 142;
	if (argc >= 2) {
		  lastEquToCorrect= atoi(argv[1]);
	}
	if (argc >= 3) {
		threshold1_print_level = atoi(argv[2]);
	}
	int levHistSize = 142 - threshold1_print_level;
	if(levHistSize<0){return 1;}
	u32 *accuArr = new u32[levHistSize];
	for(int t=0;t<levHistSize;t++){accuArr[t] = 0;}
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
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	int randomMsgCounter = 0;
	int newMessageCounter = 0;

	FILE *fp_random;
	assert((fp_random = fopen("../sha_common_files/fixRandom1", "r")) != NULL);
	while (continueSearch) {
		while (newStack.empty()) {
			SHA1 newMessage;
			initialize_random_message(newMessage,M5to15) ;
		//	if (!initialize_random_message(newMessage, fp_random)) {
		//		continueSearch = false;
		//		break;
		//	} else {
				randomMsgCounter++;
		//	}
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
		SHA1 tmp;
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

		//	if (s.firstUnsatisfiedEquation_getter() > lastEquToCorrect){
		//		numberOfConformingMsg++;
		//		continue;
		//	}

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
			int returnedValue = s.correct_message_up_to_equation1(90);//, baseHashTable, alreadyInID);
			if (returnedValue == 1) {
//				if(s.firstUnsatisfiedEquation_getter()>97){
//					fprintf(stderr, "%d %d %x\n", s.mFirstUnsatisfiedEquation, s.mWindowWeight, s.mWindowWeightMask);
//					rs_pause();
//				}
				solve_90_105(s);
				if(s.mFirstUnsatisfiedEquation>=lastEquToCorrect)
				{
					continueSearch = false;
					for(int k=0;k<11;k++){fprintf(stderr, "%x ", M5to15[k]);}
					fprintf(stderr,"\n");
					end = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
					return 0;
				}
				if(s.mFirstUnsatisfiedEquation >= threshold1_print_level)
				{
					accuArr[s.mFirstUnsatisfiedEquation-threshold1_print_level]++;
				}
				if((std::chrono::system_clock::now()- start) > secs)
				{

					results_fp = fopen(results_file_name, "a+");
					time_t t = time(0);   // get time now
					struct tm tm = *localtime( & t );
					fprintf(results_fp, "host: %s lastEqToCorrect: %d Thresh: %d pid:%d %d-%d-%dT%d:%d:%d   ", host, lastEquToCorrect, threshold1_print_level, pid, tm.tm_year+1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
					for(int u=0;u<levHistSize;u++){
						fprintf(results_fp, "%u ", accuArr[u]);
					}
					fprintf(results_fp, "\n");
					
					//fprintf(stderr, "%u ", accuArr[u]);

					fclose(results_fp);
					start = std::chrono::system_clock::now();
				}
				continue;
//				if(s.firstUnsatisfiedEquation_getter()>105){fprintf(stderr, "%d\n",s.firstUnsatisfiedEquation_getter());rs_pause();}
			//	numberOfConformingMsg++;
			//	continue;
			}
//#endif
		}
	}

//	fprintf(stderr, "%d %d\n", numberOfConformingMsg, duplicatesCounter);

	for(int i = 0; i < NUM_OF_NEUTRALS; i++){
		fprintf(stderr, "%6d %6d %6d %6d %6d\n",
				neutralBitsStat[i].total, neutralBitsStat[i].failedInFirst15Rounds, neutralBitsStat[i].fail,
				neutralBitsStat[i].neutral, neutralBitsStat[i].success);
	}

#if STATISTICS & MEASURE_CORRECTIONS_PROBABILITY
	char statcorrfilename[100] = { 0 };
//	char host[50];
//	gethostname(host, 50);
	//char * host = "localhost";
	sprintf(statcorrfilename,"../sha_common_files/corr_prob/actual_correction:%s:%d", host,(unsigned) pid);
	compute_and_print_corrections_statistics(statcorrfilename, gEquationCorrections, gNumberOfCorrections, false);
//	compute_and_print_corrections_statistics_test(gEquCorr[0], gNuMOfCorr[0],true);

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

