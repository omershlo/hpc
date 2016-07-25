/*
 * solve89.cc
 *
 *  Created on: May 15, 2016
 *      Author: rc
 */
#include "solve.h"
#include "second_corrections.h"
#include "mod_spec.h"
//#define PROB
#ifdef PROB
static int fail, total;
#endif

bool solve_89(SHA1& ref, ReducedSha& baseMsg, ModStat *stat89, int numOfCorrections89){
	for(int corrIdx = 2; corrIdx < numOfCorrections89; ++corrIdx){
		int idx = stat89[corrIdx].index;
		if(globalModifications[idx].solve_upto89(ref, baseMsg, 89, stat89, corrIdx)){return true;}
	}
	return false;
}


bool SHA1::solve89(){
#ifdef PROB
	total++;
#endif
	ModStat *stat89 = correctionsIndices[89-49];
	int numOfCorrections89 = pNumberOfCorrections[89];

	if(!((mA[6]^mA[5]) & B9) && !(mA[8] & B5) && (mA[9] & B5))
	{
		if(globalModifications[0].solve_upto89(*this, m, 89, stat89, 0)){return true;}
		m.restore(*this, 6, 11);
	}
	if((!((mA[6]^mA[5]) & B10)) && !(mA[8] & B6))
	{
		if(globalModifications[1].solve_upto89(*this, m, 89, stat89, 1)){return true;}
		m.restore(*this, 6, 11);
		m.restore(*this, 18, 18);
	}
	if(solve_89(*this, m, stat89, numOfCorrections89)){return true;}

#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	m.restore(*this, 5, 20);
	return false;
}
