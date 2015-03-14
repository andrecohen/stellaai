# Introduction #

Every ROM may have one LUA script file in the rewards folder. The file is expected to be named <rom filename>.lua and is loaded at the start of StellaAI. Inside the file one may declare global variables and functions that can be called either internally from the script or from StellaAI's C++ code.

## The update function ##

It is expected that if a ROM has a LUA script, it also contains the update function. The update function is called every frame cycle and it is there that things such as updating the number of lives, calculating the reward, and detecting death is done.

## Functions available inside LUA ##

  * `log(X)` prints X to the terminal (very useful for debugging scripts).
  * `getRam(X)` returns value of specific RAM location.
  * `toHex(X)` returns hex value of X
  * `toDec(X)` returns decimal value of X
  * `toBin(X)` returns binary value of X
  * `getBit(X,Y)` returns value of bit Y in X
  * `restartEmulation()` tells StellaAI to restart emulating (as good as restarting StellaAI itself)

## Example ##

Bellow is the Pitfall's update function that is capable of restarting the emulation when death is detected.

```
function update ()
	-- Check for number of lives 
	raw = getRam(128)
	if raw == 160 then
		lives = 3
	elseif raw == 128 then
		lives = 2
	else
		lives = 1
	end

	-- If we detect death mode and Harry only has one life we reached the end
	if (getRam(232) == 31 and lives==1) or lives==0 then
		lives = 0
		log("Harry died!")
		restartEmulation()
	
	end
end
```