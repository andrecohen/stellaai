MODULE := src/ai

MODULE_OBJS := \
       	src/ai/AIBase.o \
        src/ai/AIRewards.o \
        src/ai/AIScript.o \
        src/ai/AISettings.o \
        src/ai/networking/rl-glue/RLglue_codec.o \
        src/ai/networking/AIGlue.o \
  	src/ai/networking/AIGlueEnv.o \
 	 src/ai/networking/AIProtocol.o \
        src/ai/networking/AIPlainText.o \
        src/ai/networking/AISocket.o 

MODULE_DIRS += \
	src/ai

LIBS += -llua -lrlgluenetdev

# Include common rules 
include $(srcdir)/common.rules
