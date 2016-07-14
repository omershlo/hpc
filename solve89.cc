/*
 * solve89.cc
 *
 *  Created on: May 15, 2016
 *      Author: rc
 */
#include "solve.h"
#include "second_corrections.h"
//#define PROB
#ifdef PROB
static int fail, total;
#endif


bool c_solve89_5(SHA1& ref, u32 xorDiff5, bool wOrState5, ReducedSha& baseMsg){
	if(!mod_5(ref, xorDiff5, wOrState5, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_5_6(SHA1& ref, u32 xorDiff1, u32 xorDiff2, ReducedSha& baseMsg){
	if(!mod_5_6(ref, xorDiff1, xorDiff2, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_5_6_13(SHA1& ref, u32 xorDiff5, u32 xorDiff6, u32 xorDiff13, bool wOrState13, ReducedSha& baseMsg){
	if(!mod_5_6(ref, xorDiff5, xorDiff6, baseMsg)) return false;
	if(!mod_13(ref, xorDiff13, wOrState13, baseMsg)){baseMsg.restore(ref, 5, 11); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_5_10(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg){
	if(!mod_5(ref, xorDiff1, wOrState1, baseMsg)) {
		return false;
	}
	if(!mod_10(ref, xorDiff2, wOrState2, baseMsg)) {
		baseMsg.restore(ref, 5, 10);
		return false;
	}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_5_13(SHA1& ref, u32 xorDiff1, bool wOrState1, u32 xorDiff2, bool wOrState2, ReducedSha& baseMsg){
	if(!mod_5(ref, xorDiff1, wOrState1, baseMsg)) return false;
	if(!mod_13(ref, xorDiff2, wOrState2, baseMsg)) {baseMsg.restore(ref, 5, 10); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_5_14(SHA1& ref, u32 xorDiff5, bool wOrState5, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg){
	if(!mod_5(ref, xorDiff5, wOrState5, baseMsg)) return false;
	if(!mod_14(ref, xorDiff14, wOrState14, baseMsg)) {baseMsg.restore(ref, 5, 10); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 5))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_5_15(SHA1& ref, u32 xorDiff5, bool wOrState5, u32 a20XorDiff, ReducedSha& baseMsg){
	if(!mod_5(ref, xorDiff5, wOrState5, baseMsg)) return false;
	if(!mod_15(ref, a20XorDiff, false, baseMsg)) {baseMsg.restore(ref, 5, 10); return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 6))return true;
	m.restore(ref, 5, 15);
	return false;
}

// mA[8] & B6 = 0
// mA[9] & B6 = 1

bool c_solve89_6(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg){
	int roundToStart;
	if(!mod_6(ref, xorDiff, baseMsg, roundToStart)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 6))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_6_10(SHA1& ref, u32 xorDiff6, u32 xorDiff10, bool wOrState10, ReducedSha& baseMsg){
	if(!mod_6_10(ref, xorDiff6, xorDiff10, wOrState10, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 6))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_6_13(SHA1& ref, u32 xorDiff6, u32 xorDiff13, bool wOrState13, ReducedSha& baseMsg){
	if(!mod_6( ref, xorDiff6 , false,      baseMsg)) return false;
	if(!mod_13(ref, xorDiff13, wOrState13, baseMsg)) {baseMsg.restore(ref, 6, 11);return false;}

	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 6))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_6_14(SHA1& ref, u32 xorDiff6, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg){
	if(!mod_6(ref, xorDiff6, false, baseMsg)) return false;
	if(!mod_14(ref, xorDiff14, wOrState14, baseMsg)) {baseMsg.restore(ref, 6, 11);baseMsg.restore(ref, 14, 15);return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 6))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_7_12(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 xorDiff12, bool wOrState12, ReducedSha& baseMsg){
	if(!mod_7_12(ref, xorDiff7, wOrState7, xorDiff12, wOrState12, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 7))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_7_15(SHA1& ref, u32 xorDiff, bool wOrState, u32 a20XorDiff, ReducedSha& baseMsg){
	if(!mod_7(ref, xorDiff, wOrState, baseMsg)){return false;}
	if(!mod_15(ref, a20XorDiff, false, baseMsg)){baseMsg.restore(ref, 7, 12);return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 7))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_7_15_v1(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 a20XorDiff, ReducedSha& baseMsg){
	if(!mod_7_15(ref, xorDiff7, wOrState7, a20XorDiff, false, baseMsg)){return false;}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 7))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_8_11(SHA1& ref, u32 xorDiff8, bool wOrState8, u32 xorDiff11, bool wOrState11, ReducedSha& baseMsg){
	if(!mod_8_11(ref, xorDiff8, wOrState8, xorDiff11, wOrState11, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	//if(updateAndTestConformance(ref, 88, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 8))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_9(SHA1& ref, u32 xorDiff9, bool wOrState9, ReducedSha& baseMsg){
	if(!mod_9(ref, xorDiff9, wOrState9, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 9))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_9_op(SHA1& ref, u32 xorDiff9, ReducedSha& baseMsg){
	if(!mod_9_op(ref, xorDiff9, false, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 9))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_9_14(SHA1& ref, u32 xorDiff9, bool wOrState9, u32 xorDiff14, u32 wOrState14, ReducedSha& baseMsg){
	if(!mod_9_14(ref, xorDiff9, wOrState9, xorDiff14, wOrState14, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 9))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_10(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg){
	if(!mod_10(ref, xorDiff, wOrState, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 10))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_10_13(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 xorDiff13, bool wOrState13, ReducedSha& baseMsg){
	if(!mod_10_13(ref, xorDiff10, wOrState10, xorDiff13, wOrState13, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 10))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_10_15(SHA1& ref, u32 xorDiff, bool wOrState, u32 a20XorDiff, ReducedSha& baseMsg){
	if(!mod_10_15(ref, xorDiff, wOrState, a20XorDiff, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 10))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_11(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg){
	if(!mod_11(ref, xorDiff, wOrState, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 11))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_11_14(SHA1& ref, u32 xorDiff11, bool wOrState11, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg){
	if(!mod_11_14(ref, xorDiff11, wOrState11, xorDiff14, wOrState14, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 11))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_13(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg){
	if(!mod_13(ref, xorDiff, wOrState, baseMsg)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 13))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_14(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg){
	if(!mod_14(ref, xorDiff, wOrState, baseMsg)){
		return false;
	}
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 14))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_15(SHA1& ref, u32 a20XorDiff, ReducedSha& baseMsg){
	if(!mod_15(ref, a20XorDiff, false, baseMsg)) return false;

	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 15))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool c_solve89_13_15(SHA1& ref, u32 xorDiff13, bool wOrState13, u32 a20XorDiff){
	if(!mod_13_15(ref, xorDiff13, wOrState13, a20XorDiff, m)) return false;
	int conformanceOfModifiedMsg = 0;
	if(updateAndTestConformance(ref, 89, conformanceOfModifiedMsg)) return true;;
	ReducedSha intermediate;
	intermediate.copy(ref, 5, 15);
	if(second_correction(ref, intermediate, conformanceOfModifiedMsg, 89, 13))return true;
	m.restore(ref, 5, 15);
	return false;
}

bool SHA1::solve89(){
#ifdef PROB
	total++;
#endif
	if(!((mA[6]^mA[5]) & B9) && !(mA[8] & B5) && (mA[9] & B5))
	{
		if(modifyAndUpdate_6(*this, B7, m) > 89){return true;}
		m.restore(*this, 6, 11);
	}
	if((!((mA[6]^mA[5]) & B10)) && !(mA[8] & B6))
	{
		if(modifyAndUpdate_6_bit8(*this, B8, m) > 89){return true;}
		m.restore(*this, 6, 11);
//		m.restore(*this, 18, 18);
	}
	//19
	if(c_solve89_14(*this, B5, false, m)){return true;}
	//10
	if(c_solve89_5_6(*this, B10, B8, m)){return true;}
	//9
	if(c_solve89_5_6(*this, B9, B7, m)){return true;}
	//8
	if(c_solve89_14(*this, B7, false, m)){return true;}
	//7
	if(c_solve89_5_6(*this, B9, B8, m)){return true;}
	if(c_solve89_14(*this, B6, false, m)){return true;}
	if(c_solve89_5_6(*this, B10|B9, B8, m)){return true;}//t
	if(c_solve89_9_14(*this, B8, false, B5, false, m)){return true;}
	if(c_solve89_5_13(*this, B10|B9, false, B6, true, m)){return true;}
	//6
	if(c_solve89_6_13(*this, B7, B6, true, m)){return true;}
	if(c_solve89_7_15(*this, B7, false, B28, m)){return true;}
	//5
	if(c_solve89_15(*this, B25, m)) {return true;}
	if(c_solve89_13(*this, B6, false, m)){return true;}

	if(c_solve89_5_10(*this, B10, false, B10, true, m)){return true;}

	if(c_solve89_5_6(*this, B10|B9, B7, m)){return true;}
	if(c_solve89_5_6(*this, B10, B7, m)){return true;}
	if(c_solve89_7_15_v1(*this, B7, false, B28, m)){return true;}
	//4.0
	if(c_solve89_7_15_v1(*this, B8, false, B29, m)){return true;}
	if(c_solve89_7_12(*this, B7, false, B7, true, m)){return true;}
	if(c_solve89_5(*this, B9, false, m)){return true;}
	if(c_solve89_9_op(*this, B8, m)){return true;}
	if(c_solve89_9(*this, B8, false, m)){return true;}
	//3
	if(c_solve89_6_13(*this, B8|B7, B6, true, m)){return true;}
	if(c_solve89_11_14(*this, B7, true, B5, false, m)){return true;}
	if(!(mA[13] & B4) && c_solve89_11(*this, B6, false, m)){return true;}
	if(c_solve89_6_14(*this, B7, B8, true, m)){return true;}
	if(c_solve89_6_14(*this, B7, B5, true, m)){return true;}
	if(c_solve89_13(*this, B8, false, m)){return true;}
	if(c_solve89_14(*this, B6|B5, false, m)){return true;}
	if(c_solve89_14(*this, B8, false, m)){return true;}
	if(c_solve89_13(*this, B5, true, m)){return true;}
	if(c_solve89_10_13(*this, B8, false, B5, true, m)){return true;}
	//2.5
	if(c_solve89_5_13(*this, B9, false, B6, true, m)){return true;}
	if(c_solve89_5_6_13(*this, B10, B8, B6, false, m)){return true;}//t
	if(c_solve89_5_6(*this, B10|B9, B8|B7, m)){return true;}
	if(c_solve89_10(*this, B8, false, m)){return true;}
	if(c_solve89_8_11(*this, B8, false, B9, true, m)){return true;}
	if(c_solve89_6_14(*this, B7, B7, true, m)){return true;}
	if(c_solve89_5_14(*this, B9, false, B5, true, m)){return true;}
	if(c_solve89_5_14(*this, B10, false, B6, true, m)){return true;}
	if(c_solve89_9_op(*this, B7, m)){return true;}
	if(c_solve89_6_13(*this, B8, B6, true, m)){return true;}
	if(c_solve89_5(*this, B10|B9, false, m)){return true;}
	if(c_solve89_9(*this, B7, false, m)){return true;}
	if(c_solve89_10_13(*this, B8, false, B6|B5, true, m)){return true;}
	if(c_solve89_13_15(*this, B8, false, B25))return true;

	//1.6
	if((!((mA[13] ^ mA[12]) & B6)) && c_solve89_13(*this, B4, false, m)){return true;}
	if(c_solve89_5_6_13(*this, B9, B7, B6, false, m)){return true;}

#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	m.restore(*this, 5, 20);
	return false;
}
