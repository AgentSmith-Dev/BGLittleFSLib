//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#pragma once

#include <memory>
#include <string>

//#include    "./../../../../EBMQTTLib/src/AGS_EBMQTTLib_Defines.h"
#include    "./EBMQTTLib/src/AGS_EBMQTTLib_Defines.h"


namespace NMS_AGS_LittleFS {

class clAGSFSNodeVisitor;

//  ****************************************************************************************************
///  @brief   represents one node in the LittleFS tree with child and sibling relations
//  ****************************************************************************************************
class clAGSFSNode : public std::enable_shared_from_this<clAGSFSNode>
{
public:
	clAGSFSNode();
	virtual ~clAGSFSNode();

	typerc ercAddChild(const std::shared_ptr<clAGSFSNode>& rspAGSFSNodeChild);
	std::shared_ptr<clAGSFSNode> spGetHead();
	std::shared_ptr<clAGSFSNode> spGetTail();
	void SetName(const std::string& rstrName);
	clAGSFSNode* pGetParent() const;
	clAGSFSNode* pGetChild() const;
	clAGSFSNode* pGetLeftSibling() const;
	clAGSFSNode* pGetRightSibling() const;
	const std::string& strGetName() const;

	std::string	strGetPath();
	virtual	typerc	ercAccept(clAGSFSNodeVisitor* pNodeVisitor)=0;

protected:
	std::string						m_strName;
	std::weak_ptr<clAGSFSNode>		m_wpNodeParent;
	std::shared_ptr<clAGSFSNode>	m_spNodeChild;
	std::weak_ptr<clAGSFSNode>		m_wpNodeSiblingLeft;
	std::shared_ptr<clAGSFSNode>	m_spNodeSiblingRight;
};

}	// endnamespace NMS_AGS_LittleFS
