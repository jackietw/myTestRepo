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
 *
 *  \ingroup LINK_API
 *  \defgroup APP_CTRL_LINK_API Application Control link
 *
 *  This module defines the control commands that are applicable to
 *  control application specific function when QNX on A15.
 *
 *  When QNX runs on A15, IPU1-0 still needs to control some board level
 *  devices like capture sensors
 *
 *  This link implemented on IPU1-0 exports APIs which application on A15
 *  can invoke to control these devices
 *
 *  This API is only valid when QNX runs on A15
 *
 *  This is control ONLY link, i.e is does not take any buffers as input
 *  or output.
 *
 *   @{
*/

/**
 *******************************************************************************
 *
 *  \file appCtrlLink_qnx.h
 *  \brief Application Control link for QNX
 *
 *******************************************************************************
*/

#ifndef _APP_CTRL_LINK_QNX_H_
#define _APP_CTRL_LINK_QNX_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <src/include/chains_common_srv_calib.h>
#include <src/include/chains_common_sensor.h>
#include <src/rtos/iss/include/app_util_iss.h>

//#ifdef QNX_BUILD
/**
 *******************************************************************************
 *
 *  \brief  Enum for sensor ID for image sensors.
 *
 *          These are set of sensors currently supported on the EVM
 *
 *******************************************************************************
*/
typedef enum {
    APP_CTRL_VID_SENSOR_OV10635,
    /**< Omnivision OV10635 sensor */
    APP_CTRL_VID_SENSOR_MULDES_OV1063X,
    /**< Omnivision OV10630 sensor */
    APP_CTRL_VID_SENSOR_MAX = 0xFFFFu,
    /**<Max */
    APP_CTRL_VID_SENSOR_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AppCtrlVidSensor_Id;
//#endif

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Params for command APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED
 *******************************************************************************
 */
typedef struct {

    UInt32 isConnected;
    /**< [OUT]
         TRUE: Multi-des board is connected,
         FALSE: Multi-des board is NOT connected
     */

} AppCtrlCmd_BoardIsMultiDesConnectedPrm;

/**
 *******************************************************************************
 * \brief Params for command APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED
 *
 *        MOST parameters are set based on how the connections are done on
 *        the board, limited control is given from A15 side
 *
 *******************************************************************************
 */
typedef struct {

    Chains_CaptureSrc captureSrcId;
    /**< Sensor ID */

    UInt32 isLVDSCaptMode;
    /**< [IN]
     *    TRUE: OV1063X Multi-CH LVDS capture mode
     *    FALSE: OV1063X single channel capture mode
     */

    UInt32 numLvdsCh;
    /**< [IN] Number of channels of LVDS to configure
     *        Valid values 1..6
     */
    AppUtils_Obj issUtilObj;
    /**< [IN] ISS utils OBJ */
} VideoSensorCreateAndStartAppPrm;

//#ifdef QNX_BUILD
/**
 *******************************************************************************
 * \brief Params for command APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED
 *
 *        MOST parameters are set based on how the connections are done on
 *        the board, limited control is given from A15 side
 *
 *******************************************************************************
 */
typedef struct {

    AppCtrlVidSensor_Id sensorId;
    /**< Sensor ID */

    UInt32 isLVDSCaptMode;
    /**< [IN]
     *    TRUE: OV1063X Multi-CH LVDS capture mode
     *    FALSE: OV1063X single channel capture mode
     */

    UInt32 numLvdsCh;
    /**< [IN] Number of channels of LVDS to configure
     *        Valid values 1..6
     */

} AppCtrlCmd_VideoSensorCreateAndStartPrm;
//#endif


/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup APP_CTRL_LINK_API_CMD  Application Control link Control Commands

    @{
*/

//#ifdef QNX_BUILD
//#endif

/**
 *******************************************************************************
 * \brief Link CMD: Command to enable USB port for charging
 *
 * \param NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_BOARD_ENABLE_USB_CHARGING         (0x1002)

/**
 *******************************************************************************
 * \brief Link CMD: Command to check if Multi-des board is connectoed or not
 *
 * \param  AppCtrlCmd_BoardIsMultiDesConnectedPrm *pPrm [OUT]
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED      (0x1003)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set DMM priorities
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SET_DMM_PRIORITIES                (0x1004)

/**
 *******************************************************************************
 * \brief Link CMD: Command to perform surround view calibrtaion + QSPI storage
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_SURROUNDVIEW_CALIBRATION          (0x1005)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set stat collector init
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_STAT_COLLECTOR_INIT               (0x1006)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set stat collector deinit
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_STAT_COLLECTOR_DEINIT             (0x1007)

//#ifdef QNX_BUILD
/**
 *******************************************************************************
 * \brief Link CMD: Command to create and start Video sensor
 *
 *   \param AppCtrlCmd_VideoSensorCreateAndStartPrm *pPrm [IN]
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START     (0x1008)

/**
 *******************************************************************************
 * \brief Link CMD: Command to stop and delete Video Sensor
 *
 *   \param  NONE
 *
 *******************************************************************************
*/
#define APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE      (0x1009)
//#endif

/*@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
