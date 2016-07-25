#include "types1.h"
#include "sha1.h"
#include "sha_utils.h"


//#include <execinfo.h>

//static inline void printStackTrace( FILE *out = stderr, unsigned int max_frames = 63 )
//{
//	fprintf(out, "stack trace:\n");
//
//	// storage array for stack trace address data
//	void* addrlist[max_frames+1];
//
//	// retrieve current stack addresses
//	u32 addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));
//
//	if ( addrlen == 0 )
//	{
//		fprintf( out, "  \n" );
//		return;
//	}
//
//	// create readable strings to each frame.
//	char** symbollist = backtrace_symbols( addrlist, addrlen );
//
//	// print the stack trace.
//	for ( u32 i = 1; i < addrlen; i++ )
//		fprintf( out, "%s\n", symbollist[i]);
//
//	free(symbollist);
//}

int SHA1::compute_firstUnsatisfied()
{
	for(auto it = equationList.begin(); it != equationList.end(); it++)
	{
		if(!check_single_equation_by_order(*it))
			return *it;
	}
	return 142;
}

//void SHA1::test_neutrality(LCS l, int firstEqu, int lastEqu)
//{
//	static int counter[20];
//	SHA1 m = *this;
//	m.Apply_lcs(l);
//	for(int i = firstEqu; i < lastEqu; i++)
//	{
//		if(check_single_equation_by_order(i) != m.check_single_equation_by_order(i))
//		{
//			if(i>70)counter[i-70]++;
//			break;
//		}
//	}
//	for(int i = 0; i < 20; i++)
//		if(counter[i])fprintf(stderr, "%d: %d ", i+70, counter[i]);
//	fprintf(stderr,"\n");
//}



