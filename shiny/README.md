### shiny

#### Compilation
gcc -Wall -std=c99 [-DLANG_DE|-DLANG_US] [-DCLIPBOARD] -I**INCLUDE_PATH** ini.c out.c calc.c shiny.c main.c -o shiny.exe
  
where __INCLUDE_PATH__ is a path to a directory which contains ini.h.

#### Note
shiny.exe depends on ini.c and ini.h from the small INI parser library [inih](https://github.com/benhoyt/inih).  
If the flag _CLIPBOARD_ is set, the shiny.exe will copy **target SID and PID frame* to the clipboard.  
The flag _LANG_DE_ has to be set, if **shiny.exe** is used for the German version of Pokemon FireRed/LeafGreen.  
The flag _LANG_US_ has to be set, if **shiny.exe** is used for the U.S. version of Pokemon FireRed/LeafGreen.  
Either _LANG_DE_ or _LANG_DE_ has to be set.
  
If you want to extend the tool to support versions of Pokemon in different languages, you are free to do so (__please note the [license](./LICENSE.txt)__).