
#include "rounds_90_105.h"
#include "second_corrections_nb.h"
ModStat neutralBitsStat[NUM_OF_NEUTRALS];

bool check_conformance_90_105(int conformanceOfModifiedMsg, int firstUnSatisfied, int weightOfModifiedMsg, int weight,
		ModStat neutralBitsStat[],int modIdx){
	if(conformanceOfModifiedMsg < 90){
		++(neutralBitsStat[modIdx].fail);
		return false;
	}
	else if(conformanceOfModifiedMsg < 106){
		if((conformanceOfModifiedMsg > firstUnSatisfied) || (weightOfModifiedMsg < weight)){
			++(neutralBitsStat[modIdx].success);
			return true;
		}
		else if(((conformanceOfModifiedMsg < firstUnSatisfied) && (weightOfModifiedMsg  == weight)) ||
				((conformanceOfModifiedMsg == firstUnSatisfied) && (weightOfModifiedMsg  > weight)) ||
				((conformanceOfModifiedMsg == firstUnSatisfied) && (weightOfModifiedMsg == weight))){
			++(neutralBitsStat[modIdx].neutral);
			return false;
		}
		else{
			++(neutralBitsStat[modIdx].fail);
			return false;
		}
	}
	else{
		++(neutralBitsStat[modIdx].success);
		return true;
	}
	return false;
}

ModSpec neutralBits[] = {
		{mod_6   , NULL  , NULL   , NULL    , B7      , 0    , 0  ,false, false, false, 0, 0},
		{mod_6   , NULL  , NULL   , NULL    , B8      , 0    , 0  ,false, false, false, 0, 0},
		{mod_14  , NULL  , NULL   , NULL    , B5      , 0    , 0  ,false, false, false, 0, 0},
		{NULL    , NULL  , mod_5_6, NULL    , B10     , B8   , 0  ,false, false, false, 0, 1},
		{NULL    , NULL  , mod_5_6, NULL    , B9      , B7   , 0  ,false, false, false, 0, 1},
		{mod_14  , NULL  , NULL   , NULL    , B7      , 0    , 0  ,false, false, false, 0, 0},
		{NULL    , NULL  , mod_5_6, NULL    , B9      , B8   , 0  ,false, false, false, 0, 1},
		{mod_14  , NULL  , NULL   , NULL    , B6      , 0    , 0  ,false, false, false, 0, 0},
		{NULL    , NULL  , mod_5_6, NULL    , B10|B9  , B8   , 0  ,false, false, false, 0, 1},
		{NULL    , NULL  , NULL   , mod_9_14, B8      , B5   , 0  ,false, false, false, 0, 2},
		{mod_5   , mod_13, NULL   , NULL    , B10|B9  , B6   , 0  ,false, true , false, 0, 3},
		{mod_6   , mod_13, NULL   , NULL    , B7      , B6   , 0  ,false, true , false, 0, 3},
		{mod_7   , mod_15, NULL   , NULL    , B7      , B28  , 0  ,false, false, false, 0, 3},
		{mod_15  , NULL  , NULL   , NULL    , B25     , 0    , 0  ,false, false, false, 0, 0},
		{mod_13  , NULL  , NULL   , NULL    , B6      , 0    , 0  ,false, false, false, 0, 0},
		{mod_5   , mod_10, NULL   , NULL    , B10     , B10  , 0  ,false, true , false, 0, 3},
		{NULL    , NULL  , mod_5_6, NULL    , B10|B9  , B7   , 0  ,false, false, false, 0, 1},
		{NULL    , NULL  , mod_5_6, NULL    , B10     , B7   , 0  ,false, false, false, 0, 1},
		{NULL    , NULL  , NULL   , mod_7_15, B7      , B28  , 0  ,false, false, false, 0, 2},
		{NULL    , NULL  , NULL   , mod_7_15, B8      , B29  , 0  ,false, false, false, 0, 2},
		{NULL    , NULL  , NULL   , mod_7_12, B7      , B7   , 0  ,false, true , false, 0, 2},
		{mod_5   , NULL  , NULL   , NULL    , B9      , 0    , 0  ,false, false, false, 0, 0},
		{mod_9_op, NULL  , NULL   , NULL    , B8      , 0    , 0  ,false, false, false, 0, 0},
		{mod_9   , NULL  , NULL   , NULL    , B8      , 0    , 0  ,false, false, false, 0, 0},
		{mod_6   , mod_13, NULL   , NULL    , B8|B7   , B6   , 0  ,false, true , false, 0, 3},
		{NULL    , NULL  , NULL   , mod_11_14, B7     , B5   , 0  ,true , false, false, 0, 2},
		{mod_6   , mod_14, NULL   , NULL    , B7      , B8   , 0  ,false, true , false, 0, 3},
		{mod_6   , mod_14, NULL   , NULL    , B7      , B5   , 0  ,false, true , false, 0, 3},
		{mod_13  , NULL  , NULL   , NULL    , B8      , 0    , 0  ,false, false, false, 0, 0},
		{mod_14  , NULL  , NULL   , NULL    , B6|B5   , 0    , 0  ,false, false, false, 0, 0},
		{mod_14  , NULL  , NULL   , NULL    , B8      , 0    , 0  ,false, false, false, 0, 0},
		{mod_13  , NULL  , NULL   , NULL    , B5      , 0    , 0  ,true , false, false, 0, 0},
		{mod_5   , mod_13, NULL   , NULL    , B9      , B6   , 0  ,false, true , false, 0, 3},
		{mod_13  , NULL  , mod_5_6, NULL     , B10    , B8   , B6 ,false, false, false, 0, 4},
		{NULL    , NULL  , mod_5_6, NULL    , B10|B9  , B8|B7, 0  ,false, false, false, 0, 1},
		{mod_10  , NULL  , NULL   , NULL     , B8     , 0    , 0  ,false, false, false, 0, 0},
		{NULL    , NULL  , NULL   , mod_8_11 , B8     , B9   , 0  ,false, true , false, 0, 2},
		{mod_6   , mod_14, NULL   , NULL    , B7      , B7   , 0  ,false, true , false, 0, 3},
		{mod_5   , mod_14, NULL   , NULL    , B9      , B5   , 0  ,false, true , false, 0, 3},
		{mod_5   , mod_14, NULL   , NULL    , B10     , B6   , 0  ,false, true , false, 0, 3},
		{mod_9_op, NULL  , NULL   , NULL    , B7      , 0    , 0  ,false, false, false, 0, 0},
		{mod_6   , mod_13, NULL   , NULL    , B8      , B6   , 0  ,false, true , false, 0, 3},
		{mod_5   , NULL  , NULL   , NULL    , B10|B9  , 0    , 0  ,false, false, false, 0, 0},
		{mod_9   , NULL  , NULL   , NULL    , B7      , 0    , 0  ,false, false, false, 0, 0},
		{mod_13  , NULL  , mod_5_6, NULL     , B9     , B7   , B6 ,false, false, false, 0, 4}
};