bool SHA1::check_single_equation_by_order(int equationOrder)
{
	u32 b[4] = {0};
	bool condition[12];
	bool pass = false;
	switch(equationOrder)
	{
	case  12:
		b[0] = (a_getter(7) & B9)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   17:
		b[0] = (a_getter(7) & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   18:
		b[0] = (a_getter(7) & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   21:
		b[0] = (a_getter(8) & B9)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   22:
		b[0] = (a_getter(8) & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   23:
		b[0] = (a_getter(8) & B29)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   24:
		b[0] = (a_getter(8) & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   25:
		b[0] = (a_getter(8) & B31)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   26:
		b[0] = (a_getter(9) & B1)?1:0;
		b[1] = (a_getter(8) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   27:
		b[0] = (a_getter(9) & B6)?1:0;
		b[1] = (a_getter(8) & B6)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   28:
		b[0] = (a_getter(9) & B26)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   29:
		b[0] = (a_getter(9) & B27)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   30:
		b[0] = (a_getter(9) & B28)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   31:
		b[0] = (a_getter(9) & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   32:
		b[0] = (a_getter(9) & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   33:
		b[0] = (a_getter(9) & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   35:
		b[0] = (a_getter(10) & B4)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   36:
		b[0] = (a_getter(10) & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   37:
		b[0] = (a_getter(10) & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   38:
		b[0] = (a_getter(10) & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   39:
		b[0] = (a_getter(10) & B31)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   40:
		b[0] = (a_getter(10) & B1)?1:0;
		b[1] = (a_getter(11) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   41:
		b[0] = (a_getter(11) & B2)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   42:
		b[0] = (a_getter(11) & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   43:
		b[0] = (a_getter(11) & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   44:
		b[0] = (a_getter(11) & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   45:
		b[0] = (a_getter(12) & B2)?1:0;
		b[1] = (w_getter(8) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   46:
		b[0] = (a_getter(12) & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   47:
		b[0] = (a_getter(12) & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case  49://142
		b[0] = (a_getter(12) & B30)?1:0;
		b[1] = (a_getter(11) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   50:
		b[0] = (a_getter(12) & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   52:
		b[0] = (a_getter(13) & B1)?1:0;
		b[1] = (a_getter(12) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   53:
		b[0] = (a_getter(13) & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   54:
		b[0] = (a_getter(13) & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   55:
		b[0] = (a_getter(13) & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   56:
		b[0] = (a_getter(13) & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   57:
		b[0] = (a_getter(14) & B26)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   58:
		b[0] = (a_getter(14) & B27)?1:0;
		b[1] = (f_getter(14) & B0)?1:0;
		b[2] = (w_getter(14) & B0)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] )== 0);
		break;
	case   59:
		b[0] = (a_getter(14) & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   60:
		b[0] = (a_getter(14) & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   61:
		b[0] = (a_getter(15) & B4)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   62:
		b[0] = (a_getter(15) & B26)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   63:
		b[0] = (a_getter(15) & B27)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   64:
		b[0] = (a_getter(15) & B29)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   65:
		b[0] = (a_getter(15) & B31)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   66:
		b[0] = (a_getter(16) & B0)?1:0;
		b[1] = (a_getter(15) & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   67:
		b[0] = (a_getter(16) & B27)?1:0;
		b[1] = (w_getter(14) & B26)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   68:
		b[0] = (a_getter(17) & B1)?1:0;
		b[1] = (a_getter(16) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   69://aux
		b[0] = (a_getter(16) & B3)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   70:
		b[0] = (a_getter(16) & B29)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   71:
		b[0] = (a_getter(17) & B27)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   72:
		b[0] = (a_getter(17) & B30)?1:0;
		pass = ((b[0] )== 1);
		break;
	case   73:
		b[0] = (a_getter(18) & B27)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   74:
		b[0] = (a_getter(18) & B28)?1:0;
		pass = ((b[0] )== 0);
		break;
	case   75:
		b[0] = (a_getter(18) & B31)?1:0;
		b[1] = (w_getter(18) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   76:
		b[0] = (a_getter(19) & B0)?1:0;
		b[1] = (a_getter(20) & B0)?1:0;
		b[2] = (w_getter(22) & B30)?1:0;//1
		b[3] = (w_getter(20) & B29)?1:0;//0
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case   77:
		b[0] = (f_getter(20) & B28)?1:0;
		b[1] = (w_getter(20) & B28)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   78:
		b[0] = (a_getter(19) & B29)?1:0;//0
		b[1] = (w_getter(19) & B2)?1:0;//0
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   79:
		b[0] = (f_getter(21) & B27)?1:0;
		b[1] = (w_getter(21) & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   80:
		b[0] = (f_getter(21) & B29)?1:0;
		b[1] = (w_getter(21) & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   81:
		b[0] = (a_getter(20) & B31)?1:0;
		b[1] = (w_getter(20) & B4)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   82:
		b[0] = (f_getter(22) & B27)?1:0;//=0
		b[1] = (w_getter(22) & B27)?1:0;//=0
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   83:
		b[0] = (f_getter(22) & B29)?1:0;
		b[1] = (w_getter(18) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   84:
		b[0] = (a_getter(20) & B30)?1:0;
		b[1] = (a_getter(22) & B28)?1:0;
		b[2] = (w_getter(20) & B29)?1:0;
		b[3] = (w_getter(23) & B27)?1:0;
		condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!condition[3])
			break;
		b[0] = (a_getter(21) & B30)?1:0;
		b[1] = (w_getter(20) & B29)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 1);
		b[0] = (a_getter(21) & B31)?1:0;
		b[1] = (w_getter(20) & B29)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 1);
		b[0] = (w_getter(23) & B27)?1:0;
		b[1] = (f_getter(23) & B29)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]))
		{
			pass = true;
		}
		break;
	case   85:
		b[0] = (a_getter(22) & B31)?1:0;
		b[1] = (w_getter(22) & B4)?1:0;//(w_getter(22) & B4)=0 => (a_getter(22) & B31) = 1
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   86:
		b[0] = (a_getter(22) & B30)?1:0;
		b[1] = (a_getter(23) & B28)?1:0;
		b[2] = (w_getter(20) & B29)?1:0;
		b[3] = (w_getter(24) & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case   87://223
		b[0] = (a_getter(23) & B29)?1:0;
		b[1] = (w_getter(22) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   88://230
		b[0] = (a_getter(23) & B31)?1:0;
		b[1] = (w_getter(23) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   89://250
		b[0] = (f_getter(25) & B27)?1:0;
		b[1] = (w_getter(25) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   90://240
		b[0] = (a_getter(24) & B31)?1:0;
		b[1] = (w_getter(24) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   91://260
		b[0] = (f_getter(26) & B27)?1:0;
		b[1] = (w_getter(26) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   92://243
		b[0] = (a_getter(25) & B29)?1:0;
		b[1] = (w_getter(24) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   93://270
		b[0] = (f_getter(27) & B27)?1:0;
		b[1] = (w_getter(22) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   94://271
		b[0] = (f_getter(27) & B29)?1:0;
		b[1] = (w_getter(23) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case   95://301
		b[0] = (a_getter(27) & B29)?1:0;
		b[1] = (w_getter(26) & B29)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 1);
		if(condition[0])
		{
			pass = true;
		}
		else
		{
			b[0] = (a_getter(27) & B30)?1:0;
			b[1] = (w_getter(26) & B29)?1:0;
			condition[1] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(27) & B31)?1:0;
			b[1] = (w_getter(26) & B29)?1:0;
			condition[2] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(25) & B0)?1:0;
			b[1] = (a_getter(26) & B0)?1:0;
			b[2] = (w_getter(29) & B2)?1:0;
			b[3] = (w_getter(26) & B29)?1:0;
			condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(28) & B31)?1:0;
			b[1] = (w_getter(29) & B2)?1:0;
			condition[4] = ((b[0] ^ b[1] )== 0);
			b[0] = (a_getter(28) & B28)?1:0;
			b[1] = (w_getter(24) & B29)?1:0;
			b[2] = (w_getter(26) & B29)?1:0;
			b[3] = (a_getter(26) & B30)?1:0;
			condition[5] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(29) & B29)?1:0;
			b[1] = (w_getter(24) & B29)?1:0;
			condition[6] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(28) & B30)?1:0;
			b[1] = (a_getter(29) & B28)?1:0;
			b[2] = (w_getter(26) & B29)?1:0;
			b[3] = (w_getter(30) & B27)?1:0;
			condition[7] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(30) & B29)?1:0;
			b[1] = (w_getter(30) & B27)?1:0;
			condition[8] = ((b[0] ^ b[1] )== 1);
			if(condition[3]&&condition[5]&&condition[7]&&(condition[1] || (condition[2] && condition[4] && condition[6] && condition[8])))
			{
				pass = true;
			}
		}
		break;
	case   96://302
		b[0] = (a_getter(27) & B0)?1:0;
		b[1] = (a_getter(28) & B0)?1:0;
		b[2] = (w_getter(30) & B30)?1:0;
		b[3] = (w_getter(28) & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case   97://290
		b[0] = (a_getter(29) & B29)?1:0;
		b[1] = (w_getter(29) & B2)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case   98://284
		b[0] = (a_getter(29) & B30)?1:0;
		b[1] = (w_getter(28) & B30)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 0);
		b[0] = (a_getter(29) & B31)?1:0;
		b[1] = (w_getter(28) & B30)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_getter(31) & B29)?1:0;
		b[1] = (w_getter(31) & B28)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_getter(32) & B29)?1:0;
		b[1] = (w_getter(32) & B28)?1:0;
		condition[3] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]&&condition[3]))
		{
			pass = true;
		}
		break;
	case   99://282
		b[0] = (a_getter(25) & B31)?1:0;
		b[1] = (a_getter(26) & B31)?1:0;
		b[2] = (w_getter(29) & B2)?1:0;
		b[3] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		break;
	case  100://281
		b[0] = (f_getter(28) & B27)?1:0;
		b[1] = (w_getter(28) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case  101://291
		b[0] = (a_getter(26) & B29)?1:0;
		b[1] = (a_getter(28) & B27)?1:0;
		b[2] = (w_getter(24) & B29)?1:0;
		b[3] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		break;
	case  102://300
		b[0] = (a_getter(28) & B29)?1:0;
		b[1] = (a_getter(29) & B27)?1:0;
		b[2] = (w_getter(26) & B29)?1:0;
		b[3] = (w_getter(30) & B27)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		break;
	case  103://280
		b[0] = (a_getter(28) & B31)?1:0;
		b[1] = (w_getter(28) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  104://310
		b[0] = (f_getter(31) & B27)?1:0;
		b[1] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case  105://311
		b[0] = (a_getter(28) & B30)?1:0;
		b[1] = (a_getter(30) & B28)?1:0;
		b[2] = (w_getter(28) & B30)?1:0;
		b[3] = (w_getter(31) & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case  106://320
		b[0] = (a_getter(32) & B31)?1:0;
		b[1] = (w_getter(32) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  107://321
		b[0] = (f_getter(32) & B27)?1:0;
		b[1] = (w_getter(32) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  108://322
		b[0] = (w_getter(32) & B28)?1:0;
		b[1] = (a_getter(31) & B28)?1:0;
		b[2] = (a_getter(30) & B30)?1:0;
		b[3] = (w_getter(28) & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		break;
	case  109://330
		b[0] = (w_getter(33) & B4)?1:0;
		b[1] = (a_getter(33) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  110://340
		b[0] = (w_getter(34) & B29)?1:0;
		b[1] = (f_getter(34) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  111://360
		b[0] = (w_getter(32) & B4)?1:0;
		b[1] = (f_getter(36) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case  112://390
		b[0] = (a_getter(39) & B31)?1:0;
		b[1] = (w_getter(39) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  113://400
		b[0] = (a_getter(38) & B1)?1:0;
		b[1] = (a_getter(37) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  114://410
		b[0] = (a_getter(41) & B31)?1:0;
		b[1] = (w_getter(41) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  115://411
		b[0] = (a_getter(40) & B29)?1:0;
		b[1] = (a_getter(38) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  116://420
		b[0] = (a_getter(41) & B29)?1:0;
		b[1] = (a_getter(40) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  117://421
		b[0] = (a_getter(40) & B1)?1:0;
		b[1] = (a_getter(39) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  118://430
		b[0] = (a_getter(43) & B31)?1:0;
		b[1] = (w_getter(43) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  119://431
		b[0] = (a_getter(42) & B29)?1:0;
		b[1] = (a_getter(40) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  120://440
		b[0] = (a_getter(43) & B29)?1:0;
		b[1] = (a_getter(42) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  121://441
		b[0] = (a_getter(42) & B1)?1:0;
		b[1] = (a_getter(41) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  122://442
		b[0] = (a_getter(45) & B30)?1:0;
		b[1] = (w_getter(44) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  123://450
		b[0] = (a_getter(44) & B29)?1:0;
		b[1] = (a_getter(42) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  124://460
		b[0] = (a_getter(45) & B29)?1:0;
		b[1] = (a_getter(44) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  125://461
		b[0] = (a_getter(44) & B0)?1:0;
		b[1] = (a_getter(43) & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  126://470
		b[0] = (a_getter(46) & B28)?1:0;
		b[1] = (a_getter(44) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  127://480
		b[0] = (a_getter(48) & B31)?1:0;
		b[1] = (w_getter(48) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  128://481
		b[0] = (a_getter(47) & B28)?1:0;
		b[1] = (a_getter(46) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  129://490
		b[0] = (a_getter(47) & B1)?1:0;
		b[1] = (a_getter(46) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  130://500
		b[0] = (a_getter(49) & B29)?1:0;
		b[1] = (a_getter(47) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  131://510
		b[0] = (a_getter(50) & B29)?1:0;
		b[1] = (a_getter(49) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  132://530
		b[0] = (a_getter(53) & B31)?1:0;
		b[1] = (w_getter(53) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  133://540
		b[0] = (a_getter(52) & B1)?1:0;
		b[1] = (a_getter(51) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  134://550
		b[0] = (a_getter(54) & B29)?1:0;
		b[1] = (a_getter(52) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  135://560
		b[0] = (a_getter(55) & B29)?1:0;
		b[1] = (a_getter(54) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  136://590
		b[0] = (a_getter(59) & B31)?1:0;
		b[1] = (w_getter(59) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  137://610
		b[0] = (a_getter(61) & B31)?1:0;
		b[1] = (w_getter(61) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  138://611
		b[0] = (w_getter(61) & B29)?1:0;
		b[1] = (f_getter(61) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  139://620
		b[0] = (w_getter(62) & B29)?1:0;
		b[1] = (f_getter(62) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case  140://630
		b[0] = (w_getter(59) & B4)?1:0;
		b[1] = (f_getter(63) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	case 141://640
		b[0] = (w_getter(64) & B29)?1:0;
		b[1] = (f_getter(64) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		break;
	case 1405:
		b[0] = (w_getter(14) & B5)?1:0;
		b[1] = (a_getter(15) & B5)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		break;
	default:
		printf("equationOrder = %d\n",equationOrder);
		rs_pause();
	}
	return pass;
}


// int equationid1[]={193, 155, 156, 181, 164, 191, 192, 180, 224, 201, 190, 210, 211, 200, 221, 222, 232, 220, 241, 223, 230, 250, 240, 260, 243, 270,
// 		   271, 301, 302, 290, 284, 282, 281, 291, 300, 280, 310, 311, 320, 321, 322, 330, 340, 360, 390, 400, 410, 411, 420, 421, 430, 431,
// 		   440, 441, 442, 450, 460, 461, 470, 480, 481, 490, 500, 510, 530, 540, 550, 560, 590, 610, 611, 620, 630, 640};

void SHA1::return_conformance_order(int equationIndex)
{
	firstUnsatisfiedEquation_setter() = equationIndex;
}

//conformance() returns the id of the first uncorfoming equation and
//the number of unconforming equations between start and end.  If
//end=0 the function returns on the first non-conformance
void SHA1::check_conformance(int start)
{
	u32 b[4] = {0};
	bool condition[12];
	bool pass = false;
	int firstNonConformance = 0;
	int startToEndWeight = 0;
	int weightBitMask = 0;
	switch(start)
	{
	case   36:
		b[0] = (a_getter(10) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 36); return;}
	case   37:
		b[0] = (a_getter(10) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 37); return;}
	case   38:
		b[0] = (a_getter(10) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 38); return;}
	case   39:
		b[0] = (a_getter(10) & B31)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 39); return;}
	case   40:
		b[0] = (a_getter(10) & B1)?1:0;
		b[1] = (a_getter(11) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 40); return;}
	case   41:
		b[0] = (a_getter(11) & B2)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 41); return;}
	case   42:
		b[0] = (a_getter(11) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 42); return;}
	case   43:
		b[0] = (a_getter(11) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 43); return;}
	case   44:
		b[0] = (a_getter(11) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 44); return;}
	case   45:
		b[0] = (a_getter(12) & B2)?1:0;
		b[1] = (w_getter(8) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 45); return;}
	case   46:
		b[0] = (a_getter(12) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 46); return;}
	case   47:
		b[0] = (a_getter(12) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 47); return;}
	case  49://142
		b[0] = (a_getter(12) & B30)?1:0;
		b[1] = (a_getter(11) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 49); return;}
	case   50:
		b[0] = (a_getter(12) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 50); return;}
	case   52:
		b[0] = (a_getter(13) & B1)?1:0;
		b[1] = (a_getter(12) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 52); return;}
	case   53:
		b[0] = (a_getter(13) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 53); return;}
	case   54:
		b[0] = (a_getter(13) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 54); return;}
	case   55:
		b[0] = (a_getter(13) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 55); return;}
	case   56:
		b[0] = (a_getter(13) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 56); return;}
	case   57:
		b[0] = (a_getter(14) & B26)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 57); return;}
	case   58:
		b[0] = (a_getter(14) & B27)?1:0;
		b[1] = (f_getter(14) & B0)?1:0;
		b[2] = (w_getter(14) & B0)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] )== 0);
		if(!pass){return_conformance_order( 58); return;}
	case   59:
		b[0] = (a_getter(14) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 59); return;}
	case   60:
		b[0] = (a_getter(14) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 60); return;}
//	case   61://aux
//		b[0] = (a_getter(15) & B4)?1:0;
//		pass = ((b[0] )== 0);
//		if(!pass){return_conformance_order( 61); return;}
	case   62:
		b[0] = (a_getter(15) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 62); return;}
	case   63:
		b[0] = (a_getter(15) & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 63); return;}
	case   64:
		b[0] = (a_getter(15) & B29)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 64); return;}
	case   65:
		b[0] = (a_getter(15) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 65); return;}
	case   66:
		b[0] = (a_getter(16) & B0)?1:0;
		b[1] = (a_getter(15) & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 66); return;}
	case   67:
		b[0] = (a_getter(16) & B27)?1:0;
		b[1] = (w_getter(14) & B26)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 67); return;}
	case  68:
		b[0] = (a_getter(17) & B1)?1:0;
		b[1] = (a_getter(16) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 68); return;}
	case   69://aux condition
		b[0] = (a_getter(16) & B3)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 69); return;}
	case   70:
		b[0] = (a_getter(16) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 70); return;}
	case   71:
		b[0] = (a_getter(17) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 71); return;}
	case   72:
		b[0] = (a_getter(17) & B30)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 72); return;}
	case   73:
		b[0] = (a_getter(18) & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 73); return;}
	case   74:
		b[0] = (a_getter(18) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 74); return;}
	case   75:
		b[0] = (a_getter(18) & B31)?1:0;
		b[1] = (w_getter(18) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 75); return;}
	case   76:
		b[0] = (a_getter(19) & B0)?1:0;
		b[1] = (a_getter(20) & B0)?1:0;
		b[2] = (w_getter(22) & B30)?1:0;
		b[3] = (w_getter(20) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){return_conformance_order( 76); return;}
	case   77:
		b[0] = (f_getter(20) & B28)?1:0;
		b[1] = (w_getter(20) & B28)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 77); return;}
	case   78:
		b[0] = (a_getter(19) & B29)?1:0;//0
		b[1] = (w_getter(19) & B2)?1:0;//0
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 78); return;}
	case   79:
		b[0] = (f_getter(21) & B27)?1:0;
		b[1] = (w_getter(21) & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 79); return;}
	case   80:
		b[0] = (f_getter(21) & B29)?1:0;
		b[1] = (w_getter(21) & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 80); return;}
	case   81:
		b[0] = (a_getter(20) & B31)?1:0;//0
		b[1] = (w_getter(20) & B4)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 81); return;}
	case   82:
		b[0] = (f_getter(22) & B27)?1:0;
		b[1] = (w_getter(22) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 82); return;}
	case   83:
		b[0] = (f_getter(22) & B29)?1:0;
		b[1] = (w_getter(18) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 83); return;}
	case   84:
		pass = false;
		b[0] = (a_getter(20) & B30)?1:0;
		b[1] = (a_getter(22) & B28)?1:0;
		condition[3] = ((b[0] ^ b[1])== 0);
//		b[2] = (w_getter(20) & B29)?1:0;//1
//		b[3] = (w_getter(23) & B27)?1:0;//0
//		condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
//		if(!condition[3]){return_conformance_order( 84); return;}
		b[0] = (a_getter(21) & B30)?1:0;
		condition[0] = b[0]== 0;
//		b[1] = (w_getter(20) & B29)?1:0;//1
//		condition[0] = ((b[0] ^ b[1] )== 1);
		b[0] = (a_getter(21) & B31)?1:0;
		condition[1] = b[0]== 0;
//		b[1] = (w_getter(20) & B29)?1:0;//1
//		condition[1] = ((b[0] ^ b[1] )== 1);
//		b[0] = (w_getter(23) & B27)?1:0;//0
		b[1] = (f_getter(23) & B29)?1:0;
		condition[2] = b[1]== 1;
//		condition[2] = ((b[0] ^ b[1] )== 1);
		if(condition[3] && ((condition[0]&&condition[2]) || (!condition[0]&&condition[1])))
			pass = true;
//		else if(solveEquation84(condition))
//			pass = true;
		if(!pass){return_conformance_order( 84); return;}
	case   85:
		b[0] = (a_getter(22) & B31)?1:0;//1
//		b[1] = (w_getter(22) & B4)?1:0;//0
//		pass = ((b[0] ^ b[1] )== 1);
		pass = (b[0] == 1);
		if(!pass){return_conformance_order( 85); return;}
	case   86:
//		b[0] = (a_getter(22) & B30)?1:0;
//		b[1] = (a_getter(23) & B28)?1:0;
////		b[2] = (w_getter(20) & B29)?1:0;//1
//		b[3] = (w_getter(24) & B28)?1:0;
//		pass = ((b[0] ^ b[1]/*^ b[2]*/ ^ b[3] )== 0);
//		if(!pass){return_conformance_order( 86); return;}
		if(((a_getter(22)>>2) ^ a_getter(23) ^ w_getter(24)) & B28){return_conformance_order( 86); return;}
	case   87:
//		b[0] = (a_getter(23) & B29)?1:0;
//		b[1] = (w_getter(22) & B29)?1:0;//0
//		pass = ((b[0] ^ b[1] )== 0);
//		if(!pass){return_conformance_order( 87); return;}
		if((a_getter(23) & B29)){return_conformance_order( 87); return;}
	case   88:
//		b[0] = (a_getter(23) & B31)?1:0;
//		b[1] = (w_getter(23) & B4)?1:0;//0
//		pass = ((b[0] ^ b[1] )== 1);
//		if(!pass){return_conformance_order( 88); return;}
		if(!(a_getter(23) & B31)){return_conformance_order( 88); return;}
	case   89://NEUTRAL_TRESHOLD
		b[0] = (f_getter(25) & B27)?1:0;
		b[1] = (w_getter(25) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 89); return;}
	case   90://WEIGHT_MINIMIZATION_START
		b[0] = (a_getter(24) & B31)?1:0;
		b[1] = (w_getter(24) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[0];
			firstNonConformance = 90;
		}
	case   91:
		b[0] = (f_getter(26) & B27)?1:0;
		b[1] = (w_getter(26) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[1];
			if(!firstNonConformance)
				firstNonConformance =   91;
		}
	case   92:
		b[0] = (a_getter(25) & B29)?1:0;
		b[1] = (w_getter(24) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[2];
			if(!firstNonConformance)
				firstNonConformance =   92;
		}
	case   93:
		b[0] = (f_getter(27) & B27)?1:0;
		b[1] = (w_getter(22) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[3];
			if(!firstNonConformance)
				firstNonConformance =   93;
		}
	case   94:
		b[0] = (f_getter(27) & B29)?1:0;
		b[1] = (w_getter(23) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[4];
			if(!firstNonConformance)
				firstNonConformance =   94;
		}
	case   95:
		pass = false;
		b[0] = (a_getter(27) & B29)?1:0;
		b[1] = (w_getter(26) & B29)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 1);
		if(condition[0])
		{
			pass = true;
		}
		else
		{
			b[0] = (a_getter(27) & B30)?1:0;
			b[1] = (w_getter(26) & B29)?1:0;
			condition[1] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(27) & B31)?1:0;
			b[1] = (w_getter(26) & B29)?1:0;
			condition[2] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(25) & B0)?1:0;
			b[1] = (a_getter(26) & B0)?1:0;
			b[2] = (w_getter(29) & B2)?1:0;
			b[3] = (w_getter(26) & B29)?1:0;
			condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(28) & B31)?1:0;
			b[1] = (w_getter(29) & B2)?1:0;
			condition[4] = ((b[0] ^ b[1] )== 0);
			b[0] = (a_getter(28) & B28)?1:0;
			b[1] = (w_getter(24) & B29)?1:0;
			b[2] = (w_getter(26) & B29)?1:0;
			b[3] = (a_getter(26) & B30)?1:0;
			condition[5] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(29) & B29)?1:0;
			b[1] = (w_getter(24) & B29)?1:0;
			condition[6] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(28) & B30)?1:0;
			b[1] = (a_getter(29) & B28)?1:0;
			b[2] = (w_getter(26) & B29)?1:0;
			b[3] = (w_getter(30) & B27)?1:0;
			condition[7] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(30) & B29)?1:0;
			b[1] = (w_getter(30) & B27)?1:0;
			condition[8] = ((b[0] ^ b[1] )== 1);
			if(condition[3]&&condition[5]&&condition[7]&&(condition[1] || (condition[2] && condition[4] && condition[6] && condition[8])))
			{
				pass = true;
			}
		}
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[5];
			if(!firstNonConformance)
				firstNonConformance =   95;
		}
	case   96:
		b[0] = (a_getter(27) & B0)?1:0;
		b[1] = (a_getter(28) & B0)?1:0;
		b[2] = (w_getter(30) & B30)?1:0;
		b[3] = (w_getter(28) & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[6];
			if(!firstNonConformance)
				firstNonConformance =   96;
		}
	case   97://WEIGHT_MINIMIZATION_END and LAST_EQUATION_TO_CORRECT
		b[0] = (a_getter(29) & B29)?1:0;
		b[1] = (w_getter(29) & B2)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[7];
			if(!firstNonConformance)
				firstNonConformance = 97;
		}
		if(firstNonConformance)
		{
			windowWeight_setter() = startToEndWeight;
			windowWeightMask_setter() = weightBitMask;
			firstUnsatisfiedEquation_setter() = firstNonConformance;
			return;
		}
		windowWeight_setter() = 0;
	case   98:
		pass = false;
		b[0] = (a_getter(29) & B30)?1:0;
		b[1] = (w_getter(28) & B30)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 0);
		b[0] = (a_getter(29) & B31)?1:0;
		b[1] = (w_getter(28) & B30)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_getter(31) & B29)?1:0;
		b[1] = (w_getter(31) & B28)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_getter(32) & B29)?1:0;
		b[1] = (w_getter(32) & B28)?1:0;
		condition[3] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]&&condition[3]))
		{
			pass = true;
		}
		if(!pass){return_conformance_order( 98); return;}
	case   99:
		b[0] = (a_getter(25) & B31)?1:0;
		b[1] = (a_getter(26) & B31)?1:0;
		b[2] = (w_getter(29) & B2)?1:0;
		b[3] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass){return_conformance_order( 99); return;}
	case  100:
		b[0] = (f_getter(28) & B27)?1:0;
		b[1] = (w_getter(28) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(100); return;}
	case  101:
		b[0] = (a_getter(26) & B29)?1:0;
		b[1] = (a_getter(28) & B27)?1:0;
		b[2] = (w_getter(24) & B29)?1:0;
		b[3] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass){return_conformance_order(101); return;}
	case  102:
		b[0] = (a_getter(28) & B29)?1:0;
		b[1] = (a_getter(29) & B27)?1:0;
		b[2] = (w_getter(26) & B29)?1:0;
		b[3] = (w_getter(30) & B27)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass){return_conformance_order(102); return;}
	case  103:
		b[0] = (a_getter(28) & B31)?1:0;
		b[1] = (w_getter(28) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(103); return;}
	case  104:
		b[0] = (f_getter(31) & B27)?1:0;
		b[1] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(104); return;}
	case  105:
		b[0] = (a_getter(28) & B30)?1:0;
		b[1] = (a_getter(30) & B28)?1:0;
		b[2] = (w_getter(28) & B30)?1:0;
		b[3] = (w_getter(31) & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){return_conformance_order(105); return;}
	case  106:
		b[0] = (a_getter(32) & B31)?1:0;
		b[1] = (w_getter(32) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(106); return;}
	case  107:
		b[0] = (f_getter(32) & B27)?1:0;
		b[1] = (w_getter(32) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(107); return;}
	case  108:
		b[0] = (w_getter(32) & B28)?1:0;
		b[1] = (a_getter(31) & B28)?1:0;
		b[2] = (a_getter(30) & B30)?1:0;
		b[3] = (w_getter(28) & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){return_conformance_order(108); return;}
	case  109:
		b[0] = (w_getter(33) & B4)?1:0;
		b[1] = (a_getter(33) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(109); return;}
	case  110:
		b[0] = (w_getter(34) & B29)?1:0;
		b[1] = (f_getter(34) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(110); return;}
	case  111:
		b[0] = (w_getter(32) & B4)?1:0;
		b[1] = (f_getter(36) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(111); return;}
	case  112:
		b[0] = (a_getter(39) & B31)?1:0;
		b[1] = (w_getter(39) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(112); return;}
	case  113:
		b[0] = (a_getter(38) & B1)?1:0;
		b[1] = (a_getter(37) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(113); return;}
	case  114:
		b[0] = (a_getter(41) & B31)?1:0;
		b[1] = (w_getter(41) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(114); return;}
	case  115:
		b[0] = (a_getter(40) & B29)?1:0;
		b[1] = (a_getter(38) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(115); return;}
	case  116:
		b[0] = (a_getter(41) & B29)?1:0;
		b[1] = (a_getter(40) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(116); return;}
	case  117:
		b[0] = (a_getter(40) & B1)?1:0;
		b[1] = (a_getter(39) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(117); return;}
	case  118:
		b[0] = (a_getter(43) & B31)?1:0;
		b[1] = (w_getter(43) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(118); return;}
	case  119:
		b[0] = (a_getter(42) & B29)?1:0;
		b[1] = (a_getter(40) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(119); return;}
	case  120:
		b[0] = (a_getter(43) & B29)?1:0;
		b[1] = (a_getter(42) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(120); return;}
	case  121:
		b[0] = (a_getter(42) & B1)?1:0;
		b[1] = (a_getter(41) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(121); return;}
	case  122:
		b[0] = (a_getter(45) & B30)?1:0;
		b[1] = (w_getter(44) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(122); return;}
	case  123:
		b[0] = (a_getter(44) & B29)?1:0;
		b[1] = (a_getter(42) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(123); return;}
	case  124:
		b[0] = (a_getter(45) & B29)?1:0;
		b[1] = (a_getter(44) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(124); return;}
	case  125:
		b[0] = (a_getter(44) & B0)?1:0;
		b[1] = (a_getter(43) & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(125); return;}
	case  126:
		b[0] = (a_getter(46) & B28)?1:0;
		b[1] = (a_getter(44) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(126); return;}
	case  127:
		b[0] = (a_getter(48) & B31)?1:0;
		b[1] = (w_getter(48) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(127); return;}
	case  128:
		b[0] = (a_getter(47) & B28)?1:0;
		b[1] = (a_getter(46) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(128); return;}
	case  129:
		b[0] = (a_getter(47) & B1)?1:0;
		b[1] = (a_getter(46) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(129); return;}
	case  130:
		b[0] = (a_getter(49) & B29)?1:0;
		b[1] = (a_getter(47) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(130); return;}
	case  131:
		b[0] = (a_getter(50) & B29)?1:0;
		b[1] = (a_getter(49) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(131); return;}
	case  132:
		b[0] = (a_getter(53) & B31)?1:0;
		b[1] = (w_getter(53) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(132); return;}
	case  133:
		b[0] = (a_getter(52) & B1)?1:0;
		b[1] = (a_getter(51) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(133); return;}
	case  134:
		b[0] = (a_getter(54) & B29)?1:0;
		b[1] = (a_getter(52) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(134); return;}
	case  135:
		b[0] = (a_getter(55) & B29)?1:0;
		b[1] = (a_getter(54) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(135); return;}
	case  136:
		b[0] = (a_getter(59) & B31)?1:0;
		b[1] = (w_getter(59) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(136); return;}
	case  137:
		b[0] = (a_getter(61) & B31)?1:0;
		b[1] = (w_getter(61) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(137); return;}
	case  138:
		b[0] = (w_getter(61) & B29)?1:0;
		b[1] = (f_getter(61) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(138); return;}
	case  139:
		b[0] = (w_getter(62) & B29)?1:0;
		b[1] = (f_getter(62) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(139); return;}
	case  140:
		b[0] = (w_getter(59) & B4)?1:0;
		b[1] = (f_getter(63) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(140); return;}
	case  141:
		b[0] = (w_getter(64) & B29)?1:0;
		b[1] = (f_getter(64) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(141); return;}
	}
	firstUnsatisfiedEquation_setter() = 142;
	return;
}

