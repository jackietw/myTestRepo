/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
#include <src/rtos/alg_plugins/surroundview/include/svCommonDefs.h>
#include <src/include/chains_common.h>
#include <src/include/chains_common_surround_view.h>
#include <src/include/chains_common_osal.h>
#include <src/include/chains_common_srv_calib.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include "chains_issMultCaptIsp2d3dSv_priv.h"
#include "chains_issMultCaptIsp2d3dSv.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enable the LDC slice parameters locally
 *
 *******************************************************************************
*/
//#define LOCAL_LDC_SLICE_PRM

/*******************************************************************************
 *  Global Variables
 *******************************************************************************
 */
static Chain_Common_SRV_mediaObj gSrvMediaObj;

#ifdef LOCAL_LDC_SLICE_PRM
    extern SRV_UC_3D_LDC_SLICE_PRM gLdcSlicePrmNo2d3d;

    static AlgorithmLink_ldcSlicePrm \
    gLdcSlicePrm[SRV_UC_3D_LDC_SLICE_PRM_MAX][ALGLINK_SRV_COMMON_MAX_CAMERAS] =
    {
        /* 0:1 slice with 16x16 block size */
        {
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 1:1 slice with 16x8 block size */
        {
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 2:2 slices with 16x16 and 16x8 block sizes */
        {
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 3:2 slices with 16x16 and 16x4 block sizes */
        {
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 4:1 slice with 16x4 block size */
        {
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 5:2 slices with 16x8 and 16x4 block sizes */
        {
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,400,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                0,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,0,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                288,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 6:3 slices with 16x16, 16x8 and 16x4 block sizes */
        {
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                216,320,320,112,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,400,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                0,216,112,576,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                0,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                216,0,320,112,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,0,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                208,216,112,576,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                288,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },
    };
#endif

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
static Int32 mediaReadLdcViewPointParams(
                chains_issMultCaptIsp2d3dSv_DisplayAppObj *pChainsObj,
                Chain_Common_SRV_mediaObj *pMediaObj,
                AlgorithmLink_SrvCommonViewPointParams *pSrvViewPointsParam,
                System_VideoFrameCompositeBuffer *pVidCompBuf,
                UInt32 numViewPoints,
                UInt32 numCameras,
                UInt32 ldcLutSize)
{
    Int32 retVal;
    UInt32 cnt, idx;
    UInt32 rawMemSize, alignedLdcLutSize, alignedCarImgSize, alignedHeaderSize;
    UInt32 blendTableSize, alignedBlendTableSize;
    AlgorithmLink_SrvCommonViewPointParams *pLocalSrvParams;
    System_VideoFrameCompositeBuffer *pLocalVidCompBuf;
    UInt32 start,end;
    UInt32 readSkipSize;
    UInt32 idxBufPtr, viewPointDataSize;

    start = Utils_getCurTimeInMsec();

    for (cnt = 0; cnt < numViewPoints; cnt ++)
    {
        if (1U == cnt)
        {
            /*
             *  Start the SRV use case when the first view point parameters are
             *  available
             */
            BspOsal_semPost(pChainsObj->startSrvDemo);
        }

        if (0U == (cnt % 5U))
        {
            Vps_printf(" SRV_MEDIA: Reading LDC LUT for view point %d ...\n",cnt);
        }

        pLocalSrvParams = pSrvViewPointsParam + cnt;
        pLocalVidCompBuf = pVidCompBuf + cnt;

        pLocalSrvParams->pCompBuf = pLocalVidCompBuf;

        /* DSP will use this CAR Image, hence aliging on 128 boundary */
        blendTableSize = \
            (SRV_OUTPUT_WIDTH_TDA3X_3D_LDC * SRV_OUTPUT_HEIGHT_TDA3X_3D_LDC);
        alignedBlendTableSize = SystemUtils_align(blendTableSize, 128U);

        alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);
        alignedHeaderSize = SystemUtils_align(SRV_MEDIA_SIZE_HEADER, 128U);

        /*
         *  Get the View point data size from the index buffer
         */
        idxBufPtr = (cnt * 2) + (SRV_MEDIA_SIZE_METADATA >> 2);
        viewPointDataSize = *(pMediaObj->idxBuf + idxBufPtr + 1);

        /* Max size */
        if (TRUE == pChainsObj->useUserBlendTable3DLDC)
        {
            rawMemSize = viewPointDataSize;
            readSkipSize = 0U;
        }
        else
        {
            rawMemSize = viewPointDataSize - alignedBlendTableSize;
            readSkipSize = alignedBlendTableSize;
        }

        pLocalSrvParams->baseBufAddr =
                        ChainsCommon_Osal_memAlloc( rawMemSize, 128U);
        pMediaObj->srvBufSize[cnt] = rawMemSize;

        retVal = Chain_Common_SRV_mediaReadBlock(
                                            pMediaObj,
                                            pLocalSrvParams,
                                            cnt,
                                            readSkipSize,
                                            SRV_MEDIA_FILE_LUT);
        if (SYSTEM_LINK_STATUS_SOK == retVal)
        {
            alignedCarImgSize = pLocalSrvParams->sizeOfcarImg;

            pLocalSrvParams->carImgPtr = (UInt32 *)
                    ((UInt32)pLocalSrvParams->baseBufAddr + alignedHeaderSize);

            for (idx = 0; idx < numCameras; idx++)
            {
                pLocalVidCompBuf->metaBufAddr[idx] = (Void*)
                    ((UInt32) pLocalSrvParams->baseBufAddr + alignedHeaderSize
                        + alignedCarImgSize + (alignedLdcLutSize * idx));
            }

            pLocalVidCompBuf->numFrames = numCameras;

            if (TRUE == pChainsObj->useUserBlendTable3DLDC)
            {
                pLocalSrvParams->blendTableAddr = (Void*)
                    ((UInt32) pLocalSrvParams->baseBufAddr + alignedHeaderSize
                    + alignedCarImgSize + (alignedLdcLutSize * numCameras));
            }
            else
            {
                pLocalSrvParams->blendTableAddr = NULL;
            }
        }

        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

#ifdef LOCAL_LDC_SLICE_PRM
        memcpy(
            &pLocalSrvParams->slicePrm,
            &gLdcSlicePrm[gLdcSlicePrmNo2d3d],
            sizeof(AlgorithmLink_ldcSlicePrm) * ALGLINK_SRV_COMMON_MAX_CAMERAS);
#endif
    }

    end = Utils_getCurTimeInMsec();

    Vps_printf(" SRV_MEDIA: Time taken to read %d view point data = %d msec\n",
               numViewPoints, (end - start));

    return retVal;
}

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Void chains_issMultCaptIsp2d3dSv_MediaTask(UArg arg1, UArg arg2)
{
    UInt32 lineOffset, ldcLutSize;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    chains_issMultCaptIsp2d3dSv_DisplayAppObj *pChainsObj;

    UTILS_COMPILETIME_ASSERT (SRV_MEDIA_SIZE_HEADER >= \
                                sizeof(AlgorithmLink_SrvCommonViewPointParams));

    pChainsObj = (chains_issMultCaptIsp2d3dSv_DisplayAppObj *)arg1;
    UTILS_assert(NULL != pChainsObj);

    lineOffset = (SRV_UC_3D_LDC_OUTPUT_WIDTH_MAX /
                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((SRV_UC_3D_LDC_OUTPUT_HEIGHT_MAX /
                                (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                + 1U);

    status = Chain_Common_SRV_mediaInit(
                                &gSrvMediaObj,
                                &pChainsObj->lutIdxFilePresent,
                                &pChainsObj->v2WIdxFilePresent,
                                &pChainsObj->numViewPoints,
                                SRV_MEDIA_FILE_LUT);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    UTILS_assert((TRUE == pChainsObj->lutIdxFilePresent) ||
                 (TRUE == pChainsObj->v2WIdxFilePresent));

    while (SYSTEM_LINK_STATUS_SOK == status)
    {
        if(pChainsObj->lutIdxFilePresent == TRUE)
        {
            /*
             *  The LDC LUT are available in the file therefore allocate the
             *  buffers and read the LUTs.
             */
            status = mediaReadLdcViewPointParams(
                                        pChainsObj,
                                        &gSrvMediaObj,
                                        &pChainsObj->algViewParams[0U],
                                        &pChainsObj->ldcMeshTableContainer[0U],
                                        pChainsObj->numViewPoints,
                                        SRV_UC_3D_NUM_CAMERAS,
                                        ldcLutSize);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }

        if(pChainsObj->lutIdxFilePresent == TRUE)
        {
            pChainsObj->freeToSwitch = TRUE;
        }

        break;
    }

    Chain_Common_SRV_mediaDeinit(&gSrvMediaObj);
}

Int32 chains_issMultCaptIsp2d3dSv_FreeBufs(
                chains_issMultCaptIsp2d3dSv_DisplayAppObj *pChainsObj)
{
    UInt32 cnt;
    Chain_Common_SRV_mediaObj *pMediaObj = &gSrvMediaObj;

    for(cnt = 0;cnt < pChainsObj->numViewPoints;cnt ++)
    {
        if(pChainsObj->algViewParams[cnt].baseBufAddr != NULL)
        {
            ChainsCommon_Osal_memFree(
                                    pChainsObj->algViewParams[cnt].baseBufAddr,
                                    pMediaObj->srvBufSize[cnt]);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}
