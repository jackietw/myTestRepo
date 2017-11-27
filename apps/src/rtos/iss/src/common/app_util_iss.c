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

/**
 *******************************************************************************
 * \file chains_common_iss.c
 *
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <iss_sensors.h>
#include <iss_utils.h>
#include <algorithmLink_issAewb.h>
#include <app_util_iss.h>

#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>
#include <src/rtos/utils_common/include/utils.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */
typedef struct
{
    UInt32                      isAlloc;
    AppUtils_Obj                appSensorInfo;
    ChainsCommon_IssSensorIf    sensorIntfInfo;
    IssSensor_Info              sensorInfo;
    IssSensor_CreateParams      sensorCreatePrms;

    Ptr                         sensorHandle;
    IssAewbAlgOutParams         issAewbPrms;

    UInt32                      issCaptLinkId;
    UInt32                      issIspLinkId;
    UInt32                      issSimcopLinkId;
    UInt32                      issAewbLinkId;

    IssM2mSimcopLink_ConfigParams   simcopCfg;
    vpsissldcConfig_t               ldcCfg;
    vpsissvtnfConfig_t              vtnfCfg;
} AppUtils_IssObj;

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

AppUtils_IssObj gAppUtilsIssObj = {0};


/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
Void appSetDccParams(Ptr pIspCfg, Ptr pSimcopCfg, Void *appData);
Void appSetMergeParams(AlgorithmLink_IssAewbOutParams *pAewbAlgOut,
    Ptr pIspCfg, Void *appData);
Void appSetAewbOutputParams(
    AlgorithmLink_IssAewbOutParams *pAewbAlgOut, Ptr pCfg, Void *appData);


/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief   Sensor Creation
 *
 *******************************************************************************
*/
Void appCreateISSSensor(AppUtils_Obj *pSensorInfo)
{
    Int32 status;
    UInt32 ch;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;
    IssSensor_CreateParams *prms = NULL;
    ChainsCommon_IssSensorIf *ifInfo;

    if (pIssObj->isAlloc)
    {
        return;
    }
    else
    {
        prms = &pIssObj->sensorCreatePrms;
        ifInfo = &pIssObj->sensorIntfInfo;

        prms->numChan = pSensorInfo->numCh;
        strncpy(prms->name, pSensorInfo->sensorName, ISS_SENSORS_MAX_NAME);

        status = IssSensor_GetSensorInfo(prms->name, &pIssObj->sensorInfo);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        status = ChainsPlatform_GetSensorIntfInfo(prms->name, ifInfo);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        prms->i2cInstId = ifInfo->i2cInstId;

        for(ch = 0;ch < prms->numChan;ch++)
        {
            prms->i2cAddr[ch] = ifInfo->i2cAddr[ch];
            prms->videoIfWidth[ch] = ifInfo->videoIfWidth;

            prms->enableFeatures[ch] = 0;
            switch(pSensorInfo->ispOpMode)
            {
                default:
                case ISSM2MISP_LINK_OPMODE_12BIT_LINEAR:
                    prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_LINEAR_MODE;
                    break;
                case ISSM2MISP_LINK_OPMODE_1PASS_WDR:
                    prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_ONE_PASS_WDR_MODE;
                    break;
                case ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED:
                case ISSM2MISP_LINK_OPMODE_2PASS_WDR:
                    prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_TWO_PASS_WDR_MODE;
                    break;
            }

            if ((ALGORITHMS_ISS_AEWB_MODE_AE == pIssObj->sensorInfo.aewbMode) ||
                (ALGORITHMS_ISS_AEWB_MODE_AEWB == pIssObj->sensorInfo.aewbMode))
            {
                prms->enableFeatures[ch] |=
                    ISS_SENSOR_FEATURE_MANUAL_EXPOSURE |
                        ISS_SENSOR_FEATURE_MANUAL_GAIN;
            }

            if ((0 == strncmp(SENSOR_OMNIVISION_OV10640_CSI2, prms->name,
                ISS_SENSORS_MAX_NAME)) ||
                (0 == strncmp(SENSOR_OMNIVISION_OV10640_IMI, prms->name,
                ISS_SENSORS_MAX_NAME)))
            {
                prms->enableFeatures[ch] |= ISS_SENSOR_FEATURE_HFLIP;
            }
        }

        pIssObj->sensorHandle = IssSensor_Create(prms);
        UTILS_assert(NULL != pIssObj->sensorHandle);

        memcpy(&pIssObj->appSensorInfo, pSensorInfo, sizeof(AppUtils_Obj));
        pIssObj->isAlloc = 1;
    }
}