void SHA1::check_conformance_no_aux(int start)
{
	u32 b[4] = {0};
	bool condition[12];
	bool pass = false;
	int firstNonConformance = 0;
	int startToEndWeight = 0;
	int weightBitMask = 0;
	switch(start)
	{
	case  12:
		b[0] = (a_getter(7) & B9)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 12); return;}
	case   17:
		b[0] = (a_getter(7) & B30)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 17); return;}
	case   18:
		b[0] = (a_getter(7) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 18); return;}
	case   21:
		b[0] = (a_getter(8) & B9)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 21); return;}
	case   22:
		b[0] = (a_getter(8) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 22); return;}
	case   23:
		b[0] = (a_getter(8) & B29)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 23); return;}
	case   24:
		b[0] = (a_getter(8) & B30)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 24); return;}
	case   25:
		b[0] = (a_getter(8) & B31)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 25); return;}
	case   26:
		b[0] = (a_getter(9) & B1)?1:0;
		b[1] = (a_getter(8) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 26); return;}
	case   27:
		b[0] = (a_getter(9) & B6)?1:0;
		b[1] = (a_getter(8) & B6)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 27); return;}
	case   28:
		b[0] = (a_getter(9) & B26)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 28); return;}
	case   29:
		b[0] = (a_getter(9) & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 29); return;}
	case   36:
		b[0] = (a_getter(10) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 36); return;}
	case   37:
		b[0] = (a_getter(10) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 37); return;}
	case   38:
		b[0] = (a_getter(10) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 38); return;}
	case   39:
		b[0] = (a_getter(10) & B31)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 39); return;}
	case   40:
		b[0] = (a_getter(10) & B1)?1:0;
		b[1] = (a_getter(11) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 40); return;}
	case   41:
		b[0] = (a_getter(11) & B2)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 41); return;}
	case   42:
		b[0] = (a_getter(11) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 42); return;}
	case   43:
		b[0] = (a_getter(11) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 43); return;}
	case   44:
		b[0] = (a_getter(11) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 44); return;}
	case   45:
		b[0] = (a_getter(12) & B2)?1:0;
		b[1] = (w_getter(8) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 45); return;}
	case   46:
		b[0] = (a_getter(12) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 46); return;}
	case   47:
		b[0] = (a_getter(12) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 47); return;}
	case  49://142
		b[0] = (a_getter(12) & B30)?1:0;
		b[1] = (a_getter(11) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 49); return;}
	case   50:
		b[0] = (a_getter(12) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 50); return;}
	case   52:
		b[0] = (a_getter(13) & B1)?1:0;
		b[1] = (a_getter(12) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 52); return;}
	case   53:
		b[0] = (a_getter(13) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 53); return;}
	case   54:
		b[0] = (a_getter(13) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 54); return;}
	case   55:
		b[0] = (a_getter(13) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 55); return;}
	case   56:
		b[0] = (a_getter(13) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 56); return;}
	case   57:
		b[0] = (a_getter(14) & B26)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 57); return;}
	case   58:
		b[0] = (a_getter(14) & B27)?1:0;
		b[1] = (f_getter(14) & B0)?1:0;
		b[2] = (w_getter(14) & B0)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] )== 0);
		if(!pass){return_conformance_order( 58); return;}
	case   59:
		b[0] = (a_getter(14) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 59); return;}
	case   60:
		b[0] = (a_getter(14) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 60); return;}
