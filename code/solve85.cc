/*
 * solve85.cc
 *
 *  Created on: Mar 28, 2016
 *      Author: rc
 */

//#define PROB
#ifdef PROB
static int fail, total;
#endif

//#define DEBUG
#include "solve.h"

bool correctAtRound14(SHA1& ref, u32 d, int& conformance)
{
	u32 w14 = ref.mW[14]; u32 a15 = ref.mA[15]; u32 a30_15 = ref.mA30[15];
	u32 w15 = ref.mW[15];
	ref.mW[14] += d;
	if((ref.mW[14] ^ m.w[14]) & mM[R14]){ref.mW[14] = w14;return false;}
	ref.mA[15] += d;
	if((ref.mA[15] ^ m.a[15]) & 0xac000000){ref.mW[14] = w14; ref.mA[15] = a15;return false;}
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	ref.mW[15] -= (d<<5);
	if((ref.mW[15] ^ m.w[15]) & mM[R15]){ref.mW[14] = w14; ref.mA[15] = a15; ref.mA30[15] = a30_15; ref.mW[15] = w15; return false;}
	conformance = updateAndTest(ref);
	if(conformance > 85){ref.mFirstUnsatisfiedEquation = conformance; return true;}
	ref.mW[14] = w14; ref.mA[15] = a15; ref.mA30[15] = a30_15; ref.mW[15] = w15;
	return false;
}

bool allCorrectionsRound14(SHA1& ref, int& conformance)
{
	u32 a15 = ref.mA[15];
	u32 d8 = (a15 & B8) ? MB8 : B8;
	if(correctAtRound14(ref, d8, conformance))return true;
	u32 d7 = (a15 & B7) ? MB7 : B7;
	if(correctAtRound14(ref, d7, conformance))return true;
	u32 d6 = (a15 & B6) ? MB6 : B6;
	if(correctAtRound14(ref, d6, conformance))return true;
	u32 d5 = (a15 & B5) ? MB5 : B5;
	if(correctAtRound14(ref, d5, conformance))return true;
	return false;
}

bool correctAtRound15(SHA1& ref, u32 d, int& conformance)
{
	u32 w15 = ref.mW[15]; u32 a16 = ref.mA[16]; u32 a30_16 = ref.mA30[16];
	ref.mW[15] += d;
	if((ref.mW[15] ^ m.w[15]) & mM[R15]){ref.mW[15] -= d; return false;}
	ref.mA[16] += d;
	if((ref.mA[16] ^ m.a[16]) & 0x28000001){ref.mW[15] -= d;ref.mA[16] -= d;return false;}
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	conformance = updateAndTest(ref);
	if(conformance > 85){ref.mFirstUnsatisfiedEquation = conformance; return true;}
	ref.mW[15] = w15; ref.mA[16] = a16; ref.mA30[16] = a30_16;
	return false;
}

// 5, 6, 56, 568, 8, 68, 58
bool allCorrectionsRound15(SHA1& ref, int& conformance)
{
	u32 d;
	u32 a20 = ref.mA[20];
//	u32 a20 = m.a[20];
	u32 d8 = (a20 & B28) ? MB8 : B8;
	if(correctAtRound15(ref, d8, conformance))return true;
	u32 d6 = (a20 & B26) ? MB6 : B6;
	if(correctAtRound15(ref, d6, conformance))return true;
	u32 d5 = (a20 & B25) ? MB5 : B5;
	if(correctAtRound15(ref, d5, conformance))return true;
	d = d5 + d6;
	if(correctAtRound15(ref, d, conformance))return true;
	d = d5 + d6 + d8;
	if(correctAtRound15(ref, d, conformance))return true;
	d = d5 + d8;
	if(correctAtRound15(ref, d, conformance))return true;
	d = d6 + d8;
	if(correctAtRound15(ref, d, conformance))return true;
	return false;
}


bool SHA1::solve85_5(u32 stateXorDiff1, u32 stateXorDiff2, u32 stateXorDiff3)
{
//5
	u32 stateSubDiff = (mA[6] ^ stateXorDiff1) - mA[6];
	mW[5] += stateSubDiff;
	if((mW[5] ^ m.w[5]) & mM[R5]){mW[5] = m.w[5];return false;}
	mA[6] += stateSubDiff;
	mA30[6] = ROTATE(mA[6], 30);
//6
	mW[6] -= (stateSubDiff<<5);
	if((mW[6] ^ m.w[6]) & mM[R6]){m.restore(*this, 5, 6);return false;}
//7
	mF[7] = F_00_19(mA[6], mA30[5], mA30[4]);
	mW[7] -= (mF[7] - m.f[7]);
	if((mW[7] ^ m.w[7]) & mM[R7]){m.restore(*this, 5, 7);return false;}
//8
	mF[8] = F_00_19(mA[7], mA30[6], mA30[5]);
	mW[8] -= (mF[8] - m.f[8]);
	if((mW[8] ^ m.w[8]) & mM[R8]){m.restore(*this, 5, 8);return false;}
//9
	mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
	mW[9] -= mF[9]- m.f[9];
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 9);return false;}
//10
	mW[10] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 5, 10);return false;}
