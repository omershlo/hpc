/*
 * solve87.cc
 *
 *  Created on: Apr 22, 2016
 *      Author: rc
 */
#include "solve.h"

//#define PROB
#ifdef PROB
static int fail, total;
#endif

bool SHA1::solve87_5bit_9(int& conformance)
{
//5
	u32 stateSubDiff = (mA[6] ^ B9) - mA[6];
	mW[5] += stateSubDiff;
	if((mW[5] ^ m.w[5]) & mM[R5]){mW[5] = m.w[5];return false;}
	mA[6] ^= B9;
	mA30[6] = ROTATE(mA[6], 30);
//6
	mW[6] -= (stateSubDiff<<5);
	if((mW[6] ^ m.w[6]) & mM[R6]){m.restore(*this, 5, 6);return false;}
//8
	if(mA[7] & B7){
		mF[8] = F_00_19(mA[7], mA30[6], mA30[5]);
		mW[8] -= mF[8]- m.f[8];
		if((mW[8] ^ m.w[8]) & mM[R8]){m.restore(*this, 5, 8);return false;}
	}
//9
	if(!(mA[8] & B7)){
		mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
		mW[9] -= mF[9]- m.f[9];
		if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 9);return false;}
	}
//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mW[10] -= stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 5, 10);return false;}

	conformance = updateAndTest(*this);
	if(conformance > 87){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, corrAtRound15, 87, conformance)) return true;
	m.restore(*this, 5, 10);
	return false;
}

bool SHA1::solve87_5bits_9_10(int& conformance)
{
	//5
	u32 stateSubDiff = (mA[6] ^ (B10|B9)) - mA[6];
	mW[5] += stateSubDiff;
	if((mW[5] ^ m.w[5]) & mM[R5]){mW[5] = m.w[5];return false;}
	mA[6] ^= B10|B9;
	mA30[6] = ROTATE(mA[6], 30);
	//6
	mW[6] -= (stateSubDiff<<5);
	if((mW[6] ^ m.w[6]) & mM[R6]){m.restore(*this, 5, 6);return false;}
	//8
	mF[8] = F_00_19(mA[7], mA30[6], mA30[5]);
	mW[8] -= mF[8]- m.f[8];
	if((mW[8] ^ m.w[8]) & mM[R8]){m.restore(*this, 5, 8);return false;}
	//9
	mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
	mW[9] -= mF[9]- m.f[9];
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 9);return false;}
	//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mW[10] -= stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 5, 10);return false;}

	conformance = updateAndTest(*this);
	if(conformance > 87){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, corrAtRound15, 87, conformance)) return true;

	m.restore(*this, 5, 15);

	return false;
}

bool SHA1::solve87_5bit10(int& conformance)
{
	int startFrom18 = true;
//5
	u32 stateSubDiff = (mA[6] ^ B10) - mA[6];
	mW[5] += stateSubDiff;
	mA[6] ^= B10;
	mA30[6] = ROTATE(mA[6], 30);
//6
	mW[6] -= (stateSubDiff<<5);
	if((mW[6] ^ m.w[6]) & mM[R6]){m.restore(*this, 5, 6);return false;}
//9
	if(!(mA[8] & B8)){
		startFrom18 = false;
		mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
		mW[9] -= mF[9]- m.f[9];
		if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 9);return false;}
	}
//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mW[10] -= stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 5, 10);return false;}

	if(startFrom18){
		conformance = updateAndTest(*this, 18);
	}
	else{
		conformance = updateAndTest(*this, 17);
	}
	if(conformance > 87) {mFirstUnsatisfiedEquation = conformance;return true;}

	if(allCorrectionsRound15(*this, corrAtRound15, 87, conformance)) return true;

	m.restore(*this, 5, 15);

	return false;
}

