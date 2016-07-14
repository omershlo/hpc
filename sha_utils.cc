#include "sha_utils.h"

void conformance_counter(int conformance){
	static int c[140];
	static int total;
	total++;
	c[conformance]++;
	fprintf(stderr, "%d:   ", total);
	for(int i = 0; i < 140; i++)
		if(c[i])
			fprintf(stderr, "%d: %d ", i, c[i]);
	fprintf(stderr, "\n");
}

void c_compute_state(SHA1 &ref, int round)
{
	Xupdate(ref.mW[round], ref.mW[round - 3], ref.mW[round - 8], ref.mW[round - 14], ref.mW[round - 16]);
	ref.mA30[round - 2] = ROTATE(ref.mA[round - 2], 30);
	if (round < 20){
		ref.mF[round] = F_00_19(ref.mA[round - 1], ref.mA30[round - 2], ref.mA30[round - 3]);
		ref.mK[round] = K_00_19 + ROTATE(ref.mA[round], 5) + ref.mF[round] + ref.mA30[round - 4];
	}
	else if (round < 40){
		ref.mF[round] = F_20_39(ref.mA[round - 1], ref.mA30[round - 2], ref.mA30[round - 3]);
		ref.mK[round] = K_20_39 + ROTATE(ref.mA[round], 5) + ref.mF[round] + ref.mA30[round - 4];
	}
	else if (round < 60){
		ref.mF[round] = F_40_59(ref.mA[round - 1], ref.mA30[round - 2], ref.mA30[round - 3]);
		ref.mK[round] = K_40_59 + ROTATE(ref.mA[round], 5) + ref.mF[round] + ref.mA30[round - 4];
	}
	else{
		ref.mF[round] = F_60_79(ref.mA[round - 1], ref.mA30[round - 2], ref.mA30[round - 3]);
		ref.mK[round] = K_60_79 + ROTATE(ref.mA[round], 5) + ref.mF[round] + ref.mA30[round - 4];
	}
	ref.mA[round + 1]   = ref.mW[round] + ref.mK[round];
}

int c_check_Inequality(SHA1 &base, SHA1 &comparedTo, int upToRound) {
	for (int i = 5; i < upToRound; ++i){
		if(base.mA30[i-4] != comparedTo.mA30[i-4]){
			fprintf(stderr, "a30[%2d]: ",i-4);print_duo(base.mA30[i-4], comparedTo.mA30[i-4], stderr);
			fprintf(stderr, "\n");
			return i;
		}
		if(base.mF[i]     != comparedTo.mF[i]){
			fprintf(stderr, "f  [%2d]: ",i);print_duo(base.mF[i], comparedTo.mF[i], stderr);
			fprintf(stderr, "\n");
			return i;
		}
		// if(base.mA5[i]    != comparedTo.mA5[i]){
		//   fprintf(stderr, "a5 [%2d]: ",i);print_duo(base.mA5[i], comparedTo.mA5[i], stderr);
		//   fprintf(stderr, "\n");
		//   return i;
		// }
		if(base.mW[i]     != comparedTo.mW[i]){
			fprintf(stderr, "w  [%2d]: ",i);print_duo(base.mW[i], comparedTo.mW[i], stderr);
			fprintf(stderr, "\n");
			return i;
		}
		if(base.mA[i+1]   != comparedTo.mA[i+1]){
			fprintf(stderr, "a  [%2d]: ",i+1);print_duo(base.mA[i+1], comparedTo.mA[i+1], stderr);
			fprintf(stderr, "\n");
			return i;
		}
	}
	return upToRound;
}



