#pragma once
#include <string>
#include "Table.h"

/*
 *	Heightmap class based on Heightmap  class from
 *	"Introduction to 3D Game Programming with DirectX 9.0c: A Shader Approach"
 *	by Frank Luna.
 *
 *  Pages 291 - 293.
 */
class Heightmap
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		std::string mHeightMapFilename;
		Table<float> mHeightMap;
		float mHeightScale;
		float mHeightOffset;

	////////////////////////////////////
	// Constructor
	////////////////////////////////////
	public:
		Heightmap();
		Heightmap(int m, int n);
		Heightmap(int m, int n, const std::string& filename, float heightScale, float heightOffset);

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void recreate(int m, int n);
		void loadRAW(int m, int n, const std::string& filename, float heightScale, float heightOffset);
		int numRows() const;
		int numCols() const;
		// For non-const objects
		float& operator()(int i, int j);
		// For const objects
		const float& operator()(int i, int j)const;
	private:
		bool inBounds(int i, int j);
		float sampleHeight3x3(int i, int j);
		void filter3x3();
};

