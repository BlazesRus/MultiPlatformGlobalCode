/*	Code Created by James Michael Armstrong (NexusName:BlazesRus)
	Latest Code Release at https://github.com/BlazesRus/NifLibEnvironment
	*/
#ifndef SuperDec_ExtraDec64_19Decimal_IncludeGuard
#define SuperDec_ExtraDec64_19Decimal_IncludeGuard

#ifndef BlazesGlobalCode_FileStructureVersion
#	define BlazesGlobalCode_FileStructureVersion 0
//FileStructureVersion 0 = Refers to required files set up similar/same as Library Versions of files
//FileStructureVersion 1 = All required files from GlobalCode within same folder locally
#endif

#ifdef BLAZESGLOBALCODE_LIBRARY
#	include "..\DLLAPI.h"
#else
//Dummy define of DLL_API to prevent requiring 2 separate Defines of initial class headers(without needing the DLL_API define)
#	ifndef DLL_API
#		define DLL_API
#	endif
#endif

#if !defined BlazesGlobalCode_CSharpCode
#	include <io.h>
#	include <math.h>
#	include <iostream>
#	include <string>
#	include "SuperDecHex.h"

//


//Non-Alternating headers above (Structure based headers in this section)
#	if BlazesGlobalCode_FileStructureVersion == 0 || !defined BlazesGlobalCode_FileStructureVersion//(library style  layout)
//Place  library Style  layout here
#		include "..\ThirdPartyCode\uint128_t\uint128_t.h"
#	elif BlazesGlobalCode_FileStructureVersion == 1//(Local version style layout)
//Place Local version layout here
#		include "uint128_t.h"
#	endif
#endif

using Int128 = uint128_t;

//Attempt to auto-detect if compiling code as C#
#if !defined BlazesGlobalCode_CSharpCode && !defined __cplusplus
	#define BlazesGlobalCode_CSharpCode true
#endif

#ifdef BlazesGlobalCode_CSharpCode//C# version of code

