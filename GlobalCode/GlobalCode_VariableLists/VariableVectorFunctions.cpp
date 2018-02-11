/*	Code Created by James Michael Armstrong (NexusName:BlazesRus)
	Latest Code Release at https://github.com/BlazesRus/NifLibEnvironment
*/

#include "VariableVectorFunctions.h"
#include <string>
#include "StringFunctions.h"

//Inside this ifdef block holds GlobalCode Environment library version of header structure (preprocessor defined inside all GlobalCode library configs)
#ifdef BLAZESGLOBALCODE_LIBRARY
#include "..\GlobalCode_VariableConversionFunctions\VariableConversionFunctions.h"
//Local Version of headers here(within else block)
#else
#include "VariableConversionFunctions.h"
//Dummy define of DLL_API to prevent requiring 2 separate Defines of initial class headers(without needing the DLL_API define)
#ifndef DLL_API
#define DLL_API
#endif
#endif

using std::string;

StringVectorList VariableVectorFunctions::ReadStringParamFromStringList(StringVectorList TempStringList)
{
	string TempString = "";
	StringVectorList ParamList;
	size_t StringLength;
	char StringChar;
	string LineString;
	for(size_t ListLine = 0; TempStringList.StreamLineData(); ++ListLine)
	{
		LineString = TempStringList.CurrentStreamedLineString();
		StringLength = LineString.length();
		for(int i = 0; i < StringLength; i++)
		{
			StringChar = LineString.at(i);
			if(StringChar == ' ' || StringChar == '	'&&TempString != "")
			{
				ParamList.Add(TempString);
				TempString = "";
			}
			else
			{
				TempString += StringChar;
			}
		}
	}
	if(TempString != "")
	{
		ParamList.Add(TempString);
	}
	return ParamList;
}

IntegerList VariableVectorFunctions::ReadIntParamFromStringList(StringVectorList TempStringList)
{
	string TempString = "";
	IntegerList ParamList;
	size_t StringLength;
	char StringChar;
	string LineString;
	for(size_t ListLine = 0; TempStringList.StreamLineData(); ++ListLine)
	{
		LineString = TempStringList.CurrentStreamedLineString();
		StringLength = LineString.length();
		for(int i = 0; i < StringLength; i++)
		{
			StringChar = LineString.at(i);
			if(StringChar == ' ' || StringChar == '	'&&TempString != "")
			{
				ParamList.Add(VariableConversionFunctions::ReadIntFromString(TempString));
				TempString = "";
			}
			else
			{
				TempString += StringChar;
			}
		}
	}
	if(TempString != "")
	{
		ParamList.Add(VariableConversionFunctions::ReadIntFromString(TempString));
	}
	return ParamList;
}

DoubleList VariableVectorFunctions::ReadDoubleParamFromStringList(StringVectorList TempStringList)
{
	string TempString = "";
	DoubleList ParamList;
	size_t StringLength;
	char StringChar;
	string LineString;
	for(size_t ListLine = 0; TempStringList.StreamLineData(); ++ListLine)
	{
		LineString = TempStringList.CurrentStreamedLineString();
		StringLength = LineString.length();
		for(int i = 0; i < StringLength; i++)
		{
			StringChar = LineString.at(i);
			if(StringChar == ' ' || StringChar == '	')
			{
				ParamList.Add(VariableConversionFunctions::ReadDoubleFromString(TempString));
				TempString = "";
			}
			else
			{
				TempString += StringChar;
			}
		}
	}
	if(TempString != "")
	{
		ParamList.Add(VariableConversionFunctions::ReadDoubleFromString(TempString));
	}
	return ParamList;
}

//
/** Retrieve StringList from LineString
* @param LineString
* @return
*/
StringVectorList VariableVectorFunctions::ParamInfoFromString(string LineString)
{
	string TempString = "";
	StringVectorList ParamList;
	size_t StringLength = LineString.length();
	char StringChar;
	for(int i = 0; i < StringLength; i++)
	{
		StringChar = LineString.at(i);
		if(StringChar == ',')
		{
			ParamList.Add(TempString);
			TempString = "";
		}
		else
		{
			TempString += StringChar;
		}
	}
	if(TempString != "")
	{
		ParamList.Add(TempString);
	}
	return ParamList;
}

/** Convert Variable Index from one StringList to Another StringList
* @param Index
* @param CurrentVarList
* @param NewVarList
* @return integer of new VariableIndex
*/
size_t VariableVectorFunctions::ConvertVariableIndex(size_t Index, StringVectorList CurrentVarList, StringVectorList NewVarList)
{
	string TempString = CurrentVarList.elementAt(Index);
	return NewVarList.GetElementIndex(TempString);
}

/** Converts Entries in StringList to Rows of 16-entry Strings
* (Use to convert StringList for BoneEntries back to Lines of Strings)
* @param TempStringList
* @return
*/
StringVectorList VariableVectorFunctions::ConvertStringEntriesToStringRows(StringVectorList TempStringList)
{
	//16 Entries a row(Bone-indexes)
	StringVectorList StringRows;
	string CurrentRowString = "";
	int ColumnNum = 0;
	for(int i = 0; i < TempStringList.length(); i++)
	{
		if(ColumnNum == 0)
		{
			CurrentRowString = TempStringList.elementAt(i);
		}
		else
		{
			CurrentRowString += " " + TempStringList.elementAt(i);
		}
		ColumnNum++;
		if(ColumnNum >= 16)
		{
			StringRows.Add(CurrentRowString);
			ColumnNum = 0;
		}
	}
	if(ColumnNum != 0)
	{
		StringRows.Add(CurrentRowString);
	}
	return StringRows;
}

StringVectorList VariableVectorFunctions::IniInfoFromString(string LineString)
{
	string TempString = "";
	StringVectorList ParamList;
	size_t StringLength = LineString.length();
	string StringChar;
	bool IgnoreWhitespace = true;
	for(size_t i = 0; i < StringLength; ++i)
	{
		StringChar = "" + LineString.at(i);
		if(StringChar == "=")
		{
			ParamList.Add(TempString);
			TempString = "";
		}
		else if(StringChar == "\\\"")
		{
			IgnoreWhitespace = !IgnoreWhitespace;
		}
		else if(IgnoreWhitespace && StringChar == "[^\\\\d]") {}
		else
		{
			TempString += StringChar;
		}
	}
	if("" != TempString)
	{
		ParamList.Add(TempString);
	}
	return ParamList;
}

StringVectorList VariableVectorFunctions::ParamInfoFromStringList(StringVectorList TempStringList)
{
	string TempString = "";
	StringVectorList ParamList;
	size_t StringLength;
	char StringChar;
	string LineString;
	for(size_t ListLine = 0; TempStringList.StreamLineData(); ++ListLine)
	{
		LineString = TempStringList.CurrentStreamedLineString();
		StringLength = LineString.length();
		for(size_t i = 0; i < StringLength; i++)
		{
			StringChar = LineString.at(i);
			if(StringChar == ',')
			{
				ParamList.Add(TempString);
				TempString = "";
			}
			else
			{
				TempString += StringChar;
			}
		}
	}
	if(TempString != "")
	{
		ParamList.Add(TempString);
	}
	return ParamList;
}

/** Find Number of Parameters in LineString
* @param LineString
* @return
*/
size_t VariableVectorFunctions::GetNumberOfParamsFromString(string LineString)
{
	StringVectorList ParamList = ParamInfoFromString(LineString);
	return ParamList.length();
}

VariableVectorFunctions::VariableVectorFunctions()
{}

VariableVectorFunctions::~VariableVectorFunctions()
{}