#include "IniData.h"


void IniData::LoadIniData(std::string FileName)
{
	StringVectorList TargetSettings;
	TargetSettings.LoadFileDataV2(FileName);
	//First part of command;Syntax:[ScriptArg01=ScriptArg02]
	string ScriptArg01;
	//Command Value;Syntax:[ScriptArg01=ScriptArg02]
	string ScriptArg02;
	//CommandScan Stage (limited to value of 255 to save little ram)
	unsigned short CommandStage = 0;
	string LineString = "";
	unsigned int LineSize;
	char LineChar;
	bool InsideParenthesis = false;
	IniDataElement ElementData;
	for(unsigned int LineNumber = 0; TargetSettings.StreamLineData(); ++LineNumber)
	{
		LineString = TargetSettings.CurrentStreamedLineString();
		LineSize = LineString.length();
		for(unsigned int i = 0; i < LineSize; ++i)
		{
			LineChar = LineString.at(i);
			if(LineChar == '"') { InsideParenthesis = !InsideParenthesis; }
			else if(LineChar == '[')
			{
				ScriptArg01 = "";
				CommandStage = 1;
			}
			else if(CommandStage > 0)
			{
				if(InsideParenthesis==false&&(LineChar == '=' || LineChar == ':'))
				{
					CommandStage = 2;
				}
				else if(CommandStage == 2)
				{
					if(LineChar == ']')
					{
						//std::cout << "Executing Command:" << ScriptArg01 << " with parameter "<<ScriptArg02<<"\n";
						CommandStage = 0;
						ElementData.ScriptArg01 = ScriptArg01;
						ElementData.ScriptArg02 = ScriptArg02;
						Add(ElementData);
						ScriptArg02 = "";
						ScriptArg01 = "";
					}
					else
					{
						ScriptArg02 += LineChar;
					}
				}
				else
				{
					ScriptArg01 += LineChar;
				}
			}
		}
	}
}

IniData::IniData()
{}


IniData::~IniData()
{}


IniDataElement::IniDataElement()
{}


IniDataElement::~IniDataElement()
{}
