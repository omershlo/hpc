#include "modifications.h"
#include "check_equations.h"

// bool test_corrections(SHA1& ref, SHA1& tmp, int equToCorrect, int conformance, int conformanceToTest, bool testAll){
//   if(testAll || (conformance == conformanceToTest)){
//     for(int correctionIndex = gNuMOfCorr[0] - 1; correctionIndex > - 1; correctionIndex--)
//     {
//       if(ref.apply_single_correction_and_check_neutral(tmp, gEquCorr[0][correctionIndex], EQUATION_TO_ROUND(equToCorrect)) > equToCorrect)
//       {
//         tmp.firstUnsatisfiedEquation_setter() = tmp.compute_firstUnsatisfied();
//         if(tmp.firstUnsatisfiedEquation_getter() > equToCorrect){
//           ref = tmp;
//           gEquCorr[0][correctionIndex].success++;
//           return true;
//         }
//         else
//         {
//           if(tmp.firstUnsatisfiedEquation_getter()==equToCorrect)
//           {
//             gEquCorr[0][correctionIndex].neutral++;
//           }
//           gEquCorr[0][correctionIndex].fail++;
//         }
//       }
//       else
//       {
//         if(tmp.firstUnsatisfiedEquation_getter()==equToCorrect)
//         {
//           gEquCorr[0][correctionIndex].neutral++;
//         }
//         gEquCorr[0][correctionIndex].fail++;
//       }
//     }
//     return false;
//   }
//   return false;
// }

bool w_Or_state(SHA1& ref, int round, u32 xorDiff, u32& stateSubDiff, bool wOrState, ReducedSha& baseMsg){
	if(wOrState){
		stateSubDiff = SHIFT_RIGHT5_SIGNED(ref.mW[round+1] - (ref.mW[round+1] ^ (xorDiff << 5)));
	}
	else{
		stateSubDiff = (ref.mA[round+1] ^ xorDiff) - ref.mA[round+1];
	}
	ref.mW[round] += stateSubDiff;
	if((ref.mW[round] ^ baseMsg.w[round]) & mM[round-5]){baseMsg.restore(ref, round, round);return false;}
	ref.mA[round+1] += stateSubDiff;
	ref.mA30[round+1] = ROTATE(ref.mA[round+1], 30);
	if(wOrState){
		ref.mW[round+1] ^= (xorDiff << 5);
	}
	else{
		ref.mW[round+1] -= (stateSubDiff<<5);
		if((ref.mW[round+1] ^ baseMsg.w[round+1]) & mM[round-4]){baseMsg.restore(ref, round, round+1);return false;}
	}
	return true;
}

bool mod(SHA1& ref, int round, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	if(round == 15){
		stateSubDiff = (baseMsg.a[20] ^ xorDiff) - baseMsg.a[20];
		stateSubDiff = SHIFT_RIGHT20_SIGNED(stateSubDiff);
		ref.mW[15] += stateSubDiff;
		if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){ref.mW[15] -= stateSubDiff;return false;}
		ref.mA[16] += stateSubDiff;
		ref.mA30[16] = ROTATE(ref.mA[16], 30);
		return true;
	}
	//round, round+1
	if(!w_Or_state(ref, round, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	if(round == 14)return true;
	//round+2
	ref.mF[round+2] = F_00_19(ref.mA[round+1], ref.mA30[round], ref.mA30[round-1]);
	ref.mW[round+2] -= (ref.mF[round+2] - baseMsg.f[round+2]);
	if(((ref.mW[round+2] ^ baseMsg.w[round+2]) & mM[round-3])){baseMsg.restore(ref, round, round+2);return false;}
	if(round == 13)return true;
	//round+3
	ref.mF[round+3] = F_00_19(ref.mA[round+2], ref.mA30[round+1], ref.mA30[round]);
	ref.mW[round+3] -= ref.mF[round+3]- baseMsg.f[round+3];
	if((ref.mW[round+3] ^ baseMsg.w[round+3]) & mM[round-2]){baseMsg.restore(ref, round, round+3);return false;}
	if(round == 12)return true;
	//round+4
	ref.mF[round+4] = F_00_19(ref.mA[round+3], ref.mA30[round+2], ref.mA30[round+1]);
	ref.mW[round+4] -= ref.mF[round+4]- baseMsg.f[round+4];
	if((ref.mW[round+4] ^ baseMsg.w[round+4]) & mM[round-1]){baseMsg.restore(ref, round, round+4);return false;}
	if(round == 11)return true;
	//round+5
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	ref.mW[round+5] -= stateSubDiff;
	if((ref.mW[round+5] ^ baseMsg.w[round+5]) & mM[round]){baseMsg.restore(ref, round, round+5);return false;}
	return true;
}


bool w_Or_state_v1(SHA1& ref, int round, u32 xorDiff, u32& stateSubDiff, bool wOrState, ReducedSha& baseMsg){
	if(wOrState){
		stateSubDiff = SHIFT_RIGHT5_SIGNED(ref.mW[round+1] - (ref.mW[round+1] ^ (xorDiff << 5)));
	}
	else{
		stateSubDiff = (ref.mA[round+1] ^ xorDiff) - ref.mA[round+1];
	}
	ref.mW[round] += stateSubDiff;
	if((ref.mW[round] ^ baseMsg.w[round]) & mM[round-5]){baseMsg.restore(ref, round, round);return false;}
	ref.mA[round+1] += stateSubDiff;
	ref.mA30[round+1] = ROTATE(ref.mA[round+1], 30);
	if(wOrState){
		ref.mW[round+1] ^= (xorDiff << 5);
	}
	else{
		ref.mW[round+1] -= (stateSubDiff<<5);
		if((ref.mW[round+1] ^ baseMsg.w[round+1]) & mM[round-4]){baseMsg.restore(ref, round, round+1);return false;}
	}
	return true;
}

bool mod_5(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	if(!w_Or_state_v1(ref, 5, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	//7
	ref.mF[7] = F_00_19(ref.mA[6], ref.mA30[5], ref.mA30[4]);
	ref.mW[7] -= (ref.mF[7] - baseMsg.f[7]);
	if(((ref.mW[7] ^ baseMsg.w[7]) & mM[R7])){baseMsg.restore(ref, 5, 7);return false;}
	//8
	ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
	ref.mW[8] -= ref.mF[8]- baseMsg.f[8];
	if((ref.mW[8] ^ baseMsg.w[8]) & mM[R8]){baseMsg.restore(ref, 5, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= ref.mF[9]- baseMsg.f[9];
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 5, 9);return false;}
	//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	ref.mW[10] -= stateSubDiff;
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 5, 10);return false;}
	return true;
}

bool mod_5_6(SHA1& ref, u32 xorDiff5, u32 xorDiff6, ReducedSha& baseMsg)
{
	u32 stateSubDiff5  = (ref.mA[6] ^ xorDiff5) - ref.mA[6];
	u32 stateSubDiff6  = (ref.mA[7] ^ xorDiff6) - ref.mA[7];
	ref.mW[5] += stateSubDiff5;
	if((ref.mW[5] ^ baseMsg.w[5]) & mM[R5]){baseMsg.restore(ref, 5, 5); return false;}
	ref.mA[6] ^= xorDiff5;
	ref.mA30[6] = ROTATE(ref.mA[6], 30);
	//7
	ref.mW[6] += stateSubDiff6 - (stateSubDiff5 << 5);
	if((ref.mW[6] ^ baseMsg.w[6]) & mM[R6]){baseMsg.restore(ref, 5, 6); return false;}
	ref.mA[7] ^= xorDiff6;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//8
	ref.mF[7] = F_00_19(ref.mA[6], ref.mA30[5], ref.mA30[4]);
	ref.mW[7] -= (ref.mF[7] - baseMsg.f[7]) + (stateSubDiff6 << 5);
	if(((ref.mW[7] ^ baseMsg.w[7]) & mM[R7])){baseMsg.restore(ref, 5, 7);return false;}
	//8
	ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
	ref.mW[8] -= ref.mF[8]- baseMsg.f[8];
	if((ref.mW[8] ^ baseMsg.w[8]) & mM[R8]){baseMsg.restore(ref, 5, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= ref.mF[9]- baseMsg.f[9];
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 5, 9);return false;}
	//10
	stateSubDiff5 = SHIFT_RIGHT2_SIGNED(stateSubDiff5);
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= stateSubDiff5 + (ref.mF[10]- baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 5, 10);return false;}
	//11
	stateSubDiff6 = SHIFT_RIGHT2_SIGNED(stateSubDiff6);
	ref.mW[11] -= stateSubDiff6;
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 5, 11);return false;}
	return true;
}


