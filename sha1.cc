#define __STDC_FORMAT_MACROS
#include "sha1.h"
#include "sha_utils.h"
#include "duplicates.h"
#include "ReducedSha.h"
//#define DEBUG

ReducedSha m;

void SHA1::print_message(FILE *fp)
{
	for(int i = 5; i < 16; i++)
		fprintf(fp, "%08x ",mW[i]);
	fprintf(fp, "\n");
	fflush(fp);
	return;
}

void SHA1::print_message(char* path, int firstUnSatisfied)
{
	char fileName[100];
	sprintf(fileName, "%s%d", path,firstUnSatisfied);
	FILE *fp = fopen(fileName, "a");
	print_message(fp);
	fclose(fp);
	return;
}

bool check_for_duplicates(Key message, messageID id, messageID& alreadyInId, mHashTable& hashTable)
{
	std::pair<mHashTable::iterator, bool> returnedValue;
	returnedValue = hashTable.insert(std::pair<Key,messageID>(message,id));
	if(returnedValue.second == false)
	{
		alreadyInId = returnedValue.first->second;
		//		fprintf(stderr, "x %4d %2d %d %d %2d: %4d %2d %d %d %2d\n", id[0], id[1], id[2], id[3], id[4], alreadyInId[0], alreadyInId[1], alreadyInId[2], alreadyInId[3], alreadyInId[4]);
		//		rs_pause();
		return true;
	}
	//	fprintf(stderr, "%4d %2d %d %d %2d\n", id[0], id[1], id[2], id[3], id[4]);
	return false;
}

bool SHA1::modify_message(int rnd, u32 bit, unsigned char correctionFlags, mStack &newStack, messageInStack& m)
{
	u32 d = (w_getter(rnd+1) & BIT_BY_INDEX[bit+5]) ? BIT_BY_INDEX[bit] : -BIT_BY_INDEX[bit];
	if(((w_getter(rnd) + d) ^ w_getter(rnd)) & messageMask[rnd])
		return false;
	SHA1 derivedSha = *this;
	derivedSha.w_setter(rnd) += d;
	derivedSha.w_setter(rnd+1) ^= BIT_BY_INDEX[bit+5];
	if(correctionFlags & B1)
	{
		u32 xorDiffDisturbance = a_getter(rnd+1) ^ derivedSha.a_getter(rnd+1);
		u32 IFdiff = state_difference_to_IF_difference1(xorDiffDisturbance, rnd);
		if(IFdiff)
		{
			if(((derivedSha.w_getter(rnd+2) - IFdiff) ^ derivedSha.w_getter(rnd+2)) & messageMask[rnd+2])
				return false;
			derivedSha.w_setter(rnd+2) -= IFdiff;
		}
		else return false;//(correctionFlags & B1) is set but no correction is required. Hence, this modification is the same as a modification with (correctionFlags & B1) unset
	}
	else return false;//modification violates messageMask[] conditions
	derivedSha.firstUnsatisfiedEquation_setter() = derivedSha.compute_firstUnsatisfied();
	if(derivedSha.firstUnsatisfiedEquation_setter() > 67)
	{
		m.message = derivedSha.extract_message();
		m.id[4] = derivedSha.firstUnsatisfiedEquation_getter();
		newStack.push(m);
		m.stackIndex++;
	}

	return true;
}

void SHA1::derive_delta_neutral(int linearIndex, mStack &newStack)
{
	messageInStack m;
	m.message = extract_message();
	m.id = id;
	m.id[2] = linearIndex;
	m.id[3] = 0;
	m.id[4] = id[4] = firstUnsatisfiedEquation_getter();
	newStack.push(m);
	m.stackIndex++;
	modify_message(13,  6, 1, newStack, m);
	modify_message(13,  6, 3, newStack, m);
	//	modify_message(13,  7, 1, newStack, m);
	//	modify_message(13,  7, 3, newStack, m);
	modify_message(13,  8, 1, newStack, m);
	modify_message(13,  8, 3, newStack, m);
	modify_message(13,  9, 1, newStack, m);
	modify_message(13, 11, 1, newStack, m);
	modify_message(13, 11, 3, newStack, m);
}

