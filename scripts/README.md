### [lcrng library](./lcrng_lib)

#### Compilation
```
cd ./lcrng_lib  
gcc -Wall -fPIC -shared -o lcrng.dll -IINCLUDE_PATH -LLIBRARY_PATH -llua5.1 lcrng.c  
```
  
where	__INCLUDE_PATH__ is a path to Lua5.1 *.h files,  
and		__LIBRARY_PATH__ is a path which contains the shared library lua5.1.dll.  

#### Note
lcrng.dll is a shared library which is used by the script [r_frame_finder.lua](./r_frame_finder.lua) to simulate LCRNG calls.  
It depends on the Lua 5.1 library which can be downloaded [here](https://sourceforge.net/projects/luabinaries/files/5.1.5/Windows%20Libraries/Dynamic/lua-5.1.5_Win64_dllw4_lib.zip/download).  
lcrng.dll and lua5.1.dll need to be copied into the top-level folder of the [BizHawk multi-system emulator](https://github.com/TASVideos/BizHawk) (_which contains the **EmuHawk.exe**_).