//15
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	ReducedSha m5;
	m5.copy(*this, 5, 15);

//8
	stateSubDiff = (mA[9] ^ B8) - mA[9];
	mW[8] += stateSubDiff;
	if((mW[8] ^ m5.w[8]) & mM[R8]){mW[8] = m5.w[8]; goto c5_9;}
	mA[9] += stateSubDiff;
	mA30[9] = ROTATE(mA[9], 30);
//9
	mW[9] -= (stateSubDiff << 5);
	if((mW[9] ^ m5.w[9]) & mM[R9]){m5.restore(*this, 8, 9); goto c5_9;}
//10
	mF[10] = F_00_19(mA[9], mA30[8], mA30[7]);
	mW[10] -= (mF[10] - m5.f[10]);
	if((mW[10] ^ m5.w[10]) & mM[R10]){m5.restore(*this, 8, 10); goto c5_9;}
//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= (mF[11] - m5.f[11]);
	if((mW[11] ^ m5.w[11]) & mM[R11]){m5.restore(*this, 8, 11); goto c5_9;}
//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m5.f[12]);
	if((mW[12] ^ m5.w[12]) & mM[R12]){m5.restore(*this, 8, 12); goto c5_9;}
//13
	mW[13] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[13] ^ m5.w[13]) & mM[R13]){m5.restore(*this, 8, 13); goto c5_9;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m5.restore(*this, 8, 13);

c5_9:
	stateSubDiff = (mA[10] ^ B7) - mA[10];
//9
	mW[9] += stateSubDiff;
	if((mW[9] ^ m.w[9]) & mM[R9]){mW[9] = m5.w[9]; goto c5_10;}
	mA[10] += stateSubDiff;
	mA30[10] = ROTATE(mA[10], 30);
//10
	mW[10] -= stateSubDiff << 5;
	if((mW[10] ^ m.w[10]) & mM[R10]){m5.restore(*this, 9, 10); goto c5_10;}
//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= (mF[11] - m.f[11]);
	if((mW[11] ^ m.w[11]) & mM[R11]){m5.restore(*this, 9, 11); goto c5_10;}
//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m5.restore(*this, 9, 12); goto c5_10;}
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m5.restore(*this, 9, 13); goto c5_10;}
//14
	mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[14] ^ m.w[14]) & mM[R14]){m5.restore(*this, 9, 14); goto c5_10;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, conformance)) return true;

	m5.restore(*this, 9, 14);

c5_10:
	stateSubDiff = (mA[11] ^ B8) - mA[11];
//10
	mW[10] += stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){mW[10] = m5.w[10]; goto c5_11;}
	mA[11] += stateSubDiff;
	mA30[11] = ROTATE(mA[11], 30);
//11
	mW[11] -= (stateSubDiff<<5);
	if((mW[11] ^ m.w[11]) & mM[R11]){m5.restore(*this, 10, 11); goto c5_11;}
//12conformanceToTest
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m5.restore(*this, 10, 12); goto c5_11;}
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m5.restore(*this, 10, 13); goto c5_11;}
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= mF[14]- m.f[14];
	if((mW[14] ^ m.w[14]) & mM[R14]){m5.restore(*this, 10, 14); goto c5_11;}
//15
	mW[15] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[15] ^ m.w[15]) & mM[R15]){m5.restore(*this, 10, 15); goto c5_11;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, conformance)) return true;
	m5.restore(*this, 10, 15);

c5_11:
	stateSubDiff = (mW[12] & B14) ?  B9 : MB9;
	//11
	mW[11] += stateSubDiff;
	if((mW[11] ^ m.w[11]) & mM[R11]){m5.restore(*this, 11, 11); goto c5_13;}
	mA[12] += stateSubDiff;
	mA30[12] = ROTATE(mA[12], 30);
	//12
	mW[12] ^= B14;
	//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m5.restore(*this, 11, 13); goto c5_13;}
	//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14]){m5.restore(*this, 11, 14); goto c5_13;}
	//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m5.restore(*this, 11, 15); goto c5_13;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, conformance)) return true;
	m5.restore(*this, 11, 15);


