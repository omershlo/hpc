#include "sha1.h"
#include "sha_utils.h"
#include "CorrectionSet.h"
//check_neutral() checks that the message is neutral up to (but not include) equationToCorrectIndex
int SHA1::apply_single_correction_and_check_neutral(SHA1 &mod, const correctionSet correction, const int lastRoundToTest)
{
	int equationToCorrect = firstUnsatisfiedEquation_getter()>98 ? 98 : firstUnsatisfiedEquation_getter();
	bool pass = false;
	int nc = (int)correction.nl;
	int firstcorr = 0;
	mod = *this;

	for(int i = 0; i < nc - 1; i++)
	{
		if(i==0)
			firstcorr = correction.wb[i].wbnl.word;
		else if(firstcorr > correction.wb[i].wbnl.word)
			firstcorr = correction.wb[i].wbnl.word;
		disturb_and_correct(mod, correction.wb[i].wbnl);
	}
	if(nc)
	{
		//firstcorr identifies if a wbset has more than one wbcorrnl
		pass = disturb_correct_and_test(mod, correction.wb[correction.nl - 1].wbnl, firstcorr, equationToCorrect, lastRoundToTest);
	}
	if(correction.l)
	{
		pass = disturb_correct_and_test_linear(mod, correction.wb[0].wbl, equationToCorrect, lastRoundToTest);
	}
	if(pass)
	{
		return mod.firstUnsatisfiedEquation_getter();
	}
	else
		return 0;
}

int SHA1::disturb_correct_and_test_linear(SHA1 &mod, const linearCorrection &linearCorrection, int const equationToCorrect, const int lastRoundToTest)
{
	int  lowestWord = 5;
	int  lowestBit = 0;
	int n = linearCorrection.n;//the number of wb's to complement
	int w = 0;
	int bit = 0;
	const uint32_t *stateMask = STATE_MASK_POINTER[equationToCorrect - MASK_POINTER_OFFSET];
	switch(n)
	{
	case 3:
		w = linearCorrection.wordc;
		bit = linearCorrection.bitc;
		mod.w_setter(w) ^= BIT_BY_INDEX[bit];
		lowestWord = w;
		lowestBit = bit;
	case 2:
		w = linearCorrection.wordb;
		bit = linearCorrection.bitb;
		mod.w_setter(w) ^= BIT_BY_INDEX[bit];
		if(n==2)
		{
			lowestWord = w;
			lowestBit = bit;
		}
		w = linearCorrection.worda;
		bit = linearCorrection.bita;
		mod.w_setter(w) ^= BIT_BY_INDEX[bit];
		if((w < lowestWord) || ((w == lowestWord) && (bit < lowestBit)))
		{
			lowestWord = w;
			lowestBit = bit;
		}
		break;
	}
	//mod.updatedToRound_setter() = lowestWord -1;
	for(int i = lowestWord; i<=lastRoundToTest; i++)
	{
		if((mod.a_getter(i+1) ^ a_getter(i+1)) & stateMask[i-5])
		{
			return false;
		}
//TODO:check if we ever enter the following condition
		if((i == 11) && (equationToCorrect > 49) && !mod.check_single_equation_by_order(49))
		{
			return false;
		}
	}
	if(!mod.check_single_equation_by_order(equationToCorrect))
	{
		return false;
	}
	return equationToCorrect;
}

