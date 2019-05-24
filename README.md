### Shiny Starter FR LG

#### Description
This project contains research scripts and code for tools for a [technique](TODO)
which let's you aquire a shiny starter in German/U.S version of Pokemon FireRed/LeafGreen.

#### [Research scripts](./scripts)
These LUA scripts were used for the research.
They can be loaded by the [BizHawk multi-system emulator](https://github.com/TASVideos/BizHawk) to reproduce the found results.

#### [Main tool: shiny](TODO)
This tool reads the file _config.ini._ which contains key/value-pairs (_according to INI-syntax_) whose values can and should be modified by the user. 
Depending on these values, **shiny** outputs the **target SID frame**, and the predicted **SID** (which is going to be true if the user hits the **target SID frame**).
Afterwards **shiny** will ask the user to input the **TID** (in _decimal_).
It will then print the **target PID frame** for a Pokemon which has properties that were defined by the user in _config.ini_.
It will also print a table with Pokemon which occure on frames which are adjacent to the **target PID frame**.

#### [Tool: eon_timer_enter](TODO)
Searches for the first two windows of running applications with the Name **"EonTimer v1.6"** and simulates a keyboard stroke of the button _RETURN_. 
If the compiler flag _DELAY_ was set, it waits for a second before simulating the key stroke (_which is useful if the technique is applied for an emulator which runs on the same Windows-system_).

#### [Tool: routine.bat](TODO)
Alternatingly executes _shiny.exe_ and _eon_timer_enter.exe_ 
because applying the technique needs _more than one iteration (with high probability)_.