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
 * \file iss_sensor_tda3xx.c
 *
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
/* Including system.h for Int32/UInt32 data type */
#include <include/link_api/system.h>
#include <iss_sensors.h>
#include <iss_utils.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_capture.h>
#include <ti/drv/vps/include/devices/bsp_device.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* I2C Instance for the board Mux */
#define CHAINS_COMMON_TDA3XX_BOARD_MUX_I2C_INST     (0U)
/* I2C Address of the board mux */
#define CHAINS_COMMON_TDA3XX_BOARD_MUX_I2C_ADDR     (0x23U)


/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */
typedef struct {
    char name[ISS_SENSORS_MAX_NAME];
    ChainsCommon_IssSensorIf info;
} ChainsCommon_SensorIntfInfo;

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

const static ChainsCommon_SensorIntfInfo gSensorInterfaceInfo[] = {
    {SENSOR_APTINA_AR0132,
        {1u, {0x10}, {0x10}, FALSE, SYSTEM_VIFW_12BIT, SYSTEM_VIFM_SCH_CPI}},
    {SENSOR_APTINA_AR0140,
        {1u, {0x10}, {0x10}, FALSE, SYSTEM_VIFW_12BIT, SYSTEM_VIFM_SCH_CPI}},
    {SENSOR_OMNIVISION_OV10640_CSI2,
        {1u, {0x32}, {0x32}, FALSE, SYSTEM_VIFW_4LANES, SYSTEM_VIFM_SCH_CSI2,
            SYSTEM_CSI2_RAW12 /* CSI2 DataFormat*/, 0 /*Virtual Channel Id*/,
                {TRUE /* isCplxCfgValid */,
                    {{FALSE, 2}, /* Clock Lane */
                     {FALSE, 1}, /* data1Lane */
                     {FALSE, 3}, /* data2Lane */
                     {FALSE, 4}, /* data3Lane*/
                     {FALSE, 5}},/* data4Lane */
                     400 /* csi2PhyClk */ }}},
    {SENSOR_SONY_IMX224_CSI2,
        {1u, {0x36}, {0x36}, FALSE, SYSTEM_VIFW_4LANES, SYSTEM_VIFM_SCH_CSI2,
            SYSTEM_CSI2_RAW12 /* CSI2 DataFormat*/, 0 /*Virtual Channel Id*/,
                {TRUE /* isCplxCfgValid */,
                    {{FALSE, 2u}, /* Clock Lane */
                     {FALSE, 1u}, /* data1Lane */
                     {FALSE, 3u}, /* data2Lane */
                     {FALSE, 4u}, /* data3Lane*/
                     {FALSE, 5u}},/* data4Lane */
                     150u /* csi2PhyClk */ }}},
    {SENSOR_OMNIVISION_OV10640_IMI,
        {
#ifdef BOARD_TYPE_TDA3XX_RVP
            0u, /* TDA3X RVP board uses I2C instance 0 */
#else
            1u, /* TDA3X EVM board uses I2C instance 1 */
#endif
            {0x40, 0x42, 0x44, 0x46},   /* Sensor alias address */
            {0x74, 0x76, 0x78, 0x7A},   /* Serializer alias address */
            TRUE, /* isMultiChannel */
            SYSTEM_VIFW_4LANES, SYSTEM_VIFM_SCH_CSI2,
            SYSTEM_CSI2_RAW12 /* CSI2 DataFormat*/,
            0 /*Virtual Channel Id*/,
                {TRUE /* isCplxCfgValid */,
                    {{FALSE, 1}, /* Clock Lane */
                     {FALSE, 2}, /* data1Lane */
                     {FALSE, 3}, /* data2Lane */
                     {FALSE, 4}, /* data3Lane*/
                     {FALSE, 5}},/* data4Lane */
                     800 /* csi2PhyClk */ },
                     FVID2_VID_SENSOR_IMI_OV10640_DRV,          /* sensorDrvId */
                     TRUE,      /* sensorBroadcast */
                     TRUE}},    /* enableFsin */
    {SENSOR_APTINA_AR0140_TIDA262,
        {
#ifdef BOARD_TYPE_TDA3XX_RVP
            0u, /* TDA3X RVP board uses I2C instance 0 */
#else
            1u, /* TDA3X EVM board uses I2C instance 1 */
#endif
            {0x40, 0x42, 0x44, 0x46},   /* Sensor alias address */
            {0x74, 0x76, 0x78, 0x7A},   /* Serializer alias address */
            TRUE, /* isMultiChannel */
            SYSTEM_VIFW_4LANES, SYSTEM_VIFM_SCH_CSI2,
            SYSTEM_CSI2_RAW12 /* CSI2 DataFormat*/,
            0 /*Virtual Channel Id*/,
                {TRUE /* isCplxCfgValid */,
                    {{FALSE, 1}, /* Clock Lane */
                     {FALSE, 2}, /* data1Lane */
                     {FALSE, 3}, /* data2Lane */
                     {FALSE, 4}, /* data3Lane*/
                     {FALSE, 5}},/* data4Lane */
                     800 /* csi2PhyClk */ },
                     FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV, /* sensorDrvId */
                     FALSE,     /* sensorBroadcast */
                     FALSE}},   /* enableFsin */
    {SENSOR_OMNIVISION_OV2775_CSI2,
        {1u, {0x36}, {0x36}, FALSE, SYSTEM_VIFW_4LANES, SYSTEM_VIFM_SCH_CSI2,
            SYSTEM_CSI2_RAW12 /* CSI2 DataFormat*/, 0 /*Virtual Channel Id*/,
                {TRUE /* isCplxCfgValid */,
                    {{FALSE, 3}, /* Clock Lane */
                     {FALSE, 4}, /* data1Lane */
                     {FALSE, 2}, /* data2Lane */
                     {FALSE, 5}, /* data3Lane*/
                     {FALSE, 1}},/* data4Lane */
                     480 /* csi2PhyClk */ }}},
    {SENSOR_APTINA_AR0143_MARS,
        {
#ifdef BOARD_TYPE_TDA3XX_RVP
            0u, /* TDA3X RVP board uses I2C instance 0 */
#else
            1u, /* TDA3X EVM board uses I2C instance 1 */
#endif
            {0x40, 0x42, 0x44, 0x46},   /* Sensor alias address */
            {0x74, 0x76, 0x78, 0x7A},   /* Serializer alias address */
            TRUE, /* isMultiChannel */
            SYSTEM_VIFW_4LANES, SYSTEM_VIFM_SCH_CSI2,
            SYSTEM_CSI2_RAW12 /* CSI2 DataFormat*/,
            0 /*Virtual Channel Id*/,
                {TRUE /* isCplxCfgValid */,
                    {{FALSE, 1}, /* Clock Lane */
                     {FALSE, 2}, /* data1Lane */
                     {FALSE, 3}, /* data2Lane */
                     {FALSE, 4}, /* data3Lane*/
                     {FALSE, 5}},/* data4Lane */
                     800 /* csi2PhyClk */ },
                     0,         /* sensorDrvId */
                     FALSE,     /* sensorBroadcast */
                     FALSE}},   /* enableFsin */

};

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */


