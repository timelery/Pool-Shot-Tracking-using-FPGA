// Olga Souverneva 2016

#include "stdafx.h"
#include "ReddishHue.h"

static const float TRAINING_HUE_PD[][5] = 
{
	{0,0.073015,0,0,0.028043},
	{0,0.085694,0,0,0.026839},
	{0,0.095467,0,0,0.02323},
	{0,0.105,0,0,0.018393},
	{0,0.11292,0,0,0.011769},
	{0,0.11781,0,0,0.0052202},
	{0,0.11905,0,0,0.0099371},
	{0,0.11753,0,0,0.022034},
	{0,0.1128,0,0,0.030693},
	{0,0.11356,0,0,0.035915},
	{0,0.11306,0,0,0.038799},
	{0,0.10872,0,0,0.038387},
	{0,0.10249,0,0,0.034389},
	{0,0.093098,0,0,0.028285},
	{0,0.08589,0,0,0.022112},
	{0,0.079345,0,0,0.013712},
	{0,0.074918,0,0,0.0098264},
	{0,0.073173,0,0,0.037727},
	{0,0.071869,0,0,0.071092},
	{0,0.073922,0,0,0.096165},
	{0,0.076202,0,0,0.11519},
	{0,0.083582,0,0,0.12684},
	{0,0.092612,0,0,0.13214},
	{0,0.11231,0,0,0.12791},
	{0,0.14724,0,0,0.13107},
	{0,0.21107,0,0,0.12724},
	{0,0.31431,0,0,0.10831},
	{0,0.49562,0,0,0.12501},
	{0,0.7431,0,0,0.14154},
	{0,1.0657,0,0,0.15836},
	{0,1.5051,0,0,0.17814},
	{0,2.0235,0,0,0.19085},
	{0,2.5725,0,0,0.18978},
	{0,3.213,0,0,0.1778},
	{0,3.7942,0,0,0.18565},
	{0,4.412,0,0,0.18583},
	{0,4.9963,0,0,0.17221},
	{0,5.501,0,0,0.14758},
	{0,5.8432,0,0,0.15475},
	{0,6.1788,0,0,0.19434},
	{0,6.4769,0,0,0.22155},
	{0,6.562,0,0,0.23567},
	{0,6.5175,0,0,0.23769},
	{0,6.4449,0,0,0.2473},
	{0,6.312,0,0,0.25852},
	{0,6.0771,0,0,0.25963},
	{0,5.8836,0,0,0.23017},
	{0,5.6519,0,0,0.18257},
	{0,5.4218,0,0,0.17678},
	{0,5.2093,0,0,0.18069},
	{0,4.9378,0,0,0.16793},
	{0,4.7435,0.00083703,0,0.1489},
	{0,4.5874,0.015423,0,0.13134},
	{0,4.4052,0.019713,0,0.12224},
	{0,4.1745,0.054457,0,0.13544},
	{0,4.0657,0.072412,0,0.15168},
	{0,3.9912,0.085646,0,0.16314},
	{0,3.8465,0.057228,0,0.17522},
	{0,3.7103,0.13215,0,0.17573},
	{0,3.6184,0.22417,0,0.17542},
	{0,3.5355,0.2272,0,0.16773},
	{0,3.4428,0.21806,0,0.1517},
	{0,3.4315,0.19796,0,0.12765},
	{0,3.373,0.18959,0,0.090787},
	{0,3.2952,0.13112,0,0.078582},
	{0,3.209,0.14182,0,0.077437},
	{0,3.1293,0.12263,0,0.083343},
	{0,2.985,0.20228,0,0.093349},
	{0,2.9251,0.32667,0,0.094898},
	{0,2.8463,0.31106,0,0.094305},
	{0,2.7638,0.14174,0,0.089423},
	{0,2.6405,0.011426,0,0.078417},
	{0,2.5177,0.091092,0,0.059568},
	{0,2.4108,0.14071,0,0.039731},
	{0,2.318,0.11903,0,0.038108},
	{0,2.2213,0.03306,0,0.040329},
	{0,2.0623,0.032641,0,0.052042},
	{0,1.9437,0.073441,0,0.063364},
	{0,1.9054,0.12358,0,0.068498},
	{0,1.7897,0.1915,0,0.067445},
	{0,1.678,0.22928,0,0.069138},
	{0,1.5761,0.17901,0,0.10441},
	{0,1.4857,0.075712,0,0.1218},
	{0,1.3728,0.05609,0,0.13315},
	{0,1.281,0.15715,0,0.13909},
	{0,1.1864,0.17259,0,0.13556},
	{0.025771,1.0697,0.097146,0,0.12806},
	{0.032589,0.93977,0.047139,0,0.11506},
	{0.058706,0.844,0.16614,0,0.088318},
	{0.054758,0.75628,0.23963,0,0.049959},
	{0.033483,0.69924,0.24768,0,0.028235},
	{0,0.64795,0.19546,0,0.031129},
	{0.0063117,0.58335,0.13138,0,0.03166},
	{0.037211,0.53207,0.054509,0,0.031284},
	{0.0789,0.507,0.036513,0,0.02978},
	{0.071321,0.46658,0.096163,0,0.027291},
	{0.036465,0.42988,0.15401,0,0.025511},
	{0.031947,0.41988,0.16228,0,0.029285},
	{0.047736,0.41974,0.13624,0,0.042035},
	{0.060757,0.42901,0.084827,0,0.05907},
	{0.047837,0.44812,0.050467,0,0.070092},
	{0.054967,0.45635,0.069179,0,0.0793},
	{0.069374,0.46334,0.1169,0,0.091884},
	{0.082808,0.46428,0.12768,0,0.097544},
	{0.091081,0.4788,0.10535,0,0.096197},
	{0.176,0.50216,0.1212,0,0.08738},
	{0.20508,0.53353,0.14137,0,0.070921},
	{0.19782,0.55355,0.17902,0,0.055685},
	{0.2403,0.56708,0.44331,0,0.044159},
	{0.33762,0.58273,0.6039,0,0.042261},
	{0.44408,0.63064,0.61638,0,0.038455},
	{0.52264,0.68024,0.52115,0,0.052864},
	{0.58239,0.71665,0.54309,0,0.070396},
	{0.56117,0.74036,0.65701,0.0029674,0.084516},
	{0.7478,0.76244,0.82065,0.010232,0.097708},
	{0.95998,0.78343,1.0483,0.039929,0.11338},
	{1.2163,0.82091,1.8659,0.094996,0.12054},
	{1.5083,0.83648,2.5728,0.17759,0.12011},
	{1.7431,0.84534,2.3924,0.30465,0.10948},
	{2.07,0.82797,1.5787,0.47735,0.095084},
	{2.9475,0.83175,1.2762,0.72737,0.076512},
	{4.4744,0.83341,1.3765,1.0377,0.064023},
	{6.3556,0.83036,1.468,1.3634,0.051289},
	{7.6438,0.80354,1.7542,1.7541,0.11422},
	{8.0918,0.75207,2.1157,2.1841,0.18011},
	{8.4811,0.69767,2.1344,2.7143,0.23311},
	{9.595,0.67114,2.7226,3.3677,0.28295},
	{12.071,0.64135,3.7094,4.2487,0.31859},
	{14.522,0.59643,4.6508,5.3529,0.34348},
	{14.751,0.53785,4.7101,6.5958,0.38874},
	{15.989,0.47684,4.7885,7.7865,0.46801},
	{20.772,0.42328,5.8217,8.6884,0.57367},
	{26.226,0.37748,8.1219,9.1577,0.73308},
	{24.74,0.32235,11.5,9.2616,0.98798},
	{17.278,0.27343,15.374,9.0967,1.3038},
	{10.018,0.21937,19.228,8.8132,1.8033},
	{6.3011,0.19284,21.582,8.2838,2.4772},
	{3.875,0.16988,21.802,7.723,3.3753},
	{2.1063,0.15605,19.8,7.3074,4.3942},
	{1.3688,0.14922,16.093,7.0077,5.3547},
	{2.1068,0.15038,11.623,6.6867,6.1263},
	{3.1939,0.15325,7.7696,6.2282,6.6899},
	{3.1233,0.1645,5.6259,5.6785,7.0428},
	{1.9118,0.17707,4.416,5.1866,7.1415},
	{0.88925,0.18978,3.6491,4.9253,7.094},
	{1.3182,0.20431,2.609,5.1657,6.9341},
	{2.138,0.21479,1.8004,5.7234,6.6392},
	{2.1432,0.22511,1.3518,6.3511,6.4402},
	{1.6432,0.23893,1.4015,6.9482,6.3106},
	{1.6631,0.26018,1.4967,7.2843,6.1366},
	{1.6035,0.28887,1.4385,7.209,5.8309},
	{1.1381,0.31734,1.1886,6.8515,5.4914},
	{0.71156,0.34455,1.2541,6.3092,5.2336},
	{0.37211,0.36639,1.6218,5.7229,5.1107},
	{0.055073,0.38455,1.9403,5.1833,5.3006},
	{0.003242,0.40076,1.8427,4.937,5.6854},
	{0,0.41657,1.4052,5.0514,6.1895},
	{0.00012771,0.43441,1.0468,5.3393,6.9171},
	{0.0089925,0.44202,1.0517,5.6375,7.9904},
	{0.010765,0.43934,1.5317,5.725,9.444},
	{0.0054466,0.42971,1.7735,5.4135,10.661},
	{0,0.41043,1.4696,4.8292,11.442},
	{0,0.37938,0.87203,4.0495,11.689},
	{0,0.33828,0.54477,3.1575,11.358},
	{0,0.29397,0.36739,2.2434,10.443},
	{0,0.25447,0.30731,1.4267,9.0607},
	{0,0.22123,0.27817,0.76253,7.2763},
	{0,0.18838,0.262,0.30438,5.3219},
	{0,0.15577,0.18909,0.074946,3.6378},
	{0,0.12395,0.14252,0.0089932,2.4973},
	{0,0.092517,0.14545,0.00215,1.6279},
	{0.0075874,0.06402,0.12646,0.00016162,0.97556},
	{0.010986,0.044542,0.087643,0,0.56483},
	{0.0072919,0.031337,0.045904,0,0.28918},
	{0,0.021015,0.051273,0,0.1387},
	{0,0.013782,0.073236,0,0.090317},
	{0,0.0084014,0.097552,0,0.061656},
	{0,0.003041,0.077203,0,0.044492},
	{0,0.0014723,0.027122,0,0.035388},
	{0,0.0010398,0,0,0.030119},
	{0,0.00077718,0,0,0.032307},
	{0,0.00079876,0,0,0.040982},
	{0,0.00127,0,0,0.050835},
	{0,0.0023663,0,0,0.058385},
	{0,0.0043356,0,0,0.064623},
	{0,0.0071279,0,0,0.06433},
	{0,0.0094774,0,0,0.05803},
	{0,0.011543,0,0,0.049175},
	{0,0.014087,0,0,0.03825},
	{0,0.016,0,0,0.027021},
	{0,0.017282,0,0,0.013733},
	{0,0.018206,0,0,0.011297},
	{0,0.018773,0,0,0.011575},
	{0,0.018632,0,0,0.014772},
	{0,0.01778,0,0,0.022348},
	{0,0.016219,0,0,0.026829},
	{0,0.014361,0,0,0.02941},
	{0,0.012798,0,0,0.029766},
	{0,0.010969,0,0,0.027372},
	{0,0.010049,0,0,0.022228},
	{0,0.0095407,0,0,0.016208},
	{0,0.0095018,0,0,0.011599},
	{0,0.0089899,0,0,0.0058882},
	{0,0.0084887,0,0,0.0035599},
	{0,0.008683,0,0,0.0039419},
	{0,0.0094221,0,0,0.0039801},
	{0,0.0097521,0,0,0.0036745},
	{0,0.011136,0,0,0.0048647},
	{0,0.01217,0,0,0.013898},
	{0,0.014953,0,0,0.020182},
	{0,0.017246,0,0,0.0247},
	{0,0.019187,0,0,0.027508},
	{0,0.020489,0,0,0.027909},
	{0,0.02301,0,0,0.025903},
	{0,0.02525,0,0,0.021492},
	{0,0.027379,0,0,0.014674},
	{0,0.028634,0,0,0.0086576},
	{0,0.028786,0,0,0.0069556},
	{0,0.027834,0,0,0.010573},
	{0,0.025777,0,0,0.013546},
	{0,0.023189,0,0,0.015145},
	{0,0.021193,0,0,0.015368},
	{0,0.020523,0,0,0.014217},
	{0,0.01953,0,0,0.01169},
	{0,0.017892,0,0,0.0085262},
	{0,0.017379,0,0,0.0062631},
	{0,0.018703,0,0,0.0072772},
	{0,0.019622,0,0,0.00726},
	{0,0.02057,0,0,0.0078884},
	{0,0.024679,0,0,0.010918},
	{0,0.029453,0,0,0.012591},
	{0,0.033295,0,0,0.012889},
	{0,0.035803,0,0,0.011812},
	{0,0.038635,0,0,0.010523},
	{0,0.040518,0,0,0.0099338},
	{0,0.045124,0,0,0.0096703},
	{0,0.049144,0,0,0.012595},
	{0,0.055094,0,0,0.013764},
	{0,0.062775,0,0,0.014035},
	{0,0.069965,0,0,0.014974},
	{0,0.075566,0,0,0.014539},
	{0,0.080002,0,0,0.012728},
	{0,0.082802,0,0,0.00972},
	{0,0.082949,0,0,0.0070272},
	{0,0.084449,0,0,0.003303},
	{0,0.085761,0,0,0},
	{0,0.084744,0,0,0},
	{0,0.080338,0,0,0},
	{0,0.072965,0,0,0},
	{0,0.063814,0,0,0},
	{0,0.053492,0,0,0},
	{0,0.044228,0,0,0},
	{0,0.035233,0,0,0},
	{0,0.027385,0,0,0},
	{0,0.02052,0,0,0},
};

float GetReddishHuePd(BallId id, unsigned char tHue)
{
	switch(id)
	{
	case BALL_3:
		return TRAINING_HUE_PD[tHue][0];
	case BALL_4:
		return TRAINING_HUE_PD[tHue][1];
	case BALL_7:
		return TRAINING_HUE_PD[tHue][2];
	case BALL_11:
		return TRAINING_HUE_PD[tHue][3];
	case BALL_15:
		return TRAINING_HUE_PD[tHue][4];
	default:
		return 0.0f;
	}
}