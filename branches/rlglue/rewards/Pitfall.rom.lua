-- Pitfall.rom --

lives = 3

function update ()
	log("Update...")
	-- detect if we died
	-- maybe do something else as well?
end

function reward ()
	return time()
end

function lives ()
	return lives
end

function score ()

end

function time ()
	min = getRam(216)
	sec = getRam(217)  
	return toHex(min)*60+toHex(sec)
end