//	case   61://aux
//		b[0] = (a_getter(15) & B4)?1:0;
//		pass = ((b[0] )== 0);
//		if(!pass){return_conformance_order( 61); return;}
	case   62:
		b[0] = (a_getter(15) & B26)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 62); return;}
	case   63:
		b[0] = (a_getter(15) & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 63); return;}
	case   64:
		b[0] = (a_getter(15) & B29)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 64); return;}
	case   65:
		b[0] = (a_getter(15) & B31)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 65); return;}
	case   66:
		b[0] = (a_getter(16) & B0)?1:0;
		b[1] = (a_getter(15) & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 66); return;}
	case   67:
		b[0] = (a_getter(16) & B27)?1:0;
		b[1] = (w_getter(14) & B26)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 67); return;}
	case  68:
		b[0] = (a_getter(17) & B1)?1:0;
		b[1] = (a_getter(16) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 68); return;}
//	case   69://aux condition
//		b[0] = (a_getter(16) & B3)?1:0;
//		pass = ((b[0] )== 0);
//		if(!pass){return_conformance_order( 69); return;}
	case   70:
		b[0] = (a_getter(16) & B29)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 70); return;}
	case   71:
		b[0] = (a_getter(17) & B27)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 71); return;}
	case   72:
		b[0] = (a_getter(17) & B30)?1:0;
		pass = ((b[0] )== 1);
		if(!pass){return_conformance_order( 72); return;}
	case   73:
		b[0] = (a_getter(18) & B27)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 73); return;}
	case   74:
		b[0] = (a_getter(18) & B28)?1:0;
		pass = ((b[0] )== 0);
		if(!pass){return_conformance_order( 74); return;}
	case   75:
		b[0] = (a_getter(18) & B31)?1:0;
		b[1] = (w_getter(18) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 75); return;}
	case   76:
		b[0] = (a_getter(19) & B0)?1:0;
		b[1] = (a_getter(20) & B0)?1:0;
		b[2] = (w_getter(22) & B30)?1:0;
		b[3] = (w_getter(20) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){return_conformance_order( 76); return;}
	case   77:
		b[0] = (f_getter(20) & B28)?1:0;
		b[1] = (w_getter(20) & B28)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 77); return;}
	case   78:
		b[0] = (a_getter(19) & B29)?1:0;//0
		b[1] = (w_getter(19) & B2)?1:0;//0
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 78); return;}
	case   79:
		b[0] = (f_getter(21) & B27)?1:0;
		b[1] = (w_getter(21) & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 79); return;}
	case   80:
		b[0] = (f_getter(21) & B29)?1:0;
		b[1] = (w_getter(21) & B27)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 80); return;}
	case   81:
		b[0] = (a_getter(20) & B31)?1:0;//0
		b[1] = (w_getter(20) & B4)?1:0;//1
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 81); return;}
	case   82:
		b[0] = (f_getter(22) & B27)?1:0;
		b[1] = (w_getter(22) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 82); return;}
	case   83:
		b[0] = (f_getter(22) & B29)?1:0;
		b[1] = (w_getter(18) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order( 83); return;}
	case   84:
		pass = false;
		b[0] = (a_getter(20) & B30)?1:0;
		b[1] = (a_getter(22) & B28)?1:0;
		condition[3] = ((b[0] ^ b[1])== 0);
