# File name: build_sbl.mk
#            This file builds the SBL from PDK package

#
# SBL options,
# -------------------
# EMIF_MODE        = SINGLE_EMIF_512MB (default) or
#                    DUAL_EMIF_1GB_512MB or
#                    DUAL_EMIF_2X512MB or
#                    SINGLE_EMIF_256MB
# NOTE:
# DUAL_EMIF_1GB_512MB : uses EMIF2 - 1GB and EMIF1 512MB, BUT in non-interleaved mode
#                       Vision SDK uses only 1GB hence effectivly this is single EMIF
#                       non-interleaved mode for Vision SDK
#                       0x8000_0000 - 0xBFFF_FFFF is mapped to EMIF2
#                       0xC000_0000 - 0xDFFF_FFFF is mapped to EMIF1
# DUAL_EMIF_2X512MB   : uses EMIF1 and EMIF 512MB each in interleaved mode
#                       0x8000_0000 - 0x9FFF_FFFF is interleaved between EMIF1 and EMIF2
# SINGLE_EMIF_256MB   : uses EMIF1 with 256MB
#                       0x8000_0000 - 0x8FFF_FFFF is mapped to EMIF1
# SINGLE_EMIF_512MB   : uses EMIF1 with 512MB
#                       0x8000_0000 - 0x9FFF_FFFF is mapped to EMIF1
#

PDK_BUILD_OPTIONS  = MAKERULEDIR=$(pdk_PATH)/packages/ti/build/makerules PDK_INSTALL_PATH=$(pdk_PATH)/packages
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_GCC=$(CODEGEN_PATH_A15) TOOLCHAIN_PATH_TI_CGT=$(CODEGEN_PATH_M4) C6X_GEN_INSTALL_PATH=$(CODEGEN_PATH_DSP)
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_EVE=$(CODEGEN_PATH_EVE) BIOS_INSTALL_PATH=$(bios_PATH) XDC_INSTALL_PATH=$(xdc_PATH)
PDK_BUILD_OPTIONS += EDMA3LLD_BIOS6_INSTALLDIR=$(edma_PATH) radarLink_PATH=$(radarLink_PATH)
PDK_BUILD_OPTIONS += utils_PATH=$(UTILSPATH)

PDK_SBL_BUILD_OPTIONS = $(PDK_BUILD_OPTIONS) EMIF_MODE=SINGLE_EMIF_512MB
ifneq ($(ECC_FFI_INCLUDE),yes)
PDK_SBL_BUILD_OPTIONS+= SBL_CONFIG=disable_safety
endif

ifeq ($(FAST_BOOT_INCLUDE), yes)
PDK_SBL_BUILD_OPTIONS+= SBL_CONFIG=disable_safety SBL_BUILD_MODE=prod SBL_OPT_MODE=high
endif

ifeq ($(HS_DEVICE),yes)
PDK_SBL_BUILD_OPTIONS += BUILD_HS=yes
PDK_SBL_BUILD_OPTIONS += MSHIELD_DK_DIR=$(MSHIELD_DK_DIR)
endif

sbl:
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE) BUILD_PROFILE=$(PROFILE_$(PDK_SBL_CORE))
ifeq ($(HS_DEVICE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/boot/sbl_auto/sbl_app -fmakefile_mshield.mk $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE) 2>/dev/null >/dev/null
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE)
endif
#Build the tools required for flashing as well - only IPU build supported
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ qspi_flash_writer $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ nor_flash_writer  $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0

sbl_clean:
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps_clean $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE)
ifeq ($(HS_DEVICE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps_clean $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE)
endif
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ qspi_flash_writer_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ nor_flash_writer_clean  $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0
