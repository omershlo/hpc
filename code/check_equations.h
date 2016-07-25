enum EQU_INDEX_ALL_NO_AUX{EQ_17=0,EQ_18=1,EQ_21=2,EQ_22=3,EQ_23=4,EQ_24=5,EQ_25=6,EQ_26=7,EQ_27=8,EQ_28=9,EQ_29=10,EQ_30=11,EQ_31=12,EQ_32=13,EQ_33=14,EQ_35=15,EQ_36=16,EQ_37=17,EQ_38=18,EQ_39=19,EQ_40=20,EQ_41=21,EQ_42=22,EQ_43=23,EQ_44=24,EQ_45=25,EQ_46=26,EQ_47=27,EQ_49=28,EQ_56=29,EQ_57=30,EQ_58=31,EQ_59=32,EQ_60=33,EQ_62=34,EQ_63=35,EQ_64=36,EQ_65=37,EQ_67=38,EQ_68=39,EQ_70=40,EQ_71=41,EQ_72=42,EQ_73=43,EQ_74=44,EQ_75=45,EQ_76=46,EQ_77=47,EQ_78=48,EQ_79=49,EQ_80=50,EQ_81=51,EQ_82=52,EQ_83=53,EQ_84=54,EQ_85=55,EQ_86=56,EQ_87=57,EQ_88=58,EQ_89=59,EQ_90=60,EQ_91=61,EQ_92=62,EQ_93=63,EQ_94=64,EQ_95=65,EQ_96=66,EQ_97=67,EQ_98=68,EQ_99=69,EQ_100=70,EQ_101=71,EQ_102=72,EQ_103=73,EQ_104=74,EQ_105=75,EQ_106=76,EQ_107=77,EQ_108=78,EQ_109=79,EQ_110=80,EQ_111=81,EQ_112=82,EQ_113=83,EQ_114=84,EQ_115=85,EQ_116=86,EQ_117=87,EQ_118=88,EQ_119=89,EQ_120=90,EQ_121=91,EQ_122=92,EQ_123=93,EQ_124=94,EQ_125=95,EQ_126=96,EQ_127=97,EQ_128=98,EQ_129=99,EQ_130=100,EQ_131=101,EQ_132=102,EQ_133=103,EQ_134=104,EQ_135=105,EQ_136=106,EQ_137=107,EQ_138=108,EQ_139=109,EQ_140=110,EQ_141=111};

const int c_equationList_all_no_aux[] = {17,18,21,22,23,24,25,26,27,28,29,30,31,32,33,35,36,37,38,39,40,41,42,43,44,45,46,47,49,56,57,58,59,60,62,63,64,65,67,68,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141};


bool c_check_single_equation(SHA1& ref, int equationOrder);
int c_compute_firstUnsatisfied(SHA1& ref);
bool c_check_single_equation(SHA1& ref, int equationOrder);
int  c_compute_firstUnsatisfied(SHA1& ref, int start);
void c_check_conformance(SHA1 &ref, int start);

inline void update_w_a_a30_00_19(SHA1 &ref, int rnd);
inline void update_w_a_a30_20_39(SHA1 &ref, int rnd);
inline void update_w_a_a30_40_59(SHA1 &ref, int rnd);
inline void update_w_a_a30_60_79(SHA1 &ref, int rnd);
inline void update_a_00_19(SHA1 &ref, int rnd);
inline void update_a_20_39(SHA1 &ref, int rnd);
inline void update_a30(SHA1 &ref, int rnd);
inline u32 f_20_39(SHA1 &ref, int rnd);
inline void updateW(SHA1 &ref, int round);

inline void update_w_a_a30_00_19(SHA1 &ref, int rnd)
{
	ref.mA30[rnd-2] = ROTATE(ref.mA[rnd-2], 30);
	Xupdate(ref.mW[rnd], ref.mW[rnd-3], ref.mW[rnd-8], ref.mW[rnd-14], ref.mW[rnd-16]);
	ref.mA[rnd+1] = K_00_19 + ref.mW[rnd] + ROTATE(ref.mA[rnd], 5) + F_00_19(ref.mA[rnd-1], ref.mA30[rnd-2], ref.mA30[rnd-3]) + ref.mA30[rnd-4];
}

inline void update_w_a_a30_20_39(SHA1 &ref, int rnd)
{
	ref.mA30[rnd-2] = ROTATE(ref.mA[rnd-2], 30);
	Xupdate(ref.mW[rnd], ref.mW[rnd-3], ref.mW[rnd-8], ref.mW[rnd-14], ref.mW[rnd-16]);
	ref.mA[rnd+1] = K_20_39 + ref.mW[rnd] + ROTATE(ref.mA[rnd], 5) + F_20_39(ref.mA[rnd-1], ref.mA30[rnd-2], ref.mA30[rnd-3]) + ref.mA30[rnd-4];
}

inline void update_w_a_a30_40_59(SHA1 &ref, int rnd)
{
	ref.mA30[rnd-2] = ROTATE(ref.mA[rnd-2], 30);
	Xupdate(ref.mW[rnd], ref.mW[rnd-3], ref.mW[rnd-8], ref.mW[rnd-14], ref.mW[rnd-16]);
	ref.mA[rnd+1] = K_40_59 + ref.mW[rnd] + ROTATE(ref.mA[rnd], 5) + F_40_59(ref.mA[rnd-1], ref.mA30[rnd-2], ref.mA30[rnd-3]) + ref.mA30[rnd-4];
}

inline void update_w_a_a30_60_79(SHA1 &ref, int rnd)
{
	ref.mA30[rnd-2] = ROTATE(ref.mA[rnd-2], 30);
	Xupdate(ref.mW[rnd], ref.mW[rnd-3], ref.mW[rnd-8], ref.mW[rnd-14], ref.mW[rnd-16]);
	ref.mA[rnd+1] = K_60_79 + ref.mW[rnd] + ROTATE(ref.mA[rnd], 5) + F_60_79(ref.mA[rnd-1], ref.mA30[rnd-2], ref.mA30[rnd-3]) + ref.mA30[rnd-4];
}

inline void update_a_00_19(SHA1 &ref, int rnd)
{
	ref.mA[rnd+1] = K_00_19 + ref.mW[rnd] + ROTATE(ref.mA[rnd], 5) + F_00_19(ref.mA[rnd-1], ref.mA30[rnd-2], ref.mA30[rnd-3]) + ref.mA30[rnd-4];
}

inline void update_a_20_39(SHA1 &ref, int rnd)
{
	ref.mA[rnd+1] = K_20_39 + ref.mW[rnd] + ROTATE(ref.mA[rnd], 5) + F_20_39(ref.mA[rnd-1], ref.mA30[rnd-2], ref.mA30[rnd-3]) + ref.mA30[rnd-4];
}

inline void update_a30(SHA1 &ref, int rnd)
{
	ref.mA30[rnd] = ROTATE(ref.mA[rnd], 30);
}

inline u32 f_20_39(SHA1 &ref, int rnd){
	return ref.mA[rnd-1] ^ ref.mA30[rnd-2] ^ ref.mA30[rnd-3];
}

inline void updateW(SHA1 &ref, int round){
	Xupdate(ref.mW[round], ref.mW[round - 3], ref.mW[round - 8], ref.mW[round - 14], ref.mW[round - 16]);
}
