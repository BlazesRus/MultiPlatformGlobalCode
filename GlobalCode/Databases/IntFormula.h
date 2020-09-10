// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// ***********************************************************************
#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "..\VariableConversionFunctions\VariableConversionFunctions.h"

#ifdef BlazesGlobalCode_LocalLayout
#ifndef DLL_API
#ifdef UsingBlazesGlobalCodeDLL
#define DLL_API __declspec(dllimport)
#elif defined(BLAZESGLOBALCODE_LIBRARY)
#define DLL_API __declspec(dllexport)
#else
#define DLL_API
#endif
#endif
#else
#include "..\DLLAPI.h"
#endif

#include "..\tsl\ordered_map.h"
#ifdef IntFormula_UseMathLib
#include <cmath>
#else
//#include "boost/rational.hpp"
#endif

//Preprocessor Switches
/*
IntFormula_UseMathLib = Use <cmath> functions instead of alternative functions 
IntFormula_UseFloatingOperations = Use long double instead of MediumDec for non-integer operations
*/
//Supported Operators/Functions
/*
^ = Power of; * = Multiplication; / = Division; % = Modulus
+ = Addition; - = Subtraction; ! = Not;
&& = And; || = Or;
$ = XOR (bitwise exclusive Or)
&, |
*/
//Unsupported Operators/Functions(for later)
/*
++Prefix; --Prefix; ++Postfix; --Postfix (will detect and partially store but won't perform operation in evaluation at moment)
? = TernaryOperator(Not stored/evaluated yet)
Assignment operators not supported
Sqrt = Square Root of (applied to right value)
Root = Nth Root of (left value is equal to N; applied to right value)
*/

class DLL_API IntFormElement
{
public:
    /// <summary>
    /// The element type (Other values refer to variable names)
    /// @ = Formula Val; # = int Value; ? = TernaryOperator(Not Supported Yet)
    //	++Prefix; --Prefix; ++Postfix; ++Postfix
    /// true/false for boolean values
    /// </summary>
    std::string ElementType;
    /// <summary>
    /// (Primarily used for FormElements, ++,--, and TernaryOperator)
    /// The index/Key position of stored element (not used for variable names or booleans)(Might not even be needed for most values since matches key)
    //   For variable names: If not -1, refers to stored related Value Key(which is used for prefix/postfix ops as well)
    //   For Increment/Decrement Op: Refers to index of related value
    /// </summary>
    int Index;