/*******************************************************************************
 *  Function Definition
 *******************************************************************************
 */

Int32 ChainsPlatform_GetSensorIntfInfo(char name[],
    ChainsCommon_IssSensorIf *info)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, numSensors;

    UTILS_assert(NULL != info);

    numSensors = sizeof(gSensorInterfaceInfo)/sizeof(ChainsCommon_SensorIntfInfo);

    for (cnt = 0u; cnt < numSensors; cnt ++)
    {
        if (0 == strncmp(name, gSensorInterfaceInfo[cnt].name,
                ISS_SENSORS_MAX_NAME))
        {
            info->i2cInstId = gSensorInterfaceInfo[cnt].info.i2cInstId;
            info->i2cAddr[0] = gSensorInterfaceInfo[cnt].info.i2cAddr[0];
            info->i2cAddr[1] = gSensorInterfaceInfo[cnt].info.i2cAddr[1];
            info->i2cAddr[2] = gSensorInterfaceInfo[cnt].info.i2cAddr[2];
            info->i2cAddr[3] = gSensorInterfaceInfo[cnt].info.i2cAddr[3];
            info->i2cAddrSer[0] = gSensorInterfaceInfo[cnt].info.i2cAddrSer[0];
            info->i2cAddrSer[1] = gSensorInterfaceInfo[cnt].info.i2cAddrSer[1];
            info->i2cAddrSer[2] = gSensorInterfaceInfo[cnt].info.i2cAddrSer[2];
            info->i2cAddrSer[3] = gSensorInterfaceInfo[cnt].info.i2cAddrSer[3];
            info->isMultiChannel = gSensorInterfaceInfo[cnt].info.isMultiChannel;
            info->videoIfWidth = gSensorInterfaceInfo[cnt].info.videoIfWidth;
            info->videoIfMode = gSensorInterfaceInfo[cnt].info.videoIfMode;
            info->inCsi2DataFormat =
                gSensorInterfaceInfo[cnt].info.inCsi2DataFormat;
            info->inCsi2VirtualChanNum =
                gSensorInterfaceInfo[cnt].info.inCsi2VirtualChanNum;
            info->csi2Prms = gSensorInterfaceInfo[cnt].info.csi2Prms;
            info->sensorDrvId = gSensorInterfaceInfo[cnt].info.sensorDrvId;
            info->sensorBroadcast = gSensorInterfaceInfo[cnt].info.sensorBroadcast;
            info->enableFsin = gSensorInterfaceInfo[cnt].info.enableFsin;
            status = SYSTEM_LINK_STATUS_SOK;
            break;
        }
    }

    return (status);
}

