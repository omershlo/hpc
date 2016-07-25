#include <assert.h>
#include "sha1.h"
#include "sha_utils.h"
#include "wbs.h"
#include "CorrectionSet.h"




bool initialize_random_message(SHA1& deltaLinearMessage, FILE* fp_random)
{
	const u32 MESSAGE_MASK[16] = {	0xffffffff, 0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xfff8003f,0xfc000071,0x3c00001d,
									0x3c000004,0x3c00001a,0x3c000010,0x3c00001c,0x7c000014,0x0c000000,0x5c000010,0x3400001c};
	const u32 MESSAGE_VALUE[16] = {	0xf49867bb,0x9dfbd98f,0xcc597023,0x8215c718,0x60acb18a,0xb0000028,0x48000050,0x0c00001c,
									0x1c000000,0x20000018,0x00000010,0x00000010,0x70000000,0x00000000,0x0c000000,0x1000000c};
	if(11 != fread(&deltaLinearMessage.w_setter(5), sizeof(u32), 11, fp_random))
		return false;
	for(int i = 5; i < 16; i++)
	{
		deltaLinearMessage.w_setter(i) = ((deltaLinearMessage.w_getter(i) & ~MESSAGE_MASK[i]) | MESSAGE_VALUE[i]);
	}
	deltaLinearMessage.updatedToRound_setter() = 4;
	deltaLinearMessage.firstUnsatisfiedEquation_setter() = 0;
	return true;
}

//next two are message masks for corrections
enum MESSAGE_MASK_INDEX {	MESSAGE_MASK_CORRECTION_49=0, MESSAGE_MASK_CORRECTION_56=1, MESSAGE_MASK_CORRECTION_57=2,
	MESSAGE_MASK_CORRECTION_58=3, MESSAGE_MASK_CORRECTION_59=4, MESSAGE_MASK_CORRECTION_60=5, MESSAGE_MASK_CORRECTION_61=6,
	MESSAGE_MASK_CORRECTION_62=7, MESSAGE_MASK_CORRECTION_63=8, MESSAGE_MASK_CORRECTION_64=9, MESSAGE_MASK_CORRECTION_65=10,
	MESSAGE_MASK_CORRECTION_67=11};

const u32 MESSAGE_MASKS[][11] = {
		{0xfff8003f,0xfc00007f,0xbc00001f,0xbc00000d,0x3c00001f,0x7c000011,0x7c00001e,0,0,0,0},                                   //49: a[12][30]=a[11][30]
		{0xfff8003f,0xfc00007f,0xbc00001f,0xfc00000f,0x7c00001e,0x7c00001b,0xfc00001e,0xfc00001e,0,0,0},                          //56: a[13][31]=1
		{0xffff003f,0xffbe007f,0xfef8001f,0xffff800f,0xfffe001f,0xfff8001f,0xffff001f,0xff78001f,0x07ff800f,0,0},                 //57: a[14][26]=1
		{0xffff003f,0xffbe007f,0xfef8001f,0xffff800f,0xfffe001f,0xfff8001f,0xffff001f,0xff78001f,0x0fff800f,0,0},                 //58: a[14][27]^f[14][0]^w[14][0]=0
		{0xffff003f,0xffbe007f,0xfef8001f,0xffff800f,0xfffe001f,0xfff8001f,0xffff001f,0xff78001f,0x3fff800f,0,0},                 //59: a[14][29]=0
		{0xffff003f,0xffbe007f,0xfef8001f,0xffff800f,0xfffe001f,0xfff8001f,0xffff001f,0xff78001f,0xffff800f,0,0},                 //60: a[14[31]=1
		{0xffff003f,0xffbe007f,0xfef8001f,0xffff800f,0xfffe001f,0xfff8001f,0xffff001f,0xff78001f,0xffff800f,0x0000001f,0},        //61: a[15][4]=0
		{0xffff003f,0xffff007f,0xfefa001f,0xffff800f,0xfffe801f,0xfffe001f,0xffff001f,0xfffd001f,0xffff800f,0x03fe801f,0},        //62: a[15][26]=0
		{0xffff003f,0xffff007f,0xfefa001f,0xffff800f,0xfffe801f,0xfffe001f,0xffff001f,0xfffd001f,0xffff800f,0x0ffe801f,0},        //63: a[15][27]=0
		{0xffff003f,0xffff007f,0xfefa001f,0xffff800f,0xfffe801f,0xfffe001f,0xffff001f,0xfffd001f,0xffff800f,0x3ffe801f,0},        //64: a[15][29]=1
		{0xffff003f,0xffff007f,0xfefa001f,0xffff800f,0xfffe801f,0xfffe001f,0xffff001f,0xfffd001f,0xffff800f,0xfffe801f,0},        //65: a[15][31]=1
		{0xffff803f,0xffff207f,0xffffc01f,0xffff800f,0xfffed01f,0xfffe801f,0xffff001f,0xfffda01f,0xffff800f,0xfffe901f,0x0fffc01f}//67: a[16][27]^w[14][26]=1
};

void update_before_correcting(const int equationToCorrect, SHA1 &ref, int maskIndex)
{
	for(int i=5; i <= 15; i++)
		ref.messageMask[i] = MESSAGE_MASKS[maskIndex][i-5];
	ref.firstUnsatisfiedEquation_setter() = equationToCorrect;
}

//TODO: in each of the case add the linear modification to the message mask in order avoid duplications
//TODO: avoid re-computation. E.g., in case 1 and case 2 the messages are identical up to w[15][13] so we may save the message
//we generate in case 1, complement bits 14 and 16 of w[15] and jump to w[15][14].
#define NUMBER_OF_LINEAR_MODIFICATIONS 14
void apply_modifications(SHA1 &deltaLinearMessage, const int modificationsBitMask[NUMBER_OF_LINEAR_MODIFICATIONS])
{
	for(int i=0; i < NUMBER_OF_LINEAR_MODIFICATIONS; i++)
	{
		if(modificationsBitMask[i] == 0) continue;
		switch(i)
		{
			case   0:
				deltaLinearMessage.w_setter(15) ^= B16;
				break;
			case 1:
				deltaLinearMessage.w_setter(15) ^= B14;
				break;
			case 2:
				deltaLinearMessage.w_setter(14) ^= B15;
				break;
			case 3:
				deltaLinearMessage.w_setter(14) ^= B12;
				break;
			case 4:
				deltaLinearMessage.w_setter(13) ^= B19;
				break;
			case 5:
				deltaLinearMessage.w_setter(13) ^= B17;
				break;
			case 6:
				deltaLinearMessage.w_setter(12) ^= B22;
				break;
			case 7:
				deltaLinearMessage.w_setter(12) ^= B21;
				break;
			case 8:
				deltaLinearMessage.w_setter(12) ^= B16;
				break;
			case 9:
				deltaLinearMessage.w_setter(12) ^= B15;
				break;
			case 10:
				deltaLinearMessage.w_setter(12) ^= B13;
				break;
			case 11:
				deltaLinearMessage.w_setter(11) ^= B20;
				break;
			case 12:
				deltaLinearMessage.w_setter(11) ^= B18;
				break;
			case 13:
				deltaLinearMessage.w_setter(9) ^= B12;
				break;
		}
	}
	//TODO use a more accurate conf start
}

