#include "solve.h"
#include "check_equations.h"

//  #define DEBUG
//static int success, fail, total;
static int cNeutral[106], cComplement[106];

bool SHA1::solve90(){
if((!((mA[6]^mA[5]) & B9)) )
	{
		if(modifyAndUpdate_6(*this, B8|B7, m) > 89){
			SHA1 ref = *this;
			ref.mUpdatedToRound = 4;
			for(int i = 22; i < 32; i++)
				update_w_a_a30_20_39(*this, i);

			for(int equ = 90; equ < 106; equ++){
				bool c1 = c_check_single_equation(*this, equ);
				bool c2  = ref.check_single_equation_by_order(equ);
				if(c1^c2){
//					if(equ == 90){
//						ref.compare_duo_Sha1ParameterNotUpdated(*this, 5, 25, stderr);
//						ref.check_conformance(49);
//						fprintf(stderr, "%d\n", ref.firstUnsatisfiedEquation_getter());
//						rs_pause();
//					}

					cComplement[equ]++;
				}
				else
					cNeutral[equ]++;

			}
			for(int equ = 90; equ < 106; equ++){
				fprintf(stderr, "%5d ", cComplement[equ]);
			}
			fprintf(stderr, "\n");
			for(int equ = 90; equ < 106; equ++){
				fprintf(stderr, "%5d ", cNeutral[equ]);
			}
			fprintf(stderr, "\n");
			for(int equ = 90; equ < 106; equ++){
				fprintf(stderr, "%.3g ", (double)cNeutral[equ]/(cNeutral[equ]+cComplement[equ]));
			}
			fprintf(stderr, "\n");
			for(int equ = 90; equ < 106; equ++){
				fprintf(stderr, "%.3g ", (double)cComplement[equ]/(cNeutral[equ]+cComplement[equ]));
			}
			fprintf(stderr, "\n\n");
		}




//		int conf = modifyAndUpdate_6(*this, B8, m);
//		if(conf > 90){
//			ref.compare_duo_Sha1ParameterNotUpdated(*this, 19, 27, stderr);
//			rs_pause();
//			return true;
//		}





		m.restore(*this, 6, 11);
//		{fail++; fprintf(stderr,"%d %d %.2g\n",total, total-fail, (double)(total-fail)/total);}
	}
	return false;
}
