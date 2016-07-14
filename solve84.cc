//TODO: improve the correction with w15
#include "solve.h"

//#define DEBUG

//#define PROB
#ifdef PROB
static int fail, total;
#endif

u32 nb[7];
int numOfNeutrals;
extern int equation84Condition;


bool SHA1::solve84_5(u32 stateXorDiff)
{
//5
	u32 stateSubDiff = (mA[6] ^ stateXorDiff) - mA[6];
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
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	u32 w15 = mW[15];
	u32 a16 = mA[16];
//	assert(numOfNeutrals < 8);
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		int conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}
	ReducedSha m5;
	m5.copy(*this, 5, 15);
	u32 w13Xor = mW[8] ^ m.w[8];
	if(!w13Xor)w13Xor = B5;
	mW[15] = m5.w[15];
	mA[16] = m5.a[16];
	stateSubDiff = (mW[13] ^ w13Xor) - m5.w[13];
	//13
	mW[13] += stateSubDiff;
	if(((mW[13] ^ m.w[13]) & mM[R13])){m.restore(*this, 5, 22);goto w_9_1;}
	mA[14] += stateSubDiff;
	mA30[14] = ROTATE(mA[14], 30);
	//14
	mW[14] -= (stateSubDiff<<5);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 5, 22);goto w_9_1;}
	//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if(((mW[15] ^ m.w[15]) & mM[R15])){m.restore(*this, 5, 22);goto w_9_1;}
	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	w15 = mW[15];
	a16 = mA[16];
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		int conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}
w_9_1:
	m5.restore(*this, 5, 15);
	u32 w10XorDiff = B12;
	stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[10] - (mW[10] ^ w10XorDiff));
//9
	mW[9] += stateSubDiff;
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 5, 22);return false;}
	mA[10] += stateSubDiff;
	mA30[10] = ROTATE(mA[10], 30);
//10
	mW[10] ^= w10XorDiff;
//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= (mF[11] - m.f[11]);
	if((mW[11] ^ m.w[11]) & mM[R11]){m.restore(*this, 5, 22);return false;}
//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 5, 22);return false;}
//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	if(!(mF[13] - m.f[13])){m.restore(*this, 5, 22);return false;}
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 5, 22);return false;}
//14
	mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 5, 22);return false;}
	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	w15 = mW[15];
	a16 = mA[16];
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}

	m.restore(*this, 5, 22);
	return false;
}

bool SHA1::solve84_7(u32 stateXorDiff)
{
//7
	u32 stateSubDiff = (mA[8] ^ stateXorDiff) - mA[8];
	mW[7] += stateSubDiff;
	if((mW[7] ^ m.w[7]) & mM[R7]){mW[7] = m.w[7];;return false;}
	mA[8] += stateSubDiff;
	mA30[8] = ROTATE(mA[8], 30);
//8
	mW[8] -= (stateSubDiff<<5);
	if((mW[8] ^ m.w[8]) & mM[R8]){m.restore(*this, 7, 8);return false;}
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
//15
	u32 subDiffCompensationW15 = SHIFT_RIGHT5_SIGNED(mW[16] - (mW[16] ^ ((mW[8] ^ m.w[8]) << 1)));
	mW[15] += subDiffCompensationW15;
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 7, 15);return false;}
	mA[16] += subDiffCompensationW15;
	mA30[16] = ROTATE(mA[16], 30);
	int conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}

	u32 w15 = mW[15];
	u32 a16 = mA[16];
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}
	m.restore(*this, 7, 22);
	return false;
}

bool SHA1::solve84_7_12(u32 wXorDiff)
{
//7
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[8] - (mW[8] ^ wXorDiff));
	mW[7] += stateSubDiff;
	if((mW[7] ^ m.w[7]) & mM[R7]){mW[7] = m.w[7];return false;}
	mA[8] += stateSubDiff;
	if(!(mA[8] & B9)){m.restore(*this, 7, 7);return false;}
	mA30[8] = ROTATE(mA[8], 30);