#else//C++ version of code
class DLL_API SuperDec_ExtraDec64_19Decimal
{
	unsigned __int64 IntValue;
	unsigned __int8 DecBoolStatus = 0;
	unsigned __int64 DecimalStatus;
	//************************************
	// Method:    AsInt32
	// FullName:  CustomDec_ExtraDec64_19Decimal::AsInt32
	// Access:    private
	// Returns:   signed __int32
	// Qualifier:
	//************************************
	signed __int32 AsInt32();
	//************************************
	// Method:    AsSignedInt64
	// FullName:  CustomDec_ExtraDec64_19Decimal::AsSignedInt64
	// Access:    private
	// Returns:   signed __int64
	// Qualifier:
	//************************************
	signed __int64 AsSignedInt64();
	//************************************
	// Method:    AsDouble
	// FullName:  CustomDec_ExtraDec64_19Decimal::AsDouble
	// Access:    private
	// Returns:   double
	// Qualifier:
	//************************************
	double AsDouble();
	//************************************
	// Method:    AsString
	// FullName:  CustomDec_ExtraDec64_19Decimal::AsString
	// Access:    private
	// Returns:   std::string
	// Qualifier:
	//************************************
	std::string AsString();
	//************************************
	// Method:    ApplyAddition
	// FullName:  CustomDec_ExtraDec64_19Decimal::ApplyAddition
	// Access:    private
	// Returns:   void
	// Qualifier:
	// Parameter: ValueType Value
	//************************************
	template <typename ValueType>
	void ApplyIntAddition(ValueType Value);
	SuperDec_ExtraDec64_19Decimal operator+(unsigned int Value) { ApplyIntAddition(Value); };
	SuperDec_ExtraDec64_19Decimal operator+(signed int Value) { ApplyIntAddition(Value); };
	SuperDec_ExtraDec64_19Decimal operator+(unsigned __int64 Value) { ApplyIntAddition(Value); }
	SuperDec_ExtraDec64_19Decimal operator+(signed __int64 Value) { ApplyIntAddition(Value); }
	SuperDec_ExtraDec64_19Decimal operator+(unsigned __int16 Value) { ApplyIntAddition(Value); }
	SuperDec_ExtraDec64_19Decimal operator+(signed __int16 Value) { ApplyIntAddition(Value); }
	SuperDec_ExtraDec64_19Decimal operator+(unsigned __int8 Value) { ApplyIntAddition(Value); }
	SuperDec_ExtraDec64_19Decimal operator+(signed __int8 Value) { ApplyIntAddition(Value); }
	//************************************
	// Method:    operator+
	// FullName:  CustomDec_ExtraDec64_19Decimal::operator+
	// Access:    private
	// Returns:   CustomDec
	// Qualifier:
	// Parameter: double Value
	//************************************
	SuperDec_ExtraDec64_19Decimal operator+(double Value);
	//************************************
	// Method:    operator+
	// FullName:  CustomDec_ExtraDec64_19Decimal::operator+
	// Access:    private
	// Returns:   CustomDec
	// Qualifier:
	// Parameter: std::string Value
	//************************************
	SuperDec_ExtraDec64_19Decimal operator+(std::string Value);
	//************************************
	// Method:    ApplySubtraction
	// FullName:  CustomDec_ExtraDec64_19Decimal::ApplySubtraction
	// Access:    private
	// Returns:   void
	// Qualifier:
	// Parameter: ValueType Value
	//************************************
	template <typename ValueType>
	void ApplyIntSubtraction(ValueType Value);
	SuperDec_ExtraDec64_19Decimal operator-(unsigned int Value) { ApplyIntSubtraction(Value); };
	SuperDec_ExtraDec64_19Decimal operator-(signed int Value) { ApplyIntSubtraction(Value); };
	SuperDec_ExtraDec64_19Decimal operator-(unsigned __int64 Value) { ApplyIntSubtraction(Value); }
	SuperDec_ExtraDec64_19Decimal operator-(signed __int64 Value) { ApplyIntSubtraction(Value); }
	SuperDec_ExtraDec64_19Decimal operator-(unsigned __int16 Value) { ApplyIntSubtraction(Value); }
	SuperDec_ExtraDec64_19Decimal operator-(signed __int16 Value) { ApplyIntSubtraction(Value); }
	SuperDec_ExtraDec64_19Decimal operator-(unsigned __int8 Value) { ApplyIntSubtraction(Value); }
	SuperDec_ExtraDec64_19Decimal operator-(signed __int8 Value) { ApplyIntSubtraction(Value); }
	//************************************
	// Method:    ApplyEqual
	// FullName:  CustomDec_ExtraDec64_19Decimal::ApplyEqual
	// Access:    private
	// Returns:   void
	// Qualifier:
	// Parameter: ValueType Value
	//************************************
	template <typename ValueType>
	void ApplyIntEqual(ValueType Value);
	SuperDec_ExtraDec64_19Decimal operator=(std::string Value);
	SuperDec_ExtraDec64_19Decimal operator=(unsigned int Value) { ApplyIntEqual(Value); };
	SuperDec_ExtraDec64_19Decimal operator=(signed int Value) { ApplyIntEqual(Value); };
	SuperDec_ExtraDec64_19Decimal operator=(unsigned __int64 Value) { ApplyIntEqual(Value); }
	SuperDec_ExtraDec64_19Decimal operator=(signed __int64 Value) { ApplyIntEqual(Value); }
	SuperDec_ExtraDec64_19Decimal operator=(unsigned __int16 Value) { ApplyIntEqual(Value); }
	SuperDec_ExtraDec64_19Decimal operator=(signed __int16 Value) { ApplyIntEqual(Value); }
	SuperDec_ExtraDec64_19Decimal operator=(unsigned __int8 Value) { ApplyIntEqual(Value); }
	SuperDec_ExtraDec64_19Decimal operator=(signed __int8 Value) { ApplyIntEqual(Value); }
	SuperDec_ExtraDec64_19Decimal operator=(double Value);
	//************************************
	// Method:    ApplyModulus
	// FullName:  CustomDec_ExtraDec64_19Decimal::ApplyModulus
	// Access:    private
	// Returns:   void
	// Qualifier:
	// Parameter: ValueType Value
	//************************************
	template <typename ValueType>
	void ApplyModulus(ValueType Value);
	SuperDec_ExtraDec64_19Decimal operator%(unsigned int Value) { ApplyModulus(Value); };
	SuperDec_ExtraDec64_19Decimal operator%(signed int Value) { ApplyModulus(Value); };
	SuperDec_ExtraDec64_19Decimal operator%(unsigned __int64 Value) { ApplyModulus(Value); }
	SuperDec_ExtraDec64_19Decimal operator%(signed __int64 Value) { ApplyModulus(Value); }
	SuperDec_ExtraDec64_19Decimal operator%(unsigned __int16 Value) { ApplyModulus(Value); }
	SuperDec_ExtraDec64_19Decimal operator%(signed __int16 Value) { ApplyModulus(Value); }
	SuperDec_ExtraDec64_19Decimal operator%(unsigned __int8 Value) { ApplyModulus(Value); }
	SuperDec_ExtraDec64_19Decimal operator%(signed __int8 Value) { ApplyModulus(Value); }
	//Value to power of Value
	SuperDec_ExtraDec64_19Decimal operator^(unsigned int Value);
	//************************************
	// Method:    ApplyIntCompare
	// FullName:  CustomDec_ExtraDec64_19Decimal::ApplyIntCompare
	// Access:    private
	// Returns:   bool
	// Qualifier:
	// Parameter: CustomDec c1
	// Parameter: ValueType Value
	//************************************
	template <typename ValueType>
	bool ApplyIntCompare(CustomDec c1, ValueType Value);
	//************************************
	// Method:    ApplyIntNotEquals
	// FullName:  CustomDec_ExtraDec64_19Decimal::ApplyIntNotEquals
	// Access:    private
	// Returns:   bool
	// Qualifier:
	// Parameter: CustomDec c1
	// Parameter: ValueType Value
	//************************************
	template <typename ValueType>
	bool ApplyIntNotEquals(SuperDec_ExtraDec64_19Decimal c1, ValueType Value);
	friend bool operator== (const SuperDec_ExtraDec64_19Decimal &c1, unsigned int &c2) { return ApplyIntCompare(c1, c2); };
	friend bool operator!= (const SuperDec_ExtraDec64_19Decimal &c1, unsigned int &c2) { return ApplyIntNotEquals(c1, c2); };
	//************************************
	// Method:    operator*
	// FullName:  CustomDec_ExtraDec64_19Decimal::operator*
	// Access:    private
	// Returns:   CustomDec
	// Qualifier:
	// Parameter: double Value
	//************************************
	SuperDec_ExtraDec64_19Decimal operator*(double Value);
	template <typename ValueType>
	void ApplyIntMultiply(ValueType Value);
	SuperDec_ExtraDec64_19Decimal operator*(unsigned int Value) { ApplyIntMultiply(Value); };
	SuperDec_ExtraDec64_19Decimal operator*(signed int Value) { ApplyIntMultiply(Value); };
	SuperDec_ExtraDec64_19Decimal operator*(unsigned __int64 Value) { ApplyIntMultiply(Value); }
	SuperDec_ExtraDec64_19Decimal operator*(signed __int64 Value) { ApplyIntMultiply(Value); }
	SuperDec_ExtraDec64_19Decimal operator*(unsigned __int16 Value) { ApplyIntMultiply(Value); }
	SuperDec_ExtraDec64_19Decimal operator*(signed __int16 Value) { ApplyIntMultiply(Value); }
	SuperDec_ExtraDec64_19Decimal operator*(unsigned __int8 Value) { ApplyIntMultiply(Value); }
	SuperDec_ExtraDec64_19Decimal operator*(signed __int8 Value) { ApplyIntMultiply(Value); }
	//************************************
	// Method:    operator/
	// FullName:  CustomDec_ExtraDec64_19Decimal::operator/
	// Access:    private
	// Returns:   CustomDec
	// Qualifier:
	// Parameter: double Value
	//************************************
	SuperDec_ExtraDec64_19Decimal operator/(double Value);
	template <typename ValueType>
	void ApplyIntDivide(ValueType Value);
	SuperDec_ExtraDec64_19Decimal operator/(unsigned int Value) { ApplyIntDivide(Value); };
	SuperDec_ExtraDec64_19Decimal operator/(signed int Value) { ApplyIntDivide(Value); };
	SuperDec_ExtraDec64_19Decimal operator/(unsigned __int64 Value) { ApplyIntDivide(Value); }
	SuperDec_ExtraDec64_19Decimal operator/(signed __int64 Value) { ApplyIntDivide(Value); }
	SuperDec_ExtraDec64_19Decimal operator/(unsigned __int16 Value) { ApplyIntDivide(Value); }
	SuperDec_ExtraDec64_19Decimal operator/(signed __int16 Value) { ApplyIntDivide(Value); }
	SuperDec_ExtraDec64_19Decimal operator/(unsigned __int8 Value) { ApplyIntDivide(Value); }
	SuperDec_ExtraDec64_19Decimal operator/(signed __int8 Value) { ApplyIntDivide(Value); }
};

