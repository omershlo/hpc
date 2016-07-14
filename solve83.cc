#include "solve83.h"
#include "solve.h"

//#define PROB
#ifdef PROB
static int fail, total;
#endif

//#define DEBUG

bool updateAndTest83_2nd(SHA1& ref, int restoreFromRound)
{
	//16
	ref.mF[16] = F_00_19(ref.mA[15], ref.mA30[14], ref.mA30[13]);
	Xupdate(ref.mW[16], ref.mW[13], ref.mW[8], ref.mW[2], ref.mW[0]);
	ref.mA[17] = K_00_19 + ref.mW[16] + ROTATE(ref.mA[16], 5) + ref.mF[16] + ref.mA30[12];
	if(!(ref.mA[17] & B27)) return false;//71
	ref.mA30[17] = ROTATE(ref.mA[17], 30);
	//17
	ref.mF[17] = F_00_19(ref.mA[16], ref.mA30[15], ref.mA30[14]);
	Xupdate(ref.mW[17], ref.mW[14], ref.mW[9], ref.mW[3], ref.mW[1]);
	ref.mA[18] = K_00_19 + ref.mW[17] + ROTATE(ref.mA[17], 5) + ref.mF[17] + ref.mA30[13];
	if(ref.mA[18] & B27)return false;//73
	ref.mA30[18] = ROTATE(ref.mA[18], 30);
	//18
	ref.mF[18] = F_00_19(ref.mA[17], ref.mA30[16], ref.mA30[15]);
	Xupdate(ref.mW[18], ref.mW[15], ref.mW[10], ref.mW[4], ref.mW[2]);
	ref.mA[19] = K_00_19 + ref.mW[18] + ROTATE(ref.mA[18], 5) + ref.mF[18] + ref.mA30[14];
	if(ref.mA[19] & B29)return false;//78
	ref.mA30[19] = ROTATE(ref.mA[19], 30);
	//19
	ref.mF[19] = F_00_19(ref.mA[18], ref.mA30[17], ref.mA30[16]);
	Xupdate(ref.mW[19], ref.mW[16], ref.mW[11], ref.mW[5], ref.mW[3]);
	ref.mA[20] = K_00_19 + ref.mW[19] + ROTATE(ref.mA[19], 5) + ref.mF[19] + ref.mA30[15];
	if(!((ref.mA[19] ^ ref.mA[20]) & B0))return false;//76
	if(ref.mA[20] & B31) return false;//81
	ref.mA30[20] = ROTATE(ref.mA[20], 30);
	//20
	ref.mF[20] = F_20_39(ref.mA[19], ref.mA30[18], ref.mA30[17]);
	if((ref.mF[20] ^ m.f[20]) & fMask[0])return false;//77
	Xupdate(ref.mW[20], ref.mW[17], ref.mW[12], ref.mW[6], ref.mW[4]);
	ref.mA[21] = K_20_39 + ref.mW[20] + ROTATE(ref.mA[20], 5) + ref.mF[20] + ref.mA30[16];
	ref.mA30[21] = ROTATE(ref.mA[21], 30);
	ref.mF[21] = F_20_39(ref.mA[20], ref.mA30[19], ref.mA30[18]);
	if(!(ref.mF[21] & B27) || (ref.mF[21] & B29))return false;//79, 80
	ref.mF[22] = F_20_39(ref.mA[21], ref.mA30[20], ref.mA30[19]);
	if(ref.mF[22] & B27)return false;//82
	if(!((((ref.mF[22] & B29) >> 25) ^ ref.mW[18]) & B4))//83
	{
		//at this point w[20], a[21], f[20], a30[20] are updated, k[19] is not updated
		//i.e., we need to update f[21], f[22], k[21] in order to say that mUpdatedToRound=20
		ref.mK[21] = K_20_39 + ROTATE(ref.mA[21], 5) + ref.mF[21] + ref.mA30[17];
		ref.mUpdatedToRound = restoreFromRound-1;
//#ifdef DEBUG
//		int firstUnSat = ref.compute_firstUnsatisfied();
//		if(firstUnSat < 84)
//		{
//			fprintf(stderr, "%d\n", firstUnSat);
//			rs_pause();
//		}
//		if(!test_linear_equations(ref))rs_pause();
//#endif
		ref.check_conformance(83);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool correctAtRound15(SHA1& ref, u32 d, int restoreFromRound)
{
//	SHA1 tmp = ref;
	if((((ref.mW[15]+d) ^ m.w[15]) & mM[R15]) || (((ref.mA[16]+d) ^ m.a[16]) & aMask[R15]))
		return false;
	ref.mW[15] += d;
	ref.mA[16] += d;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	if(updateAndTest83_2nd(ref, restoreFromRound)){
//		tmp.updatedToRound_setter() = ref.updatedToRound_setter() = 5;
//		tmp.compare_duo(ref, 15, 23, stderr);rs_pause();
		return true;
	}
	else return false;
}

bool updateAndTest83(SHA1& ref, int restoreFromRound)
{
	//16
	ref.mF[16] = F_00_19(ref.mA[15], ref.mA30[14], ref.mA30[13]);
	Xupdate(ref.mW[16], ref.mW[13], ref.mW[8], ref.mW[2], ref.mW[0]);
	ref.mA[17] = K_00_19 + ref.mW[16] + ROTATE(ref.mA[16], 5) + ref.mF[16] + ref.mA30[12];
	if(!(ref.mA[17] & B27)) {m.restore(ref, restoreFromRound,15);return false;}//71
	ref.mA30[17] = ROTATE(ref.mA[17], 30);
	//17
	ref.mF[17] = F_00_19(ref.mA[16], ref.mA30[15], ref.mA30[14]);
	Xupdate(ref.mW[17], ref.mW[14], ref.mW[9], ref.mW[3], ref.mW[1]);
	ref.mA[18] = K_00_19 + ref.mW[17] + ROTATE(ref.mA[17], 5) + ref.mF[17] + ref.mA30[13];
	if(ref.mA[18] & B27){m.restore(ref, restoreFromRound,15);return false;}//73
	ref.mA30[18] = ROTATE(ref.mA[18], 30);
	//18
	ref.mF[18] = F_00_19(ref.mA[17], ref.mA30[16], ref.mA30[15]);
	Xupdate(ref.mW[18], ref.mW[15], ref.mW[10], ref.mW[4], ref.mW[2]);
	ref.mA[19] = K_00_19 + ref.mW[18] + ROTATE(ref.mA[18], 5) + ref.mF[18] + ref.mA30[14];
	if(ref.mA[19] & B29){m.restore(ref, restoreFromRound, 15);return false;}//78
	ref.mA30[19] = ROTATE(ref.mA[19], 30);
	//19
	ref.mF[19] = F_00_19(ref.mA[18], ref.mA30[17], ref.mA30[16]);
	Xupdate(ref.mW[19], ref.mW[16], ref.mW[11], ref.mW[5], ref.mW[3]);
	ref.mA[20] = K_00_19 + ref.mW[19] + ROTATE(ref.mA[19], 5) + ref.mF[19] + ref.mA30[15];
	if(!((ref.mA[19] ^ ref.mA[20]) & B0)){m.restore(ref, restoreFromRound, 15);return false;}//76
	if(ref.mA[20] & B31)//81
	{
		u32 d = (ref.mA[19] & B26)? MB11 : B11;
		if(correctAtRound15(ref, d, restoreFromRound))return true;
		else{m.restore(ref, restoreFromRound, 15);return false;}
	}
	ref.mA30[20] = ROTATE(ref.mA[20], 30);
	//20
	ref.mF[20] = F_20_39(ref.mA[19], ref.mA30[18], ref.mA30[17]);
	if((ref.mF[20] ^ m.f[20]) & fMask[0]){m.restore(ref, restoreFromRound, 15);return false;}//77
	Xupdate(ref.mW[20], ref.mW[17], ref.mW[12], ref.mW[6], ref.mW[4]);
	ref.mA[21] = K_20_39 + ref.mW[20] + ROTATE(ref.mA[20], 5) + ref.mF[20] + ref.mA30[16];
	ref.mA30[21] = ROTATE(ref.mA[21], 30);
	ref.mF[21] = F_20_39(ref.mA[20], ref.mA30[19], ref.mA30[18]);
	if(!(ref.mF[21] & B27))//79
	{
		u32 d = (ref.mA[20] & B26)? B6 : MB6;
		if(correctAtRound15(ref, d, restoreFromRound))return true;
		else{m.restore(ref, restoreFromRound, 15);return false;}
	}
	if(ref.mF[21] & B29)//80
	{
		u32 d = (ref.mA[19] & B24)? MB9 : B9;
		if(correctAtRound15(ref, d, restoreFromRound))return true;
		else{m.restore(ref, restoreFromRound, 15);return false;}
	}
	ref.mF[22] = F_20_39(ref.mA[21], ref.mA30[20], ref.mA30[19]);
	if((ref.mF[22] ^ m.f[22]) & fMask[2])//82
	{
		u32 d = (ref.mA[20] & B30)? MB10 : B10;
		if(correctAtRound15(ref, d, restoreFromRound))return true;
		else{m.restore(ref, restoreFromRound, 15);return false;}
	}
	if(!((((ref.mF[22] & B29) >> 25) ^ ref.mW[18]) & B4))//83
	{
		//at this point w[20], a[21], f[20], a30[20] are updated, k[19] is not updated
		//i.e., we need to update f[21], f[22], k[21] in order to say that mUpdatedToRound=20
		ref.mK[21] = K_20_39 + ROTATE(ref.mA[21], 5) + ref.mF[21] + ref.mA30[17];
		ref.mUpdatedToRound = restoreFromRound-1;
//#ifdef DEBUG
//		int firstUnSat = ref.compute_firstUnsatisfied();
//		if(firstUnSat < 84)
//		{
//			fprintf(stderr, "%d\n", firstUnSat);
//			rs_pause();
//		}
//		if(!test_linear_equations(ref))rs_pause();
//#endif
		ref.check_conformance(83);
		return true;
	}
	else{m.restore(ref, restoreFromRound,15);return false;}
	return true;
}

bool SHA1::solve83_9(u32 w10XorDiff)
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
	if(!(mF[13] - m.f[13])){m.restore(*this, 9, 13);return false;}
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 9, 13);return false;}
//14
	mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 9, 14);return false;}
