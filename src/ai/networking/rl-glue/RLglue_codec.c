/* 
* Copyright (C) 2007, Andrew Butcher

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
* 
*  $Revision$
*  $Date$
*  $Author$
*  $HeadURL$
* 
*/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h> /* assert  */
#include <unistd.h> /* sleep   */
#include <string.h> /* strlen */ /* I'm sorry about using strlen. */
#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* calloc, getenv, exit */

#include <ctype.h> /* isdigit */
#include <netdb.h> /* gethostbyname */
#include <arpa/inet.h> /* inet_ntoa */

#include <rlglue/Environment_common.h>
#include <rlglue/network/RL_network.h>

/* Include the utility methods*/
#include <rlglue/utils/C/RLStruct_util.h>

// Customization: for StellaAI
static int theConnection;


static const char* kUnknownMessage = "Unknown Message: %s\n";

static action_t ce_globalaction                 = {0};
static state_key_t ce_globalstatekey            = {0};
static random_seed_key_t ce_globalrandomseedkey = {0};
static rlBuffer ce_globalrlbuffer               = {0};
static char* ce_globalinmessage = 0;
static unsigned int ce_globalinmessagecapacity = 0;

static void onEnvInit(int theConnection) {
	const char * theTaskSpec = 0;
	unsigned int theTaskSpecLength = 0;
	unsigned int offset = 0;

	/* Read the data in the buffer (data from server) */
	/* No data to read .... */

	/* Call RL method on the recv'd data */
	theTaskSpec = env_init();
	if (theTaskSpec != NULL) {
		theTaskSpecLength = strlen(theTaskSpec);
	}

	/* Prepare the buffer for sending data back to the server */
	rlBufferClear(&ce_globalrlbuffer);
	offset = rlBufferWrite(&ce_globalrlbuffer, offset, &theTaskSpecLength, 1, sizeof(int));
	if (theTaskSpecLength > 0) {
		offset = rlBufferWrite(&ce_globalrlbuffer, offset, theTaskSpec, theTaskSpecLength, sizeof(char));
	}
}

static void onEnvStart(int theConnection) {
  const observation_t *theObservation=0;
          unsigned int offset = 0;

  theObservation=env_start();
  __RL_CHECK_STRUCT(theObservation)

  rlBufferClear(&ce_globalrlbuffer);
  offset = rlCopyADTToBuffer(theObservation, &ce_globalrlbuffer, offset);
}

static void onEnvStep(int theConnection) {
  const reward_observation_t *ro = 0;
  unsigned int offset = 0;

  offset = rlCopyBufferToADT(&ce_globalrlbuffer, offset, &ce_globalaction);
  __RL_CHECK_STRUCT(&ce_globalaction);

  ro = env_step(&ce_globalaction);        
  __RL_CHECK_STRUCT(ro->observation)


  rlBufferClear(&ce_globalrlbuffer);
  offset = 0;
  offset = rlBufferWrite(&ce_globalrlbuffer, offset, &ro->terminal, 1, sizeof(int));
  offset = rlBufferWrite(&ce_globalrlbuffer, offset, &ro->reward, 1, sizeof(double));
  offset = rlCopyADTToBuffer(ro->observation, &ce_globalrlbuffer, offset);
}

static void onEnvCleanup(int theConnection) {
	env_cleanup();
	rlBufferClear(&ce_globalrlbuffer);

	clearRLStruct(&ce_globalaction);
	clearRLStruct(&ce_globalrandomseedkey);
	clearRLStruct(&ce_globalstatekey);
	if(ce_globalinmessage!=0)
		free(ce_globalinmessage);


	ce_globalinmessage = 0;
	ce_globalinmessagecapacity = 0;
}

static void onEnvSetState(int theConnection) {
  unsigned int offset = 0;

  offset = rlCopyBufferToADT(&ce_globalrlbuffer, offset, &ce_globalstatekey);
  env_set_state(&ce_globalstatekey);

  rlBufferClear(&ce_globalrlbuffer);
}

static void onEnvSetRandomSeed(int theConnection) {
  unsigned int offset = 0;

  offset = rlCopyBufferToADT(&ce_globalrlbuffer, offset, &ce_globalrandomseedkey);  
  env_set_random_seed(&ce_globalrandomseedkey);

  rlBufferClear(&ce_globalrlbuffer);
}

static void onEnvGetState(int theConnection) {
  const state_key_t *key = 0;
  unsigned int offset = 0;

  key = env_get_state();
  __RL_CHECK_STRUCT(key);

  rlBufferClear(&ce_globalrlbuffer);
  offset = rlCopyADTToBuffer(key, &ce_globalrlbuffer, offset);
}

static void onEnvGetRandomSeed(int theConnection) {
  const random_seed_key_t *key = 0;
  unsigned int offset = 0;

  key=env_get_random_seed();
  __RL_CHECK_STRUCT(key);


  rlBufferClear(&ce_globalrlbuffer);
  rlCopyADTToBuffer(key, &ce_globalrlbuffer, offset);
}