bool mod_5_10(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	if(!w_Or_state_v1(ref, 5, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	//7
	ref.mF[7] = F_00_19(ref.mA[6], ref.mA30[5], ref.mA30[4]);
	ref.mW[7] -= (ref.mF[7] - baseMsg.f[7]);
	if(((ref.mW[7] ^ baseMsg.w[7]) & mM[R7])){baseMsg.restore(ref, 5, 7);return false;}
	//8
	ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
	ref.mW[8] -= ref.mF[8]- baseMsg.f[8];
	if((ref.mW[8] ^ baseMsg.w[8]) & mM[R8]){baseMsg.restore(ref, 5, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= ref.mF[9]- baseMsg.f[9];
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 5, 9);return false;}
	//10
	stateSubDiff = SHIFT_RIGHT2_SIGNED(stateSubDiff);
	ref.mA[11] += stateSubDiff;
	ref.mA30[11] = ROTATE(ref.mA[11], 30);
	//11
	ref.mW[11] -= stateSubDiff << 5;
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 5, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 5, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 5, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= ref.mF[14]- baseMsg.f[14];
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 5, 14);return false;}
	//15
	ref.mW[15] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 5, 15);return false;}
	return true;
}

int modifyAndUpdate_6(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg){
	u32 stateSubDiff = (ref.mA[7] ^ xorDiff) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff;
	ref.mA[7] += stateSubDiff;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff<<5);
	//11
	ref.mW[11] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[11] ^ baseMsg.w[11]) & 0xffff001f){return 0;}

	//19
	ref.mF[19] = F_00_19(ref.mA[18], ref.mA30[17], ref.mA30[16]);
	Xupdate(ref.mW[19], ref.mW[16], ref.mW[11], ref.mW[5], ref.mW[3]);
	ref.mA[20] = K_00_19 + ref.mW[19] + ROTATE(ref.mA[19], 5) + ref.mF[19] + ref.mA30[15];
	if(!((ref.mA[19] ^ ref.mA[20]) & B0))return 76;//76
	if(ref.mA[20] & B31) return 81;//81
	ref.mA30[20] = ROTATE(ref.mA[20], 30);
	//20
	ref.mF[20] = F_20_39(ref.mA[19], ref.mA30[18], ref.mA30[17]);
	if((ref.mF[20] ^ m.f[20]) & 0x10000000)return 77;//77
	Xupdate(ref.mW[20], ref.mW[17], ref.mW[12], ref.mW[6], ref.mW[4]);
	ref.mA[21] = K_20_39 + ref.mW[20] + ROTATE(ref.mA[20], 5) + ref.mF[20] + ref.mA30[16];
	ref.mA30[21] = ROTATE(ref.mA[21], 30);
	//21
	ref.mF[21] = F_20_39(ref.mA[20], ref.mA30[19], ref.mA30[18]);
	if(!(ref.mF[21] & B27) || (ref.mF[21] & B29))return 79;//79, 80
	//22
	ref.mF[22] = F_20_39(ref.mA[21], ref.mA30[20], ref.mA30[19]);
	if(ref.mF[22] & B27)return 82;//82
	if((((ref.mF[22] & B29) >> 25) ^ ref.mW[18]) & B4)return 83;//83
	//21 - continue
	Xupdate(ref.mW[21], ref.mW[18], ref.mW[13], ref.mW[7], ref.mW[5]);
	ref.mA[22] = K_20_39 + ref.mW[21] + ROTATE(ref.mA[21], 5) + ref.mF[21] + ref.mA30[17];
	ref.mA30[22] = ROTATE(ref.mA[22], 30);
	//23
	ref.mF[23] = F_20_39(ref.mA[22], ref.mA30[21], ref.mA30[20]);
	if(!(!((ref.mA[20] ^ (ref.mA[22]<<2)) & B30) && ( (!(ref.mA[21] & B30) && (ref.mF[23] & B29)) || ((ref.mA[21] & B30) && !(ref.mA[21] & B31)) ))) return 84;//84
	if(!(ref.mA[22] & B31)) return 85;
	Xupdate(ref.mW[22], ref.mW[19], ref.mW[14], ref.mW[8], ref.mW[6]);
	Xupdate(ref.mW[23], ref.mW[20], ref.mW[15], ref.mW[9], ref.mW[7]);
	Xupdate(ref.mW[24], ref.mW[21], ref.mW[16], ref.mW[10], ref.mW[8]);
	ref.mA[23] = K_20_39 + ref.mW[22] + ROTATE(ref.mA[22], 5) + ref.mF[22] + ref.mA30[18];
	if(((ref.mA[22]>>2) ^ ref.mA[23] ^ ref.mW[24]) & B28) return 86;//86
	if(ref.mA[23] & B29) return 87;//87
	if(!(ref.mA[23] & B31)) return 88;//88
	ref.mA[24] = K_20_39 + ref.mW[23] + ROTATE(ref.mA[23], 5) + ref.mF[23] + ref.mA30[19];
	//24
	ref.mF[24] = F_20_39(ref.mA[23], ref.mA30[22], ref.mA30[21]);
	//25
	ref.mA30[23] = ROTATE(ref.mA[23], 30);
	ref.mF[25] = F_20_39(ref.mA[24], ref.mA30[23], ref.mA30[22]);
	Xupdate(ref.mW[25], ref.mW[22], ref.mW[17], ref.mW[11], ref.mW[9]);
	if((ref.mW[25] ^ ref.mF[25]) & B27)
	{
		c_check_conformance(ref, 90);
		return ref.mFirstUnsatisfiedEquation;
	}
	else
	{
		return 89;
	}
}

