
$(call SAVE_CONTEXT)

LOCAL_PATH := $(call my-dir)

INCLUDE_DIRS := $(call all-dirs-under, .)

LOCAL_CFLAGS += -I$(LOCAL_PATH)

LOCAL_CFLAGS += $(addprefix -I$(LOCAL_PATH)/, $(INCLUDE_DIRS))

SRC_FILES := $(call all-c-files-under, .)

LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/, $(SRC_FILES))
$(call RESTORE_CONTEXT)

