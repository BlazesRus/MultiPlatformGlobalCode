/*	Code Created by James Michael Armstrong (NexusName:BlazesRus)
    Latest Code Release at https://github.com/BlazesRus/NifLibEnvironment
*/
#include "IniDataV2.h"
#include <string>

/// <summary>
/// Gets the element data as std::string
/// </summary>
/// <param name="Value">The value.</param>
/// <returns></returns>

#ifdef BlazesGlobalCode_EnableFloatingIni
/// <summary>
/// Gets the float element data.
/// </summary>
/// <param name="Value">The value.</param>
/// <returns></returns>
inline float IniDataV2::GetFloatElementData(std::string Value)
{
	return FloatSettings[Value];
}
#endif

//MediumDec GetMediumDecElementData(std::string Value){}

#ifndef BlazesGlobalCode_DisableMediumDecIni
//inline float IniDataV2::GetMediumDecElementData(std::string Value)
//{
//	return MediumDecSettings[Value];
//}

inline void IniDataV2::SetMediumDecElementData(std::string Key, int Value)
{
	//MediumDecSettings.Add(Key, Value);
}

//inline void IniDataV2::AddMediumDecElementData(std::string Key, MediumDec Value)
//{
//	MediumDecSettings[Key] += Value;
//}
#endif