int modifyAndUpdate_6_bit8(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg){
	u32 stateSubDiff = (ref.mA[7] ^ xorDiff) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff;
	ref.mA[7] += stateSubDiff;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff<<5);
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	//11
	ref.mW[11] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[11] ^ baseMsg.w[11]) & 0xffff001f){return false;}

	//18
	ref.mF[18] = F_00_19(ref.mA[17], ref.mA30[16], ref.mA30[15]);
	Xupdate(ref.mW[18], ref.mW[15], ref.mW[10], ref.mW[4], ref.mW[2]);
	ref.mA[19] = K_00_19 + ref.mW[18] + ROTATE(ref.mA[18], 5) + ref.mF[18] + ref.mA30[14];
	if(ref.mA[19] & B29)return 78;//78
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
	if((ref.mF[20] ^ m.f[20]) & 0x10000000)return false;//77
	Xupdate(ref.mW[20], ref.mW[17], ref.mW[12], ref.mW[6], ref.mW[4]);
	ref.mA[21] = K_20_39 + ref.mW[20] + ROTATE(ref.mA[20], 5) + ref.mF[20] + ref.mA30[16];
	ref.mA30[21] = ROTATE(ref.mA[21], 30);
	//21
	ref.mF[21] = F_20_39(ref.mA[20], ref.mA30[19], ref.mA30[18]);
	if(!(ref.mF[21] & B27) || (ref.mF[21] & B29))return false;//79, 80
	//22
	ref.mF[22] = F_20_39(ref.mA[21], ref.mA30[20], ref.mA30[19]);
	if(ref.mF[22] & B27)return 82;//82
	if((((ref.mF[22] & B29) >> 25) ^ ref.mW[18]) & B4)return 83;//83
	//21 - continue
	Xupdate(ref.mW[21], ref.mW[18], ref.mW[13], ref.mW[7], ref.mW[5]);
	ref.mA[22] = K_20_39 + ref.mW[21] + ROTATE(ref.mA[21], 5) + ref.mF[21] + ref.mA30[17];
	ref.mA30[22] = ROTATE(ref.mA[22], 30);
	//23
	ref.mF[23] = F_20_39(ref.mA[22], ref.mA30[21], ref.mA30[20]);
	if(!( !((ref.mA[20] ^ (ref.mA[22]<<2)) & B30) &&
			( (!(ref.mA[21] & B30) && (ref.mF[23] & B29)) || ((ref.mA[21] & B30) && !(ref.mA[21] & B31)) ))
	) return 84;//84
	if(!(ref.mA[22] & B31)) return 85;
	Xupdate(ref.mW[22], ref.mW[19], ref.mW[14], ref.mW[8], ref.mW[6]);
	Xupdate(ref.mW[23], ref.mW[20], ref.mW[15], ref.mW[9], ref.mW[7]);
	Xupdate(ref.mW[24], ref.mW[21], ref.mW[16], ref.mW[10], ref.mW[8]);
	ref.mA[23] = K_20_39 + ref.mW[22] + ROTATE(ref.mA[22], 5) + ref.mF[22] + ref.mA30[18];
	if(((ref.mA[22]>>2) ^ ref.mA[23] ^ ref.mW[24]) & B28) return 86;//86
	if(ref.mA[23] & B29) return 87;//87
	if(!(ref.mA[23] & B31)) return 88;//88
	ref.mA[24] = K_20_39 + ref.mW[23] + ROTATE(ref.mA[23], 5) + ref.mF[23] + ref.mA30[19];
	//24
	ref.mF[24] = F_20_39(ref.mA[23], ref.mA30[22], ref.mA30[21]);
	//25
	ref.mA30[23] = ROTATE(ref.mA[23], 30);
	ref.mF[25] = F_20_39(ref.mA[24], ref.mA30[23], ref.mA30[22]);
	Xupdate(ref.mW[25], ref.mW[22], ref.mW[17], ref.mW[11], ref.mW[9]);
	if((ref.mW[25] ^ ref.mF[25]) & B27)
	{
		c_check_conformance(ref, 90);
		return ref.mFirstUnsatisfiedEquation;
	}
	else
	{
		return 89;
	}
}

bool mod_6(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (ref.mA[7] ^ xorDiff) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff;
	ref.mA[7] += stateSubDiff;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff<<5);
	//8
	ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
	ref.mW[8] -= (ref.mF[8] - baseMsg.f[8]);
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	//11
	ref.mW[11] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 6, 11);return false;}
	return true;
}

bool mod_6(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg, int& roundToStart)
{
	u32 stateSubDiff = (ref.mA[7] ^ xorDiff) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff;
	ref.mA[7] += stateSubDiff;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff<<5);
	//8
	roundToStart = 19;
	if((xorDiff<<2) & ref.mA[6]){
		roundToStart = 16;
		ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
		ref.mW[8] -= (ref.mF[8] - baseMsg.f[8]);
	}
	//9
	if(((xorDiff>>2) & ref.mA[8])){
		if(roundToStart > 17) roundToStart = 17;
		ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
		ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	}
	//10
	if(((xorDiff>>2) & ref.mA[9]) ^ (xorDiff>>2)){
		if(roundToStart > 18) roundToStart = 18;
		ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
		ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
		if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	}
	//11
	ref.mW[11] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 6, 11);return false;}
	return true;
}

bool mod_6_8(SHA1& ref, u32 xorDiff6, u32 xorDiff8, bool wOrState8, ReducedSha& baseMsg)
{
	u32 stateSubDiff6 = (ref.mA[7] ^ xorDiff6) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff6;
	ref.mA[7] += stateSubDiff6;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff6<<5);
	//8
	if((xorDiff6<<2) & ref.mA[6]){
		ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
		ref.mW[8] -= (ref.mF[8] - baseMsg.f[8]);
	}
	//8
	ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
	u32 stateSubDiff8;
	if(wOrState8){
		stateSubDiff8 = SHIFT_RIGHT5_SIGNED(ref.mW[9] - (ref.mW[9] ^ (xorDiff8 << 5)));
	}
	else{
		stateSubDiff8 = (ref.mA[9] ^ xorDiff8) - ref.mA[9];
	}
	ref.mW[8] += stateSubDiff8 - (ref.mF[8] - baseMsg.f[8]);
	if((ref.mW[8] ^ baseMsg.w[8]) & mM[R8]){baseMsg.restore(ref, 6, 8);return false;}
	ref.mA[9] += stateSubDiff8;
	ref.mA30[9] = ROTATE(ref.mA[9], 30);
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (stateSubDiff8 << 5) + (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 6, 9);return false;}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]) + SHIFT_RIGHT2_SIGNED(stateSubDiff6);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 6, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 6, 12);return false;}
	//13
	ref.mW[13] -= SHIFT_RIGHT2_SIGNED(stateSubDiff8);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 6, 13);return false;}
	return true;
}