template <typename ValueType>
void SuperDec_ExtraDec64_19Decimal::ApplyIntAddition(ValueType Value)
{
#	if defined SuperDec_SignedIntStatus
	IntValue += Value;
#	elif defined SuperDec_UnsignedBoolean
	if(DecBoolStatus==0)
	{
		if(Value<0)
		{
			if(Value>IntValue)
			{
				IntValue = Value - IntValue;
				DecBoolStatus = 1;
			}
			else
			{
			}
		}
		else
		{
		}
	}
	else if(DecBoolStatus==1)
	{
	}
	else//Other Values used for special Decimal Statuses etc
	{
	}
	if(IntValue==0&&DecBoolStatus==1)//Fix so negative zero is positive zero
	{
		DecBoolStatus = 0;
	}
#	else//Unsigned Version (Stored data in Decimal Status)

#	endif
}

template <typename ValueType>
void SuperDec_ExtraDec64_19Decimal::ApplyIntSubtraction(ValueType Value)
{
	if(DecBoolStatus==0)//Was Positive
	{
		if(Value>0)//- Value
		{
			if(Value>IntValue)
			{
				IntValue = Value - IntValue;
				DecBoolStatus = 1;
			}
			else
			{
				IntValue -= Value;
			}
		}
		else//+ Abs(Value)
		{
			IntValue += abs(Value);
		}
	}
	else if(DecBoolStatus == 1)//Was Negative
	{
		if(Value<0)//+ Abs(Value)
		{

		}
		else
		{
			IntValue += Value;
		}
	}
	else//Other Values used for special Decimal Statuses etc
	{
	}
	if(IntValue==0&&DecBoolStatus==1)//Fix so negative zero is positive zero
	{
		DecBoolStatus = 0;
	}
}

