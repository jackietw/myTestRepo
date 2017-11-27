
#
# This file has override conditions
#
# If user gives a conflicting config,
# logic in this file will override to a logically correct config
#

#
# To get a faster incremental build do below
# BUILD_DEPENDENCY_ALWAYS=no
#
# IMPORTANT: In this case make sure to do
# (g)make -s depend
# in case of any change in dependancies like
# - changes in pdk/EDMA3LLD .c or .h file
# - changes in number of cores used for build (value of PROC_<CPU>_INCLUDE)
# - change in value of DDR_MEM
# - change in value of NDK_PROC_TO_USE
#
BUILD_DEPENDENCY_ALWAYS=no

#
# Enable this macro to enable Ultra sonic based initialization
# This is added as the power measurement and Ultra sonic use the same
# pad on the device. Kindly note the Ultrasonic and power measurement
# use the same GPIO6_14/15 pads with different functionalities. Ultrasonic configures
# UART10 on those pads and power measurement configures I2C3. Hence when this
# macro is yes the power measurement functionality is not supported.
#
ULTRASONIC_INCLUDE=no

TREAT_WARNINGS_AS_ERROR=yes



# Set the PACKAGE_SELECT option for pdk to individually control VIP, VPE and DSS
# For Bios on A15  - Display will be controlled by M4 Bios, so set as "all" (including DSS)
# For Linux on A15 - If Display will be controlled by A15 Linux, then set as "vps-vip-vpe" (excluding DSS)
ifeq ($(A15_TARGET_OS),Bios)
BSP_STW_PACKAGE_SELECT := all
endif

# Vision SDK Linux supports display only on M4 (Bios)
ifeq ($(A15_TARGET_OS),Linux)
# For InfoADAS display is on A15 (Linux/DRM)
    ifeq ($(BUILD_INFOADAS),yes)
         BSP_STW_PACKAGE_SELECT := vps-vip-vpe
    else
         BSP_STW_PACKAGE_SELECT := all
    endif
endif

# Vision SDK QNX supports display only on A15
ifeq ($(A15_TARGET_OS),Qnx)
    BSP_STW_PACKAGE_SELECT := vps-vip-vpe
endif

ROOTDIR := $(vision_sdk_PATH)

XDCPATH = $(bios_PATH)/packages;$(ipc_PATH)/packages;$(xdc_PATH)/packages;$(edma_PATH)/packages;$(pdk_PATH)/packages;$(fc_PATH)/packages;$(vision_sdk_PATH);$(xdais_PATH)/packages;$(hdvicplib_PATH)/packages;$(jpegvdec_PATH)/packages;$(jpegvenc_PATH)/packages;$(ndk_PATH)/packages;$(nsp_PATH)/packages;$(avbtp_PATH)/packages;$(mm_PATH);$(ce_PATH)/packages;$(mm_PATH)/extrel/ti/ivahd_codecs/packages;$(mm_PATH)/src;$(OpenCL_PATH)/packages;$(uia_PATH)/packages;$(vision_sdk_PATH)/links_fw

edma_DRV_PATH = $(edma_PATH)/packages/ti/sdo/edma3/drv
edma_RM_PATH  = $(edma_PATH)/packages/ti/sdo/edma3/rm

# postfixes we require
_CORES     := M4 DSP EVE A15
# Check for the existence of each compiler!
$(foreach path,$(_CORES),$(if $(realpath $(CODEGEN_PATH_$(path))),,$(error CODEGEN_PATH_$(path) does not exist! ($(CODEGEN_PATH_$(path))))))
# prefixes we require...
_REQ_PATHS := xdc bios pdk edma evealg
_OPT_PATHS := ndk nsp avbtp hdvicplib jpegvdec jpegvenc vlib fc ipc xdais
ifeq ($(HS_DEVICE), yes)
_OPT_PATHS += tda3x_signing_tool
endif
# Check for the existence of each xxxxx_PATH variable! Error if it does not exist.
$(foreach path,$(_REQ_PATHS),$(if $(realpath $($(path)_PATH)),,$(error $(path)_PATH does not exist! ($($(path)_PATH)))))
$(foreach path,$(_OPT_PATHS),$(if $(realpath $($(path)_PATH)),,$(warning $(path)_PATH does not exist! ($($(path)_PATH)))))

ifeq ($(NDK_PROC_TO_USE),ipu1_1)
    ifeq ($(PROC_IPU1_1_INCLUDE),no)
        NDK_PROC_TO_USE=none
    endif
endif

ifeq ($(NDK_PROC_TO_USE),ipu1_0)
    ifeq ($(PROC_IPU1_0_INCLUDE),no)
        NDK_PROC_TO_USE=none
    endif