void apply_linear_modification(SHA1 &deltaLinearMessage, const int modificationIndex)
{
//	if(modificationIndex == 1)
//		return deltaLinearMessage.firstUnsatisfiedEquation_getter();

	const int modifications[][NUMBER_OF_LINEAR_MODIFICATIONS] =
	{
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
//	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
//	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	};
	apply_modifications(deltaLinearMessage, modifications[modificationIndex]);
}

bool apply_linear_modification_and_fix(SHA1& base, SHA1& derivedSha, linear_equation  linearEquations[], int baseIndex, int firstConfToCheck)//returns IF above round 15
{
	derivedSha = base;

	if(baseIndex == 0)//dont modify anything
		return true;

	for(int i=0; i < 6; i++)
	{
		if(baseIndex & BIT_BY_INDEX[i])
		{
			apply_linear_modification(derivedSha, i);
			baseIndex &= (baseIndex-1);
		}
		if(!baseIndex)break;
	}

	derivedSha.check_conformance(firstConfToCheck);
	int nextUnsatisfiedEq = derivedSha.firstUnsatisfiedEquation_getter();

//	base.compare_duo(derivedSha, 9, 16, stderr);
//	printf("nextUnsatisfiedEq=%d\n", nextUnsatisfiedEq);

	bool result = false;
	if(nextUnsatisfiedEq > 67)
	{
		result = true;
#if DEBUG_LOG_LEVEL > 0
		fprintf(gDebugLogFile, "\tAdding1 LM %d-%d \n\t", baseIndex, nextUnsatisfiedEq);
		print_sha(derivedSha, gDebugLogFile);
		fprintf(gDebugLogFile, "\n");
#endif
	}
	else
	{
		int firstRoundToUpdate = 1000 + nextUnsatisfiedEq;
		if (0 < test_and_fix_till_round_15(derivedSha, firstRoundToUpdate, linearEquations))
		{
			result = true;
#if DEBUG_LOG_LEVEL > 0
			fprintf(gDebugLogFile, "\tAdding2 LM %d-%d\n\t", baseIndex, nextUnsatisfiedEq);
			print_sha(derivedSha, gDebugLogFile);
			fprintf(gDebugLogFile, "\n");
#endif
		}
	}
	return result;
}


// int apply_linear_modification(SHA1 &deltaLinearMessage, char modificationsSelector)
// {
//   int currentBitForModification = 0;
//   int firstRoundToUpdate = 16;
//   while(modificationsSelector)
//     {
//       if(modificationsSelector & 0x1)
// 	{
// 	  switch(currentBitForModification)
// 	    {
// 	    case   0:
// 	      deltaLinearMessage.w_setter(15) ^= B14;
// 	      deltaLinearMessage.w_setter(15) ^= B16;
// 	      deltaLinearMessage.a(16) = deltaLinearMessage.w_setter(15) + deltaLinearMessage.k(16);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 15);
// 	      break;
// 	    case   1:
// 	      deltaLinearMessage.w_setter(15) ^= B16;
// 	      deltaLinearMessage.w_setter(14) ^= B12;
// 	      deltaLinearMessage.a(15) = deltaLinearMessage.w_setter(14) + deltaLinearMessage.k(15);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 14);
// 	      break;
// 	    case   2://3
// 	      deltaLinearMessage.w_setter(15) ^= B16;
// 	      deltaLinearMessage.w_setter(12) ^= B15;
// 	      deltaLinearMessage.a(13) = deltaLinearMessage.w_setter(12) + deltaLinearMessage.k(13);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 12);
// 	      break;
// 	    case   3://5
// 	      deltaLinearMessage.w_setter(15) ^= B14;
// 	      deltaLinearMessage.w_setter(14) ^= B15;
// 	      deltaLinearMessage.w_setter(14) ^= B12;
// 	      deltaLinearMessage.w_setter(12) ^= B16;
// 	      deltaLinearMessage.a(13) = deltaLinearMessage.w_setter(12) + deltaLinearMessage.k(13);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 12);
// 	      break;
// 	    case   4://7
// 	      deltaLinearMessage.w_setter(15) ^= B16;
// 	      deltaLinearMessage.w_setter(12) ^= B13;
// 	      deltaLinearMessage.a(13) = deltaLinearMessage.w_setter(12) + deltaLinearMessage.k(13);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 12);
// 	      break;
// 	    case   5://11
// 	      deltaLinearMessage.w_setter(14) ^= B15;
// 	      deltaLinearMessage.w_setter(12) ^= B16;
// 	      deltaLinearMessage.w_setter(12) ^= B15;
// 	      deltaLinearMessage.w_setter(12) ^= B13;
// 	      deltaLinearMessage.a(13) = deltaLinearMessage.w_setter(12) + deltaLinearMessage.k(13);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 12);
// 	      break;
// 	    case   6://12
// 	      deltaLinearMessage.w_setter(14) ^= B12;
// 	      deltaLinearMessage.w_setter( 9) ^= B12;
// 	      deltaLinearMessage.a(10) = deltaLinearMessage.w_setter(9) + deltaLinearMessage.k(10);
// 	      firstRoundToUpdate = MIN(firstRoundToUpdate, 9);
// 	      break;
// 	    default:
// 	      printf("default!!");
// 	      exit(1);
// 	    }
// 	}
//       currentBitForModification++;
//       modificationsSelector /= 2;
//     }
//   return firstRoundToUpdate + 1000;
// }

void check_and_fix_bit(SHA1 &deltaLinearMessage, const int round, const uint32_t xoredBit, const uint32_t expectedValue, const int bitFix)
{
	if((deltaLinearMessage.a_getter(round) & xoredBit) == expectedValue)
	{
		if(deltaLinearMessage.a_getter(round-1) & bitFix)
			deltaLinearMessage.w_setter(round-2) -= bitFix;
		else
			deltaLinearMessage.w_setter(round-2) += bitFix;
		deltaLinearMessage.a_setter(round-1) = deltaLinearMessage.k_getter(round-2) + deltaLinearMessage.w_getter(round-2);
		deltaLinearMessage.update_a5_a30_f_k(round-2);
		deltaLinearMessage.a_setter(round) = deltaLinearMessage.k_getter(round-1) + deltaLinearMessage.w_getter(round-1);
	}
}

//TODO: replace carry_control() with a simpler logic
//return 0 = bit2control is not controlable by carry
u32 carry_control(u32 w, u32 a, int bit2control, int firstbit)
{
	int i;
	int bit;
	u32 complemented = 0;
	int bit2compare = 0;
	for(i = bit2control - 1; i >= firstbit; i--)
	{
		if((w ^ a) & BIT_BY_INDEX[i])
		{
			complemented |= BIT_BY_INDEX[i];
			bit = i + 1;
			if(a & BIT_BY_INDEX[i])
				bit2compare = 1;
			break;
		}
	}
	if(!complemented)
		return 0;
	for(i = bit; i < bit2control; i++)
	{
		if(((a & BIT_BY_INDEX[i]) && !bit2compare) || (!(a & BIT_BY_INDEX[i]) && bit2compare))
			complemented |= BIT_BY_INDEX[i];
	}
	return complemented;
}

void SHA1::set_A_to_equal_W_using_carry(int round, int bit)
{
	if((mA[round + 1] ^ mW[round]) & BIT_BY_INDEX[bit])
	{
		if((mA[round + 1] ^ mW[round]) & BIT_BY_INDEX[bit-1])
		{
			mW[round] ^= BIT_BY_INDEX[bit-1];
			mA[round+1] = mK[round] + mW[round];
		}
	}
}


int test_and_fix_till_round_15(SHA1 &deltaLinearMessage, int startRound, linear_equation linearEquations[])
{
	int round = startRound;
	//TODO: initialize watchdogs when deriving messages by using linear solutions
	int watchDog1531 = 0;
	while((round < 16)||(round>1000))
	{
		switch(round)
		{
		case 5: /* A[6] */
			watchDog1531 = 0; //TODO why this is needed
			//			deltaLinearMessage.windowWeight_setter() = 150;
			/* a(7)[7] */
			/* a(7)[8] */
			deltaLinearMessage.w_setter(5) |= (B11 | B10 | B9 | B6);
//			deltaLinearMessage.w_setter(5) |= ( B10 | B9 | B6);
			deltaLinearMessage.w_setter(5) &= NB7;
			deltaLinearMessage.w_setter(5) &= NB12;
			deltaLinearMessage.w_setter(5) &= NB8;
			deltaLinearMessage.a_setter(6) = deltaLinearMessage.k_getter(5) + deltaLinearMessage.w_getter(5);
			//a(6)[13]=0 => f(8)[11]=9 => a(9)[11]=w(8)[11]
			deltaLinearMessage.test_and_corr(round, B13, 0);
			deltaLinearMessage.update_a5_a30_f_k(5);//update a5(6) a30(6) f(7) k(6)
			round = 5;

#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif

		case 6: /*A[7]*/
			round = 6;
			// ref.w_setter(6) &= 0xfc1f203f;
			deltaLinearMessage.w_setter(6) &= 0xfc1fffff;
			deltaLinearMessage.w_setter(6) &= ~(B3 | B2);
			// ref.w_setter(6) |= (B25 | B15 | B12 | B9 | B6 | B1);
			deltaLinearMessage.w_setter(6) |= (B25 | B15 | B14 | B12 | B7 | B6 | B1);
			deltaLinearMessage.a_setter(7) = deltaLinearMessage.k_getter(6) + deltaLinearMessage.w_getter(6);
			/******************************************************/
			/* a(6)[9, 10]*/
			/* a(7)[7]=0 by w[6] selection */
			// ref.test_and_corr(rnd, B7, 0);
			deltaLinearMessage.test_and_corr(round, B8, 0);
			/******************************************************/
			/* a(7)[9] = 0 (equ 12) */
			deltaLinearMessage.test_and_corr(round, B9, 0);
			/* a(8)[8]*/
			deltaLinearMessage.test_and_corr(round, B10, 2);
			//f(9)[9]=a(7)[11]=1 => w(9)[9]=a(10)[9]
			deltaLinearMessage.test_and_corr(round, B11, 1);
			/***********************************************************/
			/*		w(5)[7, 9, 10]*/
			/*		w[6][12]=!a[6][7]*/
			/* a(6)[7]=0 =>  w(6)[12]=1 */
			/* a(6)[9]=0 =>  w(6)[14]=1 */
			/* a(6)[10]=0 => w(6)[15]=1 */
			/*		w[6][12]=!a[6][7]*/
			deltaLinearMessage.set_a_w_comp(5, B7);
			/*		w[6][14]=!a[6][9]*/
			deltaLinearMessage.set_a_w_comp(5, B9);
			/*		w[6][15]=!a[6][10]*/
			deltaLinearMessage.set_a_w_comp(5, B10);
			/***********************************************************/
			/*		correct a(7)[31,...,28] = 1101,
			a(7)[27] = !w(6)[26], a(7)[26] = 0
			with w(6)[31,29,...,25]*/
			/*		we add three conditions a[7][30]=1
			a[7][29]=0 a[7][27] = !w[6][26] to
			avoid forbidden states of condw8 and
			to allow free selection of w[8][28]*/
			/* a(7)[30]=1, a(7)[29]=0, a(7)[28]=1, a(7)[27]=!w(6)[26], a(7)[26]=0 */
			if((deltaLinearMessage.a_getter(7) & 0x7c000000) != 0x58000000) // was a7_30_2_26
			{
				deltaLinearMessage.w_setter(6) ^= B25;
				deltaLinearMessage.a_setter(7) = deltaLinearMessage.k_getter(6) + deltaLinearMessage.w_getter(6);
			}
			/* a(7)[31]=1 */
			/* 		ref.test_and_corr(rnd, B31, 1); */
			deltaLinearMessage.update_a5_a30_f_k(6);//update a5(7) a30(7) f(8) k(7)
#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
		case 7: /* A[8]*/
			round = 7;
			// ref.w_setter(7) &= 0xfc1fc01f;
			deltaLinearMessage.w_setter(7) &= 0xfc1fff1f;
			/* ref.w_setter(7)[7] = ref.a(8)[7] = 1, aux cond for w(6)[9]*/
			deltaLinearMessage.w_setter(7) |= (B25 | B13 | B12 | B7 | B6);
			/* a(7)[7], (a(8)[5]=0 contradicts the requirement a(8)[5]=1 for a(6)[7]) */
			/* a(7)[8], (a(8)[6]=a(9)[6]=0 (equ 27) thus, we can choose a correction in
			 * w(9) or w(10) but we cannot eliminate both) */
			deltaLinearMessage.w_setter(7) &= (NB11 & NB5 & NB1);
			/* w(7)[0]=0 => a(8)[0]=a(6)[31]=0 */
			/*a[9][6]^a[8][6]=0 (equ 27)*/
			deltaLinearMessage.a_setter(8) = deltaLinearMessage.k_getter(7) + deltaLinearMessage.w_getter(7);
			/******************************************************/
			deltaLinearMessage.test_and_corr(round, B6, 0);
			/* a(6)[9, 10] */
			deltaLinearMessage.test_and_corr(round, B8, 1);
			/* w(8)[8] the condition for w(8)[11] which is
	     a(8)[13]=a(7)[13] might contradicts the condition
	     w(7)[13]=!a(7)[8], thus we skip it */
			/* ref.test_and_corr(rnd, B10, 2); */
			/******************************************************/
			/* a(8)[9]=1 */
			deltaLinearMessage.test_and_corr(round, B9, 1);
			/***********************************************************/
			/* a(8)[8]*/
			deltaLinearMessage.test_and_corr(round, B10, 2);
			/* a(7)[7, 8] */

			/* correct a(8)[26] = 0 with w(6)[21] */
			check_and_fix_bit(deltaLinearMessage, 8, B26, B26, B21);
			/* correct a(8)[27] = 0 with w(6)[22] */
			check_and_fix_bit(deltaLinearMessage, 8, B27, B27, B22);
			/* correct a(8)[28] = 1 with w(6)[23] */
			check_and_fix_bit(deltaLinearMessage, 8, B28, 0, B23);
			/* correct a(8)[29] = 1 with w(6)[24] */
			check_and_fix_bit(deltaLinearMessage, 8, B29, 0, B24);

			deltaLinearMessage.test_and_corr(round, B30, 1);/* a(8)[30]=1 */
			/*
	    to avoid forbiden states of condw9: a[8][30]=0,
	    a[6][31]=0 => a[8][31]=1, otherwise a[8][31]=0, but since
	    we chose a[8][30]=1, then a[8][31]=0
			 */
			deltaLinearMessage.test_and_corr(round, B31, 0);/* a(8)[31]=0 */
			deltaLinearMessage.update_a5_a30_f_k(7);//update a5(8) a30(8) f(9) k(8)
#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
		case 8: /* A[9] */
			round = 8;
			deltaLinearMessage.w_setter(8) &= 0xfc1f800f;
			/* B8 is for a(6)[10]*/
			deltaLinearMessage.w_setter(8) |= (B25 | B14 | B8 | B7 | B5 | B4 );
			/* equ[0]: w(6)[3]=w(8)[3] */
			if((deltaLinearMessage.w_getter(8) ^ deltaLinearMessage.w_getter(6)) & B3) deltaLinearMessage.w_setter(8) ^= B3;

			if(deltaLinearMessage.a_getter(8) & B27)
				deltaLinearMessage.w_setter(8) &= NB0;
			else
				deltaLinearMessage.w_setter(8) |= B0;
			if(deltaLinearMessage.a_getter(8) & B28)
				deltaLinearMessage.w_setter(8) &= NB1;
			else
				deltaLinearMessage.w_setter(8) |= B1;
			deltaLinearMessage.a_setter(9) = deltaLinearMessage.k_getter(8) + deltaLinearMessage.w_getter(8);
			/******************************************************/
			// /********************a[9][6]^a[8][6]=0 (equ 27)********************/
			deltaLinearMessage.test_and_corr(round, B6, 2);
			// /********************a[9][6]^a[8][6]=0 (equ 27)********************/

			/* a(10)[7, 8, 9] */
			deltaLinearMessage.test_and_corr(round, B9, 2);
			deltaLinearMessage.test_and_corr(round, B10, 2);
			/* increase the prob of no carry when a(9)[11] is used */
			if((deltaLinearMessage.w_setter(8) ^ deltaLinearMessage.a_getter(9)) & B11)
			{
				if(deltaLinearMessage.a_getter(9) & B10)
					deltaLinearMessage.w_setter(8) += B10;
				else
					deltaLinearMessage.w_setter(8) -= B10;
				deltaLinearMessage.a_setter(9) = deltaLinearMessage.k_getter(8) + deltaLinearMessage.w_getter(8);
			}

			deltaLinearMessage.test_and_corr(round, B11, 2);
			/******************************************************/
			/***********************************************************/
			/* a(8)[7, 8] */
			deltaLinearMessage.set_a_w_comp(7, B7);/*w[8][12]=!a[8][7] */
			deltaLinearMessage.set_a_w_comp(7, B8);/*w[8][13]=!a[8][8] */
			/***********************************************************/
			check_and_fix_bit(deltaLinearMessage, 9, B26, 0, B21);
			check_and_fix_bit(deltaLinearMessage, 9, B27, B27, B22);
			check_and_fix_bit(deltaLinearMessage, 9, B28, 0, B23);
			check_and_fix_bit(deltaLinearMessage, 9, B29, B29, B24);

			deltaLinearMessage.test_and_corr(round, B30, 1);/* a[9][30]=1 */
			deltaLinearMessage.test_and_corr(round, B31, 1);/* a[9][31]=1 */
			deltaLinearMessage.update_a5_a30_f_k(8);//update a5(9) a30(9) f(10) k(9)
#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
		case 9: /* A[10]*/
			round = 9;
			deltaLinearMessage.w_setter(9) &= 0xfc1ff0ff;
			/* equ[1]: w(9)[2]=!w(6)[2] */
			deltaLinearMessage.w_setter(9) |= (B25 | B11 | B7 | B2);
			deltaLinearMessage.w_setter(9) &= (NB6 & NB5 & NB0);
			deltaLinearMessage.a_setter(10) = deltaLinearMessage.k_getter(9) + deltaLinearMessage.w_getter(9);
//			if(((deltaLinearMessage.a_getter(10) ^ deltaLinearMessage.w_getter(9)) & B7) == 0)rs_pause();
			/* a(11)[5, 7, 8, 9, 10] */
			// ref.test_and_corr(rnd, B7, 2);
			deltaLinearMessage.test_and_corr(round, B8, 2);
			deltaLinearMessage.test_and_corr(round, B9, /*0*/2);/*contradicts a(8)[11]*/
			//	  ref.test_and_corr(rnd, B10, 2);
			/* increase the prob of no carry when a(10)[11] is used */
			if((deltaLinearMessage.w_getter(9) ^ deltaLinearMessage.a_getter(10)) & B11)
			{
				if(deltaLinearMessage.a_getter(10) & B10)
					deltaLinearMessage.w_setter(9) += B10;
				else
					deltaLinearMessage.w_setter(9) -= B10;
				deltaLinearMessage.a_setter(10) = deltaLinearMessage.k_getter(9) + deltaLinearMessage.w_getter(9);
			}
			deltaLinearMessage.test_and_corr(round, B11, 2);
			/* a(9)[8], w[9][13]=!a[9][8] */
			//the labels are used  when we replace a linear solution
			//HERE
			//			deltaLinearMessage.w_setter(9) &= NB12;
			//			deltaLinearMessage.a_setter(10) = deltaLinearMessage.w_getter(9) + deltaLinearMessage.k_getter(9);

			deltaLinearMessage.set_a_w_comp(8, B8);
			/* a(9)[11], w[9][16]=!a[9][11] */
			deltaLinearMessage.set_a_w_comp(8, B11);

//			 deltaLinearMessage.w_setter(9) ^= B9;
//			 deltaLinearMessage.a_setter(10) = deltaLinearMessage.k_getter(9) + deltaLinearMessage.w_getter(9);

		case 1036:
			//36, 37, 38
			round = 9;
			check_and_fix_bit(deltaLinearMessage, 10, B26, B26, B21);
			check_and_fix_bit(deltaLinearMessage, 10, B27, 0, B22);
			check_and_fix_bit(deltaLinearMessage, 10, B28, B28, B23);
			//39
			deltaLinearMessage.test_and_corr(round, B31, 0);/* a[10][31]=0 */
			deltaLinearMessage.update_a5_a30_f_k(9);//update a5(10) a30(10) f(11) k(10)

#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif

			/* A[11] */
		case 10:
			round = 10;
			//	  ref.w_setter(10) &= 0xfc1c001f;
			deltaLinearMessage.w_setter(10) &= 0xfc1f80ff;
			/* a(7)[8]: w(10)[6]=1 => no carry in the correction of
	     a(7)[8] at round 10. may contradicts a(10)[8] */
			deltaLinearMessage.w_setter(10) |= (B25 | B17 | B7 | B6 | B5);
			deltaLinearMessage.w_setter(10) &=  (NB1 & NB0);
			if(!(((deltaLinearMessage.w_setter(10) & B2) == 0) ^ ((deltaLinearMessage.a_getter(10) & B29) == 0)))
				deltaLinearMessage.w_setter(10) ^= B2;
			if(!(((deltaLinearMessage.w_setter(10) & B3) == 0) ^ ((deltaLinearMessage.a_getter(10) & B30) == 0)))
				deltaLinearMessage.w_setter(10) ^= B3;
			deltaLinearMessage.a_setter(11) = deltaLinearMessage.k_getter(10) + deltaLinearMessage.w_getter(10);
			/******************************************************/
			/* a(6)[7] (may contradicts a(10)[7]:  ref.test_and_corr(rnd, B5, 0);)*/
			// ref.test_and_corr(rnd, B5, 1);/* a(11)[5] = 1 */
			/* a(10)[8] */

			//	  ref.test_and_corr(rnd, B6, 0);
			/* a(6)[9] (may contradicts a(10)[9] and a(12)[5]) */
			/* a(6)[10] */
			deltaLinearMessage.set_e_w_comp(5, B10);
			/* a(12)[7] */
			deltaLinearMessage.test_and_corr(round, B9, 2);
			// 	  /* a(10)[5] */
			deltaLinearMessage.set_a_w_comp(9, B5);
			//(aux cond for 1 14 5) this along with w(14)[5] = !w(15)[10] => w(17)[6] = !w(18)[11]
			// 	  if(ref.w_setter(9) & B5)
			// 	    ref.w_setter(10) |= B5;
			// 	  else
			// 	    ref.w_setter(10) &= NB5;
			/* a(10)[6] (may contradicts a(12)[9]: ref.test_and_corr(rnd, B11, 2);) */
			deltaLinearMessage.set_a_w_comp(9, B6);
			/* a(10)[7] */
			deltaLinearMessage.set_a_w_comp(9, B7);
			/* a(10)[8] */
			deltaLinearMessage.set_a_w_comp(9, B8);
			/* a(10)[9] */
			deltaLinearMessage.set_a_w_comp(9, B9);
			/* a(10)[9] */
			deltaLinearMessage.set_a_w_comp(9, B11);

//			 deltaLinearMessage.w_setter(10) ^= B11;
//			 deltaLinearMessage.a_setter(11) = deltaLinearMessage.k_getter(10) + deltaLinearMessage.w_getter(10);


			if(!((deltaLinearMessage.w_getter(10) ^ (deltaLinearMessage.w_getter(10) << 1)) & B22))
			{
				deltaLinearMessage.w_setter(10) ^= B22;
				deltaLinearMessage.a_setter(11) = deltaLinearMessage.w_getter(10) + deltaLinearMessage.k_getter(10);
			}
			//42, 43, 44
		case 1042:
			round = 10;
			check_and_fix_bit(deltaLinearMessage, 11, B26, B26, B21);
			check_and_fix_bit(deltaLinearMessage, 11, B28, B28, B23);
			check_and_fix_bit(deltaLinearMessage, 11, B29, B29, B24);

			deltaLinearMessage.test_and_corr(round, B30, 0);
			deltaLinearMessage.test_and_corr(round, B31, 1);
			deltaLinearMessage.update_a5_a30_f_k(10);//update a5(11) a30(11) f(12) k(11)


#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
			/* A[12] */
		case 11:
			round = 11;
			//			deltaLinearMessage.w_setter(11) &= 0xfc1f001f;
			deltaLinearMessage.w_setter(11) &= 0xfc1fff1f;
			deltaLinearMessage.w_setter(11) |= (B25 | B15 | B5);
			/* 45: a(12)[2] = !w(8)[1] */
			if(!(((deltaLinearMessage.w_getter(11) & B0) == 0) ^ ((deltaLinearMessage.a_getter(11) & B27) == 0)))/*w(11)[0]=!a(11)[27]*/
				deltaLinearMessage.w_setter(11) ^= B0;
			if((deltaLinearMessage.w_getter(11) ^ deltaLinearMessage.w_getter(8)) & B1)
				deltaLinearMessage.w_setter(11) ^= B1;
			deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);

			/******************************************************/
			/* a(7)[7] */
			// ref.set_e_w_comp(6, B7);
			// ref.verify(5,12);fprintf(stderr,"%x %x\n",ref.w_setter(11) & b5, ref.a(7) & B7);rs_pause();
			/* a(7)[8]*/
			// ref.set_e_w_comp(6, B8);
			/* w(9)[7, 8, 9, 11] */
			deltaLinearMessage.test_and_corr(round, B7, 2);

			/*w(10)[10]*/
			/* increase the prob of no carry when a(12)[9] is used */
			if((deltaLinearMessage.w_getter(11) ^ deltaLinearMessage.a_getter(12)) & B9)
			{
				if(deltaLinearMessage.a_getter(12) & B8)
					deltaLinearMessage.w_setter(11) += B8;
				else
					deltaLinearMessage.w_setter(11) -= B8;
				deltaLinearMessage.a_setter(12) =  deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);
			}
			//ref.test_and_corr(rnd, B8, 0);
			/* w(9)[11] */
			deltaLinearMessage.test_and_corr(round, B9, 1);
			/******************************************************/
			/***********************************************************/
			/* w(10)[7, 8, 9, 10] */
			deltaLinearMessage.set_a_w_comp(10, B5);/* w[11][10]=!a[11][5] */
			deltaLinearMessage.set_a_w_comp(10, B6);/* w[11][12]=!a[11][6] */
			deltaLinearMessage.set_a_w_comp(10, B7);/* w[11][12]=!a[11][7] */
			deltaLinearMessage.set_a_w_comp(10, B8);/* w[11][13]=!a[11][8] */
			deltaLinearMessage.set_a_w_comp(10, B9);/* w[11][14]=!a[11][9] */
			deltaLinearMessage.set_a_w_comp(10, B10);/* w[11][15]=!a[11][10] */
			//			if(((deltaLinearMessage.w_getter(11) ^ (deltaLinearMessage.w_getter(11)<<1)) & B16)==0)
			//			{
			//				deltaLinearMessage.w_setter(11) ^= B16;
			//				deltaLinearMessage.a_setter(12) =  deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);
			//			}
			/***********************************************************/
			if(((deltaLinearMessage.a_getter(11) & B21) == 0) ^ ((deltaLinearMessage.a_getter(12) & B26) == 0))
			{
				u32 c = carry_control(deltaLinearMessage.w_getter(11), deltaLinearMessage.a_getter(12), 26, 17);
				if(c)
				{
					deltaLinearMessage.w_setter(11) ^= c;
					deltaLinearMessage.a_setter(12) =  deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);
				}

			}
			//46 47
		case 1046:
			round = 11;
			check_and_fix_bit(deltaLinearMessage, 12, B27, 0, B22);
			check_and_fix_bit(deltaLinearMessage, 12, B29, B29, B24);

			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[2]);/* w(11)[30] */
			/* cond 49: a[12][30] ^ a[11][30]=0 */
			if((deltaLinearMessage.a_getter(12) ^ deltaLinearMessage.a_getter(11)) & B30)
			{
				if(!((deltaLinearMessage.w_getter(10) ^ deltaLinearMessage.a_getter(11)) & B25))
				{
					deltaLinearMessage.w_setter(10) ^= B25;
					deltaLinearMessage.a_setter(11) = deltaLinearMessage.k_getter(10) + deltaLinearMessage.w_getter(10);
					deltaLinearMessage.update_a5_a30_f_k(10);//recalculate a5(11) a30(11) f(12) k(11)
					deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);//recalculate a(12)
				}
				else if((!((deltaLinearMessage.w_getter(9) ^ deltaLinearMessage.a_getter(10)) & B25)) && !(deltaLinearMessage.a_getter(8) & B27))
				{
					deltaLinearMessage.w_setter(9) ^= B25;
					deltaLinearMessage.a_setter(10) = deltaLinearMessage.k_getter(9) + deltaLinearMessage.w_getter(9);
					deltaLinearMessage.update_a5_a30_f_k(9);//recalculate a5(10) a30(10) f(11) k(10)
					deltaLinearMessage.a_setter(11) = deltaLinearMessage.k_getter(10) + deltaLinearMessage.w_getter(10);//recalculate a(11)
					deltaLinearMessage.update_a5_a30_f_k(10);//recalculate a5(11) a30(11) f(12) k(11)
					deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);//recalculate a(12)
				}
				else
				{
					update_before_correcting(49, deltaLinearMessage, MESSAGE_MASK_CORRECTION_49);
					if(!deltaLinearMessage.correct_equation_using_all_corrections(gNumberOfCorrections[49], gEquationCorrections[49], round))
						return -20;
				}
			}
			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[3]);/* w(11)[31] */
			//50:  if a(12)[31]=0 we complement two variables of equ[3]
			if(!(deltaLinearMessage.a_getter(12) & B31))
			{
				deltaLinearMessage.w_setter(10) ^= B3;
				deltaLinearMessage.a_setter(11) = deltaLinearMessage.k_getter(10) + deltaLinearMessage.w_getter(10);
				deltaLinearMessage.update_a5_a30_f_k(10);//recalculate a5(11) a30(11) f(12) k(12)
				deltaLinearMessage.w_setter(11) ^= B31;
				deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);//recalculate a(12)
			}
			deltaLinearMessage.update_a5_a30_f_k(11);//recalculate a5(12) a30(12) f(13) k(12)
