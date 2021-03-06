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

/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/
#include "chains_lvdsVipSingleStereoCalibration_priv.h"
Void chains_lvdsVipSingleStereoCalibration_SetLinkId(chains_lvdsVipSingleStereoCalibrationObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE_0;
       pObj->VPE_captureLinkID              = SYSTEM_LINK_ID_VPE_0;
       pObj->IPCOut_IPU1_0_EVE2_0LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_EVE2_IPU1_0_0LinkID      = EVE2_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_RemapMergeLinkID           = EVE2_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->IPCOut_EVE2_IPU1_0_0LinkID     = EVE2_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_IPU1_0_EVE2_0LinkID      = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->VPE_orgLinkID                  = SYSTEM_LINK_ID_VPE_1;
       pObj->Sync_orgLinkID                 = IPU1_0_LINK (SYSTEM_LINK_ID_SYNC_0);
       pObj->Alg_DmaSwMs_orgLinkID          = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->Display_orgLinkID              = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
}

Void chains_lvdsVipSingleStereoCalibration_ResetLinkPrms(chains_lvdsVipSingleStereoCalibrationObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       VpeLink_CreateParams_Init(&pObj->VPE_capturePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_EVE2_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_EVE2_IPU1_0_0Prm);
       AlgorithmLink_RemapMerge_Init(&pObj->Alg_RemapMergePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_EVE2_IPU1_0_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_IPU1_0_EVE2_0Prm);
       VpeLink_CreateParams_Init(&pObj->VPE_orgPrm);
       SyncLink_CreateParams_Init(&pObj->Sync_orgPrm);
       AlgorithmLink_DmaSwMsCreateParams_Init(&pObj->Alg_DmaSwMs_orgPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_orgPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_lvdsVipSingleStereoCalibration_SetPrms(chains_lvdsVipSingleStereoCalibrationObj *pObj){
       (pObj->Alg_RemapMergePrm).baseClassCreate.size  = sizeof(AlgorithmLink_RemapMergeCreateParams);
       (pObj->Alg_RemapMergePrm).baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_REMAPMERGE;
       (pObj->Alg_DmaSwMs_orgPrm).baseClassCreate.size  = sizeof(AlgorithmLink_DmaSwMsCreateParams);
       (pObj->Alg_DmaSwMs_orgPrm).baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;
}

Void chains_lvdsVipSingleStereoCalibration_ConnectLinks(chains_lvdsVipSingleStereoCalibrationObj *pObj){

       //Capture -> VPE_capture
       pObj->CapturePrm.outQueParams.nextLink = pObj->VPE_captureLinkID;
       pObj->VPE_capturePrm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->VPE_capturePrm.inQueParams.prevLinkQueId = 0;

       //VPE_capture -> IPCOut_IPU1_0_EVE2_0
       pObj->VPE_capturePrm.outQueParams[0].nextLink = pObj->IPCOut_IPU1_0_EVE2_0LinkID;
       pObj->IPCOut_IPU1_0_EVE2_0Prm.inQueParams.prevLinkId = pObj->VPE_captureLinkID;
       pObj->IPCOut_IPU1_0_EVE2_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_IPU1_0_EVE2_0 -> IPCIn_EVE2_IPU1_0_0
       pObj->IPCOut_IPU1_0_EVE2_0Prm.outQueParams.nextLink = pObj->IPCIn_EVE2_IPU1_0_0LinkID;
       pObj->IPCIn_EVE2_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_EVE2_0LinkID;
       pObj->IPCIn_EVE2_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_EVE2_IPU1_0_0 -> Alg_RemapMerge
       pObj->IPCIn_EVE2_IPU1_0_0Prm.outQueParams.nextLink = pObj->Alg_RemapMergeLinkID;
       pObj->Alg_RemapMergePrm.inQueParams.prevLinkId = pObj->IPCIn_EVE2_IPU1_0_0LinkID;
       pObj->Alg_RemapMergePrm.inQueParams.prevLinkQueId = 0;

       //Alg_RemapMerge -> IPCOut_EVE2_IPU1_0_0
       pObj->Alg_RemapMergePrm.outQueParams.nextLink = pObj->IPCOut_EVE2_IPU1_0_0LinkID;
       pObj->IPCOut_EVE2_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->Alg_RemapMergeLinkID;
       pObj->IPCOut_EVE2_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_EVE2_IPU1_0_0 -> IPCIn_IPU1_0_EVE2_0
       pObj->IPCOut_EVE2_IPU1_0_0Prm.outQueParams.nextLink = pObj->IPCIn_IPU1_0_EVE2_0LinkID;
       pObj->IPCIn_IPU1_0_EVE2_0Prm.inQueParams.prevLinkId = pObj->IPCOut_EVE2_IPU1_0_0LinkID;
       pObj->IPCIn_IPU1_0_EVE2_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_IPU1_0_EVE2_0 -> VPE_org
       pObj->IPCIn_IPU1_0_EVE2_0Prm.outQueParams.nextLink = pObj->VPE_orgLinkID;
       pObj->VPE_orgPrm.inQueParams.prevLinkId = pObj->IPCIn_IPU1_0_EVE2_0LinkID;
       pObj->VPE_orgPrm.inQueParams.prevLinkQueId = 0;

       //VPE_org -> Sync_org
       pObj->VPE_orgPrm.outQueParams[0].nextLink = pObj->Sync_orgLinkID;
       pObj->Sync_orgPrm.inQueParams.prevLinkId = pObj->VPE_orgLinkID;
       pObj->Sync_orgPrm.inQueParams.prevLinkQueId = 0;

       //Sync_org -> Alg_DmaSwMs_org
       pObj->Sync_orgPrm.outQueParams.nextLink = pObj->Alg_DmaSwMs_orgLinkID;
       pObj->Alg_DmaSwMs_orgPrm.inQueParams.prevLinkId = pObj->Sync_orgLinkID;
       pObj->Alg_DmaSwMs_orgPrm.inQueParams.prevLinkQueId = 0;

       //Alg_DmaSwMs_org -> Display_org
       pObj->Alg_DmaSwMs_orgPrm.outQueParams.nextLink = pObj->Display_orgLinkID;
       pObj->Display_orgPrm.inQueParams.prevLinkId = pObj->Alg_DmaSwMs_orgLinkID;
       pObj->Display_orgPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_lvdsVipSingleStereoCalibration_Create(chains_lvdsVipSingleStereoCalibrationObj *pObj, Void *appObj){

       Int32 status;

       chains_lvdsVipSingleStereoCalibration_SetLinkId(pObj);
       chains_lvdsVipSingleStereoCalibration_ResetLinkPrms(pObj);

       chains_lvdsVipSingleStereoCalibration_SetPrms(pObj);
       chains_lvdsVipSingleStereoCalibration_SetAppPrms(pObj, appObj);

       chains_lvdsVipSingleStereoCalibration_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPE_captureLinkID, &pObj->VPE_capturePrm, sizeof(pObj->VPE_capturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_EVE2_0LinkID, &pObj->IPCOut_IPU1_0_EVE2_0Prm, sizeof(pObj->IPCOut_IPU1_0_EVE2_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_EVE2_IPU1_0_0LinkID, &pObj->IPCIn_EVE2_IPU1_0_0Prm, sizeof(pObj->IPCIn_EVE2_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_RemapMergeLinkID, &pObj->Alg_RemapMergePrm, sizeof(pObj->Alg_RemapMergePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_EVE2_IPU1_0_0LinkID, &pObj->IPCOut_EVE2_IPU1_0_0Prm, sizeof(pObj->IPCOut_EVE2_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_IPU1_0_EVE2_0LinkID, &pObj->IPCIn_IPU1_0_EVE2_0Prm, sizeof(pObj->IPCIn_IPU1_0_EVE2_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPE_orgLinkID, &pObj->VPE_orgPrm, sizeof(pObj->VPE_orgPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Sync_orgLinkID, &pObj->Sync_orgPrm, sizeof(pObj->Sync_orgPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_DmaSwMs_orgLinkID, &pObj->Alg_DmaSwMs_orgPrm, sizeof(pObj->Alg_DmaSwMs_orgPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_orgLinkID, &pObj->Display_orgPrm, sizeof(pObj->Display_orgPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_lvdsVipSingleStereoCalibration_Start(chains_lvdsVipSingleStereoCalibrationObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_DmaSwMs_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Sync_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPE_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_IPU1_0_EVE2_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_EVE2_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_RemapMergeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_EVE2_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_EVE2_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPE_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_lvdsVipSingleStereoCalibration_Stop(chains_lvdsVipSingleStereoCalibrationObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_DmaSwMs_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Sync_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPE_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_IPU1_0_EVE2_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_EVE2_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_RemapMergeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_EVE2_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_EVE2_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPE_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_lvdsVipSingleStereoCalibration_Delete(chains_lvdsVipSingleStereoCalibrationObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_DmaSwMs_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Sync_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPE_orgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_IPU1_0_EVE2_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_EVE2_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_RemapMergeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_EVE2_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_EVE2_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPE_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_lvdsVipSingleStereoCalibration_printBufferStatistics(chains_lvdsVipSingleStereoCalibrationObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->VPE_captureLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_EVE2_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_EVE2_IPU1_0_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_RemapMergeLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_EVE2_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_IPU1_0_EVE2_0LinkID);
       System_linkPrintBufferStatistics(pObj->VPE_orgLinkID);
       System_linkPrintBufferStatistics(pObj->Sync_orgLinkID);
       System_linkPrintBufferStatistics(pObj->Alg_DmaSwMs_orgLinkID);
       System_linkPrintBufferStatistics(pObj->Display_orgLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_lvdsVipSingleStereoCalibration_printStatistics(chains_lvdsVipSingleStereoCalibrationObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->VPE_captureLinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_EVE2_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_EVE2_IPU1_0_0LinkID);
       System_linkPrintStatistics(pObj->Alg_RemapMergeLinkID);
       System_linkPrintStatistics(pObj->IPCOut_EVE2_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_IPU1_0_EVE2_0LinkID);
       System_linkPrintStatistics(pObj->VPE_orgLinkID);
       System_linkPrintStatistics(pObj->Sync_orgLinkID);
       System_linkPrintStatistics(pObj->Alg_DmaSwMs_orgLinkID);
       System_linkPrintStatistics(pObj->Display_orgLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

