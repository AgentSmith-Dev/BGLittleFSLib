#pragma once

#include <memory>
#include <string>

#include	"./ThirdParty/littlefs/lfs.h"

#include    "./EBMQTTLib/src/AGS_EBMQTTLib_Defines.h"


namespace NMS_AGS_LittleFS {

class clAGSFSDirectory;

//  ****************************************************************************************************
/*!	@brief   C++ wrapper class for LittleFS
 */
//  ****************************************************************************************************
class	clAGS_LittleFS
{
public:
	clAGS_LittleFS();
	~clAGS_LittleFS();

	typerc  ercInit();

	typerc  ercMountFileSystem();
	typerc  ercReadTree(std::shared_ptr<clAGSFSDirectory> spRootDirectory);

	static	int CB_Read(const struct lfs_config *c, lfs_block_t block,	lfs_off_t   off, void    *buffer,	lfs_size_t  size);
	static	int CB_Prog(const struct	lfs_config *c, lfs_block_t	block,	lfs_off_t off, const	void *buffer, lfs_size_t size);
	static	int CB_Erase(const struct lfs_config *c, lfs_block_t block);
	static	int CB_Sync(const struct lfs_config *c);

	int iRead(const struct lfs_config *c, lfs_block_t block,	lfs_off_t   off, void    *buffer,	lfs_size_t  size);
	int iProg(const struct lfs_config *p_lfsConfig, lfs_block_t ui8NbBlock, lfs_off_t ui16OffsetInBlock, const void *pTargetBuffer, lfs_size_t iNbBytesTobeRead);
	int	iErase(const struct lfs_config *p_lfsConfig, lfs_block_t ui8NbBlock);
	int iSync(const struct lfs_config *p_lfsConfig);

	typerc  ercMkDir(const    char*    pcPath);
	typerc  ercGetNbBytesToRead(uint32_t*   p_ui32NbBytesFileLength, const    char*    pcFileName);
	typerc  ercOpen(lfs_file_t* pLFS_File, const	char*    pcFileName, uint32_t    ui32Flags);
	typerc  ercWrite(lfs_file_t* pLFS_File, void*    pBuffer, uint32_t    ui32NbBytesToWrite);
	typerc  ercRead(lfs_file_t* pLFS_File, void*    pBuffer, uint32_t    ui32NbBytesToRead);
	typerc  ercClose(lfs_file_t* pLFS_File);


protected:
	uint8_t*	m_pBuffer=nullptr;
	lfs_t	m_lfs;
	lfs_config	m_lfs_config;

};

};	//	endnamespace	AGS_Beoge