endif

ifeq ($(NDK_PROC_TO_USE),ipu2)
    ifeq ($(PROC_IPU2_INCLUDE),no)
        NDK_PROC_TO_USE=none
    endif
endif

ifeq ($(NDK_PROC_TO_USE),a15_0)
    ifeq ($(PROC_A15_0_INCLUDE),no)
        NDK_PROC_TO_USE=none
    endif
endif

ifeq ($(FATFS_PROC_TO_USE),ipu1_1)
    ifeq ($(PROC_IPU1_1_INCLUDE),no)
        FATFS_PROC_TO_USE=none
    endif
endif

ifeq ($(FATFS_PROC_TO_USE),ipu1_0)
    ifeq ($(PROC_IPU1_0_INCLUDE),no)
        FATFS_PROC_TO_USE=none
    endif
endif

ifeq ($(FATFS_PROC_TO_USE),ipu2)
    ifeq ($(PROC_IPU2_INCLUDE),no)
        FATFS_PROC_TO_USE=none
    endif
endif

ifeq ($(FATFS_PROC_TO_USE),a15_0)
    ifeq ($(PROC_A15_0_INCLUDE),no)
        FATFS_PROC_TO_USE=none
    endif
endif

#
# NDK/NSP on A15 with SMP BIOS has issues and hence disable networking
# support on A15, when A15 is running SMP Bios
#
ifeq ($(DUAL_A15_SMP_BIOS),yes)
    ifeq ($(NDK_PROC_TO_USE),a15_0)
        NDK_PROC_TO_USE=none
    endif
endif

IPU1_EVELOADER_INCLUDE=no
ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
    ifeq ($(PROC_EVE1_INCLUDE), yes)
        IPU1_EVELOADER_INCLUDE=yes
    endif
    ifeq ($(PROC_EVE2_INCLUDE), yes)
        IPU1_EVELOADER_INCLUDE=yes
    endif
    ifeq ($(PROC_EVE3_INCLUDE), yes)
        IPU1_EVELOADER_INCLUDE=yes
    endif
    ifeq ($(PROC_EVE4_INCLUDE), yes)
        IPU1_EVELOADER_INCLUDE=yes
    endif
endif

ifeq ($(PROFILE),debug)
CPU_IDLE_ENABLED=no
endif

PROC_EVE_INCLUDE = no
ifeq ($(PROC_EVE2_INCLUDE),yes)
    PROC_EVE_INCLUDE=yes
endif
ifeq ($(PROC_EVE3_INCLUDE),yes)
    PROC_EVE_INCLUDE=yes
endif
ifeq ($(PROC_EVE4_INCLUDE),yes)
    PROC_EVE_INCLUDE=yes
endif
ifeq ($(PROC_EVE1_INCLUDE),yes)
    PROC_EVE_INCLUDE=yes
endif

PROC_DSP_INCLUDE = no
ifeq ($(PROC_DSP1_INCLUDE),yes)
    PROC_DSP_INCLUDE=yes
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
    PROC_DSP_INCLUDE=yes
endif

#
# For TDA3xx, when NDK is enabled, FATFS cannot be used due to MMCSD conflict with RGMII0.
# To use MMCSD and NDK together, RGMII1 daughter board needs to be used.
#
ifeq ($(PLATFORM),$(filter $(PLATFORM), tda3xx-evm tda3xx-rvp))
    ifeq ($(NDK_PROC_TO_USE),ipu1_1)
        FATFS_PROC_TO_USE=none
    endif
    ifeq ($(NDK_PROC_TO_USE),ipu1_0)
        FATFS_PROC_TO_USE=none
    endif
    ifeq ($(NDK_PROC_TO_USE),a15_0)
        FATFS_PROC_TO_USE=none
    endif
endif

PROC_SINGLE_CORE = no
ifeq ($(PROC_DSP_INCLUDE)$(PROC_EVE_INCLUDE)$(PROC_A15_0_INCLUDE)$(PROC_IPU1_0_INCLUDE)$(PROC_IPU1_1_INCLUDE)$(PROC_IPU2_INCLUDE), nononoyesnono)
    PROC_SINGLE_CORE = yes
endif

BUILD_CPUS?=all

PROC_IPU1_0_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), ipu* ipu1* ipu1_0 all),yes,no)
PROC_IPU1_1_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), ipu* ipu1* ipu1_1 all),yes,no)
PROC_IPU2_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), ipu* ipu2 all),yes,no)
PROC_DSP1_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), dsp* dsp1 all),yes,no)
PROC_DSP2_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), dsp* dsp2 all),yes,no)
PROC_EVE1_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), eve* eve1 all),yes,no)
PROC_EVE2_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), eve* eve2 all),yes,no)
PROC_EVE3_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), eve* eve3 all),yes,no)
PROC_EVE4_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), eve* eve4 all),yes,no)
PROC_A15_0_BUILD_INCLUDE=$(if $(filter $(BUILD_CPUS), a15* a15_0 all),yes,no)

