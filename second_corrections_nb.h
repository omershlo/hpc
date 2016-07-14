/*
 * second_corrections_nb.h
 *
 *  Created on: Jul 13, 2016
 *      Author: rc
 */

#ifndef SECOND_CORRECTIONS_NB_H_
#define SECOND_CORRECTIONS_NB_H_
#include "rounds_90_105.h"

bool corrAtRound15_nb(SHA1& ref, u32 d, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg, ModStat neutralBitsStat[], int modIdx)
{
	u32 w15 = ref.mW[15]; u32 a16 = ref.mA[16]; u32 a30_16 = ref.mA30[16];
	ref.mW[15] += d;
	if((ref.mW[15] ^ m.w[15]) & mM[R15]){ref.mW[15] -= d; return false;}
	ref.mA[16] += d;
	if((ref.mA[16] ^ m.a[16]) & 0x28000001){ref.mW[15] -= d;ref.mA[16] -= d;return false;}
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	int conformanceOfModifiedMsg = updateAndTest(ref);
	if(conformanceOfModifiedMsg > 89){
		int weightOfModifiedMsg = ref.mWindowWeight;
		if(check_conformance_90_105(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg, weightOfModifiedMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)){
			return true;
		}
	}
	else{
		return false;
	}
	ref.mW[15] = w15; ref.mA[16] = a16; ref.mA30[16] = a30_16;
	return false;
}