#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
			/* A[13] */
		case 12:
			round = 12;
			deltaLinearMessage.w_setter(12) &= 0xffffa01f;
			if(deltaLinearMessage.a_setter(12) & B31) deltaLinearMessage.w_setter(12) &= NB4;
			else deltaLinearMessage.w_setter(12) |= B4;
			deltaLinearMessage.w_setter(12) |=  B12;
			deltaLinearMessage.a_setter(13) = deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
			//52: a[13][1] = a[12][1] ^ B1
			deltaLinearMessage.test_and_corr(round, B1, 3);
			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[4]);//w(12)[3]
			/******************************************************/
			//w(10)[7, 8, 9, 10]
			/* a(7)[7]*/
			deltaLinearMessage.set_e_w_comp(7, B7);
			/* a(7)[8]*/
			deltaLinearMessage.test_and_corr(round, B6, 0);
			deltaLinearMessage.test_and_corr(round, B7, 2);
			deltaLinearMessage.test_and_corr(round, B8, 2);
			/* a(12)[5, 6, 7] */
			deltaLinearMessage.set_a_w_comp(11, B5);
			deltaLinearMessage.set_a_w_comp(11, B6);
			deltaLinearMessage.set_a_w_comp(11, B7);

			//HERE
			//			deltaLinearMessage.w_setter(12) |= B13;
			//			deltaLinearMessage.a_setter(13) = deltaLinearMessage.w_getter(12) + deltaLinearMessage.k_getter(12);
			deltaLinearMessage.set_a_w_comp(11, B9);
			deltaLinearMessage.set_a_w_comp(11, B12);

			if((deltaLinearMessage.a_getter(13) ^ deltaLinearMessage.w_getter(12)) & B23)
			{
				u32 c = carry_control(deltaLinearMessage.w_getter(12), deltaLinearMessage.a_getter(13), 23, 17);
				if(c)
				{
					deltaLinearMessage.w_setter(12) ^= c;
					deltaLinearMessage.a_setter(13) =  deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
				}
			}
		case 1053:
			round = 12;
			//53
			if(!(deltaLinearMessage.a_getter(13) & B27))
			{
				if(((deltaLinearMessage.w_getter(12) ^ deltaLinearMessage.a_getter(13)) & B25) && !(((deltaLinearMessage.a_getter(13) >> 1) ^ deltaLinearMessage.a_getter(13)) & B25))
				{
					deltaLinearMessage.w_setter(12) ^= B25;
					deltaLinearMessage.a_setter(13) =  deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
				}
				else
				{
					if(deltaLinearMessage.a_getter(12) & B22)
						deltaLinearMessage.w_setter(11) -= B22;
					else
						deltaLinearMessage.w_setter(11) += B22;
					deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);
					deltaLinearMessage.update_a5_a30_f_k(11);//recalculate a5(12) a30(12) f(13) k(12)
					deltaLinearMessage.a_setter(13) = deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
				}
			}
		case 1054:
			round = 12;
			//54
			if(deltaLinearMessage.a_getter(13) & B28)//a(13)[28]=0
			{
				if(deltaLinearMessage.a_getter(12) & B23)
					deltaLinearMessage.w_setter(11) -= B23;
				else
					deltaLinearMessage.w_setter(11) += B23;
				if(deltaLinearMessage.w_getter(11) & B26)
				{
					return -1;
				}
				deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);
				deltaLinearMessage.update_a5_a30_f_k(11);//recalculate a5(12) a30(12) f(13) k(12)
				deltaLinearMessage.a_setter(13) = deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
			}
		case 1055:
			round = 12;
			//55
			if(deltaLinearMessage.a_getter(13) & B29)//a(13)[29]=0
			{
				if(deltaLinearMessage.a_getter(12) & B24)
					deltaLinearMessage.w_setter(11) -= B24;
				else
					deltaLinearMessage.w_setter(11) += B24;
				if(deltaLinearMessage.w_getter(11) & B26)
				{
					return -2;
				}
				deltaLinearMessage.a_setter(12) = deltaLinearMessage.k_getter(11) + deltaLinearMessage.w_getter(11);
				deltaLinearMessage.update_a5_a30_f_k(11);//recalculate a5(12) a30(12) f(13) k(12)
				deltaLinearMessage.a_setter(13) = deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
			}
			//a(16)[0]=1 => f(15)[0]=!w(15)[0]. sol[5]=!f(15)[0]
			//a(14)[0]=1 => f(15)[0]=a(13)[2]
			linearEquations[5].solution = (deltaLinearMessage.a_getter(13) & B2)?0:1;
			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[5]);
			/* a[13][31] = 1 */
		case 1056:
			round = 12;

			if(!(deltaLinearMessage.a_getter(13) & B31))
			{
				update_before_correcting(56, deltaLinearMessage, MESSAGE_MASK_CORRECTION_56);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[56], gEquationCorrections[56], round))
				{
					return -3;
				}
			}
			deltaLinearMessage.update_a5_a30_f_k(12);//recalculate a5(13) a30(13) f(14) k(13)

