#define DEBUG
#undef DEBUG
#include "mod_spec.h"
#include "second_corrections_nb.h"
extern int numberOfNB;

extern int conformanceCounter[143];
void solve_90_105(SHA1& ref){
	ModStat *statNB = correctionsIndices[90-49];
	int numOfCorrectionsNB = pNumberOfCorrections[90];
	ReducedSha baseMsg;
	int firstUnSatisfied = ref.mFirstUnsatisfiedEquation;
	int weight = ref.mWindowWeight;
	baseMsg.copy(ref, 5, 15);
	if(firstUnSatisfied > 105){
		conformanceCounter[firstUnSatisfied]++;
		if(firstUnSatisfied >= conformanceToWrite){
			ref.print_message(pathToMessages, firstUnSatisfied);
		}
	}

	for(int corrIdx = 0; corrIdx < numOfCorrectionsNB; ++corrIdx){
		int tmpIdx = statNB[corrIdx].index;
//		fprintf(stderr,"%d: %d: %d %d\n", corrIdx, tmpIdx, firstUnSatisfied, weight );
//		globalModifications[tmpIdx].print_spec(stderr);rs_pause();
		baseMsg.restore(ref, 5, 15);
		if(!globalModifications[tmpIdx].used){
			if(globalModifications[tmpIdx].solve(ref, baseMsg, firstUnSatisfied, weight, statNB[corrIdx])){
				globalModifications[tmpIdx].used = true;
				firstUnSatisfied = ref.mFirstUnsatisfiedEquation;
				weight = ref.mWindowWeight;
//				fprintf(stderr,"success %d %d: %d %d\n", corrIdx, tmpIdx, firstUnSatisfied, weight );//rs_pause();
//				corrIdx = 0;
				if(firstUnSatisfied > 105){
//					fprintf(stderr,"success %d %d: %d %d\n", corrIdx, tmpIdx, firstUnSatisfied, weight );//rs_pause();
					++(statNB[corrIdx].above105counter);
					conformanceCounter[firstUnSatisfied]++;
					if(firstUnSatisfied >= conformanceToWrite){
						ref.print_message(pathToMessages, firstUnSatisfied);
					}
				}
//				break;
//				continue;
			}
		}
	}
	for(int corrIdx = 0; corrIdx < numOfCorrectionsNB; ++corrIdx){
		int tmpIdx = statNB[corrIdx].index;
		globalModifications[tmpIdx].used = false;;
	}
//	for(int corrIdx = 0; corrIdx < numberOfNB; ++corrIdx){
//		int tmpIdx = corrIdx;
////		fprintf(stderr,"%d: %d %d\n", tmpIdx, firstUnSatisfied, weight );
//		baseMsg.restore(ref, 5, 15);
//		if(!NB[corrIdx].used){
//			if(NB[corrIdx].solve(ref, baseMsg, firstUnSatisfied, weight)){
//				//need to take care of the cases where weight=0
//				NB[corrIdx].used = true;
//				firstUnSatisfied = ref.mFirstUnsatisfiedEquation;
//				weight = ref.mWindowWeight;
////				fprintf(stderr,"success %d: %d %d\n", tmpIdx, firstUnSatisfied, weight );rs_pause();
//				corrIdx = 0;
//				if(firstUnSatisfied > 105){
//					++(NB[tmpIdx].stat.above105counter);
////					print_second_message(ref);
////					if(firstUnSatisfied > 105)fprintf(stderr, "***%d:%d******\n", tmpIdx, firstUnSatisfied);
//					conformanceCounter[firstUnSatisfied]++;
//					if(firstUnSatisfied >= conformanceToWrite){
//						ref.print_message(pathToMessages, firstUnSatisfied);
//					}
//				}
//#ifdef DEBUG
//				tmp = ref;
//				tmp.updatedToRound_setter() = 4;
//				tmp.check_conformance_no_aux(36);
//				if(tmp.firstUnsatisfiedEquation_getter() != firstUnSatisfied){
//					tmp.compare_duo_Sha1ParameterNotUpdated(ref, 5, 20, stderr);
//					fprintf(stderr, "%d %d\n", tmp.firstUnsatisfiedEquation_getter(), firstUnSatisfied);
//					fprintf(stderr,"%d\n", corrIdx);
//					if(corrIdx!=0)
//						rs_pause();
//				}
//#endif
//				continue;
//				//				if ref is not improved continue to the next nb
//				//				if ref is improved but still has unsatisfied equations in 90-105, update nb[corrIdx] to "used" and restart
//				//				if all equ in 90-105 are solved: exit and call above_105();
//			}
//		}
//	}
//	for(int corrIdx = 0; corrIdx < numberOfNB; ++corrIdx){
//		NB[corrIdx].used = false;;
//	}
}