//15
	if(updateAndTest83(*this, 9))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// a[16] bit 4 => a[21] bit 29
//	* 1  10   6   2     1    6   0
bool SHA1::solve83_10_6(u32 stateXorDiff)
{
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
	u32 d2;
//f14=a13 a12 a11 : if df14=d
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	d2  = mF[14]- m.f[14];
	if(d2)
	{
		mA[15] += d2; //OS??
		mA30[15] = ROTATE(mA[15],30);
		//15
		mW[15] -= (d2 << 5);
		if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 10, 15);return false;}
	}
//15
	mA[16] += SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mA30[16] = ROTATE(mA[16], 30);
//16
	if(updateAndTest83(*this, 10))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//* 1  10  10   1     1    e   0
bool SHA1::solve83_10_10(u32 w11XorDiff)
{
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[11] - (mW[11] ^ w11XorDiff));
	if(((mW[10]+stateSubDiff) ^ m.w[10]) & mM[R10])
		return false;
	//10
	mW[10] += stateSubDiff;
	mA[11] += stateSubDiff;
	mA30[11] = ROTATE(mA[11], 30);
	//11
	mW[11] ^= w11XorDiff;
	//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12]){m.restore(*this, 10, 12);return false;}
	//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	if(!(mF[13] - m.f[13])){m.restore(*this, 10, 13);return false;}
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13])
	{
		m.restore(*this, 10, 13);
		return false;
	}
	//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14])
	{
		m.restore(*this, 10, 14);
		return false;
	}
	//15
	mA[16] += SHIFT_RIGHT2_SIGNED(stateSubDiff);
	mA30[16] = ROTATE(mA[16], 30);
	//16
	if(updateAndTest83(*this, 10))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//a[11] bit 9 a[10] bit 9
