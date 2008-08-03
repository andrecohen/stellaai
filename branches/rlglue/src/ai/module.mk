MODULE := src/ai

MODULE_OBJS := \
	src/ai/AIBase.o \
	src/ai/AIRewards.o \
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

#	Removed these.. they're only used in the direct connection
#	src/ai/networking/rl-glue/RL_network.o \
#	src/ai/networking/rl-glue/RL_network_glue.o \
#
#
#	src/ai/networking/rl-glue/RL_client_agent.o \
#	src/ai/networking/rl-glue/RL_client_experiment.o \
#	src/ai/networking/rl-glue/RL_direct_agent.o \
#	src/ai/networking/rl-glue/RL_direct_environment.o \
#	src/ai/networking/rl-glue/RL_direct_experiment.o \
#	src/ai/networking/rl-glue/RL_network_experiment.o \
#	src/ai/networking/rl-glue/RL_network_agent.o \
#	src/ai/networking/rl-glue/RL_server_agent.o \
#	src/ai/networking/rl-glue/RL_server_experiment.o \
#	src/ai/networking/rl-glue/RL_glue.o \
#	src/ai/networking/rl-glue/RL_server_environment.o \

MODULE_DIRS += \
	src/ai

# Include common rules 
include $(srcdir)/common.rules