void SHA1::apply_disturbance(const nonLinearCorrection &x)
{
	int r = x.word;
	u32 correction = BIT_BY_INDEX[x.bit];
	u32 word;
	u32 bit;
	switch(x.carry)
	{
	case 0:// no carry in w[i][j]
		word = w_getter(r);
		w_setter(r) -= (word & BIT_BY_INDEX[x.bit]) ? correction : -correction;
		break;
	case 1://no carry in w[i+1][j+5]
		word = w_getter(r + 1);
		w_setter(r) -= (word & BIT_BY_INDEX[x.bit + 5]) ? -correction : correction;
		break;
	case 2://no carry in a[i+1][j]
		word = a_getter(r + 1);
		w_setter(r) -= (word & BIT_BY_INDEX[x.bit]) ? correction : -correction;
		break;
	case 3://a carry in a[i+1][j]
		word = a_getter(r + 1);
		bit = BIT_BY_INDEX[x.bit];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	case 4://no carry in a[i+2][j+5]
		word = a_getter(r + 2);
		bit = BIT_BY_INDEX[x.bit + 5];
		w_setter(r) -= (word & bit) ? correction : -correction;
		break;
	case 5://a carry in a[i+2][j+5]
		word = a_getter(r + 2);
		bit = BIT_BY_INDEX[x.bit + 5];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	case 6://no carry in a[i+3][j+10]
		word = a_getter(r + 3);
		bit = BIT_BY_INDEX[x.bit + 10];
		w_setter(r) -= (word & bit) ? correction : -correction;
		break;
	case 7://a carry in a[i+3][j+10]
		word = a_getter(r + 3);
		bit = BIT_BY_INDEX[x.bit + 10];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	case 8://no carry in a[i+4][j+15]
		word = a_getter(r + 4);
		bit = BIT_BY_INDEX[x.bit + 15];
		w_setter(r) -= (word & bit) ? correction : -correction;
		break;
	case 9://a carry in a[i+4][j+15]
		word = a_getter(r + 4);
		bit = BIT_BY_INDEX[x.bit + 15];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	case 10://no carry in a[i+5][j+20]
		word = a_getter(r + 5);
		bit = BIT_BY_INDEX[(x.bit + 20) % 32];
		w_setter(r) -= (word & bit) ? correction : -correction;
		break;
	case 11://a carry in a[i+5][j+20]
		word = a_getter(r + 5);
		bit = BIT_BY_INDEX[(x.bit + 20) % 32];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	case 12://no carry in a[i+6][j+25]
		word = a_getter(r + 6);
		bit = BIT_BY_INDEX[(x.bit + 25) % 32];
		w_setter(r) -= (word & bit) ? correction : -correction;
		break;
	case 13://a carry in a[i+6][j+25]
		word = a_getter(r + 6);
		bit = BIT_BY_INDEX[(x.bit + 25) % 32];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	default:// a carry in w[i][j]
		word = w_getter(r);
		bit = BIT_BY_INDEX[x.bit];
		w_setter(r) -= (word & bit) ? -correction : correction;
		break;
	}
}

void SHA1::disturb_and_correct(SHA1 &mod, const nonLinearCorrection &x)
{
	int r = x.word;
	unsigned f_a5 = x.corr_a5;
	unsigned f_f = x.corr_f;
	unsigned f_a30 = 0;
	if(x.corr_a30) f_a30 = 0x10;
//TODO: need to save less base[...]
	uint32_t base[6];
	base[0] = f_a5&1?mod.a5_getter(r+1):0;
	base[1] = f_f&2?mod.f_getter(r+2):0;
	base[2] = f_f&4?mod.f_getter(r+3):0;
	base[3] = f_f&8?mod.f_getter(r+4):0;
	base[4] = f_a30&0x10?mod.a30_getter(r+1):0;
	base[5] = f_a5&0x20?mod.a5_getter(r+6):0;

	//the disturbance of the second order diff is applied by using the switch.
	//it is applied to w(r) as +(1<<bit) or -(1<<bit). The sign is determined according to
	//where we do not want a carry to occur.

	//apply a disturbance (2nd order)
	mod.apply_disturbance(x);
	// Apply corrections (2nd order) in accordance with the f_a30, f_f,
	// f_a5 flags. Since corrections are applied to each single
	// disturbance, only one of (f_a30 & 1), (f_f & 1), (f_a5 & 1) is
	// true

	if(f_a5 & 0x1)
	{
		mod.w_setter(r+1) -= mod.a5_getter(r+1) - base[0];
	}
	if(f_f & 0x2)
	{
		mod.w_setter(r+2) -= mod.f_getter(r+2) - base[1];
	}
	if(f_f & 0x4)
	{
		mod.w_setter(r+3) -= mod.f_getter(r+3) - base[2];
	}
	if(f_f & 0x8)
	{
		mod.w_setter(r+4) -= mod.f_getter(r+4) - base[3];
	}
	if(f_a30 & 0x10)
	{
		mod.w_setter(r+5) -= mod.a30_getter(r+1) - base[4];
	}
	if(f_a5 & 0X20)
	{
		mod.w_setter(r+6) -= mod.a5_getter(r+6) - base[5];
	}
}

