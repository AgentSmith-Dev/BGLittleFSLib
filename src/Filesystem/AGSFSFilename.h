//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#pragma once

#include <cstdint>

#include "./AGSFSNode.h"


namespace NMS_AGS_LittleFS {

class clAGSFSNodeVisitor;

//  ****************************************************************************************************
///  @brief   represents a file node in the LittleFS tree
//  ****************************************************************************************************
class clAGSFSFile : public clAGSFSNode
{
public:
	clAGSFSFile();
	~clAGSFSFile() override;
	void SetFileSize(uint32_t ui32FileSize);
	uint32_t ui32GetFileSize() const;
	virtual typerc ercAccept(clAGSFSNodeVisitor* pNodeVisitor) override;

protected:
	uint32_t	m_ui32FileSize;
};

}	// endnamespace NMS_AGS_LittleFS