uint64_t rdtsc(){
	unsigned int lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

void rs_pause()
{
	static int pause_var = 0;
	int ch;

	if(pause_var <= 0)
	{
		pause_var = 0;
		printf("PAUSE-->");
		fflush(stdout);
		while((ch = getchar()) != '\n')
			if(ch >= '0' && ch <= '9')
				pause_var = pause_var * 10 + ch - '0';
	}
	else
	{
		printf("PAUSE-------------> %d\n", pause_var);
		pause_var--;
	}
}

void print_diffs(FILE *fp, uint32_t x, uint32_t y)
{
	for(int i = 31; i > -1; i--)
		if((x ^ y) & (1 << i))
			fprintf(fp, " %c%d", "-+"[(x >> i) & 1], i);
	fputc('\n', fp);
}

void SHA1::compare(SHA1 &s, int begin, int end, FILE *fp)
{
	for (int i = begin; i < end; ++i)
	{
		fprintf(fp, "a30[%2d]: %08x %08x %08x", i-4, a30_getter(i-4), s.a30_getter(i-4), a30_getter(i-4) ^ s.a30_getter(i-4)); print_diffs(fp, a30_getter(i-4), s.a30_getter(i-4));
		fprintf(fp, "f  [%2d]: %08x %08x %08x", i  ,   f_getter(i  ), s.  f_getter(i  ),   f_getter(i  ) ^ s.  f_getter(i  )); print_diffs(fp,   f_getter(i  ), s.  f_getter(i  ));
		fprintf(fp, "a5 [%2d]: %08x %08x %08x", i  ,  (ROTATE(a_getter(i), 5)), ROTATE(s.a_getter(i), 5),  (ROTATE(a_getter(i), 5)) ^ (ROTATE(s.a_getter(i), 5))); print_diffs(fp,  (ROTATE(a_getter(i), 5)), (ROTATE(s.a_getter(i), 5)));
		fprintf(fp, "W  [%2d]: %08x %08x %08x", i  ,   w_getter(i  ), s.  w_getter(i  ),   w_getter(i  ) ^ s.  w_getter(i  )); print_diffs(fp,   w_getter(i  ), s.  w_getter(i  ));
		fprintf(fp, "A  [%2d]: %08x %08x %08x", i+1,   a_getter(i+1), s.  a_getter(i+1),   a_getter(i+1) ^ s.  a_getter(i+1)); print_diffs(fp,   a_getter(i+1), s.  a_getter(i+1));
		fputc('\n', fp);
	}
}


void print_sha(SHA1 &currSha, FILE *outputFile)
{
	for(int i=0; i <= 10; i++)
	{
		fprintf(outputFile, "%08x ",currSha.w_getter(5+i));
	}
}

#define LATEX 0

void print_duo(uint32_t a, uint32_t b, FILE *fp)
{
	for(int i=31; i> -1; i--)
	{
		if(a & BIT_BY_INDEX[i])
		{
			if((a^b) & BIT_BY_INDEX[i])
			{
#if LATEX
				fprintf(fp, "\\bro");
#else
				fprintf(fp, BOLDRED "1" RESET);
#endif
			}
			else
			{
#if LATEX
				fprintf(fp, "\\go");
#else
				fprintf(fp, "1");
#endif
			}
		}
		else
		{
			if((a^b) & BIT_BY_INDEX[i])
			{
#if LATEX
				fprintf(fp, "\\brz");
#else
				fprintf(fp, BOLDRED "0" RESET);
#endif
			}
			else
			{
#if LATEX
				fprintf(fp, "\\gz");
#else
				fprintf(fp, "0");
#endif
			}
		}
	}
}

void print_duo_nl(uint32_t a, uint32_t b, FILE *fp)
{
	for(int i=31; i> -1; i--)
	{
		if(a & BIT_BY_INDEX[i])
		{
			if((a^b) & BIT_BY_INDEX[i])
			{
#if LATEX
				fprintf(fp, "\\bro");
#else
				fprintf(fp, BOLDRED "1" RESET);
#endif
			}
			else
			{
#if LATEX
				fprintf(fp, "\\go");
#else
				fprintf(fp, "1");
#endif
			}
		}
		else
		{
			if((a^b) & BIT_BY_INDEX[i])
			{
#if LATEX
				fprintf(fp, "\\brz");
#else
				fprintf(fp, BOLDRED "0" RESET);
#endif
			}
			else
			{
#if LATEX
				fprintf(fp, "\\gz");
#else
				fprintf(fp, "0");
#endif
			}
		}
	}
	fprintf(fp,"\n");
}

void print_duo_(uint32_t a, uint32_t b, FILE *fp, int start, int end)
{
	for(int i=start; i> end; i--)
	{
		if(a & BIT_BY_INDEX[i])
		{
			if((a^b) & BIT_BY_INDEX[i])
			{
#if LATEX
				fprintf(fp, "\\bro");
#else
				fprintf(fp, BOLDRED "1" RESET);
#endif
			}
			else
			{
#if LATEX
				fprintf(fp, "\\go");
#else
				fprintf(fp, "1");
#endif
			}
		}
		else
		{
			if((a^b) & BIT_BY_INDEX[i])
			{
#if LATEX
				fprintf(fp, "\\brz");
#else
				fprintf(fp, BOLDRED "0" RESET);
#endif
			}
			else
			{
#if LATEX
				fprintf(fp, "\\gz");
#else
				fprintf(fp, "0");
#endif
			}
		}
	}
}

void print_duo_frame(uint32_t a, uint32_t b, FILE *fp, int bit)
{
	if(a & BIT_BY_INDEX[bit])
	{
		if((a^b) & BIT_BY_INDEX[bit])
			fprintf(fp, ANSI_UNDERLINED_PRE BOLDRED "1" RESET);
		else
			fprintf(fp, ANSI_UNDERLINED_PRE"1" RESET);
	}
	else
	{
		if((a^b) & BIT_BY_INDEX[bit])
			fprintf(fp, ANSI_UNDERLINED_PRE BOLDRED "0" RESET);
		else
			fprintf(fp, ANSI_UNDERLINED_PRE"0" RESET);
	}
}

void print_duo_for_latex(uint32_t a, uint32_t b, FILE *fp)
{
	for(int i=31; i> -1; i--)
	{
		if(a & BIT_BY_INDEX[i])
		{
			if((a^b) & BIT_BY_INDEX[i])
				fprintf(fp, "{\\bro}");
			else
				fprintf(fp, "\\go");
		}
		else
		{
			if((a^b) & BIT_BY_INDEX[i])
				fprintf(fp, "{\\brz}");
			else
				fprintf(fp, "\\gz");
		}
	}
}

void SHA1::print_message_and_state_duo(SHA1 &s, int begin, int end, FILE *fp)
{
	for (int i = begin; i < end; ++i)
	{
		fprintf(fp, "W  [%2d]: ",i);  print_duo(w_getter(i), s.w_getter(i), fp);fprintf(fp, "  ");
		fprintf(fp, "A  [%2d]: ",i+1);print_duo(a_getter(i+1), s.a_getter(i+1), fp);fprintf(fp, "\n");
		//		fprintf(fp, "$W_{%2d}$: ",i);  print_duo_for_latex(w_getter(i), s.w_getter(i), fp);fprintf(fp, "  ");
		//		fprintf(fp, "$A_{%2d}$: ",i+1);print_duo_for_latex(a_getter(i+1), s.a_getter(i+1), fp);fprintf(fp, "\n");
	}
}

void check_equation_and_print_results(SHA1 &currSha, SHA1 &modifiedSha, int equ, FILE *fp)
{
	if(!currSha.check_single_equation_by_order(equ))
	{
		if(!modifiedSha.check_single_equation_by_order(equ))
		{
			fprintf(fp, BOLDRED "%d " RESET, equ);
			fprintf(fp, BOLDRED "%d   " RESET, equ);
		}
		else
		{
			fprintf(fp, BOLDRED "%d " RESET, equ);
			fprintf(fp, "%d   ", equ);
		}
	}
	else
	{
		if(!modifiedSha.check_single_equation_by_order(equ))
		{
			fprintf(fp, "%d ", equ);
			fprintf(fp, BOLDRED "%d   " RESET, equ);
		}
		else
		{
			fprintf(fp, "%d %d   ", equ, equ);
		}
	}
}
#define PRINT_SUBDIFF
//#undef  PRINT_SUBDIFF
void SHA1::compare_duo(SHA1 &s, int begin, int end, FILE *fp)
{
	for (int i = begin; i < end; ++i)
	{
		//		fprintf(fp,"         -   -   -   -   -   -   -   -\n");
		fprintf(fp, "a30[%2d]: ",i-4);print_duo(a30_getter(i-4), s.a30_getter(i-4), fp);
#ifdef PRINT_SUBDIFF
		print_diffs(fp, a30_getter(i-4), s.a30_getter(i-4));
#else
		fprintf(fp, "\n");
#endif

		//		fprintf(fp, "f  [%2d]: ",i);  print_duo(f_getter(i), s.f_getter(i), fp);fprintf(fp, "\n");

		fprintf(fp, "f  [%2d]: ",i);
		switch(i)
		{
		case 20:
			print_duo_(f_getter(i), s.f_getter(i), fp, 31, 28);
			print_duo_frame(f_getter(i), s.f_getter(i), fp, 28);
			print_duo_(f_getter(i), s.f_getter(i), fp, 27, -1);
			break;
		case 21:case 22:
			print_duo_(f_getter(i), s.f_getter(i), fp, 31, 29);
			print_duo_frame(f_getter(i), s.f_getter(i), fp, 29);
			print_duo_(f_getter(i), s.f_getter(i), fp, 28, 27);
			print_duo_frame(f_getter(i), s.f_getter(i), fp, 27);
			print_duo_(f_getter(i), s.f_getter(i), fp, 26, -1);
			break;
		case 25:case 26:
			print_duo_(f_getter(i), s.f_getter(i), fp, 31, 27);
			print_duo_frame(f_getter(i), s.f_getter(i), fp, 27);
			print_duo_(f_getter(i), s.f_getter(i), fp, 26, -1);
			break;
		case 27:
			print_duo_(f_getter(i), s.f_getter(i), fp, 31, 29);
			print_duo_frame(f_getter(i), s.f_getter(i), fp, 29);
			print_duo_(f_getter(i), s.f_getter(i), fp, 28, 27);
			print_duo_frame(f_getter(i), s.f_getter(i), fp, 27);
			print_duo_(f_getter(i), s.f_getter(i), fp, 26, -1);
			break;
		default:
			print_duo_(f_getter(i), s.f_getter(i), fp, 31, -1);
		}
#ifdef PRINT_SUBDIFF
		print_diffs(fp, f_getter(i), s.f_getter(i));
#else
		fprintf(fp, "\n");
#endif


		fprintf(fp, "a5 [%2d]: ",i);  print_duo((ROTATE(a_getter(i), 5)), (ROTATE(s.a_getter(i), 5)), fp);
#ifdef PRINT_SUBDIFF
		print_diffs(fp, (ROTATE(a_getter(i), 5)), (ROTATE(s.a_getter(i), 5)));
#else
		fprintf(fp, "\n");
#endif
		fprintf(fp, "W  [%2d]: ",i);  print_duo(w_getter(i), s.w_getter(i), fp);
#ifdef PRINT_SUBDIFF
		print_diffs(fp, w_getter(i), s.w_getter(i));
#else
		fprintf(fp, "\n");
#endif
		//fprintf(fp, "\n");
		fprintf(fp, "A  [%2d]: ",i+1);
		switch(i)
		{
		case 15:
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 29);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 28, 27);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 27);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 26, 0);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 0);
			break;
		case 16:
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 31, 30);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 30);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 29, 27);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 27);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 26, -1);
			break;
		case 17:
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 31);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 30, 28);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 28);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 27);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 26, -1);
			break;
		case 18:
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 29);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 28, 0);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 0);
			break;
		case 19:
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 31);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 30);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 29, 0);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 0);
			break;
		case 21:
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 31);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 30, 28);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 28);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 27, -1);
			break;
		case 22:
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 31);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 30, 29);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 29);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 28, -1);
			break;
		case 23:
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 31);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 30, -1);
			break;
		case 24:
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 29);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 28, -1);
			break;
		case 28:
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.a_getter(i+1), fp, 29);
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 28, -1);
			break;
		default:
			print_duo_(a_getter(i+1), s.a_getter(i+1), fp, 31, -1);
		}
		print_diffs(fp, a_getter(i+1), s.a_getter(i+1));
		fprintf(fp, "\n");

		switch(i)
		{

		case 15:
			check_equation_and_print_results(*this, s, 66, fp);
			check_equation_and_print_results(*this, s, 67, fp);
			check_equation_and_print_results(*this, s, 70, fp);
			break;
		case 16:
			check_equation_and_print_results(*this, s, 68, fp);
			check_equation_and_print_results(*this, s, 71, fp);
			check_equation_and_print_results(*this, s, 72, fp);
			break;
		case 17:
			check_equation_and_print_results(*this, s, 73, fp);
			check_equation_and_print_results(*this, s, 74, fp);
			check_equation_and_print_results(*this, s, 75, fp);
			break;
		case 18:
			check_equation_and_print_results(*this, s, 78, fp);
			break;
		case 19:
			check_equation_and_print_results(*this, s, 76, fp);
			check_equation_and_print_results(*this, s, 81, fp);
			break;
		case 20:
			check_equation_and_print_results(*this, s, 77, fp);
			break;
		case 21:
			check_equation_and_print_results(*this, s, 79, fp);
			check_equation_and_print_results(*this, s, 80, fp);
			check_equation_and_print_results(*this, s, 84, fp);
			check_equation_and_print_results(*this, s, 85, fp);
			break;
		case 22:
			check_equation_and_print_results(*this, s, 82, fp);
			check_equation_and_print_results(*this, s, 83, fp);
			check_equation_and_print_results(*this, s, 86, fp);
			check_equation_and_print_results(*this, s, 87, fp);
			check_equation_and_print_results(*this, s, 88, fp);
			break;
		case 23:
			check_equation_and_print_results(*this, s, 90, fp);
			break;
		case 24:
			check_equation_and_print_results(*this, s, 92, fp);
			break;
		case 25:
			check_equation_and_print_results(*this, s, 89, fp);
			break;
		case 26:
			check_equation_and_print_results(*this, s, 91, fp);
			break;
		case 27:
			check_equation_and_print_results(*this, s, 93, fp);
			check_equation_and_print_results(*this, s, 94, fp);
			check_equation_and_print_results(*this, s, 96, fp);
			break;
		case 28:
			check_equation_and_print_results(*this, s, 97, fp);
			break;
		case 30:
			check_equation_and_print_results(*this, s, 95, fp);
			break;
		default:
			break;
		}
		fprintf(fp,"\n");
		//		fprintf(fp, "A  [%2d]: ",i+1);print_duo(a_getter(i+1), s.a_getter(i+1), fp);fprintf(fp, "\n");


		//		fprintf(fp, "a30[%2d]: ",i-4);print_duo_for_latex(a30_getter(i-4), s.a30_getter(i-4), fp);fprintf(fp, "\n");
		//		fprintf(fp, "f  [%2d]: ",i);  print_duo_for_latex(f_getter(i), s.f_getter(i), fp);fprintf(fp, "\n");
		//		fprintf(fp, "a5 [%2d]: ",i);  print_duo_for_latex(a5_getter(i), s.a5_getter(i), fp);fprintf(fp, "\n");
		//		fprintf(fp, "W  [%2d]: ",i);  print_duo_for_latex(w_getter(i), s.w_getter(i), fp);fprintf(fp, "\n");
		//		fprintf(fp, "A  [%2d]: ",i+1);print_duo_for_latex(a_getter(i+1), s.a_getter(i+1), fp);fprintf(fp, "\n");
		fputc('\n', fp);
	}
}

