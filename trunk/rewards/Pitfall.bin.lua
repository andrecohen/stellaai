lives = 3

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

		-- Option 1: restarts emulation
		restartEmulation()

		-- Option 2: save initial ROM state, and later reload it
		-- Not needed in pitfall.. maybe another game may need it?			
	end
end

function reward ()
	return time()
end

function lives ()
	return lives
end

function score ()
	return getRam(214)*100+getRam(215)
end

function time ()
	min = getRam(216)
	sec = getRam(217)  
	return toHex(min)*60+toHex(sec)
end
