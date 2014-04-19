/*
*	Heightmap class based on Heightmap  class from
*	"Introduction to 3D Game Programming with DirectX 9.0c: A Shader Approach"
*	by Frank Luna.
*
*  Pages 291 - 293.
*/
#include <fstream>
#include <vector>
#include "Heightmap.h"

////////////////////////////////////
// Constructor
////////////////////////////////////
Heightmap::Heightmap()
{
}

Heightmap::Heightmap(int m, int n)
{
	recreate(m, n);
}

Heightmap::Heightmap(int m, int n, const std::string& filename, float heightScale, float heightOffset)
{
	loadRAW(m, n, filename, heightScale, heightOffset);
}

////////////////////////////////////
// Methods
////////////////////////////////////
void Heightmap::recreate(int m, int n)
{
	mHeightScale = 1.0f;
	mHeightOffset = 0.0f;
	mHeightMap.resize(m, n, 0.0f);
}

void Heightmap::loadRAW(int m, int n, const std::string& filename, float heightScale, float heightOffset)
{
	mHeightMapFilename = filename;
	mHeightScale = heightScale;
	mHeightOffset = heightOffset;

	// A height for each vertex
	std::vector<unsigned char> in(m * n);

	// Open the file.
	std::ifstream inFile;
	inFile.open(filename.c_str(), std::ios_base::binary);
	if (!inFile) return;

	// Read the RAW bytes.
	inFile.read((char*)&in[0], (std::streamsize)in.size());

	// Done with file.
	inFile.close();

	// Copy the array data into a float table format and scale
	// the heights.
	mHeightMap.resize(m, n, 0);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int k = i * n + j;
			mHeightMap(i, j) = (float)in[k] * heightScale + heightOffset;
		}
	}

	filter3x3();
}

void Heightmap::filter3x3()
{
	Table<float> temp(mHeightMap.numRows(), mHeightMap.numCols());

	for (int i = 0; i < mHeightMap.numRows(); ++i)
	for (int j = 0; j < mHeightMap.numCols(); ++j)
		temp(i, j) = sampleHeight3x3(i, j);

	mHeightMap = temp;
}

int Heightmap::numRows()const
{
	return mHeightMap.numRows();
}

int Heightmap::numCols()const
{
	return mHeightMap.numCols();
}

float& Heightmap::operator()(int i, int j)
{
	return mHeightMap(i, j);
}

bool Heightmap::inBounds(int i, int j)
{
	return
		i >= 0 &&
		i < (int)mHeightMap.numRows() &&
		j >= 0 &&
		j < (int)mHeightMap.numCols();
}

float Heightmap::sampleHeight3x3(int i, int j)
{
	float avg = 0.0f;
	float num = 0.0f;

	for (int m = i - 1; m <= i + 1; ++m)
	{
		for (int n = j - 1; n <= j + 1; ++n)
		{
			if (inBounds(m, n))
			{
				avg += mHeightMap(m, n);
				num += 1.0f;
			}
		}
	}

	return avg / num;
}