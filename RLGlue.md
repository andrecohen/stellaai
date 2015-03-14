[RL-Glue](http://rlai.cs.ualberta.ca/RLBB/top.html) is a software framework for reinforcement learning.

A project that uses RL-Glue must use RL-Glue's four main components:
  * the environment
  * the experiment
  * the agent
  * the glue

The environment is the implementation of the "reinforcement learning problem" (eg. Mountain Car), the agent is the implementation of the "algorithm" or the decision-maker (eg. Sarsa), the experiment program runs the algorithm on the environment, and the glue binds them altogether.

In StellaAI, `AIGlue` object implements the RL-Glue AIProtocol used by Stella to make decisions. The actual implementation of the environment (the `env_` functions) is is `src/ai/AIGlueEnv.cpp`. To enable the RL-Glue environment, set enabled\_protocol to the value of PROTOCOL\_RLGLUE.

The implementations of RL-Glue agents for StellaAI are kept separately at the moment. If you would like them please contact Marc Lanctot.

The experiment and RL-Glue are used from the main RL-Glue distribution.

To start an experiment using RL-Glue, load all four RL-Glue component executables. Note that when StellaAI's enabled protocol is set to PROTOCOL\_RLGLUE, it will act as the RL-Glue environment.