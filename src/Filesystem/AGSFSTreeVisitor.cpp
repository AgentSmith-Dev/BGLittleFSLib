//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "./AGSFSDirectory.h"
#include "./AGSFSFilename.h"
#include "./AGSFSNode.h"
#include "./AGSFSTreeVisitor.h"


namespace NMS_AGS_LittleFS {


clAGSFSTreeVisitor::clAGSFSTreeVisitor()
:	m_strTree(""),
	m_vecbHasMoreSiblings()
{
}


clAGSFSTreeVisitor::~clAGSFSTreeVisitor()
{
}


//  ---------------------------------------------------------------------------------------
/// \brief  create an ASCII tree representation of the given node tree
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	pAGSFSNodeRoot	root node of the tree to be rendered
///	\param	pstrTree		output buffer for the resulting tree representation
///	\return	0 ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSTreeVisitor::ercCreateTree(clAGSFSNode* pAGSFSNodeRoot, std::string* pstrTree)
{
	typerc	ercRet=-1;

	m_strTree.clear();
	m_vecbHasMoreSiblings.clear();

	if((pAGSFSNodeRoot==nullptr) || (pstrTree==nullptr)){

	}else if((ercRet=pAGSFSNodeRoot->ercAccept(this))){

	}else{
		*pstrTree=m_strTree;
	}

	return	ercRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the previously created ASCII tree
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	tree representation collected by this visitor
//  ---------------------------------------------------------------------------------------
const std::string& clAGSFSTreeVisitor::strGetTree() const
{
	return	m_strTree;
}

//  ---------------------------------------------------------------------------------------
/// \brief  append one formatted node line to the tree output
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	rstrNodeText	node text to be appended to the output
///	\return	0 ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSTreeVisitor::ercAppendNodeLine(const std::string& rstrNodeText)
{
	typerc	ercRet=-1;
	size_t	iIdx=0;

	if(rstrNodeText.empty()){

	}else{
		if(m_vecbHasMoreSiblings.empty()){
			m_strTree+=rstrNodeText;
			m_strTree+="\n";
		}else{
			for(iIdx=0; iIdx+1<m_vecbHasMoreSiblings.size(); iIdx++){
				if(m_vecbHasMoreSiblings[iIdx]){
					m_strTree+="|   ";
				}else{
					m_strTree+="    ";
				}
			}

			if(m_vecbHasMoreSiblings.back()){
				m_strTree+="|-- ";
			}else{
				m_strTree+="`-- ";
			}

			m_strTree+=rstrNodeText;
			m_strTree+="\n";
		}

		ercRet=0;
	}

	return	ercRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  visit the given node and recursively render all of its children
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	pAGSFSNode	node to be rendered
///	\return	0 ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSTreeVisitor::ercVisitNode(clAGSFSNode* pAGSFSNode)
{
	typerc			ercRet=-1;
	clAGSFSNode*	pAGSFSNodeChild=nullptr;
	clAGSFSNode*	pAGSFSNodeNextSibling=nullptr;
	bool			bHasMoreSiblings=false;

	if(pAGSFSNode==nullptr){

	}else if((ercRet=ercAppendNodeLine(pAGSFSNode->strGetName()))){

	}else{
		pAGSFSNodeChild=pAGSFSNode->pGetChild();
		ercRet=0;

		while(pAGSFSNodeChild){
			pAGSFSNodeNextSibling=pAGSFSNodeChild->pGetRightSibling();
			bHasMoreSiblings=(pAGSFSNodeNextSibling!=nullptr);
			m_vecbHasMoreSiblings.push_back(bHasMoreSiblings);
			ercRet=pAGSFSNodeChild->ercAccept(this);
			m_vecbHasMoreSiblings.pop_back();

			if(ercRet){
				pAGSFSNodeChild=nullptr;
			}else{
				pAGSFSNodeChild=pAGSFSNodeNextSibling;
			}
		}
	}

	return	ercRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  visit a directory node while rendering the tree
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	pAGSFSDirectory	directory node to be rendered
///	\return	0 ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSTreeVisitor::ercVisit(clAGSFSDirectory* pAGSFSDirectory)
{
	typerc	ercRet=-1;

	ercRet=ercVisitNode(pAGSFSDirectory);

	return	ercRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  visit a file node while rendering the tree
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	pAGSFSFile	file node to be rendered
///	\return	0 ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSTreeVisitor::ercVisit(clAGSFSFile* pAGSFSFile)
{
	typerc		ercRet=-1;
	std::string	strNodeText;

	if(pAGSFSFile==nullptr){

	}else{
		strNodeText=pAGSFSFile->strGetName()+" ("+std::to_string(pAGSFSFile->ui32GetFileSize())+")";
		ercRet=ercAppendNodeLine(strNodeText);
	}

	return	ercRet;
}


}	// endnamespace NMS_AGS_LittleFS