#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
			//A[14]
		case 13:
			round = 13;
//			rs_pause();
			if(((deltaLinearMessage.w_getter(11) >> 1) ^ deltaLinearMessage.w_getter(8)) & B0)//equ[6]
				deltaLinearMessage.w_setter(13) |= B0;
			else
				deltaLinearMessage.w_setter(13) &= ~B0;

			deltaLinearMessage.w_setter(13) &= 0xffff801f;
			deltaLinearMessage.w_setter(13) |= B14;
			if(deltaLinearMessage.w_getter(9) & B13)
				deltaLinearMessage.w_setter(13) |= B6;
			else
				deltaLinearMessage.w_setter(13) &= NB6;
			deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);
			for(int i = 7; i < 12; i++)
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);//w[13][1],...,w[13][17]
			}
			//			deltaLinearMessage.set_A_to_equal_W_using_carry(13, 5);
			//			deltaLinearMessage.set_A_to_equal_W_using_carry(13, 6);
			//			deltaLinearMessage.set_A_to_equal_W_using_carry(13, 7);
			//			deltaLinearMessage.set_A_to_equal_W_using_carry(13, 8);
			if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B5)
			{
				if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B4)
				{
					deltaLinearMessage.w_setter(13) ^= B4;
					deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);
				}
			}
			if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B6)
			{
				if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B5)
				{
					deltaLinearMessage.w_setter(13) ^= B5;
					deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);
				}
			}
			if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B7)
			{
				if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B6)
				{
					deltaLinearMessage.w_setter(13) ^= B6;
					deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);
				}
			}
			if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B8)
			{
				if((deltaLinearMessage.a_getter(14)^deltaLinearMessage.w_getter(13)) & B7)
				{
					deltaLinearMessage.w_setter(13) ^= B7;
					deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);
				}
			}
			/* aux cond for w(14)[5], w(14)[6], w(14)[7] */
			deltaLinearMessage.test_and_corr(round, B7, 2);
			deltaLinearMessage.test_and_corr(round, B8, 2);
			deltaLinearMessage.test_and_corr(round, B9, 2);

			deltaLinearMessage.set_a_w_comp(12, B5);
			//     // auxiliary cond for a(14)[26] = 1
			// if(!(((ref.a(14) >> 1) ^ ref.a(14)) & B17))
			// {
			//     ref.w_setter(13) ^= B18;
			//     ref.a(14) = ref.w_setter(13) + ref.k(14);
			// }
			for(int i = 12; i < 18; i++)
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);//w[13][20],...,w[13][25]
			}
		case 1057:
			round = 13;
			/* 57: a[14][26]=1 */
			if(!(deltaLinearMessage.a_getter(14) & B26))
			{
				update_before_correcting(57, deltaLinearMessage, MESSAGE_MASK_CORRECTION_57);

				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[57], gEquationCorrections[57], round))
				{
					return -4;
				}
			}
			for(int i = 18; i < 23; i++)
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);/*w[13][28],...,w[14][0] */
			}

		case 1058:
			round = 13;
			/* 58: a(14)[27]^f(14)[0]^w(14)[0] = 0 */
			if(((deltaLinearMessage.a_getter(14) >> 27) ^ deltaLinearMessage.f_getter(14) ^ deltaLinearMessage.w_getter(14)) & B0)
			{
				update_before_correcting( 58, deltaLinearMessage, MESSAGE_MASK_CORRECTION_58);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 58], gEquationCorrections[ 58], round))
				{
					return -5;
				}
			}
			if(deltaLinearMessage.a_getter(14) & B28)
			{
				deltaLinearMessage.w_setter(12) ^= B23;
				deltaLinearMessage.a_setter(13) = deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
				deltaLinearMessage.update_a5_a30_f_k(12);//recalculate a5(13) a30(13) f(14) k(13)
				deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);//recalculate a(14)

				if(!(deltaLinearMessage.a_getter(13) & B27))
				{
					deltaLinearMessage.w_setter(12) ^= B23;
					deltaLinearMessage.a_setter(13) = deltaLinearMessage.k_getter(12) + deltaLinearMessage.w_getter(12);
					deltaLinearMessage.update_a5_a30_f_k(12);//recalculate a5(13) a30(13) f(14) k(13)
					deltaLinearMessage.a_setter(14) = deltaLinearMessage.k_getter(13) + deltaLinearMessage.w_getter(13);//recalculate a(14)
				}
				else
				{
					deltaLinearMessage.a_setter(14) = deltaLinearMessage.w_getter(13) + deltaLinearMessage.k_getter(13);
				}
			}
		case 1059:
			round = 13;
			/* 59: a[14][29]=0 */
			if(deltaLinearMessage.a_getter(14) & B29)
			{
				update_before_correcting( 59, deltaLinearMessage, MESSAGE_MASK_CORRECTION_59);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 59], gEquationCorrections[ 59], round))
				{
					return -6;
				}
			}
		case 1060:
			round = 13;
			/* a[14][31]=1 */
			if(!(deltaLinearMessage.a_getter(14) & B31))
			{
				//may also be corrected by linear sol: 13 15, 11 21
				update_before_correcting( 60, deltaLinearMessage, MESSAGE_MASK_CORRECTION_60);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 60], gEquationCorrections[ 60], round))
				{
					return -7;
				}
			}
			deltaLinearMessage.update_a5_a30_f_k(13);//recalculate a5(14) a30(14) f(15) k(14)

