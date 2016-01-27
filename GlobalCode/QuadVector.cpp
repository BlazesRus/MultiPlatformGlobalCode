/*	Code Created by James Michael Armstrong (NexusName:BlazesRus)
	Latest Code Release at https://github.com/BlazesRus/NifLibEnvironment
*/
#include "QuadVector.h"
#include "StringFunctions.h"
#include "MiscFunctions.h"

void QuadVector::StoreInVectorIndex(int index, double TempValue)
{
	if(index == 0) { PositionX = TempValue; }
	else if(index == 1) { PositionY = TempValue; }
	else if(index == 2) { PositionZ = TempValue; }
	else if(index == 3) { PositionW = TempValue; }
}

double QuadVector::GetVectorValue(int index)
{
	if(index == 0) { return PositionX; }
	else if(index == 1) { return PositionY; }
	else if(index == 2) { return PositionZ; }
	else if(index == 3) { return PositionW; }
	else { return 0.0;/*Error Value but return 0.0 to prevent crash*/ }
}

//converts variables back into string format that havok uses in files(0.000000 0.000000 0.000000 0.000000)
std::string QuadVector::ConvertToString()
{
	std::string TempString = "(";
	TempString += std::to_string(PositionX);
	TempString += " ";
	TempString += std::to_string(PositionY);
	TempString += " ";
	TempString += std::to_string(PositionZ);
	TempString += " ";
	TempString += std::to_string(PositionW);
	TempString += ")";
	TempString += StringFunctions::DoubleToStringConversion(1.1);
	return TempString;
}

DoubleList QuadVector::ConvertToDoubleList()
{
	DoubleList TempValue;
	for(int i = 0; i < 4; i++)
	{
		TempValue.Add(GetVectorValue(i));
	}
	return TempValue;
}

void QuadVector::ReadQuadVectorFromString(std::string LineString)
{
	//Current character loaded in steam
	char StringChar;
	//Current Characters worth of string found of Double Value
	std::string PartialSearchBuffer = "";
	//Temporary Storage of converted double value
	double DoubleStorageTemp;
	//Vector index of value to store
	unsigned __int8 VectorIndex = 0;
	//Scanning Double value check for index
	bool ScanningDouble = false;
	//Total size of LineString to load
	size_t StringSize = LineString.size();
	for(size_t i = 0; i < StringSize&&VectorIndex < 4; ++i)
	{
		StringChar = LineString.at(i);
		if(StringChar == ' ' || StringChar == '	'&&PartialSearchBuffer != "")
		{
			if(ScanningDouble)
			{
				DoubleStorageTemp = StringFunctions::ReadDoubleFromString(PartialSearchBuffer);
				StoreInVectorIndex(VectorIndex, DoubleStorageTemp);
				PartialSearchBuffer = "";
				VectorIndex++;
			}
		}
		else if(StringChar == '.' || StringChar == '0' || StringChar == '1' || StringChar == '2' || StringChar == '3' || StringChar == '4' || StringChar == '5' || StringChar == '6' || StringChar == '7' || StringChar == '8' || StringChar == '9' || StringChar == '-')
		{
			PartialSearchBuffer += StringChar;
			if(ScanningDouble == false) { ScanningDouble = true; }
		}
	}
}

QuadVector::QuadVector(std::string TempString)
{
	size_t StringLength;
	StringLength = TempString.length();
	std::string ValueExtractionBuffer = "";
	//Temporary Storage of converted double value
	double DoubleStorageTemp;
	//Current character loaded in steam
	std::string StringChar;
	//Vector index of value to store
	unsigned __int8 VectorIndex = 0;
	for(unsigned __int8 i = 0; i < StringLength&&VectorIndex < 4; i++)
	{
		StringChar = TempString.at(i);
		if(StringChar == " " || StringChar == "\t" || StringChar == ")")
		{
			if(ValueExtractionBuffer != "")
			{
				//std::cout << "ValueStored:" << ValueExtractionBuffer << " VectorIndex:" << VectorIndex << "\n";
				DoubleStorageTemp = StringFunctions::ReadDoubleFromString(ValueExtractionBuffer);
				StoreInVectorIndex(VectorIndex, DoubleStorageTemp);
				ValueExtractionBuffer = "";
				VectorIndex++;
			}
		}
		else if(StringChar == "." || StringFunctions::IsDigit(StringChar) || StringChar == "-")
		{
			ValueExtractionBuffer += StringChar;
		}
	}
}

QuadVector::QuadVector()
{}

QuadVector::~QuadVector()
{}

size_t QuadVectorList::AddData()
{
	size_t Index = Size();
	QuadVector TempValue = QuadVector("(0.0 0.0 0.0 0.0)");
	Add(TempValue);
	return Index;
}

void QuadVectorList::ConvertStringToVectorList(std::string Content)
{
	if(Size() != 0)
	{
		Reset();
	}
	const size_t StringSize = Content.length();
	char CurrentChar;
	std::string CurrentElement = "";
	QuadVector CurrentElementVector;
	for(size_t Index=0; Index < StringSize; ++Index)
	{
		CurrentChar = Content.at(Index);
		if(CurrentElement == "")
		{
			if(CurrentChar != '\n'&&CurrentChar != ' '&&CurrentChar != '\t'&&CurrentChar != '	')
			{
				CurrentElement = CurrentChar;
			}
		}
		else
		{
			if(CurrentChar != '\n'&&CurrentChar != ' '&&CurrentChar != '\t'&&CurrentChar != '	')
			{
				CurrentElement += CurrentChar;
			}
			else
			{
				CurrentElementVector.ReadQuadVectorFromString(CurrentElement);
				AddElement(CurrentElementVector);
				CurrentElement = "";
			}
		}
	}
}