bool SHA1::mod87_5(u32 xorDiff)
{
	//5
	u32 stateSubDiff = (mA[6] ^ xorDiff) - mA[6];
	mW[5] += stateSubDiff;
	if((mW[5] ^ m.w[5]) & mM[R5]){mW[5] = m.w[5];return false;}
	mA[6] ^= xorDiff;
	mA30[6] = ROTATE(mA[6], 30);
	//6
	mW[6] -= (stateSubDiff<<5);
	if((mW[6] ^ m.w[6]) & mM[R6]){m.restore(*this, 5, 6);return false;}
	//8
	mF[8] = F_00_19(mA[7], mA30[6], mA30[5]);
	mW[8] -= mF[8]- m.f[8];
	if((mW[8] ^ m.w[8]) & mM[R8]){m.restore(*this, 5, 8);return false;}
	//9
	mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
	mW[9] -= mF[9]- m.f[9];
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 9);return false;}
	//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mW[10] -= stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 5, 10);return false;}
	return true;
}

bool SHA1::mod87_13(u32 wXorDiff)
{
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[14] - (mW[14] ^ wXorDiff));
	//13
	mW[13] += stateSubDiff;
	if(((mW[13] ^ m.w[13]) & mM[R13])){m.restore(*this, 13, 13);return false;}
	mA[14] += stateSubDiff;
	mA30[14] = ROTATE(mA[14], 30);
	//14
	mW[14] ^= wXorDiff;
	//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if(((mW[15] ^ m.w[15]) & mM[R15])){m.restore(*this, 13, 15);return false;}
	return true;
}

bool SHA1::solve87_5_13(u32 xorDiff5, u32 wXorDiff13, int& conformance){
	if(!mod87_5(xorDiff5)) return false;
	if(!mod87_13(wXorDiff13)){m.restore(*this, 5, 15);return false;}
	conformance = updateAndTest(*this);
	if(conformance > 87){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, corrAtRound15, 87, conformance)) return true;
	m.restore(*this, 5, 15);
	return false;
}


bool SHA1::solve87_10(u32 xorDiff, int& conformance, bool wOrState)//wOrState = true => w
{
	conformance = 0;
	u32 stateSubDiff;
	if(wOrState){
		stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[11] - (mW[11] ^ xorDiff));
	}
	else{
		stateSubDiff = (mA[11] ^ xorDiff) - mA[11];
	}
//10
	mW[10] += stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 10, 10);return false;}
	mA[11] += stateSubDiff;
	mA30[11] = ROTATE(mA[11], 30);
//11
	if(wOrState){
		mW[11] ^= xorDiff;
	}
	else{
		mW[11] -= (stateSubDiff<<5);
		if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 10, 11);return false;}
	}
//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 10, 12);return false;}
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 10, 13);return false;}
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= mF[14]- m.f[14];
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 10, 14);return false;}
//15
	mW[15] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 10, 15);return false;}
//16
	conformance = updateAndTest(*this);
	if(conformance > 87){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 10, 15);
	return false;
}

bool SHA1::solve87_13(u32 w14XorDiff, int& conformance)
{

	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[14] - (mW[14] ^ w14XorDiff));
//13
	mW[13] += stateSubDiff;
	if(((mW[13] ^ m.w[13]) & mM[R13])){m.restore(*this, 13, 13);return false;}
	mA[14] += stateSubDiff;
	mA30[14] = ROTATE(mA[14], 30);
//14
	mW[14] ^= w14XorDiff;
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if(((mW[15] ^ m.w[15]) & mM[R15])){m.restore(*this, 13, 15);return false;}

	conformance = updateAndTest(*this);
	if(conformance > 87){mFirstUnsatisfiedEquation = conformance; return true;}

	if(solve87_5bit_9(conformance))return true;
	m.restore(*this, 5, 10);
	if(solve87_5bits_9_10(conformance))return true;
	m.restore(*this, 5, 10);
	if(allCorrectionsRound15(*this, corrAtRound15, 87, conformance)) return true;

	m.restore(*this, 13, 15);
	return false;
}

