//  ****************************************************************************************************
/// \copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by ChatGPT, 2026
///
//  ****************************************************************************************************

#include "./AGSFSFilename.h"
#include "./AGSFSNodeVisitor.h"


namespace NMS_AGS_LittleFS {


clAGSFSFile::clAGSFSFile()
:	clAGSFSNode(),
	m_ui32FileSize(0)
{
}


clAGSFSFile::~clAGSFSFile()
{
}

//  ---------------------------------------------------------------------------------------
/// \brief  set the file size of this file node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\param	ui32FileSize	file size in bytes
///	\return	void
//  ---------------------------------------------------------------------------------------
void clAGSFSFile::SetFileSize(uint32_t ui32FileSize)
{
	m_ui32FileSize=ui32FileSize;

	return;
}

//  ---------------------------------------------------------------------------------------
/// \brief  return the file size of this file node
/// \author ChatGPT
///	\date	05/25/2026  ChatGPT Start
///
///	\return	file size in bytes
//  ---------------------------------------------------------------------------------------
uint32_t clAGSFSFile::ui32GetFileSize() const
{
	uint32_t	ui32FileSizeRet=0;

	ui32FileSizeRet=m_ui32FileSize;

	return	ui32FileSizeRet;
}


//  ---------------------------------------------------------------------------------------
/// \brief  accept a visitor for this file node
/// \author ChatGPT
///	\date	05/24/2026  ChatGPT Start
///
///	\param	pNodeVisitor	the visitor to be applied to this node
///	\return	0	ok, !0 nok
//  ---------------------------------------------------------------------------------------
typerc clAGSFSFile::ercAccept(clAGSFSNodeVisitor* pNodeVisitor)
{
	typerc	ercRet=-1;

	if(pNodeVisitor==nullptr){

	}else{
		ercRet=pNodeVisitor->ercVisit(this);
	}

	return	ercRet;
}


}	// endnamespace NMS_AGS_LittleFS