Void appStartIssSensorSerDes(AppUtils_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    ChainsCommon_IssSensorIf sensorIntfInfo;
    IssSensor_CreateParams sensorCreatePrms;
    BspUtils_Ub960SourceI2cAddr ub960I2cAddr;
    BspUtils_Ub960Status ub960Status;
    UInt32 start, end;

    strncpy(sensorCreatePrms.name, pObj->sensorName,
        ISS_SENSORS_MAX_NAME);

    status = ChainsPlatform_GetSensorIntfInfo(sensorCreatePrms.name,
        &sensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if(TRUE == sensorIntfInfo.isMultiChannel)
    {
        start = Utils_getCurTimeInMsec();

        /*  1. UB96x init */
        ub960I2cAddr.slaveAddr = UB960_SLAVE_ADDR;
        ub960I2cAddr.numSource = pObj->numCh;

        for(cnt = 0; cnt < ub960I2cAddr.numSource; cnt ++)
        {
            ub960I2cAddr.rSlave1Addr[cnt] = sensorIntfInfo.i2cAddrSer[cnt];

            if(TRUE == sensorIntfInfo.sensorBroadcast)
            {
                /*  When broadcast is enabled then all the senors will have the
                    same alias i2c address */
                ub960I2cAddr.rSlave2Addr[cnt] = sensorIntfInfo.i2cAddr[0];
            }
            else
            {
                ub960I2cAddr.rSlave2Addr[cnt] = sensorIntfInfo.i2cAddr[cnt];
            }
        }

        status = BspUtils_appInitUb960(
                                0U,
                                sensorIntfInfo.sensorDrvId,
                                &ub960I2cAddr,
                                &ub960Status);
        UTILS_assert (status == 0);

        /*  2. Program the sensors */
        if(TRUE == sensorIntfInfo.sensorBroadcast)
        {
            /* Program only ONE sensor */
            appStartISSSensor(pObj, 0);
        }
        else
        {
            for(cnt = 0 ; cnt < ub960I2cAddr.numSource; cnt ++)
            {
                appStartISSSensor(pObj, cnt);
            }
        }

        /*  3. Disable sensor broadcast */
        if(TRUE == sensorIntfInfo.sensorBroadcast)
        {
            for(cnt = 0 ; cnt < ub960I2cAddr.numSource; cnt ++)
            {
                ub960I2cAddr.rSlave2Addr[cnt] = sensorIntfInfo.i2cAddr[cnt];
            }

            status = BspUtils_updateSlaveAddrUb960(0U, &ub960I2cAddr);
            UTILS_assert (status == 0);
        }

        /*  4.Enable FSIN for IMI camera */
        if(TRUE == sensorIntfInfo.enableFsin)
        {
            status = BspUtils_appUb960EnableFsin(
                                    0U,
                                    sensorIntfInfo.sensorDrvId,
                                    &ub960I2cAddr,
                                    &ub960Status);
            UTILS_assert (status == 0);
        }
    }
    else
    {
        appStartISSSensor(pObj, 0);
    }

    end = Utils_getCurTimeInMsec();
    Vps_printf(" #### Sensor Config time = %d msec ####\n",(end - start));
}

Void appStartISSSensor(AppUtils_Obj *pObj,UInt32 numCh)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    status = IssSensor_Start(pIssObj->sensorHandle, numCh);
    UTILS_assert(0 == status);
}