c5_13:
//13
	stateSubDiff = (mA[14] ^ stateXorDiff2) - mA[14];
	mW[13] += stateSubDiff;
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 13, 13); goto c5_14;}
	mA[14] += stateSubDiff;
	mA30[14] = ROTATE(mA[14], 30);
//14
	mW[14] -= (stateSubDiff<<5);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 13, 14); goto c5_14;}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 13, 15); goto c5_14;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, conformance)) return true;

	m5.restore(*this, 13, 15);

c5_14:
//14
	stateSubDiff = (mA[15] ^ stateXorDiff3) - mA[15];
	mW[14] += stateSubDiff;
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 5, 15);return false;}
	mA[15] += stateSubDiff;
	mA30[15] = ROTATE(mA[15], 30);
//15
	mW[15] -= (stateSubDiff<<5);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 5, 15);return false;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 5, 15);
	return false;
}

//	* 2   8   8   2     1    e   1    10   7   3     1    e   1
bool SHA1::solve85_8_8__10_7(u32 stateXorDiff1, u32 stateXorDiff2, bool carry, int& conformance)
{
	conformance = 0;
//8
	u32 stateSubDiff1 = (mA[9] ^ stateXorDiff1) - mA[9];
	mW[8] += stateSubDiff1;
	if((mW[8] ^ m.w[8]) & mM[R8]){m.restore(*this, 8, 8);return false;}
	mA[9] += stateSubDiff1;
	mA30[9] = ROTATE(mA[9], 30);
//9
	mW[9] -= (stateSubDiff1 << 5);
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 8, 9);return false;}
//10
	mF[10] = F_00_19(mA[9], mA30[8], mA30[7]);
	u32 stateSubDiff2;
	if(carry)
		stateSubDiff2 = mA[11] - (mA[11] ^ stateXorDiff2); // 10   7   3     1    e   1
	else
		stateSubDiff2 = (mA[11] ^ stateXorDiff2) - mA[11]; // 10   7   2     1    e   1
	mW[10] = mW[10] + stateSubDiff2 - (mF[10] - m.f[10]);
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 8, 10);return false;}
	mA[11] += stateSubDiff2;
	mA30[11] = ROTATE(mA[11], 30);
//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= (stateSubDiff2 << 5) + (mF[11] - m.f[11]);
	if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 8, 11);return false;}
//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 8, 12);return false;}
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]) + SHIFT_RIGHT2_SIGNED(stateSubDiff1);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 8, 13);return false;}
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 8, 14);return false;}
//15
	mW[15] -= SHIFT_RIGHT2_SIGNED(stateSubDiff2);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 8, 15);return false;}
	conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 8, 15);
	return false;
}

bool SHA1::solve85_14(u32 stateXorDiff)
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
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 14, 15);
	return false;
}
// * 2   7   7   2     1    e   1   12   7   1     1    6   0
bool SHA1::solve85_7_12(u32 stateXor, u32 wXorDiff)
{
//7
	u32 stateSubDiff = (mA[8] ^ stateXor) - mA[8];
	mW[7] += stateSubDiff;
	if((mW[7] ^ m.w[7]) & mM[R7]){mW[7] = m.w[7];return false;}
	mA[8] += stateSubDiff;
	mA30[8] = ROTATE(mA[8], 30);
//8
	mW[8] -= (stateSubDiff << 5);
//9
	mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
	mW[9] -= (mF[9] - m.f[9]);
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 7, 9);return false;}
//10
	mF[10] = F_00_19(mA[9], mA30[8], mA30[7]);
	mW[10] -= (mF[10] - m.f[10]);
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 7, 10);return false;}
//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= mF[11]- m.f[11];
	if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 7, 11);return false;}
//12
	mW[12] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[13] - (mW[13] ^ wXorDiff));
	mW[12] = mW[12] + stateSubDiff;
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 7, 12);return false;}
	mA[13] += stateSubDiff;
	mA30[13] = ROTATE(mA[13], 30);
//13
	mW[13] ^= wXorDiff;
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 7, 14);return false;}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 7, 15);return false;}
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 7, 15);
	return false;
}

bool SHA1::solve85_11_7(u32 w12XorDiff)
{
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[12] - (mW[12] ^ w12XorDiff));
//11
	mW[11] += stateSubDiff;
	if(((mW[11] ^ m.w[11]) & mM[R11])){m.restore(*this, 11, 11);return false;}
	mA[12] += stateSubDiff;
	mA30[12] = ROTATE(mA[12], 30);
