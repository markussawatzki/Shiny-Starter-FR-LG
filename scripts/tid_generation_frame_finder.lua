-- SEED_OFFSET = 0x03004F50 -- location of the seed of the current frame (in german version of LeafGreen)
SEED_OFFSET = 0x03005000 -- location of the seed of the current frame (in us version of FireRed)
MAX_FRAMES = 30

frame_counter = 1
a_was_pressed = false
start_frame = -1
while frame_counter < 30 do
	seed = memory.read_u32_le(SEED_OFFSET)
	
	if joypad.get()["A"] then
		a_was_pressed = true
		
		if start_frame == -1 then
			start_frame = emu.framecount()
		end
	end

	if a_was_pressed then
		-- prints first seed of frame frame_counter
		print(string.format("%02d: %010u", frame_counter, seed))
		frame_counter = frame_counter + 1
	end
	
	emu.frameadvance()
end

-- usage for t_f:
-- trigger event s
-- play until player trainer card can be opened
-- compare TID with each seed
-- if TID matches a seed, the preceding frame count is t_f

-- testing results:
-- t_f = 25 (GER LG)
-- t_f = 25	(US FR)