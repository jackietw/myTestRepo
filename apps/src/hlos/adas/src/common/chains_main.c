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
#include <system_cfg.h>
#include <src/hlos/adas/include/chains.h>


Chains_Ctrl gChains_usecaseCfg;

/**
 *******************************************************************************
 * \brief Run Time Test Menu string.
 *******************************************************************************
 */
char gChains_testMenu[] = {
    "\r\n "
    "\r\n ========="
    "\r\n Test Menu"
    "\r\n ========="
    "\r\n "
    "\r\n Single Camera Use-cases,"
    "\r\n ------------------------"
#ifdef UC_vip_single_cam_sgx_display
    "\r\n 1: 1CH VIP capture + SGX Copy + DISPLAY"
#endif
#ifndef IPUMM_INCLUDE
#ifdef UC_vip_single_cam_enc_dec_sgx_display
    "\r\n 2: 1CH VIP capture + Encode + Decode + SGX Copy + DISPLAY"
#endif
#endif
#ifdef UC_vip_single_cam_framecopyEve_sgx_display
    "\r\n 3: 1CH VIP capture + Alg FrameCopy (EVE1) + SGX Copy + DISPLAY - (TDA2xx ONLY)"
#endif
#ifdef FPD_DISPLAY
#ifdef UC_vip_single_cam_dualSgxDisplay
    "\r\n 4: 1CH VIP capture + SGX Copy + DUAL Display(HDMI & FPD-Out)"
#endif
#endif
#ifndef IPUMM_INCLUDE
#ifdef UC_null_src_decode_display
    "\r\n 5: NullSrc + Decode + Display (Only 1920x1080 H264/MJPEG Video Input Bit-Stream Supported)"
#endif
#endif
#ifdef UC_vip_single_cam_framecopy_sgx_display
    "\r\n 6: 1CH VIP capture + Alg Frame Copy (A15) + SGX Copy + DISPLAY"
#endif
#ifdef UC_vip_single_cam_connectorLinksA15_sgx_display
    "\r\n 7: 1CH VIP + Alg Frame Copy (A15) + Connetor Links (Dup, Merge, Select, Gate on A15) + SGX Copy + DISPLAY"
#endif
#ifdef ENABLE_OPENCV
#ifdef UC_vip_single_cam_opencvcanny_sgx_display
    "\r\n 8: 1CH VIP capture + OpenCV Canny (A15) + SGX Copy + DISPLAY"
#endif
#ifdef UC_vip_single_cam_opencvcanny_sgx_display
    "\r\n 9: 1CH VIP capture + OpenCV OpenCL Dilation (A15 + DSP) + SGX Copy + DISPLAY"
#endif
#endif
#ifdef OPENCL_INCLUDE
#ifdef UC_vip_single_cam_openclframe_copy
    "\r\n g: 1CH VIP capture + OpenCL Copy (A15->DSP) + SGX Copy + DISPLAY"
#endif
#endif
    "\r\n "
    "\r\n Multi-Camera LVDS Use-cases,"
    "\r\n ----------------------------"
#ifdef UC_lvds_vip_multi_cam_view_sgx_display
    "\r\n a: 4CH VIP LVDS capture + SGX MOSAIC + DISPLAY"
#endif
#ifdef UC_lvds_vip_multi_cam_vpe_enc_null
    "\r\n t: 4CH VIP LVDS capture + Scale + Encode + Null (file dump)"
#endif
#ifdef UC_lvds_vip_multi_cam_3d_srv
    "\r\n b: 4CH VIP LVDS capture + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_lvds_vip_multi_cam_2mp_3d_srv
    "\r\n l: 4CH VIP LVDS 2MP capture + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_lvds_vip_multi_cam_3d_perception
    "\r\n c: 4CH VIP LVDS capture + 3D SRV + 4CH SfM (3D perception demo - EVE1-4/DSP1&2) + DISPLAY - Only on TDA2xx with HDMI 1080p display"
#endif
#ifdef UC_ov490_vip_multi_cam_3d_srv
    "\r\n d: 2CH OV490 2560x720 capture + Split + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_srv_calibration
    "\r\n e: Surround View Calibration"
#endif
#ifdef UC_csi2Cal_multi_cam_3d_srv
    "\r\n j: 4CH CSI2 CAL capture + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_srv_calibration
    "\r\n k: CSI2 CAL Surround View Calibration"
#endif
#ifdef UC_csi2Cal_multi_cam_view
    "\r\n w: 4CH CSI2 CAL capture + SgxFrmCpy + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_lvds_vip_multi_cam_3d_adaptive_srv
    "\r\n o: 4CH VIP LVDS capture + Adaptive 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
    "\r\n "
    "\r\n AVB RX Use-cases, (TDA2x ONLY)"
    "\r\n ------------------------------"
#ifdef UC_avb_rx_multi_cam_decode_sgx_display
    "\r\n f: 4CH AVB Capture + Decode + SGX MOSAIC + DISPLAY"
#endif
#ifdef UC_avb_rx_multi_cam_3d_srv
    "\r\n h: 4CH AVB Capture + Decode + SGX 3D-SRV + DISPLAY"
#endif
#ifdef UC_avbrx_sv_display_avbtx
    "\r\n r: 4CH AVB Capture + Decode + SGX 3D-SRV + DISPLAY + ENCODE + AVBTX"
#endif
    "\r\n "
#ifdef OPENVX_INCLUDE
    "\r\n OPENVX Usecase, (TDA2x ONLY)"
    "\r\n ----------------------------"
    "\r\n m: OpenVX v1.1 Conformance Test"
    "\r\n q: OpenVX Tutorials"
    "\r\n "
#endif

#ifdef ISS_INCLUDE
    "\r\n ISS Usecase, (TDA2PX ONLY)"
    "\r\n ----------------------------"
#ifdef UC_iss_capture_isp_simcop_display
    "\r\n r: 1CH ISS Capture + ISP + DISPLAY"
#endif
#ifdef UC_iss_multi_cam_isp_sgx_3d_srv_display
    "\r\n t: 4CH ISS Capture + ISP + 3DSRV + SGX + Display"
#endif
#ifdef UC_srv_calibration
    "\r\n v: ISS CAL SRV Calibration"
#endif
    "\r\n "
#endif

#ifdef UC_csi2Cal_multi_cam_3d_srv_cbb
    "\r\n n: 4CH CSI2 CAL capture + 3D SRV (SGX/A15) + Car Black Box + DISPLAY - Only HDMI 1080p display supported"
#endif
    "\r\n p: CPU Status"
    "\r\n i: Show IP Addr (IPU + NDK + AVB) "
    "\r\n "
    "\r\n s: System Settings "
    "\r\n "
    "\r\n x: Exit "
    "\r\n z: Exit - AND SHUTDOWN Remote CPUs"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


/**
 *******************************************************************************
 * \brief Menu for capture settings.
 *******************************************************************************
 */
char gChains_menuCaptureSrc[] = {
    "\r\n "
    "\r\n =============="
    "\r\n Capture Source"
    "\r\n =============="
    "\r\n "
    "\r\n 1: OV10635 Sensor 720P30"
    "\r\n 2: HDMI Capture 1080P60 "
    "\r\n 3: OV10640 CSI2 Sensor 1280x720 (Only on TDA3xx/TDA2px)"
    "\r\n 4: OV10640 IMI Sennsor 1280x720 (Only on TDA3xx/TDA2px)"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Menu for system settings.
 *******************************************************************************
 */
 char gChains_menuSystemSettings[] = {
    "\r\n "
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
    "\r\n 1: Display Settings"
    "\r\n 2: Capture Settings"
    "\r\n 3: Calibration Settings"
    "\r\n 4: ISS Settings"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Menu for display settings.
 *******************************************************************************
 */
char gChains_menuDisplaySettings[] = {
    "\r\n "
    "\r\n ================"
    "\r\n Display Settings"
    "\r\n ================"
    "\r\n "
#if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD)
    "\r\n 1: LCD  10-inch 1280x720@60fps"
#endif
    "\r\n 2: HDMI 1080P60 "
#ifdef FPD_DISPLAY
    "\r\n 3: FPD Out "
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Menu for ISS settings.
 *******************************************************************************
 */
char gChains_menuISSSettings[] = {
    "\r\n "
    "\r\n ================"
    "\r\n ISS Settings"
    "\r\n ================"
    "\r\n "
    "\r\n 1: Enable Linear Mode"
    "\r\n 2: Enable Two Pass WDR Mode"
    "\r\n 3: Enable Single Pass WDR Mode"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
*******************************************************************************
* \brief Menu for automatic calibration settings.
*******************************************************************************
*/

char gChains_menuCalibrationSettings[] = {
    "\r\n "
    "\r\n ====================="
    "\r\n Calibration Settings"
    "\r\n ====================="
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: Binarization Settings "
    "\r\n 2: Corner Detection Settings "
    "\r\n 3: Pose Estimation Settings "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuBinarizationSettings[] = {
    "\r\n "
    "\r\n ======================"
    "\r\n Binarization Settings"
    "\r\n ======================"
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: White Bias (0.9) "
    "\r\n 2: No Bias (1.0) "
    "\r\n 3: Default Bias (1.1) "
    "\r\n 4: Black Bias 1 (1.15) "
    "\r\n 5: Black Bias 2 (1.25) "
    "\r\n "
    "\r\n 6: Small Window (50x50)"
    "\r\n 7: Large Window (75x75 Default) "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuCornerSettings[] = {
    "\r\n "
    "\r\n =========================="
    "\r\n Corner Detection Settings"
    "\r\n =========================="
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: Line Estimation RANSAC Off (Default) "
    "\r\n 2: Line Estimation RANSAC On "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuPoseSettings[] = {
    "\r\n "
    "\r\n =========================="
    "\r\n Pose Estimation Settings"
    "\r\n =========================="
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: Pose Estimation RANSAC Off (Default) "
    "\r\n 2: Pose Estimation RANSAC On "
    "\r\n 3: Single Chart Pose Estimation Off (Default) "
    "\r\n 4: Single Chart Pose Estimation On "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Run Time Menu string for 3D SRV.
 *******************************************************************************
 */
char gChains_3DSrvRunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n c: Change Camera "
    "\r\n a: Change Angle "
    "\r\n t: Change Target "
    "\r\n i: Increase in c, a or t"
    "\r\n d: Decrease in c, a or t"
    "\r\n x: Modify X position by delta "
    "\r\n y: Modify Y position by delta "
    "\r\n z: Modify Z position by delta "
    "\r\n m: increase delta, or more change "
    "\r\n l: decrease delta or less change "
    "\r\n 1: Preset view 0 "
    "\r\n 2: Preset view 1 "
    "\r\n 3: Preset view 2 "
    "\r\n b: Turn bowl view on/off "
    "\r\n v: Turn car view on/off "
    "\r\n j: Turn Animation On "
    "\r\n k: Turn Animation Off "
    "\r\n n: Change Render mode "
    "\r\n w: Change car "
    "\r\n "
    "\r\n 4: Control bowl depth"
    "\r\n "
    "\r\n To make changes follow the below sequence:"
    "\r\n First select c , a or t. Then select i or d. Then select x, y or z."
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
*******************************************************************************
* \brief Run Time Menu strings for autocalibration settings.
*******************************************************************************
*/
void Chains_showBinarizationSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuBinarizationSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 1;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 2;
            done = TRUE;
            break;
        case '3':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 0;
            done = TRUE;
            break;
        case '4':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 3;
            done = TRUE;
            break;
        case '5':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 4;
            done = TRUE;
            break;
        case '6':
            gChains_usecaseCfg.calibrationParams.windowMode = 1;
            done = TRUE;
            break;
        case '7':
            gChains_usecaseCfg.calibrationParams.windowMode = 0;
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}

void Chains_showCornerDetectionSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuCornerSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            gChains_usecaseCfg.calibrationParams.Ransac = 0;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.calibrationParams.Ransac = 1;
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}

void Chains_showPoseDetectionSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuPoseSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            gChains_usecaseCfg.calibrationParams.PoseRansac = 0;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.calibrationParams.PoseRansac = 1;
            done = TRUE;
            break;
        case '3':
            gChains_usecaseCfg.calibrationParams.SingleChartPose = 0;
            done = TRUE;
            break;
        case '4':
            gChains_usecaseCfg.calibrationParams.SingleChartPose = 1;
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}

void Chains_showISSSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuISSSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '1':
            gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_2PASS_WDR;
            done = TRUE;
            break;
        case '3':
            gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_1PASS_WDR;
            done = TRUE;
            break;
        case 'x':
        case 'X':
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);
}

void Chains_showCalibrationSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuCalibrationSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            Chains_showBinarizationSettingsMenu();
            done = TRUE;
            break;
        case '2':
            Chains_showCornerDetectionSettingsMenu();
            done = TRUE;
            break;
        case '3':
            Chains_showPoseDetectionSettingsMenu();
            done = TRUE;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Function to set display settings.
 *
 *******************************************************************************
*/
Void Chains_showDisplaySettingsMenu()
{
    char ch;
    Bool displaySelectDone;
    displaySelectDone = FALSE;

    do
    {
        Vps_printf(gChains_menuDisplaySettings);
        Vps_printf(" \r\n");
        ch = getchar();

        switch(ch)
        {
            case '1':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_LCD_10_INCH;
                displaySelectDone = TRUE;
                break;
            case '2':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                displaySelectDone = TRUE;
                break;
#ifdef FPD_DISPLAY
            case '3':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_FPD;
                displaySelectDone = TRUE;
                break;
#endif
            case 'x':
            case 'X':
                displaySelectDone = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }

    }while(displaySelectDone == FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Function to set capture settings.
 *
 *******************************************************************************
*/
Void Chains_showCaptureSettingsMenu()
{
    char ch;
    Bool captSrcSelectDone;
    captSrcSelectDone = FALSE;

    do
    {
        Vps_printf(gChains_menuCaptureSrc);
        Vps_printf(" \r\n");
        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                captSrcSelectDone = TRUE;
                break;
            case '2':
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_HDMI_1080P;
                captSrcSelectDone = TRUE;
                break;
            case '3':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_OMNIVISION_OV10640_CSI2,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '4':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_OMNIVISION_OV10640_IMI,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case 'x':
            case 'X':
                captSrcSelectDone = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }

    }while(captSrcSelectDone == FALSE);
}
/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char Chains_menuRunTime()
{
    Vps_printf(gChains_runTimeMenu);

    return Chains_readChar();
}

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection for 3D SRV
 *
 *          This functions displays the run time options available for 3D SRV
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char Chains_menu3DSrvRunTime()
{
    Vps_printf(gChains_3DSrvRunTimeMenu);

    return Chains_readChar();
}

/**
 *******************************************************************************
 *
 * \brief   Function to select systems settings option.
 *
 *******************************************************************************
*/
Void Chains_showSystemSettingsMenu()
{
    char ch;
    Bool done;
    done = FALSE;

    do
    {
        Vps_printf(gChains_menuSystemSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                Chains_showDisplaySettingsMenu();
                done = TRUE;
                break;
            case '2':
                Chains_showCaptureSettingsMenu();
                done = TRUE;
                break;
            case '3':
                Chains_showCalibrationSettingsMenu();
                done = TRUE;
                break;
            case '4':
                Chains_showISSSettingsMenu();
                done = TRUE;
                break;
            case 'x':
            case 'X':
                done = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }while(!done);
}

#ifdef OPENVX_INCLUDE
char vx_tutorial_get_char()
{
    return getchar();
}
#endif

/**
 *******************************************************************************
 *
 * \brief   Application's main - entry function
 *
 *******************************************************************************
*/
Int32 main (Int32 argc, Char ** argv)
{
    Char ch;
    Bool shutdownRemoteCores = FALSE;

    System_init();
    ChainsCommon_appCtrlCommonInit();
    Chains_Ctrl_Init(&gChains_usecaseCfg);

    /* allow remote prints to complete, before showing main menu */
    OSA_waitMsecs(500);

    static UInt8 autoBoot = 0;
    gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
    strncpy(gChains_usecaseCfg.sensorName, SENSOR_OMNIVISION_OV10640_IMI,
        ISS_SENSORS_MAX_NAME);

    while(1)
    {
        Vps_printf(gChains_testMenu);
        if (autoBoot == 0)
        {
            ch = getchar();
        }
        else
        {
            ch = 'b';
            autoBoot = 0;
        }


        if((ch=='x') || (ch=='X'))
            break;

        if((ch=='z') || (ch=='Z'))
        {
            shutdownRemoteCores = TRUE;
            break;
        }

        switch(ch)
        {
            #ifdef UC_vip_single_cam_sgx_display
            case '1':
                chains_vipSingleCam_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifndef IPUMM_INCLUDE
            #ifdef UC_vip_single_cam_enc_dec_sgx_display
            case '2':
                chains_vipSingleCam_Enc_Dec_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifdef UC_vip_single_cam_framecopyEve_sgx_display
            case '3':
                gChains_usecaseCfg.algProcId = SYSTEM_PROC_EVE1;
                chains_vipSingleCamFrmcpyEve_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef FPD_DISPLAY
            #ifdef UC_vip_single_cam_dualSgxDisplay
            case '4':
                chains_vipSingleCam_SGX_IpuDualDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifndef IPUMM_INCLUDE
            #ifdef UC_null_src_decode_display
            case '5':
                gChains_usecaseCfg.numLvdsCh = 1;
                Chains_nullSrc_DecodeDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifdef UC_vip_single_cam_framecopy_sgx_display
            case '6':
                chains_vipSingleCamFrameCopySgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_connectorLinksA15_sgx_display
            case '7':
                chains_vipSingleCamConnectorLinksA15SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif

            #ifdef ENABLE_OPENCV
            #ifdef UC_vip_single_cam_opencvcanny_sgx_display
            case '8':
                chains_vipSingleCamOpenCVCannySgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_opencvopencldilation_sgx_display
            case '9':
                chains_vipSingleCamOpenCVOpenCLDilationSgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifdef UC_lvds_vip_multi_cam_view_sgx_display
            case 'a':
            case 'A':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                chains_lvdsVipMultiCam_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_vpe_enc_null
            case 't':
            case 'T':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                chains_lvdsVipMultiCam_vpeEncNull(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_3d_srv
            case 'b':
            case 'B':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_lvdsVipMultiCam_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_2mp_3d_srv
            case 'l':
            case 'L':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_IMX290ISP;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_lvdsVipMultiCam2mp_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_3d_perception
            case 'c':
            case 'C':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                chains_lvdsVipMultiCam_3d_perception(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_ov490_vip_multi_cam_3d_srv
            case 'd':
            case 'D':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_ov490VipMultiCam_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_srv_calibration
            case 'e':
            case 'E':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_VIP);
                break;
            #endif
            #ifdef UC_avb_rx_multi_cam_decode_sgx_display
            case 'f':
            case 'F':
                gChains_usecaseCfg.numLvdsCh = 4;
                Chains_AvbRxDecodeSgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef OPENCL_INCLUDE
            #ifdef UC_vip_single_cam_openclframe_copy
            case 'g':
            case 'G':
                chains_vipSingleCamOpenCLFrameCopySgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifdef UC_avb_rx_multi_cam_3d_srv
            case 'h':
            case 'H':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                Chains_AvbRxSgx3DSrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_avbrx_sv_display_avbtx
            case 'r':
            case 'R':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_avbrxSrvDisplayAvbtx(&gChains_usecaseCfg);
                break;
            #endif
            case 'p':
            case 'P':
                ChainsCommon_printCpuStatus();
                break;
            case 'i':
            case 'I':
                if(System_isProcEnabled(SYSTEM_IPU_PROC_PRIMARY))
                {
                    SystemCommon_IpAddr ipuIpAddr;
                    System_linkControl(
                        SYSTEM_LINK_ID_IPU1_0,
                        SYSTEM_COMMON_CMD_GET_IP_ADDR,
                        &ipuIpAddr,
                        sizeof(SystemCommon_IpAddr),
                        TRUE
                    );
                    Vps_printf(" Network IP address : %s\n", ipuIpAddr.ipAddr);
                }
                break;
            #ifdef UC_csi2Cal_multi_cam_3d_srv
            case 'j':
            case 'J':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_csi2CalMultiCam_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_srv_calibration
            case 'k':
            case 'K':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_CSI2CAL);
                break;
            #endif
            #ifdef OPENVX_INCLUDE
            case 'm':
            case 'M':
                TestModuleRegister();
                vx_conformance_test_main(0U, NULL);
                break;
            case 'q':
            case 'Q':
                vx_tutorial_run_interactive();
                break;
            #endif
            #ifdef UC_csi2Cal_multi_cam_3d_srv_cbb
            case 'n':
            case 'N':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_3d_adaptive_srv
            case 'o':
            case 'O':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_lvdsVipMultiCam_Sgx3D_adaptive_srv(&gChains_usecaseCfg);
                break;
            #endif
            case 's':
            case 'S':
                    Chains_showSystemSettingsMenu();
                    break;
            #ifdef UC_csi2Cal_multi_cam_view
            case 'w':
            case 'W':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_csi2CalMultiCam_View(&gChains_usecaseCfg);
                break;
            #endif

            #ifdef UC_iss_capture_isp_simcop_display
            case 'r':
            case 'R':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                Chains_issIspSimcop_Display(&gChains_usecaseCfg);
                break;
            #endif

            #ifdef UC_iss_multi_cam_isp_sgx_3d_srv_display
            case 't':
            case 'T':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_issMultiCamIspSgx3DSrv_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_srv_calibration
            case 'v':
            case 'V':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.numLvdsCh = 4;
                chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_ISS);
                break;
            #endif
        }
    }
    ChainsCommon_appCtrlCommonDeInit();
    System_deInit(shutdownRemoteCores);

    return 0;
}

