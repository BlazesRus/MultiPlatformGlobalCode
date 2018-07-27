/*	Code Created by James Michael Armstrong (NexusName:BlazesRus)(https://github.com/BlazesRus)
	Latest Code Release at https://github.com/BlazesRus/MultiPlatformGlobalCode
*/
#ifdef BlazesGlobalCode_UsePreprocessor
#ifdef BlazesGlobalCode_LocalLayout
	#include "stdafx.h"
#else
	#include "..\stdafx.h"
#endif
#endif

#pragma once
#ifndef QuadVector_IncludeGuard
#define QuadVector_IncludeGuard

#include <string>

#ifdef BLAZESGLOBALCODE_LIBRARY
	#include "..\DLLAPI.h"
#else
//Dummy define of DLL_API to prevent requiring 2 separate Defines of initial class headers(without needing the DLL_API define)
	#ifndef DLL_API
		#define DLL_API
	#endif
#endif

#ifdef BlazesGlobalCode_LocalLayout//(Local version style layout)
#include "..\GlobalCode_VariableLists\StringVectorList.h"
#include "..\GlobalCode_VariableLists\VariableList.h"
#else
#include "StringVectorList.h"
#include "VariableList.h"
#endif

class DLL_API QuadVector
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
	std::string ConvertToString();
	//Reconstruct as DoubleList vector
	DoubleList ConvertToDoubleList();
	//Construct QuadVector from String
	void ReadQuadVectorFromString(std::string LineString);
	QuadVector(std::string TempString);
	QuadVector();
	~QuadVector();
};

class DLL_API QuadVectorList : public VariableList < QuadVector >
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