//		b[2] = (w_getter(20) & B29)?1:0;//1
//		b[3] = (w_getter(23) & B27)?1:0;//0
//		condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
//		if(!condition[3]){return_conformance_order( 84); return;}
		b[0] = (a_getter(21) & B30)?1:0;
		condition[0] = b[0]== 0;
//		b[1] = (w_getter(20) & B29)?1:0;//1
//		condition[0] = ((b[0] ^ b[1] )== 1);
		b[0] = (a_getter(21) & B31)?1:0;
		condition[1] = b[0]== 0;
//		b[1] = (w_getter(20) & B29)?1:0;//1
//		condition[1] = ((b[0] ^ b[1] )== 1);
//		b[0] = (w_getter(23) & B27)?1:0;//0
		b[1] = (f_getter(23) & B29)?1:0;
		condition[2] = b[1]== 1;
//		condition[2] = ((b[0] ^ b[1] )== 1);
		if(condition[3] && ((condition[0]&&condition[2]) || (!condition[0]&&condition[1])))
			pass = true;
//		else if(solveEquation84(condition))
//			pass = true;
		if(!pass){return_conformance_order( 84); return;}
	case   85:
		b[0] = (a_getter(22) & B31)?1:0;//1
//		b[1] = (w_getter(22) & B4)?1:0;//0
//		pass = ((b[0] ^ b[1] )== 1);
		pass = (b[0] == 1);
		if(!pass){return_conformance_order( 85); return;}
	case   86:
