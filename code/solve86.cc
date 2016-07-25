//#define DEBUG
#include "solve.h"

//#define PROB
#ifdef PROB
static int fail, total;
#endif

//extern correctionSet** gEquCorr;
//extern int *gNuMOfCorr;
//
//bool test_corrections(SHA1& ref, SHA1& tmp, int equToCorrect, int conformance, int conformanceToTest, bool testAll){
//	if(testAll || conformance == conformanceToTest){
//		for(int correctionIndex = gNuMOfCorr[0] - 1; correctionIndex > - 1; correctionIndex--)
//		{
//			if(ref.apply_single_correction_and_check_neutral(tmp, gEquCorr[0][correctionIndex], EQUATION_TO_ROUND(equToCorrect)) > equToCorrect)
//			{
//				tmp.firstUnsatisfiedEquation_setter() = tmp.compute_firstUnsatisfied();
//				if(tmp.firstUnsatisfiedEquation_getter() > equToCorrect){
//					ref = tmp;
//					gEquCorr[0][correctionIndex].success++;
//					return true;
//				}
//				else
//				{
//					if(tmp.firstUnsatisfiedEquation_getter()==equToCorrect)
//					{
//						gEquCorr[0][correctionIndex].neutral++;
//					}
//					gEquCorr[0][correctionIndex].fail++;
//				}
//			}
//			else
//			{
//				if(tmp.firstUnsatisfiedEquation_getter()==equToCorrect)
//				{
//					gEquCorr[0][correctionIndex].neutral++;
//				}
//				gEquCorr[0][correctionIndex].fail++;
//			}
//		}
//		return false;
//	}
//	return false;
//}


bool correctAtRound15_86(SHA1& ref, u32 d, int& conformance)
{
	u32 w15 = ref.mW[15]; u32 a16 = ref.mA[16]; u32 a30_16 = ref.mA30[16];
	ref.mW[15] += d;
	if((ref.mW[15] ^ m.w[15]) & mM[R15]){ref.mW[15] -= d; return false;}
	ref.mA[16] += d;
	if((ref.mA[16] ^ m.a[16]) & 0x28000001){ref.mW[15] -= d;ref.mA[16] -= d;return false;}
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	conformance = updateAndTest(ref);
	if(conformance > 86){ref.mFirstUnsatisfiedEquation = conformance; return true;}
	ref.mW[15] = w15; ref.mA[16] = a16; ref.mA30[16] = a30_16;
	return false;
}

// 5, 6, 56, 568, 8, 68, 58
bool allCorrectionsRound15_86(SHA1& ref, int& conformance)
{
	u32 d;
//	u32 a20 = ref.mA[20];
	u32 a20 = m.a[20];
	u32 d8 = (a20 & B28) ? MB8 : B8;
	if(correctAtRound15_86(ref, d8, conformance))return true;
	u32 d6 = (a20 & B26) ? MB6 : B6;
	if(correctAtRound15_86(ref, d6, conformance))return true;
	u32 d5 = (a20 & B25) ? MB5 : B5;
	if(correctAtRound15_86(ref, d5, conformance))return true;
	d = d5 + d6;
	if(correctAtRound15_86(ref, d, conformance))return true;
	d = d5 + d6 + d8;
	if(correctAtRound15_86(ref, d, conformance))return true;
	d = d5 + d8;
	if(correctAtRound15_86(ref, d, conformance))return true;
	d = d6 + d8;
	if(correctAtRound15_86(ref, d, conformance))return true;
	return false;
}


bool SHA1::solve86_9(u32 stateXorDiff, int& conformance)
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
	conformance = updateAndTest(*this);
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 9, 14);
	return false;
}


bool SHA1::solve86_10(u32 stateXorDiff, int& conformance)
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 10, 15);
	return false;
}

bool SHA1::solve86_5(u32 stateXorDiff1, u32 stateXorDiff2, u32 stateXorDiff3, int& conformance)
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
	conformance = updateAndTest(*this);
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15_86(*this, conformance)) return true;

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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15_86(*this, conformance)) return true;

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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}

	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 5, 15);
	return false;
}


bool SHA1::solve86_5_13(u32 stateXorDiff1, u32 wXorDiff2, int& conformance)
{
	conformance = 0;
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
//13
	stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[14] - (mW[14] ^ wXorDiff2));
	mW[13] += stateSubDiff;
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 5, 13); return false;}
	mA[14] += stateSubDiff;
	mA30[14] = ROTATE(mA[14], 30);
