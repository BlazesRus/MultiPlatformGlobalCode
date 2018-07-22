﻿using CSharpGlobalCode.GlobalCode_ExperimentalCode;
using CSharpGlobalCode.GlobalCode_StringFunctions;
using CSharpGlobalCode.GlobalCode_VariableConversionFunctions;
using CSharpGlobalCode.GlobalCode_VariableLists;
using System.Collections.Generic;
using System.Linq;

namespace CSharpGlobalCode.GlobalCode_NodeTrees
{
    internal class XMLNode : NodeV2<XMLTagTree, XMLNode>
    {
        public string NodeName = "";

        //Detects if either Closing Tag, Closed Tag, or Neither
        //0 = Tag is not a Closing Tag
        //1 = Is Closing Tag
        //2 = Tag is Closed by Tag with InternalName of InternalNameOfTagClosed
        public byte ClosingStatus = 0;

        public string TagContent = "";

        public dynamic ConvertedTagContent = null;

        //Type of data stores inside Tag (Strings stored in TagContent)
        //0:Default Extracted content
        //1:Int
        //2:Bool
        //3:Double
        //4:String
        //5:Event Index(Int)
        //6:Variable Index(Int)
        //7:Havok Class index(Int)
        //8:Short
        //9:QuadVector
        //10:Event String
        //11:Variable String
        //12:Animation Path String
        //13:Condition (String)
        //14:Havok Class Target Name (String)
        //20:List<int>
        //21:DoubleList
        //22:StringList
        //23:BooleanList
        //24:QuadVectorList
        //50:flags (String)
        //51:Clip Mode (String)
        //240:Holds Havok Class info
        //241:hkobject Container
        //250:Unknown (String)
        public byte TagContentType = 0;

        //Additional Tag Args
        public XMLOptionList AdditionTagOptions;

        public bool SelfContainedTag = false;

        public bool XMLVersionTag = false;

        /// <summary>
        /// Detects the type of the content contained within tag
        /// </summary>
        public void DetectTagContentType()
        {
            if (TagContentType == 0 && TagContent != "")
            {
                TagContentType = StringFunctions.FindContentType(TagContent);
                switch (TagContentType)
                {
                    case 1:
                    case 5:
                    case 6:
                    case 7:
                        ConvertedTagContent = VariableConversionFunctions.ReadIntFromString(TagContent);
                        break;

                    case 8:
                        ConvertedTagContent = VariableConversionFunctions.ReadShortFromString(TagContent);
                        break;

                    case 3:
                        ConvertedTagContent = (MediumDec)TagContent;
                        break;

                    case 9:
                        ConvertedTagContent = (QuadVector)TagContent;
                        break;

                    case 20:
                        ConvertedTagContent = (IntegerList)TagContent;
                        break;

                    case 21:
                        ConvertedTagContent = (MediumDecList)TagContent;
                        break;

                    case 22:
                        ConvertedTagContent = (StringList)TagContent;
                        break;

                    case 24:
                        ConvertedTagContent = (QuadVectorList)TagContent;
                        break;
                }
            }
        }

        /// <summary>
        /// Alternative version of DetectTagContentTypesWithin designed to use extra contents from hkparam tags as part of detection of ContentType
        /// </summary>
        public void DetectTagContentTypesWithin()
        {
            DetectTagContentType();
            int ChildListSize = this.NodeLists.Count;
            for (int Index = 0; Index < ChildListSize; ++Index)
            {
                this.NodeLists[Index].DetectTagContentTypesWithin();
            }
        }