bool mod_6_9(SHA1& ref, u32 xorDiff6, u32 xorDiff9, bool wOrState9, ReducedSha& baseMsg)
{
	u32 stateSubDiff6 = (ref.mA[7] ^ xorDiff6) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff6;
	ref.mA[7] += stateSubDiff6;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff6<<5);
	//8
	if((xorDiff6<<2) & ref.mA[6]){
		ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
		ref.mW[8] -= (ref.mF[8] - baseMsg.f[8]);
	}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	u32 stateSubDiff9;
	if(wOrState9){
		stateSubDiff9 = SHIFT_RIGHT5_SIGNED(ref.mW[10] - (ref.mW[10] ^ (xorDiff9 << 5)));
	}
	else{
		stateSubDiff9 = (ref.mA[10] ^ xorDiff9) - ref.mA[10];
	}
	ref.mW[9] += stateSubDiff9 - (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 6, 9);return false;}
	ref.mA[10] += stateSubDiff9;
	ref.mA30[10] = ROTATE(ref.mA[10], 30);
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (stateSubDiff9 << 5) + (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]) + SHIFT_RIGHT2_SIGNED(stateSubDiff6);;
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 6, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 6, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 6, 13);return false;}
	//14
	ref.mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff9);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 6, 14);return false;}
	return true;
}

bool mod_6_10(SHA1& ref, u32 xorDiff6, u32 xorDiff10, bool wOrState10, ReducedSha& baseMsg)
{
	u32 stateSubDiff6 = (ref.mA[7] ^ xorDiff6) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff6;
	ref.mA[7] += stateSubDiff6;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff6<<5);
	//8
	if((xorDiff6<<2) & ref.mA[6]){
		ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
		ref.mW[8] -= (ref.mF[8] - baseMsg.f[8]);
	}
	//9
	if(((xorDiff6>>2) & ref.mA[8])){
		ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
		ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	u32 stateSubDiff10;
	if(wOrState10){
		stateSubDiff10 = SHIFT_RIGHT5_SIGNED(ref.mW[11] - (ref.mW[11] ^ (xorDiff10 << 5)));
	}
	else{
		stateSubDiff10 = (ref.mA[11] ^ xorDiff10) - ref.mA[11];
	}
	ref.mW[10] += stateSubDiff10 - (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	ref.mA[11] += stateSubDiff10;
	ref.mA30[11] = ROTATE(ref.mA[11], 30);
	//11
	ref.mW[11] -= (stateSubDiff10 << 5) + SHIFT_RIGHT2_SIGNED(stateSubDiff6);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 6, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 6, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 6, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 6, 14);return false;}
	//15
	ref.mW[15] -= SHIFT_RIGHT2_SIGNED(stateSubDiff10);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 6, 15);return false;}
	return true;
}

bool mod_6_11(SHA1& ref, u32 xorDiff6, u32 xorDiff11, bool wOrState11, ReducedSha& baseMsg)
{
	u32 stateSubDiff6 = (ref.mA[7] ^ xorDiff6) - ref.mA[7];
	//6
	ref.mW[6] += stateSubDiff6;
	ref.mA[7] += stateSubDiff6;
	ref.mA30[7] = ROTATE(ref.mA[7], 30);
	//7
	ref.mW[7] -= (stateSubDiff6<<5);
	//8
	if((xorDiff6<<2) & ref.mA[6]){
		ref.mF[8] = F_00_19(ref.mA[7], ref.mA30[6], ref.mA30[5]);
		ref.mW[8] -= (ref.mF[8] - baseMsg.f[8]);
	}
	//9
	if(((xorDiff6>>2) & ref.mA[8])){
		ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
		ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	}
	//10
	if(((xorDiff6>>2) & ref.mA[9]) ^ (xorDiff6>>2)){
		ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
		ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
		if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 6, 10);return false;}
	}
	//11
	u32 stateSubDiff11;
	if(wOrState11){
		stateSubDiff11 = SHIFT_RIGHT5_SIGNED(ref.mW[12] - (ref.mW[12] ^ (xorDiff11 << 5)));
	}
	else{
		stateSubDiff11 = (ref.mA[12] ^ xorDiff11) - ref.mA[12];
	}
	ref.mW[11] += stateSubDiff11 - SHIFT_RIGHT2_SIGNED(stateSubDiff6);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 6, 11);return false;}
	ref.mA[12] += stateSubDiff11;
	ref.mA30[12] = ROTATE(ref.mA[12], 30);
	//12
	ref.mW[12] -= stateSubDiff11 << 5;
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 6, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 6, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 6, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 6, 15);return false;}
	return true;
}

bool mod_7(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	//7, 8
	if(!w_Or_state_v1(ref, 7, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	if(!(ref.mA[8] & B9)){baseMsg.restore(ref, 7, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 7, 9);return false;}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 7, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= ref.mF[11]- baseMsg.f[11];
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 7, 11);return false;}
	//12
	ref.mW[12] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 7, 12);return false;}
	return true;
}


bool mod_7_15(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 a20XorDiff, bool wOrState15, ReducedSha& baseMsg)
{
	u32 stateSubDiff7;
	//7, 8
	if(!w_Or_state_v1(ref, 7, xorDiff7, stateSubDiff7, wOrState7, baseMsg)) return false;
	if(!(ref.mA[8] & B9)){baseMsg.restore(ref, 7, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 7, 9);return false;}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 7, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= ref.mF[11]- baseMsg.f[11];
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 7, 11);return false;}
	//12
	ref.mW[12] -= SHIFT_RIGHT2_SIGNED(stateSubDiff7);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 7, 12);return false;}

	Xupdate(ref.mW[16], ref.mW[13], ref.mW[8], ref.mW[2], ref.mW[0]);
	ref.mA[17] = K_00_19 + ref.mW[16] + ROTATE(ref.mA[16], 5) + ref.mF[16] + ref.mA30[12];
	ref.mA30[17] = ROTATE(ref.mA[17], 30);
	Xupdate(ref.mW[17], ref.mW[14], ref.mW[9], ref.mW[3], ref.mW[1]);
	ref.mA[18] = K_00_19 + ref.mW[17] + ROTATE(ref.mA[17], 5) + ref.mF[17] + ref.mA30[13];
	ref.mA30[18] = ROTATE(ref.mA[18], 30);
	ref.mF[18] = F_00_19(ref.mA[17], ref.mA30[16], ref.mA30[15]);
	Xupdate(ref.mW[18], ref.mW[15], ref.mW[10], ref.mW[4], ref.mW[2]);
	ref.mA[19] = K_00_19 + ref.mW[18] + ROTATE(ref.mA[18], 5) + ref.mF[18] + ref.mA30[14];
	//19
	ref.mF[19] = F_00_19(ref.mA[18], ref.mA30[17], ref.mA30[16]);
	Xupdate(ref.mW[19], ref.mW[16], ref.mW[11], ref.mW[5], ref.mW[3]);
	ref.mA[20] = K_00_19 + ref.mW[19] + ROTATE(ref.mA[19], 5) + ref.mF[19] + ref.mA30[15];

	u32 stateSubDiff15 = (ref.mA[20] ^ a20XorDiff) - ref.mA[20];
	stateSubDiff15 = SHIFT_RIGHT20_SIGNED(stateSubDiff15);
	ref.mW[15] += stateSubDiff15;
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 7, 15);return false;}
	ref.mA[16] += stateSubDiff15;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}



