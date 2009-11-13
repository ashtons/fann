
Fann win32 dll readme:

Rebuilding the fann win32 dll's require Microsoft Visual Studio C++ 2003/7.1.
The build process places dll's and import libraries in win32/bin. Once built the
dll's can be used by earlier compilers and other development tools.


Project configurations:

The windll project has a large number of configurations. The three number
formats supported in the fann library are double, fixed and float. The C
runtime has two variations: single threaded and multi thread safe. Then
there is the choice between debug without optimizations and release with
global optimizations set for speed.

Dll name		- Configuration name

fanndoubled.dll		- Debug Double
fanndoubleMTd.dll	- Debug Double Multithread
fanndouble.dll		- Release Double
fanndoubleMT.dll	- Release Double Multithread

fannfixedd.dll		- Debug Fixed
fannfixedMTd.dll	- Debug Fixed Multithread
fannfixed.dll		- Release Fixed
fannfixedMT.dll		- Release Fixed Multithread

fannfloatd.dll		- Debug Float
fannfloatMTd.dll	- Debug Float Multithread
fannfloat.dll		- Release Float
fannfloatMT.dll		- Release Float Multithread

The import libraries are named as the dll's but with the .lib extension.


Application usage:

To use a dll in an application include one of the doublefann.h, fixedfann.h
or floatfann.h header files in the source code and depending on the
number format selected and the settings (debug, release, single or
multithreaded) in the application link with the matching import library.
When executing the application make sure the required dll is in the search
path. For example copy the dll to the same directory as the application or
add win32/bin to the search path (for example on WinXP use the System
applet Configuration Manager and select Advanced and Environment Variables).


Visual Studio C++ instructions:

To build a dll in one of the configurations, select it in the Solutions
Configurations dropdown on the standard toolbar and build it from the
Build menu.

To build all configurations select Batch Build in the Build menu. Click
Select All, Rebuild. All the dll's are placed in the win32\bin sub directory.
The intermediary directories named after their configurations can be
deleted or Clean can be used from Batch Build to save space. The dll's in
win32\bin will not be deleted by Clean.


Command line version instructions:

A makefile to rebuild the fann win32 dll's with the command line Microsoft
C++ 2003/7.1 compiler is located in the win32 directory. Open a command
window in the win32 directory and use the vcvars32 command file to set
environment for the compiler tools.
 
To rebuild all dll's run: nmake
To rebuild all debug dll's run: nmake "Debug"
To rebuild all release dll's run: nmake "Release"
To rebuild just one dll (for example "Release Fixed") run: nmake "Release Fixed"

To delete all intermediary directories named "Debug Double" and so forth
and ***ALL*** their content (the dll's in win32\bin will not be deleted)
run: nmake "Clean"
