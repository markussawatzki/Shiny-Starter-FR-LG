### eontimer_enter

#### Compilation
```
gcc -Wall -std=c99 [-DDELAY] -o eontimer_enter.exe eontimer_enter.c
```  
where __INCLUDE_PATH__ is a path to a directory which contains ini.h.

#### Note
If the flag __DELAY__ is set, **eontimer_enter.exe** listens _globally_ for a key stroke _RETURN_  
and afterwards waits 1 second (60 frames) before simulating the key stroke _RETURN_ on the "EonTimer v1.6" windows.