// the disturbance at round 12 is not corrected
bool mod_7_12(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	//7, 8
	if(!w_Or_state_v1(ref, 7, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	if(!(ref.mA[8] & B9)){baseMsg.restore(ref, 7, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 7, 9);return false;}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 7, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= ref.mF[11]- baseMsg.f[11];
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 7, 11);return false;}
	//12
	ref.mA[13] += SHIFT_RIGHT2_SIGNED(stateSubDiff);
	ref.mA30[13] = ROTATE(ref.mA[13], 30);
	//13
	ref.mW[13] -= stateSubDiff << 3;
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 7, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 7, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 7, 15);return false;}
	return true;
}

bool mod_7_12(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 xorDiff12, bool wOrState12, ReducedSha& baseMsg)
{
	u32 stateSubDiff7;
	//7, 8
	if(!w_Or_state_v1(ref, 7, xorDiff7, stateSubDiff7, wOrState7, baseMsg)) return false;
	if(!(ref.mA[8] & B9)){baseMsg.restore(ref, 7, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 7, 9);return false;}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 7, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= ref.mF[11]- baseMsg.f[11];
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 7, 11);return false;}
	//12
	u32 stateSubDiff12;
	if(wOrState12){
		stateSubDiff12 = SHIFT_RIGHT5_SIGNED(ref.mW[13] - (ref.mW[13] ^ (xorDiff12 << 5)));
	}
	else{
		stateSubDiff12 = (ref.mA[13] ^ xorDiff12) - ref.mA[13];
	}
	ref.mW[12] += stateSubDiff12 - SHIFT_RIGHT2_SIGNED(stateSubDiff7);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 7, 12);return false;}
	ref.mA[13] += stateSubDiff12;
	ref.mA30[13] = ROTATE(ref.mA[13], 30);
	//13
	ref.mW[13] -= (stateSubDiff12 << 5);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 7, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 7, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 7, 15);return false;}
	return true;
}

bool mod_7_12_14(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 xorDiff12, bool wOrState12, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg)
{
	u32 stateSubDiff7;
	//7, 8
	if(!w_Or_state_v1(ref, 7, xorDiff7, stateSubDiff7, wOrState7, baseMsg)) return false;
	if(!(ref.mA[8] & B9)){baseMsg.restore(ref, 7, 8);return false;}
	//9
	ref.mF[9] = F_00_19(ref.mA[8], ref.mA30[7], ref.mA30[6]);
	ref.mW[9] -= (ref.mF[9] - baseMsg.f[9]);
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 7, 9);return false;}
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 7, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= ref.mF[11]- baseMsg.f[11];
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 7, 11);return false;}
	//12
	u32 stateSubDiff12;
	if(wOrState12){
		stateSubDiff12 = SHIFT_RIGHT5_SIGNED(ref.mW[13] - (ref.mW[13] ^ (xorDiff12 << 5)));
	}
	else{
		stateSubDiff12 = (ref.mA[13] ^ xorDiff12) - ref.mA[13];
	}
	ref.mW[12] += stateSubDiff12 - SHIFT_RIGHT2_SIGNED(stateSubDiff7);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 7, 12);return false;}
	ref.mA[13] += stateSubDiff12;
	ref.mA30[13] = ROTATE(ref.mA[13], 30);
	//13
	ref.mW[13] -= (stateSubDiff12 << 5);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 7, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	u32 stateSubDiff14;
	if(wOrState14){
		stateSubDiff14 = SHIFT_RIGHT5_SIGNED(ref.mW[15] - (ref.mW[15] ^ (xorDiff14 << 5)));
	}
	else{
		stateSubDiff14 = (ref.mA[15] ^ xorDiff14) - ref.mA[15];
	}
	ref.mW[14] += stateSubDiff14 - (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 7, 14);return false;}
	ref.mA[15] += stateSubDiff14;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]) + (stateSubDiff14 << 5);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 7, 15);return false;}
	return true;
}

bool mod_8_11(SHA1& ref, u32 xorDiff8, bool wOrState8, u32 xorDiff11, bool wOrState11, ReducedSha& baseMsg)
{
	u32 stateSubDiff8;
	//8, 9
	if(!w_Or_state_v1(ref, 8, xorDiff8, stateSubDiff8, wOrState8, baseMsg)) return false;
	//10
	ref.mF[10] = F_00_19(ref.mA[9], ref.mA30[8], ref.mA30[7]);
	ref.mW[10] -= (ref.mF[10] - baseMsg.f[10]);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 8, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	u32 stateSubDiff11;
	if(wOrState11){
		stateSubDiff11 = SHIFT_RIGHT5_SIGNED(ref.mW[12] - (ref.mW[12] ^ (xorDiff11 << 5)));
	}
	else{
		stateSubDiff11 = (ref.mA[12] ^ xorDiff11) - ref.mA[12];
	}
	ref.mW[11] += stateSubDiff11 - (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 8, 11);return false;}
	ref.mA[12] += stateSubDiff11;
	ref.mA30[12] = ROTATE(ref.mA[12], 30);
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= ref.mF[12]- baseMsg.f[12] + (stateSubDiff11 << 5);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 8, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -=   ref.mF[13]- baseMsg.f[13] + SHIFT_RIGHT2_SIGNED(stateSubDiff8);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 8, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= ref.mF[14]- baseMsg.f[14];
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 8, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 8, 15);return false;}
	return true;
}

bool mod_9(SHA1& ref, u32 xorDiff9, bool wOrState9, ReducedSha& baseMsg)
{
	u32 stateSubDiff9;
	//9, 10
	if(!w_Or_state_v1(ref, 9, xorDiff9, stateSubDiff9, wOrState9, baseMsg)) return false;
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 9, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 9, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 9, 13);return false;}
	//14
	ref.mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff9);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 9, 14);return false;}
	return true;
}