    /// <summary>
    /// Initializes a new instance of the <see cref="IntFormElement"/> class. (Defaults as boolean with true value)
    /// </summary>
    IntFormElement()
    {
        ElementType = "true";
        Index = -1;
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="IntFormElement"/> class.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <param name="index">The index.</param>
    IntFormElement(std::string Value, int index = 0)
    {
        ElementType = Value;
        Index = index;
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="IntFormElement"/> class for PostFix OpValue.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <param name="opBuffer">The operator value.</param>
    IntFormElement(std::string Value, std::string opBuffer)
    {
        if (opBuffer == "++") { ElementType = "++Postfix"; }
        else { ElementType = "--Postfix"; }
        Index = -1;
        //Create new variable storage and set index to it if variable storage matching key doesn't exist
    }
};

/// <summary>
/// int Formula Data (Variant of OrderedIndexDictionary)
/// Implements the <see cref="tsl::ordered_map{int, IntFormElement}" />
/// </summary>
/// <seealso cref="tsl::ordered_map{int, IntFormElement}" />
class DLL_API IntFormData : public tsl::ordered_map<int, IntFormElement>
{
private:
    using IntVector = std::vector<int>;
public:
    ///// <summary>
    ///// Vector referring to keys in formula
    ///// </summary>
    //std::vector<int> FormData;
    int LastAdded = -1;

    /// <summary>
    /// Map of operation Index Values by with key storing precedence category (of those used for formula code) starting from zero
    /// </summary>
    std::vector<IntVector> OpOrderMap;

    std::unordered_map<int, int> NumMap;

    std::unordered_map<int, std::string> VariableMap;
    std::unordered_map<std::string, int> VariableStorageMap;
private:
    /// <summary>
    /// The next index
    /// </summary>
    int NextIndex = 0;
    std::vector<int> RemovedIndexes;
    unsigned int Add(int Key, IntFormElement Value)
    {
        this->insert_or_assign(Key, Value);
        return Key;
    }
protected:
    /// <summary>
    /// Adds the specified value into next free Index position(Returns index of new value)
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>unsigned int</returns>
    int Add(IntFormElement Value)
    {
        int IndexPos;
        if (RemovedIndexes.empty())//Adds new Indexes in order
        {
            IndexPos = NextIndex;
            Add(NextIndex, Value);
            NextIndex++; return IndexPos;
        }
        else//Otherwise adds based on last removed key
        {
            int TargetIndex = RemovedIndexes.back();
            Add(TargetIndex, Value);
            RemovedIndexes.pop_back();
            return TargetIndex;
        }
    }

    /// <summary>
    /// Removes the specified key.
    /// </summary>
    /// <param name="Key">The key.</param>
    void Remove(int Key)
    {
        this->erase(Key);
        RemovedIndexes.push_back(Key);
    }
public:
    /// <summary>
    /// Replaces the non-number based form value.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void ReplaceFormVal(int Key, bool Value)
    {
        IntFormElement& KeyedVal = this->at(Key);
        if (Value) { KeyedVal.ElementType = "true"; }
        else { KeyedVal.ElementType = "false"; }
    }

    /// <summary>
    /// Replaces the non-number based form value (and add to number map).
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void ReplaceFormVal(int Key, int Value)
    {
        IntFormElement& KeyedVal = this->at(Key);
        KeyedVal.ElementType = "#";
        NumMap.insert_or_assign(Key, Value);
    }

    void SwitchOpToVal(IntFormElement& OpVal, IntFormData::iterator& LeftIterator, IntFormData::iterator& RightIterator, bool Value)
    {
        if (Value) { OpVal.ElementType = "true"; }
        else { OpVal.ElementType = "false"; }

        if (LeftIterator->second.ElementType == "#") { NumMap.erase(LeftIterator->first); }
        if (LeftIterator->second.ElementType == "#") { NumMap.erase(RightIterator->first); }

        int LeftKey = LeftIterator->first; int RightKey = RightIterator->first;
        this->erase(LeftIterator); this->erase(RightKey);
        RemovedIndexes.push_back(LeftKey); RemovedIndexes.push_back(RightKey);
    }

    void SwitchOpToVal(IntFormElement& OpVal, int OpKey, IntFormData::iterator& RightIterator, int Value)
    {
        NumMap.insert_or_assign(OpKey, Value);
        OpVal.ElementType = "#";

        if (RightIterator->second.ElementType == "#") { NumMap.erase(RightIterator->first); }

        int RightKey = RightIterator->first;
        this->erase(RightKey);
        RemovedIndexes.push_back(RightKey);
    }

    void SwitchOpToVal(IntFormElement& OpVal, int OpKey, IntFormData::iterator& LeftIterator, IntFormData::iterator& RightIterator, int Value)
    {
        NumMap.insert_or_assign(OpKey, Value);
        OpVal.ElementType = "#";

        if (LeftIterator->second.ElementType == "#") { NumMap.erase(LeftIterator->first); }
        if (RightIterator->second.ElementType == "#") { NumMap.erase(RightIterator->first); }

        int LeftKey = LeftIterator->first; int RightKey = RightIterator->first;
        this->erase(LeftIterator); this->erase(RightKey);
        RemovedIndexes.push_back(LeftKey); RemovedIndexes.push_back(RightKey);
    }

    /// <summary>
    /// Clears this instance.
    /// </summary>
    void clear()
    {
        NextIndex = 0;//Free up all index slots usage as well
        RemovedIndexes.clear();
    }

    void AddBool(bool Value)
    {
        if (Value)
            LastAdded = Add(IntFormElement("true"));
        else
            LastAdded = Add(IntFormElement("false"));
    }

    /// <summary>
    /// Adds the specified value.
    /// </summary>
    /// <param name="Value">The value.</param>
    void AddNum(std::string Value)
    {
        LastAdded = Add(IntFormElement("#"));
        NumMap.insert_or_assign(LastAdded, Value);
    }

    /// <summary>
    /// Adds the specified value.
    /// </summary>
    /// <param name="Value">The value.</param>
    void AddVariable(std::string Value)
    {
        LastAdded = Add(IntFormElement(Value));
        VariableMap.insert_or_assign(LastAdded, Value);
    }

    /// <summary>
    /// Adds the specified value.
    /// </summary>
    /// <param name="Value">The value.</param>
    void Add(std::string Value)
    {
        LastAdded = Add(IntFormElement(Value));
    }

    /// <summary>
    /// Adds the specified operator value.
    /// </summary>
    /// <param name="Value">The value.</param>
    void AddOp(std::string Value)
    {
        LastAdded = Add(IntFormElement(Value));
        if (Value == "^") { OpOrderMap[0].push_back(LastAdded); }//"++PostFix"||Value=="--PostFix")//(Group 2 precedence, left to right associativity)
        else if (Value == "!")//++Prefix, --Prefix as well(Group 3 precedence, right to left associativity)
        {
            OpOrderMap[1].push_back(LastAdded);
        }
        else if (Value == "*" || Value == "/" || Value == "%")// Multiplication, division, and remainder (Group 5 precedence)
        {
            OpOrderMap[2].push_back(LastAdded);
        }
        else if (Value == "+" || Value == "-")// Addition and subtraction (Group 6 precedence)
        {
            OpOrderMap[3].push_back(LastAdded);
        }
        else if (Value == "<" || Value == "<=" || Value == ">" || Value == ">=")//<,<=, >, >= (Group 8 precedence)
        {
            OpOrderMap[4].push_back(LastAdded);
        }
        else if (Value == "==" || Value == "!=")// 	==, != (Group 9 precedence)
        {
            OpOrderMap[5].push_back(LastAdded);
        }
        else if (Value == "&")// 	Bitwise AND
        {
            OpOrderMap[6].push_back(LastAdded);
        }
        else if (Value == "XOR")// 	Bitwise ^ (exclusive Or)
        {
            OpOrderMap[7].push_back(LastAdded);
        }
        else if (Value == "|")// 	Bitwise inclusive Or
        {
            OpOrderMap[8].push_back(LastAdded);
        }
        else if (Value == "&&")
        {
            OpOrderMap[9].push_back(LastAdded);
        }
        else if (Value == "||")
        {
            OpOrderMap[10].push_back(LastAdded);
        }
        //else if (Value == "?")//Ternary conditional, =, +=, -=, *=, /=, %=, <<=, >>=, &=, ^=, |= (Not supported yet)
        //{
        //    OpOrderMap[11].push_back(LastAdded);
        //}
    }

    void AddPrefixOp(std::string Value)
    {
        LastAdded = Add(IntFormElement("$" + Value, Value.front() == '+' ? 0 : 1));
        OpOrderMap[1].push_back(LastAdded);
    }

    /// <summary>
    /// Changes the last added element into postfix ++/-- OpValue
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <param name="FormIndex">Index of the form.</param>
    void ChangeLastToPostfixOp(std::string Value, size_t FormIndex)
    {
        auto lastElement = this[FormIndex].at(LastAdded);
        std::string strBuffer = lastElement.ElementType;
        this[FormIndex].Remove(LastAdded);
        LastAdded = Add(IntFormElement(strBuffer, Value));
    }

    void ResetOps()
    {
        OpOrderMap.clear();
        for (int index = 0; index < 11; ++index) { OpOrderMap.push_back(IntVector()); }
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="IntFormData"/> class.
    /// </summary>
    IntFormData()
    {//Initialize vector for Order of operations
        for (int index = 0; index < 12; ++index) { OpOrderMap.push_back(IntVector()); }
    }
    /// <summary>
    /// Finalizes an instance of the <see cref="IntFormData"/> class.
    /// </summary>
    ~IntFormData() {}
};

/// <summary>
/// Class IntFormula. (FormulaElement)Operator(FormulaElement)
/// FormulaElements stored as std::vector<std::string>
/// Expression Example: ((Variable01 >= 1)&&(Variable02>2.5))
/// with (Variable01 >= 1) FormulaElement values:
/// Variable01, >=, #i0
/// with (Variable01 >= 1) values referenced from:
/// Variable01, >=, IntValues[0]
/// with (Variable02>2.5) FormulaElement values:
/// Variable02, >, #i0
/// with (Variable02>2.5) values referenced from:
/// Variable02, >, IntValues[0]
/// Initial FormulaElement Values : @1, &&, @2
/// </summary>
DLL_API class IntFormula : public std::vector<IntFormData>
{
private:
    using IntVector = std::vector<int>;
    /// <summary>
    /// Prevents a default instance of the <see cref="IntFormula"/> class from being created.
    /// </summary>
    IntFormula() {}
protected://All Derivatives can use
    /// <summary>
    /// Returns the rest of string.
    /// </summary>
    /// <param name="targetStr">The target string.</param>
    /// <param name="index">The index.</param>
    /// <returns>std.string.</returns>
    std::string ReturnRestOfString(std::string& targetStr, size_t index)
    {
        std::string strBuffer = "";
        for (std::string::iterator CurrentVal = targetStr.begin() + index, LastVal = targetStr.end(); CurrentVal != LastVal; ++CurrentVal)
        {
            strBuffer += *CurrentVal;
        }
        return strBuffer;
    }

    /// <summary>
    /// Applies Power of operation
    /// </summary>
    /// <param name="expValue">The exponent value.</param>
    template<typename ValueType>
    static int PowOp(int& value, ValueType& expValue)
    {
        if (expValue == 1) { return value; }//Return self
        else if (expValue == 0)
        {
            return 1;
        }
        else if (expValue < 0)//Negative Pow
        {
            return 0;//Since int can't have decimal format values just setting as one
        }
        else if (value == 10)
        {
            return VariableConversionFunctions::PowerOfTens[expValue];
        }
        else
        {
            //Code based on https://www.geeksforgeeks.org/write-an-iterative-olog-y-function-for-powx-y/
            int self = value;
            int res = 1;// Initialize result
            while (expValue > 0)
            {
                // If expValue is odd, multiply self with result
                if (expValue % 2 == 1)
                    res *= self;
                // n must be even now
                expValue = expValue >> 1; // y = y/2
                self = self * self; // Change x to x^2
            }
            return res;
        }
    }
public:
    /// <summary>
    /// Trims the formula.
    /// </summary>
    void TrimFormula()
    {
        if (this->size() == 2 && at(0).size() == 1 && at(0).begin()->second.ElementType.front() == '@')//this[0][0].front() == "@")
        {
            this[0] = this[1]; this->pop_back();//Reduce formula in (@1) to just @1
        }
    }

    int EvaluateOrderOfOperations(IntFormData& FormCopy)
    {
        int valResult;

        bool TempBool;
        int tempValue;
        int leftValue;
        int rightValue;

        IntVector& OpOrderElement = FormCopy.OpOrderMap[0];
        IntFormData::iterator OpIterator;
        auto OpVal = FormCopy.at(0);
        IntFormData::iterator LeftVal;
        IntFormData::iterator RightVal;
        int leftResult;
        int rightResult;

        //Applying operations via C++ variation of order of operations
        //https://en.cppreference.com/w/cpp/language/operator_precedence
        for (int opIndex = 0; opIndex < 12; ++opIndex)
        {
            OpOrderElement = FormCopy.OpOrderMap[opIndex];
            for (IntVector::iterator CurrentVal = OpOrderElement.begin(), LastVal = OpOrderElement.end(); CurrentVal != LastVal; ++CurrentVal)
            {
                OpIterator = FormCopy.find(*CurrentVal);
                OpVal = FormCopy[*CurrentVal];

                if (OpIterator->second.ElementType != "!" && OpIterator->second.ElementType != "SqrtOf")
                {
                    LeftVal = OpIterator - 1;
                    leftValue = LeftVal->second.ElementType == "true" ? 1 : (LeftVal->second.ElementType == "false" ? 0 : FormCopy.NumMap[LeftVal->first]);
                }
                RightVal = OpIterator + 1;
                rightValue = RightVal->second.ElementType == "true" ? 1 : (RightVal->second.ElementType == "false" ? 0 : FormCopy.NumMap[RightVal->first]);

                switch (opIndex)
                {
                default://placeholder code
                    break;
                case 0://PowerOf, ++ PostFix, -- PostFix Not Supported
                    if (OpIterator->second.ElementType == "^")
                    {
#ifdef IntFormula_UseMathLib
                        leftValue = std::pow(leftValue, rightValue);
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
#else
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, IntFormula::PowOp(leftValue, rightValue));
#endif
                    }
                    break;
                case 1://(++ PreFix, -- PreFix Not Supported), ! (Unary plus and minus not supported yet)
                    if (OpIterator->second.ElementType == "!")
                    {
                        if (RightVal->second.ElementType == "true")
                        {
                            FormCopy.at(RightVal->first).ElementType = "false";
                        }
                        else if (RightVal->second.ElementType == "false")
                        {
                            FormCopy.at(RightVal->first).ElementType = "true";
                        }
                        else
                        {
                            if (rightValue == 0)//Zero is false otherwise count as if it was true
                                FormCopy.SwitchOpToVal(OpVal, OpIterator->first, RightVal, true);
                            else
                                FormCopy.SwitchOpToVal(OpVal, OpIterator->first, RightVal, false);
                        }
                        FormCopy.erase(OpIterator);
                    }
                    else if (OpIterator->second.ElementType == "-")//Only applies to numbers
                    {
                        rightValue = FormCopy.NumMap[RightVal->first];
                        rightValue *= -1;
                        FormCopy.NumMap[RightVal->first] = rightValue;
                    }
                    break;
                case 2:// 	Multiplication, division, and remainder
                    if (OpVal.ElementType == "*")
                    {
                        leftValue *= rightValue;
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    }
                    else if (OpVal.ElementType == "/")
                    {
                        leftValue /= rightValue;
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    }
                    else if (OpVal.ElementType == "%")
                    {
                        leftValue %= rightValue;
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    }
                    break;
                case 3://Addition and subtraction
                    if (OpVal.ElementType == "+")
                    {
                        leftValue += rightValue;
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    }
                    else if (OpVal.ElementType == "-")
                    {
                        leftValue -= rightValue;
                        FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    }
                    break;
                    //case 3.3://(<<   >>  Bitwise left shift and right shift not supported yet)
                    //	break;
                    //case 3.6: <=> 	Three-way comparison operator not supported yet
                    //	break;
                case 4://<,<=, >, >=
                    if (OpVal.ElementType == "<") { TempBool = leftValue < rightValue; }
                    else if (OpVal.ElementType == "<=") { TempBool = leftValue <= rightValue; }
                    else if (OpVal.ElementType == ">") { TempBool = leftValue > rightValue; }
                    else if (OpVal.ElementType == ">=") { TempBool = leftValue >= rightValue; }
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, TempBool);
                    break;
                case 5://==, !=
                    if (OpVal.ElementType == "==") { TempBool = (leftValue == rightValue); }
                    else if (OpVal.ElementType == "!=") { TempBool = (leftValue != rightValue); }
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, TempBool);
                    break;
                case 6://&
                        leftValue = leftValue & rightValue;
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    break;
                case 7://XOR
                        leftValue = leftValue ^ rightValue;
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    break;
                case 8:// | Bitwise OR (inclusive or)
                    leftValue = leftValue | rightValue;
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, leftValue);
                    break;
                case 9://&&
                    leftValue = LeftVal->second.ElementType == "true" ? 1 : (LeftVal->second.ElementType == "false" ? 0 : FormCopy.NumMap[LeftVal->first]);
                    rightValue = RightVal->second.ElementType == "true" ? 1 : (RightVal->second.ElementType == "false" ? 0 : FormCopy.NumMap[RightVal->first]);
                    TempBool = leftValue && rightValue;
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, TempBool);
                    break;
                case 10:// || (Logical OR)
                    leftValue = LeftVal->second.ElementType == "true" ? 1 : (LeftVal->second.ElementType == "false" ? 0 : FormCopy.NumMap[LeftVal->first]);
                    rightValue = RightVal->second.ElementType == "true" ? 1 : (RightVal->second.ElementType == "false" ? 0 : FormCopy.NumMap[RightVal->first]);
                    TempBool = leftValue || rightValue;
                    FormCopy.SwitchOpToVal(OpVal, OpIterator->first, LeftVal, RightVal, TempBool);
                    break;
                    //case 11://Ternary conditional, =, +=,   -=, *=,   /=,   %=,<<=,   >>=, &= ,  ^=,   |= (Not supported yet)
                    //	break;
                }
            }
        }
        if (FormCopy.size() == 1)
        {
            IntFormData::iterator ElementIter = FormCopy.begin();
            int KeyIndex = ElementIter->first;
            if (ElementIter->second.ElementType == "true")
            {
                return 1;
            }
            else if (ElementIter->second.ElementType == "false")
            {
                return 0;
            }
            else if (ElementIter->second.ElementType == "#")
            {
                return FormCopy.NumMap[KeyIndex];
            }
            else
            {
                throw "Failed to evaluate:" + ElementIter->second.ElementType;
            }
        }
        else
        {
            throw "Failed to evaluate to single value!";
        }
    }

    void SwapUpdatedFormData(IntFormData& FormCopy, std::map<std::string, int>& ElementValues, size_t FormIndex = 0)
    {
        std::string CurString;
        char firstChar;
        int targetResult;
        for (IntFormData::iterator CurrentVal = at(FormIndex).begin(), LastVal = at(FormIndex).end(); CurrentVal != LastVal; ++CurrentVal)
        {
            CurString = CurrentVal->second.ElementType;
            firstChar = CurString.front();
            if (firstChar == '@')//FormulaDetected
            {
                targetResult = RecursivelyEvalValues(ElementValues, CurrentVal->second.Index);
                FormCopy.ReplaceFormVal(CurrentVal->first, targetResult);
            }
            else if (firstChar != '#' && firstChar != '$' && firstChar != '+' && firstChar != '-' && firstChar != '*' && firstChar != '/' && firstChar != '%' &&
                firstChar != '&' && firstChar != '|' && firstChar != '!' && firstChar != '<' && firstChar != '>' && firstChar != '^' && firstChar != '=' && CurString.front() != '?' && CurString == "XOR")
            {//Swap Variable with values
                FormCopy.ReplaceFormVal(CurrentVal->first, ElementValues.at(CurString));
            }
        }
    }

    int RecursivelyEvalValues(std::map<std::string, int>& ElementValues, size_t FormIndex)
    {//Each Formula Calculates order of operations etc separately
        IntFormData FormCopy = at(FormIndex);
        SwapUpdatedFormData(FormCopy, ElementValues, FormIndex);
        return EvaluateOrderOfOperations(FormCopy);
    }

    int EvalValues(std::map<std::string, int> ElementValues)
    {
        IntFormData FormCopy = this->at(0);//Duplicate values so can erase parts when calculating
        SwapUpdatedFormData(FormCopy, ElementValues);
        return EvaluateOrderOfOperations(FormCopy);
    }

    /// <summary>
    /// Recursively adds to the string.
    /// </summary>
    /// <param name="strBuffer">The string buffer.</param>
    /// <param name="FormIndex">Index of the form.</param>
    void RecursivelyAddToString(std::string& strBuffer, size_t FormIndex)
    {
        std::string CurString;
        for (IntFormData::iterator CurrentVal = at(FormIndex).begin(), LastVal = at(FormIndex).end(); CurrentVal != LastVal; ++CurrentVal)
        {
            CurString = CurrentVal->second.ElementType;
            if (CurString.front() == '@')//FormulaDetected
            {
                strBuffer += "(";
                RecursivelyAddToString(strBuffer, CurrentVal->second.Index);
                strBuffer += ")";
            }
            else if (CurString.front() == '#')//NumberDetected
            {
                strBuffer += at(0).NumMap.at(CurrentVal->first);
            }
            else
            {
                strBuffer += CurString;
            }
        }
    }

    /// <summary>
    /// Converts to string(with no extra spacing applied).
    /// </summary>
    /// <returns>std.string.</returns>
    std::string ToString()
    {
        std::string strBuffer = "";
        std::string CurString;
        for (IntFormData::iterator CurrentVal = at(0).begin(), LastVal = at(0).end(); CurrentVal != LastVal; ++CurrentVal)
        {
            CurString = CurrentVal->second.ElementType;
            if (CurString.front() == '@')//FormulaDetected
            {
                strBuffer += "(";
                RecursivelyAddToString(strBuffer, CurrentVal->second.Index);
                strBuffer += ")";
            }
            else if (CurString.front() == '#')//NumberDetected
            {
                strBuffer += at(0).NumMap.at(CurrentVal->first);
            }
            else
            {
                strBuffer += CurString;
            }
        }
        return strBuffer;
    }

    /// <summary>
    /// Inserts from buffer.
    /// </summary>
    /// <param name="strBuffer">The string buffer.</param>
    /// <param name="FormulaIndex">Index of the formula.</param>
    /// <param name="ScanType">Type of the scan.</param>
    void InsertFromBuffer(std::string& strBuffer, size_t& FormulaIndex, short& ScanType)
    {
        //https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/
        std::string ConvertedStr = strBuffer;
        std::for_each(ConvertedStr.begin(), ConvertedStr.end(), [](char& c) {c = ::tolower(c); });
        if (ConvertedStr == "true")
        {
            this->at(FormulaIndex).AddBool(true);
        }
        else if (ConvertedStr == "false")
        {
            this->at(FormulaIndex).AddBool(false);
        }
        else if (ScanType == 3)
        {
            this->at(FormulaIndex).AddVariable(strBuffer);
        }
        else if (ScanType == 4)
        {
            this->at(FormulaIndex).AddNum(strBuffer);
        }
        else if (ScanType == 1)
        {
            this->at(FormulaIndex).AddOp(strBuffer);
        }
        else if (ScanType == 11)//Prefix ++ or --
        {
            this->at(FormulaIndex).AddPrefixOp(strBuffer);
        }
        else if (ScanType == 10)//Postfix Op ++ or --
        {
            this->at(FormulaIndex).ChangeLastToPostfixOp(strBuffer, FormulaIndex);
        }
        //else if(ScanType==12)
        //{
        //	this->at(FormulaIndex).AddTernaryOperatorOp(strBuffer);
        //}
        else//CATCH-ALL
        {
            this->at(FormulaIndex).AddVariable(strBuffer);
        }
    }

    /// <summary>
    /// Resets to single blank formula
    /// </summary>
    void ResetToBlank()
    {
        this->clear();
        this->push_back(IntFormData());//Initialize first (Formula) field
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="IntFormula" /> class.
    /// </summary>
    /// <param name="ElemValue">The elem value to read in order to create formula data.</param>
    IntFormula(std::string ElemValue)
    {
        //0 = ???
        //1 = Operator
        //3 = Variable Value
        //4 = Number
        short ScanType = 0;
        std::string strBuffer = "";
        size_t FormulaIndex = 0;
        //size_t CurrentFormElement = 0;
        this->push_back(IntFormData());//Initialize first (Formula) field
        //auto targetForm = at(0);
        for (std::string::iterator CurrentVal = ElemValue.begin(), LastVal = ElemValue.end(); CurrentVal != LastVal; ++CurrentVal)
        {
            if (*CurrentVal == '(')
            {
                //if(ScanType==10){strBuffer = at(FormulaIndex).back()+strBuffer;at(FormulaIndex).back()=strBuffer;}
                if (!strBuffer.empty()) { InsertFromBuffer(strBuffer, FormulaIndex, ScanType); }
                FormulaIndex = this->size();
                this->push_back(IntFormData());
            }
            else if (*CurrentVal == ')')
            {
                InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                strBuffer = ""; ScanType = 0;
                --FormulaIndex;
            }
            else if (ScanType == 0 || ScanType == 10)//Almost only at either start of a formula or after operator
            {
                if (ScanType == 10)//Prefix/postfix detection for ++/--
                {
                    if (*CurrentVal == ' ' || *CurrentVal == '*' || *CurrentVal == '/' || *CurrentVal == '&' || *CurrentVal == '|' || *CurrentVal == '<' || *CurrentVal == '>' || *CurrentVal == '=' || *CurrentVal == '!' || *CurrentVal == '+' || *CurrentVal == '-')//Postfix
                    {
                        this->at(FormulaIndex).ChangeLastToPostfixOp(strBuffer, FormulaIndex);
                        ScanType = 0;
                    }
                    else//Likely prefix
                    {
                        strBuffer += *CurrentVal;
                        ScanType = 11;
                        continue;
                    }
                }
                //operators = ['==', '!=', '>=', '<=', '&&', '||', '&', '|', '-', '+', '>', '<', '/', '*', '!','++','--']
                if (*CurrentVal == '+')
                {
                    strBuffer = '+'; ScanType = 1;
                }
                else if (*CurrentVal == '-')
                {
                    strBuffer = '-'; ScanType = 1;//Either Number or operator
                }
                else if (*CurrentVal == '!')//Negative Operator only valid for in front of NonOperators
                {
                    this->at(FormulaIndex).AddOp("!");
                }
                else if (*CurrentVal == '^')
                {
                    this->at(FormulaIndex).AddOp("^");
                }
                //else if(*CurrentVal == '?')//TernaryOperator detection start
                //{
                //	strBuffer = this->at(FormulaIndex).ExtractLastElem();
                //	ScanType = 12;
                //}
                else
                {
                    if (VariableConversionFunctions::IsDigit(*CurrentVal))
                    {
                        ScanType = 4;
                        strBuffer = *CurrentVal;
                    }
                    else if (*CurrentVal != ' ' && *CurrentVal != '\t')//Not Whitespace
                    {
                        ScanType = 3;
                        strBuffer = *CurrentVal;
                    }
                }
            }
            else if (ScanType == 1)
            {
                if (strBuffer == "-")
                {
                    if (VariableConversionFunctions::IsDigit(*CurrentVal))
                    {
                        ScanType == 4; strBuffer += *CurrentVal;
                    }
                    else if (*CurrentVal == '-')//-- Operator
                    {
                        strBuffer = "--"; ScanType = 11;//this->at(FormulaIndex).push_back("--"); strBuffer.clear(); ScanType = 11;
                    }
                    else//- Operator
                    {
                        this->at(FormulaIndex).AddOp("-");
                        if (*CurrentVal == '!')//Inverse operator detected after
                        {
                            this->at(FormulaIndex).AddOp("!"); strBuffer.clear(); ScanType = 0;
                        }
                        else
                        {
                            strBuffer = *CurrentVal;
                        }
                    }
                }
                else if (strBuffer == "!")
                {
                    if (*CurrentVal == '=')//!= Operator
                    {
                        this->at(FormulaIndex).AddOp("!="); strBuffer.clear(); ScanType = 0;
                    }
                    else//- Operator
                    {
                        //Invalid operator between variables?
                        throw "Invalid operator between variables!";
                    }
                }
                else if (strBuffer == "+")
                {
                    strBuffer += *CurrentVal;
                    //To-Do Create detection of Prefix/postfix detection
                    if (*CurrentVal == '+')//++ Operator
                    {
                        strBuffer = "++"; ScanType = 11;//this->at(FormulaIndex).push_back("++"); strBuffer.clear(); ScanType = 0;
                    }
                    else//+ Operator
                    {
                        this->at(FormulaIndex).AddOp("+");
                        if (*CurrentVal == '!')//Inverse operator detected after
                        {
                            this->at(FormulaIndex).AddOp("!"); strBuffer.clear(); ScanType = 0;
                        }
                        else
                        {
                            strBuffer = *CurrentVal;
                            if (*CurrentVal == '-' || VariableConversionFunctions::IsDigit(*CurrentVal))
                            {
                                ScanType = 4;
                            }
                            else
                            {
                                ScanType = 3;
                            }
                        }
                    }
                }
                else if (strBuffer == "&")
                {
                    strBuffer += *CurrentVal;
                    if (*CurrentVal == '&')
                    {
                        this->at(FormulaIndex).AddOp("&&"); strBuffer.clear(); ScanType = 0;
                    }
                    else
                    {
                        this->at(FormulaIndex).AddOp("&");
                        if (*CurrentVal == '!')
                        {
                            this->at(FormulaIndex).AddOp("!"); strBuffer.clear(); ScanType = 0;
                        }
                        else
                        {
                            strBuffer = *CurrentVal;
                            if (*CurrentVal == '-' || VariableConversionFunctions::IsDigit(*CurrentVal))
                            {
                                ScanType = 4;
                            }
                            else
                            {
                                ScanType = 3;
                            }
                        }
                    }
                }
                else if (strBuffer == "|")
                {
                    strBuffer += *CurrentVal;
                    if (*CurrentVal == '|')
                    {
                        this->at(FormulaIndex).AddOp("||"); strBuffer.clear(); ScanType = 0;
                    }
                    else
                    {
                        this->at(FormulaIndex).AddOp("|");
                        if (*CurrentVal == '!')
                        {
                            this->at(FormulaIndex).AddOp("!"); strBuffer.clear(); ScanType = 0;
                        }
                        else
                        {
                            strBuffer = *CurrentVal;
                            if (*CurrentVal == '-' || VariableConversionFunctions::IsDigit(*CurrentVal))
                            {
                                ScanType = 4;
                            }
                            else
                            {
                                ScanType = 3;
                            }
                        }
                    }
                }
                else//Catch-all for most operators
                {
                    //strBuffer += *CurrentVal;
                    if (*CurrentVal == '=')
                    {
                        this->at(FormulaIndex).AddOp(strBuffer + *CurrentVal); strBuffer.clear(); ScanType = 0;
                    }
                    else
                    {
                        this->at(FormulaIndex).AddOp(strBuffer);
                        if (*CurrentVal == '!')
                        {
                            this->at(FormulaIndex).AddOp("!"); strBuffer.clear(); ScanType = 0;
                        }
                        else
                        {
                            strBuffer = *CurrentVal;
                            if (*CurrentVal == '-' || VariableConversionFunctions::IsDigit(*CurrentVal))
                            {
                                ScanType = 4;
                            }
                            else
                            {
                                ScanType = 3;
                            }
                        }
                    }
                }
            }
            else if (ScanType == 11)//Prefix Variable (Partial support for prefix increment variables)
            {
                if (*CurrentVal != ' ' && *CurrentVal != '\t')//Whitespace
                {
                    this->at(FormulaIndex).AddPrefixOp(strBuffer);
                }
                else
                {
                    strBuffer += *CurrentVal;
                }
            }
            else
            {//Scan type either number or variable at this point
                if (*CurrentVal == '+')//++ or +
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '+'; ScanType = 1;
                }
                else if (*CurrentVal == '-')//-- or -
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '-'; ScanType = 1;
                }
                else if (*CurrentVal == '!')//!=
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '!'; ScanType = 1;
                }
                else if (*CurrentVal == '&')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '&'; ScanType = 1;
                }
                else if (*CurrentVal == '|')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '|'; ScanType = 1;
                }
                else if (*CurrentVal == '=')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '='; ScanType = 1;
                }
                else if (*CurrentVal == '>')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '>'; ScanType = 1;
                }
                else if (*CurrentVal == '<')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    strBuffer = '<'; ScanType = 1;
                }
                else if (*CurrentVal == '/')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    this->at(FormulaIndex).AddOp("/");
                }
                else if (*CurrentVal == '*')
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    this->at(FormulaIndex).AddOp("*");
                }
                else if (*CurrentVal == '^')//Power of function
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    this->at(FormulaIndex).AddOp("^");
                }
                else if (*CurrentVal == '$')//Shorthand for XOR for now
                {
                    InsertFromBuffer(strBuffer, FormulaIndex, ScanType);
                    this->at(FormulaIndex).AddOp("XOR");
                }
                else
                {
                    strBuffer += *CurrentVal;
                }
            }
        }
        TrimFormula();
    }
};