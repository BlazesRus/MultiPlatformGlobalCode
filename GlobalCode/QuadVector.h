#pragma once
#ifndef QuadVector_IncludeGuard
#define QuadVector_IncludeGuard

#include <string>
#include "VariableTypeLists.h"
#include "VariableList.h"

using std::string;

class QuadVector
{
public:
	double PositionX = 0.0;
	double PositionY = 0.0;
	double PositionZ = 0.0;
	double PositionW = 0.0;
	//Store values in Position in vector
	void StoreInVectorIndex(int index, double TempValue);
	//Get value based on index value
	double GetVectorValue(int index);
	//Reconstruct as string
	string ConvertToString();
	//Reconstruct as DoubleList vector
	DoubleList ConvertToDoubleList();
	//Construct QuadVector from String
	void ReadQuadVectorFromString(std::string LineString);
	QuadVector(string TempString);
	QuadVector();
	~QuadVector();
};

class QuadVectorList : public VariableList < QuadVector >
{
	//************************************
	// Alias for Add(Fix compiler error of thinking Add(TempValue) has TempValue as double)
	// Method:    AddElement
	// FullName:  QuadVectorList::AddElement
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: QuadVector TempValue
	//************************************
	void AddElement(QuadVector TempValue)
	{
		Add(TempValue);
	}
	size_t AddData();
	void ConvertStringToVectorList(std::string Content);
};
#endif