PROC_IPU_BUILD_INCLUDE=no
ifeq ($(PROC_IPU1_0_BUILD_INCLUDE),yes)
    PROC_IPU_BUILD_INCLUDE=yes
endif
ifeq ($(PROC_IPU1_1_BUILD_INCLUDE),yes)
    PROC_IPU_BUILD_INCLUDE=yes
endif
ifeq ($(PROC_IPU2_BUILD_INCLUDE),yes)
    PROC_IPU_BUILD_INCLUDE=yes
endif

PROC_DSP_BUILD_INCLUDE=no
ifeq ($(PROC_DSP1_BUILD_INCLUDE),yes)
    PROC_DSP_BUILD_INCLUDE=yes
endif
ifeq ($(PROC_DSP2_BUILD_INCLUDE),yes)
    PROC_DSP_BUILD_INCLUDE=yes
endif

PROC_EVE_BUILD_INCLUDE=no
ifeq ($(PROC_EVE1_BUILD_INCLUDE),yes)
    PROC_EVE_BUILD_INCLUDE=yes
endif
ifeq ($(PROC_EVE2_BUILD_INCLUDE),yes)
    PROC_EVE_BUILD_INCLUDE=yes
endif
ifeq ($(PROC_EVE3_BUILD_INCLUDE),yes)
    PROC_EVE_BUILD_INCLUDE=yes
endif
ifeq ($(PROC_EVE4_BUILD_INCLUDE),yes)
    PROC_EVE_BUILD_INCLUDE=yes
endif

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
	NEED_PROC_A15_0=yes
endif

ifeq ($(A15_TARGET_OS),Bios)
	NEED_PROC_IPU1_0=yes
endif

ifeq ($(IPU_PRIMARY_CORE),ipu2)
	NEED_PROC_IPU2=yes
endif

ifeq ($(IPU_PRIMARY_CORE),ipu1_0)
	NEED_PROC_IPU1_0=yes
endif

