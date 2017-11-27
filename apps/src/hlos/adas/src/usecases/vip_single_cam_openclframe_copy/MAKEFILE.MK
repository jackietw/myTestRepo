
include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_header_a15.mk

INCLUDE+= $(SGX_DRM_INC) $(OSA_INC) -I$($(MAKEAPPNAME)_PATH)

LIBS += $(LIB_BASE_DIR)/vision_sdk_linux_demo.a
LIBS += $(shell cat $(DEST_ROOT)/appLiblist_a15_0.txt)

include $(vision_sdk_PATH)/build/hlos/makerules/linux/common_footer_a15.mk