bool solve(SHA1& ref, ReducedSha& baseMsg, ModSpec modification, int modIdx, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg){
	int restoreFromRound = 5;
	++(neutralBitsStat[modIdx].total);
	switch(modification.type){
	case 0:
		if(!modification.functionName0(ref, modification.xorDiff1, modification.wOrState1, baseMsg)) {
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			return false;
		}
		break;
	case 1:
		if(!modification.functionName1(ref, modification.xorDiff1, modification.xorDiff2, baseMsg)){
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			return false;
		}
		break;
	case 2:
		if(!modification.functionName2(ref, modification.xorDiff1, modification.wOrState1, modification.xorDiff2, modification.wOrState2, baseMsg)){
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			return false;
		}
		break;
	case 3:
		if(!modification.functionName0(ref, modification.xorDiff1, modification.wOrState1, baseMsg)){
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			return false;
		}
		if(!modification.functionName01(ref, modification.xorDiff2, modification.wOrState2, baseMsg)){
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			baseMsg.restore(ref, 5, 15);
			return false;
		}
		break;
	case 4:
		if(!modification.functionName1(ref, modification.xorDiff1, modification.xorDiff2, baseMsg)) {
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			return false;
		}
		if(!modification.functionName0(ref, modification.xorDiff3, modification.wOrState1, baseMsg)) {
			++(neutralBitsStat[modIdx].failedInFirst15Rounds);
			baseMsg.restore(ref, 5, 15);
			return false;
		}
		break;
	default:
		break;
	}

	int conformanceOfModifiedMsg = updateAndTest(ref);
	int weightOfModifiedMsg = ref.mWindowWeight;
	if(check_conformance_90_105(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg, weightOfModifiedMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)){
		return true;
	}

	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction_nb(ref, intermediate, firstUnSatisfiedOriginalMsg, conformanceOfModifiedMsg, weightOfOriginalMsg,
			neutralBitsStat, modIdx, restoreFromRound))return true;
	m.restore(ref, 5, 15);
	return false;
}

void solve_90_105(SHA1& ref){
	ReducedSha baseMsg;
	int firstUnSatisfied = ref.mFirstUnsatisfiedEquation;
	int weight = ref.mWindowWeight;
	baseMsg.copy(ref, 5, 15);
//	fprintf(stderr, "new\n");
	for(int corrIdx = 0; corrIdx < NUM_OF_NEUTRALS; ++corrIdx){
		neutralBits[corrIdx].used = false;;
	}
	for(int corrIdx = 0; corrIdx < NUM_OF_NEUTRALS; ++corrIdx){
		baseMsg.restore(ref, 5, 15);
		if(!neutralBits[corrIdx].used){
			if(solve(ref, m, neutralBits[corrIdx], corrIdx, firstUnSatisfied, weight)){
//need to take care of the cases where weight=0
			//	fprintf(stderr,"%d: %d %d   %d %d \n", corrIdx, firstUnSatisfied, weight, ref.mFirstUnsatisfiedEquation, ref.mWindowWeight);
				neutralBits[corrIdx].used = true;
				firstUnSatisfied = ref.mFirstUnsatisfiedEquation;
				weight = ref.mWindowWeight;
				corrIdx = 0;
				if(firstUnSatisfied>105)
					{
			//			rs_pause();
						return;
					}
				continue;

				//				if ref is not improved continue to the next nb

				//				if ref is improved but still has unsatisfied equations in 90-105, update nb[corrIdx] to "used" and restart

				//				if all equ in 90-105 are solved: exit and call above_105();

			}
		}
	}
}