//8
	mW[8] ^= wXorDiff;
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
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	u32 w15 = mW[15];
	u32 a16 = mA[16];
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}
	m.restore(*this, 7, 22);
	return false;
}

bool SHA1::solve84_9(u32 w10XorDiff)
{
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[10] - (mW[10] ^ w10XorDiff));
//9
	mW[9] += stateSubDiff;
	if((mW[9] ^ m.w[9]) & mM[R9]){m.restore(*this, 9, 9);return false;}
	mA[10] += stateSubDiff;
	mA30[10] = ROTATE(mA[10], 30);
//10
	mW[10] ^= w10XorDiff;
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
	u32 w15 = mW[15];
	u32 a16 = mA[16];
	int conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	u32 diff = (mA[20] & B26) ? MB6 : B6;
	mW[15] = w15 + diff;
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 9, 15);return false;}
	mA[16] = a16 + diff;
	mA30[16] = ROTATE(mA[16], 30);
	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 9, 22);
	return false;
}

bool SHA1::solve84_12(u32 wXorDiff)
{
//12
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[13] - (mW[13] ^ wXorDiff));
	if(((mW[12] + stateSubDiff) ^ m.w[12]) & mM[R12])
		return false;
	mW[12] = mW[12] + stateSubDiff;
	mA[13] += stateSubDiff;
	mA30[13] = ROTATE(mA[13], 30);
//13
	mW[13] ^= wXorDiff;
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 12, 14);return false;}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	u32 subDiffW15 = - ((mF[15] - m.f[15]) & 0xffffffe0);
	subDiffW15 += SHIFT_RIGHT5_SIGNED(mW[16] - (mW[16] ^ (wXorDiff << 1)));
	mW[15] += subDiffW15;
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 12, 15);return false;}
	mA[16] = K_00_19 + mW[15] + ROTATE(mA[15], 5) + mF[15] + mA30[11];
	mA30[16] = ROTATE(mA[16], 30);
	int conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	u32 w15 = mW[15];
	u32 a16 = mA[16];
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}
	m.restore(*this, 12, 22);
	return false;
}

bool SHA1::solve84_13(u32 wXorDiff)
{
//13
	mW[13] ^= wXorDiff;
	u32 stateSubDiff = mW[13] - m.w[13];
	mA[14] += stateSubDiff;
	mA30[14] = ROTATE(mA[14], 30);
//14
	mW[14] -= (stateSubDiff<<5);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 13, 14);return false;}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 13, 15);return false;}
	int conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	u32 diff = (mA[20] & B26) ? MB6 : B6;
	mW[15] += diff;
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 13, 15);return false;}
	mA[16] += diff;
	mA30[16] = ROTATE(mA[16], 30);
	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 13, 22);
	return false;
}


bool SHA1::solve84_14(u32 wXorDiff)
{
//14
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[15] - (mW[15] ^ wXorDiff));
	mW[14] += stateSubDiff;
	if((mW[14] ^ m.w[14]) & mM[R14]){mW[14] = m.w[14];return false;}
	mA[15] += stateSubDiff;
	mA30[15] = ROTATE(mA[15], 30);
//15
	mW[15] ^= wXorDiff;
	int conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	u32 w15 = mW[15];
	u32 a16 = mA[16];
	for(int i = 0; i < numOfNeutrals; ++i){
		mW[15] = w15 + nb[i];
		if((mW[15] ^ m.w[15]) & mM[R15])continue;
		mA[16] = a16 + nb[i];
		mA30[16] = ROTATE(mA[16], 30);
		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	}
	m.restore(*this, 14, 22);
	return false;
}

