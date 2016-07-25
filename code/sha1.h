#ifndef SHA1_H__
#define SHA1_H__
#define TEST_DUPLICATES

#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <chrono>
#include "types1.h"
#include "wbs.h"
#include "CorrectionSet.h"

extern int *gNumberOfCorrections;
extern correctionSet **gEquationCorrections;
const u32 linearVar[11] = {0x00078000, 0x03ff200e, 0xc3ffc002, 0xc3ff800b, 0xc3fed005, 0xc3fe800f, 0xc3ff0003, 0x83fda00b, 0xf3ff800f, 0xa3fe900f, 0xcbffc003};

enum attack_stage {INITIALIZED, UPTO_67, _68_TO_89, _90_TO_97, ABOVE_97};

struct ReducedSha;
struct Key;
//TODO get rid of setting updatedToRound() from outside (use setters), lazy evaluate w, etc above 30, etc
class SHA1
{
public:
	messageArray extract_message();
	void extend_state();
	void verify_state_access(int round)
	{
		while(updatedToRound_getter() < round)
			extend_state();
	}

	uint32_t &w_setter(const int rnd)
	{
		assert(rnd < 16);
		if(rnd <= updatedToRound_getter())
			mUpdatedToRound = rnd - 1;
		return mW[rnd];
	}

	uint32_t w_getter(const int rnd)
	{
		//TODO split verify_state_access to each of the different vars, so only required var is computed (i.e., one for w that does not update a, a5, etc)
		if(rnd >= 16)
			verify_state_access(rnd);
		return mW[rnd];
	}

	uint32_t &a_setter(const int rnd)
	{
		assert((rnd <= 16)||(rnd>=6));
		if(rnd <= updatedToRound_getter())
			mUpdatedToRound = rnd - 1;
		return mA[rnd];
	}

	uint32_t a_getter(const int rnd)
	{
		//		if(current_stage() != UPTO_67)
		verify_state_access(rnd - 1);
		return mA[rnd];
	}

	uint32_t a5_getter(const int rnd)
	{
		//		if(current_stage() != UPTO_67)
		verify_state_access(rnd - 1);
		return mA5[rnd];
	}

	uint32_t a30_getter(const int rnd)
	{
		//		if(current_stage() != UPTO_67)
		verify_state_access(rnd - 1);
		return mA30[rnd];
	}

	uint32_t f_getter(const int rnd)
	{
		//		if(current_stage() != UPTO_67)
		verify_state_access(rnd - 2);
		return mF[rnd];
	}

	uint32_t k_getter(const int rnd)
	{
		//		if(current_stage() != UPTO_67)
		verify_state_access(rnd - 1);
		return mK[rnd];
	}

	int &firstUnsatisfiedEquation_setter() 	 { return mFirstUnsatisfiedEquation;}
	int firstUnsatisfiedEquation_getter() const { return mFirstUnsatisfiedEquation;}
	int compute_firstUnsatisfied();

	int& updatedToRound_setter() 					 {return mUpdatedToRound;}
	int updatedToRound_getter() const 				 {return mUpdatedToRound; }

	int& windowWeight_setter() 						 {return mWindowWeight;}
	int windowWeight_getter() const 				 {return mWindowWeight;}

	int& windowWeightMask_setter() 						 {return mWindowWeightMask;}
	int windowWeightMask_getter() const 				 {return mWindowWeightMask;}

	bool isBase() const { return mIsBase;}
	void unsetIsBase() { mIsBase = false; }

	bool operator ==(SHA1& s);
	bool operator !=(SHA1& s);
	bool compare_linear_solution(SHA1& s);
	void extract_linear_solution(Key& linearW);
	void update_state_till_round(int rnd);
	void update_a5_a30_f_k(int round);
	void test_and_corr(int rnd, u32 bit, int val);
	void set_a_w_comp(int word, u32 bit);
	void set_e_w_comp(int word, u32 bit);
	void set_A_to_equal_W_using_carry(int round, int bit);
	void check_conformance(int start);
	void check_conformance_no_aux(int start);
	bool check_single_equation_by_order(int equationId);
	bool correct_equation_using_all_corrections(const int numberOfCorrections, correctionSet* corr, const int round);
	int apply_single_correction_and_check_neutral(SHA1& mod,const correctionSet correction, const int round) ;

	int disturb_correct_and_test_linear(SHA1& mod, const linearCorrection& linearCorrection, const int equationToCorrectIndex, const int round);
	void apply_disturbance(const nonLinearCorrection &x);
	void disturb_and_correct(SHA1& mod, const nonLinearCorrection& x);
	bool disturb_correct_and_test(SHA1& modmod, const nonLinearCorrection& x, const int nc,	const int equationToCorrectIndex, const int round);
	int disturb_correct_and_test(SHA1 &mod, CorrectionSet& c, const int equationToCorrect);
	void compare(SHA1 &s, int begin, int end, FILE *fp);
	void compare_duo(SHA1 &s, int begin, int end, FILE *fp);
	void compare_duo_Sha1ParameterNotUpdated(SHA1 &s, int begin, int end, FILE *fp);
	void print_message_and_state_duo(SHA1 &s, int begin, int end, FILE *fp);