#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
			//A[15]
		case 14:
			round = 14;
			// deltaLinearMessage.w_setter(round) = (deltaLinearMessage.w_setter(round) & ~MESSAGE_MASK[round]) | MESSAGE_VALUE[round];
			deltaLinearMessage.w_setter(14) &= 0xffff9a1f;
			//	  ref.w_setter(14) |= (B14 | B12);
			/* a(10)[7] */
			if(deltaLinearMessage.w_getter(9) & B7)
				deltaLinearMessage.w_setter(14) &= NB5;
			else
				deltaLinearMessage.w_setter(14) |= B5;
			deltaLinearMessage.a_setter(15) = deltaLinearMessage.k_getter(14) + deltaLinearMessage.w_getter(14);
			for(int i = 23; i < 26; i++)
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);//w[14][0],...,w[14][3]
			}
			/* auxilary cond */
#ifdef AUX
		case 1061:
			round = 14;
			if(deltaLinearMessage.a_getter(15) & B4)
			{
//				if(!watchDog1204 && (!(deltaLinearMessage.a30_getter(13) & B4)) && ((deltaLinearMessage.a30_getter(12) ^ deltaLinearMessage.a30_getter(11)) & B6))
//				{
//					watchDog1204++;
//					deltaLinearMessage.w_setter(12) ^= B4;
//					//					deltaLinearMessage.updatedToRound_setter() = 11;
//					round = 12;
//					break;
//				}
//				watchDog1204 = 0;
				update_before_correcting( 61, deltaLinearMessage, MESSAGE_MASK_CORRECTION_61);
				if(deltaLinearMessage.a_getter(13) & B4)
				{
					if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 61]-1, gEquationCorrections[61], round))
						return -8;
				}
				else
				{
					if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 61], gEquationCorrections[61], round))
						return -8;
				}
				//				if(!deltaLinearMessage.correct_equation_using_all_corrections( numberOfCorrections[ 61], correction[61], round))
				//				{
				//					return -8;
				//				}
			}