int SHA1::derive_delta_linear(int newMessageCounter, linear_equation* linearEquations, mStack &newStack)
{
	mHashTable linearHashTable;
	SHA1 derivedSha1;
	SHA1 derivedSha2;
	messageID alreadyInID;//if the message we want to insert is already in, alreadyInID will be updated with the id of the colliding message
	Key linear;//we verify that all linear solutions are different
	for(int baseIndex = 0; baseIndex < 16; baseIndex++)
	{
		if(apply_linear_modification_and_fix(*this, derivedSha1, linearEquations, baseIndex, 36))
		{
			derivedSha1.id = {newMessageCounter, baseIndex, 0, 0, 0};
			derivedSha1.extract_linear_solution(linear);
			if(!check_for_duplicates(linear, derivedSha1.id, alreadyInID, linearHashTable))
			{
				derivedSha1.correct_message_up_to_equation(79);
				if(derivedSha1.firstUnsatisfiedEquation_getter() >= 79)
				{
					derivedSha1.derive_delta_neutral(0, newStack);
				}
				derivedSha2 = derivedSha1;
				derivedSha2.w_setter(15) ^= B16;
				derivedSha2.w_setter(14) ^= B12;
				derivedSha2.firstUnsatisfiedEquation_setter() = derivedSha2.compute_firstUnsatisfied();
				derivedSha2.id = {newMessageCounter, baseIndex, 1, 0, derivedSha2.firstUnsatisfiedEquation_getter()};
				derivedSha2.extract_linear_solution(linear);
				if(!check_for_duplicates(linear, derivedSha2.id, alreadyInID, linearHashTable))//check for duplicate is performed once
				{
					derivedSha2.correct_message_up_to_equation(79);
					if(derivedSha2.firstUnsatisfiedEquation_getter() >= 79)
					{
						derivedSha2.derive_delta_neutral(1, newStack);
					}
					derivedSha2 = derivedSha1;
					derivedSha2.w_setter(15) ^= B14;
					derivedSha2.w_setter(14) ^= B12;
					derivedSha2.firstUnsatisfiedEquation_setter() = derivedSha2.compute_firstUnsatisfied();
					derivedSha2.id = {newMessageCounter, baseIndex, 2, 0, derivedSha2.firstUnsatisfiedEquation_getter()};
					derivedSha2.correct_message_up_to_equation(79);
					if(derivedSha2.firstUnsatisfiedEquation_getter() >= 79)
					{
						derivedSha2.derive_delta_neutral(2, newStack);
					}
					derivedSha2 = derivedSha1;
					derivedSha2.w_setter(15) ^= B16;
					derivedSha2.w_setter(15) ^= B14;
					derivedSha2.firstUnsatisfiedEquation_setter() = derivedSha2.compute_firstUnsatisfied();
					derivedSha2.id = {newMessageCounter, baseIndex, 3, 0, derivedSha2.firstUnsatisfiedEquation_getter()};
					derivedSha2.correct_message_up_to_equation(79);
					if(derivedSha2.firstUnsatisfiedEquation_getter() >= 79)
					{
						derivedSha2.derive_delta_neutral(3, newStack);
					}
				}
			}
		}
	}
	return 1;
}

messageArray SHA1::extract_message()
{
	messageArray t = {mW[5],mW[6],mW[7],mW[8],mW[9],mW[10],mW[11],mW[12],mW[13],mW[14],mW[15]};
	return t;
}
// at the end of round, a_getter(round + 1) is known and we update a5(round + 1) a30(round + 1) f(round + 2) k(round + 2)
// round 19:  a_getter(20) = k(20) + w(19) = K_00_19 + a5(19) + f(19) + a30(15) +w(19)
void SHA1::update_a5_a30_f_k(int round)
{
	mA5[round + 1] =  ROTATE(mA[round+1], 5);
	mA30[round + 1] = ROTATE(mA[round+1], 30);

	if(round < 18)
		mF[round + 2] = F_00_19(mA[round+1], mA30[round], mA30[round - 1]);
	else if(round < 38)
		mF[round + 2] = F_20_39(mA[round+1], mA30[round], mA30[round - 1]);
	else if(round < 58)
		mF[round + 2] = F_40_59(mA[round+1], mA30[round], mA30[round - 1]);
	else
		mF[round + 2] = F_60_79(mA[round+1], mA30[round], mA30[round - 1]);

	if (round < 19)
		mK[round+1] = K_00_19 + mA5[round+1] + mF[round+1] + mA30[round - 3];
	else if (round < 39)
		mK[round+1] = K_20_39 + mA5[round+1] + mF[round+1] + mA30[round - 3];
	else if (round < 59)
		mK[round+1] = K_40_59 + mA5[round+1] + mF[round+1] + mA30[round - 3];
	else
		mK[round+1] = K_60_79 + mA5[round+1] + mF[round+1] + mA30[round - 3];
	//	computek(round + 1);
	mUpdatedToRound = round;
}

