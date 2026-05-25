//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#pragma once

#include "./AGSFSNode.h"


namespace NMS_AGS_LittleFS {

class clAGSFSNodeVisitor;

//  ****************************************************************************************************
///  @brief   represents a directory node in the LittleFS tree
//  ****************************************************************************************************
class clAGSFSDirectory : public clAGSFSNode
{
public:
	clAGSFSDirectory();
	~clAGSFSDirectory() override;
	virtual typerc ercAccept(clAGSFSNodeVisitor* pNodeVisitor) override;
};

}	// endnamespace NMS_AGS_LittleFS