bool mod_9(SHA1& ref, u32 stateXorDiff, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (ref.mA[10] ^ stateXorDiff) - ref.mA[10];
	//9
	ref.mW[9] += stateSubDiff;
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 9, 9);return false;}
	ref.mA[10] += stateSubDiff;
	ref.mA30[10] = ROTATE(ref.mA[10], 30);
	//10
	ref.mW[10] -= (stateSubDiff << 5);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 9, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 9, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 9, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 9, 13);return false;}
	//14
	ref.mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 9, 14);return false;}
	return true;
}

bool mod_9_op(SHA1& ref, u32 stateXorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff = ref.mA[10] - (ref.mA[10] ^ stateXorDiff);
	//9
	ref.mW[9] += stateSubDiff;
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 9, 9);return false;}
	ref.mA[10] += stateSubDiff;
	ref.mA30[10] = ROTATE(ref.mA[10], 30);
	//10
	ref.mW[10] -= (stateSubDiff << 5);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 9, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 9, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 9, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 9, 13);return false;}
	//14
	ref.mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 9, 14);return false;}
	return true;
}

bool mod_9_14(SHA1& ref, u32 stateXorDiff, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (ref.mA[10] ^ stateXorDiff) - ref.mA[10];
	//9
	ref.mW[9] += stateSubDiff;
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 9, 9);return false;}
	ref.mA[10] += stateSubDiff;
	ref.mA30[10] = ROTATE(ref.mA[10], 30);
	//10
	ref.mW[10] -= (stateSubDiff << 5);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 9, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 9, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 9, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 9, 13);return false;}
	//14
	ref.mA[15] += SHIFT_RIGHT2_SIGNED(stateSubDiff);
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mW[15] -= stateSubDiff << 3;
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 9, 15);return false;}
	return true;
}

bool mod_9_14(SHA1& ref, u32 stateXorDiff1, u32 stateXorDiff2, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (ref.mA[10] ^ stateXorDiff1) - ref.mA[10];
	//9
	ref.mW[9] += stateSubDiff;
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 9, 9);return false;}
	ref.mA[10] += stateSubDiff;
	ref.mA30[10] = ROTATE(ref.mA[10], 30);
	//10
	ref.mW[10] -= (stateSubDiff << 5);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 9, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 9, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 9, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 9, 13);return false;}
	//14
	ref.mW[14] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);

	stateSubDiff = (ref.mA[15] ^ stateXorDiff2) - ref.mA[15];
	ref.mW[14] += stateSubDiff;
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 9, 14);return false;}
	ref.mA[15] += stateSubDiff;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mW[15] -= stateSubDiff << 5;
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 9, 15);return false;}
	return true;
}

bool mod_9_14(SHA1& ref, u32 xorDiff9, bool wOrState9, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg)
{
	u32 stateSubDiff9;
	//9, 10
	if(wOrState9){
		stateSubDiff9 = SHIFT_RIGHT5_SIGNED(ref.mW[10] - (ref.mW[10] ^ (xorDiff9 << 5)));
	}
	else{
		stateSubDiff9 = (ref.mA[10] ^ xorDiff9) - ref.mA[10];
	}
	ref.mW[9] += stateSubDiff9;
	if((ref.mW[9] ^ baseMsg.w[9]) & mM[R9]){baseMsg.restore(ref, 9, 9);return false;}
	ref.mA[10] += stateSubDiff9;
	ref.mA30[10] = ROTATE(ref.mA[10], 30);
	//10
	ref.mW[10] -= (stateSubDiff9 << 5);
	if((ref.mW[10] ^ baseMsg.w[10]) & mM[R10]){baseMsg.restore(ref, 9, 10);return false;}
	//11
	ref.mF[11] = F_00_19(ref.mA[10], ref.mA30[9], ref.mA30[8]);
	ref.mW[11] -= (ref.mF[11] - baseMsg.f[11]);
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 9, 11);return false;}
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 9, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 9, 13);return false;}
	//14
	u32 stateSubDiff14;
	if(wOrState14){
		stateSubDiff14 = SHIFT_RIGHT5_SIGNED(ref.mW[15] - (ref.mW[15] ^ (xorDiff14 << 5)));
	}
	else{
		stateSubDiff14 = (ref.mA[15] ^ xorDiff14) - ref.mA[15];
	}
	ref.mW[14] += stateSubDiff14 - SHIFT_RIGHT2_SIGNED(stateSubDiff9);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 9, 14);return false;}
	ref.mA[15] += stateSubDiff14;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mW[15] -= (stateSubDiff14<<5);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 9, 15);return false;}
	return true;
}

bool mod_10(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)//wOrState = true => w
{
	u32 stateSubDiff;
	if(!w_Or_state_v1(ref, 10, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 10, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 10, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= ref.mF[14]- baseMsg.f[14];
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 10, 14);return false;}
	//15
	ref.mW[15] -= SHIFT_RIGHT2_SIGNED(stateSubDiff);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 10, 15);return false;}
	return true;
}

bool mod_10_13(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 xorDiff13, bool wOrState13, ReducedSha& baseMsg)
{
	u32 stateSubDiff10;
	if(!w_Or_state_v1(ref, 10, xorDiff10, stateSubDiff10, wOrState10, baseMsg)) return false;
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 10, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	u32 stateSubDiff13;
	if(wOrState13){
		stateSubDiff13 = SHIFT_RIGHT5_SIGNED(ref.mW[14] - (ref.mW[14] ^ (xorDiff13 << 5)));
	}
	else{
		stateSubDiff13 = (ref.mA[14] ^ xorDiff13) - ref.mA[14];
	}
	ref.mW[13] += stateSubDiff13 - (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 10, 13);return false;}
	ref.mA[14] += stateSubDiff13;
	ref.mA30[14] = ROTATE(ref.mA[14], 30);
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (stateSubDiff13 << 5) + (ref.mF[14] -  baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 10, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -=  (ref.mF[15] -  baseMsg.f[15]) + SHIFT_RIGHT2_SIGNED(stateSubDiff10);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 10, 15);return false;}
	return true;
}

bool mod_10_14(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg)
{
	u32 stateSubDiff10;
	if(!w_Or_state_v1(ref, 10, xorDiff10, stateSubDiff10, wOrState10, baseMsg)) return false;
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 10, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 10, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	u32 stateSubDiff14;
	if(wOrState14){
		stateSubDiff14 = SHIFT_RIGHT5_SIGNED(ref.mW[15] - (ref.mW[15] ^ (xorDiff14 << 5)));
	}
	else{
		stateSubDiff14 = (ref.mA[15] ^ xorDiff14) - ref.mA[15];
	}
	ref.mW[14] += stateSubDiff14 - (ref.mF[14]- baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 10, 14);return false;}
	ref.mA[15] += stateSubDiff14;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mW[15] -= (stateSubDiff14 << 5) + SHIFT_RIGHT2_SIGNED(stateSubDiff10);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 10, 15);return false;}
	return true;
}

