//Code Created by James Michael Armstrong(Skyrim nexus name:BlazesRus)
#pragma once
#ifndef IniData_IncludeGuard
#define IniData_IncludeGuard
#include "VariableList.h"
#include "StringVectorList.h"

class IniDataElement
{
public:
	bool IsIniCategory = false;
	std::string ScriptArg01;
	std::string ScriptArg02;
	IniDataElement();
	~IniDataElement();
};

class IniData : public VariableList <IniDataElement>
{
public:
	unsigned __int8 IniType = 0;
	//************************************
	// Method:    LoadIniData
	// FullName:  IniData::LoadIniData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string FileName
	//************************************
	void LoadIniData(std::string FileName);
	bool CheckIfElementExists(std::string Value)
	{
		const unsigned int ListSize = Size();
		IniDataElement ElementData;
		bool ElementExists = false;
		for(size_t Index=0;Index<ListSize&&ElementExists==false;++Index)
		{
			ElementData = ElementAt(Index);
			if(ElementData.ScriptArg01==Value)
			{
				ElementExists = true;
			}
		}
		return ElementExists;
	}
	std::string GetElementData(std::string Value)
	{
		const size_t ListSize = Size();
		std::string ElementValue="";
		IniDataElement ElementData;
		bool ElementExists = false;
		for(size_t Index=0; Index < ListSize && ElementExists == false; ++Index)
		{
			ElementData = ElementAt(Index);
			if(ElementData.ScriptArg01 == Value)
			{
				ElementExists = true;
				ElementValue = ElementData.ScriptArg02;
			}
		}
		if(ElementExists == false)
		{
			std::cout << "Ini setting named "<<Value<<"not found.\n";
		}
		return ElementValue;
	}
	IniData();
	~IniData();
};
#endif