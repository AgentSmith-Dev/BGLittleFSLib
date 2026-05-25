//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#pragma once

#include    "./../../../EBMQTTLib/src/AGS_EBMQTTLib_Defines.h"


namespace NMS_AGS_LittleFS {

class clAGSFSDirectory;
class clAGSFSFile;

//  ****************************************************************************************************
///  @brief   visitor interface for LittleFS nodes
//  ****************************************************************************************************
class clAGSFSNodeVisitor
{
public:
	clAGSFSNodeVisitor();
	virtual ~clAGSFSNodeVisitor();

	virtual typerc ercVisit(clAGSFSDirectory* pAGSFSDirectory)=0;
	virtual typerc ercVisit(clAGSFSFile* pAGSFSFile)=0;
};

}	// endnamespace NMS_AGS_LittleFS