void SHA1::compare_duo_Sha1ParameterNotUpdated(SHA1 &s, int begin, int end, FILE *fp)
{
	for (int i = begin; i < end; ++i)
	{
		fprintf(fp, "a30[%2d]: ",i-4);print_duo(a30_getter(i-4), s.mA30[i-4], fp);
#ifdef PRINT_SUBDIFF
		print_diffs(fp, a30_getter(i-4), s.mA30[i-4]);
#else
		fprintf(fp, "\n");
#endif
		fprintf(fp, "f  [%2d]: ",i);
		switch(i)
		{
		case 20:
			print_duo_(f_getter(i), s.mF[i], fp, 31, 28);
			print_duo_frame(f_getter(i), s.mF[i], fp, 28);
			print_duo_(f_getter(i), s.mF[i], fp, 27, -1);
			break;
		case 21:case 22:
			print_duo_(f_getter(i), s.mF[i], fp, 31, 29);
			print_duo_frame(f_getter(i), s.mF[i], fp, 29);
			print_duo_(f_getter(i), s.mF[i], fp, 28, 27);
			print_duo_frame(f_getter(i), s.mF[i], fp, 27);
			print_duo_(f_getter(i), s.mF[i], fp, 26, -1);
			break;
		case 25:case 26:
			print_duo_(f_getter(i), s.mF[i], fp, 31, 27);
			print_duo_frame(f_getter(i), s.mF[i], fp, 27);
			print_duo_(f_getter(i), s.mF[i], fp, 26, -1);
			break;
		case 27:
			print_duo_(f_getter(i), s.mF[i], fp, 31, 29);
			print_duo_frame(f_getter(i), s.mF[i], fp, 29);
			print_duo_(f_getter(i), s.mF[i], fp, 28, 27);
			print_duo_frame(f_getter(i), s.mF[i], fp, 27);
			print_duo_(f_getter(i), s.mF[i], fp, 26, -1);
			break;
		default:
			print_duo_(f_getter(i), s.mF[i], fp, 31, -1);
		}
#ifdef PRINT_SUBDIFF
		print_diffs(fp, f_getter(i), s.mF[i]);
#else
		fprintf(fp, "\n");
#endif
		fprintf(fp, "a5 [%2d]: ",i);  print_duo((ROTATE(a_getter(i), 5)), (ROTATE(s.mA[i], 5)), fp);
#ifdef PRINT_SUBDIFF
		print_diffs(fp, (ROTATE(a_getter(i), 5)), (ROTATE(s.mA[i], 5)));
#else
		fprintf(fp, "\n");
#endif
		fprintf(fp, "W  [%2d]: ",i);  print_duo(w_getter(i), s.mW[i], fp);
#ifdef PRINT_SUBDIFF
		print_diffs(fp, w_getter(i), s.mW[i]);
#else
		fprintf(fp, "\n");
#endif
		fprintf(fp, "A  [%2d]: ",i+1);
		switch(i)
		{
		case 15:
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 29);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 28, 27);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 27);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 26, 0);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 0);
			break;
		case 16:
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 31, 30);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 30);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 29, 27);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 27);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 26, -1);
			break;
		case 17:
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 31);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 30, 28);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 28);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 27);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 26, -1);
			break;
		case 18:
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 29);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 28, 0);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 0);
			break;
		case 19:
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 31);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 30);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 29, 0);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 0);
			break;
		case 21:
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 31);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 30, 28);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 28);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 27, -1);
			break;
		case 22:
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 31);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 30, 29);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 29);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 28, -1);
			break;
		case 23:
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 31);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 30, -1);
			break;
		case 24:
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 29);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 28, -1);
			break;
		case 28:
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 31, 29);
			print_duo_frame(a_getter(i+1), s.mA[i+1], fp, 29);
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 28, -1);
			break;
		default:
			print_duo_(a_getter(i+1), s.mA[i+1], fp, 31, -1);
		}
		print_diffs(fp, a_getter(i+1), s.mA[i+1]);
		fprintf(fp, "\n");
		// switch(i)
		// {
		// case 15:
		// 	check_equation_and_print_results(*this, s, 66, fp);
		// 	check_equation_and_print_results(*this, s, 67, fp);
		// 	check_equation_and_print_results(*this, s, 70, fp);
		// 	break;
		// case 16:
		// 	check_equation_and_print_results(*this, s, 68, fp);
		// 	check_equation_and_print_results(*this, s, 71, fp);
		// 	check_equation_and_print_results(*this, s, 72, fp);
		// 	break;
		// case 17:
		// 	check_equation_and_print_results(*this, s, 73, fp);
		// 	check_equation_and_print_results(*this, s, 74, fp);
		// 	check_equation_and_print_results(*this, s, 75, fp);
		// 	break;
		// case 18:
		// 	check_equation_and_print_results(*this, s, 78, fp);
		// 	break;
		// case 19:
		// 	check_equation_and_print_results(*this, s, 76, fp);
		// 	check_equation_and_print_results(*this, s, 81, fp);
		// 	break;
		// case 20:
		// 	check_equation_and_print_results(*this, s, 77, fp);
		// 	break;
		// case 21:
		// 	check_equation_and_print_results(*this, s, 79, fp);
		// 	check_equation_and_print_results(*this, s, 80, fp);
		// 	check_equation_and_print_results(*this, s, 84, fp);
		// 	check_equation_and_print_results(*this, s, 85, fp);
		// 	break;
		// case 22:
		// 	check_equation_and_print_results(*this, s, 82, fp);
		// 	check_equation_and_print_results(*this, s, 83, fp);
		// 	check_equation_and_print_results(*this, s, 86, fp);
		// 	check_equation_and_print_results(*this, s, 87, fp);
		// 	check_equation_and_print_results(*this, s, 88, fp);
		// 	break;
		// case 23:
		// 	check_equation_and_print_results(*this, s, 90, fp);
		// 	break;
		// case 24:
		// 	check_equation_and_print_results(*this, s, 92, fp);
		// 	break;
		// case 25:
		// 	check_equation_and_print_results(*this, s, 89, fp);
		// 	break;
		// case 26:
		// 	check_equation_and_print_results(*this, s, 91, fp);
		// 	break;
		// case 27:
		// 	check_equation_and_print_results(*this, s, 93, fp);
		// 	check_equation_and_print_results(*this, s, 94, fp);
		// 	check_equation_and_print_results(*this, s, 96, fp);
		// 	break;
		// case 28:
		// 	check_equation_and_print_results(*this, s, 97, fp);
		// 	break;
		// case 30:
		// 	check_equation_and_print_results(*this, s, 95, fp);
		// 	break;
		// default:
		// 	break;
		// }
		fprintf(fp,"\n");
		fputc('\n', fp);
	}
}