        //************************************
        // Method:    GenerateHTMLDoc
        // FullName:  TagNodeTreeTemplateData::Node::GenerateHTMLDoc
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: StringVectorList & OutputBuffer
        // Parameter: int & OutputLvl
        // Parameter: const byte & GenerationOptions
        //************************************
        private StringList GenerateHTMLDoc(StringList OutputBuffer, int TargetBhvNum = 0, int GenerationOptions = 0)
        {
            int OutputLvl = 0;
            string TempTag;
            int SizeTemp;
            TempTag = "<code>";
            TempTag += StringFunctions.CreateTabSpace(OutputLvl);
            TempTag += "<";
            if (ClosingStatus == 1)
            {
                TempTag += "/";
            }
            TempTag += NodeName;
            //Tag Option output
            SizeTemp = AdditionTagOptions.Count;
            XMLOption OptionTemp;
            for (int Index = 0; Index < SizeTemp; ++Index)
            {
                TempTag += " ";
                OptionTemp = AdditionTagOptions.ElementAt(Index);
                if (OptionTemp.ValueType == "None")
                {
                    TempTag += OptionTemp.OptionName;
                }
                else if (OptionTemp.ValueNotInParenthesis)
                {
                    TempTag += "=";
                    TempTag += OptionTemp.ValueString;
                }
                else
                {
                    TempTag += "=\"";
                    TempTag += OptionTemp.ValueString;
                    TempTag += "\"";
                }
            }
            if (SelfContainedTag)
            {
                TempTag += "/>";
                TempTag += "<br>"; OutputBuffer.Add(TempTag);
            }
            else if (ClosingStatus != 1)
            {
                TempTag += ">";
                TempTag += "</code>";
                if (!((TagContentType >= 1 && TagContentType <= 14) || TagContentType == 252))
                {//Don't Separate line for known single-line Tags
                    TempTag += "<br>"; OutputBuffer.Add(TempTag);
                    TempTag = "<code>";
                    TempTag += StringFunctions.CreateTabSpace(OutputLvl + 1);
                    TempTag += "</code>";
                }
                //Output TagContent
                //StringVectorList TempList;
                switch (TagContentType)
                {
                    case 14://Generate link to Havok class
                        {
                            TempTag += "<a href=\"#\"";
                            TempTag += TagContent;
                            TempTag += "\">";
                            TempTag += TagContent;
                            TempTag += "</a>";
                            break;
                        }
                    case 15://Generate linked Havok classes
                        {
                            StringList TempList = (StringList)TagContent;
                            SizeTemp = TempList.Count;
                            //Limit 16 entries a line
                            int LineIndex = 0;
                            for (int Index = 0; Index < SizeTemp; ++Index)
                            {
                                if (LineIndex == 16)
                                {
                                    TempTag += "<br>"; OutputBuffer.Add(TempTag);
                                    TempTag = "<code>";
                                    TempTag += StringFunctions.CreateTabSpace(OutputLvl + 1);
                                    TempTag += "</code>";
                                    LineIndex = 0;
                                }
                                if (LineIndex != 0)
                                {
                                    TempTag += "<code> </code>";
                                }
                                TempTag += "<a href=\"#\"";
                                TempTag += TagContent;
                                TempTag += "\">";
                                TempTag += TagContent;
                                TempTag += "</a>";
                                ++LineIndex;
                            }
                            TempTag += "<br>"; OutputBuffer.Add(TempTag);
                            TempTag = "<code>";
                            TempTag += StringFunctions.CreateTabSpace(OutputLvl + 1);
                            TempTag += "</code>";
                            break;
                        }
                    //case 5://Display index to Event with alt text of EventName (link to EventName)
                    //{
                    //	 int Index = StringFunctions.ReadXIntFromString(TempTag);
                    //	 string NameTemp = SharedData.TargetBHVTreePointer->VariableData.eventNames.ElementAt(Index);
                    //	TempTag += "<a href=\"#\"";
                    //	//Link to EventName here
                    //	TempTag += "eventNames_";
                    //	TempTag += StringFunctions.DoubleToStringConversion(Index);
                    //	TempTag += "\" title=\"";
                    //	//Mouse-Over Text of EventName
                    //	TempTag += NameTemp;
                    //	TempTag += "\">";
                    //	TempTag += TagContent;
                    //	TempTag += "</a>";
                    //	break;
                    //}
                    //case 6://Display index to variable with alt text
                    //{
                    //	 int Index = StringFunctions.ReadXIntFromString(TempTag);
                    //	 string NameTemp = SharedData.TargetBHVTreePointer->VariableData.variableNames.ElementAt(Index);
                    //	TempTag += "<a href=\"#\"";
                    //	//;//Link to EventName here
                    //	TempTag += "variableNames_";
                    //	TempTag += StringFunctions.DoubleToStringConversion(Index);
                    //	TempTag += "\" title=\"";
                    //	//Mouse-Over Text of EventName
                    //	TempTag += NameTemp;
                    //	TempTag += "\">";
                    //	TempTag += TagContent;
                    //	TempTag += "</a>";
                    //	break;
                    //}
                    case 252:
                        {
                            TempTag += "<a href=\"#\"";
                            TempTag += TagContent;
                            TempTag += "\">";
                            TempTag += TagContent;
                            TempTag += "</a>";
                            break;
                        }
                    default:
                        {
                            TempTag += TagContent;
                            TempTag += "<br>"; OutputBuffer.Add(TempTag);
                            break;
                        }
                }
            }
            else
            {
                if (!((TagContentType >= 1 && TagContentType <= 14) || TagContentType == 252))
                {//Don't Separate line for known single-line Tags
                    TempTag += TagContent;
                    TempTag += "<br>"; OutputBuffer.Add(TempTag);
                }
            }
            //}
            return OutputBuffer;
        }

        //************************************
        // Method:    GenerateHTMLDocWithin
        // FullName:  TagNodeTreeTemplateData::Node::GenerateHTMLDocWithin
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: NodeTreeType * NodeTreeTarget
        // Parameter: StringVectorList & OutputBuffer
        // Parameter: int & OutputLvl
        // Parameter: const byte & GenerationOptions
        //************************************
        private StringList GenerateHTMLDocWithin(StringList OutputBuffer, int TargetBhvNum = 0, int GenerationOptions = 0)
        {
            OutputBuffer = GenerateHTMLDoc(OutputBuffer, TargetBhvNum, GenerationOptions);
            int ChildListSize = this.NodeLists.Count;
            for (int Index = 0; Index < ChildListSize; ++Index)
            {
                OutputBuffer = this.NodeLists[Index].GenerateHTMLDocWithin(OutputBuffer, TargetBhvNum, GenerationOptions);
            }
            return OutputBuffer;
        }

        /// <summary>
        /// Copies the other data from node of type CurrentType
        /// </summary>
        /// <param name="TargetNode">The target node.</param>
        public void CopyOtherDataFromNode(dynamic TargetNode)
        {//(Using Dynamic to prevent compiler errors)
            TagContent = TargetNode.TagContent;
            SelfContainedTag = TargetNode.SelfContainedTag;
            ClosingStatus = TargetNode.ClosingStatus;
            AdditionTagOptions = TargetNode.AdditionTagOptions;
            ConvertedTagContent = TargetNode.ConvertedTagContent;
            TagContentType = TargetNode.TagContentType;
        }

        public XMLNode()
        {
            NodeLists = new List<XMLNode>();
        }
    }

    internal class XMLTagTree : NodeTreeV2<XMLNode>
    {
    }
}