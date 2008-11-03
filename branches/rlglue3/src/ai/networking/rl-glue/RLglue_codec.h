
#ifndef __RLGLUE_CODEC_H
#define __RLGLUE_CODEC_H

#ifdef __APPLE__
#if __cplusplus
extern "C" {
#endif
#endif

int rlStartEnvironment(char *host, int port);
void rlUpdateEnvironment();
void rlEndEnvironment();

#ifdef __APPLE__
#if __cplusplus
}
#endif
#endif
	
#endif

