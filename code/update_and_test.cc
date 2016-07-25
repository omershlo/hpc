//  #define DEBUG

#include "solve.h"
#include "check_equations.h"

int updateAndTest(SHA1& ref, int roundToStart)
{
	switch(roundToStart){
	case 16:
		ref.mF[16] = F_00_19(ref.mA[15], ref.mA30[14], ref.mA30[13]);
		Xupdate(ref.mW[16], ref.mW[13], ref.mW[8], ref.mW[2], ref.mW[0]);
		ref.mA[17] = K_00_19 + ref.mW[16] + ROTATE(ref.mA[16], 5) + ref.mF[16] + ref.mA30[12];
		if(!(ref.mA[17] & B27)) return 71;//71
		ref.mA30[17] = ROTATE(ref.mA[17], 30);
	case 17:
		ref.mF[17] = F_00_19(ref.mA[16], ref.mA30[15], ref.mA30[14]);
		Xupdate(ref.mW[17], ref.mW[14], ref.mW[9], ref.mW[3], ref.mW[1]);
		ref.mA[18] = K_00_19 + ref.mW[17] + ROTATE(ref.mA[17], 5) + ref.mF[17] + ref.mA30[13];
		if(ref.mA[18] & B27)return 73;//73
		ref.mA30[18] = ROTATE(ref.mA[18], 30);
	case 18:
		ref.mF[18] = F_00_19(ref.mA[17], ref.mA30[16], ref.mA30[15]);
		Xupdate(ref.mW[18], ref.mW[15], ref.mW[10], ref.mW[4], ref.mW[2]);
		ref.mA[19] = K_00_19 + ref.mW[18] + ROTATE(ref.mA[18], 5) + ref.mF[18] + ref.mA30[14];
		if(ref.mA[19] & B29)return 78;//78
		ref.mA30[19] = ROTATE(ref.mA[19], 30);
	}
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
	return ref.mFirstUnsatisfiedEquation;
}

int updateAndTest(SHA1& ref)
{
	ref.mF[16] = F_00_19(ref.mA[15], ref.mA30[14], ref.mA30[13]);
	Xupdate(ref.mW[16], ref.mW[13], ref.mW[8], ref.mW[2], ref.mW[0]);
	ref.mA[17] = K_00_19 + ref.mW[16] + ROTATE(ref.mA[16], 5) + ref.mF[16] + ref.mA30[12];
	if(!(ref.mA[17] & B27)) return 71;//71
	ref.mA30[17] = ROTATE(ref.mA[17], 30);
	ref.mF[17] = F_00_19(ref.mA[16], ref.mA30[15], ref.mA30[14]);
	Xupdate(ref.mW[17], ref.mW[14], ref.mW[9], ref.mW[3], ref.mW[1]);
	ref.mA[18] = K_00_19 + ref.mW[17] + ROTATE(ref.mA[17], 5) + ref.mF[17] + ref.mA30[13];
	if(ref.mA[18] & B27)return 73;//73
	ref.mA30[18] = ROTATE(ref.mA[18], 30);
	ref.mF[18] = F_00_19(ref.mA[17], ref.mA30[16], ref.mA30[15]);
	Xupdate(ref.mW[18], ref.mW[15], ref.mW[10], ref.mW[4], ref.mW[2]);
	ref.mA[19] = K_00_19 + ref.mW[18] + ROTATE(ref.mA[18], 5) + ref.mF[18] + ref.mA30[14];
	if(ref.mA[19] & B29)return 78;//78
	ref.mA30[19] = ROTATE(ref.mA[19], 30);
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
	return ref.mFirstUnsatisfiedEquation;
}

