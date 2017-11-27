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

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_lvdsVip3dSurroundView_priv.h"
#include <src/hlos/common/chains_common.h>
#include <vivi_srv.h>
#include "../../ti-plugins/include/srv_chain.h"
#ifndef QNX_BUILD
#include <src/hlos/system/system_gbm_allocator.h>
#endif

/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
#define CAPTURE_SENSOR_WIDTH                 (1280)
#define CAPTURE_SENSOR_HEIGHT                (720)
#define SGX3DSRV_OUTPUT_FRAME_WIDTH          (880)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT         (1080)

#define SYNC_DELTA_IN_MSEC                   (16)
#define SYNC_DROP_THRESHOLD_IN_MSEC          (33)

enum synctype {
    LOOSE_SYNC,
    TIGHT_SYNC
};

typedef struct {
    chains_lvdsVip3dSurroundViewObj ucObj;

    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    UInt32  appCtrlLinkId;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32 numLvdsCh;
    AlgorithmLink_SrvOutputModes svOutputMode;
    Bool enableCarOverlayInAlg;
#ifndef QNX_BUILD
    Bool bEglInfoInCreate;
#endif
} Chains_lvdsVip3dSurroundViewAppObj;

Chains_lvdsVip3dSurroundViewAppObj gLvdsVip3dSurroundViewObj;

#ifndef QNX_BUILD
static struct control_srv_egl_ctx chainsEglParams = {
    .get_egl_native_display = gbm_allocator_get_native_display,
    .get_egl_native_buffer = gbm_allocator_get_native_buffer,
    .destroy_egl_native_buffer = gbm_allocator_destroy_native_buffer,
};
#endif

static Void chains_lvdsVip3dSurroundView_SetSgx3DsrvLinkPrms (
                                  Sgx3DsrvLink_CreateParams *prms)
{
    prms->maxOutputHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    prms->maxOutputWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    prms->maxInputHeight = CAPTURE_SENSOR_HEIGHT;
    prms->maxInputWidth = CAPTURE_SENSOR_WIDTH;
    prms->numViews = 1;
    prms->bAnimate = 1;
    prms->numInQue = 4;
    prms->inBufType[0] = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    prms->inBufType[1] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[2] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[3] = SYSTEM_BUFFER_TYPE_METADATA;
#ifndef QNX_BUILD
    prms->bEglInfoInCreate = FALSE;
#endif
    prms->EglInfo = NULL;
}

static Void chains_lvdsVip3dSurroundView_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

Void chains_lvdsVip3dSurroundView_SetAppPrms(
        chains_lvdsVip3dSurroundViewObj *pUcObj, Void *appObj)
{
    EpLink_CreateParams  *pEndp;

    Chains_lvdsVip3dSurroundViewAppObj *pObj
            = (Chains_lvdsVip3dSurroundViewAppObj*)appObj;
    UInt32 svOutWidth, svOutHeight;

    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_OV10635;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = 4;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
            APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
            &pObj->vidSensorPrm,
            sizeof(VideoSensorCreateAndStartAppPrm),
            TRUE);

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    ChainsCommon_MultiCam_SetCapturePrms(
                    &pUcObj->CapturePrm,
                    pObj->numLvdsCh);

    {
        UInt32 i;
        CaptureLink_VipInstParams *pInstPrm;
        for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {
            pInstPrm = &pUcObj->CapturePrm.vipInst[i];
            pInstPrm->numBufs = 5;
            /* skip alternate frame to make it 15fps output for Front camera */
            if (i >= 4)
                pInstPrm->outParams[0].frameSkipMask = 0x2AAAAAAA;
        }
    }

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->svOutputMode,
                                    pObj->enableCarOverlayInAlg);
#ifdef EARLY_SRV_ENABLE
    pUcObj->Alg_SynthesisPrm.earlyCreate = TRUE;
#endif

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlign3DParams(
                                    &pUcObj->Alg_GeoAlign3DPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->svOutputMode);

    chains_lvdsVip3dSurroundView_SetSyncPrm(
                        &pUcObj->SyncPrm,
                        pObj->numLvdsCh
                        );
    chains_lvdsVip3dSurroundView_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

#ifndef QNX_BUILD
    if(pObj->bEglInfoInCreate == TRUE) {
        pUcObj->Sgx3DsrvPrm.bEglInfoInCreate = TRUE;
        pUcObj->Sgx3DsrvPrm.EglInfo = (void *)&chainsEglParams;
        Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView setting bEglInfoCreate = TRUE!\n");
    }
