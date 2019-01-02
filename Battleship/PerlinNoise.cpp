#include "PerlinNoise.h"



void PerlinNoise::SetupPerlinNoise(float **fSeed, float **fOutputn, int nOutputWidth, int nOutputHeight) {
	delete[] * fSeed;
	delete[] * fOutputn;
	*fSeed = new float[nOutputWidth * nOutputHeight];
	*fOutputn = new float[nOutputWidth * nOutputHeight];
	for (int i = 0; i < nOutputWidth * nOutputHeight; i++) (*fSeed)[i] = (float)rand() / (float)RAND_MAX;
}
void PerlinNoise::PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput)
{
	for (int x = 0; x < nWidth; x++)
		for (int y = 0; y < nHeight; y++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nWidth >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
				int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / fBias;
			}
			fOutput[y * nWidth + x] = fNoise / fScaleAcc;
		}

}