Void appStopISSSensor(AppUtils_Obj *pObj)
{
    Int32 status, cnt;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    for (cnt = 0u; cnt < pObj->numCh; cnt ++)
    {
        status = IssSensor_Stop(pIssObj->sensorHandle, cnt);
        UTILS_assert(0 == status);
    }
}

Void appDeleteISSSensor(AppUtils_Obj *pObj)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    status = IssSensor_Delete(pIssObj->sensorHandle);
    UTILS_assert(0 == status);

    pIssObj->sensorHandle = NULL;
    memset(&pIssObj->appSensorInfo, 0, sizeof(AppUtils_Obj));
    pIssObj->isAlloc = 0;
}

Void appInitIssCaptParams(AppUtils_Obj *pObj, UInt32 issCaptLinkId,
    IssCaptureLink_CreateParams *pCapturePrm)
{
    Int32 status;
    ChainsCommon_IssSensorIf *pSensorIntfInfo;
    IssSensor_Info *pSensorInfo;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pCapturePrm);

    pIssObj->issCaptLinkId = issCaptLinkId;

    pSensorInfo = &pIssObj->sensorInfo;
    pSensorIntfInfo = &pIssObj->sensorIntfInfo;

    status = IssSensor_GetSensorInfo(pObj->sensorName, pSensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = ChainsPlatform_GetSensorIntfInfo(pObj->sensorName,
        pSensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pCapturePrm->outParams[0U].dataFormat =
        (System_VideoDataFormat)pSensorInfo->dataFormat;
    pCapturePrm->outParams[0U].width = pSensorInfo->width;
    pCapturePrm->outParams[0U].height = pSensorInfo->height;

    if (pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED)
    {
        pCapturePrm->outParams[0U].width  =
            pSensorInfo->lnIntrExpFrmInfo.totalWidth;
        pCapturePrm->outParams[0U].height =
            pSensorInfo->lnIntrExpFrmInfo.totalHeight;
    }

    pCapturePrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;
    pCapturePrm->outParams[0U].maxWidth = pCapturePrm->outParams[0U].width;
    pCapturePrm->outParams[0U].maxHeight = pCapturePrm->outParams[0U].height;
    pCapturePrm->outParams[0U].numOutBuf = 3;

    /* Initialize Capture parameters from sensor interface information */
    pCapturePrm->videoIfMode =
        (System_VideoIfMode)pSensorIntfInfo->videoIfMode;
    pCapturePrm->videoIfWidth =
        (System_VideoIfWidth)pSensorIntfInfo->videoIfWidth;

    pCapturePrm->outParams[0U].inCsi2DataFormat = pSensorIntfInfo->inCsi2DataFormat;
    pCapturePrm->outParams[0U].inCsi2VirtualChanNum =
        pSensorIntfInfo->inCsi2VirtualChanNum;

    pCapturePrm->csi2Params[0U] = pSensorIntfInfo->csi2Prms;
}

Void appInitIssIspParams(AppUtils_Obj *pObj, UInt32 issIspLinkId,
    IssM2mIspLink_CreateParams *pPrm)
{
    Int32 status;
    UInt32 chId;
    ChainsCommon_IssSensorIf *pSensorIntfInfo;
    IssSensor_Info *pSensorInfo;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pPrm);

    pIssObj->issIspLinkId = issIspLinkId;

    pSensorInfo = &pIssObj->sensorInfo;
    pSensorIntfInfo = &pIssObj->sensorIntfInfo;

    status = IssSensor_GetSensorInfo(pObj->sensorName, pSensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = ChainsPlatform_GetSensorIntfInfo(pObj->sensorName,
        pSensorIntfInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    for(chId = 0; chId < ISSM2MISP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode   = pObj->ispOpMode;
        pPrm->channelParams[chId].inBpp           = pSensorInfo->bpp;

        pPrm->channelParams[chId].numBuffersPerCh = 3;

        pPrm->channelParams[chId].outParams.widthRszA  = pSensorInfo->width;
        pPrm->channelParams[chId].outParams.heightRszA = pSensorInfo->height;
        pPrm->channelParams[chId].outParams.widthRszB  = pSensorInfo->width;
        pPrm->channelParams[chId].outParams.heightRszB = pSensorInfo->height;
        pPrm->channelParams[chId].outParams.winWidthH3a = 16;
        pPrm->channelParams[chId].outParams.winHeightH3a = 16;
        pPrm->channelParams[chId].outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;

        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A] = 1;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_H3A]  = 1;
        pPrm->channelParams[chId].enableOut[
            ISSM2MISP_LINK_OUTPUTQUE_H3A_AF]  = 0;

        {
            pPrm->channelParams[chId].enableOut[
                ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 1;
        }

        if (pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED)
        {
            pPrm->channelParams[chId].outParams.widthRszA  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    width;
            pPrm->channelParams[chId].outParams.heightRszA =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    height;

            pPrm->channelParams[chId].wdrOffsetPrms.longLineOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    starty;
            pPrm->channelParams[chId].wdrOffsetPrms.longPixelOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    startx;
            pPrm->channelParams[chId].wdrOffsetPrms.shortLineOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].
                    starty;
            pPrm->channelParams[chId].wdrOffsetPrms.shortPixelOffset  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_SHORT].
                    startx;
            pPrm->channelParams[chId].wdrOffsetPrms.width  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    width;
            pPrm->channelParams[chId].wdrOffsetPrms.height  =
                pSensorInfo->lnIntrExpFrmInfo.info[ISS_SENSOR_EXPOSURE_LONG].
                    height;
        }
    }
}