void SHA1::extend_state()
{
	int round = mUpdatedToRound + 1;
	if(round >= 16)
		Xupdate(mW[round], mW[round - 3], mW[round - 8], mW[round - 14], mW[round - 16]);
	mA[round + 1]   = mW[round] + mK[round];
	update_a5_a30_f_k(round);
}

/* may be used when a[i+1] is not modified, i.e., the computation of
   a5, a30, f in advance remain valid. This ver is good when
   corrections are tested.*/
void SHA1::update_state_till_round(int round)
{
	while(round > updatedToRound_getter())
		extend_state();
}

//val = 0 => a(rnd+1)  = 0
//val = 1 => a(rnd+1)  = 1
//val = 2 => a(rnd+1)  = a(rnd)
//val = 3 => a(rnd+1) != a(rnd)
void SHA1::test_and_corr(int rnd, u32 bit, int val)
{
	switch(val)
	{
	case 3:
		if((mA[rnd+1] ^ mA[rnd]) & bit)
			return;
		else
			break;
	case 2:
		if(!((mA[rnd+1] ^ mA[rnd]) & bit))
			return;
		else
			break;
	case 1:
		if(mA[rnd+1] & bit)
			return;
		else
			break;
	case 0:
		if(!(mA[rnd+1] & bit))
			return;
		else
			break;
	}

	mW[rnd] ^= bit;
	mA[rnd+1] = mW[rnd] + mK[rnd];
	return;
}

bool SHA1::operator ==(SHA1 &s)
						{
	for (int i=5; i<16; ++i)
	{
		if(w_getter(i) != s.w_getter(i))
			return false;
	}
	return true;
						}

bool SHA1::operator !=(SHA1 &s) {
	for (int i=5; i<16; ++i)
		if(w_getter(i) != s.w_getter(i))
			return true;
	return false;
}


void SHA1::extract_linear_solution(Key& linearW)
{
	linearW.a[0] = w_getter(5) & 0x00078000;
	linearW.a[1] = w_getter(6) & 0x03ff200e;
	linearW.a[2] = w_getter(7) & 0xc3ffc002;
	linearW.a[3] = w_getter(8) & 0xc3ff800b;
	linearW.a[4] = w_getter(9) & 0xc3fed005;
	linearW.a[5] = w_getter(10) & 0xc3fe800f;
	linearW.a[6] = w_getter(11) & 0xc3ff0003;
	linearW.a[7] = w_getter(12) & 0x83fda00b;
	linearW.a[8] = w_getter(13) & 0xf3ff800f;
	linearW.a[9] = w_getter(14) & 0xa3fe900f;
	linearW.a[10] = w_getter(15)& 0xcbffc003;
}

int SHA1::test_and_correct_linear_equation(linear_equation equ)
{
	int i;
	int weight = 0;
	for(i = 5; i < 16; i++)
	{
		weight += HAMMING((equ.w[i] & mW[i]));
	}
	if((weight ^ equ.solution) & B0)
	{
		w_setter(equ.pivotWordIndex) ^=  BIT_BY_INDEX[(int)equ.pivotBitIndex];
		a_setter(equ.pivotWordIndex+1) = w_getter(equ.pivotWordIndex) + k_getter(equ.pivotWordIndex);
	}
	return (weight ^ equ.solution) & B0;
}

int SHA1::test_linear_equation(linear_equation equ)
{
	int i;
	int weight = 0;
	for(i = 5; i < 16; i++)
	{
		weight += HAMMING((equ.w[i] & mW[i]));
	}
	return ((weight ^ equ.solution) & B0);
}
//sets w(i+1)[j+5] = !a_getter(i+1)[j]
void SHA1::set_a_w_comp(int word, u32 bit)
{
	if(mA[word+1] & bit)
	{
		mW[word+1] &= ~(bit << 5);
	}
	else
	{
		mW[word+1] |= (bit << 5);
	}
	mA[word+2] = mW[word+1] + mK[word+1];
}