bool SHA1::solve87_14(u32 stateXorDiff, int& conformance)
{
//14
	u32 stateSubDiff = (mA[15] ^ stateXorDiff) - mA[15];
	mW[14] += stateSubDiff;
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 14, 14);return false;}
	mA[15] += stateSubDiff;
	mA30[15] = ROTATE(mA[15], 30);
//15
	mW[15] -= (stateSubDiff<<5);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 14, 15);return false;}
	conformance = updateAndTest(*this);
	if(conformance > 87){mFirstUnsatisfiedEquation = conformance; return true;}
//	if(solve87_5bit10(conformance))return true;
//	m.restore(*this, 5, 10);
	if(solve87_5bit_9(conformance))return true;
	m.restore(*this, 5, 10);
	if(solve87_5bits_9_10(conformance))return true;
	m.restore(*this, 5, 10);
	if(allCorrectionsRound15(*this, corrAtRound15, 87, conformance)) return true;
	m.restore(*this, 5, 15);
	return false;
}


bool SHA1::solve87(){
	int conformance = 0;
#ifdef PROB
	total++;
#endif
	if(solve87_5bit10(conformance))return true;
	switch(conformance){
	case 82:
		//t[1]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_13(B10, conformance))return true;
		if(solve87_13(B11|B10, conformance))return true;
		if(solve87_13(B11, conformance))return true;
		if(solve87_13(B13, conformance))return true;
		if(solve87_13(B14|B13, conformance))return true;
		if(solve87_13(B14, conformance))return true;
		if(solve87_14(B5, conformance))	return true;
		if(solve87_14(B6, conformance)) return true;
		if(solve87_14(B5|B6, conformance)) return true;
		if(solve87_14(B7, conformance)) return true;
		if(solve87_14(B7|B5, conformance)) return true;
		if(solve87_14(B7|B6, conformance)) return true;
		if(solve87_14(B7|B6|B5, conformance)) return true;
		if(solve87_14(B8, conformance)) return true;
		if(solve87_14(B8|B5, conformance)) return true;
		if(solve87_14(B8|B6, conformance)) return true;
		if(solve87_14(B8|B7, conformance)) return true;
		if(solve87_14(B8|B6|B5, conformance)) return true;
		if(solve87_14(B8|B7|B5, conformance)) return true;
		if(solve87_14(B8|B7|B6, conformance)) return true;
		if(solve87_14(B8|B7|B6|B5, conformance)) return true;
		if(solve87_14(B9|B8|B7|B6|B5, conformance)) return true;
		if(solve87_14(B9|B8|B7|B6, conformance)) return true;
		if(solve87_14(B9|B8|B7, conformance)) return true;
		if(solve87_14(B9|B8, conformance)) return true;
		if(solve87_10(B15, conformance, true)) return true;
		if(solve87_10(B8, conformance, false)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[1]++;
		break;
	case 83:
		//t[2]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_13(B10, conformance))return true;
		if(solve87_13(B11|B10, conformance))return true;
		if(solve87_13(B11, conformance))return true;
		if(solve87_13(B13, conformance))return true;
		if(solve87_13(B14|B13, conformance))return true;
		if(solve87_13(B14, conformance))return true;
		if(solve87_14(B6, conformance)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[2]++;
		break;
	case 84:
		//t[3]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_13(B10, conformance))return true;
		if(solve87_13(B11|B10, conformance))return true;
		if(solve87_13(B11, conformance))return true;
		if(solve87_13(B13, conformance))return true;
		if(solve87_13(B14|B13, conformance))return true;
		if(solve87_13(B14, conformance))return true;
		if(solve87_14(B5, conformance))	return true;
		if(solve87_14(B6, conformance)) return true;
		if(solve87_14(B5|B6, conformance)) return true;
		if(solve87_14(B7, conformance)) return true;
		if(solve87_14(B7|B5, conformance)) return true;
		if(solve87_14(B7|B6, conformance)) return true;
		if(solve87_14(B7|B6|B5, conformance)) return true;
		if(solve87_14(B8, conformance)) return true;
		if(solve87_14(B8|B5, conformance)) return true;
		if(solve87_14(B8|B6, conformance)) return true;
		if(solve87_14(B8|B7, conformance)) return true;
		if(solve87_14(B8|B6|B5, conformance)) return true;
		if(solve87_14(B8|B7|B5, conformance)) return true;
		if(solve87_14(B8|B7|B6, conformance)) return true;
		if(solve87_14(B8|B7|B6|B5, conformance)) return true;
		if(solve87_14(B9|B8|B7|B6|B5, conformance)) return true;
		if(solve87_14(B9|B8|B7|B6, conformance)) return true;
		if(solve87_14(B9|B8|B7, conformance)) return true;
		if(solve87_14(B9|B8, conformance)) return true;
		if(solve87_10(B15, conformance, true)) return true;
		if(solve87_10(B8, conformance, false)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[3]++;
		break;
	case 85:
		//t[4]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_13(B10, conformance))return true;
		if(solve87_13(B11|B10, conformance))return true;
		if(solve87_13(B11, conformance))return true;
		if(solve87_13(B13, conformance))return true;
		if(solve87_13(B14|B13, conformance))return true;
		if(solve87_13(B14, conformance))return true;
		if(solve87_14(B5, conformance)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[4]++;
		break;
	case 86:
		//t[5]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_14(B6, conformance)) return true;
		if(solve87_10(B8, conformance, false)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[5]++;
		break;
	case 87:
		//t[6]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_13(B10, conformance))return true;
		if(solve87_13(B11|B10, conformance))return true;
		if(solve87_13(B11, conformance))return true;
		if(solve87_13(B13, conformance))return true;
		if(solve87_13(B14|B13, conformance))return true;
		if(solve87_13(B14, conformance))return true;
		if(solve87_14(B6, conformance)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[6]++;
		break;
	default:
		//t[0]++;
		if(solve87_5bit_9(conformance))	return true;
		if(solve87_5bits_9_10(conformance))	return true;
		if(solve87_13(B10, conformance))return true;
		if(solve87_13(B11|B10, conformance))return true;
		if(solve87_13(B11, conformance))return true;
		if(solve87_13(B13, conformance))return true;
		if(solve87_13(B14|B13, conformance))return true;
		if(solve87_13(B14, conformance))return true;
		if(solve87_14(B5, conformance))	return true;
		if(solve87_14(B6, conformance)) return true;
		if(solve87_14(B5|B6, conformance)) return true;
		if(solve87_14(B7, conformance)) return true;
		if(solve87_14(B7|B5, conformance)) return true;
		if(solve87_14(B7|B6, conformance)) return true;
		if(solve87_14(B7|B6|B5, conformance)) return true;
		if(solve87_14(B8, conformance)) return true;
		if(solve87_14(B8|B5, conformance)) return true;
		if(solve87_14(B8|B6, conformance)) return true;
		if(solve87_14(B8|B7, conformance)) return true;
		if(solve87_14(B8|B6|B5, conformance)) return true;
		if(solve87_14(B8|B7|B5, conformance)) return true;
		if(solve87_14(B8|B7|B6, conformance)) return true;
		if(solve87_14(B8|B7|B6|B5, conformance)) return true;
		if(solve87_14(B9|B8|B7|B6|B5, conformance)) return true;
		if(solve87_14(B9|B8|B7|B6, conformance)) return true;
		if(solve87_14(B9|B8|B7, conformance)) return true;
		if(solve87_14(B9|B8, conformance)) return true;
		if(solve87_10(B15, conformance, true)) return true;
		if(solve87_10(B8, conformance, false)) return true;
		if(solve87_5_13(B10, B11, conformance)) return true;
		if(solve87_5_13(B10, B13, conformance)) return true;
		if(solve87_5_13(B10, B14|B13, conformance)) return true;
		//f[0]++;
		break;
	}
#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	m.restore(*this, 5, 22);
	return false;
}



