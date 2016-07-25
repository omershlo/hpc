/*
 * second_corrections_nb.h
 *
 *  Created on: Jul 13, 2016
 *      Author: rc
 */

#ifndef SECOND_CORRECTIONS_NB_H_
#define SECOND_CORRECTIONS_NB_H_
//#include "mod_spec.h"
struct ModSpec;
//static int failNeutral, totalNeutral;
bool check_conformance_90_105(int conformanceOfModifiedMsg, int firstUnSatisfied, int weightOfModifiedMsg, int weight, int modIdx);


inline bool updateAndTestConformance_nb(SHA1& ref, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg, int modIdx){
	int conformanceOfModifiedMsg = updateAndTest(ref);
	if(conformanceOfModifiedMsg > 89){
		int weightOfModifiedMsg = ref.mWindowWeight;
		if(check_conformance_90_105(conformanceOfModifiedMsg, firstUnSatisfiedOriginalMsg, weightOfModifiedMsg, weightOfOriginalMsg, modIdx)){
			return true;
		}
	}
	else{
		return false;
	}
	return false;
}


inline bool c86nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		int modIdx, int restoreFrom){
	if(!mod_14(ref, B5, true, intermediate))//1.3
	{
		goto c86_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 14, 15);
c86_1:
	m.restore(ref, restoreFrom, 15);
	return false;
}


inline bool c87nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		int modIdx, int restoreFrom){
	if(!mod_5(ref, B10, false, intermediate))//2.3
	{
		goto c87_0;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 10);
c87_0://1.5
	if(!mod_5(ref, B9, false, intermediate))//2.3
	{
		goto c87_01;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 10);
c87_01://1
	if(!mod_14(ref, B6, false, intermediate))//1.3
	{
		goto c87_10;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 14, 15);
c87_10://1
	if(!mod_5(ref, B10|B9, false, intermediate))//1.3
	{
		goto c87_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 10);
c87_1://.5
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c88nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		int modIdx, int restoreFrom){
	if(!mod_9(ref, B7, false, intermediate))//4
	{
		goto c88_0;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 15);
c88_0://3
	if(!mod_9_op(ref, B7, false, intermediate))//6.4
	{
		goto c88_01;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 15);
c88_01://1.6
	if(!mod_14(ref, B8, true, intermediate))//B8:2.2  B7:1.2
	{
		goto c88_1;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 15);
c88_1://1
	if(!mod_14(ref, B7, true, intermediate))//2.2
	{
		goto c88_2;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 5, 15);
c88_2://.5
	m.restore(ref, restoreFrom, 15);
	return false;
}


inline bool c89nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int weightOfOriginalMsg,
		int modIdx, int restoreFrom){
	if(!mod_6(ref, B7, false, intermediate))//17%
//		if(!mod_6(ref, B7, false, intermediate))//17%
	{
		goto c89_00;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 6, 11);
c89_00:
	if(!mod_6(ref, B8, false, intermediate))//5%
	{
		goto c89_01;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 6, 11);
c89_01:
	if(!mod_14(ref, B8, true, intermediate))//2.4%
	{
		goto c89_02;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 14, 15);
c89_02:
	if(!mod_14(ref, B5, true, intermediate))//2.6
	{
		goto c89_03;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 14, 15);
c89_03:
	if(!mod_14(ref, B7, true, intermediate))//2.6
	{
		goto c89_04;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 14, 15);
c89_04://.8
	if(!mod_7_15(ref, B8, false, B29, false, intermediate))//2.1
	{
		goto c89_05;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 7, 15);
c89_05://1
	if(!mod_6(ref, B8|B7, false, intermediate))//2.1
	{
		goto c89_06;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref, 6, 15);
c89_06://.6
	if(!mod_14(ref, B8|B7, true, intermediate))//1.4%
	{
		goto c89_08;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref,14, 15);
c89_08://1
	if(!mod_13(ref, B6, false, intermediate))
	{
		goto c89_09;
	}
	if(updateAndTestConformance_nb(ref, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx)) return true;
	intermediate.restore(ref,13, 15);
c89_09://.5
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool second_correction_nb(SHA1& ref, ReducedSha& intermediate, int firstUnSatisfiedOriginalMsg, int conformanceOfModifiedMsg, int weightOfOriginalMsg,
		int modIdx, int restoreFromRound){
	switch (conformanceOfModifiedMsg) {
	case 86:
		if(c86nb(ref, intermediate, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx, restoreFromRound))return true;
		return false;
		break;
	case 87:
		if(c87nb(ref, intermediate, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx, restoreFromRound))return true;
		return false;
		break;
	case 88:
		if(c88nb(ref, intermediate, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx, restoreFromRound))return true;
		return false;
		break;
	case 89:
		if(c89nb(ref, intermediate, firstUnSatisfiedOriginalMsg, weightOfOriginalMsg, modIdx, restoreFromRound))return true;
		return false;
		break;
	default:
		break;
	}
	return false;
}


#endif /* SECOND_CORRECTIONS_NB_H_ */