//12
	mW[12] ^= w12XorDiff;
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 11, 13);return false;}
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 11, 14);return false;}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 11, 15);return false;}
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 11, 15);
	return false;
}

bool SHA1::solve85_9(u32 stateXorDiff)
{
	u32 stateSubDiff = (mA[10] ^ stateXorDiff) - mA[10];
//9
	mW[9] += stateSubDiff;
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 9, 9);return false;}
	mA[10] += stateSubDiff;
	mA30[10] = ROTATE(mA[10], 30);
//10
	mW[10] -= (stateSubDiff << 5);
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 9, 10);return false;}
//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= (mF[11] - m.f[11]);
	if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 9, 11);return false;}
//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 9, 12);return false;}
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 9, 13);return false;}
//14
	mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 9, 14);return false;}
//15
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound14(*this, conformance)) return true;
	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 9, 15);
	return false;
}

bool SHA1::solve85_10(u32 stateXorDiff, int& conformance)
{
	conformance = 0;
	u32 stateSubDiff = (mA[11] ^ stateXorDiff) - mA[11];
//10
	mW[10] += stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 10, 10);return false;}
	mA[11] += stateSubDiff;
	mA30[11] = ROTATE(mA[11], 30);
//11
	mW[11] -= (stateSubDiff<<5);
	if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 10, 11);return false;}
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
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 10, 15);
	return false;
}

//* 2  10   7   3     1    e   1   13   5   2     1    2   0
bool SHA1::solve85_10__13(u32 stateXorDiff1, u32 stateXorDiff2){
	u32 stateSubDiff1 = mA[11] - (mA[11] ^ stateXorDiff1);
	//10
	mW[10] += stateSubDiff1;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 10, 10);return false;}
	mA[11] += stateSubDiff1;
	mA30[11] = ROTATE(mA[11], 30);
	//11
	mW[11] -= (stateSubDiff1<<5);
	if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 10, 11);return false;}
	//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 10, 12);return false;}
	//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	u32 stateSubDiff2 = (mA[14] ^ stateXorDiff2) - mA[14];
	mW[13] = mW[13] + stateSubDiff2 - (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 10, 13);return false;}
	mA[14] += stateSubDiff2;
	mA30[14] = ROTATE(mA[14], 30);
	//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (stateSubDiff2 << 5) + mF[14]- m.f[14];
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 10, 14);return false;}
	//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= mF[15]- m.f[15] + SHIFT_RIGHT2_SIGNED(stateSubDiff1);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 10, 15);return false;}
	//16
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15(*this, conformance)) return true;
	m.restore(*this, 10, 15);
	return false;
}

bool SHA1::solve85_13(u32 w14XorDiff)
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
	int conformance = updateAndTest(*this);
	if(conformance > 85){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound14(*this, conformance)) return true;

	if(allCorrectionsRound15(*this, conformance)) return true;

	m.restore(*this, 13, 15);
	return false;
}

bool SHA1::solve85(){
	int conformance;
#ifdef PROB
	total++;
#endif
	if((solve85_10(B8|B7, conformance))){
		return true;
	}
	else{
		switch(conformance){
		case 85:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_5(B10, B5, B5)) return true;
//			if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
			break;
		case 84:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_5(B10, B5, B5)) return true;
//			if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
			break;
		case 83:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_5(B10, B5, B5)) return true;
//			if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
			break;
		case 82:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_5(B10, B5, B5)) return true;
//			if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
			break;
		case 79:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_5(B10, B5, B5)) return true;
			break;
		case 0:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_5(B10, B5, B5)) return true;
//			if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
			break;
		default:
			if(solve85_8_8__10_7(B8, B7, true, conformance))return true;
			if(solve85_10__13(B7, B5))return true;
			if(solve85_11_7(B12)) return true;
			if(solve85_5(B7, B5, B5)) return true;
			if(solve85_9(B7)) return true;
			if(solve85_14(B5)) return true;
			if(solve85_14(B6|B5)) return true;
			if(solve85_8_8__10_7(B8, B7, false, conformance))return true;
			if((solve85_10(B7, conformance))) return true;
			if(solve85_7_12(B7, B12)) return true;
			if(solve85_9(B8)) return true;
			if(solve85_13(B13)) return true;
			if(solve85_5(B10, B5, B5)) return true;
//			if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
			break;
		}
	}
//	if(test_corrections(*this, tmp, 85, conformance, 82, true))return true;
	m.restore(*this, 5, 22);
#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	return false;
}