//f[13] bit 7 => w[13] bit 7 => w[16] bit 8 => a[17] bit 8 => a[21] bit 28, bit 29
//TODO: check why aux cond 61: a[15] bit 4 = 0 helps
//	* 1  11   ?   1     1    e   0
bool SHA1::solve83_11(u32 stateXorDiff, u32 testF15Diff)
{
	//11
	//OS1:testF15Diff
	if(((testF15Diff & B6) && (mA[14] & B4)) || ((testF15Diff & B5) && (mA[14] & B3))) return false;
	u32 stateSubDiff = (mA[12] ^ stateXorDiff) - mA[12];
	mW[11] += stateSubDiff;
	if(((mW[11] ^ m.w[11]) & mM[R11])){m.restore(*this, 11,12);return false;}
	mA[12] += stateSubDiff;
	mA30[12] = ROTATE(mA[12], 30);
	//12
	mW[12] -= (stateSubDiff << 5);
	if(((mW[12] ^ m.w[12]) & mM[R12])){m.restore(*this, 11,12);	return false;}
	//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 11, 13);return false;}
	//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mA[15] += mF[14] - m.f[14];
	mA30[15] = ROTATE(mA[15], 30);
	//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[14] - m.f[14]) << 5;
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 11, 15);return false;}
	mA[16] = K_00_19 + mW[15] + ROTATE(mA[15], 5) + mF[15] + mA30[11];
	mA30[16] = ROTATE(mA[16], 30);
	if(updateAndTest83(*this, 11)){return true;}
	else{return false;}
}

