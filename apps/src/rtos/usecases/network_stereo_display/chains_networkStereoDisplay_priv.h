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

#ifndef _chains_networkStereoDisplay_H_
#define _chains_networkStereoDisplay_H_

#include <include/link_api/system.h>
#include <include/link_api/nullSrcLink.h>
#include <include/link_api/decLink.h>
#include <include/link_api/dupLink.h>
#include <include/alglink_api/algorithmLink_census.h>
#include <include/alglink_api/algorithmLink_disparityHamDist.h>
#include <include/link_api/mergeLink.h>
#include <include/alglink_api/algorithmLink_stereoPostProcess.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/vpeLink.h>
#include <include/link_api/syncLink.h>
#include <include/alglink_api/algorithmLink_dmaSwMs.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>

typedef struct {
       UInt32    NullSourceLinkID;
       UInt32    IPCOut_A15_0_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_A15_0_0LinkID;
       UInt32    DecodeLinkID;
       UInt32    VPE_decodeOutLinkID;
       UInt32    Dup_origLinkID;
       UInt32    Sync_dispLinkID;
       UInt32    Dup_CensusInputLinkID;
       UInt32    IPCOut_IPU1_0_EVE2_0LinkID;
       UInt32    IPCIn_EVE2_IPU1_0_0LinkID;
       UInt32    Alg_CensusLinkID;
       UInt32    IPCOut_EVE2_EVE3_0LinkID;
       UInt32    IPCIn_EVE3_EVE2_0LinkID;
       UInt32    Alg_DisparityHamDistLinkID;
       UInt32    IPCOut_EVE3_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_EVE3_1LinkID;
       UInt32    MergeLinkID;
       UInt32    IPCOut_IPU1_0_DSP1_1LinkID;
       UInt32    IPCIn_DSP1_IPU1_0_0LinkID;
       UInt32    Alg_StereoPostProcessLinkID;
       UInt32    IPCOut_DSP1_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_DSP1_2LinkID;
       UInt32    VPE_disparityLinkID;
       UInt32    Display_disparityLinkID;
       UInt32    VPE_orgdispLinkID;
       UInt32    Sync_orgLinkID;
       UInt32    Alg_DmaSwMsLinkID;
       UInt32    Display_orgLinkID;
       UInt32    GrpxSrcLinkID;
       UInt32    Display_GrpxLinkID;

       NullSrcLink_CreateParams                NullSourcePrm;
       IpcLink_CreateParams                    IPCOut_A15_0_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_A15_0_0Prm;
       DecLink_CreateParams                    DecodePrm;
       VpeLink_CreateParams                    VPE_decodeOutPrm;
       DupLink_CreateParams                    Dup_origPrm;
       SyncLink_CreateParams                   Sync_dispPrm;
       DupLink_CreateParams                    Dup_CensusInputPrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE2_0Prm;
       IpcLink_CreateParams                    IPCIn_EVE2_IPU1_0_0Prm;
       AlgorithmLink_CensusCreateParams        Alg_CensusPrm;
       IpcLink_CreateParams                    IPCOut_EVE2_EVE3_0Prm;
       IpcLink_CreateParams                    IPCIn_EVE3_EVE2_0Prm;
       AlgorithmLink_DisparityHamDistCreateParams Alg_DisparityHamDistPrm;
       IpcLink_CreateParams                    IPCOut_EVE3_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_EVE3_1Prm;
       MergeLink_CreateParams                  MergePrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_DSP1_1Prm;
       IpcLink_CreateParams                    IPCIn_DSP1_IPU1_0_0Prm;
       AlgorithmLink_StereoPostProcessCreateParams Alg_StereoPostProcessPrm;
       IpcLink_CreateParams                    IPCOut_DSP1_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_DSP1_2Prm;
       VpeLink_CreateParams                    VPE_disparityPrm;
       DisplayLink_CreateParams                Display_disparityPrm;
       VpeLink_CreateParams                    VPE_orgdispPrm;
       SyncLink_CreateParams                   Sync_orgPrm;
       AlgorithmLink_DmaSwMsCreateParams       Alg_DmaSwMsPrm;
       DisplayLink_CreateParams                Display_orgPrm;
       GrpxSrcLink_CreateParams                GrpxSrcPrm;
       DisplayLink_CreateParams                Display_GrpxPrm;
} chains_networkStereoDisplayObj;

Void chains_networkStereoDisplay_SetLinkId(chains_networkStereoDisplayObj *pObj);

Void chains_networkStereoDisplay_ResetLinkPrms(chains_networkStereoDisplayObj *pObj);

Void chains_networkStereoDisplay_SetPrms(chains_networkStereoDisplayObj *pObj);

Void chains_networkStereoDisplay_ConnectLinks(chains_networkStereoDisplayObj *pObj);

Int32 chains_networkStereoDisplay_Create(chains_networkStereoDisplayObj *pObj, Void *appObj);

Int32 chains_networkStereoDisplay_Start(chains_networkStereoDisplayObj *pObj);

Int32 chains_networkStereoDisplay_Stop(chains_networkStereoDisplayObj *pObj);

Int32 chains_networkStereoDisplay_Delete(chains_networkStereoDisplayObj *pObj);

Void chains_networkStereoDisplay_printBufferStatistics(chains_networkStereoDisplayObj *pObj);

Void chains_networkStereoDisplay_printStatistics(chains_networkStereoDisplayObj *pObj);

Void chains_networkStereoDisplay_SetAppPrms(chains_networkStereoDisplayObj *pObj, Void *appObj);

#endif /* _chains_networkStereoDisplay_H_ */