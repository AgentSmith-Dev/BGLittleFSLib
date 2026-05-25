//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "./AGSFSDirectory.h"
#include "./AGSFSNodeVisitor.h"


namespace NMS_AGS_LittleFS {


clAGSFSDirectory::clAGSFSDirectory()
:	clAGSFSNode()
{
}


clAGSFSDirectory::~clAGSFSDirectory()
{
}


//  ---------------------------------------------------------------------------------------
/// \brief  accept a visitor for this directory node
/// \author ChatGPT
///	\date	05/24/2026  ChatGPT Start
///
///	\param	pNodeVisitor	the visitor to be applied to this node
///	\return	0	ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSDirectory::ercAccept(clAGSFSNodeVisitor* pNodeVisitor)
{
	typerc	ercRet=-1;

	if(pNodeVisitor==nullptr){

	}else{
		ercRet=pNodeVisitor->ercVisit(this);
	}

	return	ercRet;
}


}	// endnamespace NMS_AGS_LittleFS