Void appInitIssSimcopParams(AppUtils_Obj *pObj, UInt32 issSimcopLinkId,
    IssM2mSimcopLink_CreateParams *pPrm)
{
    int chId;

    gAppUtilsIssObj.issSimcopLinkId = issSimcopLinkId;

    for(chId=0; chId<ISSM2MSIMCOP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode = pObj->simcopOpMode;;

        pPrm->channelParams[chId].numBuffersPerCh
            = ISSM2MSIMCOP_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}

Void appSetDefaultIspParams(AppUtils_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    IssIspConfigurationParameters ispConfig;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    IssM2mIspLink_ConfigParams_Init(&ispConfig);

    /* H3A and GLBCE configuration comes from the sensor layer
       Get ISP configuration for these modules from sensor */
    status = IssSensor_Control(pIssObj->sensorHandle,
        ISS_SENSORS_IOCTL_GET_ISP_CONFIG, &ispConfig, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    for (cnt = 0u; cnt < pObj->numCh; cnt ++)
    {
        /** Set the default Config received from the sensor layer
            MUST be called after link create and before link start */
        status = System_linkControl(
            pIssObj->issIspLinkId, ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
            &ispConfig, sizeof(IssIspConfigurationParameters), TRUE);
        UTILS_assert(0 == status);
    }
}

Void appSetIspParamsFromDCC(AppUtils_Obj *pObj)
{
    Int32 status;
    IssSensor_DccParams sensorDccPrms;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    status = IssSensor_GetSensorInfo(pObj->sensorName, &pIssObj->sensorInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    if (ISS_SENSOR_FEATURE_DCC_SUPPORTED ==
        (ISS_SENSOR_FEATURE_DCC_SUPPORTED & pIssObj->sensorInfo.features))
    {
        sensorDccPrms.chId = 0;
        /* Get the default Profile from the sensor */
        status = IssSensor_Control(pIssObj->sensorHandle,
            ISS_SENSORS_IOCTL_GET_DCC_PARAMS, &sensorDccPrms, NULL);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        /* Reads default configuration from the sensor layer,
           then reads and parses DCC Profile and saves it in the isp and
           simcop config */
        IssUtils_ReadAndParseDccConfig(
                pIssObj->sensorInfo.ramOffset,
                sensorDccPrms.pDccCfg,
                sensorDccPrms.dccCfgSize,
                pIssObj->issAewbLinkId);
    }
}

Void appInitIssAewbParams(AppUtils_Obj *pObj, UInt32 issAewbLinkId,
    AlgorithmLink_IssAewbCreateParams *pPrm)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pPrm);
    UTILS_assert(NULL != pIssObj->sensorHandle);

    pIssObj->issAewbLinkId = issAewbLinkId;

    status = IssSensor_Control(pIssObj->sensorHandle,
        ISS_SENSORS_IOCTL_INIT_AEWB_CONFIG, pPrm, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Since we are operating in Linear mode, disable backlight compensation */
    if ((pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_12BIT_LINEAR) ||
        (pObj->ispOpMode == ISSM2MISP_LINK_OPMODE_1PASS_WDR))
    {
        pPrm->aeDynParams.enableBlc = FALSE;
    }

    pPrm->appData = pIssObj;
    pPrm->dccAppData = pIssObj;
    pPrm->cfgCbFxn = appSetAewbOutputParams;

    /* No Need to enable merge function for single pass wdr flow */
    if (TRUE == IssM2mIspLink_IsWdrMergeMode(pObj->ispOpMode))
    {
        pPrm->mergeCbFxn = appSetMergeParams;
    }

    pPrm->dccIspCfgFxn = appSetDccParams;

    pPrm->numSteps = 6;
}

Void appSetAewbOutputParams(
    AlgorithmLink_IssAewbOutParams *pAewbAlgOut, Ptr pCfg, Void *appData)
{
    Int32 status, cnt;
    IssSensor_AeParams sensorAePrms;
    AppUtils_IssObj *pIssObj = (AppUtils_IssObj *)appData;
    IssAewbAlgOutParams *pIssAewbPrms;
    IssIspConfigurationParameters *pIspCfg =
        (IssIspConfigurationParameters *)pCfg;

    UTILS_assert(NULL != pIssObj);
    UTILS_assert(NULL != pAewbAlgOut);
    UTILS_assert(NULL != pIspCfg);

    pIssAewbPrms = &pIssObj->issAewbPrms;

    pIssAewbPrms->channelId = pAewbAlgOut->channelId;
    pIssAewbPrms->outPrms[0].useAeCfg = pAewbAlgOut->outPrms[0].useAeCfg;
    pIssAewbPrms->outPrms[0].exposureTime =
        pAewbAlgOut->outPrms[0].exposureTime;
    pIssAewbPrms->outPrms[0].analogGain = pAewbAlgOut->outPrms[0].analogGain;
    pIssAewbPrms->outPrms[0].digitalGain = pAewbAlgOut->outPrms[0].digitalGain;

    pIssAewbPrms->outPrms[0].useColorTemp =
        pAewbAlgOut->outPrms[0].useColorTemp;
    pIssAewbPrms->outPrms[0].colorTemparature =
        pAewbAlgOut->outPrms[0].colorTemparature;

    pIssAewbPrms->outPrms[0].useWbCfg = pAewbAlgOut->outPrms[0].useWbCfg;
    for (cnt = 0u; cnt < 4; cnt ++)
    {
        pIssAewbPrms->outPrms[0].gain[cnt] = pAewbAlgOut->outPrms[0].gain[cnt];
        pIssAewbPrms->outPrms[0].offset[cnt] =
            pAewbAlgOut->outPrms[0].offset[cnt];
    }

    pIssAewbPrms->numParams = 1U;

    memcpy(&pIssAewbPrms->ispCfg, pIspCfg,
        sizeof(IssIspConfigurationParameters));

    /* AEWB Output parameters are already converted and stored in
       ispCfg parameter of alg out, so set it in the ISP using ISP
       Link */
    System_linkControl(
        pIssObj->issIspLinkId, ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS, pIssAewbPrms,
        sizeof(IssAewbAlgOutParams), TRUE);

    /* Set the Sensor exposure and analog Gain */
    if (pAewbAlgOut->outPrms[0].useAeCfg)
    {
        sensorAePrms.chId = pAewbAlgOut->channelId;
        sensorAePrms.analogGain = pAewbAlgOut->outPrms[0].analogGain;
        sensorAePrms.exposureTime[0] =
            pAewbAlgOut->outPrms[0].exposureTime;

        status = IssSensor_Control(pIssObj->sensorHandle,
            ISS_SENSORS_IOCTL_SET_AE_PARAMS, &sensorAePrms, NULL);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }
}

Void appSetMergeParams(AlgorithmLink_IssAewbOutParams *pAewbAlgOut,
    Ptr pIspCfg, Void *appData)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = (AppUtils_IssObj *)appData;
    IssSensor_ExposureParams expPrms;

    UTILS_assert(NULL != pIssObj);
    UTILS_assert(NULL != pAewbAlgOut);

    /* Get Exposure ratio parameters from the sensor */
    expPrms.chId = pAewbAlgOut->channelId;
    status = IssSensor_Control(pIssObj->sensorHandle,
        ISS_SENSORS_IOCTL_GET_EXPOSURE_PARAMS, &expPrms, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* When dgain is applied only to long after split, there is a
        different ratio for split and merge */
    /* setting up merge parameters even for 2 pass wdr mode when AE is
       not enabled because merge parameter calculation uses digital gain
       for the calculation */
    if ((TRUE == pAewbAlgOut->outPrms[0].useAeCfg) ||
        ((TRUE == IssM2mIspLink_IsWdrMergeMode(
            pIssObj->appSensorInfo.ispOpMode)) &&
         (ALGORITHMS_ISS_AEWB_MODE_AWB == pIssObj->sensorInfo.aewbMode)))
    {
        pIssObj->issAewbPrms.exposureRatio = expPrms.expRatio;

        System_linkControl(
            pIssObj->issIspLinkId,
            ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS,
            &pIssObj->issAewbPrms,
            sizeof(IssAewbAlgOutParams),
            TRUE);
    }
}

Void appSetDccParams(Ptr pIspCfg, Ptr pSimcopCfg, Void *appData)
{
    Int32 status;
    UInt32 cnt;
    AppUtils_IssObj *pIssObj = (AppUtils_IssObj *)appData;
    IssIspConfigurationParameters *ispCfg =
        (IssIspConfigurationParameters *)pIspCfg;
    IssM2mSimcopLink_ConfigParams *simcopCfg =
        (IssM2mSimcopLink_ConfigParams *)pSimcopCfg;

    UTILS_assert(NULL != pIssObj);
    UTILS_assert(NULL != ispCfg);
    UTILS_assert(NULL != simcopCfg);
    UTILS_assert(pIssObj->appSensorInfo.numCh > 0);

    /* Set the ISS configuration in ISP link */
    for (cnt = 0u; cnt < pIssObj->appSensorInfo.numCh; cnt ++)
    {
        ispCfg->channelId = cnt;
        simcopCfg->chNum = cnt;

        status = System_linkControl(
            pIssObj->issIspLinkId, ISSM2MISP_LINK_CMD_SET_ISPCONFIG, ispCfg,
            sizeof(IssIspConfigurationParameters), TRUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        if (NULL != simcopCfg->ldcConfig)
        {
            /* MUST be called after link create and before link start */
            status = System_linkControl(
                pIssObj->issSimcopLinkId,
                ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
                simcopCfg, sizeof(IssM2mSimcopLink_ConfigParams), TRUE);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }
    }
}

Void appSetDefaultSimcopParams(void)
{
    Int32 status;
    AppUtils_IssObj *pIssObj = &gAppUtilsIssObj;

    pIssObj->simcopCfg.ldcConfig = &pIssObj->ldcCfg;
    pIssObj->simcopCfg.vtnfConfig = &pIssObj->vtnfCfg;

    IssUtils_InitSimcopConfig(&pIssObj->simcopCfg, TRUE, TRUE);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
        pIssObj->issSimcopLinkId,
        ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
        &pIssObj->simcopCfg, sizeof(IssM2mSimcopLink_ConfigParams), TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}
