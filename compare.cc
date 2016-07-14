#include "compare.h"

//#if STATISTICS>0
//#include "statistics.h"
//#endif

int cmp(const int p, const int q)
{
    return (p > q) - (p < q);
}
int cmpf(const float p, const float q)
{
    return (p > q) - (p < q);
}
int cmpd(const double p, const double q)
{
    return (p > q) - (p < q);
}

#if STATISTICS > 0
int compare_corr_success(const void *p, const void *q)//correction success
{
    return cmp(((correctionSet*)p)->success, ((correctionSet*)q)->success);
}
int compare_corr_success_probability(const void *p, const void *q)//correction success
{
    return cmpd(((correctionSet*)p)->pc, ((correctionSet*)q)->pc);
}

int compare_neutral1(const void *p, const void *q)
{
    return cmp(((correctionSet*)p)->neutral1, ((correctionSet*)q)->neutral1);
}

bool compare_pair(std::pair<int,int> a,std::pair<int,int> b)
{
	return a.first > b.first;
}

#endif


