//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#pragma once

#include <string>
#include <vector>

#include "./AGSFSNodeVisitor.h"


namespace NMS_AGS_LittleFS {

class clAGSFSNode;

//  ****************************************************************************************************
///  @brief   visitor used to create an ASCII tree representation of a LittleFS node tree
//  ****************************************************************************************************
class clAGSFSTreeVisitor : public clAGSFSNodeVisitor
{
public:
	clAGSFSTreeVisitor();
	~clAGSFSTreeVisitor() override;

	typerc ercCreateTree(clAGSFSNode* pAGSFSNodeRoot, std::string* pstrTree);
	const std::string& strGetTree() const;

	virtual typerc ercVisit(clAGSFSDirectory* pAGSFSDirectory) override;
	virtual typerc ercVisit(clAGSFSFile* pAGSFSFile) override;

protected:
	typerc ercAppendNodeLine(const std::string& rstrNodeText);
	typerc ercVisitNode(clAGSFSNode* pAGSFSNode);

	std::string			m_strTree;
	std::vector<bool>	m_vecbHasMoreSiblings;
};

}	// endnamespace NMS_AGS_LittleFS