	u32 Sub_differences_by_disturbanceXor(const Correction c, u32 (&messageXorDiff)[11], u32 (&messageSubDiff)[11], u32& f);
	u32 Sub_differences_by_disturbanceXor1(const Correction c, u32 (&messageXorDiff)[11], u32 (&messageSubDiff)[11], u32& f);
	u32 Compensate_w8_w13(u32 (&messageSubDiff)[11], u32 (&messageXorDiff)[11]);
	u32 state_difference_to_IF_difference1(uint32_t stateDisturbanceXor, int round);
	uint32_t state_difference_to_IF_difference2(uint32_t stateDisturbanceXor, int round);
	uint32_t state_difference_to_IF_difference3(uint32_t stateDisturbanceXor, int round);
	uint32_t state_difference_to_IF_difference12(uint32_t stateDisturbanceXor1, uint32_t stateDisturbanceXor2, int round);
	void state_difference_to_XOR_difference(uint32_t stateDisturbanceXor, int round, uint32_t *XORsub);

	bool solveEquation(SHA1& modifiedSha, int equToCorrect);

	bool solve83();
	bool solve83_8_8__9_8(u32 w9XorDiff, u32 w10XorDiff);
	bool solve83_9(u32 w10XorDiff);
	bool solve83_10_10(u32 w11XorDiff);
	bool solve83_10_6(u32 stateXorDiff);
	bool solve83_11(u32 stateXorDiff, u32 testF15Diff);
	bool solve83_11_7(u32 w12XorDiff);
	bool solve83_11_13(u32 w13Xor);
	bool solve83_12_6(u32 stateDiff);
	bool solve83_13(u32 w14XorDiff, u32 lcsCorr);
	bool solve83_14_8(u32 w15XorDiff);

	bool solve84();
	bool solve84_5(u32 stateXorDiff);
	bool solve84_7(u32 stateXorDiff);
	bool solve84_7_12(u32 stateXorDiff);
	bool solve84_9(u32 w10XorDiff);
	bool solve84_12(u32 w1Xor);
	bool solve84_13(u32 wXorDiff);
	bool solve84_14(u32 wXorDiff);
	bool solve84_15();

	bool solve85();
	bool solve85nextOrderFix(u32 stateXorDiff1,u32 start_round);
	bool solve85_5(u32 stateXorDiff1);
	bool solve85_5(u32 stateXorDiff1, u32 stateXorDiff2, u32 stateXorDiff3);
	bool solve85_7_12(u32 stateXor, u32 wXorDiff);
	bool solve85_8_8__10_7(u32 stateSubDiff1, u32 stateSubDiff2, bool carry, int& conformance);
	bool solve85_9(u32 stateXorDiff);
	bool solve85_10(u32 stateXorDiff, int& conformance);
	bool solve85_10__13(u32 stateXorDiff1, u32 stateXorDiff2);
	bool solve85_11_7(u32 w12XorDiff);
	bool solve85_13(u32 w14XorDiff);
	bool solve85_14(u32 wXorDiff);

	bool solve86();
	bool solve86_5(u32 stateXorDiff1, u32 stateXorDiff2, u32 stateXorDiff3, int& conformance);
	bool solve86_5bits_9_10(int& conformance);
	bool solve86_5bit10(int& conformance);
	bool solve86_5bit_9(int& conformance);
	bool solve86_5_13(u32 stateXorDiff1, u32 wXorDiff2, int& conformance);
	bool solve86_6(u32 xorDiff, int& conformance);
	bool solve86_10(u32 stateXorDiff, int& conformance);
	bool solve86_13(u32 w14XorDiff, int& conformance);
	bool solve86_14(u32 stateXorDiff, int& conformance);
	bool solve86_9(u32 stateXorDiff, int& conformance);
	bool solve86_11(u32 w12XorDiff, int& conformance);
	bool solve86_7(u32 stateXorDiff, int& conformance);

	bool solve87();
	bool solve87_5bits_9_10(int& conformance);
	bool solve87_5bit10(int& conformance);
	bool solve87_5bit_9(int& conformance);
	bool solve87_10(u32 stateXorDiff, int& conformance, bool wOrState);
	bool solve87_13(u32 w14XorDiff, int& conformance);
	bool solve87_14(u32 stateXorDiff, int& conformance);
	bool solve87_5_13(u32 xorDiff5, u32 wXorDiff13, int& conformance);
	bool mod87_5(u32 xorDiff);
	bool mod87_13(u32 wXorDiff);

	bool solve88();
	bool solve89();
	bool solve90();

