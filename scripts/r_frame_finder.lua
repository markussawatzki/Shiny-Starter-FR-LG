require("lcrng")

-- SEED_OFFSET = 0x03004F50 -- location of the seed of the current frame (in german version of LeafGreen)
SEED_OFFSET = 0x03005000 -- location of the seed of the current frame (in us version of FireRed)

local start_seed = -1
local tid = -1
local global_r_frames = 0

local count = 0
local inflation = true

local global_frame_advc = 0

local pause_on_a = false

R = {}

local function get_seed()
	return memory.read_u32_le(SEED_OFFSET)
end

local function frame_start()
	start_seed = get_seed()
	
	R[count] = {}
	R[count].start_r = global_r_frames
	R[count].start_s = start_seed
end

local function frame_end()
	local end_seed = get_seed()
	local seed = start_seed
	
	local r_frames = 0
	while seed ~= end_seed do
		r_frames = r_frames + 1
		
		seed = lcrng(seed)
	end
	
	global_r_frames = global_r_frames + r_frames
	
	if inflation and r_frames ~= 1 then
		print(string.format("%d: %u r frames", count, r_frames))
	end
	
	global_frame_advc = global_frame_advc + r_frames - 1
	
	R[count].end_r = global_r_frames - 1
	R[count].end_s = seed
	
	count = count + 1
	
	if pause_on_a and joypad.get()["A"] then
		client.pause()
	end
end

-- wait until tid is set as seed
while bit.rshift(get_seed(), 16) ~= 0 do 
	emu.frameadvance()
end

tid = get_seed()

if joypad.get()["A"] then
	print("a: ")
end

event.onframestart(frame_start)
event.onframeend(frame_end)

-- turn on/off setting to print frame inflation
function pi(inf)
	inflation = inf
end

-- turn on/off setting to pause on a (at the end of a frame)
function poa(_pause_on_a)
	pause_on_a = _pause_on_a
end

-- print global in-game frame advances
function gfa()
	print("FA:", global_frame_advc)
end

-- returns F(x)
function F(x)
	i = x

	while R[i] do
		if x >= R[i].start_r then
			return i
		end
		
		i = i - 1
	end
	
	return nil
end

-- returns the r frame of seed
function seed_to_r(seed)
	local i = 0
	local s = tid
	
	while seed ~= s do
		s = lcrng(s)
		
		i = i + 1
	end
	
	return i
end