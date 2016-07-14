#ifndef ReducedSha_H__
#define ReducedSha_H__
#include "types1.h"
#include "sha1.h"

const u32 mM[] = {0xffff803f, 0xffff207f, 0xffffc01f, 0xffff800f, 0xfffed01f, 0xfffe801f, 0xffff001f, 0xfffda01f, 0xffff800f, 0xfffe901f, 0x0fffc01f};

struct ReducedSha
{

  u32 ws[30];
  u32* w = ws-5;
  u32 as[30];
  u32* a = as-6;
  /* u32 a5s[30]; */
  /* u32* a5= a5s-6; */
  u32 a30s[30];
  u32* a30 = a30s-6;
  u32 fs[30];
  u32* f = fs-5;

  void copy(SHA1& ref, int firstRound, int lastRound)
  {
    for(int i = firstRound; i <= lastRound; ++i)
      {
	w[i] = ref.mW[i];
	a[i+1] = ref.mA[i+1];
	/* a5[i+1] = ref.mA5[i+1]; */
	a30[i+1] = ref.mA30[i+1];
	f[i] = ref.mF[i];
      }
  }

  void restore(SHA1& ref, int firstRound, int lastRound)
  {
    ref.updatedToRound_setter() = firstRound - 1;
    for(int i = firstRound; i <= lastRound; i++)
      {
	ref.mW[i] = w[i];
	ref.mA[i+1] = a[i+1];
	/* ref.mA5[i+1] = a5[i+1]; */
	ref.mA30[i+1] = a30[i+1];
	ref.mF[i] = f[i];
      }
  }
};

extern ReducedSha m;

#endif /*__ReducedSha_H__*/
