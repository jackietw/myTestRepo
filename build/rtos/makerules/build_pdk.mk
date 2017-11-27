# File name: build_pdk.mk
#            This file builds the PDK libs.

PDK_BUILD_OPTIONS = MAKERULEDIR=$(pdk_PATH)/packages/ti/build/makerules PDK_INSTALL_PATH=$(pdk_PATH)/packages
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_GCC=$(CODEGEN_PATH_A15) TOOLCHAIN_PATH_TI_CGT=$(CODEGEN_PATH_M4) C6X_GEN_INSTALL_PATH=$(CODEGEN_PATH_DSP)
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_EVE=$(CODEGEN_PATH_EVE) BIOS_INSTALL_PATH=$(bios_PATH) XDC_INSTALL_PATH=$(xdc_PATH)
PDK_BUILD_OPTIONS += EDMA3LLD_BIOS6_INSTALLDIR=$(edma_PATH) radarLink_PATH=$(radarLink_PATH)
PDK_BUILD_OPTIONS += utils_PATH=$(UTILSPATH)
PDK_BUILD_OPTIONS += INCLUDE_DUMMY_OSAL=no
PDK_BUILD_OPTIONS += PACKAGE_VIP=yes
PDK_BUILD_OPTIONS += INCLUDE_SYSBIOS=yes

ifeq ($(VPE_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_VPE=yes
else
PDK_BUILD_OPTIONS += PACKAGE_VPE=no
endif

ifeq ($(CAL_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_CAL=yes
else
PDK_BUILD_OPTIONS += PACKAGE_CAL=no
endif

ifeq ($(ISS_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_ISS=yes
else
PDK_BUILD_OPTIONS += PACKAGE_ISS=no
endif

ifeq ($(DSS_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_DSS=yes
else
PDK_BUILD_OPTIONS += PACKAGE_DSS=no
endif

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
ifeq ($(EARLY_SRV_ENABLE),yes)
PDK_BUILD_OPTIONS += VSDK_OPTIM_SENSOR_INIT=yes
endif
ifeq ($(ROBUST_RVC_INCLUDE),yes)
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C2=yes
else
ifeq ($(PLATFORM), tda2xx-evm)
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C0=yes VPS_DISABLE_I2C2=yes VPS_DISABLE_I2C3=yes VPS_DISABLE_I2C4=yes
else
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C0=yes VPS_DISABLE_I2C2=yes VPS_DISABLE_I2C3=yes VPS_DISABLE_I2C1=yes
endif
endif
endif

pdk:
ifeq ($(PROC_IPU_BUILD_INCLUDE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0 BUILD_PROFILE=$(PROFILE_ipu1_0)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_1 BUILD_PROFILE=$(PROFILE_ipu1_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu2_0 BUILD_PROFILE=$(PROFILE_ipu2)
endif
ifeq ($(PROC_DSP_BUILD_INCLUDE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66x BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_1 BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_2 BUILD_PROFILE=$(PROFILE_c66xdsp_2)
endif
ifeq ($(PROC_EVE_BUILD_INCLUDE),yes)
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2px-evm tda3xx-evm tda3xx-rvp))
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_1 BUILD_PROFILE=$(PROFILE_arp32_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_2 BUILD_PROFILE=$(PROFILE_arp32_2)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_3 BUILD_PROFILE=$(PROFILE_arp32_3)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_4 BUILD_PROFILE=$(PROFILE_arp32_4)
endif
endif
ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(PROC_A15_0_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Bios)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=a15_0 BUILD_PROFILE=$(PROFILE_a15_0)
endif
endif
endif

pdk_clean:
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0 BUILD_PROFILE=$(PROFILE_$(IPU_PRIMARY_CORE))
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_1 BUILD_PROFILE=$(PROFILE_ipu1_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu2_0 BUILD_PROFILE=$(PROFILE_ipu2)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66x BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_1 BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_2 BUILD_PROFILE=$(PROFILE_c66xdsp_2)
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2px-evm tda3xx-evm tda3xx-rvp))
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_1 BUILD_PROFILE=$(PROFILE_arp32_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_2 BUILD_PROFILE=$(PROFILE_arp32_2)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_3 BUILD_PROFILE=$(PROFILE_arp32_3)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_4 BUILD_PROFILE=$(PROFILE_arp32_4)
endif
ifeq ($(PROC_A15_0_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Bios)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=a15_0 BUILD_PROFILE=$(PROFILE_a15_0)
endif
endif

