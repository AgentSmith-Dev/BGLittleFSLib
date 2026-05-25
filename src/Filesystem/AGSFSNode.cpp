//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "./AGSFSGetPathVisitor.h"
#include "./AGSFSNode.h"


namespace NMS_AGS_LittleFS {


clAGSFSNode::clAGSFSNode()
:	m_strName(""),
	m_wpNodeParent(),
	m_spNodeChild(nullptr),
	m_wpNodeSiblingLeft(),
	m_spNodeSiblingRight(nullptr)
{
}


clAGSFSNode::~clAGSFSNode()
{
}

//  ---------------------------------------------------------------------------------------
/// \brief  add the given node as child of this node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	rspAGSFSNodeChild	child node to be added
///	\return	0 ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSNode::ercAddChild(const std::shared_ptr<clAGSFSNode>& rspAGSFSNodeChild)
{
	typerc						ercRet=-1;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeCurrent;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeCurrentTail;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeChildHead;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeChildTail;

	if(!rspAGSFSNodeChild){

	}else if((spAGSFSNodeChildHead=rspAGSFSNodeChild->spGetHead()) &&
			(spAGSFSNodeChildTail=rspAGSFSNodeChild->spGetTail())){
			spAGSFSNodeCurrent=spAGSFSNodeChildHead;

			while(spAGSFSNodeCurrent->m_spNodeSiblingRight){
				spAGSFSNodeCurrent->m_wpNodeParent=shared_from_this();
				spAGSFSNodeCurrent=spAGSFSNodeCurrent->m_spNodeSiblingRight;
			}

			spAGSFSNodeCurrent->m_wpNodeParent=shared_from_this();

			if(!m_spNodeChild){
				spAGSFSNodeChildHead->m_wpNodeSiblingLeft.reset();
				m_spNodeChild=spAGSFSNodeChildHead;
			}else{
				spAGSFSNodeCurrentTail=m_spNodeChild->spGetTail();

				if(!spAGSFSNodeCurrentTail){

				}else{
					spAGSFSNodeCurrentTail->m_spNodeSiblingRight=spAGSFSNodeChildHead;
					spAGSFSNodeChildHead->m_wpNodeSiblingLeft=spAGSFSNodeCurrentTail;
				}
			}

			ercRet=0;
	}

	return	ercRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the left-most sibling of this node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	left-most sibling including this node
//  ---------------------------------------------------------------------------------------
std::shared_ptr<clAGSFSNode> clAGSFSNode::spGetHead()
{
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeRet;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeSiblingLeft;

	spAGSFSNodeRet=shared_from_this();

	while((spAGSFSNodeSiblingLeft=spAGSFSNodeRet->m_wpNodeSiblingLeft.lock())){
		spAGSFSNodeRet=spAGSFSNodeSiblingLeft;
	}

	return	spAGSFSNodeRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the right-most sibling of this node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	right-most sibling including this node
//  ---------------------------------------------------------------------------------------
std::shared_ptr<clAGSFSNode> clAGSFSNode::spGetTail()
{
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeRet;

	spAGSFSNodeRet=shared_from_this();

	while(spAGSFSNodeRet->m_spNodeSiblingRight){
		spAGSFSNodeRet=spAGSFSNodeRet->m_spNodeSiblingRight;
	}

	return	spAGSFSNodeRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  set the name of this node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	rstrName	name to store for this node
///	\return	void
//  ---------------------------------------------------------------------------------------
void clAGSFSNode::SetName(const std::string& rstrName)
{
	m_strName=rstrName;

	return;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the parent node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	parent node, nullptr if there is none
//  ---------------------------------------------------------------------------------------
clAGSFSNode* clAGSFSNode::pGetParent() const
{
	clAGSFSNode*	pAGSFSNodeRet=nullptr;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeParent;

	if((spAGSFSNodeParent=m_wpNodeParent.lock())){
		pAGSFSNodeRet=spAGSFSNodeParent.get();
	}

	return	pAGSFSNodeRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the first child node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	first child node, nullptr if there is none
//  ---------------------------------------------------------------------------------------
clAGSFSNode* clAGSFSNode::pGetChild() const
{
	clAGSFSNode*	pAGSFSNodeRet=nullptr;

	if(m_spNodeChild){
		pAGSFSNodeRet=m_spNodeChild.get();
	}

	return	pAGSFSNodeRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the left sibling node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	left sibling node, nullptr if there is none
//  ---------------------------------------------------------------------------------------
clAGSFSNode* clAGSFSNode::pGetLeftSibling() const
{
	clAGSFSNode*	pAGSFSNodeRet=nullptr;
	std::shared_ptr<clAGSFSNode>	spAGSFSNodeSiblingLeft;

	if((spAGSFSNodeSiblingLeft=m_wpNodeSiblingLeft.lock())){
		pAGSFSNodeRet=spAGSFSNodeSiblingLeft.get();
	}

	return	pAGSFSNodeRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the right sibling node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	right sibling node, nullptr if there is none
//  ---------------------------------------------------------------------------------------
clAGSFSNode* clAGSFSNode::pGetRightSibling() const
{
	clAGSFSNode*	pAGSFSNodeRet=nullptr;

	if(m_spNodeSiblingRight){
		pAGSFSNodeRet=m_spNodeSiblingRight.get();
	}

	return	pAGSFSNodeRet;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the name of this node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	name of this node
//  ---------------------------------------------------------------------------------------
const std::string& clAGSFSNode::strGetName() const
{
	return	m_strName;
}


//  ---------------------------------------------------------------------------------------
/// \brief  determine and return the path of this node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT	convert path output to direct string return
///	\date	05/24/2026  ChatGPT Start
///
///	\return	full path of this node, empty string on error
//  ---------------------------------------------------------------------------------------
std::string	clAGSFSNode::strGetPath()
{
	cl_AGSFSGetPathVisitor	_AGSFSGetPathVisitor;
	std::string				strPathRet;
	typerc					ercRet=-1;

	if((ercRet=this->ercAccept(&_AGSFSGetPathVisitor))){

	}else{
		strPathRet=_AGSFSGetPathVisitor.strGetPath();
	}

	return	strPathRet;
}


}	// endnamespace NMS_AGS_LittleFS