//a single wb disturbance
bool SHA1::disturb_correct_and_test(SHA1 &mod, const nonLinearCorrection &x, const int firstcorr, const int equationToCorrect, const int lastRoundToTest)
{
//	fprintf(stderr, "%d %d\n", equationToCorrect,round);
	//	const int CONDITION_TO_TEST[7] = {68, 76, 84, 87, 96, 97, 98};
	int r = x.word;
	const u32 *stateMask = STATE_MASK_POINTER[equationToCorrect - MASK_POINTER_OFFSET];
	const u32 *functionMask = FUNCTION_MASK_POINTER[equationToCorrect - MASK_POINTER_OFFSET];
	//if firstcorr>0 then there are more then one wbcorrnl in the wbset
	if(firstcorr)
	{
		for(int i = firstcorr; i < r; i++)
		{
			if((w_getter(i) ^ mod.w_getter(i)) & messageMask[i])
			{
				return false;
			}
			if((a_getter(i+1) ^ mod.a_getter(i+1)) & stateMask[i-5])
			{
				return false;
			}
		}
	}
	uint32_t correction;
	unsigned  f_a5 = x.corr_a5;
	unsigned  f_f = x.corr_f;
	unsigned  f_a30 = 0;
	if(x.corr_a30)f_a30 = 0x10;
	uint32_t base[6];
	base[0] = f_a5&1?mod.a5_getter(r+1):0;
	base[1] = f_f&2?mod.f_getter(r+2):0;
	base[2] = f_f&4?mod.f_getter(r+3):0;
	base[3] = f_f&8?mod.f_getter(r+4):0;
	base[4] = f_a30&0x10?mod.a30_getter(r+1):0;
	base[5] = f_a5&0x20?mod.a5_getter(r+6):0;
	correction = BIT_BY_INDEX[(x.bit)];
//TODO: when w_setter is called with a_getter, updated2rnd is not consistent + need tp replace the code of while(...) in the switch and to use verify_state_access() instead
	//disturb
	mod.apply_disturbance(x);
	if (((w_getter(r) ^ mod.w_getter(r)) & messageMask[r]) || ((a_getter(r+1) ^ mod.a_getter(r+1)) & stateMask[r-5]))
	{
		mod.firstUnsatisfiedEquation_setter() = r;
		return false;
	}

	correction = 0;
	int i = 0;
	while((r < 16) && (f_a5 || f_f || f_a30))
	{
		r++;
		uint32_t wtemp = mod.w_getter(r);
		switch(i)
		{
		case 0:
			if(f_a5 & 1)
			{
				correction = mod.a5_getter(r) - base[0];
			}
			break;
		case 1:case 2:case 3:
			if(f_f & 1)
			{
				correction = mod.f_getter(r) - base[i];
			}
			break;
		case 4:
			if(f_a30 & 1)
			{
				correction = mod.a30_getter(r-4) - base[4];
			}
			break;
		case 5:
			if(f_a5 & 1)
			{
				correction = mod.a5_getter(r) - base[5];
			}
			break;
		}
		if(correction)
		{
			wtemp -= correction;
			correction = 0;
			if((w_getter(r) ^ wtemp) & messageMask[r])
			{
			}
			else
				mod.w_setter(r) = wtemp;
		}
		if ((w_getter(r) ^ mod.w_getter(r)) & messageMask[r])
		{
			mod.firstUnsatisfiedEquation_setter() = r;
			return false;
		}

		if ((a_getter(r+1) ^ mod.a_getter(r+1)) & stateMask[r-5])
		{
			mod.firstUnsatisfiedEquation_setter() = r;
			return false;
		}
		f_a30 >>= 1;
		f_f   >>= 1;
		f_a5  >>= 1;
		i++;
	}
//	fprintf(stderr,"%d\n",r);
//	compare_duo(mod, 9, 14, stderr);
//
	while(++r <= lastRoundToTest)
	{
		if ((r<16) && ((w_getter(r) ^ mod.w_getter(r)) & messageMask[r]))
		{
			mod.firstUnsatisfiedEquation_setter() = r;
			return false;
		}

		//check state mask
		uint32_t diffa = (a_getter(r+1) ^ mod.a_getter(r+1)) & stateMask[r-5];
		uint32_t difff = 0;
		if(NULL != functionMask)
			difff = (r > 17)?((f_getter(r+2) ^ mod.f_getter(r+2)) & functionMask[r-18]):0;
//equations that cannot be tested by stateMask and functionMask are tested by check_single_equation_by_order
		switch(r)
		{
		case 16:
			if(!mod.check_single_equation_by_order(68))
			{
				mod.firstUnsatisfiedEquation_setter() = 68;
				return false;
			}
			break;
		case 19:
			if(!mod.check_single_equation_by_order(76))
			{
				mod.firstUnsatisfiedEquation_setter() = 76;
				return false;
			}
			break;
		case 21:
			if(!mod.check_single_equation_by_order(84))
			{
				mod.firstUnsatisfiedEquation_setter() = 84;
				return false;
			}
			else if(equationToCorrect == 84)break;
			break;
		case 22:
			if(!mod.check_single_equation_by_order(86))
			{
				mod.firstUnsatisfiedEquation_setter() = 86;
				return false;
			}
			break;
		case 28:
			if(!mod.check_single_equation_by_order(95))
			{
				mod.firstUnsatisfiedEquation_setter() = 95;
				return false;
			}
			if((equationToCorrect>=96) &&(!mod.check_single_equation_by_order(96)))
			{
				mod.firstUnsatisfiedEquation_setter() = 96;
				return false;
			}
			break;
		}

		if (diffa || difff)
		{
			switch(r)
			{
			case 16:
				mod.check_conformance(71);//v
				break;
			case 17:
				mod.check_conformance(73);//v
				break;
			case 18:
				mod.check_conformance(77);//v
				break;
			case 19:
				mod.check_conformance(79);//v
				break;
			case 20:
				mod.check_conformance(82);//v
				break;
			case 21:
				mod.firstUnsatisfiedEquation_setter() = 86;
//				mod.check_conformance(86);//v
				break;
			case 22:
				mod.check_conformance(88);//v
				break;
			case 23:
				mod.check_conformance(90);//v
				break;
			case 24:
				mod.check_conformance(92);//v
				break;
			case 25:
				mod.check_conformance(94);
				break;
			case 28:
				mod.firstUnsatisfiedEquation_setter() = 98;
				break;
			default:
				if(r<16)
				{
					mod.firstUnsatisfiedEquation_setter() = r;
				}
			}
			return false;
		}
	}

	if(equationToCorrect < 68)
	{
		if(mod.check_single_equation_by_order(equationToCorrect))
			return true;
		else
			return false;
	}
	else
	{
		mod.check_conformance(equationToCorrect);
	}
	if(mod.firstUnsatisfiedEquation_getter()>equationToCorrect)
		return true;
	else
	{
		return false;
	}
}
//if a disturbance is applied at Round 8 or 13, we cancel the difference of the expansion in word 16 by a disturbance at round 15
//works for (13,9), (13,11)
u32 SHA1::Compensate_w8_w13(u32 (&messageSubDiff)[11], u32 (&messageXorDiff)[11])
{
	u32 xorDifferenceAtRound8_Or_13;
	u32 subDiffCompensationW15;
	xorDifferenceAtRound8_Or_13 = (w_getter(8)+messageSubDiff[3]) ^ w_getter(8);
	xorDifferenceAtRound8_Or_13 ^= (w_getter(13)+messageSubDiff[8]) ^ w_getter(13);
	subDiffCompensationW15 = SHIFT_RIGHT5_SIGNED(w_getter(16)-(w_getter(16)^(xorDifferenceAtRound8_Or_13<<1)));
	messageSubDiff[10] += subDiffCompensationW15;
	messageXorDiff[10] = ((w_getter(15)+messageSubDiff[10]) ^ w_getter(15));
	if(messageXorDiff[10] & messageMask[15])
		return 0;
	return subDiffCompensationW15;
}

