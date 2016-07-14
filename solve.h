/*
 * solve89.h
 *
 *  Created on: May 15, 2016
 *      Author: rc
 */

#ifndef SOLVE_H_
#define SOLVE_H_

#include "modifications.h"

bool check_conformance_90_105(int conformanceOfModifiedMsg, int firstUnSatisfied, int weightOfModifiedMsg, int weight, int modIdx);
int updateAndTest(SHA1& ref, int roundToStart);
int updateAndTest(SHA1& ref);
inline bool updateAndTestConformance(SHA1& ref, int equToSolve, int& conformanceOfModifiedMsg);
inline bool updateAndTestConformance(SHA1& ref, int equToSolve, int& conformanceOfModifiedMsg){
	conformanceOfModifiedMsg = updateAndTest(ref);
	if(conformanceOfModifiedMsg > equToSolve) {ref.mFirstUnsatisfiedEquation = conformanceOfModifiedMsg; return true;}
	return false;
}

#endif /* SOLVE_H_ */