void seek_message(int n, FILE* fp)
{
	u32 w[11];
	for(int i = 0; i < n-1; i++)
		assert(fread(w, sizeof(u32), 11, fp)==11);
}

u32 sub_to_xor(u32 w, u32 sub)
{
	return (w+sub)^w;
}

u32 xor_to_sub(u32 w, u32 xorDiff)
{
	return (w^xorDiff)-w;
}

int replace(int equNum)
{
	switch(equNum)
	{
	case 79: return 0;
	case 82: return 1;
	case 841: return 2;
	case 842: return 3;
	case 843: return 4;
	case 85: return 5;
	}
	return 6;
}
int unreplace(int index)
{
	switch(index)
	{
	case 0: return 79;
	case 1: return 82;
	case 2: return 841;
	case 3: return 842;
	case 4: return 843;
	case 5: return 85;
	case 6: return 0;
	}
	return 0;
}

#if STATISTICS & 0X2
void compute_and_print_equations_statistics(int *uncorrected, int *corrected, const char *statisticsFileName)
{
	FILE *fp;
	if(NULL == (fp = fopen(statisticsFileName, "w")))
	{
		print_at;
		fprintf(stderr, "cannot open %s\n", statisticsFileName);
		exit(1);
	}
	for(int i = 0; i < 150; i++)
	{
		if(uncorrected[i]+corrected[i])
		{
			if(corrected[i] == 0)
			{
				fprintf(fp, "%3d: 0\n", i);
				continue;
			}
			if(uncorrected[i] == 0)
			{
				fprintf(fp, "%3d: 1\n", i);
				continue;
			}
			fprintf(fp, "%3d: %g\n", i, (double)corrected[i] / (corrected[i] + uncorrected[i]));
		}
	}
	fflush(fp);
	fclose(fp);
}