#endif
    /* We have two sink epLinks in the chain; we will configure them now */
    /* sink2 */
    pEndp = &pUcObj->EpSink_3dPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = LVDS_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);

    /* sink1 */
    pEndp = &pUcObj->EpSink_imPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = LVDS_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);
}

Void chains_lvdsVip3dSurroundView_InitApp()
{
    Bool startWithCalibration;
    Chains_lvdsVip3dSurroundViewAppObj *pObj
        = (Chains_lvdsVip3dSurroundViewAppObj*)&gLvdsVip3dSurroundViewObj;

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_InitApp !!!\n");

    /* SRV Algo related initialization */
    pObj->numLvdsCh = 4;
    pObj->svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
    pObj->enableCarOverlayInAlg = 0;
#ifndef QNX_BUILD
    pObj->bEglInfoInCreate = FALSE;
#endif
    /* Set startWithCalibration = TRUE to start the demo with calibration.
       Else it will use the previously calibrated LUTs */
    startWithCalibration = TRUE;
    ChainsCommon_SurroundView_CalibInit(
                                startWithCalibration,
                                pObj->svOutputMode);

    ChainsCommon_statCollectorReset();

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_InitApp DONE !!!\n");
}

Int32 chains_lvdsVip3dSurroundView_CreateApp(struct vivi_sink *sink, struct vivi_source *source)
{
    Int32 status;
    chains_lvdsVip3dSurroundViewObj *pUcObj;
    Chains_lvdsVip3dSurroundViewAppObj *pObj
        = (Chains_lvdsVip3dSurroundViewAppObj*)&gLvdsVip3dSurroundViewObj;

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_CreateApp !!!\n");

    chains_lvdsVip3dSurroundView_InitApp();
#ifndef QNX_BUILD
    pObj->bEglInfoInCreate = sink->bEglInfoInCreate;
#endif
    status = chains_lvdsVip3dSurroundView_Create(&gLvdsVip3dSurroundViewObj.ucObj, &gLvdsVip3dSurroundViewObj);

    /* Let's set the epLink ids now */
    pUcObj = &gLvdsVip3dSurroundViewObj.ucObj;
    sink->eplink_id[0] = pUcObj->EpSink_imLinkID;
    sink->eplink_id[1] = pUcObj->EpSink_3dLinkID;

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_CreateApp DONE !!!\n");
    return status;
}

Int32 chains_lvdsVip3dSurroundView_StartApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_StartApp !!!\n");
    ChainsCommon_memPrintHeapStatus();

    status = chains_lvdsVip3dSurroundView_Start(&gLvdsVip3dSurroundViewObj.ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_StartApp DONE!!!\n");
    return status;
}

Int32 chains_lvdsVip3dSurroundView_StopApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_StopApp !!!\n");
    status = chains_lvdsVip3dSurroundView_Stop(&gLvdsVip3dSurroundViewObj.ucObj);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
            APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
            &gLvdsVip3dSurroundViewObj.vidSensorPrm,
            sizeof(VideoSensorCreateAndStartAppPrm),
            TRUE);

    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_StopApp DONE!!!\n");
    return status;
}

Int32 chains_lvdsVip3dSurroundView_DeleteApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_DeleteApp !!!\n");

    status = chains_lvdsVip3dSurroundView_Delete(&gLvdsVip3dSurroundViewObj.ucObj);

    ChainsCommon_SurroundView_CalibDeInit();

    Vps_printf(" CHAIN: chains_lvdsVip3dSurroundView_DeleteApp DONE!!!\n");
    return status;
}

Int32 chains_lvdsVip3dSurroundView_PauseApp()
{
    Int32 status;
    chains_lvdsVip3dSurroundViewObj *pObj = &gLvdsVip3dSurroundViewObj.ucObj;

    status = System_linkStop(pObj->CaptureLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Int32 chains_lvdsVip3dSurroundView_ResumeApp()
{
    Int32 status;
    chains_lvdsVip3dSurroundViewObj *pObj = &gLvdsVip3dSurroundViewObj.ucObj;

    status = System_linkStart(pObj->CaptureLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Void chains_lvdsVip3dSurroundView_CalibApp()
{
    ChainsCommon_SurroundView_MenuCalibration();
}

Void chains_lvdsVip3dSurroundView_StatApp()
{
    chains_lvdsVip3dSurroundView_printStatistics(&gLvdsVip3dSurroundViewObj.ucObj);
    ChainsCommon_memPrintHeapStatus();
}