Void ChainsPlatform_SetPinMux(char name[])
{
    Int32 status;
    UInt32 cnt, numSensors;
    Bsp_BoardMode boardMode;

    numSensors = sizeof(gSensorInterfaceInfo)/sizeof(ChainsCommon_IssSensorIf);

    for (cnt = 0u; cnt < numSensors; cnt ++)
    {
        if ((0 == strncmp(name, gSensorInterfaceInfo[cnt].name,
                ISS_SENSORS_MAX_NAME)) &&
            (SYSTEM_VIFM_SCH_CPI == gSensorInterfaceInfo[cnt].info.videoIfMode))
        {
            switch (gSensorInterfaceInfo[cnt].info.videoIfWidth)
            {
                default:
                    boardMode = BSP_BOARD_MODE_NONE;
                    break;
                case SYSTEM_VIFW_8BIT:
                    boardMode = BSP_BOARD_MODE_VIDEO_8BIT;
                    break;
                case SYSTEM_VIFW_10BIT:
                    boardMode = BSP_BOARD_MODE_VIDEO_10BIT;
                    break;
                case SYSTEM_VIFW_12BIT:
                    boardMode = BSP_BOARD_MODE_VIDEO_12BIT;
                    break;
                case SYSTEM_VIFW_14BIT:
                    boardMode = BSP_BOARD_MODE_VIDEO_14BIT;
                    break;
                case SYSTEM_VIFW_16BIT:
                    boardMode = BSP_BOARD_MODE_VIDEO_16BIT;
                    break;
                case SYSTEM_VIFW_24BIT:
                    boardMode = BSP_BOARD_MODE_VIDEO_24BIT;
                    break;
            }

            /* Set pinmux */
            status = Bsp_boardSetPinMux(FVID2_VPS_CAPT_VID_DRV,
                VPS_CAPT_INST_ISS_CAL_A, boardMode);

            UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);

            break;
        }
    }

}

Void ChainsBoard_SetBoardMux(char name[])
{
    Int32 status;
    UInt32 cnt, numSensors;
    UInt8 regValue[3U];

    numSensors = sizeof(gSensorInterfaceInfo)/sizeof(ChainsCommon_IssSensorIf);

    for (cnt = 0u; cnt < numSensors; cnt ++)
    {
        if ((0 == strncmp(name, gSensorInterfaceInfo[cnt].name,
                ISS_SENSORS_MAX_NAME)) &&
            (SYSTEM_VIFM_SCH_CPI == gSensorInterfaceInfo[cnt].info.videoIfMode))
        {
            status = Bsp_boardReadTCA6424BoardMux(3, regValue);
            UTILS_assert(status == BSP_SOK);

            /* Select the CPI input by setting Mux Control 0 and 5 */
            regValue[0u] |= (0x21);
            /* Set VIN_MAP[0:2] to 010 for Aptina 12-bit - Level 2 */
            regValue[2u] &= ~(0x3D);

            status = Bsp_boardWriteTCA6424BoardMux(3, regValue);
            UTILS_assert(status == BSP_SOK);

            BspOsal_sleep(50);

            break;
        }
    }
}
