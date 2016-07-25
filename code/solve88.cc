/*
 * solve88.cc
 *
 *  Created on: May 2, 2016
 *      Author: rc
 */
#include "solve.h"
#include "second_corrections.h"

//#define PROB
#ifdef PROB
static int fail, total;
#endif
bool CorrectionsRound15_5(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int equToTest), int equationToTest)
{
	u32 d;
	u32 a20 = ref.mA[20];
	//	u32 a20 = m.a[20];
	u32 d8 = (a20 & B28) ? MB8 : B8;
	if(corrAtRound15(ref, d8, equationToTest))return true;
	u32 d6 = (a20 & B26) ? MB6 : B6;
	if(corrAtRound15(ref, d6, equationToTest))return true;
	u32 d5 = (a20 & B25) ? MB5 : B5;
	if(corrAtRound15(ref, d5, equationToTest))return true;
	d = d5 + d6;
	if(corrAtRound15(ref, d, equationToTest))return true;
	d = d5 + d6 + d8;
	if(corrAtRound15(ref, d, equationToTest))return true;
	d = d5 + d8;
	if(corrAtRound15(ref, d, equationToTest))return true;
	d = d6 + d8;
	if(corrAtRound15(ref, d, equationToTest))return true;
	return false;
}

bool c_solve88_9_op(SHA1& ref, u32 xorDiff){
	if(!mod_9_op(ref, xorDiff, false, m)){//14%
		return false;
	}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 9))return true;
	m.restore(ref, 5, 15);
	return false;
}



