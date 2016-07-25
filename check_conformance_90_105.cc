#include "mod_spec.h"
extern ModSpec *NB;

bool check_conformance_90_105(int conformanceOfModifiedMsg, int firstUnSatisfied, int weightOfModifiedMsg, int weight,int modIdx){
	if(conformanceOfModifiedMsg < 90){
		++(NB[modIdx].stat.fail);
		return false;
	}
	else if(conformanceOfModifiedMsg < 106){
		if((conformanceOfModifiedMsg > firstUnSatisfied) || (weightOfModifiedMsg < weight)){
			++(NB[modIdx].stat.success);
			return true;
		}
		else if(((conformanceOfModifiedMsg < firstUnSatisfied) && (weightOfModifiedMsg  == weight)) ||
				((conformanceOfModifiedMsg == firstUnSatisfied) && (weightOfModifiedMsg  > weight)) ||
				((conformanceOfModifiedMsg == firstUnSatisfied) && (weightOfModifiedMsg == weight))){
			++(NB[modIdx].stat.neutral);
			return false;
		}
		else{
			++(NB[modIdx].stat.fail);
			return false;
		}
	}
	else{
		++(NB[modIdx].stat.success);
		return true;
	}
	return false;
}