//sets w(i+5)[j-2] = !a_getter(i+1)[j]
void SHA1::set_e_w_comp(int word, u32 bit)
{
	if(mA[word+1] & bit)
	{
		mW[word+5] &= ~(bit >> 2);
	}
	else
	{
		mW[word+5] |= (bit >> 2);
	}
	mA[word+6] = mW[word+5] + k_getter(word+5);
}

u32 SHA1::state_difference_to_IF_difference1(uint32_t stateDisturbanceXor, int round)
{
	uint32_t xorDiff;
	//r+2
	xorDiff = (a_getter(round) ^ a_getter(round-1)) & (stateDisturbanceXor << 2);
	if(xorDiff)
	{
		return (f_getter(round+2) ^ (xorDiff >> 2)) - f_getter(round+2);
	}
	return 0;
}

u32 SHA1::state_difference_to_IF_difference2(uint32_t stateDisturbanceXor, int round)
{
	uint32_t xorDiff;
	//r+3
	xorDiff = a_getter(round+2) & (stateDisturbanceXor >> 2);
	if(xorDiff)
	{
		return (f_getter(round+3) ^ xorDiff) - f_getter(round+3);
	}
	return 0;
}

u32 SHA1::state_difference_to_IF_difference3(uint32_t stateDisturbanceXor, int round)
{
	uint32_t xorDiff;
	//r+4
	xorDiff = (a_getter(round+3) ^ (stateDisturbanceXor >> 2)) & (stateDisturbanceXor >> 2);
	if(xorDiff)
	{
		return (f_getter(round+4) ^ xorDiff) - f_getter(round+4);
	}
	return 0;
}


//TODO: correct_equa..() and apply_sing...() do mod=*this. need to remove one of the substitutions
bool SHA1::correct_equation_using_all_corrections(const int numberOfCorrections, correctionSet *corr, const int round)
{
	SHA1 mod;
	for(int correctionIndex = numberOfCorrections - 1; correctionIndex > - 1; correctionIndex--)
	{
		if(corr[correctionIndex].l)
		{
			mod = *this;
			if(disturb_correct_and_test_linear(mod, corr[correctionIndex].wb[0].wbl , firstUnsatisfiedEquation_getter(), round))
			{
#if MEASURE_CORRECTIONS_PROBABILITY
				corr[correctionIndex].success++;
#endif
				*this = mod;
				return true;
			}
#if MEASURE_CORRECTIONS_PROBABILITY
			else
				corr[correctionIndex].fail++;
#endif
		}
		else if(corr[correctionIndex].nl==1)
		{
			mod = *this;
			if(disturb_correct_and_test(mod, corr[correctionIndex].wb[0].wbnl, 0,firstUnsatisfiedEquation_getter(), round))
			{
				//				if((firstUnsatisfiedEquation_getter()==65) && (correctionIndex == (numberOfCorrections - 3)))
				//				{
				//					compare_duo(mod, 8, 15, stderr);
				//					rs_pause();
				//				}
#if MEASURE_CORRECTIONS_PROBABILITY
				corr[correctionIndex].success++;
#endif
				//				fprintf(stderr,"succeeded\n");
				*this = mod;
				return true;
			}
#if MEASURE_CORRECTIONS_PROBABILITY
			else
			{
				//				fprintf(stderr,"failed\n");
				//				if(firstUnsatisfiedEquation_getter()==56)
				//				{
				//					compare_duo(mod, 9, 14, stderr);
				//					rs_pause();
				//				}
				corr[correctionIndex].fail++;
			}
#endif
		}
		else if(apply_single_correction_and_check_neutral(mod, corr[correctionIndex], round))
		{
#if MEASURE_CORRECTIONS_PROBABILITY
			corr[correctionIndex].success++;
#endif
			*this = mod;
			return true;
		}
#if MEASURE_CORRECTIONS_PROBABILITY
		else
			corr[correctionIndex].fail++;
#endif
	}
	return false;
}

