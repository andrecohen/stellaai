
#ifndef __RLGLUE_CODEC_H
#define __RLGLUE_CODEC_H

#if __cplusplus
extern "C" {
#endif

int rlStartEnvironment(char *host, int port);
void rlUpdateEnvironment();
void rlEndEnvironment();

#if __cplusplus
}
#endif
	
#endif

