//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#pragma once

#include <string>

#include "./AGSFSNodeVisitor.h"


namespace NMS_AGS_LittleFS {

class clAGSFSNode;

//  ****************************************************************************************************
///  @brief   visitor used to determine the path of a file system node
//  ****************************************************************************************************
class cl_AGSFSGetPathVisitor : public clAGSFSNodeVisitor
{
public:
	cl_AGSFSGetPathVisitor();
	~cl_AGSFSGetPathVisitor() override;

	const	std::string& strGetPath()const;

	virtual typerc ercVisit(clAGSFSDirectory* pAGSFSDirectory) override;
	virtual typerc ercVisit(clAGSFSFile* pAGSFSFile) override;

protected:
	typerc ercVisitNode(clAGSFSNode* pAGSFSNode);

	std::string	m_strPath;
};

}	// endnamespace NMS_AGS_LittleFS
