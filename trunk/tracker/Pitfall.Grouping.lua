function group(A, B) 
	ca = objectInfo(A,"color")
	cb = objectInfo(B,"color")
	ab = objectDistance(A,B)
	xa = objectInfo(A,"X")
	xb = objectInfo(B,"X")
	ya = objectInfo(A,"Y")
	yb = objectInfo(B,"Y")
	
	-- Tree leafs
	if ca==0x355f18 and ca==cb and ya<70 and yb<70 then
		objectSetName(A, "TreeGree")
		return 1
	end
	
	-- Borders
	if ca==0x000000 and ca==cb then
		if objectInside(A, 16, 115, 320, 130)==0 and objectInside(B, 16, 115, 320, 130)==0 then
			objectSetName(A, "Border")
			return 1
		end
	end
	
	-- Hole
	if ca==0x000000 and objectInside(A, 17, 115, 320, 130)==1 then
		if objectInfo(A, "W")>24 then
			objectSetName(A, "Pit")
		else
			objectSetName(A, "Hole")
		end
		
		if cb==0x000000 and objectInside(B, 17, 115, 320, 130)==1 then
			return 1
		end
	end
	
	
	-- Text
	if ca==0xd6d6d6 and ca==cb then
		objectSetName(A, "Text")
		return 1
	end
	
	-- Walls-Bricks
	if ca==0xa71a1a and ca==cb then
		objectSetName(A, "Wall")
		return 1
	end
	-- Walls-Cement
	if ca==0x8e8e8e and ca==cb then
		objectSetName(A, "Wall")
		return 1
	end
	
	-- Background trees / Vine!?
	if ca==0x484800 and ca==cb then
		objectSetName(A, "Tree")
		return 1
	end

	-- Log // Harry's hair
	if ca==0x69690f and ca==cb and (ya<133 and yb<133 and yb>117 and ya>117) then
		objectSetName(A, "Log")
		return 1
	end
	
	
	-- Background
	if ca==0x6e9c42 and cb==ca then
		objectSetName(A, "Background")
		return 1
	end
	
	-- Ladder
	if ca==0x86861d and objectInside(A, 153, 134, 167, 179)==1 then
		objectSetName(A, "Ladder")
		if cb==ca and objectInside(B, 153, 134, 167, 179)==1 then
			return 1
		end
	end
	
	-- Ground lower
	if ca==0x86861d and (objectInside(A, 153, 134, 167, 179)==0 or ya>178) then
		objectSetName(A, "Ground")
		if cb==ca and (objectInside(B, 153, 134, 167, 179)==0 or yb>178) then
			return 1
		end
	end

	-- Ground top
	if ca==0xbbbb35 and cb==ca then
		objectSetName(A, "Ground")
		return 1
	end

	-- Harry 
	if ca==0x5cba5c or ca==0xe46f6f or (ca==0x355f18 and ya>70) then
		objectSetName(A, "Harry")
	end
	if ca==0xe46f6f and cb==0x69690f then
		objectSetName(B, "Harry")
	end
	
	if objectInfo(A, "name")=="Harry" and objectInfo(B, "name")=="Harry" then
		return 1;
	end

	-- Ground
	if objectInside(A,16,180,320,190)==1 then
		objectSetName(A, "Ground")
	end
	
	-- Water
	if ca==0x986d2d and ca==cb then
		objectSetName(A, "Water")
		return 1
	end
	
	-- Gator!
	if ca==0x3c14 and ca==cb and  ab<5 then
		objectSetName(A, "Allagator")
		return 1
	end
	
	-- Scorpion 
	if ca==0xececec and ca==cb then 
		objectSetName(A, "Scorpion")
		return 1
	end
	
	-- Fire
	--if ca==0x74bcfc or ca==0x60c8ec

	return 0
end

