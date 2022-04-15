///////////////////////////////////////////////////////////////////////
// FunkyStars Text Mode Version
// Win32 Console-mode application
///////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Sine table: signed 16-bit ints, -32767 to 32767
// 628 values from 0-6.28 radians, 0.01 step
// Index as Radians*100 (to two places). For CoSine, add 157
const signed short SINE[] = {

0, 328, 655, 983, 1310, 1638, 1965, 2292, 2619, 2945, 
3271, 3597, 3923, 4248, 4572, 4897, 5220, 5544, 5866, 6188, 
6510, 6831, 7151, 7470, 7789, 8107, 8424, 8740, 9055, 9370, 
9683, 9996, 10307, 10618, 10927, 11236, 11543, 11849, 12154, 12458, 
12760, 13061, 13361, 13660, 13957, 14253, 14547, 14840, 15131, 15421, 
15709, 15996, 16281, 16565, 16847, 17127, 17405, 17682, 17957, 18230, 
18502, 18771, 19039, 19305, 19568, 19830, 20090, 20348, 20604, 20857, 
21109, 21359, 21606, 21851, 22094, 22335, 22574, 22810, 23044, 23276, 
23506, 23733, 23957, 24180, 24400, 24617, 24832, 25045, 25255, 25462, 
25667, 25870, 26069, 26267, 26461, 26653, 26842, 27029, 27213, 27394, 
27572, 27748, 27921, 28091, 28258, 28423, 28584, 28743, 28899, 29052, 
29202, 29349, 29494, 29635, 29773, 29909, 30041, 30170, 30297, 30420, 
30540, 30657, 30771, 30883, 30991, 31095, 31197, 31296, 31391, 31484, 
31573, 31659, 31742, 31822, 31898, 31972, 32042, 32109, 32172, 32233, 
32290, 32344, 32395, 32443, 32487, 32528, 32566, 32601, 32632, 32660, 
32685, 32706, 32725, 32740, 32751, 32760, 32765, 32767, 32766, 32761, 
32753, 32742, 32727, 32710, 32689, 32664, 32637, 32606, 32572, 32534, 
32494, 32450, 32403, 32353, 32299, 32242, 32182, 32119, 32053, 31983, 
31910, 31834, 31755, 31672, 31587, 31498, 31406, 31311, 31213, 31112, 
31007, 30900, 30789, 30676, 30559, 30439, 30316, 30191, 30062, 29930, 
29795, 29657, 29516, 29373, 29226, 29076, 28924, 28768, 28610, 28449, 
28285, 28118, 27948, 27776, 27601, 27423, 27242, 27058, 26872, 26684, 
26492, 26298, 26101, 25902, 25700, 25495, 25288, 25078, 24866, 24652, 
24435, 24215, 23993, 23769, 23542, 23313, 23081, 22848, 22612, 22373, 
22133, 21890, 21645, 21398, 21149, 20898, 20644, 20389, 20131, 19872, 
19610, 19347, 19081, 18814, 18545, 18274, 18001, 17726, 17450, 17171, 
16891, 16610, 16327, 16042, 15755, 15467, 15177, 14886, 14594, 14299, 
14004, 13707, 13409, 13109, 12808, 12506, 12202, 11898, 11592, 11285, 
10977, 10667, 10357, 10046, 9733, 9420, 9105, 8790, 8474, 8157, 
7839, 7521, 7202, 6882, 6561, 6240, 5918, 5595, 5272, 4948, 
4624, 4299, 3974, 3649, 3323, 2997, 2671, 2344, 2017, 1690, 
1362, 1035, 707, 380, 52, -275, -603, -931, -1258, -1586, 
-1913, -2240, -2567, -2893, -3219, -3545, -3871, -4196, -4521, -4845, 
-5169, -5492, -5815, -6137, -6459, -6780, -7100, -7419, -7738, -8056, 
-8373, -8690, -9005, -9320, -9633, -9946, -10258, -10569, -10878, -11187, 
-11494, -11800, -12105, -12409, -12712, -13013, -13313, -13612, -13910, -14206, 
-14500, -14793, -15085, -15375, -15664, -15951, -16236, -16520, -16802, -17082, 
-17361, -17638, -17913, -18187, -18459, -18728, -18996, -19262, -19526, -19789, 
-20049, -20307, -20563, -20817, -21069, -21319, -21567, -21812, -22056, -22297, 
-22536, -22773, -23007, -23239, -23469, -23697, -23922, -24145, -24365, -24583, 
-24798, -25011, -25222, -25429, -25635, -25838, -26038, -26235, -26430, -26623, 
-26812, -26999, -27184, -27365, -27544, -27720, -27894, -28064, -28232, -28397, 
-28559, -28718, -28874, -29028, -29178, -29326, -29471, -29613, -29751, -29887, 
-30020, -30150, -30277, -30400, -30521, -30639, -30753, -30865, -30974, -31079, 
-31181, -31280, -31376, -31469, -31559, -31645, -31729, -31809, -31886, -31960, 
-32031, -32098, -32162, -32223, -32281, -32336, -32387, -32435, -32480, -32522, 
-32560, -32595, -32627, -32656, -32681, -32703, -32722, -32738, -32750, -32759, 
-32764, -32767, -32766, -32762, -32755, -32744, -32730, -32713, -32692, -32668, 
-32641, -32611, -32577, -32541, -32501, -32457, -32411, -32361, -32308, -32252, 
-32192, -32129, -32063, -31994, -31922, -31846, -31768, -31686, -31601, -31512, 
-31421, -31327, -31229, -31128, -31024, -30917, -30807, -30694, -30578, -30459, 
-30336, -30211, -30082, -29951, -29817, -29679, -29539, -29396, -29249, -29100, 
-28948, -28793, -28635, -28475, -28311, -28145, -27976, -27804, -27629, -27451, 
-27271, -27088, -26902, -26714, -26523, -26329, -26133, -25934, -25732, -25528, 
-25321, -25112, -24900, -24686, -24469, -24250, -24029, -23805, -23578, -23349, 
-23118, -22885, -22649, -22412, -22171, -21929, -21684, -21438, -21189, -20938, 
-20685, -20430, -20172, -19913, -19652, -19389, -19124, -18857, -18588, -18317, 
-18044, -17770, -17494, -17216, -16936, -16655, -16372, -16087, -15801, -15513, 
-15224, -14933, -14640, -14346, -14051, -13754, -13456, -13157, -12856, -12554, 
-12251, -11946, -11641, -11334, -11026, -10717, -10406, -10095, -9783, -9470, 
-9156, -8841, -8525, -8208, -7890, -7572, -7253, -6933, -6612, -6291, 
-5969, -5646, -5323, -5000, -4676, -4351, -4026, -3701, -3375, -3049, 
-2723, -2396, -2069, -1742, -1415, -1087, -760, -432, -104, 
};