bool c_solve88_9(SHA1& ref, u32 xorDiff){
	if(!mod_9(ref, xorDiff, false, m)){//14%
		return false;
	}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 9))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_5_10(SHA1& ref, u32 xorDiff1, bool wOrState1){
	if(!mod_5_10(ref, xorDiff1, wOrState1, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_5_10(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2){
	if(!mod_5(ref, xorDiff1, wOrState1, m)) return false;
	if(!mod_10(ref, xorDiff2, wOrState2, m)) {m.restore(ref, 5, 10); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_5_14(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2){
	if(!mod_5(ref, xorDiff1, wOrState1, m)) return false;
	if(!mod_14(ref, xorDiff2, wOrState2, m)) {m.restore(ref, 5, 10); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_5_13(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2){
	if(!mod_5(ref, xorDiff1, wOrState1, m)) return false;
	if(!mod_13(ref, xorDiff2, wOrState2, m)) {m.restore(ref, 5, 10); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_7_15(SHA1& ref, u32 xorDiff, bool wOrState){
	if(!mod_7(ref, xorDiff, wOrState, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 7))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_11(SHA1& ref, u32 xorDiff, bool wOrState){
	if(!mod_11(ref, xorDiff, wOrState, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 11))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_13(SHA1& ref, u32 xorDiff, bool wOrState){
	if(!mod_13(ref, xorDiff, wOrState, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 13))return true;
	m.restore(ref, 13, 15);
	return false;
}

bool c_solve88_14(SHA1& ref, u32 xorDiff, bool wOrState){
	if(!mod_14(ref, xorDiff, wOrState, m)){
		return false;
	}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 14))return true;	
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_7_15(SHA1& ref, u32 xorDiff, bool wOrState, u32 a20XorDiff, ReducedSha& baseMsg){
	if(!mod_7(ref, xorDiff, wOrState, baseMsg)){return false;}
	if(!mod_15(ref, a20XorDiff, false, baseMsg)){baseMsg.restore(ref, 7, 15);return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 7))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_7_15v1(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 a20XorDiff, bool wOrState, ReducedSha& baseMsg){
	if(!mod_7_15(ref, xorDiff7, wOrState7, a20XorDiff, wOrState, baseMsg)){return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 7))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_7_12_14(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, u32 xorDiff3, bool wOrState3){
	if(!mod_7(ref, xorDiff1, wOrState1, m)) return false;
	ReducedSha m7;
	m7.copy(ref, 12, 15);
	if(!mod_12(ref, xorDiff2, wOrState2, m7)) {m.restore(ref, 7, 12); return false;}
	ReducedSha m12;
	m12.copy(ref, 14, 15);
	if(!mod_14(ref, xorDiff3, wOrState3, m12)) {m.restore(ref, 7, 15);return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 7))return true;
	m.restore(ref, 7, 15);
	return false;
}

bool c_solve88_5_6(SHA1& ref, u32 xorDiff1, u32 xorDiff2){
	if(!mod_5_6(ref, xorDiff1, xorDiff2, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 5))return true;
	m.restore(ref, 5, 11);
	return false;
}

bool c_solve88_10(SHA1& ref, u32 xorDiff, bool wOrState){
	if(!mod_10(ref, xorDiff, wOrState, m)) {return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 10))return true;
	m.restore(ref, 10, 15);
	return false;
}

bool c_solve88_10_13(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 xorDiff13, bool wOrState13){
	if(!mod_10_13(ref, xorDiff10, wOrState10, xorDiff13, wOrState13, m)) {return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 10))return true;
	m.restore(ref, 10, 15);
	return false;
}

bool c_solve88_10_no_further_corr(SHA1& ref, u32 xorDiff, bool wOrState){
	if(!mod_10(ref, xorDiff, wOrState, m)) {return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	m.restore(ref, 10, 15);
	return false;
}

bool c_solve88_5_9_14(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2){
	if(!mod_5(ref, xorDiff1, wOrState1, m)) return false;
	if(!mod_9_14(ref, xorDiff2, false, m)){m.restore(ref, 5, 14); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve88_9_14(SHA1& ref, u32 xorDiff){
	if(!mod_9_14(ref, xorDiff, false, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 9))return true;
	m.restore(ref, 9, 15);
	return false;
}

bool c_solve88_9_14(SHA1& ref, u32 xorDiff1,u32 xorDiff2){
	if(!mod_9_14(ref, xorDiff1,xorDiff2, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 9))return true;
	m.restore(ref, 9, 15);
	return false;
}

bool c_solve88_9_13(SHA1& ref, u32 xorDiff1,u32 xorDiff2){
	if(!mod_9(ref, xorDiff1,false, m)) return false;
	if(!mod_13(ref, xorDiff2,false, m)) {m.restore(ref, 9, 14); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 9))return true;
	m.restore(ref, 9, 15);
	return false;
}

bool c_solve88_13_15(SHA1& ref, u32 xorDiff13, bool wOrState13, u32 a20XorDiff){
	if(!mod_13_15(ref, xorDiff13, wOrState13, a20XorDiff, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 88, 9))return true;
	m.restore(ref, 9, 15);
	return false;
}

bool SHA1::solve88(){
#ifdef PROB
	++total;
#endif
	//32

	if(((mA[12] & B5) == B5)){
		if(c_solve88_9(*this, B7)){return true;}
		if(c_solve88_9_op(*this, B7)){return true;}
	}
	//12
	if(c_solve88_5_6(*this, B10, B7)){return true;}//2.6
	//10
	if(c_solve88_14(*this, B8, true))return true;
	if(c_solve88_7_12_14(*this, B7, false, B7, true, B5, false))return true;
	if(c_solve88_14(*this, B5, true))return true;
	//8.5
	if(c_solve88_5_6(*this, B9, B7)){return true;}//2.6
	//7
	if(c_solve88_7_15(*this, B8, false, B29, m))return true;
	if(c_solve88_14(*this, B7, false))return true;
	if(c_solve88_5_6(*this, B10|B9, B7)){return true;}//2.6
	if(c_solve88_5_6(*this, B9, B8)){return true;}//2.6
	if(c_solve88_10(*this, B9, false))return true;//2.3
	if(c_solve88_10(*this, B7, false))return true;//2.3
	if(c_solve88_5_10(*this, B10, false, B9, false))return true;//2.2
	//4.5
	if(c_solve88_5_9_14(*this, B10, false, B7)) return true;//1.5
	if(c_solve88_5_10(*this, B9, false, B9, false))return true;//2.2
	if(c_solve88_14(*this, B6, false))return true;
	if(c_solve88_7_12_14(*this, B7, false, B7, true, B6|B5, false))return true;
	if(c_solve88_5_6(*this, B10, B8)){return true;}//2.6
	if(c_solve88_5_6(*this, B10|B9, B8)){return true;}//2.6
	if(c_solve88_10(*this, B10, false))return true;//2.3
	if(c_solve88_5_13(*this, B9, false, B6, true))return true;//4.2
	if(c_solve88_5_13(*this, B9, false, B5, true))return true;//4.5
	if(c_solve88_5_13(*this, B9, false, B7, true))return true;//4.8
	if(c_solve88_7_15(*this, B7, false)) return true;;
	if(c_solve88_10_13(*this, B8, false, B5, true)){return true;}
	//3
	if(c_solve88_5_14(*this, B9, false, B5, false))return true;
	if(c_solve88_7_15(*this, B8, false, B30|B29, m))return true;
	if(c_solve88_5_13(*this, B10, false, B8, true))return true;
	if(c_solve88_5_13(*this, B9, false, B7|B6, true))return true;//4.3
	if(c_solve88_5_9_14(*this, B9, false, B7)) return true;//1.5
	if(c_solve88_5_6(*this, B10|B9, B8|B7)){return true;}//2.6
	if(c_solve88_5_6(*this, B9, B8|B7)){return true;}//2.6
	if(c_solve88_5_10(*this, B10|B9, false, B9, false))return true;//2.2
	if(c_solve88_5_10(*this, B10, false, B7, false))return true;//2.2
	if(c_solve88_5_13(*this, B9, false, B9, true))return true;//4.8
	if(c_solve88_5_14(*this, B10, false, B5, false))return true;
	if(c_solve88_5_14(*this, B10|B9, false, B5, false))return true;
	if(c_solve88_5_14(*this, B10, false, B6, false))return true;
	if(c_solve88_9(*this, B8|B7))return true;
	if(c_solve88_11(*this, B7, true))return true;
	//2.3
	if(allCorrectionsRound15(*this, corrAtRound15, 88)) return true;
	if(c_solve88_10(*this, B8, false)) return true;
	if(c_solve88_5_10(*this, B10, false, B10, true))return true;//2.2
	if(c_solve88_5_9_14(*this, B10|B9, false, B7)) return true;//1.5
	if(c_solve88_5_6(*this, B10, B8|B7)){return true;}//2.6
	if(c_solve88_13_15(*this, B8, false, B25))return true;
	//2
	if(c_solve88_10_13(*this, B7, false, B5, true)){return true;}
	if(c_solve88_10_13(*this, B9|B8, false, B5, true)){return true;}
	if(c_solve88_10(*this, B9|B7, false))return true;//2.3
	if(c_solve88_14(*this, B6, true))return true;
	if(c_solve88_5_13(*this, B9, false, B6|B5, true))return true;//3.8
	if(c_solve88_5_13(*this, B10|B9, false, B6, true))return true;//4.2
	if(c_solve88_5_13(*this, B10|B9, false, B5, true))return true;//4.5
	if(c_solve88_5_13(*this, B10|B9, false, B7, true))return true;//4.8
	if(c_solve88_5_13(*this, B10|B9, false, B7|B6, true))return true;//4.3
	if(c_solve88_5_13(*this, B10|B9, false, B9, true))return true;//4.8
	if(c_solve88_5_13(*this, B10, false, B6, true))return true;//4.2
	if(c_solve88_5_13(*this, B10, false, B5, true))return true;//4.5
	if(c_solve88_5_13(*this, B10, false, B7, true))return true;//4.8
	if(c_solve88_5_13(*this, B10, false, B7|B6, true))return true;//4.3
	if(c_solve88_5_13(*this, B10, false, B9, true))return true;//4.8
	if(c_solve88_5_13(*this, B10|B9, false, B8, true))return true;
	if(c_solve88_5_13(*this, B9, false, B8, true))return true;
	if(c_solve88_5_13(*this, B10, false, B9|B8, true))return true;
	if(c_solve88_7_15(*this, B7, false, B29, m))return true;
	if(c_solve88_9_14(*this, B6))return true;//1.6
	if(c_solve88_9_14(*this, B7))return true;//1.6
	if(c_solve88_9_14(*this, B8|B7))return true;//1.6
	if(c_solve88_5_14(*this, B9, false, B6, false))return true;
	if(c_solve88_5_14(*this, B10|B9, false, B6, false))return true;
	if(c_solve88_5_14(*this, B10, false, B6|B5, false))return true;//x
	if(c_solve88_14(*this, B6|B5, true))return true;
	if(c_solve88_5_13(*this, B7, false, B5, true))return true;
	if(c_solve88_7_12_14(*this, B7, false, B7, true, B6, false))return true;
	if(c_solve88_5_13(*this, B9, false, B7|B8|B6, true))return true;
	if(c_solve88_11(*this, B8|B7, true))return true;
	if(c_solve88_9_14(*this, B7, B6))return true;
	if(c_solve88_7_15v1(*this, B7, false, B28, false, m))return true;
	if(c_solve88_7_15v1(*this, B8, false, B29, false, m))return true;
	if(c_solve88_5_13(*this, B7, false, B8, true))return true;//2.1

	if(c_solve88_7_12_14(*this, B7, false, B7, true, B7|B6, false))return true;//1.8
	if(c_solve88_5_10(*this, B10|B9, false))return true;//1.8
	if(c_solve88_10(*this, B8|B7, false)) return true;//1.7
	if(c_solve88_5_14(*this, B9, false, B6|B5, false))return true;//1.7
	if(c_solve88_9_14(*this, B9|B8))return true;//1.6
	if(c_solve88_5_13(*this, B7, false, B6|B5, true))return true;//1.6
	if(c_solve88_5_10(*this, B9, false))return true;//1.5
	if(c_solve88_5_14(*this, B10, false, B7, false))return true;//1.5
	if(c_solve88_5_9_14(*this, B10|B9, false, B8|B7)) return true;//1.5

#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	m.restore(*this, 5, 20);
	return false;
}
