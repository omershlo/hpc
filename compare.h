#ifndef __COMPARE_H__
#define __COMPARE_H__

#include "wbs.h"

int  cmp(const int p, const int q);
int  cmpf(const float p, const float q);
int cmpd(const double p, const double q);
int  compare_corr_success(const void *p, const void *q);
int compare_corr_success_probability(const void *p, const void *q);
int  compare_neutral1(const void *p, const void *q);
int  compare_two_int(const void *p, const void *q);
int  compare_equ(const void *p, const void *q);
int  compare_success(const void *p, const void *q);
bool compare_pair(std::pair<int,int> a,std::pair<int,int> b);
#endif /*__COMPARE_H__*/
