/*
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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_mcspi.c
 *
 * \brief  This file has the implementataion for UART
 *
 * \version 0.0 (Aug 2016) : [PG] First version
 * \version 0.1 (Oct 2017) : [PG] Updated for 4 McSPI
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/csl/soc.h>
#include <src/rtos/utils_common/include/utils_mcspi.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>

#define UTILS_MCSPI_NUM_MCSPI_INST (4U)

/** \brief McSPI Configuration parameters */
static Mcspi_Params mcspiCfgPrms[UTILS_MCSPI_NUM_MCSPI_INST];

/** \brief String identifiers for the McSPI driver names */
static xdc_String gMcspiDriverNames[UTILS_MCSPI_NUM_MCSPI_INST] =
{
    "/mcspi0",
    "/mcspi1",
    "/mcspi2",
    "/mcspi3"
};

/**
 *******************************************************************************
 *  \brief  User defined function which will initialize the McSPI. This function
 *          is called when the driver for McSPI is created.
 *
 * \return  None
 *
 *******************************************************************************
 */
static void Utils_mcspiUserCommonInit(uint32_t mcSPINum);

static void Utils_mcspi0UserInit(void);
static void Utils_mcspi1UserInit(void);
static void Utils_mcspi2UserInit(void);
static void Utils_mcspi3UserInit(void);

/**
 *******************************************************************************
 *
 * \brief Initializes the McSPI and adds the GIO_Device
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Utils_mcspiInit(UInt32 mcSpiInstNum)
{
    if (mcSpiInstNum < UTILS_MCSPI_NUM_MCSPI_INST)
    {
        /* Set the mcspi params */
        switch(mcSpiInstNum)
        {
            case 0U: GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi0UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_0);
                    break;
            case 1U: GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi1UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_1);
                    break;
            case 2U: /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_59, MCSPI3_IRQ);
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi2UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_2);
                    break;
            case 3U:
                    /* Set up non default Cross Bar */
                    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                                CPU_IPU1, XBAR_INST_IPU1_IRQ_60, MCSPI4_IRQ);
                    GIO_addDevice(gMcspiDriverNames[mcSpiInstNum],
                    (xdc_Ptr) & Mcspi_IOMFXNS,
                    &Utils_mcspi3UserInit,
                    (xdc_Int)mcSpiInstNum, (xdc_Ptr) & (mcspiCfgPrms[mcSpiInstNum]));
                    Bsp_boardSelectDevice(BSP_DRV_ID_MCSPI, BSP_DEVICE_MCSPI_INST_ID_3);
                    break;
            default:
                    /* Should not come here */
                    break;
        }
    }
}

Void Utils_mcspiDeinit(UInt32 mcSpiInstNum)
{
    GIO_removeDevice(gMcspiDriverNames[mcSpiInstNum]);
}

void Utils_mcspiGetDevName (UInt32 mcSpiInstNum, xdc_String devName)
{
    if (mcSpiInstNum < UTILS_MCSPI_NUM_MCSPI_INST)
    {
        strcpy(devName, gMcspiDriverNames[mcSpiInstNum]);
    }
}

static void Utils_mcspi0UserInit(void)
{
    Utils_mcspiUserCommonInit(0U);
}

static void Utils_mcspi1UserInit(void)
{
    Utils_mcspiUserCommonInit(1U);
}

static void Utils_mcspi2UserInit(void)
{
    Utils_mcspiUserCommonInit(2U);
}

static void Utils_mcspi3UserInit(void)
{
    Utils_mcspiUserCommonInit(3U);
}

static void Utils_mcspiUserCommonInit(uint32_t mcSPINum)
{
    UInt32       i = 0U;
    static uint32_t done = 0U;
    if (done == 0U)
    {
        Mcspi_init();
        done = 1U;
    }
    memcpy((Void *)&mcspiCfgPrms[mcSPINum], (const Void *)&Mcspi_PARAMS, sizeof(Mcspi_Params));
    /* Set the McSPI parameters */
    mcspiCfgPrms[mcSPINum].instNum = mcSPINum;
    mcspiCfgPrms[mcSPINum].opMode          = MCSPI_OPMODE_INTERRUPT;
    mcspiCfgPrms[mcSPINum].hwiNumber       = 7;
    mcspiCfgPrms[mcSPINum].enableCache     = (UInt32) TRUE;
    mcspiCfgPrms[mcSPINum].edma3EventQueue = 0;
    mcspiCfgPrms[mcSPINum].enableErrIntr   = (UInt32) FALSE;
    mcspiCfgPrms[mcSPINum].prcmPwrmEnable = TRUE;

    mcspiCfgPrms[mcSPINum].spiHWCfgData.masterOrSlave         = MCSPI_COMMMODE_MASTER;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.singleOrMultiChEnable = MCSPI_MULTI_CHANNEL;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.pinOpModes    = MCSPI_PINOPMODE_4PIN;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.fifoRxTrigLvl = 32;
    mcspiCfgPrms[mcSPINum].spiHWCfgData.fifoTxTrigLvl = 32;

    for (i = 0U; i < CSL_MCSPI_0_NumOfPhyChannels; i++)
    {
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].charLength = MCSPI_LEN_16BIT;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].multiWordAccessEnable =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiChipSelectEnablePol =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].clockMode =
            MCSPI_MODE0;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].clockRatioExtension = 0;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiWordInitDelay    =
            MCSPI_NO_DELAY;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].trasmitReceiveMode =
            MCSPI_BOTH_RXTX;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].granularityEnable =
            (UInt32) TRUE;
        /* 800 KHz Bus Frequency */
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].busFreq           = 8000000;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spienHighPolarity =
            (UInt32) FALSE;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].slaveModeChipSelect =
            MCSPI_SPIEN_0;
#if defined (RADAR_INCLUDE) && defined(SOC_TDA2XX)
        if (mcSPINum == 2)
        {
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_IN;
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_OUT;
        }
        else
        {
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_OUT;
            mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_IN;
        }
#else
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat0Dir = MCSPI_OUT;
        mcspiCfgPrms[mcSPINum].spiHWCfgData.configChfmt[i].spiDat1Dir = MCSPI_IN;
#endif
    }

    if (MCSPI_OPMODE_INTERRUPT == mcspiCfgPrms[mcSPINum].opMode)
    {
        Vps_printf(" UTILS_MCSPI: McSPI is configured in interrupt mode!!\r\n");
    }
}