#define NUMSTARS 128

struct {
	int x, y, z;
	int oldx, oldy;
} Star[NUMSTARS];

int x,y,r,rs=0, tmprs=0;
HANDLE hOutput;

void Init()
{
	int idx;

	CONSOLE_SCREEN_BUFFER_INFO myInfo;
	DWORD tmp;
	COORD myCoord;

	for (idx=0; idx<NUMSTARS; idx++)
	{
		Star[idx].x=rand()%10000-5000;
		Star[idx].y=rand()%10000-5000;
		Star[idx].z=rand()%10000+1;
		Star[idx].oldx=Star[idx].x;
		Star[idx].oldy=Star[idx].y;
	}
	
	SetConsoleTitle("Funky Stars");
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &myInfo);
	myCoord.X=myInfo.srWindow.Left;
	myCoord.Y=myInfo.srWindow.Top;
	FillConsoleOutputCharacter(hOutput, ' ', (myInfo.srWindow.Right-myInfo.srWindow.Left)*(myInfo.srWindow.Bottom-myInfo.srWindow.Top), myCoord, &tmp);
}

void MoveStars()
{
	int idx;
	int sinr, cosr;
	int tmp;
	DWORD dwTmp;
	COORD myCoord;
	char ch;
    int cx, cy;
    static int oldcx=0;
    static int oldcy=0;

	/* Speed at which rotation changes */
	tmprs++;
	if (tmprs>1) {
		rs++;
		while (rs>628) rs-=628;
		tmprs=0;
	}

	/* actual amount to rotate this frame */
	r=SINE[rs]>>12;
	while (r<0) r+=628;
	while (r>628) r-=628;
	sinr=SINE[r];
    cosr=r+157;     /* cosine offset */
    while (cosr>628) cosr-=628;
    cosr=SINE[cosr];

    /* get center (maybe only every 'x' frames? seems fast enough though) */
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (GetConsoleScreenBufferInfo(hOutput, &info)) {
            COORD c;
            c.X=0; c.Y=0;
            SetConsoleCursorPosition(hOutput, c);
            cx = (info.srWindow.Right-info.srWindow.Left)/2;
            cy = (info.srWindow.Bottom-info.srWindow.Top)/2;
        }
    }

	for (idx=0; idx<NUMSTARS; idx++)
	{
		myCoord.X=(Star[idx].oldx>>4)+oldcx;
		myCoord.Y=(Star[idx].oldy>>4)+oldcy;
		FillConsoleOutputCharacter(hOutput, ' ', 1, myCoord, &dwTmp);
		
		// rotate star
	    Star[idx].x = (int)((Star[idx].x*cosr)-(Star[idx].y*sinr))>>15;
    	Star[idx].y = (int)((Star[idx].x*sinr)+(Star[idx].y*cosr))>>15;

		// move star
		Star[idx].z-=75;
		if (Star[idx].z < 1)
		{
			Star[idx].z+=10000;
			Star[idx].x=rand()%10000-5000;
			Star[idx].y=rand()%10000-5000;
		}

		tmp=(10000-Star[idx].z)/2000;
		Star[idx].oldx=Star[idx].x*1000/Star[idx].z;
		Star[idx].oldy=Star[idx].y*1000/Star[idx].z;

		myCoord.X=(Star[idx].oldx>>4)+cx;
		myCoord.Y=(Star[idx].oldy>>4)+cy;
		switch (tmp) {
		case 0: ch='.'; break;
		case 1: ch=','; break;
		case 2: ch='"'; break;
		case 3: ch='o'; break;
		default:ch='O'; break;
		}
		FillConsoleOutputCharacter(hOutput, ch, 1, myCoord, &dwTmp);
	}

    oldcx = cx;
    oldcy = cy;
}

void main() {
	Init();
	while (!_kbhit()) {
		MoveStars();
		Sleep(1);
	}
}