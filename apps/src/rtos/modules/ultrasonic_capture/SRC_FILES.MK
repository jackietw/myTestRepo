
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/ultrasonic_capture

SRCS_$(IPU_PRIMARY_CORE) += \
		ultrasonicCaptureLink_tsk.c \
		ultrasonicCaptureLink_hw.c \

