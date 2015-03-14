Once you've successfully compiled StellaAI, you will probably want to know how it works. This page describes the flow of execution of the program.

![http://www.cs.ualberta.ca/~lanctot/files/stellaai-execflow.png](http://www.cs.ualberta.ca/~lanctot/files/stellaai-execflow.png)

First, the entry point of the program `main()` is found in `src/common/mainSDL.cxx`.

After some combination of calls, Stella enters its main loop `OSystem::mainLoop` in `src/emucore/OSystem.cxx`. The main loop code is small, and starts with the hook into the AI module:

```
mainloop()
{
  for(;;)
  {
    aiBase->update();

    myTimingInfo.start = getTicks();
    myEventHandler->poll(myTimingInfo.start);
    if(myQuitLoop) break;  // Exit if the user wants to quit
    myFrameBuffer->update();
    myTimingInfo.current = getTicks();
    myTimingInfo.virt += myTimePerFrame;

    //if(myTimingInfo.current < myTimingInfo.virt)
    //  SDL_Delay((myTimingInfo.virt - myTimingInfo.current) / 1000);

    myTimingInfo.totalTime += (getTicks() - myTimingInfo.start);
    myTimingInfo.totalFrames++;
  }
}
```

`AIBase::update` gets the current state of the screen, and uses its AIProtocol object to communicate with an external decision-maker. Currently, two protocols are implemented: a plain text protocol, and an RL-Glue protocol.

The decision-maker inspects the current state, sends back its decision of what to do (SDL joystick keys) which then gets fed into the appropriate Stella keyboard-handling objects, and the main loop continues.