bool mod_10_15(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 a20XorDiff, ReducedSha& baseMsg)
{
	u32 stateSubDiff10;
	if(!w_Or_state_v1(ref, 10, xorDiff10, stateSubDiff10, wOrState10, baseMsg)) return false;
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 10, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 10, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= ref.mF[14]- baseMsg.f[14];
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 10, 14);return false;}
	//15
	u32 stateSubDiff15 = SHIFT_RIGHT20_SIGNED(((baseMsg.a[20] ^ a20XorDiff) - baseMsg.a[20]));
	ref.mW[15] += stateSubDiff15 - SHIFT_RIGHT2_SIGNED(stateSubDiff10);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 10, 15);return false;}
	ref.mA[16] += stateSubDiff15;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}

bool mod_10_15_v1(SHA1& ref, u32 xorDiff10, bool wOrState10, ReducedSha& baseMsg)
{
	u32 stateSubDiff10;
	if(!w_Or_state_v1(ref, 10, xorDiff10, stateSubDiff10, wOrState10, baseMsg)) return false;
	//12
	ref.mF[12] = F_00_19(ref.mA[11], ref.mA30[10], ref.mA30[9]);
	ref.mW[12] -= (ref.mF[12] - baseMsg.f[12]);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 10, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 10, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= ref.mF[14]- baseMsg.f[14];
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 10, 14);return false;}
	//15
	ref.mA[16] += SHIFT_RIGHT2_SIGNED(stateSubDiff10);
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}


bool mod_11(SHA1& ref, u32 xorDiff, bool wOrState , ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	//12
	if(!w_Or_state_v1(ref, 11, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 11, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 11, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 7, 15);return false;}
	return true;
}

//wOrState14 = false => a[15] ^= xorDiff14
//wOrState14 = true => w[15] ^= xorDiff14<<5
bool mod_11_14(SHA1& ref, u32 xorDiff11, bool wOrState11, u32 xorDiff14, bool wOrState14 , ReducedSha& baseMsg)
{
	u32 stateSubDiff11;
	//11
	if(wOrState11){
		stateSubDiff11 = SHIFT_RIGHT5_SIGNED(ref.mW[12] - (ref.mW[12] ^ (xorDiff11 << 5)));
	}
	else{
		stateSubDiff11 = (ref.mA[12] ^ xorDiff11) - ref.mA[12];
	}
	ref.mW[11] += stateSubDiff11;
	if((ref.mW[11] ^ baseMsg.w[11]) & mM[R11]){baseMsg.restore(ref, 11, 11);return false;}
	//12
	ref.mA[12] += stateSubDiff11;
	ref.mA30[12] = ROTATE(ref.mA[12], 30);
	ref.mW[12] -= (stateSubDiff11<<5);
	if((ref.mW[12] ^ baseMsg.w[12]) & mM[R12]){baseMsg.restore(ref, 11, 12);return false;}
	//13
	ref.mF[13] = F_00_19(ref.mA[12], ref.mA30[11], ref.mA30[10]);
	ref.mW[13] -= (ref.mF[13] - baseMsg.f[13]);
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 11, 13);return false;}
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	u32 stateSubDiff14;
	if(wOrState14){
		stateSubDiff14 = SHIFT_RIGHT5_SIGNED(ref.mW[15] - (ref.mW[15] ^ (xorDiff14 << 5)));
	}
	else{
		stateSubDiff14 = (ref.mA[15] ^ xorDiff14) - ref.mA[15];
	}
	ref.mW[14] += stateSubDiff14 - (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 11, 14);return false;}
	ref.mA[15] += stateSubDiff14;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (stateSubDiff14<<5) + (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 7, 15);return false;}
	return true;
}

bool mod_12(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	//12
	if(!w_Or_state_v1(ref, 12, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	//14
	ref.mF[14] = F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]);
	ref.mW[14] -= (ref.mF[14] - baseMsg.f[14]);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 12, 14);return false;}
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 12, 15);return false;}
	return true;
}

bool mod_13(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff;
	if(!w_Or_state_v1(ref, 13, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -= (ref.mF[15] - baseMsg.f[15]);
	if(((ref.mW[15] ^ baseMsg.w[15]) & mM[R15])){baseMsg.restore(ref, 13, 15);return false;}
	return true;
}

bool mod_13_14(SHA1& ref, u32 xorDiff13, bool wOrState13, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg)
{
	//13
	u32 stateSubDiff13;
	if(wOrState13){
		stateSubDiff13 = SHIFT_RIGHT5_SIGNED(ref.mW[14] - (ref.mW[14] ^ (xorDiff13 << 5)));
	}
	else{
		stateSubDiff13 = (ref.mA[14] ^ xorDiff13) - ref.mA[14];
	}
	ref.mW[13] += stateSubDiff13;
	if((ref.mW[13] ^ baseMsg.w[13]) & mM[R13]){baseMsg.restore(ref, 13, 13);return false;}
	ref.mA[14] += stateSubDiff13;
	ref.mA30[14] = ROTATE(ref.mA[14], 30);
	//14
	u32 stateSubDiff14;
	if(wOrState14){
		stateSubDiff14 = SHIFT_RIGHT5_SIGNED(ref.mW[15] - (ref.mW[15] ^ (xorDiff14 << 5)));
	}
	else{
		stateSubDiff14 = (ref.mA[15] ^ xorDiff14) - ref.mA[15];
	}
	ref.mW[14] +=  stateSubDiff14 - (stateSubDiff13 << 5);
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 13, 14);return false;}
	ref.mA[15] += stateSubDiff14;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	ref.mW[15] -=  (stateSubDiff14 << 5) + ((ref.mF[15] - baseMsg.f[15]));
	if(((ref.mW[15] ^ baseMsg.w[15]) & mM[R15])){baseMsg.restore(ref, 13, 15);return false;}
	return true;
}

bool mod_13_15(SHA1& ref, u32 xorDiff13, bool wOrState13, u32 a20XorDiff, ReducedSha& baseMsg)
{
	u32 stateSubDiff13;
	if(!w_Or_state_v1(ref, 13, xorDiff13, stateSubDiff13, wOrState13, baseMsg)) return false;
	//15
	ref.mF[15] = F_00_19(ref.mA[14], ref.mA30[13], ref.mA30[12]);
	u32 stateSubDiff15 = SHIFT_RIGHT20_SIGNED((baseMsg.a[20] ^ a20XorDiff)- baseMsg.a[20]);
	ref.mW[15] +=  stateSubDiff15 - ((ref.mF[15] - baseMsg.f[15]));
	if(((ref.mW[15] ^ baseMsg.w[15]) & mM[R15])){baseMsg.restore(ref, 13, 15);return false;}
	ref.mA[16] += stateSubDiff15;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}

