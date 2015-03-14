There are several steps you need to do to get StellaAI running using RL-Glue 3 with an RL-Glue 3 compatible agent. This document describes how to do so.

### 1. Download the required packages. ###

You'll need:
  * RL-Glue 3. Get a stable package from [RL-Glue project page](http://code.google.com/p/rl-glue/)
  * RL-Glue extensions (C codec). Get a stable package from [RL-Glue extensions page](http://code.google.com/p/rl-glue-ext/)
  * StellaAI RL-Glue 3 branch source code. Detailed instructions on how to do this below.
  * An RL-Glue 3 compatible random agent, [atari\_random\_rlglue3.tar.gz](http://www.cs.ualberta.ca/~lanctot/files/atari_random_rlglue3.tar.gz)

### 2. Install RL-Glue 3. ###

If you downloaded RC2 and want to install it as root:
```
tar -xzvf rlglue-3.0-RC2.tar.gz
cd rlglue-3.0-RC2
./configure
make
make check
sudo make install
```

Or, as a regular user with prefix /home/username:
```
tar -xzvf rlglue-3.0-RC2.tar.gz
cd rlglue-3.0-RC2
./configure --prefix=/home/username
make
make check
make install
```

### 3. Install RL-Glue C codec. ###

If you downloaded version 2.0 of the codec and want to install it as root:
```
tar -xzvf c-codec-2.0-RC2.tar.gz
cd c-codec-2.0
./configure
make
sudo make install
```

Or, as a regular user with prefix /home/username:
```
tar -xzvf c-codec-2.0-RC2.tar.gz
cd c-codec-2.0
./configure --prefix=/home/username --with-rl-glue=/home/username
make
make install
```

### 4. Get RL-Glue 3 enabled StellaAI ###

At the moment this is in a branch. Maybe later when RL-Glue 3 is officially release it will be merged into the trunk.

To get a read/write copy`***`:
```
svn checkout https://stellaai.googlecode.com/svn/branches/rlglue3 stellaai --username your.username
```

To get a read-only copy:
```
svn checkout http://stellaai.googlecode.com/svn/branches/rlglue3 stellaai
```

`***` Note: right now, for some reason, the read/write copy doesn't seem available to anybody other than the person who created the branch (Marc Lanctot). We're looking into this.

Build it as normal to produce the `stella` executable.

### 5. Compile the Agent. ###

```
tar -xzvf atari_random_rlglue3.tar.gz
cd atari_random_rlglue3
make
```

This will produce the ./RL\_agent executable.

### 6. Compile an Experiment program. ###

There is an example skeleton experiment file in `rlglue-3.0-RC2/examples/skeleton`. Before you build it, read the next few paragraphs.

You can use this experiment program as a starting point. Note, you may need to run make like so:

```
CFLAGS=-I/usr/local/include LDFLAGS=-L/usr/local/lib make
```

or

```
CFLAGS=-I/home/username/include LDFLAGS=-L/home/username/lib make
```

The Atari environment/agent does not support multiple episodes yet. So in `SkeletonAgent` you have to remove all the runEpisode statements except the last one runEpisode(0); which has no limit. This means there will be one episode that runs indefinitely.

Building in support for multiple episodes won't be trivial in the case of Atari because you may have to completely restart the emulator. If not, you'll have to figure out how to "re-initialize it" to its initial state before running a game, and call that function from within the environment when RL-Glue requests a new env\_start(). This may be fixed sooner or later by Chris Rayner.

### 7. Run all four required RL-Glue components. ###

The order with which you start these should not matter. I'm presenting you with the order I use. In four different terminals,

  * Start the main RL-Glue executable: `rl_glue`
  * Start the experiment program.
  * Start the agent `RL_agent`.
  * Start StellaAI _with a ROM as the argument_ (otherwise the random agent will happily navigate your filesystem for a ROM to load!): `./stella ~/Pitfall.bin` .