// 5, 6, 56, 568, 8, 68, 58
bool allCorrectionsRound15_nb(SHA1& ref, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg, ModStat neutralBitsStat[], int modIdx,
		bool (*corrAtRound15_nb)(SHA1& ref, u32 d, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg, ModStat neutralBitsStat[], int modIdx))
{
	u32 d;
	u32 a20 = ref.mA[20];
	//	u32 a20 = m.a[20];
	u32 d8 = (a20 & B28) ? MB8 : B8;
	if(corrAtRound15_nb(ref, d8, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	u32 d6 = (a20 & B26) ? MB6 : B6;
	if(corrAtRound15_nb(ref, d6, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	u32 d5 = (a20 & B25) ? MB5 : B5;
	if(corrAtRound15_nb(ref, d5, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	d = d5 + d6;
	if(corrAtRound15_nb(ref, d, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	d = d5 + d6 + d8;
	if(corrAtRound15_nb(ref, d, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	d = d5 + d8;
	if(corrAtRound15_nb(ref, d, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	d = d6 + d8;
	if(corrAtRound15_nb(ref, d, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx))return true;
	return false;
}

bool updateAndTestConformance_nb(SHA1& ref, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg, ModStat neutralBitsStat[], int modIdx){
	int conformanceOfModifiedMsg = updateAndTest(ref);
	if(conformanceOfModifiedMsg > 89){
		int weightOfModifiedMsg = ref.mWindowWeight;
		if(check_conformance_90_105(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg, weightOfModifiedMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)){
			return true;
		}
	}
	else{
		return false;
	}
	return false;
}

inline bool c84nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFrom){
	if(allCorrectionsRound15_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, corrAtRound15_nb)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c85nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFrom){
	if(!mod_14(ref, B5, true, intermediate))//B6|B5:0.9 B5:1.3
	{
		goto c85_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c85_1:
	if(allCorrectionsRound15_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, corrAtRound15_nb)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c86nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFrom){
	if(!mod_14(ref, B5, true, intermediate))//1.3
	{
		goto c86_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c86_1:
	if(!mod_5(ref, B10, false, intermediate))//1.1
	{
		goto c86_2;
	}
	if(!mod_13(ref, B6, true, intermediate))
	{
		intermediate.restore(ref, 5, 15);
		goto c86_2;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c86_2:
	if(!mod_14(ref, B8, true, intermediate))//1.1
	{
		goto c86_4;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c86_4:
	if(allCorrectionsRound15_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, corrAtRound15_nb)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c87nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFrom){
	if(!mod_5(ref, B10, false, intermediate))//7.3
	{
		goto c87_0;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 10);
c87_0:
	if(!mod_5(ref, B9, false, intermediate))//2.3
	{
		goto c87_01;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 10);
c87_01:
	if(!mod_14(ref, B6, false, intermediate))//1.3
	{
		goto c87_10;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c87_10:
	if(!mod_5(ref, B10|B9, false, intermediate))//1.3
	{
		goto c87_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 10);
c87_1:
	if(!mod_5(ref, B10, false, intermediate))//1
	{
		goto c87_2;
	}
	if(!mod_13(ref, B6, true, intermediate))
	{
		intermediate.restore(ref, 5, 15);
		goto c87_2;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c87_2:
	if(allCorrectionsRound15_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, corrAtRound15_nb)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c88nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFrom){
	if(!mod_9(ref, B7, false, intermediate))//6.4
	{
		goto c88_0;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c88_0:
	if(!mod_9_op(ref, B7, false, intermediate))//6.4
	{
		goto c88_01;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c88_01:
	if(!mod_14(ref, B8, true, intermediate))//B8:2.2  B7:1.2
	{
		goto c88_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c88_1:
	if(!mod_14(ref, B7, true, intermediate))//2.2
	{
		goto c88_2;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c88_2:
	if(!mod_5(ref, B10, false, intermediate))//1.1
	{
		goto c88_5;
	}
	if(!mod_13(ref, B6, true, intermediate))
	{
		intermediate.restore(ref, 5, 15);
		goto c88_5;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c88_5:
	if(!mod_7_15(ref, B8, false, B29, false, intermediate))//1.6%
	{
		goto c88_7;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 7, 15);
c88_7:
	if(allCorrectionsRound15_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, corrAtRound15_nb)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}


inline bool c89nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFrom){
	int roundToStart = 16;
	if(!mod_6(ref, B7, intermediate, roundToStart))//17%
	{
		goto c89_00;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 6, 11);
c89_00:
	if(!mod_6(ref, B8, intermediate, roundToStart))//5%
	{
		goto c89_01;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 6, 11);
c89_01:
	if(!mod_14(ref, B8, true, intermediate))//2.4%
	{
		goto c89_10;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c89_10:
	if(!mod_14(ref, B5, true, intermediate))//2.6
	{
		goto c89_4;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c89_4:
	if(!mod_14(ref, B7, true, intermediate))//2.7%
	{
		goto c89_5;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 14, 15);
c89_5:
	if(!mod_7_15(ref, B8, false, B29, false, intermediate))//2.1
	{
		goto c89_6;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 7, 15);
c89_6:
	if(!mod_6(ref, B8|B7, intermediate, roundToStart))//2.1
	{
		goto c89_9;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 6, 15);
c89_9:
	if(!mod_5(ref, B10, false, intermediate))//1.7
	{
		goto c89_a;
	}
	if(!mod_13(ref, B6, true, intermediate))
	{
		intermediate.restore(ref, 5, 15);
		goto c89_a;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref, 5, 15);
c89_a:
	if(!mod_14(ref, B8|B7, true, intermediate))//1.4%
	{
		goto c89_b;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref,14, 15);
c89_b:
	if(!mod_13(ref, B6, false, intermediate))
	{
		goto c89_c;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx)) return true;;
	intermediate.restore(ref,13, 15);
c89_c:
	if(allCorrectionsRound15_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, corrAtRound15_nb)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool second_correction_nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int conformanceOfModifiedMsg, int weightOfOriginalMsg,
		ModStat neutralBitsStat[], int modIdx, int restoreFromRound){
	switch (conformanceOfModifiedMsg) {
//	case 84:
//		if(c84nb(ref, equToCorrect, restoreFromRound))return true;
//		return false;
//		break;
//	case 85:
//		if(c85nb(ref, intermediate, equToCorrect, restoreFromRound))return true;
//		return false;
//		break;
//	case 86:
//		if(c86nb(ref, intermediate, equToCorrect, restoreFromRound))return true;
//		return false;
//		break;
//	case 87:
//		if(c87nb(ref, intermediate, equToCorrect, restoreFromRound))return true;
//		return false;
//		break;
//	case 88:
//		if(c88nb(ref, intermediate, equToCorrect, restoreFromRound))return true;
//		return false;
//		break;
	case 89:
		if(c89nb(ref, intermediate, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, neutralBitsStat, modIdx, restoreFromRound))return true;
		return false;
		break;
	default:
		break;
	}
	return false;
}


#endif /* SECOND_CORRECTIONS_NB_H_ */
