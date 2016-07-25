//here I put utilities that may be deleted in the actual run
#ifndef __SHA_UTILS_H__
#define __SHA_UTILS_H__
#include "sha1.h"
#define __STDC_FORMAT_MACROS
/* #include <inttypes.h> */

extern linear_equation  linearEquations[NUM_OF_LINEAR_EQUATIONS];

uint64_t rdtsc();

#define RESET   "\033[0m"
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLU     "\033[1m\033[34m"      /* Bold Blue */
#define EQUATION_TO_ROUND(eq) (16 + (eq>72) + ((eq>75)?2:0) + (eq>81) + (eq>83) + (eq>86) + (eq>89) + (eq>91) + (eq>93) + ((eq>95)?3:0))
#define FIRST_CONF_TO_RECORD 80
#define NUMBER_OF_NEUTRALS_TO_RECURSE 17

bool solve89_v1(SHA1& ref);
void verify_conformance(SHA1& ref);
void c_compute_state(SHA1 &ref, int round);
int  c_check_Inequality(SHA1 &base, SHA1 &comparedTo, int upToRound);
void print_second_message(SHA1& ref);
void conformance_counter(int conformance);
void compute_and_print_equations_statistics(int *uncorrected, int *corrected, const char *statisticsFileName);
void rs_pause();
void print_diffs(FILE *fp, uint32_t x, uint32_t y);
void print_duo(uint32_t a, uint32_t b, FILE *fp);
void print_duo_nl(uint32_t a, uint32_t b, FILE *fp);
void seek_message(int n, FILE* fp);
void recurse_neutrals_greedy_type(int predicateID);
u32 sub_to_xor(u32 w, u32 sub);
u32 xor_to_sub(u32 w, u32 xorDiff);
int replace(int equNum);
int unreplace(int index);
bool test_linear_equations(SHA1& m);
bool compare_round(SHA1& p, SHA1& q, int r);
bool compare_round_no_getter(SHA1& p, SHA1& q, int r);
void solve_90_105(SHA1& ref);
#if DEBUG_LOG_LEVEL > 0
extern FILE *gDebugLogFile;
#endif

#if PERFORMANCE == 1
extern int gConfcounter[150];
void performance_measurments(performance_variables &a);
#endif

#endif /* __SHA_UTILS_H__ */

