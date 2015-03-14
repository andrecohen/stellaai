# Downloading #

Enter the terminal and type:
`svn checkout http://stellaai.googlecode.com/svn/trunk/ stellaai`

# Compiling #

### Selecting the Protocol ###

You must choose which protocol to use with StellaAI. To do so you must edit the variable `enabled_protocol` that is located in src/ai/AIBase.cpp. The three possible values are

  * `PROTOCOL_NONE` - No protocol is used (standalone emulator)
  * `PROTOCOL_PLAINTEXT` - Plain text protocol
  * `PROTOCOL_RLGLUE` - RL-Glue protocol

### Linux ###

  1. Run `./configure`
  1. If successful you are ready to `make`

### Mac OSX ###

Open the XCode project file that is located in `src/macosx` folder. Then just click Build.

### Windows ###

Not currently being supported.

# Running #

### By itself ###

Simply type `./stella` followed by the rom filepath of your choice.

### With Plain Text Protocol ###

Begin the PTP Agent and then call StellaAI as if it was running by itself.

### With RL-Glue ###

Start RL-Glue, agent and experiment then call StellaAI the same way as above.