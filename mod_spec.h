/*
 * rounds_90_105.h
 *
 *  Created on: Jul 12, 2016
 *      Author: rc
 */
#ifndef ROUNDS_90_105_H_
#define ROUNDS_90_105_H_

#include "modifications.h"
#include "second_corrections_nb.h"
#include "second_corrections.h"

extern int conformanceToWrite;
extern char pathToMessages[];


struct ModStat{
	int index;
	int total;
	int success;
	int neutral;
	int fail;
	int failedInFirst15Rounds;
	int above105counter;
	void init(){
		total = success = neutral = fail = failedInFirst15Rounds = above105counter = 0;
	}
	void print(FILE* fp){
		int t = success+neutral+fail+failedInFirst15Rounds;
		int f = neutral + fail + failedInFirst15Rounds;
		fprintf(fp, "%3d:  %6d %6d %6d %6d %6d %6d  %.4g %.4g %.4g   %d\n", index, t, total, success, neutral, fail, failedInFirst15Rounds,
				(double)f/t, (double)neutral/t, (double)success/t, above105counter);
	}
};

struct ModSpec{
	bool (*functionName0 )(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg);
	bool (*functionName1)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg);
	bool (*functionName2 )(SHA1& ref, u32 xorDiff1, u32 xorDiff2,   ReducedSha& baseMsg);
	bool (*functionName3 )(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg);
	u32 xorDiff1;
	u32 xorDiff2;
	u32 xorDiff3;
	bool wOrState1;
	bool wOrState2;
	bool used;
	int conformTo;
	int type;
	int modIndex;
	ModStat stat;
	void init(){
		functionName0  = NULL;
		functionName1 = NULL;
		functionName2  = NULL;
		functionName3  = NULL;
		xorDiff1 = xorDiff2 = xorDiff3 = 0;
		wOrState1 = wOrState2 = false;
		used = false;
		type = 0;
		stat.init();
	}
	int read_spec(FILE* fp){
		char wOrS1[10] = "";
		char* pwOrS1 = wOrS1;
		char wOrS2[10] = "";
		char* pwOrS2 = wOrS2;
		char f0[10]  = "";
		char* pf0  = f0;
		char f1[10] = "";
		char* pf1  = f1;
		char f2[10]  = "";
		char* pf2  = f2;
		char f3[10]  = "";
		char* pf3  = f3;
		if(10!=fscanf(fp, "%s %s %s %s %x %x %x %s %s %d\n",
				pf0, pf1, pf2, pf3, &xorDiff1, &xorDiff2, &xorDiff3, pwOrS1, pwOrS2, &type))
			return 0;
		if(!strcmp(     f0, "mod_5"))   functionName0 = mod_5;
		else if(!strcmp(f0, "mod_6"))   functionName0 = mod_6;
		else if(!strcmp(f0, "mod_7"))   functionName0 = mod_7;
		//		else if(!strcmp(f0, "mod_8"))   functionName0 = mod_8;
		else if(!strcmp(f0, "mod_9"))   functionName0 = mod_9;
		else if(!strcmp(f0, "mod_9_op"))functionName0 = mod_9_op;
		else if(!strcmp(f0, "mod_9_14"))functionName0 = mod_9_14;
		else if(!strcmp(f0, "mod_10"))  functionName0 = mod_10;
		else if(!strcmp(f0, "mod_11"))  functionName0 = mod_11;
		else if(!strcmp(f0, "mod_12"))  functionName0 = mod_12;
		else if(!strcmp(f0, "mod_13"))  functionName0 = mod_13;
		else if(!strcmp(f0, "mod_14"))  functionName0 = mod_14;
		else if(!strcmp(f0, "mod_15"))  functionName0 = mod_15;
		else functionName0 = NULL;

		if(!strcmp(     f1, "mod_5"))   functionName1 = mod_5;
		else if(!strcmp(f1, "mod_6"))   functionName1 = mod_6;
		else if(!strcmp(f1, "mod_7"))   functionName1 = mod_7;
		//		else if(!strcmp(f01, "mod_8"))   functionName01 = mod_8;
		else if(!strcmp(f1, "mod_9"))   functionName1 = mod_9;
		else if(!strcmp(f1, "mod_9_op"))functionName1 = mod_9_op;
		else if(!strcmp(f1, "mod_9_14"))functionName1 = mod_9_14;
		else if(!strcmp(f1, "mod_10"))  functionName1 = mod_10;
		else if(!strcmp(f1, "mod_11"))  functionName1 = mod_11;
		else if(!strcmp(f1, "mod_12"))  functionName1 = mod_12;
		else if(!strcmp(f1, "mod_13"))  functionName1 = mod_13;
		else if(!strcmp(f1, "mod_14"))  functionName1 = mod_14;
		else if(!strcmp(f1, "mod_15"))  functionName1 = mod_15;
		else functionName1 = NULL;

		if(!strcmp(     f2, "mod_5_6"))  functionName2 = mod_5_6;
		else functionName2 = NULL;

		if(!strcmp(     f3, "mod_7_12"))   functionName3 = mod_7_12;
		else if(!strcmp(f3, "mod_7_15"))   functionName3 = mod_7_15;
		else if(!strcmp(f3, "mod_9_14"))   functionName3 = mod_9_14;
		else if(!strcmp(f3, "mod_11_14"))  functionName3 = mod_11_14;
		else if(!strcmp(f3, "mod_8_11"))   functionName3 = mod_8_11;
		else if(!strcmp(f3, "mod_10_13"))   functionName3 = mod_10_13;
		else functionName3 = NULL;

		wOrState1 = (!strcmp(wOrS1, "true")) ? true : false;
		wOrState2 = (!strcmp(wOrS2, "true")) ? true : false;
		//		used =      (!strcmp(u,     "true")) ? true : false;
		return 1;
	}
	void print_spec(FILE* fp){
		if(     functionName0 == mod_5 )fprintf(fp,       " mod_5     ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_6 )fprintf(fp,        " mod_6     ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_7 )fprintf(fp,        " mod_7     ");
		//		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_8 )fprintf(fp,        " mod_8     ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_9 )fprintf(fp,        " mod_9     ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_9_op )fprintf(fp,     " mod_9_op  ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_9_14 )fprintf(fp,     " mod_9_14  ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_10 )fprintf(fp,       " mod_10    ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_11 )fprintf(fp,       " mod_11    ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_12 )fprintf(fp,       " mod_12    ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_13 )fprintf(fp,       " mod_13    ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_14 )fprintf(fp,       " mod_14    ");
		else if(functionName0 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_15 )fprintf(fp,       " mod_15    ");
		else fprintf(fp, " NULL      ");

		if(     functionName1 == mod_5 )fprintf(fp,       " mod_5    ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_6 )fprintf(fp,        " mod_6     ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_7 )fprintf(fp,        " mod_7     ");
		//		else if(functionName01 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_8 )fprintf(fp,        " mod_8     ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_9 )fprintf(fp,        " mod_9     ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_9_op )fprintf(fp,     " mod_9_op  ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_9_14 )fprintf(fp,     " mod_9_14  ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_10 )fprintf(fp,       " mod_10    ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_11 )fprintf(fp,       " mod_11    ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_12 )fprintf(fp,       " mod_12    ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_13 )fprintf(fp,       " mod_13    ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_14 )fprintf(fp,       " mod_14    ");
		else if(functionName1 == (bool(*)(SHA1& ref, u32 xorDiff1, bool wOrState1, ReducedSha& baseMsg))mod_15 )fprintf(fp,       " mod_15    ");
		else fprintf(fp, " NULL      ");

		if(functionName2 == mod_5_6)fprintf(fp, " mod_5_6   ");
		else fprintf(fp, " NULL      ");


		if(functionName3 == (bool (*)(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg))mod_7_12)fprintf(fp,      " mod_7_12  ");
		else if(functionName3 == (bool (*)(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg))mod_7_15)fprintf(fp, " mod_7_15  ");
		else if(functionName3 == (bool (*)(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg))mod_9_14)fprintf(fp, " mod_9_14  ");
		else if(functionName3 == mod_11_14)fprintf(fp," mod_11_14 ");
		else if(functionName3 == mod_8_11)fprintf(fp, " mod_8_11  ");
		else if(functionName3 == (bool (*)(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg))mod_10_13)fprintf(fp, " mod_10_13  ");
		else fprintf(fp, " NULL      ");

		fprintf(fp, "%9x ", xorDiff1);
		fprintf(fp, "%9x ", xorDiff2);
		fprintf(fp, "%9x ", xorDiff3);

		if(wOrState1)fprintf(fp," true  ");else fprintf(fp," false ");
		if(wOrState2)fprintf(fp," true  ");else fprintf(fp," false ");
		//		if(used)fprintf(fp," true  ");else fprintf(fp," false ");

		fprintf(fp, "%d\n", type);
	}
	int isEqual(ModSpec& s){
		if(functionName0  != s.functionName0) return 1;
		if(functionName1 != s.functionName1) return 2;
		if(functionName2  != s.functionName2) return 3;
		if(functionName3  != s.functionName3) return 4;
		if(xorDiff1       != s.xorDiff1) {fprintf(stderr, "xorDiff1: %x %x\n", xorDiff1,  s.xorDiff1);return 5;}
		if(xorDiff2       != s.xorDiff2) {fprintf(stderr, "xorDiff2: %x %x\n", xorDiff2,  s.xorDiff2);return 6;}
		if(xorDiff3       != s.xorDiff3) {fprintf(stderr, "xorDiff3: %x %x\n", xorDiff3,  s.xorDiff3);return 7;}
		if(wOrState1      != s.wOrState1){fprintf(stderr, "wOrState1:%d %d\n", wOrState1, s.wOrState1);return 8;}
		if(wOrState2      != s.wOrState2){fprintf(stderr, "wOrState2:%d %d\n", wOrState2, s.wOrState2);return 9;}
		//		if(used           != s.used) {fprintf(stderr, "used: %d %d\n", used, s.used);return 10;}
		if(type           != s.type) {fprintf(stderr, "type: %d %d\n", type, s.type);return 11;}
		return 0;
	}

	bool check_conformance(int conformanceOfModifiedMsg, int firstUnSatisfied, int weightOfModifiedMsg, int weight){
		if(firstUnSatisfied < 90){
			if(conformanceOfModifiedMsg > firstUnSatisfied){
				++(stat.success);
				return true;
			}
			else{
				if(conformanceOfModifiedMsg == firstUnSatisfied){
					++(stat.neutral);
				}
				else{
					++(stat.fail);
				}
				return false;
			}
		}
		else{
			if(conformanceOfModifiedMsg < 90){
				++(stat.fail);
				return false;
			}
			else if(conformanceOfModifiedMsg < 106){
				if((conformanceOfModifiedMsg > firstUnSatisfied) || (weightOfModifiedMsg < weight)){
					++(stat.success);
					return true;
				}
				else if(((conformanceOfModifiedMsg < firstUnSatisfied) && (weightOfModifiedMsg  == weight)) ||
						((conformanceOfModifiedMsg == firstUnSatisfied) && (weightOfModifiedMsg  > weight)) ||
						((conformanceOfModifiedMsg == firstUnSatisfied) && (weightOfModifiedMsg == weight))){
					++(stat.neutral);
					return false;
				}
				else{
					++(stat.fail);
					return false;
				}
			}
			else{
				++(stat.success);
				return true;
			}
		}
		return false;
	}

	bool solve(SHA1& ref, ReducedSha& baseMsg, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg){
		int restoreFromRound = 5;
		++(stat.total);
		switch(type){
		case 0:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)) {
				++(stat.failedInFirst15Rounds);
				return false;
			}
			break;
		case 1:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)){
				++(stat.failedInFirst15Rounds);
				return false;
			}
			break;
		case 2:
			if(!functionName3(ref, xorDiff1, wOrState1, xorDiff2, wOrState2, baseMsg)){
				++(stat.failedInFirst15Rounds);
				return false;
			}
			break;
		case 3:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)){
				++(stat.failedInFirst15Rounds);
				return false;
			}
			if(!functionName1(ref, xorDiff2, wOrState2, baseMsg)){
				++(stat.failedInFirst15Rounds);
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		case 4:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)) {
				++(stat.failedInFirst15Rounds);
				return false;
			}
			if(!functionName0(ref, xorDiff3, wOrState1, baseMsg)) {
				++(stat.failedInFirst15Rounds);
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		default:
			break;
		}

		int conformanceOfModifiedMsg = updateAndTest(ref);
		int weightOfModifiedMsg = ref.mWindowWeight;
		if(check_conformance(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg, weightOfModifiedMsg, weightOfOriginalMsg)){
//			fprintf(stderr,"a  ");
			++(stat.success);
			return true;
		}

		ReducedSha intermediate;
		intermediate.copy(ref, 5, 15);
		if(conformanceOfModifiedMsg < 92){
			if(second_correction_nb(ref, intermediate, firstUnSatisfiedOriginalMsg, conformanceOfModifiedMsg, weightOfOriginalMsg, modIndex, restoreFromRound)){
//				fprintf(stderr,"c  ");
				++(stat.success);
				return true;
			}
		}

		m.restore(ref, 5, 15);
		return false;
	}

	bool solve(SHA1& ref, ReducedSha& baseMsg, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg, ModStat& statNB){
		int restoreFromRound = 5;
		++(statNB.total);
		switch(type){
		case 0:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)) {
				++(statNB.failedInFirst15Rounds);
				return false;
			}
			break;
		case 1:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)){
				++(statNB.failedInFirst15Rounds);
				return false;
			}
			break;
		case 2:
			if(!functionName3(ref, xorDiff1, wOrState1, xorDiff2, wOrState2, baseMsg)){
				++(statNB.failedInFirst15Rounds);
				return false;
			}
			break;
		case 3:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)){
				++(statNB.failedInFirst15Rounds);
				return false;
			}
			if(!functionName1(ref, xorDiff2, wOrState2, baseMsg)){
				++(statNB.failedInFirst15Rounds);
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		case 4:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)) {
				++(statNB.failedInFirst15Rounds);
				return false;
			}
			if(!functionName0(ref, xorDiff3, wOrState1, baseMsg)) {
				++(statNB.failedInFirst15Rounds);
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		default:
			break;
		}

		int conformanceOfModifiedMsg = updateAndTest(ref);
		int weightOfModifiedMsg = ref.mWindowWeight;
		if(check_conformance(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg, weightOfModifiedMsg, weightOfOriginalMsg)){
			++(statNB.success);
			return true;
		}

		ReducedSha intermediate;
		intermediate.copy(ref, 5, 15);
		if(conformanceOfModifiedMsg < 92){
			if(second_correction_nb(ref, intermediate, firstUnSatisfiedOriginalMsg, conformanceOfModifiedMsg, weightOfOriginalMsg, modIndex, restoreFromRound)){
				++(statNB.success);
				return true;
			}
		}

		++(statNB.fail);
		m.restore(ref, 5, 15);
		return false;
	}

	bool check_conformance_upto89(int conformanceOfModifiedMsg, int firstUnSatisfied){
		if(conformanceOfModifiedMsg > firstUnSatisfied){return true;}
		return false;
	}

	bool solve_upto89(SHA1& ref, ReducedSha& baseMsg, int firstUnSatisfiedOriginalMsg, ModStat *stat89, int corrIdx){
		++(stat89[corrIdx].total);
		switch(type){
		case 0:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)) {
				++(stat89[corrIdx].failedInFirst15Rounds);
				return false;
			}
			break;
		case 1:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)){
				++(stat89[corrIdx].failedInFirst15Rounds);
				return false;
			}
			break;
		case 2:
			if(!functionName3(ref, xorDiff1, wOrState1, xorDiff2, wOrState2, baseMsg)){
				++(stat89[corrIdx].failedInFirst15Rounds);
				return false;
			}
			break;
		case 3:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)){
				++(stat89[corrIdx].failedInFirst15Rounds);
				return false;
			}
			if(!functionName1(ref, xorDiff2, wOrState2, baseMsg)){
				++(stat89[corrIdx].failedInFirst15Rounds);
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		case 4:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)) {
				++(stat89[corrIdx].failedInFirst15Rounds);
				return false;
			}
			if(!functionName0(ref, xorDiff3, wOrState1, baseMsg)) {
				++(stat89[corrIdx].failedInFirst15Rounds);
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		default:
			break;
		}

		int conformanceOfModifiedMsg = updateAndTest(ref);
		if(check_conformance_upto89(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg)){
			++(stat89[corrIdx].success);
			return true;
		}

		ReducedSha intermediate;
		intermediate.copy(ref, 5, 15);
		if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 14)){
			++(stat89[corrIdx].success);
			return true;
		}
		++(stat89[corrIdx].fail);
		m.restore(ref, 5, 15);
		return false;
	}

	bool solve_upto89(SHA1& ref, ReducedSha& baseMsg, int firstUnSatisfiedOriginalMsg){
		switch(type){
		case 0:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)) {
				return false;
			}
			break;
		case 1:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)){
				return false;
			}
			break;
		case 2:
			if(!functionName3(ref, xorDiff1, wOrState1, xorDiff2, wOrState2, baseMsg)){
				return false;
			}
			break;
		case 3:
			if(!functionName0(ref, xorDiff1, wOrState1, baseMsg)){
				return false;
			}
			if(!functionName1(ref, xorDiff2, wOrState2, baseMsg)){
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		case 4:
			if(!functionName2(ref, xorDiff1, xorDiff2, baseMsg)) {
				return false;
			}
			if(!functionName0(ref, xorDiff3, wOrState1, baseMsg)) {
				baseMsg.restore(ref, 5, 15);
				return false;
			}
			break;
		default:
			break;
		}

		int conformanceOfModifiedMsg = updateAndTest(ref);
		if(check_conformance_upto89(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg)){return true;}

		ReducedSha intermediate;
		intermediate.copy(ref, 5, 15);
		if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 14))return true;
		m.restore(ref, 5, 15);
		return false;
	}

};


extern ModSpec *NB;

#endif /* ROUNDS_90_105_H_ */