bool test_linear_equations(SHA1& m)
{
	bool pass = true;
	linearEquations[5].solution = (m.mA[13] & B2) ? 0 : 1;
	for(int i = 0; i < NUM_OF_LINEAR_EQUATIONS; i++)
	{
		if(m.test_linear_equation(linearEquations[i]))
		{
			pass = false;
			printf("linear equ %d unsolved\n",i);
		}
	}
	return pass;
}


bool compare_round(SHA1& p, SHA1& q, int r)
{
	bool pass = true;
	//	 q.updatedToRound_setter() = r-1;
	if(p.mW[r] ^ q.w_getter(r)) {fprintf(stderr, "w  '[%02d]:%08x\n", r, p.mW[r] ^ q.w_getter(r)); pass = false;}
	if(p.mA[r+1] ^ q.a_getter(r+1)) {fprintf(stderr, "a  '[%02d]:%08x\n", r+1, p.mA[r+1] ^ q.a_getter(r+1)); pass = false;}
	if(p.mF[r] ^ q.f_getter(r)) {fprintf(stderr, "f  '[%02d]:%08x\n", r, p.mF[r] ^ q.f_getter(r)); pass = false;}
	if(p.mA30[r-4] ^ q.a30_getter(r-4)) {fprintf(stderr, "a30'[%02d]:%08x\n", r-4, p.mA30[r-4] ^ q.a30_getter(r-4)); pass = false;}
	return pass;
}
bool compare_round_no_getter(SHA1& p, SHA1& q, int r)
{
	bool pass = true;
	//	 q.updatedToRound_setter() = r-1;
	if(p.mW[r] ^ q.mW[r]) {fprintf(stderr, "w  '[%02d]:%08x\n", r, p.mW[r] ^ q.mW[r]); pass = false;}
	if(p.mA[r+1] ^ q.mA[r+1]) {fprintf(stderr, "a  '[%02d]:%08x\n", r+1, p.mA[r+1] ^ q.mA[r+1]); pass = false;}
	if(p.mF[r] ^ q.mF[r]) {fprintf(stderr, "f  '[%02d]:%08x\n", r, p.mF[r] ^ q.mF[r]); pass = false;}
	if(p.mA30[r-4] ^ q.mA30[r-4]) {fprintf(stderr, "a30'[%02d]:%08x\n", r-4, p.mA30[r-4] ^ q.mA30[r-4]); pass = false;}
	return pass;
}

#endif