//a[11] bit 9 ^ a[10] bit 9 = 1
//f[13] bit 7 => w[13] bit 7 => w[16] bit 8 => a[17] bit 8 => a[21] bit 28, bit 29
//	* 1  11   7   1     1    6   0
//	* 1  11   7   1     1    e   0
bool SHA1::solve83_11_7(u32 w12XorDiff)
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
	if(!(mF[13] - m.f[13])){m.restore(*this, 11, 13);return false;}
	mW[13] -= (mF[13] - m.f[13]);
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 11, 13);return false;}
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 11, 14);return false;}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mA[16] = K_00_19 + mW[15] + ROTATE(mA[15], 5) + mF[15] + mA30[11];
	mA30[16] = ROTATE(mA[16], 30);
	ReducedSha mm;
	mm.copy(*this, 5, 15);
	if(updateAndTest83(*this, 11)){return true;}
	else
	{
//		if(mF[15] - m.f[15])
		{
			mm.restore(*this, 11, 15);
			mA[16] = m.a[16];
			mA30[16] = m.a30[16];
			mW[15] = m.w[15] - (mF[15] - m.f[15]);
			if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 11, 15);return false;}
			if(updateAndTest83(*this, 11)){return true;}else{return false;}
		}
		return false;
	}
}

//* 2  11   7   1     1    e   0   13   5   0     1    2   0
bool SHA1::solve83_11_13(u32 w13Xor)
{
	//11
	u32 stateSubDiff = (mW[12] & B12) ? B7 : MB7;
	mW[11] += stateSubDiff;
	if(((mW[11] ^ m.w[11]) & mM[R11])){m.restore(*this, 11,12);return false;}
	mA[12] += stateSubDiff;
	mA30[12] = ROTATE(mA[12], 30);
	//12
	mW[12] -= (stateSubDiff << 5);
	if(((mW[12] ^ m.w[12]) & mM[R12])){m.restore(*this, 11,12);	return false;}
	//13
	u32 stateSubDiff1= (mW[13] ^ w13Xor) - mW[13];
//	u32 stateSubDiff1= (mW[13] & w13Xor) ? MB5 : B5;
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]) - stateSubDiff1;
	if((mW[13] ^ m.w[13]) & mM[R13]){m.restore(*this, 11, 13);return false;}
	mA[14] += stateSubDiff1;
	mA30[14] = ROTATE(mA[14], 30);
	//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]) + (stateSubDiff1 << 5);
	if((mW[14] ^ m.w[14]) & mM[R14]){m.restore(*this, 11, 14);return false;}
	//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mW[15] -= (mF[15] - m.f[15]);
	if((mW[15] ^ m.w[15]) & mM[R15]){m.restore(*this, 11, 15);return false;}
	if(updateAndTest83(*this, 11)){return true;}
	else{return false;}
}

