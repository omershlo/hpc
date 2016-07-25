#include "wbs.h"

int read_linear_equations(char *file_name, linear_equation  *equ)
{
	linear_equation  variablesOfCurrentEquation[NUM_OF_LINEAR_EQUATIONS];
	linear_equation  equ_mask[NUM_OF_LINEAR_EQUATIONS];

	int i = 0;
	u32 solution;
	linear_equation variablesOfTheSet;
	variablesOfTheSet.init();
	for(i = 0; i < NUM_OF_LINEAR_EQUATIONS; i++)
	{
		equ[i].init();
		equ_mask[i].init();
		equ[i].pivotBitIndex = equ[i].pivotWordIndex = equ[i].solution = 0;
	}
	FILE *fp;
	assert(((fp = fopen(file_name, "r")) != NULL));
	i = 0;
	while(1)
	{
		if(11 != fscanf(fp, "%08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x",
				&(equ[i].w[15]), &(equ[i].w[14]), &(equ[i].w[13]), &(equ[i].w[12]), &(equ[i].w[11]), &(equ[i].w[10]),
				&(equ[i].w[9]), &(equ[i].w[8]), &(equ[i].w[7]), &(equ[i].w[6]), &(equ[i].w[5])))
		{
			fclose(fp);
			return i;
		}
		else
		{
			for(int n = 15; n > 4; n--)
			{
				if(i) equ_mask[i].w[n] |= equ_mask[i-1].w[n];
				equ_mask[i].w[n] |= equ[i].w[n];
				variablesOfCurrentEquation[i].w[n]  = equ[i].w[n] & ~(variablesOfTheSet.w[n]);
				variablesOfTheSet.w[n] |= equ[i].w[n];
			}
		}
		for(int j = 15; j > 4; j--)
		{
			if(variablesOfCurrentEquation[i].w[j])
			{
				for(int k = 31; k > -1; k--)
				{
					if(variablesOfCurrentEquation[i].w[j] & (1 << k))
					{
						equ[i].pivotWordIndex = j;
						equ[i].pivotBitIndex = k;
						j = 0;
						break;
					}
				}
			}
		}
		if(1 != fscanf(fp,"%x\n", &solution))
		{
			fclose(fp);
			return 0;
		}
		else
		{
			if(solution)
				equ[i].solution |= 1;
		}
		i++;
	}
	return 0;
}