template <typename ValueType>
void SuperDec_ExtraDec64_19Decimal::ApplyIntMultiply(ValueType Value)
{
	if(Value == 0)
	{
		IntValue = 0;
		DecimalStatus = 0;
	}
	else if(Value == 1) {}
	else if(Value ==-1)
	{
//		if(DecimalStatus==0&&IntValue==0){}
//#	if defined SuperDec_SignedIntStatus
//#		if defined SuperDec_sInt32
//		else if(IntValue == -2147483648)
//		{
//#		elif defined SuperDec_sInt8
//		else if(IntValue==-128)
//		{
//#		elif defined SuperDec_sInt16
//		else if(IntValue == -32768)
//		{
//#		elif defined SuperDec_sInt64
//		else if(IntValue == -9223372036854775808)
//		{
//#		endif
//			IntValue = 0;
//		}
//		else if(IntValue==0)
//		{//Set to representation -Zero.XX.....
//#		if defined SuperDec_sInt32
//			IntValue = -2147483648;
//#		elif defined SuperDec_sInt8
//			IntValue = -128;
//#		elif defined SuperDec_sInt16
//			IntValue = -32768;
//#		elif defined SuperDec_sInt64
//			IntValue = -9223372036854775808;
//#		endif
//		}
//		else
//		{
//			IntValue *= -1;
//		}
//#	elif defined SuperDec_UnsignedBoolean
//		if(DecBoolStatus == 1)
//		{
//			DecBoolStatus = 0;
//		}
//		else if(DecBoolStatus == 0)
//		{
//			DecBoolStatus = 1;
//		}
//#		if defined SuperDec_EnableSpecialDecimalStatus
//		else
//		{
//
//		}
//#		endif
//#	else
//		if(DecimalStatus==0)
//		{
//			if(IntValue==0){}
//			else
//			{
//#		if defined SuperDec_9Decimal
//				DecimalStatus = -2147483648;
//#		elif defined SuperDec_2Decimal
//				DecimalStatus = -128;
//#		elif defined SuperDec_4Decimal
//				DecimalStatus = -32768;
//#		elif defined SuperDec_18Decimal
//				DecimalStatus = -9223372036854775808;
//#		endif
//			}
		////}
//#		if defined SuperDec_9Decimal
//		else if(DecimalStatus == -2147483648)
//		{
//#		elif defined SuperDec_2Decimal
//		else if(DecimalStatus==-128)
//		{
//#		elif defined SuperDec_4Decimal
//		else if(DecimalStatus == -32768)
//		{
//#		elif defined SuperDec_18Decimal
//		else if(DecimalStatus == -9223372036854775808)
//		{
//#		endif
//			DecimalStatus = 0;
//		}
//		else
//		{
//			DecimalStatus *= -1;
//		}
//#	endif
	}
	else
	{
//		bool ResultIsNegative = false;
//		if(Value < 0)
//		{
//#		if defined SuperDec_UnsignedBoolean
//			if(DecBoolStatus == 1)
//			{
//				ResultIsNegative = true;
//			}
//#		elif defined SuperDec_SignedIntStatus
//			if(IntValue > 0)
//			{
//				ResultIsNegative = true;
//			}
//#		else
//			if(DecimalStatus > 0)
//			{
//				ResultIsNegative = true;
//			}
//#		endif
//		}
//		else
//		{
//#		if defined SuperDec_UnsignedBoolean
//			if(DecBoolStatus < 0)
//			{
//				ResultIsNegative = true;
//			}
//#		elif defined SuperDec_SignedIntStatus
//			if(IntValue < 0)
//			{
//				ResultIsNegative = true;
//			}
//#		else
//			if(DecimalStatus < 0)
//			{
//				ResultIsNegative = true;
//			}
//#		endif
//		}
//		unsigned __int64 DecRep = DecAsUnsignedInt();
//#	if SuperDec_PreventTruncationToZero == 2
//		//DecRep is multiplied by 10 to allow rounding up remaining value
//		DecRep *= 10;
//#	endif
//		DecRep *= Value;
//#	if SuperDec_PreventTruncationToZero == 2//Place code here for extra rounding up feature
//#	endif
//		ConvertFromDecRep(DecRep);
//		if(ResultIsNegative)
//		{
//#		if defined SuperDec_UnsignedBoolean
//			DecBoolStatus = 1;
//#		elif defined SuperDec_SignedIntStatus
//			if(IntValue == 0 && ResultIsNegative)
//			{
//#			if defined SuperDec_sInt32
//				IntValue = -2147483648;
//#			elif defined SuperDec_sInt8
//				IntValue = -128;
//#			elif defined SuperDec_sInt16
//				IntValue = -32768;
//#			elif defined SuperDec_sInt64
//				IntValue = -9223372036854775808;
//#			endif
//			}
//			else { IntValue *= -1; }
//#		elif !defined SuperDec_AngleDecimal
//			DecimalStatus *= -1;
//#		endif
//		}
//		else
//		{
//#		if defined SuperDec_UnsignedBoolean
//			DecBoolStatus = 0;
//#		endif
//		}
	}
//	//#		if defined SuperDec_SignedIntStatus
//	//		if(DecimalStatus == 0)
//	//		{
//	//			IntValue *= Value;
//	//		}
//	//		else
//	//		{
//	//			signed __int64 DecRep = DecAsSignedInt();
//	//			DecRep *= Value;
//	//			ConvertFromDecRep(DecRep);
//	//		}
//	//#		else
//	//		signed __int64 DecRep = DecAsSignedInt();
//	//		DecRep *= Value;
//	//		ConvertFromDecRep(DecRep);
//	//#		endif
}