#endif
			deltaLinearMessage.test_and_corr(round, B5, 0);
			deltaLinearMessage.test_and_corr(round, B6, 0);
			deltaLinearMessage.test_and_corr(round, B7, 0);

			/* a(10)[8]*/
			// ref.set_e_w_comp(9, B8);
			// ref.test_and_corr(rnd, B7, 2);
			deltaLinearMessage.test_and_corr(round, B8, 2);
			//	  ref.test_and_corr(rnd, B9, 2);
			deltaLinearMessage.test_and_corr(round, B10, 2);
			// 	  ref.test_and_corr(rnd, B11, 2);
			// 	  ref.test_and_corr(rnd, B12, 2);
			// 	  ref.test_and_corr(rnd, B13, 2);
			/* a(14)[4]*/
			deltaLinearMessage.set_a_w_comp(13, B4);
			/* a(14)[5]*/
			deltaLinearMessage.set_a_w_comp(13, B5);
			deltaLinearMessage.set_a_w_comp(13, B6);

		case 1014:
			round = 14;
			/* improves w(6)[7] ? */
			//     //w(20)[9]=!w(20)[8]
			// ref.w_setter(14) ^= (((ref.w_setter(20) ^ (ref.w_setter(20) << 1)) & B9) ^ B9)  >> 2;
			// ref.a(15)  = ref.w_setter(14) + ref.k(15);
			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[26]);//w[14][15]
			deltaLinearMessage.a_setter(15) = deltaLinearMessage.w_getter(14) + deltaLinearMessage.k_getter(14);
			if(deltaLinearMessage.w_getter(13) & B11)
				deltaLinearMessage.w_setter(14) &= NB16;
			else
				deltaLinearMessage.w_setter(14) |= B16;

			deltaLinearMessage.a_setter(15) = deltaLinearMessage.k_getter(14) + deltaLinearMessage.w_getter(14);

			for(int i = 27; i < 36; i++)
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);//w[14][17],...,w[14][25]
			}
		case 1062:
			round = 14;
			/* 62: a[15][26]=0*/
			if(deltaLinearMessage.a_getter(15) & B26)
			{
				update_before_correcting(62, deltaLinearMessage, MESSAGE_MASK_CORRECTION_62);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[62], gEquationCorrections[62], round))
				{
					return -9;
				}
			}
			/* 63: a[15][27]=0 */
		case 1063:
			round = 14;
			if(deltaLinearMessage.a_getter(15) & B27)
			{

				update_before_correcting( 63, deltaLinearMessage, MESSAGE_MASK_CORRECTION_63);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 63], gEquationCorrections[ 63], round))
				{
					return -10;
				}
			}
			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[36]);//w[14][29]
			/* 64: a[15][29]=1 */
		case 1064:
			round = 14;
			if(!(deltaLinearMessage.a_getter(15) & B29))
			{
				update_before_correcting( 64, deltaLinearMessage, MESSAGE_MASK_CORRECTION_64);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 64], gEquationCorrections[ 64], round))
				{
					return -11;
				}
			}
			deltaLinearMessage.test_and_correct_linear_equation(linearEquations[37]);//w[14][31]


			// a[15][31]=1
		case 1065:
			round = 14;
			if(!(deltaLinearMessage.a_getter(15) & B31))
			{
				watchDog1531++;
				if(watchDog1531 > 1)
				{
					watchDog1531 = 0;
					update_before_correcting( 65, deltaLinearMessage, MESSAGE_MASK_CORRECTION_65);
					if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[ 65], gEquationCorrections[ 65], round))
					{
						return -12;
					}
				}
				else
				{
					deltaLinearMessage.w_setter(12) ^= B0;
//					deltaLinearMessage.updatedToRound_setter() = 11;
					round = 12;
					//					deltaLinearMessage.messageMask[13] = deltaLinearMessage.messageMask[14] = 0;
					break;
				}
			}
			watchDog1531 = 0;
			deltaLinearMessage.update_a5_a30_f_k(14);

