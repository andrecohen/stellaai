The default protocol is PlainTextProtocol. To change it you must create a settings file for StellaAI.

  1. In the same directory as StellaAI create the file `aisettings.txt`
  1. Add the line `enabled_protocol=X` where `X` can be
    * 1 = PlainTextProtocol
    * 2 = RL-Glue
    * 0 = No protocol