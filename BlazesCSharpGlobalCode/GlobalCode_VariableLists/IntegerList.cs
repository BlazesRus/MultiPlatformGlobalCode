﻿using CSharpGlobalCode.GlobalCode_VariableConversionFunctions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpGlobalCode.GlobalCode_VariableLists
{
    public class IntegerList : List<int>
    {
        //************************************
        // Method:    AddData
        // FullName:  IntegerList::AddData
        // Access:    public
        // Returns:   int
        // Qualifier:
        //************************************
        public int AddData()
        {
            int Index = Count;
            Add(0);
            return Index;
        }

        ////************************************
        //// Method:    SaveDataToFile
        //// FullName:  IntegerList::SaveDataToFile
        //// Access:    public
        //// Returns:   void
        //// Qualifier:
        //// Parameter: std::string Path
        ////************************************
        //public void SaveDataToFile(string Path)
        //{
        //	string LineString;
        //	fstream CraftedIniFile;
        //	CraftedIniFile.open(Path, ios::out | ios::trunc);
        //	int DataSize = Count;
        //	if (CraftedIniFile.is_open())
        //	{
        //		for (int i = 0; i < DataSize; ++i)
        //		{
        //			if (i != 0)
        //			{//Carriage Return to next line
        //				CraftedIniFile << "\r\n";
        //			}
        //			LineString = VariableConversionFunctions::XIntToStringConversion(ElementAt(i));
        //			CraftedIniFile << LineString;
        //		}
        //		CraftedIniFile.close();
        //	}
        //	else
        //	{
        //		cout << "Failed to open" << Path << "\n";
        //	}
        //}

        //************************************
        // Method:    AsStringList
        // FullName:  IntegerList::AsStringList
        // Access:    public
        // Returns:   StringList
        // Qualifier:
        //************************************
        public StringList AsStringList()
        {
            StringList TempStringList = new StringList();
            string TempString;
            int TempInt = Count;
            for (int i = 0; i < TempInt; ++i)
            {
                TempString = VariableConversionFunctions.IntToStringConversion(this[i]);
                TempStringList.Add(TempString);
            }
            return TempStringList;
        }

        //************************************
        // Method:    AddEntry
        // FullName:  IntegerList::AddEntry
        // Access:    public
        // Returns:   void
        // Qualifier:
        //Adds new entry into list at index 0(Used mainly for InfiniteScopePosInt)
        //************************************
        public void AddEntry()
        {
            this.Add(0);
        }

        //************************************
        // Method:    EditLastEntry
        // FullName:  IntegerList::EditLastEntry
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: int TempValue
        // Edits last value in List(Used mainly for InfiniteScopePosInt)
        //************************************
        public void EditLastEntry(int TempValue)
        {
            int LastIndex = Count - 1;
            this[LastIndex] = TempValue;
        }

        public void IncreaseLastEntry()
        {
            int LastIndex = this.Count - 1;
            int TempValue = this[LastIndex];
            TempValue++;
            this[LastIndex] = TempValue;
        }

        //************************************
        // Generates String with format Index:0_Index:1...Index:5
        // Method:    GenerateAsString
        // FullName:  IntegerList::GenerateAsString
        // Access:    public
        // Returns:   string
        // Qualifier:
        //************************************
        public string GenerateAsString()
        {
            string ListString = "";
            int TempValue;
            int TempSize = this.Count;
            for (int i = 0; i < TempSize; ++i)
            {
                TempValue = this[i];
                if (i == 0)
                {
                    ListString = VariableConversionFunctions.IntToStringConversion(TempValue);
                }
                else
                {
                    ListString += "_";
                    ListString += VariableConversionFunctions.IntToStringConversion(TempValue);
                }
            }
            return ListString;
        }

        public void ConvertStringToList(string Content)
        {
            if (Count != 0)
            {
                Clear();
            }
            int StringSize = Content.Length;
            char CurrentChar;
            var CurrentElement = new StringBuilder();
            string CurrentAsString;
            for (int Index = 0; Index < StringSize; ++Index)
            {
                CurrentChar = Content[Index];
                CurrentAsString = CurrentElement.ToString();
                if (CurrentAsString == "")
                {
                    if (CurrentChar != '\n' && CurrentChar != ' ' && CurrentChar != '\t' && CurrentChar != '	')
                    {
                        CurrentElement.Append(CurrentChar);
                    }
                }
                else
                {
                    if (CurrentChar != '\n' && CurrentChar != ' ' && CurrentChar != '\t' && CurrentChar != '	')
                    {
                        CurrentElement.Append(CurrentChar);
                    }
                    else
                    {
                        Add(VariableConversionFunctions.ReadIntFromString(CurrentAsString));
                        CurrentElement.Clear();
                    }
                }
            }
        }

        public IntegerList(string Value)
        {
            ConvertStringToList(Value);
        }

        public static explicit operator IntegerList(string Value)
        {
            return new IntegerList(Value);
        }

		public IntegerList(){}
    }
}