bool mod_14(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)//wOrState = true => w
{
	u32 stateSubDiff;
	if(!w_Or_state_v1(ref, 14, xorDiff, stateSubDiff, wOrState, baseMsg)) return false;
	return true;
}


bool mod_14_15(SHA1& ref, u32 xorDiff14, bool wOrState14, u32 a20XorDiff, ReducedSha& baseMsg)//wOrState = true => w
{
	u32 stateSubDiff14;
	if(wOrState14){
		stateSubDiff14 = SHIFT_RIGHT5_SIGNED(ref.mW[15] - (ref.mW[15] ^ (xorDiff14 << 5)));
	}
	else{
		stateSubDiff14 = (ref.mA[15] ^ xorDiff14) - ref.mA[15];
	}
	//14
	ref.mW[14] += stateSubDiff14;
	if((ref.mW[14] ^ baseMsg.w[14]) & mM[R14]){baseMsg.restore(ref, 14, 14);return false;}
	ref.mA[15] += stateSubDiff14;
	ref.mA30[15] = ROTATE(ref.mA[15], 30);
	//15
	u32 stateSubDiff15 = SHIFT_RIGHT20_SIGNED((baseMsg.a[20] ^ a20XorDiff)- baseMsg.a[20]);
	ref.mW[15] +=  stateSubDiff15 - (stateSubDiff14 << 5);
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){baseMsg.restore(ref, 14, 15); return false;}
	ref.mA[16] += stateSubDiff15;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}

bool mod_15(SHA1& ref, u32 a20XorDiff, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (baseMsg.a[20] ^ a20XorDiff) - baseMsg.a[20];
	stateSubDiff = SHIFT_RIGHT20_SIGNED(stateSubDiff);
	ref.mW[15] += stateSubDiff;
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){ref.mW[15] -= stateSubDiff;return false;}
	ref.mA[16] += stateSubDiff;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}

bool mod_15(SHA1& ref, u32 a20XorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (baseMsg.a[20] ^ a20XorDiff) - baseMsg.a[20];
	stateSubDiff = SHIFT_RIGHT20_SIGNED(stateSubDiff);
	ref.mW[15] += stateSubDiff;
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){ref.mW[15] -= stateSubDiff;return false;}
	ref.mA[16] += stateSubDiff;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}

bool mod_15v1(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg)
{
	u32 stateSubDiff = (ref.mW[15] ^ xorDiff) - ref.mW[15];
	if(wOrState){
		stateSubDiff = -stateSubDiff;
	}
	ref.mW[15] += stateSubDiff;
	if((ref.mW[15] ^ baseMsg.w[15]) & mM[R15]){ref.mW[15] -= stateSubDiff;return false;}
	ref.mA[16] += stateSubDiff;
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	return true;
}

bool corrAtRound15(SHA1& ref, u32 d, int equationToTest)
{
	u32 w15 = ref.mW[15]; u32 a16 = ref.mA[16]; u32 a30_16 = ref.mA30[16];
	ref.mW[15] += d;
	if((ref.mW[15] ^ m.w[15]) & mM[R15]){ref.mW[15] -= d; return false;}
	ref.mA[16] += d;
	if((ref.mA[16] ^ m.a[16]) & 0x28000001){ref.mW[15] -= d;ref.mA[16] -= d;return false;}
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	int conf = updateAndTest(ref);
	if(conf > equationToTest) {ref.mFirstUnsatisfiedEquation = conf; return true;}
	ref.mW[15] = w15; ref.mA[16] = a16; ref.mA30[16] = a30_16;
	return false;
}

// 5, 6, 56, 568, 8, 68, 58
bool allCorrectionsRound15(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int equToTest), int equationToTest)
{
	u32 d;
	u32 a20 = ref.mA[20];
	//	u32 a20 = m.a[20];
	u32 d8 = (a20 & B28) ? MB8 : B8;
	if(corrAtRound15(ref, d8, equationToTest))return true;
	u32 d6 = (a20 & B26) ? MB6 : B6;
	if(corrAtRound15(ref, d6, equationToTest))return true;
	u32 d5 = (a20 & B25) ? MB5 : B5;
	if(corrAtRound15(ref, d5, equationToTest))return true;
	d = d5 + d6;
	if(corrAtRound15(ref, d, equationToTest))return true;
	d = d5 + d6 + d8;
	if(corrAtRound15(ref, d, equationToTest))return true;
	d = d5 + d8;
	if(corrAtRound15(ref, d, equationToTest))return true;
	d = d6 + d8;
	if(corrAtRound15(ref, d, equationToTest))return true;
	return false;
}


bool corrAtRound15(SHA1& ref, u32 d, int equationToTest, int& conformance)
{
	u32 w15 = ref.mW[15]; u32 a16 = ref.mA[16]; u32 a30_16 = ref.mA30[16];
	ref.mW[15] += d;
	if((ref.mW[15] ^ m.w[15]) & mM[R15]){ref.mW[15] -= d; return false;}
	ref.mA[16] += d;
	if((ref.mA[16] ^ m.a[16]) & 0x28000001){ref.mW[15] -= d;ref.mA[16] -= d;return false;}
	ref.mA30[16] = ROTATE(ref.mA[16], 30);
	conformance = updateAndTest(ref);
	if(conformance > equationToTest) {ref.mFirstUnsatisfiedEquation = conformance; return true;}
	ref.mW[15] = w15; ref.mA[16] = a16; ref.mA30[16] = a30_16;
	return false;
}

// 5, 6, 56, 568, 8, 68, 58
bool allCorrectionsRound15(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int equToTest, int& conf), int equationToTest, int& conformance)
{
	u32 d;
	u32 a20 = ref.mA[20];
	//	u32 a20 = m.a[20];
	u32 d8 = (a20 & B28) ? MB8 : B8;
	if(corrAtRound15(ref, d8, equationToTest, conformance))return true;
	u32 d6 = (a20 & B26) ? MB6 : B6;
	if(corrAtRound15(ref, d6, equationToTest, conformance))return true;
	u32 d5 = (a20 & B25) ? MB5 : B5;
	if(corrAtRound15(ref, d5, equationToTest, conformance))return true;
	d = d5 + d6;
	if(corrAtRound15(ref, d, equationToTest, conformance))return true;
	d = d5 + d6 + d8;
	if(corrAtRound15(ref, d, equationToTest, conformance))return true;
	d = d5 + d8;
	if(corrAtRound15(ref, d, equationToTest, conformance))return true;
	d = d6 + d8;
	if(corrAtRound15(ref, d, equationToTest, conformance))return true;
	return false;
}
