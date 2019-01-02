#pragma once
#include "stdlib.h"

class PerlinNoise
{
public:
	static void SetupPerlinNoise(float **fSeed, float **fOutputn, int nOutputWidth, int nOutputHeight);
	
	static void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput);



};