template <typename ValueType>
void SuperDec_ExtraDec64_19Decimal::ApplyIntDivide(ValueType Value)
{
	//signed __int64 DecRep = DecAsSignedInt();
	//DecRep /= Value;
	//ConvertFromDecRep(DecRep);
}

template <typename ValueType>
void SuperDec_ExtraDec64_19Decimal::ApplyIntEqual(ValueType Value)
{}

template <typename ValueType>
void SuperDec_ExtraDec64_19Decimal::ApplyModulus(ValueType Value)
{
#	if defined SuperDec_SignedIntStatus
	IntValue %= Value;
#	else//Unsigned Version (Stored data in Decimal Status)

#	endif
}

template <typename ValueType>
bool SuperDec_ExtraDec64_19Decimal::ApplyIntCompare(SuperDec_ExtraDec64_19Decimal c1, ValueType Value)
{
	if(c1.DecBoolStatus>1)
	{
		//Place code here for dealing with special decimal states
	}
	else if(Value<0)
	{
		if(c1.DecBoolStatus==1)
		{
			Value *= -1;
			return c1.IntValue&&c1.DecimalStatus == 0;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(c1.DecBoolStatus==1)
		{
			return false;
		}
		else
		{
			return c1.IntValue&&c1.DecimalStatus == 0;
		}
	}
}

template <typename ValueType>
bool SuperDec_ExtraDec64_19Decimal::ApplyIntNotEquals(CustomDec c1, ValueType Value)
{
	return !ApplyIntCompare(c1, Value);
}
#endif

#endif