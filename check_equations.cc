#include "sha_utils.h"
#include "check_equations.h"


int c_compute_firstUnsatisfied(SHA1& ref, int start)
{
	for(int i = start; i < EQ_141; i++)
	{
		if(!c_check_single_equation(ref, c_equationList_all_no_aux[i])){
			ref.mFirstUnsatisfiedEquation = c_equationList_all_no_aux[i];
			return c_equationList_all_no_aux[i];
		}
	}
	return 142;
}

bool c_check_single_equation(SHA1& ref, int equationOrder)
{
	u32 b[4] = {0};
	bool condition[12];
	bool pass = false;
	switch(equationOrder)
	{
	case  12:
		b[0] = (ref.mA[7] & B9)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   17:
		b[0] = (ref.mA[7] & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   18:
		b[0] = (ref.mA[7] & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   21:
		b[0] = (ref.mA[8] & B9)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   22:
		b[0] = (ref.mA[8] & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   23:
		b[0] = (ref.mA[8] & B29)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   24:
		b[0] = (ref.mA[8] & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   25:
		b[0] = (ref.mA[8] & B31)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   26:
		b[0] = (ref.mA[9] & B1)?1:0;
		b[1] = (ref.mA[8] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   27:
		b[0] = (ref.mA[9] & B6)?1:0;
		b[1] = (ref.mA[8] & B6)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   28:
		b[0] = (ref.mA[9] & B26)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   29:
		b[0] = (ref.mA[9] & B27)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   30:
		b[0] = (ref.mA[9] & B28)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   31:
		b[0] = (ref.mA[9] & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   32:
		b[0] = (ref.mA[9] & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   33:
		b[0] = (ref.mA[9] & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   35:
		b[0] = (ref.mA[10] & B4)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   36:
		b[0] = (ref.mA[10] & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   37:
		b[0] = (ref.mA[10] & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   38:
		b[0] = (ref.mA[10] & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   39:
		b[0] = (ref.mA[10] & B31)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   40:
		b[0] = (ref.mA[10] & B1)?1:0;
		b[1] = (ref.mA[11] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   41:
		b[0] = (ref.mA[11] & B2)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   42:
		b[0] = (ref.mA[11] & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   43:
		b[0] = (ref.mA[11] & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   44:
		b[0] = (ref.mA[11] & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   45:
		b[0] = (ref.mA[12] & B2)?1:0;
		b[1] = (ref.mW[8] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   46:
		b[0] = (ref.mA[12] & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   47:
		b[0] = (ref.mA[12] & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case  49://142
		b[0] = (ref.mA[12] & B30)?1:0;
		b[1] = (ref.mA[11] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   50:
		b[0] = (ref.mA[12] & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   52:
		b[0] = (ref.mA[13] & B1)?1:0;
		b[1] = (ref.mA[12] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   53:
		b[0] = (ref.mA[13] & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   54:
		b[0] = (ref.mA[13] & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   55:
		b[0] = (ref.mA[13] & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   56:
		b[0] = (ref.mA[13] & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   57:
		b[0] = (ref.mA[14] & B26)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   58:
		b[0] = (ref.mA[14] & B27)?1:0;
		b[1] = (ref.mF[14] & B0)?1:0;
		b[2] = (ref.mW[14] & B0)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] )== 0);
		break;
	case   59:
		b[0] = (ref.mA[14] & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   60:
		b[0] = (ref.mA[14] & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   61:
		b[0] = (ref.mA[15] & B4)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   62:
		b[0] = (ref.mA[15] & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   63:
		b[0] = (ref.mA[15] & B27)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   64:
		b[0] = (ref.mA[15] & B29)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   65:
		b[0] = (ref.mA[15] & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   66:
		b[0] = (ref.mA[16] & B0)?1:0;
		b[1] = (ref.mA[15] & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   67:
		b[0] = (ref.mA[16] & B27)?1:0;
		b[1] = (ref.mW[14] & B26)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   68:
		b[0] = (ref.mA[17] & B1)?1:0;
		b[1] = (ref.mA[16] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   69://aux
		b[0] = (ref.mA[16] & B3)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   70:
		b[0] = (ref.mA[16] & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   71:
		b[0] = (ref.mA[17] & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   72:
		b[0] = (ref.mA[17] & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   73:
		b[0] = (ref.mA[18] & B27)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   74:
		b[0] = (ref.mA[18] & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   75:
		b[0] = (ref.mA[18] & B31)?1:0;
		b[1] = (ref.mW[18] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   76:
		b[0] = (ref.mA[19] & B0)?1:0;
		b[1] = (ref.mA[20] & B0)?1:0;
		b[2] = (ref.mW[22] & B30)?1:0;//1
		b[3] = (ref.mW[20] & B29)?1:0;//0
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case   77:
		b[0] = (ref.mF[20] & B28)?1:0;
		b[1] = (ref.mW[20] & B28)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   78:
		b[0] = (ref.mA[19] & B29)?1:0;//0
		b[1] = (ref.mW[19] & B2)?1:0;//0
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   79:
		b[0] = (ref.mF[21] & B27)?1:0;
		b[1] = (ref.mW[21] & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   80:
		b[0] = (ref.mF[21] & B29)?1:0;
		b[1] = (ref.mW[21] & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   81:
		b[0] = (ref.mA[20] & B31)?1:0;
		b[1] = (ref.mW[20] & B4)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   82:
		b[0] = (ref.mF[22] & B27)?1:0;//=0
		b[1] = (ref.mW[22] & B27)?1:0;//=0
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   83:
		b[0] = (ref.mF[22] & B29)?1:0;
		b[1] = (ref.mW[18] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   84:
		b[0] = (ref.mA[20] & B30)?1:0;
		b[1] = (ref.mA[22] & B28)?1:0;
		b[2] = (ref.mW[20] & B29)?1:0;
		b[3] = (ref.mW[23] & B27)?1:0;
		condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!condition[3])
			break;
		b[0] = (ref.mA[21] & B30)?1:0;
		b[1] = (ref.mW[20] & B29)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 1);
		b[0] = (ref.mA[21] & B31)?1:0;
		b[1] = (ref.mW[20] & B29)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 1);
		b[0] = (ref.mW[23] & B27)?1:0;
		b[1] = (ref.mF[23] & B29)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]))
		{
			pass = true;
		}
		break;
	case   85:
		b[0] = (ref.mA[22] & B31)?1:0;
		b[1] = (ref.mW[22] & B4)?1:0;//(ref.mW[22] & B4)=0 => (ref.mA[22] & B31) = 1
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   86:
		b[0] = (ref.mA[22] & B30)?1:0;
		b[1] = (ref.mA[23] & B28)?1:0;
		b[2] = (ref.mW[20] & B29)?1:0;
		b[3] = (ref.mW[24] & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case   87:
		b[0] = (ref.mA[23] & B29)?1:0;
		b[1] = (ref.mW[22] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   88:
		pass = ((ref.mA[23] >> 27) ^ ref.mW[23]) & B4;
		// b[0] = (ref.mA[23] & B31)?1:0;
		// b[1] = (ref.mW[23] & B4)?1:0;
		// pass = ((b[0] ^ b[1] )== 1);
		break;
	case   89:
		ref.mA[24] = K_20_39 + ref.mW[23] + ROTATE(ref.mA[23], 5) + ref.mF[23] + ref.mA30[19];
		ref.mF[24] = F_20_39(ref.mA[23], ref.mA30[22], ref.mA30[21]);
		ref.mA30[23] = ROTATE(ref.mA[23], 30);
		ref.mF[25] = F_20_39(ref.mA[24], ref.mA30[23], ref.mA30[22]);
		Xupdate(ref.mW[25], ref.mW[22], ref.mW[17], ref.mW[11], ref.mW[9]);
		pass = (ref.mF[25] ^ ref.mW[25]) & B27;
		// b[0] = (ref.mF[25] & B27)?1:0;
		// b[1] = (ref.mW[25] & B27)?1:0;
		// pass = ((b[0] ^ b[1] )== 1);
		break;
	case   90:
		pass = ((ref.mA[24] >> 27) ^ ref.mW[24]) & B4;
		break;
	case   91:
		ref.mA30[24] = ROTATE(ref.mA[24], 30);
		ref.mA[25] = K_20_39 + ref.mW[24] + ROTATE(ref.mA[24], 5) + ref.mF[24] + ref.mA30[20];
		ref.mF[26] = F_20_39(ref.mA[25], ref.mA30[24], ref.mA30[23]);
		pass = (ref.mF[26] ^ ref.mW[26]) & B27;
		break;
	case   92:
		pass = (ref.mA[25] ^ ref.mW[24]) & B29;
		break;
	case   93:
		ref.mA[26] = K_20_39 + ref.mW[25] + ROTATE(ref.mA[25], 5) + ref.mF[25] + ref.mA30[21];
		ref.mA30[25] = ROTATE(ref.mA[25], 30);
		ref.mF[27] = F_20_39(ref.mA[26], ref.mA30[25], ref.mA30[24]);
		pass = (((ref.mW[22] >> 2) ^ ref.mF[27]) & B27) == 0;
		break;
	case   94:
		pass = (((ref.mF[27] >> 25) ^ ref.mW[23]) & B4) == 0;
		break;
	case   95:
		ref.mA30[26] = ROTATE(ref.mA[26], 30);
		Xupdate(ref.mW[26], ref.mW[23], ref.mW[18], ref.mW[12], ref.mW[10]);
		Xupdate(ref.mW[27], ref.mW[24], ref.mW[19], ref.mW[13], ref.mW[11]);
		Xupdate(ref.mW[28], ref.mW[25], ref.mW[20], ref.mW[14], ref.mW[12]);
		Xupdate(ref.mW[29], ref.mW[26], ref.mW[21], ref.mW[15], ref.mW[13]);
		Xupdate(ref.mW[30], ref.mW[27], ref.mW[22], ref.mW[16], ref.mW[14]);
		ref.mA[27] = K_20_39 + ref.mW[26] + ROTATE(ref.mA[26], 5) + ref.mF[26] + ref.mA30[22];
		ref.mA30[27] = ROTATE(ref.mA[27], 30);
		ref.mF[28] = F_20_39(ref.mA[27], ref.mA30[26], ref.mA30[25]);
		ref.mA[28] = K_20_39 + ref.mW[27] + ROTATE(ref.mA[27], 5) + ref.mF[27] + ref.mA30[23];
		ref.mA30[28] = ROTATE(ref.mA[28], 30);
		ref.mF[29] = F_20_39(ref.mA[28], ref.mA30[27], ref.mA30[26]);
		ref.mA[29] = K_20_39 + ref.mW[28] + ROTATE(ref.mA[28], 5) + ref.mF[28] + ref.mA30[24];
		ref.mF[30] = F_20_39(ref.mA[29], ref.mA30[28], ref.mA30[27]);
		if((ref.mA[27] ^ ref.mW[26]) & B29){
			pass = true;
			break;
		}
		else
		{
			if(
					(((((ref.mW[26] >> 29) ^ (ref.mW[29] >> 2) ^ ref.mA[26] ^ ref.mA[25]) & B0) == 0)/*c3*/&&
							((((ref.mA[26] >> 2) ^ (ref.mW[26] >> 1) ^ (ref.mW[24] >> 1) ^ ref.mA[28]) & B28) == 0)/*c5*/&&
							((((ref.mA[28] >> 3) ^ (ref.mW[26] >> 2) ^ (ref.mA[29] >> 1) ^ ref.mW[30]) & B27) == 0))/*c7*/
							&&
							(
									(((ref.mA[27] >> 1) ^ ref.mW[26]) & B29)/*c1*/ ||
									(
											(((ref.mA[27] >> 2) ^ ref.mW[26]) & B29)/*c2*/&&
											((((ref.mF[28] >> 29) ^ ref.mW[29]) & B2) == 0)/*c4*/&&
											((ref.mW[24] ^ ref.mF[29]) & B29)/*c6*/&&
											(((ref.mF[30] >> 2) ^ ref.mW[30]) & B27)/*c8*/
									)
							)
			)
			{
				pass = true;
				break;
			}
		}
		pass = false;
		break;
	case   96:
		pass = ((ref.mW[30] >> 30) ^ (ref.mW[28] >> 30) ^ ref.mA[28] ^ ref.mA[27]) & B0;
		break;
	case   97:
		pass = ((ref.mA[29] >> 27) ^ ref.mW[29]) & B2;
		break;
	case   98:
		ref.mA30[29] = ROTATE(ref.mA[29], 30);
		ref.mA[30] = K_20_39 + ref.mW[29] + ROTATE(ref.mA[29], 5) + ref.mF[29] + ref.mA30[25];
		ref.mF[31] = F_20_39(ref.mA[30], ref.mA30[29], ref.mA30[28]);
		ref.mA[31] = K_20_39 + ref.mW[30] + ROTATE(ref.mA[30], 5) + ref.mF[30] + ref.mA30[26];
		ref.mA30[30] = ROTATE(ref.mA[30], 30);
		ref.mF[32] = F_20_39(ref.mA[31], ref.mA30[30], ref.mA30[29]);
		Xupdate(ref.mW[31], ref.mW[28], ref.mW[23], ref.mW[17], ref.mW[15]);
		Xupdate(ref.mW[32], ref.mW[29], ref.mW[24], ref.mW[18], ref.mW[16]);
		b[0] = (ref.mA[29] & B30)?1:0;
		b[1] = (ref.mW[28] & B30)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 0);
		b[0] = (ref.mA[29] & B31)?1:0;
		b[1] = (ref.mW[28] & B30)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 0);
		b[0] = (ref.mF[31] & B29)?1:0;
		b[1] = (ref.mW[31] & B28)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 0);
		b[0] = (ref.mF[32] & B29)?1:0;
		b[1] = (ref.mW[32] & B28)?1:0;
		condition[3] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]&&condition[3]))
		{
			pass = true;
		}
		break;
	case   99:
		b[0] = (ref.mA[25] & B31)?1:0;
		b[1] = (ref.mA[26] & B31)?1:0;
		b[2] = (ref.mW[29] & B2)?1:0;
		b[3] = (ref.mW[26] & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		break;
	case  100:
		b[0] = (ref.mF[28] & B27)?1:0;
		b[1] = (ref.mW[28] & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case  101:
		b[0] = (ref.mA[26] & B29)?1:0;
		b[1] = (ref.mA[28] & B27)?1:0;
		b[2] = (ref.mW[24] & B29)?1:0;
		b[3] = (ref.mW[26] & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		break;
	case  102:
		b[0] = (ref.mA[28] & B29)?1:0;
		b[1] = (ref.mA[29] & B27)?1:0;
		b[2] = (ref.mW[26] & B29)?1:0;
		b[3] = (ref.mW[30] & B27)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		break;
	case  103:
		b[0] = (ref.mA[28] & B31)?1:0;
		b[1] = (ref.mW[28] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  104:
		b[0] = (ref.mF[31] & B27)?1:0;
		b[1] = (ref.mW[26] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case  105:
		b[0] = (ref.mA[28] & B30)?1:0;
		b[1] = (ref.mA[30] & B28)?1:0;
		b[2] = (ref.mW[28] & B30)?1:0;
		b[3] = (ref.mW[31] & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case  106:
		ref.mA[32] = K_20_39 + ref.mW[31] + ROTATE(ref.mA[31], 5) + ref.mF[31] + ref.mA30[27];
		b[0] = (ref.mA[32] & B31)?1:0;
		b[1] = (ref.mW[32] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  107:
		b[0] = (ref.mF[32] & B27)?1:0;
		b[1] = (ref.mW[32] & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  108:
		b[0] = (ref.mW[32] & B28)?1:0;
		b[1] = (ref.mA[31] & B28)?1:0;
		b[2] = (ref.mA[30] & B30)?1:0;
		b[3] = (ref.mW[28] & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case  109:
		ref.mA[33] = K_20_39 + ref.mW[32] + ROTATE(ref.mA[32], 5) + ref.mF[32] + ref.mA30[28];
		c_compute_state(ref, 33);//a[34], w[33], f[33], a30[31]
		b[0] = (ref.mW[33] & B4)?1:0;
		b[1] = (ref.mA[33] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  110:
		c_compute_state(ref, 34);
		b[0] = (ref.mW[34] & B29)?1:0;
		b[1] = (ref.mF[34] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  111:
		c_compute_state(ref, 35);
		c_compute_state(ref, 36);
		b[0] = (ref.mW[32] & B4)?1:0;
		b[1] = (ref.mF[36] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case  112:
		c_compute_state(ref, 37);
		c_compute_state(ref, 38);
		c_compute_state(ref, 39);
		b[0] = (ref.mA[39] & B31)?1:0;
		b[1] = (ref.mW[39] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  113:
		b[0] = (ref.mA[38] & B1)?1:0;
		b[1] = (ref.mA[37] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  114:
		c_compute_state(ref, 40);
		c_compute_state(ref, 41);
		b[0] = (ref.mA[41] & B31)?1:0;
		b[1] = (ref.mW[41] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  115:
		b[0] = (ref.mA[40] & B29)?1:0;
		b[1] = (ref.mA[38] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  116:
		b[0] = (ref.mA[41] & B29)?1:0;
		b[1] = (ref.mA[40] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  117:
		b[0] = (ref.mA[40] & B1)?1:0;
		b[1] = (ref.mA[39] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  118:
		c_compute_state(ref, 42);
		c_compute_state(ref, 43);
		b[0] = (ref.mA[43] & B31)?1:0;
		b[1] = (ref.mW[43] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  119:
		b[0] = (ref.mA[42] & B29)?1:0;
		b[1] = (ref.mA[40] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  120:
		b[0] = (ref.mA[43] & B29)?1:0;
		b[1] = (ref.mA[42] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  121:
		b[0] = (ref.mA[42] & B1)?1:0;
		b[1] = (ref.mA[41] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  122:
		c_compute_state(ref, 44);
		b[0] = (ref.mA[45] & B30)?1:0;
		b[1] = (ref.mW[44] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  123:
		b[0] = (ref.mA[44] & B29)?1:0;
		b[1] = (ref.mA[42] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  124:
		b[0] = (ref.mA[45] & B29)?1:0;
		b[1] = (ref.mA[44] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  125:
		b[0] = (ref.mA[44] & B0)?1:0;
		b[1] = (ref.mA[43] & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  126:
		c_compute_state(ref, 45);
		b[0] = (ref.mA[46] & B28)?1:0;
		b[1] = (ref.mA[44] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  127:
		c_compute_state(ref, 46);
		c_compute_state(ref, 47);
		c_compute_state(ref, 48);
		b[0] = (ref.mA[48] & B31)?1:0;
		b[1] = (ref.mW[48] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  128:
		b[0] = (ref.mA[47] & B28)?1:0;
		b[1] = (ref.mA[46] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  129:
		b[0] = (ref.mA[47] & B1)?1:0;
		b[1] = (ref.mA[46] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  130:
		b[0] = (ref.mA[49] & B29)?1:0;
		b[1] = (ref.mA[47] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  131:
		c_compute_state(ref, 49);
		b[0] = (ref.mA[50] & B29)?1:0;
		b[1] = (ref.mA[49] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  132:
		c_compute_state(ref, 50);
		c_compute_state(ref, 51);
		c_compute_state(ref, 52);
		c_compute_state(ref, 53);
		b[0] = (ref.mA[53] & B31)?1:0;
		b[1] = (ref.mW[53] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  133:
		b[0] = (ref.mA[52] & B1)?1:0;
		b[1] = (ref.mA[51] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  134:
		b[0] = (ref.mA[54] & B29)?1:0;
		b[1] = (ref.mA[52] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  135:
		c_compute_state(ref, 54);
		b[0] = (ref.mA[55] & B29)?1:0;
		b[1] = (ref.mA[54] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  136:
		c_compute_state(ref, 55);
		c_compute_state(ref, 56);
		c_compute_state(ref, 57);
		c_compute_state(ref, 58);
		c_compute_state(ref, 59);
		b[0] = (ref.mA[59] & B31)?1:0;
		b[1] = (ref.mW[59] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  137:
		c_compute_state(ref, 60);
		b[0] = (ref.mA[61] & B31)?1:0;
		b[1] = (ref.mW[61] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  138:
		c_compute_state(ref, 61);
		b[0] = (ref.mW[61] & B29)?1:0;
		b[1] = (ref.mF[61] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  139:
		c_compute_state(ref, 62);
		b[0] = (ref.mW[62] & B29)?1:0;
		b[1] = (ref.mF[62] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  140:
		c_compute_state(ref, 63);
		b[0] = (ref.mW[59] & B4)?1:0;
		b[1] = (ref.mF[63] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case 141:
		c_compute_state(ref, 64);
		b[0] = (ref.mW[64] & B29)?1:0;
		b[1] = (ref.mF[64] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case 1405:
		b[0] = (ref.mW[14] & B5)?1:0;
		b[1] = (ref.mA[15] & B5)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	default:
		printf("equationOrder = %d\n",equationOrder);
		rs_pause();
	}
	return pass;
}

void c_check_conformance(SHA1 &ref, int start)
{
	u32 b[4] = {0};
	bool condition[12];
	bool pass = false;
	int firstNonConformance = 0;
	int weightInWindow = 0;
	int weightBitMask = 0;
	switch(start)
	{
	case   36:
		b[0] = (ref.mA[10] & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 36; return;}
	case   37:
		b[0] = (ref.mA[10] & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 37; return;}
	case   38:
		b[0] = (ref.mA[10] & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 38; return;}
	case   39:
		b[0] = (ref.mA[10] & B31)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 39; return;}
	case   40:
		b[0] = (ref.mA[10] & B1)?1:0;
		b[1] = (ref.mA[11] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 40; return;}
	case   41:
		b[0] = (ref.mA[11] & B2)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 41; return;}
	case   42:
		b[0] = (ref.mA[11] & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 42; return;}
	case   43:
		b[0] = (ref.mA[11] & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 43; return;}
	case   44:
		b[0] = (ref.mA[11] & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 44; return;}
	case   45:
		b[0] = (ref.mA[12] & B2)?1:0;
		b[1] = (ref.mW[8] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 45; return;}
	case   46:
		b[0] = (ref.mA[12] & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 46; return;}
	case   47:
		b[0] = (ref.mA[12] & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 47; return;}
	case  49://142
		b[0] = (ref.mA[12] & B30)?1:0;
		b[1] = (ref.mA[11] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 49; return;}
	case   50:
		b[0] = (ref.mA[12] & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 50; return;}
	case   52:
		b[0] = (ref.mA[13] & B1)?1:0;
		b[1] = (ref.mA[12] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 52; return;}
	case   53:
		b[0] = (ref.mA[13] & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 53; return;}
	case   54:
		b[0] = (ref.mA[13] & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 54; return;}
	case   55:
		b[0] = (ref.mA[13] & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 55; return;}
	case   56:
		b[0] = (ref.mA[13] & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 56; return;}
	case   57:
		b[0] = (ref.mA[14] & B26)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 57; return;}
	case   58:
		b[0] = (ref.mA[14] & B27)?1:0;
		b[1] = (F_00_19(ref.mA[13], ref.mA30[12], ref.mA30[11]) & B0)?1:0;
		b[2] = (ref.mW[14] & B0)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 58; return;}
	case   59:
		b[0] = (ref.mA[14] & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 59; return;}
	case   60:
		b[0] = (ref.mA[14] & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 60; return;}
	case   61://aux
		b[0] = (ref.mA[15] & B4)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 61; return;}
	case   62:
		b[0] = (ref.mA[15] & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 62; return;}
	case   63:
		b[0] = (ref.mA[15] & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 63; return;}
	case   64:
		b[0] = (ref.mA[15] & B29)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 64; return;}
	case   65:
		b[0] = (ref.mA[15] & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 65; return;}
	case   66:
		b[0] = (ref.mA[16] & B0)?1:0;
		b[1] = (ref.mA[15] & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 66; return;}
	case   67:
		b[0] = (ref.mA[16] & B27)?1:0;
		b[1] = (ref.mW[14] & B26)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 67; return;}
	case  68:
		b[0] = (ref.mA[17] & B1)?1:0;
		b[1] = (ref.mA[16] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 68; return;}
	case   69://aux condition
		b[0] = (ref.mA[16] & B3)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 69; return;}
	case   70:
		b[0] = (ref.mA[16] & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 70; return;}
	case   71:
		update_w_a_a30_00_19(ref, 16);                         //w[16] a[17] a30[14]
		b[0] = (ref.mA[17] & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 71; return;}
	case   72:
		b[0] = (ref.mA[17] & B30)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 72; return;}
	case   73:
		update_w_a_a30_00_19(ref, 17);                         //w[17] a[18] a30[15]
		b[0] = (ref.mA[18] & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 73; return;}
	case   74:
		b[0] = (ref.mA[18] & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 74; return;}
	case   75:
		updateW(ref, 18);                                       //w[18]

		b[0] = (ref.mA[18] & B31)?1:0;
		b[1] = (ref.mW[18] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 75; return;}
	case   76:
		update_a30(ref, 16);                                    //            a30[16]
		update_a_00_19(ref, 18);                                //      a[19]
		update_w_a_a30_00_19(ref, 19);                          //w[19] a[20] a30[17]
		updateW(ref, 20);                                       //w[20]
		updateW(ref, 21);                                       //w[21]
		updateW(ref, 22);                                       //w[22]

		b[0] = (ref.mA[19] & B0)?1:0;
		b[1] = (ref.mA[20] & B0)?1:0;
		b[2] = (ref.mW[22] & B30)?1:0;
		b[3] = (ref.mW[20] & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 76; return;}
	case   77:
		update_a30(ref, 18);                                    //              a30[18]
		b[0] = (f_20_39(ref, 20) & B28)?1:0;
		b[1] = (ref.mW[20] & B28)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 77; return;}
	case   78:
		b[0] = (ref.mA[19] & B29)?1:0;//0
		b[1] = (ref.mW[19] & B2)?1:0;//0
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 78; return;}
	case   79:
		update_a30(ref, 19);                                    //              a30[19]
		b[0] = (f_20_39(ref, 21) & B27)?1:0;
		b[1] = (ref.mW[21] & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 79; return;}
	case   80:
		b[0] = (f_20_39(ref, 21) & B29)?1:0;
		b[1] = (ref.mW[21] & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 80; return;}
	case   81:
		b[0] = (ref.mA[20] & B31)?1:0;//0
		b[1] = (ref.mW[20] & B4)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 81; return;}
	case   82:
		update_a30(ref, 20);                                    //              a30[20]
		update_a_20_39(ref, 20);                                //        a[21]
		b[0] = (f_20_39(ref, 22) & B27)?1:0;
		b[1] = (ref.mW[22] & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 82; return;}
	case   83:
		b[0] = (f_20_39(ref, 22) & B29)?1:0;
		b[1] = (ref.mW[18] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 83; return;}
	case   84:
		pass = false;
		update_a_20_39(ref, 21);                                //        a[22]
		update_a30(ref, 21);                                    //              a30[21]
		b[0] = (ref.mA[20] & B30)?1:0;
		b[1] = (ref.mA[22] & B28)?1:0;
		condition[3] = ((b[0] ^ b[1])== 0);
		b[0] = (ref.mA[21] & B30)?1:0;
		condition[0] = b[0]== 0;
		b[0] = (ref.mA[21] & B31)?1:0;
		condition[1] = b[0]== 0;
		b[1] = (f_20_39(ref, 23) & B29)?1:0;
		condition[2] = b[1]== 1;
		if(condition[3] && ((condition[0]&&condition[2]) || (!condition[0]&&condition[1])))
			pass = true;
		if(!pass){ref.mFirstUnsatisfiedEquation = 84; return;}
	case   85:
		b[0] = (ref.mA[22] & B31)?1:0;//1
		pass = (b[0] == 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 85; return;}
	case   86:
		update_a_20_39(ref, 22);                                //        a[23]
		updateW(ref, 23);                                       //w[23]
		updateW(ref, 24);                                       //w[24]
		if(((ref.mA[22]>>2) ^ ref.mA[23] ^ ref.mW[24]) & B28){ref.mFirstUnsatisfiedEquation = 86; return;}
	case   87:
		if((ref.mA[23] & B29)){ref.mFirstUnsatisfiedEquation = 87; return;}
	case   88:
		if(!(ref.mA[23] & B31)){ref.mFirstUnsatisfiedEquation = 88; return;}
	case   89://NEUTRAL_TRESHOLD
		update_a30(ref, 22);                                    //              a30[22]
		update_a30(ref, 23);                                    //              a30[23]
		update_a_20_39(ref, 23);                                //        a[24]
		updateW(ref, 25);                                       // w[25]
		pass = (f_20_39(ref, 25) ^ ref.mW[25]) & B27;
		if(!pass){ref.mFirstUnsatisfiedEquation = 89; return;}
	case   90://WEIGHT_MINIMIZATION_START
		pass = ((ref.mA[24] >> 27) ^ ref.mW[24]) & B4;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[0];
			firstNonConformance = 90;
		}
	case   91:
		update_a30(ref, 24);                                    //              a30[24]
		update_a_20_39(ref, 24);                                //        a[25]
		updateW(ref, 26);                                       // w[26]
		pass = (f_20_39(ref, 26) ^ ref.mW[26]) & B27;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[1];
			if(!firstNonConformance)
				firstNonConformance =   91;
		}
	case   92:
		pass = (ref.mA[25] ^ ref.mW[24]) & B29;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[2];
			if(!firstNonConformance)
				firstNonConformance =   92;
		}
	case   93:
		update_a30(ref, 25);                                    //              a30[25]
		update_a_20_39(ref, 25);                                //        a[26]
		pass = (((ref.mW[22] >> 2) ^ f_20_39(ref, 27)) & B27) == 0;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[3];
			if(!firstNonConformance)
				firstNonConformance =   93;
		}
	case   94:
		pass = (((f_20_39(ref, 27) >> 25) ^ ref.mW[23]) & B4) == 0;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[4];
			if(!firstNonConformance)
				firstNonConformance =   94;
		}
	case   95:
		pass = false;
		update_a_20_39(ref, 26);                                //        a[27]
		updateW(ref, 27);                                       // w[27]
		update_a_20_39(ref, 27);                                //        a[28]
		update_w_a_a30_20_39(ref, 28);                          // w[28]  a[29] a30[26]
		update_a30(ref, 27);                                    //              a30[27]
		update_a30(ref, 28);                                    //              a30[28]
		updateW(ref, 29);                                       // w[29]
		updateW(ref, 30);                                       // w[30]
		if((ref.mA[27] ^ ref.mW[26]) & B29){
			pass = true;
		}
		else
		{
			if(
					(((((ref.mW[26] >> 29) ^ (ref.mW[29] >> 2) ^ ref.mA[26] ^ ref.mA[25]) & B0) == 0)/*c3*/&&
							((((ref.mA[26] >> 2) ^ (ref.mW[26] >> 1) ^ (ref.mW[24] >> 1) ^ ref.mA[28]) & B28) == 0)/*c5*/&&
							((((ref.mA[28] >> 3) ^ (ref.mW[26] >> 2) ^ (ref.mA[29] >> 1) ^ ref.mW[30]) & B27) == 0))/*c7*/
							&&
							(
									(((ref.mA[27] >> 1) ^ ref.mW[26]) & B29)/*c1*/ ||
									(
											(((ref.mA[27] >> 2) ^ ref.mW[26]) & B29)/*c2*/&&
											((((f_20_39(ref, 28) >> 29) ^ ref.mW[29]) & B2) == 0)/*c4*/&&
											((ref.mW[24] ^ f_20_39(ref, 29)) & B29)/*c6*/&&
											(((f_20_39(ref, 30) >> 2) ^ ref.mW[30]) & B27)/*c8*/
									)
							)
			)
			{
				pass = true;
			}
		}
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[5];
			if(!firstNonConformance)
				firstNonConformance =   95;
		}
	case   96:
		pass = ((ref.mW[30] >> 30) ^ (ref.mW[28] >> 30) ^ ref.mA[28] ^ ref.mA[27]) & B0;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[6];
			if(!firstNonConformance)
				firstNonConformance =   96;
		}
	case   97://WEIGHT_MINIMIZATION_END and LAST_EQUATION_TO_CORRECT
		pass = ((ref.mA[29] >> 27) ^ ref.mW[29]) & B2;
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[7];
			if(!firstNonConformance)
				firstNonConformance = 97;
		}
	case   98:

		update_a30(ref, 29);                                    //              a30[29]
		update_a_20_39(ref, 29);                                //        a[30]
		update_a30(ref, 30);                                    //              a30[30]
		update_a_20_39(ref, 30);                                //        a[31]
		updateW(ref, 31);                                       // w[31]
		updateW(ref, 32);                                       // w[32]
		b[0] = (ref.mA[29] & B30)?1:0;
		b[1] = (ref.mW[28] & B30)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 0);
		b[0] = (ref.mA[29] & B31)?1:0;
		b[1] = (ref.mW[28] & B30)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_20_39(ref, 31) & B29)?1:0;
		b[1] = (ref.mW[31] & B28)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_20_39(ref, 32) & B29)?1:0;
		b[1] = (ref.mW[32] & B28)?1:0;
		condition[3] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]&&condition[3]))
		{
			pass = true;
		}
		else
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[8];
			if(!firstNonConformance)
				firstNonConformance = 98;
//			ref.mFirstUnsatisfiedEquation = 98; return;
		}
	case   99:
		b[0] = (ref.mA[25] & B31)?1:0;
		b[1] = (ref.mA[26] & B31)?1:0;
		b[2] = (ref.mW[29] & B2)?1:0;
		b[3] = (ref.mW[26] & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[9];
			if(!firstNonConformance)
				firstNonConformance = 99;
		}
//		if(!pass){ref.mFirstUnsatisfiedEquation = 99; return;}
	case  100:
		b[0] = (f_20_39(ref, 28) & B27)?1:0;
		b[1] = (ref.mW[28] & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[10];
			if(!firstNonConformance)
				firstNonConformance = 100;
		}
//		if(!pass){ref.mFirstUnsatisfiedEquation = 100; return;}
	case  101:
		b[0] = (ref.mA[26] & B29)?1:0;
		b[1] = (ref.mA[28] & B27)?1:0;
		b[2] = (ref.mW[24] & B29)?1:0;
		b[3] = (ref.mW[26] & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[11];
			if(!firstNonConformance)
				firstNonConformance = 101;
		}
//		if(!pass){ref.mFirstUnsatisfiedEquation = 101; return;}
	case  102:
		b[0] = (ref.mA[28] & B29)?1:0;
		b[1] = (ref.mA[29] & B27)?1:0;
		b[2] = (ref.mW[26] & B29)?1:0;
		b[3] = (ref.mW[30] & B27)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[12];
			if(!firstNonConformance)
				firstNonConformance = 102;
		}
//		if(!pass){ref.mFirstUnsatisfiedEquation = 102; return;}
	case  103:
		b[0] = (ref.mA[28] & B31)?1:0;
		b[1] = (ref.mW[28] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[13];
			if(!firstNonConformance)
				firstNonConformance = 103;
		}
//		if(!pass){ref.mFirstUnsatisfiedEquation = 103; return;}
	case  104:
		b[0] = (f_20_39(ref, 31) & B27)?1:0;
		b[1] = (ref.mW[26] & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[14];
			if(!firstNonConformance)
				firstNonConformance = 104;
		}
//		if(!pass){ref.mFirstUnsatisfiedEquation = 104; return;}
	case  105:
		b[0] = (ref.mA[28] & B30)?1:0;
		b[1] = (ref.mA[30] & B28)?1:0;
		b[2] = (ref.mW[28] & B30)?1:0;
		b[3] = (ref.mW[31] & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass)
		{
			weightInWindow++;
			weightBitMask |= BIT_BY_INDEX[15];
			if(!firstNonConformance)
				firstNonConformance = 105;
		}
		if(firstNonConformance)
		{
			ref.mWindowWeight = weightInWindow;
			ref.mWindowWeightMask = weightBitMask;
			ref.mFirstUnsatisfiedEquation = firstNonConformance;
			return;
		}
		ref.mWindowWeight = ref.mWindowWeightMask = 0;
//		if(!pass){ref.mFirstUnsatisfiedEquation = 105; return;}
	case  106:
		update_a_20_39(ref, 31);                                      //       a[32]
		b[0] = (ref.mA[32] & B31)?1:0;
		b[1] = (ref.mW[32] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 106; return;}
	case  107:
		b[0] = (f_20_39(ref, 32) & B27)?1:0;
		b[1] = (ref.mW[32] & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 107; return;}
	case  108:
		b[0] = (ref.mW[32] & B28)?1:0;
		b[1] = (ref.mA[31] & B28)?1:0;
		b[2] = (ref.mA[30] & B30)?1:0;
		b[3] = (ref.mW[28] & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 108; return;}
	case  109:
		update_a_20_39(ref, 32);                                      //       a[33]
		update_w_a_a30_20_39(ref, 33);                                // w[33] a[34] a30[31]
		b[0] = (ref.mW[33] & B4)?1:0;
		b[1] = (ref.mA[33] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 109; return;}
	case  110:
		update_w_a_a30_20_39(ref, 34);                                // w[34] a[35] a30[32]
		b[0] = (ref.mW[34] & B29)?1:0;
		b[1] = (f_20_39(ref, 34) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 110; return;}
	case  111:
		update_w_a_a30_20_39(ref, 35);
		update_w_a_a30_20_39(ref, 36);
		b[0] = (ref.mW[32] & B4)?1:0;
		b[1] = (f_20_39(ref, 36) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 111; return;}
	case  112:
		update_w_a_a30_20_39(ref, 37);
		update_w_a_a30_20_39(ref, 38);
		update_w_a_a30_20_39(ref, 39);
		b[0] = (ref.mA[39] & B31)?1:0;
		b[1] = (ref.mW[39] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 112; return;}
	case  113:
		b[0] = (ref.mA[38] & B1)?1:0;
		b[1] = (ref.mA[37] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 113; return;}
	case  114:
		update_w_a_a30_40_59(ref, 40);
		update_w_a_a30_40_59(ref, 41);
		b[0] = (ref.mA[41] & B31)?1:0;
		b[1] = (ref.mW[41] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 114; return;}
	case  115:
		b[0] = (ref.mA[40] & B29)?1:0;
		b[1] = (ref.mA[38] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 115; return;}
	case  116:
		b[0] = (ref.mA[41] & B29)?1:0;
		b[1] = (ref.mA[40] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 116; return;}
	case  117:
		b[0] = (ref.mA[40] & B1)?1:0;
		b[1] = (ref.mA[39] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 117; return;}
	case  118:
		update_w_a_a30_40_59(ref, 42);
		update_w_a_a30_40_59(ref, 43);
		b[0] = (ref.mA[43] & B31)?1:0;
		b[1] = (ref.mW[43] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 118; return;}
	case  119:
		b[0] = (ref.mA[42] & B29)?1:0;
		b[1] = (ref.mA[40] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 119; return;}
	case  120:
		b[0] = (ref.mA[43] & B29)?1:0;
		b[1] = (ref.mA[42] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 120; return;}
	case  121:
		b[0] = (ref.mA[42] & B1)?1:0;
		b[1] = (ref.mA[41] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 121; return;}
	case  122:
		update_w_a_a30_40_59(ref, 44);
		b[0] = (ref.mA[45] & B30)?1:0;
		b[1] = (ref.mW[44] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 122; return;}
	case  123:
		b[0] = (ref.mA[44] & B29)?1:0;
		b[1] = (ref.mA[42] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 123; return;}
	case  124:
		b[0] = (ref.mA[45] & B29)?1:0;
		b[1] = (ref.mA[44] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 124; return;}
	case  125:
		b[0] = (ref.mA[44] & B0)?1:0;
		b[1] = (ref.mA[43] & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 125; return;}
	case  126:
		update_w_a_a30_40_59(ref, 45);
		b[0] = (ref.mA[46] & B28)?1:0;
		b[1] = (ref.mA[44] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 126; return;}
	case  127:
		update_w_a_a30_40_59(ref, 46);
		update_w_a_a30_40_59(ref, 47);
		update_w_a_a30_40_59(ref, 48);
		b[0] = (ref.mA[48] & B31)?1:0;
		b[1] = (ref.mW[48] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 127; return;}
	case  128:
		b[0] = (ref.mA[47] & B28)?1:0;
		b[1] = (ref.mA[46] & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 128; return;}
	case  129:
		b[0] = (ref.mA[47] & B1)?1:0;
		b[1] = (ref.mA[46] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 129; return;}
	case  130:
		b[0] = (ref.mA[49] & B29)?1:0;
		b[1] = (ref.mA[47] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 130; return;}
	case  131:
		update_w_a_a30_40_59(ref, 49);
		b[0] = (ref.mA[50] & B29)?1:0;
		b[1] = (ref.mA[49] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 131; return;}
	case  132:
		update_w_a_a30_40_59(ref, 50);
		update_w_a_a30_40_59(ref, 51);
		update_w_a_a30_40_59(ref, 52);
		update_w_a_a30_40_59(ref, 53);
		b[0] = (ref.mA[53] & B31)?1:0;
		b[1] = (ref.mW[53] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 132; return;}
	case  133:
		b[0] = (ref.mA[52] & B1)?1:0;
		b[1] = (ref.mA[51] & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 133; return;}
	case  134:
		b[0] = (ref.mA[54] & B29)?1:0;
		b[1] = (ref.mA[52] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 134; return;}
	case  135:
		update_w_a_a30_40_59(ref, 54);
		b[0] = (ref.mA[55] & B29)?1:0;
		b[1] = (ref.mA[54] & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 135; return;}
	case  136:
		update_w_a_a30_40_59(ref, 55);
		update_w_a_a30_40_59(ref, 56);
		update_w_a_a30_40_59(ref, 57);
		update_w_a_a30_40_59(ref, 58);
		update_w_a_a30_40_59(ref, 59);

		b[0] = (ref.mA[59] & B31)?1:0;
		b[1] = (ref.mW[59] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 136; return;}
	case  137:
		update_w_a_a30_60_79(ref, 60);
		b[0] = (ref.mA[61] & B31)?1:0;
		b[1] = (ref.mW[61] & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 137; return;}
	case  138:
		update_w_a_a30_60_79(ref, 61);
		b[0] = (ref.mW[61] & B29)?1:0;
		b[1] = (f_20_39(ref, 61) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 138; return;}
	case  139:
		update_w_a_a30_60_79(ref, 62);
		b[0] = (ref.mW[62] & B29)?1:0;
		b[1] = (f_20_39(ref, 62) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 139; return;}
	case  140:
		update_w_a_a30_60_79(ref, 63);
		b[0] = (ref.mW[59] & B4)?1:0;
		b[1] = (f_20_39(ref, 63) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){ref.mFirstUnsatisfiedEquation = 140; return;}
	case  141:
		update_w_a_a30_60_79(ref, 64);
		b[0] = (ref.mW[64] & B29)?1:0;
		b[1] = (f_20_39(ref, 64) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){ref.mFirstUnsatisfiedEquation = 141; return;}
	}
	ref.mFirstUnsatisfiedEquation = 142;
	return;
}