#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
			/*A[16]*/
		case 15:
			round = 15;
			// deltaLinearMessage.w_setter(round) = (deltaLinearMessage.w_setter(round) & ~MESSAGE_MASK[round]) | MESSAGE_VALUE[round];
			deltaLinearMessage.w_setter(15) &= 0xffffc01f;
			deltaLinearMessage.w_setter(15) |= B13;
			/*aux cond for cond 223: 1  10  7  2    1   e  10*/
			if(deltaLinearMessage.a_getter(11) & B7)
				deltaLinearMessage.w_setter(15) &= NB5;
			else
				deltaLinearMessage.w_setter(15) |= B5;
			/*aux cond for cond 223: 1  10  10  1    1   e  10*/
			if(deltaLinearMessage.w_setter(11) & B15)
				deltaLinearMessage.w_setter(15) |= B8;
			else
				deltaLinearMessage.w_setter(15) &= NB8;
			deltaLinearMessage.set_a_w_comp(14, B5);
			deltaLinearMessage.set_a_w_comp(14, B6);
			deltaLinearMessage.set_a_w_comp(14, B7);

			/*aux 1306:***a[15][9]=a[16][9]=>no diff in f[18][7]*/
			if(((deltaLinearMessage.a_getter(16) ^ deltaLinearMessage.a_getter(15)) & B9))
			{
				deltaLinearMessage.w_setter(15) ^= B9;
				deltaLinearMessage.a_setter(16) = deltaLinearMessage.w_getter(15) + deltaLinearMessage.k_getter(15);
			}

			/***********************************************************************************/

			//			deltaLinearMessage.a_setter(16) = deltaLinearMessage.k_getter(15) + deltaLinearMessage.w_getter(15);

			for(int i = 38; i < 40; i++)//w[15][0], w[15][1]
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);
			}

			for(int i = 40; i < 52; i++)//w[15][15],..., w[15][25], w[15][27]
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);
			}
		case 1067:
			round = 15;
			/* a[16][27]^w[14][26] = 1 */
			if(!((deltaLinearMessage.a_getter(16) ^ (deltaLinearMessage.w_getter(14) << 1)) & B27))
			{
				update_before_correcting(67, deltaLinearMessage, MESSAGE_MASK_CORRECTION_67);
				if(!deltaLinearMessage.correct_equation_using_all_corrections( gNumberOfCorrections[67], gEquationCorrections[67], round))
				{
					return -13;
				}
			}

			/* w[15][30], w[15][31] */
			for(int i = 52; i < NUM_OF_LINEAR_EQUATIONS; i++)
			{
				deltaLinearMessage.test_and_correct_linear_equation(linearEquations[i]);
			}
			//TODO:remove testing of linear equations in the live run
			{
				linearEquations[5].solution = (deltaLinearMessage.a_getter(13) & B2) ? 0 : 1;
				for(int i = 0; i < NUM_OF_LINEAR_EQUATIONS; i++)
				{
					if(deltaLinearMessage.test_linear_equation(linearEquations[i]))
					{
						printf("linear equ %d unsolved\n",i);
						rs_pause();
					}
				}
			}
			//			for(int i = 5; i < 16;i++)
			//			{
			//				u32 a = 0;
			//				for(int j=0; j< 52; j++)
			//					a |= linearEquations[j].w[i];
			//				printf("0x%08x,", a);
			//			}
			//			rs_pause();

			deltaLinearMessage.a_setter(16) = deltaLinearMessage.w_getter(15) + deltaLinearMessage.k_getter(15);
			deltaLinearMessage.update_a5_a30_f_k(15);//recalculate a5(16) a30(16) f(17) k(17)

			deltaLinearMessage.messageMask[ 5] = 0xffff803f;
			deltaLinearMessage.messageMask[ 6] = 0xffff207f;
			deltaLinearMessage.messageMask[ 7] = 0xffffc01f;
			deltaLinearMessage.messageMask[ 8] = 0xffff800f;
			deltaLinearMessage.messageMask[ 9] = 0xfffed01f;
			deltaLinearMessage.messageMask[10] = 0xfffe801f;
			deltaLinearMessage.messageMask[11] = 0xffff001f;
			deltaLinearMessage.messageMask[12] = 0xfffda01f;
			deltaLinearMessage.messageMask[13] = 0xffff800f;
			deltaLinearMessage.messageMask[14] = 0xfffe901f;
			deltaLinearMessage.messageMask[15] = 0xffffc01f;
			deltaLinearMessage.check_conformance(68);

#if DEBUG_LOG_LEVEL_UPTO_67
			fprintf(gDebugLogFile, "\tL-R%2d: %08x %08x\n", round, deltaLinearMessage.w_getter(round), deltaLinearMessage.a_getter(round+1));
#endif
			round = 16;
			break;
		default:
			fprintf(stderr, "Invalid round! (%d)\n", round);
			exit(1);
		}
	}
	//	deltaLinearMessage.verify(0,false);
	return 16;
}