	bool compute_sign(bool testMessageOrState, int index, u32 bit);
	int interpret_correction(specificationOfDifference c);//, u32 aSub[], u32 wXor[]);
	int correct_79_to_82();//u32 wSub[]);
	bool apply_corrections(u32 wSub[], int round, u32 disturbance);
	bool apply_corrections(u32 wSub[], int round, u32 disturbance, u32 correctionFalgs);
	u32 compute_disturbance(specificationOfDifference c);
	int compute_rnd_234(specificationOfDifference c, u32 xorDiffDisturbance, u32 subDiffMessage[16], u32 subDiffState[20]);
	int correct_message_up_to_equation(int equ, mHashTable& baseHashTable, messageID& alreadyInID);
	bool correct_message_up_to_equation(int equ);
	int correct_message_up_to_equation1(int equ);//, mHashTable& baseHashTable, messageID& alreadyInID);
	bool modify_message(int rnd, u32 bit, unsigned char correctionFlags, mStack& isBaseMessages,messageInStack& m);
	int  derive_delta_linear(int newMessageCounter, linear_equation* linearEquations, mStack& isBaseMessages);
	void derive_delta_neutral(int linearIndex, mStack &newStack);
	attack_stage current_stage() const {
		if (mFirstUnsatisfiedEquation <= 67)
			return UPTO_67;

		if (mFirstUnsatisfiedEquation <= 89)
			return _68_TO_89;

		if (mFirstUnsatisfiedEquation <= 97)
			return _90_TO_97;

		return ABOVE_97;
	}

	int test_and_correct_linear_equation(linear_equation equ);
	int test_linear_equation(linear_equation equ);
	void print_message(FILE *fp);
	void print_message(char* path, int firstUnSatisfied);
	void print_sha(FILE* fp)
	{
		for(int i = 0; i < 81; i++)
			fprintf(fp, "%08x %08x %08x %08x %08x %08x\n", mW[i], mA[i], mA5[i], mA30[i], mF[i], mK[i]);
		fprintf(fp, "messageMask: ");
		for(int i = 0; i < 16; i++)
			fprintf(fp, "%08x ",messageMask[i]);
		fprintf(fp,"\n");
		fprintf(fp, "mUpdatedToRound = %d\n", mUpdatedToRound);
		fprintf(fp, "minimalWeight = %d\n", minimalWeight);
		fprintf(fp, "mFirstUnsatisfiedEquation = %d\n", mFirstUnsatisfiedEquation);
		fprintf(fp, "lastSatisfiedEquationInWindow = %d\n", lastSatisfiedEquationInWindow);
		fprintf(fp, "mWindowWeight = %d\n",mWindowWeight);
		fprintf(fp, "mWindowWeightMask = %d\n", mWindowWeightMask);
		fprintf(fp, "mIsBase  = %d\n", (int)mIsBase);
	}
	void set_messageMask(){
		messageMask[5]=0xffff803f; messageMask[6]=0xffff207f; messageMask[7]=0xffffc01f; messageMask[8]=0xffff800f; messageMask[9]=0xfffed01f; messageMask[10]=0xfffe801f;
		messageMask[11]=0xffff001f;messageMask[12]=0xfffda01f;messageMask[13]=0xffff800f;messageMask[14]=0xfffe901f;messageMask[15]=0x0fffc01f;
	}

	u32 messageMask[16] = {0};
	int lastSatisfiedEquationInWindow = 89;
	int minimalWeight = 9;
	messageID id;


	//private:
	void return_conformance_order(int equationId);

	uint32_t mW[81] = {0xf49867bb, 0x9dfbd98f, 0xcc597023, 0x8215c718, 0x60acb18a,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t mA[81] = {0x13d15c13, 0x236de005, 0x416de0b8, 0x8bffff11, 0x0a800031, 0x107f0048,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//  a(-4,...,-1} = {0xb08f1943, 0xb8ca93f5, 0xbc06dffd, 0xa439992f}

	uint32_t mA5[81] = {0x7a2b8262, 0x6dbc00a4, 0x2dbc1708, 0x7fffe231, 0x50000621, 0x0fe00902,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//  a5(-4,...,-1} = {0x11e32876, 0x19527eb7, 0x80dbffb7, 0x873325f4}

	uint32_t mA30[81] = {0xc4f45704, 0x48db7801, 0x105b782e, 0x62ffffc4, 0x42a0000c, 0x041fc012,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// a30(-4,...,0} = = {0xec23c650, 0x6e32a4fd, 0x6f01b7ff, 0xe90e664b};

	uint32_t mF[81] = {0x6e03b5ff, 0x6d00e7ef, 0xc866464e, 0xc4d97704, 0x405b7800, 0x12db780e, 0x62a0ff8c,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t mK[81] = {0, 0xa3720729, 0xbfa68eee, 0x886a3919, 0xafd24ebe, 0xc61972aa,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	int mFirstUnsatisfiedEquation = 49;
	int mUpdatedToRound = 4;
	int mWindowWeight = MAXIMAL_WEIGHT;
	int mWindowWeightMask = 0;
	bool mIsBase  = true;
};


void print_sha(SHA1 &, FILE *);

bool initialize_random_message(SHA1&, FILE*);

int apply_linear_modification(SHA1&, const char, const char);

bool apply_linear_modification_and_fix(SHA1&, SHA1&, linear_equation[], int, int);

int test_and_fix_till_round_15(SHA1&, int, linear_equation[]);

bool check_for_duplicates(Key y, messageID id, messageID& alreadyInId, mHashTable &hashTable);

#endif /*__SHA1_H__*/
