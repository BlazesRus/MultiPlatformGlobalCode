// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// Code based on https://www.codeproject.com/Articles/9887/CStaticTreeCtrl-A-CStatic-derived-custom-Tree-cont
// Latest Code Release at https://github.com/BlazesRus/MultiPlatformGlobalCode
// ***********************************************************************
#pragma once
#ifndef CustomTreeNode_Header
#define CustomTreeNode_Header

#include "WP_APPDefines.h"

#include "MultiviewPrecompile.h"
#include "ContextMenu.h"
#include "DLG_TreeNodeText.h"
#ifdef BlazesGUICode_UseDictionaryBasedNodes
#include "GlobalCode_IniData/IndexedDictionary.h"
#endif
#include "GlobalCode_IniData/CustomOrderedDictionary.h"

/// <summary>
/// Edited derivable version of CustomTreeControl's Node class <para />(base code from https://www.codeproject.com/Articles/9887/CStaticTreeCtrl-A-CStatic-derived-custom-Tree-cont)
/// <para />NodeCtrl refers to NodeTree holding this class
/// <para />TreeNode refers to derived class's name (for keeping inherited functionality)
/// </summary>
class CustomTreeNode
{
//protected:
//	typedef CustomTreeNode NodeType;
public:
	/// <summary>
	/// This refers to index inside list of button contexts dictionary unless -1 in which case it uses default menu context list
	/// </summary>
	int NBMenuType;
	/// <summary>
	/// Initializes a new instance of the <see cref="CustomTreeNode"/> class.
	/// </summary>
	CustomTreeNode()
	{
		csLabel.Empty();
		rNode.SetRectEmpty();

		bUseDefaultTextColor = TRUE;

		bOpen = TRUE;
//#ifdef BlazesGUICode_UseDictionaryBasedNodes
//		pParent_Key = 18446744073709551615;//Maxed value = NULL
//		pSibling_Key = 18446744073709551615;
//		pChild_Key = 18446744073709551615;
//#else
//		pParent = NULL;
//		pSibling = NULL;
//		pChild = NULL;
//#endif
		NBMenuType = -1;//Use default node context menu options
		crText = RGB(240,240,240);//Default to a off-white grey
	}
	/// <summary>
	/// Initializes a new instance of the <see cref="CustomTreeNode"/> class.
	/// </summary>
	/// <param name="MenuType">Type of the menu.</param>
	CustomTreeNode(int MenuType)
	{
		csLabel.Empty();
		rNode.SetRectEmpty();

		bUseDefaultTextColor = TRUE;

		bOpen = TRUE;
//#ifdef BlazesGUICode_UseDictionaryBasedNodes
//		pParent_Key = 18446744073709551615;
//		pSibling_Key = 18446744073709551615;
//		pChild_Key = 18446744073709551615;
//#else
//		pParent = NULL;
//		pSibling = NULL;
//		pChild = NULL;
//#endif
		NBMenuType = MenuType;//Use non-default node context menu defined inside a (List<CustomOrderedDictionary<string, ButtonContextData>>)? or defined in override function in CustomTreeView
		crText = RGB(240, 240, 240);
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="CustomTreeNode"/> class.
	/// </summary>
	virtual ~CustomTreeNode()
	{
		csLabel.Empty();
	}

	/// <summary>
	/// The cs label
	/// </summary>
	CString		csLabel;
	/// <summary>
	/// The r node
	/// </summary>
	CRect		rNode;

	/// <summary>
	/// The cr text
	/// </summary>
	COLORREF	crText;
	/// <summary>
	/// The b use default text color
	/// </summary>
	BOOL		bUseDefaultTextColor;

	/// <summary>
	/// The b open
	/// </summary>
	BOOL    bOpen;
//#ifdef BlazesGUICode_UseDictionaryBasedNodes
//	/// <summary>
//	/// The p parent
//	/// </summary>
//	unsigned __int64 pParent_Key;
//	/// <summary>
//	/// The p sibling
//	/// </summary>
//	unsigned __int64 pSibling_Key;
//	/// <summary>
//	/// The p child
//	/// </summary>
//	unsigned __int64 pChild_Key;
//#else
//	/// <summary>
//	/// The p parent
//	/// </summary>
//	CustomTreeNode* pParent;
//	/// <summary>
//	/// The p sibling
//	/// </summary>
//	CustomTreeNode* pSibling;
//	/// <summary>
//	/// The p child
//	/// </summary>
//	CustomTreeNode* pChild;
//#endif

	/// <summary>
	/// Implements the operator ConvertedType* operator.
	/// </summary>
	/// <returns>The result of the operator.</returns>
	template <typename ConvertedType>
	explicit operator ConvertedType*()
	{
		if (self == nullptr)
		{
			return nullptr;
		}
		else
		{
			return dynamic_cast<ConvertedType*>(self);
		}
	}
};
#endif
