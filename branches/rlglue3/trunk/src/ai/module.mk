MODULE := src/ai

MODULE_OBJS := \
	src/ai/AIBase.o \
	src/ai/AIPattern.o \
	src/ai/AIRewards.o \
	src/ai/AIScript.o \
	src/ai/AISettings.o \
	src/ai/networking/AIGlue.o \
	src/ai/networking/AIGlueEnv.o \
	src/ai/networking/AIProtocol.o \
	src/ai/networking/AIPlainText.o \
	src/ai/networking/AISocket.o \
	src/ai/networking/rl-glue/C_TaskSpec_Parser.o \
	src/ai/networking/rl-glue/RLStruct_util.o \
	src/ai/networking/rl-glue/RL_client_environment.o \
	src/ai/networking/rl-glue/RL_network_environment.o \
	src/ai/networking/rl-glue/RL_network.o 

MODULE_DIRS += \
	src/ai

LIBS += -llua

# Include common rules 
include $(srcdir)/common.rules
