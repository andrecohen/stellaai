MODULE := src/ai

MODULE_OBJS := \
	src/ai/AIBase.o \
	src/ai/AIComm.o \
	src/ai/AISocket.o \
	src/ai/AIRewards.o

# removed src/ai/AIBasicCluster.o \
#         src/ai/AICentroid.o \
#	        src/ai/AIKmeans.o \
#         src/ai/AICluster.o \
#         src/ai/Classify.o \
#         src/ai/FastCluster.o \
#         src/ai/Pitfall.o 
	
MODULE_DIRS += \
	src/ai

# Include common rules 
include $(srcdir)/common.rules
