#ifndef MODIFICATIONS_H_
#define MODIFICATIONS_H_

#include "types1.h"
#include "sha1.h"
#include "sha_utils.h"
#include "ReducedSha.h"

extern correctionSet** gEquCorr;
extern int *gNuMOfCorr;

bool w_Or_state(SHA1& ref, int round, u32 xorDiff, u32& stateSubDiff, bool wOrState, ReducedSha& baseMsg);
bool mod(SHA1& ref, int round, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool test_corrections(SHA1& ref, SHA1& tmp, int equToCorrect, int conformance, int conformanceToTest, bool testAll);
bool mod_5(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_5_6(SHA1& ref, u32 xorDiff5, u32 xorDiff6, ReducedSha& baseMsg);
bool mod_5_10(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
int modifyAndUpdate_6(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg);
int modifyAndUpdate_6_bit8(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg);
bool mod_6(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_6(SHA1& ref, u32 xorDiff, ReducedSha& baseMsg, int& roundToStart);
bool mod_6_8(SHA1& ref, u32 xorDiff6, u32 xorDiff8, bool wOrState8, ReducedSha& baseMsg);
bool mod_6_9(SHA1& ref, u32 xorDiff6, u32 xorDiff9, bool wOrState9, ReducedSha& baseMsg);
bool mod_6_10(SHA1& ref, u32 xorDiff6, u32 xorDiff10, bool wOrState10, ReducedSha& baseMsg);
bool mod_6_11(SHA1& ref, u32 xorDiff6, u32 xorDiff11, bool wOrState11, ReducedSha& baseMsg);
bool mod_7(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_7_12(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_7_12(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 xorDiff12, bool wOrState12, ReducedSha& baseMsg);
bool mod_7_12_14(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 xorDiff12, bool wOrState12, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg);
bool mod_7_15(SHA1& ref, u32 xorDiff, bool wOrState, u32 a20XorDiff, ReducedSha& baseMsg);
bool mod_7_15(SHA1& ref, u32 xorDiff7, bool wOrState7, u32 a20XorDiff, bool wOrState15, ReducedSha& baseMsg);
bool mod_8_11(SHA1& ref, u32 xorDiff8, bool wOrState8, u32 xorDiff11, bool wOrState11, ReducedSha& baseMsg);
bool mod_9(SHA1& ref, u32 xorDiff9, bool wOrState9, ReducedSha& baseMsg);
bool mod_9(SHA1& ref, u32 stateXorDiff, ReducedSha& baseMsg);
bool mod_9_op(SHA1& ref, u32 stateXorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_9_14(SHA1& ref, u32 stateXorDiff9, bool wOrState9, u32 stateXorDiff14, bool wOrState14, ReducedSha& baseMsg);
bool mod_9_14(SHA1& ref, u32 stateXorDiff, ReducedSha& baseMsg);
bool mod_9_14(SHA1& ref, u32 stateXorDiff1, u32 stateXorDiff2, ReducedSha& baseMsg);
bool mod_10(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);//wOrState = true => w
bool mod_10_13(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 xorDiff13, bool wOrState13, ReducedSha& baseMsg);
bool mod_10_14(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg);
bool mod_10_15(SHA1& ref, u32 xorDiff10, bool wOrState10, u32 a20XorDiff, ReducedSha& baseMsg);
bool mod_10_15(SHA1& ref, u32 xorDiff10, bool wOrState10, ReducedSha& baseMsg);
bool mod_11(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_11_14(SHA1& ref, u32 xorDiff11, bool wOrState11, u32 xorDiff14, bool wOrState14 , ReducedSha& baseMsg);
bool mod_12(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_13(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& baseMsg);
bool mod_13_14(SHA1& ref, u32 xorDiff13, bool wOrState13, u32 xorDiff14, bool wOrState14, ReducedSha& baseMsg);
bool mod_13_15(SHA1& ref, u32 xorDiff13, bool wOrState13, u32 a20XorDiff, ReducedSha& baseMsg);
bool mod_14_15(SHA1& ref, u32 xorDiff14, bool wOrState14, u32 a20XorDiff, ReducedSha& baseMsg);
bool mod_14(SHA1& ref, u32 xorDiff, bool wOrState, ReducedSha& savedMsg);
bool mod_15(SHA1& ref, u32 a20XorDiff, bool wOrState, ReducedSha& baseMsg);
bool corr_15(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int restoreFromRound));
bool corrAtRound15(SHA1& ref, u32 d, int equationToTest);
bool allCorrectionsRound15(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int equToTest), int equationToTest);
bool corrAtRound15(SHA1& ref, u32 d, int equationToTest, int &conformance);
bool allCorrectionsRound15(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int equToTest, int &conf), int equationToTest, int &conformance);
//bool CorrectionsRound15_5(SHA1& ref, bool (*corrAtRound15)(SHA1& ref, u32 d, int equToTest), int equationToTest);
int updateAndTest(SHA1& ref);
int updateAndTest(SHA1& ref, int roundToStart);
#endif /* MODIFICATIONS_H_ */
