/*	Code Created by James Michael Armstrong (NexusName:BlazesRus)
	Latest Code release available at http://www.nexusmods.com/skyrim/mods/44884/?
	*/
#pragma once
#ifndef VariableTypeLists_IncludeGuard
#define VariableTypeLists_IncludeGuard

#include "VariableList.h"
#include "StringVectorList.h"
#include <string>

class IntegerList : public VariableList < int >
{
public:
	//************************************
	// Method:    AddData
	// FullName:  IntegerList::AddData
	// Access:    public
	// Returns:   int
	// Qualifier:
	//************************************
	size_t AddData();
	//************************************
	// Method:    SaveDataToFile
	// FullName:  IntegerList::SaveDataToFile
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Parameter: std::string Path
	//************************************
	void SaveDataToFile(std::string Path);
	//************************************
	// Method:    AsStringList
	// FullName:  IntegerList::AsStringList
	// Access:    public
	// Returns:   StringVectorList
	// Qualifier:
	//************************************
	StringVectorList AsStringList();
	//************************************
	// Method:    AddEntry
	// FullName:  IntegerList::AddEntry
	// Access:    public
	// Returns:   void
	// Qualifier:
	//Adds new entry into list at index 0(Used mainly for InfiniteScopePosInt)
	//************************************
	void AddEntry();
	//************************************
	// Method:    EditLastEntry
	// FullName:  IntegerList::EditLastEntry
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Parameter: int TempValue
	// Edits last value in List(Used mainly for InfiniteScopePosInt)
	//************************************
	void EditLastEntry(int TempValue);
	void IncreaseLastEntry()
	{
		int LastIndex = this->Size() - 1;
		int TempValue = this->ElementAt(LastIndex);
		TempValue++;
		this->SetElementAt(LastIndex, TempValue);
	}
	//************************************
	// Generates String with format Index:0_Index:1...Index:5
	// Method:    GenerateAsString
	// FullName:  IntegerList::GenerateAsString
	// Access:    public
	// Returns:   string
	// Qualifier:
	//************************************
	std::string GenerateAsString();
	void ConvertStringToVectorList(std::string Content);
};

class XIntegerList : public VariableList < long long int >
{
public:
	//************************************
	// Method:    AddData
	// FullName:  IntegerList::AddData
	// Access:    public
	// Returns:   int
	// Qualifier:
	//************************************
	size_t AddData();
	//************************************
	// Method:    SaveDataToFile
	// FullName:  IntegerList::SaveDataToFile
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Parameter: std::string Path
	//************************************
	void SaveDataToFile(std::string Path);
	//************************************
	// Method:    AsStringList
	// FullName:  IntegerList::AsStringList
	// Access:    public
	// Returns:   StringVectorList
	// Qualifier:
	//************************************
	StringVectorList AsStringList();
	//************************************
	// Method:    AddEntry
	// FullName:  IntegerList::AddEntry
	// Access:    public
	// Returns:   void
	// Qualifier:
	//Adds new entry into list at index 0(Used mainly for InfiniteScopePosInt)
	//************************************
	void AddEntry();
	//************************************
	// Method:    EditLastEntry
	// FullName:  IntegerList::EditLastEntry
	// Access:    public
	// Returns:   void
	// Qualifier:
	// Parameter: int TempValue
	// Edits last value in List(Used mainly for InfiniteScopePosInt)
	//************************************
	void EditLastEntry(long long int TempValue);
	void IncreaseLastEntry()
	{
		size_t LastIndex = this->Size() - 1;
		long long int TempValue = this->ElementAt(LastIndex);
		TempValue++;
		this->SetElementAt(LastIndex, TempValue);
	}
	//************************************
	// Generates String with format Index:0_Index:1...Index:5
	// Method:    GenerateAsString
	// FullName:  IntegerList::GenerateAsString
	// Access:    public
	// Returns:   string
	// Qualifier:
	//************************************
	std::string GenerateAsString();
	void ConvertStringToVectorList(std::string Content);
};

class DoubleList : public VariableList < double >
{
public:
	size_t AddData();
	void SaveDataToFile(std::string Path);
	StringVectorList AsStringList();
	void ConvertStringToVectorList(std::string Content);
};

class BoolList : public VariableList < bool >
{
public:
	size_t AddData();
	void SaveDataToFile(std::string Path);
	StringVectorList AsStringList();
	void ConvertStringToVectorList(std::string Content);
};
#endif