//                   7 6 5 4
//  12                 *
//  13                     1
//  14
//  15                     #
//  16

// * 1  12   6   2     1    0   0
bool SHA1::solve83_12_6(u32 stateXorDiff)
{
//df[15]!=0
	if(!(mA[14] & B4))return false;
	u32 stateSubDiff = (mA[13] ^ stateXorDiff) - mA[13];
//12
	if(((mW[12]+stateSubDiff) ^ m.w[12]) & mM[R12])
		return false;
	mW[12] += stateSubDiff;
	mA[13] += stateSubDiff;
	mA30[13] = ROTATE(mA[13], 30);
//13
	mW[13] -= (stateSubDiff<<5);
	if((mW[13] ^ m.w[13]) & mM[R13])
	{
		m.restore(*this, 12, 13);
		return false;
	}
//14
	mF[14] = F_00_19(mA[13], mA30[12], mA30[11]);
	mW[14] -= (mF[14] - m.f[14]);
	if((mW[14] ^ m.w[14]) & mM[R14])
	{
		m.restore(*this, 12, 14);
		return false;
	}
//15
	mF[15] = F_00_19(mA[14], mA30[13], mA30[12]);
	mA[16] += (mF[15] - m.f[15]);
	mA30[16] = ROTATE(mA[16], 30);
//	if(updateAndTest83Debug(*this, 12, message))
	if(updateAndTest83(*this, 12))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//* 1  14   8   1     1    0   0
bool SHA1::solve83_14_8(u32 w15XorDiff)
{
	u32 stateSubDiff = SHIFT_RIGHT5_SIGNED(mW[15] - (mW[15] ^ w15XorDiff));
	//14
	if(((mW[14]+stateSubDiff) ^ m.w[14]) & mM[R14])
	{
		return false;
	}
	mW[14] += stateSubDiff;
	mA[15] += stateSubDiff;
	if((F_00_19(mA[15], mA30[14], mA30[13]) - m.f[16]) == 0){m.restore(*this, 14, 14); return false;}
	mA30[15] = ROTATE(mA[15], 30);
	//15
	mW[15] ^= w15XorDiff; //OS4: why?
//	if(corrIndex==11)
//	{
//		tmp.compare_duo(*this,14,16,stderr);rs_pause();
//	}
	//16
	if(updateAndTest83(*this, 14))
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

//	* 2   8   8   1     1    e   1    9   8   1     1    e   1
bool SHA1::solve83_8_8__9_8(u32 w9XorDiff, u32 w10XorDiff)
{
	//8
	u32 stateSubDiff1 = SHIFT_RIGHT5_SIGNED(mW[9] - (mW[9] ^ w9XorDiff));
	if(((mW[8]+stateSubDiff1) ^ m.w[8]) & mM[R8])
	{
		return false;
	}
	mW[8] += stateSubDiff1;
	mA[9] += stateSubDiff1;
	mA30[9] = ROTATE(mA[9], 30);
	//9
	u32 stateSubDiff2 = SHIFT_RIGHT5_SIGNED(mW[10] - (mW[10] ^ w10XorDiff));
	mW[9] = (mW[9] ^ B13) + stateSubDiff2;
	if((mW[9] ^ m.w[9]) & mM[R9])
	{
		m.restore(*this, 8, 9);
		return false;
	}
	mA[10] += stateSubDiff2;
	mA30[10] = ROTATE(mA[10], 30);
	//10
	mF[10] = F_00_19(mA[9], mA30[8], mA30[7]);
	mW[10] = (mW[10] ^ B13) - (mF[10] - m.f[10]);
	if((mW[10] ^ m.w[10]) & mM[R10])
	{
		m.restore(*this, 8, 10);
		return false;
	}
	//11
	mF[11] = F_00_19(mA[10], mA30[9], mA30[8]);
	mW[11] -= (mF[11] - m.f[11]);
	if((mW[11] ^ m.w[11]) & mM[R11])
	{
		m.restore(*this, 8, 11);
		return false;
	}
	//12
	mF[12] = F_00_19(mA[11], mA30[10], mA30[9]);
	mW[12] -= (mF[12] - m.f[12]);
	if((mW[12] ^ m.w[12]) & mM[R12])
	{
		m.restore(*this, 8, 12);
		return false;
	}
	//13
	mF[13] = F_00_19(mA[12], mA30[11], mA30[10]);
	mW[13] -= (mF[13] - m.f[13]) + SHIFT_RIGHT2_SIGNED(stateSubDiff1);
	if((mW[13] ^ m.w[13]) & mM[R13])
	{
		m.restore(*this, 8, 13);
		return false;
	}
	//14
	mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff2);
	if((mW[14] ^ m.w[14]) & mM[R14])
	{
		m.restore(*this, 8, 14);
		return false;
	}
	//15
	//16
	if(updateAndTest83(*this, 8))
	{
		return true;
	}
	else
	{
	  return false;
	}
	return true;
}

//lcsCorr: five possible corrections
//OS2: lcsCorr?
bool SHA1::solve83_13(u32 w14XorDiff, u32 lcsCorr)
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
	if(lcsCorr & B2){
		mW[15] -= (mF[15] - m.f[15]);
		if(((mW[15] ^ m.w[15]) & mM[R15])){m.restore(*this, 13, 15);return false;}
	}
	else{
		mA[16] += (mF[15] - m.f[15]);
		if((mA[16] ^ m.a[16]) & aMask[R15]){m.restore(*this, 13, 15);return false;}
		mA30[16] = ROTATE(mA[16], 30);
	}
	if(updateAndTest83(*this, 13)){return true;}
	else{return false;}
}

