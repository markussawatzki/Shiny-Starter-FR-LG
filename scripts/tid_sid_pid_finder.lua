-- DMA_POINTER = 0x03004F5C;	-- location of the pointer to the DMA-protected block which contains tid and sid (in german version of LeafGreen)
DMA_POINTER = 0x0300500C;	-- location of the pointer to the DMA-protected block which contains tid and sid (in us version of FireRed)
TID_OFFSET = 0x000A;	 	-- offset for tid in data block which contains tid and sid
SID_OFFSET = 0x000C;		-- offset for tid in data block which contains tid and sid
PID = 0x02024284;			-- offset for pid


while true do
	block_ptr = memory.read_u32_le(DMA_POINTER)
	tid = memory.read_u16_le(block_ptr + TID_OFFSET)
	sid = memory.read_u16_le(block_ptr + SID_OFFSET)
	pid = memory.read_u32_le(PID)

	gui.text(0, 20, string.format("TID: 0x%04X", tid))
	gui.text(0, 40, string.format("SID: 0x%04X", sid))
	gui.text(0, 60, string.format("PID: 0x%08X", pid))

	emu.frameadvance()
end