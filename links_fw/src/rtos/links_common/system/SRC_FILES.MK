
SRCS_COMMON +=  system_linkApi.c \
                system_linkApi_local.c system_common.c \
                system_ipc.c system_ipc_msgq.c \
                system_tsk_multi_mbx.c \
                system_openvxipc.c \
                system_work_queue_if.c \
                system_work_queue_tsk.c \
                system_work_queue_unit_test.c \
                system_initDeinitLinks.c \

ifeq ($(IPC_LIB_INCLUDE), no)
SRCS_COMMON += system_ipc_bios_ipc.c
endif

ifeq ($(IPC_LIB_INCLUDE), yes)
SRCS_COMMON += system_ipc_ipc_lib.c
endif


SRCS_MULTI_MBX =

SRCS_SINGLE_MBX =

SRCS_arp32_1   += $(SRCS_MULTI_MBX)
SRCS_arp32_2   += $(SRCS_MULTI_MBX)
SRCS_arp32_3   += $(SRCS_MULTI_MBX)
SRCS_arp32_4   += $(SRCS_MULTI_MBX)

SRCS_c66xdsp_1 += $(SRCS_MULTI_MBX)
SRCS_c66xdsp_2 += $(SRCS_MULTI_MBX)

SRCS_a15_0     += $(SRCS_SINGLE_MBX)
SRCS_ipu1_1    += $(SRCS_SINGLE_MBX)

SRCS_$(IPU_PRIMARY_CORE)    += $(SRCS_SINGLE_MBX)
SRCS_$(IPU_SECONDARY_CORE)      += $(SRCS_SINGLE_MBX)

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
SRCS_$(IPU_PRIMARY_CORE) += system_rpmsg.c
SRCS_ipu1_1 += system_rpmsg.c
SRCS_$(IPU_SECONDARY_CORE) += system_rpmsg.c
SRCS_c66xdsp_1 += system_rpmsg.c
SRCS_c66xdsp_2 += system_rpmsg.c
endif
