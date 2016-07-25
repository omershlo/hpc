/*
 * rounds_90_105.h
 *
 *  Created on: Jul 12, 2016
 *      Author: rc
 */
#ifndef ROUNDS_90_105_H_
#define ROUNDS_90_105_H_

#include "modifications.h"

const int NUM_OF_NEUTRALS = 45;

struct ModStat{
	int total;
	int success;
	int neutral;
	int fail;
	int failedInFirst15Rounds;
	void init(){
		total = success = neutral = fail = 0;
	}
};

struct ModSpec{
	bool (*functionName0 )(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg);
	bool (*functionName01)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg);
	bool (*functionName1 )(SHA1& ref, u32 xorDiff1, u32 xorDiff2,   ReducedSha& baseMsg);
	bool (*functionName2 )(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg);
	u32 xorDiff1;
	u32 xorDiff2;
	u32 xorDiff3;
	bool wOrState1;
	bool wOrState2;
	bool used;
	int conformTo;
	int type;
};

bool check_conformance_90_105(int conformanceOfModifiedMsg, int firstUnSatisfied, int weightOfModifiedMsg, int weight, ModStat neutralBitsStat[],int modIdx);

#endif /* ROUNDS_90_105_H_ */