BOARD=$(PLATFORM)
export TREAT_WARNINGS_AS_ERROR
export BUILD_ADAM_CAR
export BUILD_OS
export BUILD_MACHINE
export PDK_BOARD
export PDK_SBL_CORE
export PLATFORM
export BOARD
export CORE
export PROFILE_ipu1_0
export PROFILE_ipu1_1
export PROFILE_ipu2
export PROFILE_c66xdsp_1
export PROFILE_c66xdsp_2
export PROFILE_arp32_1
export PROFILE_arp32_2
export PROFILE_arp32_3
export PROFILE_arp32_4
export PROFILE_a15_0
export CODEGEN_PATH_M4
export CODEGEN_PATH_DSP
export CODEGEN_PATH_EVE
export CODEGEN_PATH_A15
export bios_PATH
export ipc_PATH
export mm_PATH
export ce_PATH
export kernel_PATH
export cmem_PATH
export memcache_PATH
export debugss_PATH
export gdbc6x_PATH
export shm_PATH
export kernel_addon_PATH
export uboot_PATH
export sgx_PATH
export pvr_PATH
export xdc_PATH
export edma_PATH
export edma_DRV_PATH
export edma_RM_PATH
export pdk_PATH
export ndk_PATH
export nsp_PATH
export avbtp_PATH
export uia_PATH
export evealg_PATH
export fc_PATH
export xdais_PATH
export hdvicplib_PATH
export jpegvdec_PATH
export jpegvenc_PATH
export h264venc_PATH
export h264vdec_PATH
export vlib_PATH
export mathlib_PATH
export vision_sdk_RELPATH
export vision_sdk_PATH
export ROOTDIR
export XDCPATH
export KW_BUILD
export DDR_MEM
export DEST_ROOT
export PROC_DSP1_INCLUDE
export PROC_DSP2_INCLUDE
export PROC_DSP_INCLUDE
export PROC_EVE1_INCLUDE
export PROC_EVE2_INCLUDE
export PROC_EVE3_INCLUDE
export PROC_EVE4_INCLUDE
export PROC_EVE_INCLUDE
export PROC_A15_0_INCLUDE
export PROC_IPU1_0_INCLUDE
export PROC_IPU1_1_INCLUDE
export PROC_IPU2_INCLUDE
export NDK_PROC_TO_USE
export NSP_TFDTP_INCLUDE
export TDA2EX_ETHSRV_BOARD
export A15_TARGET_OS
export A15_TOOLCHAIN_PREFIX
export DEFAULT_UBOOT_CONFIG
export DEFAULT_KERNEL_CONFIG
export DEFAULT_DTB
export CMEM_INCLUDE
export LINUX_BOOT_OUT_FILES
export LINUX_TARGETFS
export BSP_STW_PACKAGE_SELECT
export AVB_INCLUDE
export IVAHD_INCLUDE
export VPE_INCLUDE
export DSS_INCLUDE
export CAL_INCLUDE
export ISS_INCLUDE
export ISS_ENABLE_DEBUG_TAPS
export WDR_LDC_INCLUDE
export IPU1_EVELOADER_INCLUDE
export lane_detect_PATH
export object_detect_PATH
export object_classification_PATH
export hcf_PATH
export VSDK_BOARD_TYPE
export CPU_IDLE_ENABLED
export stereo_postprocess_PATH
export scene_obstruction_detect_PATH
export infoadas_PATH
export BUILD_INFOADAS
export DCAN_INCLUDE
export DUAL_A15_SMP_BIOS
export FAST_BOOT_INCLUDE
export RTI_INCLUDE
export BUILD_ALGORITHMS
export RADAR_INCLUDE
export RADAR_BOARD
export FATFS_PROC_TO_USE
export PROC_SINGLE_CORE
export gpe_PATH
export sfm_PATH
export clr_PATH
export fcw_PATH
export ULTRASONIC_INCLUDE
export ECC_FFI_INCLUDE
export DCC_ESM_INCLUDE
export DATA_VIS_INCLUDE
export ENABLE_OPENCV
export ENABLE_OPENCV_TESTS
export BUILD_OPENCV_SRC
export OpenCV_SRC_PATH
export OpenCV_BUILD_PATH
export OpenCV_PREBUILD_PATH
export IPU_PRIMARY_CORE
export IPU_SECONDARY_CORE
export IPUMM_INCLUDE
export SRV_FAST_BOOT_INCLUDE
export OpenCL_PATH
export OPENCL_INCLUDE
export CLOCL
export TI_OCL_CGT_INSTALL
export BUILD_LLVM
export TARGET_ROOTDIR
export OpenVX_PATH
export openvx_INCLUDE
export VXLIB_PATH
export MAKECONFIG
export BUILD_DEPENDENCY_ALWAYS
export PROFILE
export radarLink_PATH
export mmwavelink_version
export radarMssFirmware_PATH
export radarBssFirmware_PATH
export HS_DEVICE
export MSHIELD_DK_DIR
export TI_SECURE_DEV_PKG
export TDA3X_SIGNING_TOOL_DIR
export PROC_A15_0_BUILD_INCLUDE
export PROC_IPU1_0_BUILD_INCLUDE
export PROC_IPU1_1_BUILD_INCLUDE
export PROC_IPU2_BUILD_INCLUDE
export PROC_DSP1_BUILD_INCLUDE
export PROC_DSP2_BUILD_INCLUDE
export PROC_EVE1_BUILD_INCLUDE
export PROC_EVE2_BUILD_INCLUDE
export PROC_EVE3_BUILD_INCLUDE
export PROC_EVE4_BUILD_INCLUDE
export PROC_DSP_BUILD_INCLUDE
export PROC_EVE_BUILD_INCLUDE
export PROC_IPU_BUILD_INCLUDE
export BUILD_CPUS
export NEED_PROC_IPU1_0
export NEED_PROC_IPU1_1
export NEED_PROC_IPU2
export NEED_PROC_A15_0
export NEED_PROC_DSP1
export NEED_PROC_DSP2
export NEED_PROC_EVE1
export NEED_PROC_EVE2
export NEED_PROC_EVE3
export NEED_PROC_EVE4
export ROBUST_RVC_INCLUDE
export IPC_LIB_INCLUDE
export SAFE_IPC_INCLUDE
export OPENVX_INCLUDE
export ENABLE_UART_LOG
export ENABLE_NETWORK_LOG
export ENABLE_CCS_LOG
export WORKQ_INCLUDE
export CIO_REDIRECT
export TDA2EX_17X17
export tidl_PATH
export ENABLE_UIA_PROFILING
export dmautils_PATH
export algframework_PATH
export UTILSPATH
export ENABLE_TASK_PROFILE_UTIL
export EARLY_SRV_ENABLE

ifeq ($(MAKERULEDIR),)
  MAKERULEDIR := $(ROOTDIR)/build/rtos/makerules
  export MAKERULEDIR
endif