//		b[0] = (a_getter(22) & B30)?1:0;
//		b[1] = (a_getter(23) & B28)?1:0;
////		b[2] = (w_getter(20) & B29)?1:0;//1
//		b[3] = (w_getter(24) & B28)?1:0;
//		pass = ((b[0] ^ b[1]/*^ b[2]*/ ^ b[3] )== 0);
//		if(!pass){return_conformance_order( 86); return;}
		if(((a_getter(22)>>2) ^ a_getter(23) ^ w_getter(24)) & B28){return_conformance_order( 86); return;}
	case   87:
//		b[0] = (a_getter(23) & B29)?1:0;
//		b[1] = (w_getter(22) & B29)?1:0;//0
//		pass = ((b[0] ^ b[1] )== 0);
//		if(!pass){return_conformance_order( 87); return;}
		if((a_getter(23) & B29)){return_conformance_order( 87); return;}
	case   88:
//		b[0] = (a_getter(23) & B31)?1:0;
//		b[1] = (w_getter(23) & B4)?1:0;//0
//		pass = ((b[0] ^ b[1] )== 1);
//		if(!pass){return_conformance_order( 88); return;}
		if(!(a_getter(23) & B31)){return_conformance_order( 88); return;}
	case   89://NEUTRAL_TRESHOLD
		b[0] = (f_getter(25) & B27)?1:0;
		b[1] = (w_getter(25) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order( 89); return;}
	case   90://WEIGHT_MINIMIZATION_START
		b[0] = (a_getter(24) & B31)?1:0;
		b[1] = (w_getter(24) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[0];
			firstNonConformance = 90;
		}
	case   91:
		b[0] = (f_getter(26) & B27)?1:0;
		b[1] = (w_getter(26) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[1];
			if(!firstNonConformance)
				firstNonConformance =   91;
		}
	case   92:
		b[0] = (a_getter(25) & B29)?1:0;
		b[1] = (w_getter(24) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[2];
			if(!firstNonConformance)
				firstNonConformance =   92;
		}
	case   93:
		b[0] = (f_getter(27) & B27)?1:0;
		b[1] = (w_getter(22) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[3];
			if(!firstNonConformance)
				firstNonConformance =   93;
		}
	case   94:
		b[0] = (f_getter(27) & B29)?1:0;
		b[1] = (w_getter(23) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[4];
			if(!firstNonConformance)
				firstNonConformance =   94;
		}
	case   95:
		pass = false;
		b[0] = (a_getter(27) & B29)?1:0;
		b[1] = (w_getter(26) & B29)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 1);
		if(condition[0])
		{
			pass = true;
		}
		else
		{
			b[0] = (a_getter(27) & B30)?1:0;
			b[1] = (w_getter(26) & B29)?1:0;
			condition[1] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(27) & B31)?1:0;
			b[1] = (w_getter(26) & B29)?1:0;
			condition[2] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(25) & B0)?1:0;
			b[1] = (a_getter(26) & B0)?1:0;
			b[2] = (w_getter(29) & B2)?1:0;
			b[3] = (w_getter(26) & B29)?1:0;
			condition[3] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(28) & B31)?1:0;
			b[1] = (w_getter(29) & B2)?1:0;
			condition[4] = ((b[0] ^ b[1] )== 0);
			b[0] = (a_getter(28) & B28)?1:0;
			b[1] = (w_getter(24) & B29)?1:0;
			b[2] = (w_getter(26) & B29)?1:0;
			b[3] = (a_getter(26) & B30)?1:0;
			condition[5] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(29) & B29)?1:0;
			b[1] = (w_getter(24) & B29)?1:0;
			condition[6] = ((b[0] ^ b[1] )== 1);
			b[0] = (a_getter(28) & B30)?1:0;
			b[1] = (a_getter(29) & B28)?1:0;
			b[2] = (w_getter(26) & B29)?1:0;
			b[3] = (w_getter(30) & B27)?1:0;
			condition[7] = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
			b[0] = (f_getter(30) & B29)?1:0;
			b[1] = (w_getter(30) & B27)?1:0;
			condition[8] = ((b[0] ^ b[1] )== 1);
			if(condition[3]&&condition[5]&&condition[7]&&(condition[1] || (condition[2] && condition[4] && condition[6] && condition[8])))
			{
				pass = true;
			}
		}
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[5];
			if(!firstNonConformance)
				firstNonConformance =   95;
		}
	case   96:
		b[0] = (a_getter(27) & B0)?1:0;
		b[1] = (a_getter(28) & B0)?1:0;
		b[2] = (w_getter(30) & B30)?1:0;
		b[3] = (w_getter(28) & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[6];
			if(!firstNonConformance)
				firstNonConformance =   96;
		}
	case   97://WEIGHT_MINIMIZATION_END and LAST_EQUATION_TO_CORRECT
		b[0] = (a_getter(29) & B29)?1:0;
		b[1] = (w_getter(29) & B2)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass)
		{
			startToEndWeight++;
			weightBitMask |= BIT_BY_INDEX[7];
			if(!firstNonConformance)
				firstNonConformance = 97;
		}
		if(firstNonConformance)
		{
			windowWeight_setter() = startToEndWeight;
			windowWeightMask_setter() = weightBitMask;
			firstUnsatisfiedEquation_setter() = firstNonConformance;
			return;
		}
		windowWeight_setter() = 0;
	case   98:
		pass = false;
		b[0] = (a_getter(29) & B30)?1:0;
		b[1] = (w_getter(28) & B30)?1:0;
		condition[0] = ((b[0] ^ b[1] )== 0);
		b[0] = (a_getter(29) & B31)?1:0;
		b[1] = (w_getter(28) & B30)?1:0;
		condition[1] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_getter(31) & B29)?1:0;
		b[1] = (w_getter(31) & B28)?1:0;
		condition[2] = ((b[0] ^ b[1] )== 0);
		b[0] = (f_getter(32) & B29)?1:0;
		b[1] = (w_getter(32) & B28)?1:0;
		condition[3] = ((b[0] ^ b[1] )== 1);
		if((condition[0]&&condition[2]) || (!condition[0]&&condition[1]&&condition[3]))
		{
			pass = true;
		}
		if(!pass){return_conformance_order( 98); return;}
	case   99:
		b[0] = (a_getter(25) & B31)?1:0;
		b[1] = (a_getter(26) & B31)?1:0;
		b[2] = (w_getter(29) & B2)?1:0;
		b[3] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass){return_conformance_order( 99); return;}
	case  100:
		b[0] = (f_getter(28) & B27)?1:0;
		b[1] = (w_getter(28) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(100); return;}
	case  101:
		b[0] = (a_getter(26) & B29)?1:0;
		b[1] = (a_getter(28) & B27)?1:0;
		b[2] = (w_getter(24) & B29)?1:0;
		b[3] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass){return_conformance_order(101); return;}
	case  102:
		b[0] = (a_getter(28) & B29)?1:0;
		b[1] = (a_getter(29) & B27)?1:0;
		b[2] = (w_getter(26) & B29)?1:0;
		b[3] = (w_getter(30) & B27)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 0);
		if(!pass){return_conformance_order(102); return;}
	case  103:
		b[0] = (a_getter(28) & B31)?1:0;
		b[1] = (w_getter(28) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(103); return;}
	case  104:
		b[0] = (f_getter(31) & B27)?1:0;
		b[1] = (w_getter(26) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(104); return;}
	case  105:
		b[0] = (a_getter(28) & B30)?1:0;
		b[1] = (a_getter(30) & B28)?1:0;
		b[2] = (w_getter(28) & B30)?1:0;
		b[3] = (w_getter(31) & B28)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){return_conformance_order(105); return;}
	case  106:
		b[0] = (a_getter(32) & B31)?1:0;
		b[1] = (w_getter(32) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(106); return;}
	case  107:
		b[0] = (f_getter(32) & B27)?1:0;
		b[1] = (w_getter(32) & B27)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(107); return;}
	case  108:
		b[0] = (w_getter(32) & B28)?1:0;
		b[1] = (a_getter(31) & B28)?1:0;
		b[2] = (a_getter(30) & B30)?1:0;
		b[3] = (w_getter(28) & B30)?1:0;
		pass = ((b[0] ^ b[1] ^ b[2] ^ b[3] )== 1);
		if(!pass){return_conformance_order(108); return;}
	case  109:
		b[0] = (w_getter(33) & B4)?1:0;
		b[1] = (a_getter(33) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(109); return;}
	case  110:
		b[0] = (w_getter(34) & B29)?1:0;
		b[1] = (f_getter(34) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(110); return;}
	case  111:
		b[0] = (w_getter(32) & B4)?1:0;
		b[1] = (f_getter(36) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(111); return;}
	case  112:
		b[0] = (a_getter(39) & B31)?1:0;
		b[1] = (w_getter(39) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(112); return;}
	case  113:
		b[0] = (a_getter(38) & B1)?1:0;
		b[1] = (a_getter(37) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(113); return;}
	case  114:
		b[0] = (a_getter(41) & B31)?1:0;
		b[1] = (w_getter(41) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(114); return;}
	case  115:
		b[0] = (a_getter(40) & B29)?1:0;
		b[1] = (a_getter(38) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(115); return;}
	case  116:
		b[0] = (a_getter(41) & B29)?1:0;
		b[1] = (a_getter(40) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(116); return;}
	case  117:
		b[0] = (a_getter(40) & B1)?1:0;
		b[1] = (a_getter(39) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(117); return;}
	case  118:
		b[0] = (a_getter(43) & B31)?1:0;
		b[1] = (w_getter(43) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(118); return;}
	case  119:
		b[0] = (a_getter(42) & B29)?1:0;
		b[1] = (a_getter(40) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(119); return;}
	case  120:
		b[0] = (a_getter(43) & B29)?1:0;
		b[1] = (a_getter(42) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(120); return;}
	case  121:
		b[0] = (a_getter(42) & B1)?1:0;
		b[1] = (a_getter(41) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(121); return;}
	case  122:
		b[0] = (a_getter(45) & B30)?1:0;
		b[1] = (w_getter(44) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(122); return;}
	case  123:
		b[0] = (a_getter(44) & B29)?1:0;
		b[1] = (a_getter(42) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(123); return;}
	case  124:
		b[0] = (a_getter(45) & B29)?1:0;
		b[1] = (a_getter(44) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(124); return;}
	case  125:
		b[0] = (a_getter(44) & B0)?1:0;
		b[1] = (a_getter(43) & B0)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(125); return;}
	case  126:
		b[0] = (a_getter(46) & B28)?1:0;
		b[1] = (a_getter(44) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(126); return;}
	case  127:
		b[0] = (a_getter(48) & B31)?1:0;
		b[1] = (w_getter(48) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(127); return;}
	case  128:
		b[0] = (a_getter(47) & B28)?1:0;
		b[1] = (a_getter(46) & B30)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(128); return;}
	case  129:
		b[0] = (a_getter(47) & B1)?1:0;
		b[1] = (a_getter(46) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(129); return;}
	case  130:
		b[0] = (a_getter(49) & B29)?1:0;
		b[1] = (a_getter(47) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(130); return;}
	case  131:
		b[0] = (a_getter(50) & B29)?1:0;
		b[1] = (a_getter(49) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(131); return;}
	case  132:
		b[0] = (a_getter(53) & B31)?1:0;
		b[1] = (w_getter(53) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(132); return;}
	case  133:
		b[0] = (a_getter(52) & B1)?1:0;
		b[1] = (a_getter(51) & B1)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(133); return;}
	case  134:
		b[0] = (a_getter(54) & B29)?1:0;
		b[1] = (a_getter(52) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(134); return;}
	case  135:
		b[0] = (a_getter(55) & B29)?1:0;
		b[1] = (a_getter(54) & B31)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(135); return;}
	case  136:
		b[0] = (a_getter(59) & B31)?1:0;
		b[1] = (w_getter(59) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(136); return;}
	case  137:
		b[0] = (a_getter(61) & B31)?1:0;
		b[1] = (w_getter(61) & B4)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(137); return;}
	case  138:
		b[0] = (w_getter(61) & B29)?1:0;
		b[1] = (f_getter(61) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(138); return;}
	case  139:
		b[0] = (w_getter(62) & B29)?1:0;
		b[1] = (f_getter(62) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(139); return;}
	case  140:
		b[0] = (w_getter(59) & B4)?1:0;
		b[1] = (f_getter(63) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 0);
		if(!pass){return_conformance_order(140); return;}
	case  141:
		b[0] = (w_getter(64) & B29)?1:0;
		b[1] = (f_getter(64) & B29)?1:0;
		pass = ((b[0] ^ b[1] )== 1);
		if(!pass){return_conformance_order(141); return;}
	}
	firstUnsatisfiedEquation_setter() = 142;
	return;
}
