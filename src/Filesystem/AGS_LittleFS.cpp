// *******************************************************************************
//!<@copyright  Agent Smith, Dresden Germany
//!             www.agent-smith.dev
//
//  Initial code by ChatGPT, 2026
//
//  *******************************************************************************
/*
 * AGS_LittleFS.cpp
 *
 *  Created on: 05/16/2026
 *      Author: ChatGPT
 */

#include <iostream>
#include <cstdlib>

#include    "./EBMQTTLib/src/AGS_Helper.h"

#include	"./AGSFSDirectory.h"
#include	"./AGSFSFilename.h"
#include    "./AGSFSGetPathVisitor.h"

#include	"./AGS_LittleFS.h"

constexpr   uint16_t ui16BlockSize=4096;
constexpr   uint16_t ui16NbBlocks=1024;


namespace	NMS_AGS_LittleFS
{

using namespace std;


clAGS_LittleFS::clAGS_LittleFS()
:	m_pBuffer(nullptr),
    m_lfs{},
    m_lfs_config{}
{
    m_lfs_config={
        .context    =   (void*)this,
        .read   =   &clAGS_LittleFS::CB_Read,
        .prog   =   &clAGS_LittleFS::CB_Prog,
        .erase  =   &clAGS_LittleFS::CB_Erase,
        .sync   =   &clAGS_LittleFS::CB_Sync,

    // block device configuration
    .read_size = 16,
    .prog_size = 16,
    .block_size = ui16BlockSize,
    .block_count = ui16NbBlocks,
    .block_cycles = 500,
    .cache_size = 16,
    .lookahead_size = 16,


    };
}

clAGS_LittleFS::~clAGS_LittleFS()
{
    if(m_pBuffer){
        free(m_pBuffer);
        m_pBuffer=nullptr;
    }   //  endif(m_pBuffer){
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	mount the file system - create it (new PCB) it it does not exist (yet)
*	@date   05/16/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercInit()
{
    int iErr;
    typerc  ercRet=-1;

    if((m_pBuffer=(uint8_t*)malloc(ui16BlockSize*ui16NbBlocks))==nullptr){
        //  error

    }else{
        //  ok
        memset((void*)m_pBuffer, 0xff, ui16BlockSize*ui16NbBlocks);

        ercRet=0;

    }   //  endif(    (m_pBuffer=malloc(4*1024*1024)==nullptr){

    return  ercRet;
}



//  ---------------------------------------------------------------------------------------
/*!	@brief	mount the file system - create it (new PCB) it it does not exist (yet)
*	@date   05/16/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercMountFileSystem()
{
    int iErr;
    typerc  ercRet=-1;

    cout    <<  "entering ercMountFileSystem()" <<  endl;

    if(!m_pBuffer){
        //  no buffer

    }else   if((iErr=lfs_mount(&m_lfs, &m_lfs_config))){
        //  error mounting -> this usually only happens on the first boot
        //  -> reformat

        cout    <<  "formatting filesystem()" <<  endl;

        lfs_format(&m_lfs, &m_lfs_config);
        iErr=lfs_mount(&m_lfs, &m_lfs_config);
    }

    if(iErr){
        //  major error!
    }else{
        cout    <<  "mounting ok" <<  endl;

        ercRet=ercRet_OK;
    }   //  endif(iErr){


    return  ercRet;
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	read the complete directory tree from LittleFS into the given root directory object
*	@date   05/24/2026  ChatGPT Start
*	@param  spRootDirectory    shared pointer to the root directory node
*	@return	0 ok, !0 nok
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercReadTree(std::shared_ptr<clAGSFSDirectory> spRootDirectory)
{
    typerc                  ercRet=-1;
    cl_AGSFSGetPathVisitor   _AGSFSGetPathVisitor;
    std::string             strPath;
    lfs_dir_t               _lfs_dir;
    int                     iErr=0;
    int                     iErrClose=0;
    bool                    bDirOpen=false;

    if(!spRootDirectory){

    }else   if(spRootDirectory->ercAccept(&_AGSFSGetPathVisitor)){

    }else   if((strPath=_AGSFSGetPathVisitor.strGetPath()).empty()){

    }else   if((iErr=lfs_dir_open(&m_lfs, &_lfs_dir, strPath.c_str()))){

    }else{
        lfs_info                _lfs_info;
        bDirOpen=true;
        ercRet=0;

        while((iErr=lfs_dir_read(&m_lfs, &_lfs_dir, &_lfs_info))>0){
            if((_lfs_info.name[0]=='\0') ||
                (strcmp(_lfs_info.name, ".")==0) ||
                (strcmp(_lfs_info.name, "..")==0)){

            }else   if(_lfs_info.type==LFS_TYPE_DIR){
                std::shared_ptr<clAGSFSDirectory>  spAGSFSDirectory;
                spAGSFSDirectory=std::make_shared<clAGSFSDirectory>();

                if(!spAGSFSDirectory){
                    ercRet=-1;
                    iErr=-1;
                }else{
                    spAGSFSDirectory->SetName(_lfs_info.name);

                    if((ercRet=spRootDirectory->ercAddChild(spAGSFSDirectory))){
                        iErr=-1;
                    }else   if((ercRet=ercReadTree(spAGSFSDirectory))){
                        iErr=-1;
                    }
                }
            }else   if(_lfs_info.type==LFS_TYPE_REG){
                std::shared_ptr<clAGSFSFile>       spAGSFSFile;
                spAGSFSFile=std::make_shared<clAGSFSFile>();

                if(!spAGSFSFile){
                    ercRet=-1;
                    iErr=-1;
                }else{
                    spAGSFSFile->SetName(_lfs_info.name);
                    spAGSFSFile->SetFileSize(_lfs_info.size);

                    if((ercRet=spRootDirectory->ercAddChild(spAGSFSFile))){
                        iErr=-1;
                    }
                }
            }else{

            }   //endif((_lfs_info.name[0]=='\0') ||

            if(iErr<0){
                break;
            }

        }   //  endwhile((iErr=lfs_dir_read(&m_lfs, &_lfs_dir, &_lfs_info))>0){

        if(iErr<0){
            ercRet=-1;
        }
    }

    if(!bDirOpen){
    }else if((iErrClose=lfs_dir_close(&m_lfs, &_lfs_dir))){
        (void)iErrClose;
        ercRet=-1;
    }   //  endif(!bDirOpen){

    return  ercRet;
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	
*
*       Read a region in a block. Negative error codes are propagated
*       to the user.
*
*	@date   05/16/2026  AGS Start
*	@param  p_lfsConfig ptr to LittleFS configuration
*   @param  ui8NbBlock  Number of the physical block
*/
//  ---------------------------------------------------------------------------------------
int clAGS_LittleFS::CB_Read(const struct lfs_config *p_lfsConfig, 
                                        lfs_block_t ui8NbBlock,
                                        lfs_off_t   ui16OffsetInBlock, 
                                            void    *pTargetBuffer,
                                        lfs_size_t  iNbBytesTobeRead)
{
    clAGS_LittleFS* pThis=(clAGS_LittleFS*)p_lfsConfig->context;

    return  pThis->iRead(p_lfsConfig, ui8NbBlock, ui16OffsetInBlock, pTargetBuffer, iNbBytesTobeRead);
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	
*
*   Program a region in a block. The block must have previously
*   been erased (=bytes have to be set to 0xff). Negative error codes are propagated to the user.
*   May return LFS_ERR_CORRUPT if the block should be considered bad.
*
*   Wichtig: bits er only erased (1->0). They are NEVER being set in this function (NO 0->1).
*   Therefore the memory has to be erased before (filled with 0xff).
*
*	@date   05/16/2026  AGS Start
*	@param  ui8NbBlock  nb of block to be programmed
*   @param  ui16OffsetInBlock   offset where to start in the block
*   @param  pSourceBuffer   buffer with bytes to program
*   @param  iNbBytesTobeProg    number of bytes to be programmed
*/
//  ---------------------------------------------------------------------------------------
int clAGS_LittleFS::CB_Prog(const struct lfs_config *p_lfsConfig, lfs_block_t ui8NbBlock,
            lfs_off_t ui16OffsetInBlock, const void *pSourceBuffer, lfs_size_t iNbBytesTobeProg)
{
    clAGS_LittleFS* pThis=(clAGS_LittleFS*)p_lfsConfig->context;
    return  pThis->iProg(p_lfsConfig, ui8NbBlock, ui16OffsetInBlock, pSourceBuffer, iNbBytesTobeProg);
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	
*
// Erase a block. A block must be erased before being programmed.
    // The state of an erased block is undefined. Negative error codes
    // are propagated to the user.
    // May return LFS_ERR_CORRUPT if the block should be considered bad.
*
*	@date   05/16/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
int clAGS_LittleFS::CB_Erase(const struct lfs_config *p_lfsConfig, lfs_block_t ui8NbBlock)
{
    clAGS_LittleFS* pThis=(clAGS_LittleFS*)p_lfsConfig->context;

    return  pThis->iErase(p_lfsConfig, ui8NbBlock);
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	
*
*       Sync the state of the underlying block device. Negative error codes
*       are propagated to the user.
*
*	@date   05/16/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
int clAGS_LittleFS::CB_Sync(const struct lfs_config *c)
{
    clAGS_LittleFS* pThis=(clAGS_LittleFS*)c->context;

    return  pThis->iSync(c);
}





//  ---------------------------------------------------------------------------------------
/*!	@brief	make a directory
*	@date   05/24/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercMkDir(const    char*    pcPath)
{
    typerc  ercRet=-1;

    lfs_info _lfs_info;

    int iErr;
    if((iErr=lfs_mkdir(&m_lfs, pcPath))){

    }else{

        ercRet=0;
    }   //  enddif((iErr=lfs_file_open())){s

    return  ercRet;
}




//  ---------------------------------------------------------------------------------------
/*!	@brief	open a file
*	@date   05/24/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercGetNbBytesToRead(uint32_t*   p_ui32NbBytesFileLength, const    char*    pcFileName)
{
    typerc  ercRet=-1;

    lfs_info _lfs_info;

    int iErr;
    if((iErr=lfs_stat(&m_lfs, pcFileName, &_lfs_info))){

    }else{
        *p_ui32NbBytesFileLength=_lfs_info.size;

        ercRet=0;
    }   //  enddif((iErr=lfs_file_open())){s

    return  ercRet;
}


//  ---------------------------------------------------------------------------------------
/*!	@brief	open a file
*	@date   05/24/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercOpen(lfs_file_t* pLFS_File, const    char*    pcFileName, uint32_t    ui32Flags)
{
    typerc  ercRet=-1;

    int iErr;
    if((iErr=lfs_file_open(&m_lfs, pLFS_File, pcFileName, ui32Flags))){

    }else{
        ercRet=0;
    }   //  enddif((iErr=lfs_file_open())){s

    return  ercRet;
}

//  ---------------------------------------------------------------------------------------
/*!	@brief	write into a file
*	@date   05/24/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercWrite(lfs_file_t* pLFS_File, void*    pBuffer, uint32_t    ui32NbBytesToWrite)
{
    typerc  ercRet=-1;

    lfs_ssize_t  _lfs_ssize_t;
    if((_lfs_ssize_t=lfs_file_write(&m_lfs, pLFS_File, pBuffer, (lfs_size_t)ui32NbBytesToWrite))!=ui32NbBytesToWrite){

    }else{
        ercRet=0;
    }   //  enddif((iErr=lfs_file_write())){s

    return  ercRet;
}


//  ---------------------------------------------------------------------------------------
/*!	@brief	read from a file
*	@date   05/24/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercRead(lfs_file_t* pLFS_File, void*    pBuffer, uint32_t    ui32NbBytesToRead)
{
    typerc  ercRet=-1;

    lfs_ssize_t iNbBytesRead;
    if((iNbBytesRead=lfs_file_read(&m_lfs, pLFS_File, pBuffer, (lfs_size_t)ui32NbBytesToRead))!=ui32NbBytesToRead){

    }else{
        ercRet=0;
    }   //  enddif((iErr=lfs_file_write())){s

    return  ercRet;
}



//  ---------------------------------------------------------------------------------------
/*!	@brief	close a file
*	@date   05/24/2026  AGS Start
*	@param
*/
//  ---------------------------------------------------------------------------------------
typerc  clAGS_LittleFS::ercClose(lfs_file_t* pLFS_File)
{
    typerc  ercRet=-1;

    int iErr;
 
    //  Optional: explizit flushen
    if((iErr=lfs_file_sync(&m_lfs, pLFS_File))){
        //  error

    }else if((iErr=lfs_file_close(&m_lfs, pLFS_File))){
        //  error

    }else{
        ercRet=0;
    }   //  enddif((iErr=lfs_file_write())){s

    return  ercRet;
}



/*
    // Read a region in a block. Negative error codes are propagated
    // to the user.
    int (*read)(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, void *buffer, lfs_size_t size);

    // Program a region in a block. The block must have previously
    // been erased. Negative error codes are propagated to the user.
    // May return LFS_ERR_CORRUPT if the block should be considered bad.
    int (*prog)(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, const void *buffer, lfs_size_t size);

    // Erase a block. A block must be erased before being programmed.
    // The state of an erased block is undefined. Negative error codes
    // are propagated to the user.
    // May return LFS_ERR_CORRUPT if the block should be considered bad.
    int (*erase)(const struct lfs_config *c, lfs_block_t block);

    // Sync the state of the underlying block device. Negative error codes
    // are propagated to the user.
    int (*sync)(const struct lfs_config *c);
*/

};	//	endnamespace	AGS_Beoge