bool SHA1::solve83(){

#ifdef PROB
	total++;
#endif
	if(solve83_10_6(B6))
		return true;
	if(solve83_11(B6, B6))
		return true;
	if(solve83_13(B11, B2))
		return true;
	if(solve83_11(B5, B5))
		return true;
	if(solve83_12_6(B6))
		return true;
	if(solve83_10_6(B7|B6))
		return true;
	if(solve83_14_8(B13))
		return true;
	if(solve83_11_7(B12))
		return true;
	if(solve83_10_6(B8|B7|B6)) //OS3: B8|B7|B6
		return true;
	if(solve83_9(B14|B13))
		return true;
	if(solve83_12_6(B8|B7|B6))
		return true;
	if(solve83_12_6(B7|B6))
		return true;
	if(solve83_10_10(B15))
		return true;
	if(solve83_8_8__9_8(B13, B13))
		return true;
	if(solve83_11(B7|B6, B6))
		return true;
	if(solve83_14_8(B13|B12))
		return true;
	if(solve83_13(B9, 0))
		return true;
	if(solve83_13(B10, B2))
		return true;
	if(solve83_10_6(B7))
		return true;
	if(solve83_9(B13))
		return true;
	if(solve83_11_13(B5))
		return true;
	if(solve83_11_13(B6|B5))
		return true;
	if(solve83_11_7(B12|B11))
		return true;
#ifdef PROB
	{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
#endif
	return false;
}


