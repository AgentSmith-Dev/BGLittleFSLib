//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "./AGSFSDirectory.h"
#include "./AGSFSFilename.h"
#include "./_AGSFSGetPathVisitor.h"
#include "./AGSFSNode.h"


namespace NMS_AGS_LittleFS {


cl_AGSFSGetPathVisitor::cl_AGSFSGetPathVisitor()
:	m_strPath("")
{
}


cl_AGSFSGetPathVisitor::~cl_AGSFSGetPathVisitor()
{
}


//  ---------------------------------------------------------------------------------------
/// \brief  return the path collected by previous visitor calls
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT	adjust documentation to explicit accept workflow
///	\date	05/25/2026  ChatGPT	convert path output to direct string return
///	\date	05/24/2026  ChatGPT Start
///
///	\return	collected path, empty string if no path was collected
//  ---------------------------------------------------------------------------------------
const	std::string& cl_AGSFSGetPathVisitor::strGetPath()const
{
	return	m_strPath;
}

//  ---------------------------------------------------------------------------------------
/// \brief  prepend one node name to the current path and continue with its parent
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	pAGSFSNode	the current node to append to the full path
///	\return	0	ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc cl_AGSFSGetPathVisitor::ercVisitNode(clAGSFSNode* pAGSFSNode)
{
	typerc			ercRet=-1;
	clAGSFSNode*	pAGSFSNodeParent=nullptr;
	std::string		strNodeName;

	if(pAGSFSNode==nullptr){

	}else{
		strNodeName=pAGSFSNode->strGetName();

		if(strNodeName.empty() || (strNodeName=="/")){
			if(m_strPath.empty()){
				m_strPath="/";
			}else{
				m_strPath="/"+m_strPath;
			}
		}else{
			if(m_strPath.empty()){
				m_strPath=strNodeName;
			}else{
				m_strPath=strNodeName+"/"+m_strPath;
			}
		}

		if((pAGSFSNodeParent=pAGSFSNode->pGetParent())==nullptr){
			ercRet=0;
		}else{
			ercRet=pAGSFSNodeParent->ercAccept(this);
		}
	}

	return	ercRet;
}


//  ---------------------------------------------------------------------------------------
/// \brief  visit a directory node while determining its path
/// \author ChatGPT
///	\date	05/24/2026  ChatGPT Start
///
///	\param	pAGSFSDirectory	the directory node to visit
///	\return	0	ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc cl_AGSFSGetPathVisitor::ercVisit(clAGSFSDirectory* pAGSFSDirectory)
{
	typerc	ercRet=-1;

	ercRet=ercVisitNode(pAGSFSDirectory);

	return	ercRet;
}


//  ---------------------------------------------------------------------------------------
/// \brief  visit a file node while determining its path
/// \author ChatGPT
///	\date	05/24/2026  ChatGPT Start
///
///	\param	pAGSFSFile	the file node to visit
///	\return	0	ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc cl_AGSFSGetPathVisitor::ercVisit(clAGSFSFile* pAGSFSFile)
{
	typerc	ercRet=-1;

	ercRet=ercVisitNode(pAGSFSFile);

	return	ercRet;
}


}	// endnamespace NMS_AGS_LittleFS