//14
	mW[14] ^= wXorDiff2;
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 5, 15); return false;}

	conformance = updateAndTest(*this);
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 5, 15);
	return false;
}

bool SHA1::solve86_13(u32 w14XorDiff, int& conformance)
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 13, 15);

	return false;
}

bool SHA1::solve86_5bit_9(int& conformance)
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 5, 10);
	return false;
}

bool SHA1::solve86_5bits_9_10(int& conformance)
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 5, 10);
	return false;
}

bool SHA1::solve86_5bit10(int& conformance)
{

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
		mF[9] = F_00_19(mA[8], mA30[7], mA30[6]);
		mW[9] -= mF[9]- m.f[9];
		if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 9);return false;}
	}
//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mW[10] -= stateSubDiff;
	if((mW[10] ^ m.w[10]) & mM[R10]){m.restore(*this, 5, 10);return false;}

	conformance = updateAndTest(*this);
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}

	m.restore(*this, 5, 15);
	return false;
}

bool SHA1::solve86_14(u32 stateXorDiff, int& conformance)
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
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 5, 15);
	return false;
}

bool SHA1::solve86_11(u32 w12XorDiff, int& conformance)
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

	conformance = updateAndTest(*this);
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

	m.restore(*this, 11, 15);
	return false;
}

bool SHA1::solve86_7(u32 stateXor, int& conformance)
{

//	SHA1 tmp = *this; SHA1 modifiedMessage = *this;
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
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 7, 12);return false;}

	conformance = updateAndTest(*this);
	if(conformance > 86){mFirstUnsatisfiedEquation = conformance; return true;}
	if(allCorrectionsRound15_86(*this, conformance)) return true;

//	if(tmp.apply_single_correction_and_check_neutral(modifiedMessage, gEquationCorrections[86][33],	EQUATION_TO_ROUND(86)) > 86){
//		tmp.compare_duo(modifiedMessage, 7, 23, stderr);
//		rs_pause();
//	}
	m.restore(*this, 7, 12);
	return false;
}

