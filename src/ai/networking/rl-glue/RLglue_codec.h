
#ifndef __RLGLUE_CODEC_H
#define __RLGLUE_CODEC_H


#if __MACOSX__
extern "C" {
#endif

int rlStartEnvironment(char *host, int port);
void rlUpdateEnvironment();
void rlEndEnvironment();


#if __MACOSX__
}
#endif

#endif

