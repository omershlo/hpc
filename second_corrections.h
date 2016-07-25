/*
 * second_corrections.h
 *
 *  Created on: Jul 11, 2016
 *      Author: rc
 */

#ifndef SECOND_CORRECTIONS_H_
#define SECOND_CORRECTIONS_H_

#include "solve.h"

//inline bool updateAndTestConformance(SHA1& ref, int equToSolve, int& conformanceOfModifiedMsg);
//inline bool c84_1(SHA1& ref, int equToCorrect, int restoreFrom);
//inline bool c85_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom);
//inline bool c86_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom);
//inline bool c87_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom);
//inline bool c88_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom);
//inline bool c89_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom);
//inline bool second_correction(SHA1& ref, ReducedSha& intermediate, int conformanceOfModifiedMsg, int equToCorrect, int restoreFromRound);
//inline bool second_correction_nb(SHA1& ref, ReducedSha& intermediate, int conformanceOfModifiedMsg, int firstUnSatisfied, int weight, int restoreFromRound);


inline bool c84_1(SHA1& ref, int equToCorrect, int restoreFrom){
	if(allCorrectionsRound15(ref, corrAtRound15, equToCorrect)) return true;//3.8
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c85_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom){
	int tmpConformance;
	if(!mod_14(ref, B5, true, intermediate))//B6|B5:0.9 B5:1.3
	{
		goto c85_1;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 14, 15);
c85_1:
	if(allCorrectionsRound15(ref, corrAtRound15, equToCorrect)) return true;//1.6
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c86_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom){
	int tmpConformance;
	if(!mod_14(ref, B5, true, intermediate))//1.3
	{
		goto c86_1;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
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
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c86_2:
	if(!mod_14(ref, B8, true, intermediate))//1.1
	{
		goto c86_4;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 14, 15);
c86_4:
	if(allCorrectionsRound15(ref, corrAtRound15, equToCorrect)) return true;//3.1
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c87_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom){
	int tmpConformance;
	if(!mod_5(ref, B10, false, intermediate))//7.3
	{
		goto c87_0;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 10);
c87_0:
	if(!mod_5(ref, B9, false, intermediate))//2.3
	{
		goto c87_01;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 10);
c87_01:
	if(!mod_14(ref, B6, false, intermediate))//1.3
	{
		goto c87_10;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 14, 15);
c87_10:
	if(!mod_5(ref, B10|B9, false, intermediate))//1.3
	{
		goto c87_1;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
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
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c87_2:
if(allCorrectionsRound15(ref, corrAtRound15, equToCorrect)) return true;//2.8
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c88_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom){
	int tmpConformance;
	if(!mod_9(ref, B7, false, intermediate))//6.4
	{
		goto c88_0;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c88_0:
	if(!mod_9_op(ref, B7, false, intermediate))//6.4
	{
		goto c88_01;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c88_01:
	if(!mod_14(ref, B8, true, intermediate))//B8:2.2  B7:1.2
	{
		goto c88_1;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c88_1:
	if(!mod_14(ref, B7, true, intermediate))//2.2
	{
		goto c88_2;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
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
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c88_5:
	if(!mod_7_15(ref, B8, false, B29, false, intermediate))//1.6%
	{
		goto c88_7;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 7, 15);
c88_7:
	if(allCorrectionsRound15(ref, corrAtRound15, equToCorrect)) return true;//4.7
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool c89_1(SHA1& ref, ReducedSha& intermediate, int equToCorrect, int restoreFrom){
	int tmpConformance;
	if(!mod_6(ref, B7, false, intermediate))//17%
	{
		goto c89_00;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 6, 11);
c89_00:
	if(!mod_6(ref, B8, false, intermediate))//5%
	{
		goto c89_01;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 6, 11);
c89_01:
	if(!mod_14(ref, B8, true, intermediate))//2.4%
	{
		goto c89_10;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 14, 15);
c89_10:
	if(!mod_14(ref, B5, true, intermediate))//2.6
	{
		goto c89_4;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 14, 15);
c89_4:
	if(!mod_14(ref, B7, true, intermediate))//2.7%
	{
		goto c89_5;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 14, 15);
c89_5:
	if(!mod_7_15(ref, B8, false, B29, false, intermediate))//2.1
	{
		goto c89_6;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 7, 15);
c89_6:
	if(!mod_6(ref, B8|B7, false, intermediate))//2.1
	{
		goto c89_9;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
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
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref, 5, 15);
c89_a:
	if(!mod_14(ref, B8|B7, true, intermediate))//1.4%
	{
		goto c89_b;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref,14, 15);
c89_b:
	if(!mod_13(ref, B6, false, intermediate))//1.2%
	{
		goto c89_c;
	}
	if(updateAndTestConformance(ref, equToCorrect, tmpConformance)) return true;;
	intermediate.restore(ref,13, 15);
c89_c:
	if(allCorrectionsRound15(ref, corrAtRound15, equToCorrect)) return true;//5%
	m.restore(ref, restoreFrom, 15);
	return false;
}

inline bool second_correction(SHA1& ref, ReducedSha& intermediate, int conformanceOfModifiedMsg, int equToCorrect, int restoreFromRound){
	switch (conformanceOfModifiedMsg) {
	case 84:
		if(c84_1(ref, equToCorrect, restoreFromRound))return true;
		return false;
		break;
	case 85:
		if(c85_1(ref, intermediate, equToCorrect, restoreFromRound))return true;
		return false;
		break;
	case 86:
		if(c86_1(ref, intermediate, equToCorrect, restoreFromRound))return true;
		return false;
		break;
	case 87:
		if(c87_1(ref, intermediate, equToCorrect, restoreFromRound))return true;
		return false;
		break;
	case 88:
		if(c88_1(ref, intermediate, equToCorrect, restoreFromRound))return true;
		return false;
		break;
	case 89:
		if(c89_1(ref, intermediate, equToCorrect, restoreFromRound))return true;
		return false;
		break;
	default:
		break;
	}
	return false;
}

#endif /* SECOND_CORRECTIONS_H_ */