bool SHA1::solve86(){
	int conformance = 0;
#ifdef PROB
	total++;
#endif
	if(solve86_5bit10(conformance)){
		return true;
	}
	else{
		if(solve86_5bits_9_10(conformance)){
			return true;
		}
		if(solve86_5bit_9(conformance)){
			return true;
		}
		switch(conformance){
		case 82:
			if(solve86_10(B8, conformance))	return true;
			if(solve86_9(B7, conformance))return true;
			if(solve86_9(B7|B8, conformance))return true;
			if(solve86_10(B9|B8, conformance))	return true;
			if(solve86_10(B9, conformance))	return true;
			if(solve86_10(B10, conformance))	return true;
			if(solve86_5(B7, B5, B5, conformance)) return true;
			if(solve86_5_13(B10, B11, conformance))return true;
			if(solve86_5_13(B10, B10, conformance))return true;
			if(allCorrectionsRound15_86(*this, conformance)) return true;
			if(solve86_5_13(B10, B10|B11, conformance))return true;
			if(solve86_13(B11, conformance))return true;
			if(solve86_11(B12, conformance))return true;
			if(solve86_7(B7, conformance))return true;
			if(solve86_10(B10|B9|B8, conformance))	return true;
			if(solve86_10(B10|B9, conformance))	return true;
			if(solve86_10(B10|B8, conformance))	return true;
			break;
		case 83:
			if(solve86_10(B8, conformance))	return true;
			if(solve86_9(B7, conformance))return true;
			if(solve86_9(B7|B8, conformance))return true;
			if(solve86_10(B9|B8, conformance))	return true;
			if(solve86_10(B9, conformance))	return true;
			if(solve86_10(B10, conformance))	return true;
			if(solve86_10(B10|B8, conformance))	return true;
			if(solve86_10(B10|B9, conformance))	return true;
			if(solve86_10(B10|B9|B8, conformance))	return true;
			if(solve86_5(B7, B5, B5, conformance)) return true;
			if(solve86_5_13(B10, B11, conformance))return true;
			if(solve86_5_13(B10, B10|B11, conformance))return true;
			if(solve86_5_13(B10, B10, conformance))return true;
			if(allCorrectionsRound15_86(*this, conformance)) return true;
			if(solve86_13(B11, conformance))return true;
			if(solve86_11(B12, conformance))return true;
			if(solve86_7(B7, conformance))return true;
			break;
		case 84:
			if(solve86_10(B8, conformance))	return true;
			if(solve86_9(B7, conformance))return true;
			if(solve86_9(B7|B8, conformance))return true;
			if(solve86_10(B9|B8, conformance))	return true;
			if(solve86_10(B9, conformance))	return true;
			if(solve86_10(B10, conformance))	return true;
			if(solve86_10(B10|B8, conformance))	return true;
			if(solve86_10(B10|B9, conformance))	return true;
			if(solve86_10(B10|B9|B8, conformance))	return true;
			if(solve86_14(B5, conformance))return true;
			if(solve86_5(B7, B5, B5, conformance)) return true;
			if(solve86_5_13(B10, B11, conformance))return true;
			if(solve86_5_13(B10, B10|B11, conformance))return true;
			if(solve86_5_13(B10, B10, conformance))return true;
			if(solve86_13(B10, conformance))return true;
			if(solve86_13(B11, conformance))return true;
			if(allCorrectionsRound15_86(*this, conformance)) return true;
			if(solve86_11(B12, conformance))return true;
			if(solve86_7(B7, conformance))return true;
			break;
		case 85:
			if(solve86_5(B7, B5, B5, conformance)) return true;
			if(solve86_5_13(B10, B11, conformance))return true;
			if(solve86_5_13(B10, B10|B11, conformance))return true;
			if(solve86_5_13(B10, B10, conformance))return true;
			if(solve86_9(B7, conformance))return true;
			if(solve86_9(B7|B8, conformance))return true;
			if(solve86_10(B8, conformance))	return true;
			if(solve86_10(B9|B8, conformance))	return true;
			if(solve86_10(B9, conformance))	return true;
			if(solve86_10(B10, conformance))	return true;
			if(solve86_10(B10|B8, conformance))	return true;
			if(solve86_10(B10|B9, conformance))	return true;
			if(solve86_10(B10|B9|B8, conformance))	return true;
			if(solve86_13(B11, conformance))return true;
			if(allCorrectionsRound15_86(*this, conformance)) return true;
			if(solve86_11(B12, conformance))return true;
			if(solve86_7(B7, conformance))return true;
			break;
		case 86:
			if(solve86_10(B8, conformance))	return true;
			if(solve86_9(B7, conformance))return true;
			if(solve86_9(B7|B8, conformance))return true;
			if(solve86_10(B9|B8, conformance))	return true;
			if(solve86_10(B9, conformance))	return true;
			if(solve86_10(B10, conformance))	return true;
			if(solve86_10(B10|B8, conformance))	return true;
			if(solve86_10(B10|B9, conformance))	return true;
			if(solve86_10(B10|B9|B8, conformance))	return true;
			if(solve86_5(B7, B5, B5, conformance)) return true;
			if(solve86_5_13(B10, B11, conformance))return true;
			if(solve86_5_13(B10, B10|B11, conformance))return true;
			if(solve86_5_13(B10, B10, conformance))return true;
			if(allCorrectionsRound15_86(*this, conformance)) return true;
			if(solve86_13(B11, conformance))return true;
			if(solve86_11(B12, conformance))return true;
			if(solve86_7(B7, conformance))return true;
			break;
		default:
			if(solve86_10(B8, conformance))	return true;
			if(solve86_9(B7, conformance))return true;
			if(solve86_9(B7|B8, conformance))return true;
			if(solve86_10(B9|B8, conformance))	return true;
			if(solve86_10(B9, conformance))	return true;
			if(solve86_10(B10, conformance))	return true;
			if(solve86_10(B10|B8, conformance))	return true;
			if(solve86_10(B10|B9, conformance))	return true;
			if(solve86_10(B10|B9|B8, conformance))	return true;
			if(solve86_5(B7, B5, B5, conformance)) return true;
			if(solve86_5_13(B10, B11, conformance))return true;
			if(solve86_5_13(B10, B10|B11, conformance))return true;
			if(solve86_5_13(B10, B10, conformance))return true;
			if(allCorrectionsRound15_86(*this, conformance)) return true;
			if(solve86_13(B11, conformance))return true;
			if(solve86_11(B12, conformance))return true;
			if(solve86_7(B7, conformance))return true;
			break;

		}
	}
	m.restore(*this, 5, 22);
#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	return false;
}