bool SHA1::solve84_15()
{
	int conformance;
	u32 diff = 0;
	u32 a = (mA[20]>>25) & 0xb;
	if(equation84Condition!=0x2 && equation84Condition!=0x6){
		diff = ((a^2)-a)<<5;
		mW[15] += diff;
		if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
		mA[16] += diff;
		mA30[16] = ROTATE(mA[16], 30);

		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
		m.restore(*this, 15, 15);
		if(conformance == 84)nb[numOfNeutrals++] = diff;
		diff = ((a^0xa)-a)<<5;
		mW[15] += diff;
		if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
		mA[16] += diff;
		mA30[16] = ROTATE(mA[16], 30);

		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
		m.restore(*this, 15, 15);
		if(conformance == 84)nb[numOfNeutrals++] = diff;
	}
	if(equation84Condition!=0x0 && equation84Condition!=0x4 && equation84Condition!=0x8 && equation84Condition!=0xc){
		diff = ((a^8)-a)<<5;
		mW[15] += diff;
		if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
		mA[16] += diff;
		mA30[16] = ROTATE(mA[16], 30);

		conformance = updateAndTest(*this);
		if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
		m.restore(*this, 15, 15);
		if(conformance == 84)nb[numOfNeutrals++] = diff;
	}
	diff = ((a^3)-a)<<5;
	mW[15] += diff;
	if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
	mA[16] += diff;
	mA30[16] = ROTATE(mA[16], 30);

	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 15, 15);
	if(conformance == 84)nb[numOfNeutrals++] = diff;
	diff = ((a^1)-a)<<5;
	mW[15] += diff;
	if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
	mA[16] += diff;
	mA30[16] = ROTATE(mA[16], 30);

	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 15, 15);
	if(conformance == 84)nb[numOfNeutrals++] = diff;
	diff = ((a^0xb)-a)<<5;
	mW[15] += diff;
	if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
	mA[16] += diff;
	mA30[16] = ROTATE(mA[16], 30);

	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 15, 15);
	if(conformance == 84)nb[numOfNeutrals++] = diff;
	diff = ((a^0x9)-a)<<5;
	mW[15] += diff;
	if((mW[15] ^ m.w[15]) & mM[R15]){mW[15] -= diff; return false;}
	mA[16] += diff;
	mA30[16] = ROTATE(mA[16], 30);

	conformance = updateAndTest(*this);
	if(conformance > 84){mFirstUnsatisfiedEquation = conformance; return true;}
	m.restore(*this, 15, 15);
	if(conformance == 84)nb[numOfNeutrals++] = diff;
	return false;
}

bool SHA1::solve84(){
#ifdef PROB
	total++;
#endif
	for(int i = 0; i < 7; i++)nb[i] = 0; numOfNeutrals = 0;
	equation84Condition = 0;
	equation84Condition |= (((mA[20] & B30) >> 2) ^ (mA[22] & B28)) ? 0 : B3;
	equation84Condition |= (mF[23] & B29)?B2:0;
	equation84Condition |= (mA[21] & B31)?0:B1;
	equation84Condition |= (mA[21] & B30)?0:B0;
//if(equation84Condition==0xa || equation84Condition==0xd || equation84Condition==0xe || equation84Condition==0xf)rs_pause();
//equation84Condition = 0xa, 0xe, 0xd, 0xf => equ84 is solved
	if(solve84_15())
		return true;
	if(equation84Condition != 0 && equation84Condition != 4 && equation84Condition != 8 && equation84Condition != 12){
		if(solve84_7(B7))
			return true;
		if(solve84_7(B8|B7))
			return true;
		if(solve84_7(B8))
			return true;
	}
	if(solve84_5(B7))
		return true;
	if(solve84_12(B10))
		return true;
	if(solve84_12(B12))
		return true;
	if(solve84_12(B11|B10))
		return true;
	if(solve84_12(B11))
		return true;
	if(solve84_7_12(B12))
		return true;
	if(solve84_14(B11))
		return true;
	if(solve84_14(B12|B11))
		return true;
	if(solve84_13(B5))
		return true;
	if(solve84_9(B12))
		return true;
	if(solve84_9(B13|B12))
		return true;
	if(solve84_9(B14))
		return true;
	m.restore(*this, 5, 22);
#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	return false;
}















