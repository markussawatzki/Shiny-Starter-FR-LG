-- wait for first "A", which starts the frame count
while not joypad.get()["A"] do
	emu.frameadvance()
end

frames = 0
local print_on_a = true

function frame_on_a(on) 
	print_on_a = on
end

local start_frame = emu.framecount()
local a_released = true

while true do 
	if print_on_a and a_released and joypad.get()["A"] then
		print(string.format("frame: %s", emu.framecount()-start_frame))
		
		a_released = false
	elseif joypad.get()["A"] then
		a_released = false
	elseif not joypad.get()["A"] then
		a_released = true
	end
	
	emu.frameadvance()
end

-- usage for #(a_f, sid_f]:
-- trigger event a and print the frame via this script: this will be a_f
-- use tid_sid_pid_finder to find SID
-- use TID and SID and RNGReporter to find sid_r
-- determine #(a_f, sid_f] as follows:
-- #(a_f, sid_f] = 1 + (F(sid_r) - (a_f+1-25)) = 1 + F(sid_r) - a_f + 24 
-- = 25 + F(sid_r) - a_f
-- results:
-- #(a_f, sid_f] = 232 	(GER LG)
-- #(a_f, sid_f] = 273	(US FR)