//correct_message_up_to_equation(int equ) may be used up to equation 82
bool SHA1::correct_message_up_to_equation(int equ)
{
	int equToCorrect = firstUnsatisfiedEquation_getter();
	if(equToCorrect >= equ)
		return 1;
	bool isCorrected = true;
	SHA1 modifiedMessage;
	while(firstUnsatisfiedEquation_getter() < equ)
	{
		isCorrected = false;
		equToCorrect = firstUnsatisfiedEquation_getter();
		for(int correctionIndex = gNumberOfCorrections[equToCorrect] - 1; correctionIndex > - 1; correctionIndex--)
		{
			if(apply_single_correction_and_check_neutral(modifiedMessage, gEquationCorrections[equToCorrect][correctionIndex],	EQUATION_TO_ROUND(equToCorrect)) > equToCorrect)
			{
				//								if((equToCorrect==68) && (correctionIndex==11))
				//								{
				//									compare_duo(modifiedMessage,8,17,stderr);rs_pause();
				//								}
				isCorrected = true;
				*this = modifiedMessage;
#if MEASURE_CORRECTIONS_PROBABILITY
				gEquationCorrections[equToCorrect][correctionIndex].success++;
#endif
				break;
			}
			else
			{
#if MEASURE_CORRECTIONS_PROBABILITY
				gEquationCorrections[equToCorrect][correctionIndex].fail++;
#endif
			}
		}
		if(!isCorrected)
			break;
	}
	return isCorrected;
}
#undef TEST_DUPLICATES
#ifdef TEST_DUPLICATES
int SHA1::correct_message_up_to_equation(int equ, mHashTable& baseHashTable, messageID& alreadyInID)
{
	//	static i64 t0;
	//	static i64 t1;

	//	std::chrono::time_point<std::chrono::system_clock> start, end;
	//	extern std::chrono::duration<double> elapsedSeconds;
	//	extern std::chrono::duration<double> elapsedSecondsTotal;
	int equToCorrect = firstUnsatisfiedEquation_getter();
	if(equToCorrect >= equ)
		return 1;
	Key currMessage;//the message we want to insert
	bool isCorrected = true;
	SHA1 modifiedMessage;
	id[4] = equToCorrect;
#ifdef DEBUG
	SHA1 tmp = *this;
	tmp = *this;
	tmp.updatedToRound_setter() = 4;
	tmp.check_conformance_no_aux(12);
	if(tmp.firstUnsatisfiedEquation_getter() < 70){
		rs_pause();
	}
#endif
	while(firstUnsatisfiedEquation_getter() < equ)
	{
		for(int i = 0; i < 11; i++)
		{
			currMessage.a[i] = w_getter(i+5);
		}
		if(check_for_duplicates(currMessage, id, alreadyInID, baseHashTable))
		{
			return 2;
		}
		isCorrected = false;
		equToCorrect = firstUnsatisfiedEquation_getter();
#ifdef DEBUG
		tmp = *this;
		tmp.updatedToRound_setter() = 4;
		tmp.check_conformance_no_aux(12);
		if(tmp.firstUnsatisfiedEquation_getter() < 70) rs_pause();
		if(tmp.firstUnsatisfiedEquation_getter() != mFirstUnsatisfiedEquation){
			tmp.compare_duo_Sha1ParameterNotUpdated(*this, 5, 20, stderr);
			fprintf(stderr, "%d %d\n", tmp.firstUnsatisfiedEquation_getter(), firstUnsatisfiedEquation_getter());
			rs_pause();
		}
#endif
		m.copy(*this, 5, 22);
		switch(equToCorrect){
		case 83:
			if(solve83()){
				isCorrected = true;
				break;
			}
			break;
		case 84:
			if(solve84()){
				isCorrected = true;
				break;
			}
			break;
		case 85:
			if(solve85()){
				isCorrected = true;
				break;
			}
			break;
		case 86:
			if(solve86()){
				isCorrected = true;
				break;
			}
			break;
		case 87:
			if(solve87()){
				isCorrected = true;
				break;
			}
			break;
		case 88:
			if(solve88()){
				isCorrected = true;
				break;
			}
			break;
		case 89:
			if(solve89()) {
				isCorrected = true;
				break;
			}
			break;
		case 90:
			if(solve90()) {isCorrected = true; break;}
			break;
		}
		if((!isCorrected))// && (equToCorrect < 89))
		{
			for(int correctionIndex = gNumberOfCorrections[equToCorrect] - 1; correctionIndex > - 1; correctionIndex--)
			{
				if(apply_single_correction_and_check_neutral(modifiedMessage, gEquationCorrections[equToCorrect][correctionIndex],	EQUATION_TO_ROUND(equToCorrect)) > equToCorrect)
				{
					// if((equToCorrect==89) && (correctionIndex==9))
					// {
					// 	compare_duo(modifiedMessage,7,23,stderr);
					// 	rs_pause();
					// }
					isCorrected = true;
					*this = modifiedMessage;
					id[4] = firstUnsatisfiedEquation_getter();
#if MEASURE_CORRECTIONS_PROBABILITY
					gEquationCorrections[equToCorrect][correctionIndex].success++;
#endif
					break;
				}
				else
				{
					//					if((equToCorrect==86) && (correctionIndex==44))
					//					{
					//						compare_duo(modifiedMessage,8,22,stderr);rs_pause();
					//					}
#if MEASURE_CORRECTIONS_PROBABILITY
					if(modifiedMessage.firstUnsatisfiedEquation_getter()==equToCorrect)
					{
						gEquationCorrections[equToCorrect][correctionIndex].neutral++;
					}
					gEquationCorrections[equToCorrect][correctionIndex].fail++;
#endif
				}
			}
		}

		if(!isCorrected)
			break;
	}
	return isCorrected;
}
#else
int SHA1::correct_message_up_to_equation1(int equ)//, mHashTable& baseHashTable, messageID& alreadyInID)
{
	int equToCorrect = firstUnsatisfiedEquation_getter();
	if(equToCorrect >= equ)
		return 1;
	//		Key currMessage;//the message we want to insert
	bool isCorrected = true;

#ifdef DEBUG
	SHA1 tmp = *this;
#endif
	//	id[4] = equToCorrect;
	while(firstUnsatisfiedEquation_getter() < equ)
	{
		//				for(int i = 0; i < 11; i++)
		//				{
		//					currMessage.a[i] = w_getter(i+5);
		//				}
		//				if(check_for_duplicates(currMessage, id, alreadyInID, baseHashTable))
		//				{
		//					return 2;
		//				}
		isCorrected = false;
		equToCorrect = firstUnsatisfiedEquation_getter();

#ifdef DEBUG
		tmp = *this;
		tmp.updatedToRound_setter() = 4;
		tmp.check_conformance_no_aux(36);
		if(tmp.firstUnsatisfiedEquation_getter() != firstUnsatisfiedEquation_getter()){
			tmp.compare_duo_Sha1ParameterNotUpdated(*this, 5, 20, stderr);
			fprintf(stderr, "%d %d\n", tmp.firstUnsatisfiedEquation_getter(), firstUnsatisfiedEquation_getter());
			rs_pause();
		}
#endif
		m.copy(*this, 5, 22);
		switch(equToCorrect){
		case 83:
			if(solve83()){isCorrected = true;break;}
			break;
		case 84:
			if(solve84()){isCorrected = true;break;}
			break;
		case 85:
			if(solve85()){isCorrected = true;break;}
			break;
		case 86:
			if(solve86()){isCorrected = true;break;}
			break;
		case 87:
			if(solve87()){isCorrected = true;break;}
			break;
		case 88:
			if(solve88()){isCorrected = true;break;}
			break;
		case 89:
//			if(solve89_v1(*this)){isCorrected = true;break;}
			if(solve89()){isCorrected = true;break;}
			break;
		default:
			break;
		}

		if(!isCorrected)
		{
			SHA1 modifiedMessage;
			for(int correctionIndex = gNumberOfCorrections[equToCorrect] - 1; correctionIndex > - 1; correctionIndex--)
			{
				if(apply_single_correction_and_check_neutral(modifiedMessage, gEquationCorrections[equToCorrect][correctionIndex],	EQUATION_TO_ROUND(equToCorrect)) > equToCorrect)
				{
					isCorrected = true;
					*this = modifiedMessage;
					//					id[4] = firstUnsatisfiedEquation_getter();
#if MEASURE_CORRECTIONS_PROBABILITY
					gEquationCorrections[equToCorrect][correctionIndex].success++;
#endif
					break;
				}
				else
				{
#if MEASURE_CORRECTIONS_PROBABILITY
					if(modifiedMessage.firstUnsatisfiedEquation_getter()==equToCorrect)
					{
						gEquationCorrections[equToCorrect][correctionIndex].neutral++;
					}
					gEquationCorrections[equToCorrect][correctionIndex].fail++;
#endif
				}
			}
		}
		if(!isCorrected)break;
	}
	return isCorrected;
}
#endif