/*
	- Remember that ce_globalinmessage is a global variable
*/
static void onEnvMessage(int theConnection) {
  unsigned int inMessageLength = 0;
  unsigned int outMessageLength = 0;
  char* inMessage = 0;
  const char* outMessage = 0;
  unsigned int offset = 0;

  offset = 0;
  offset = rlBufferRead(&ce_globalrlbuffer, offset, &inMessageLength, 1, sizeof(int));
  
  /*Check if the length of the message we're getting is too big
    If it is too big, allocate more space                                         */
  if (inMessageLength >= ce_globalinmessagecapacity) {
          /*We make it size + 1 so we can be sure that we can null terminate it*/
          inMessage = (char*)calloc(inMessageLength+1, sizeof(char));
          /*Free the old one (might be null, but that's safe)*/
          free(ce_globalinmessage);

          ce_globalinmessage = inMessage;
          ce_globalinmessagecapacity = inMessageLength;
  }

  /*If there was a message, read it off the buffer*/
  if (inMessageLength > 0) {
          offset = rlBufferRead(&ce_globalrlbuffer, offset, ce_globalinmessage, inMessageLength, sizeof(char));
  }
  /*Make sure to null terminate the string */
   ce_globalinmessage[inMessageLength]='\0';

  outMessage = env_message(ce_globalinmessage);

  if (outMessage != NULL) {
          outMessageLength = strlen(outMessage);
  }


  /* we want to start sending, so we're going to reset the offset to 0, 
                                                  so we write the the beginning of the buffer */
  rlBufferClear(&ce_globalrlbuffer);
  offset = 0;
  offset = rlBufferWrite(&ce_globalrlbuffer, offset, &outMessageLength, 1, sizeof(int));
  if (outMessageLength > 0) {
          offset = rlBufferWrite(&ce_globalrlbuffer, offset, outMessage, outMessageLength, sizeof(char));
  }
}

static void runEnvironmentEventLoop(int theConnection) {
  int envState = 0;
  
  // Customization: don't do a loop here anymore because we're calling this from
  // an external context (eg. StellaAI) via methods below.

  rlBufferClear(&ce_globalrlbuffer);
  rlRecvBufferData(theConnection, &ce_globalrlbuffer, &envState);

  switch(envState) {
  case kEnvInit:
    onEnvInit(theConnection);
    break;

  case kEnvStart:
    onEnvStart(theConnection);
    break;

  case kEnvStep:
    onEnvStep(theConnection);
    break;

  case kEnvCleanup:
    onEnvCleanup(theConnection);
    break;

  case kEnvSetState:
    onEnvSetState(theConnection);
    break;

  case kEnvSetRandomSeed:
    onEnvSetRandomSeed(theConnection);
    break;

  case kEnvGetState:
    onEnvGetState(theConnection);
    break;

  case kEnvGetRandomSeed:
    onEnvGetRandomSeed(theConnection);
    break;

  case kEnvMessage:
    onEnvMessage(theConnection);
    break;

  case kRLTerm:
    break;

  default:
    fprintf(stderr, kUnknownMessage, envState);
    exit(0);
    break;
  };

  rlSendBufferData(theConnection, &ce_globalrlbuffer, envState);

}

// These are the aditions that replace main (StellaAI calls these)

int rlStartEnvironment(char *host, int port){
  theConnection = 0;
  rlBufferCreate(&ce_globalrlbuffer, 4096);
  theConnection = rlWaitForConnection(host, port, kRetryTimeout);
  rlBufferClear(&ce_globalrlbuffer);
  rlSendBufferData(theConnection, &ce_globalrlbuffer, kEnvironmentConnection);
  return theConnection;
}

void rlUpdateEnvironment(){
  runEnvironmentEventLoop(theConnection);
}

void rlEndEnvironment(){
  rlClose(theConnection);
  rlBufferDestroy(&ce_globalrlbuffer);
}


/* 
int main(int argc, char** argv) {
  int theConnection = 0;

  const char *usage = "The following environment variables are used by the environment to control its function:\n"
    "RLGLUE_HOST  : If set the environment will use this ip or hostname to connect to rather than %s\n"
	"RLGLUE_PORT  : If set the environment will use this port to connect on rather than %d\n"; 
	 
  struct hostent *host_ent;

  char* host = kLocalHost;
  short port = kDefaultPort;

  char* envptr = 0;

  if (argc > 1) {
    fprintf(stderr, usage, kLocalHost, kDefaultPort);
    exit(1);
  }

  host = getenv("RLGLUE_HOST");
  if (host == 0) {
    host = kLocalHost;
  }

  envptr = getenv("RLGLUE_PORT");  
  if (envptr != 0) {
    port = strtol(envptr, 0, 10);
    if (port == 0) {
      port = kDefaultPort;
    }
  }


  if (isalpha(host[0])) {
    host_ent = gethostbyname(host); 
    host = inet_ntoa(*(struct in_addr*)host_ent->h_addr);
  }

  fprintf(stdout, "RL-Glue C Environment Codec Version %s, Build %s\n\tConnecting to host=%s on port=%d...\n", VERSION,__rlglue_get_svn_version(),host, port);
	fflush(stdout);


  // Allocate what should be plenty of space for the buffer - 
	//		it will dynamically resize if it is too small 
  rlBufferCreate(&ce_globalrlbuffer, 4096);
  
    theConnection = rlWaitForConnection(host, port, kRetryTimeout);
	fprintf(stdout, "\tRL-Glue C Environment Codec :: Connected\n");
    rlBufferClear(&ce_globalrlbuffer);
    rlSendBufferData(theConnection, &ce_globalrlbuffer, kEnvironmentConnection);
    runEnvironmentEventLoop(theConnection);
    rlClose(theConnection);

  rlBufferDestroy(&ce_globalrlbuffer);

  return 0;
}

*/

