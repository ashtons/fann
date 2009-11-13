################################################################
# 
# Makefile to rebuild fann win32 dll's with command line Microsoft C++ 2003 7.1
# 
# Use vcvars32 command file to set environment for the compiler tools.
# 
# To rebuild all dll's run: nmake
# To rebuild all debug dll's run: nmake "Debug"
# To rebuild all release dll's run: nmake "Release"
# To rebuild just one dll (for example "Release Fixed") run: nmake "Release Fixed"
# 
# To delete all intermediary directories named "Debug Double" and so forth
# and ***ALL*** their content run: nmake "Clean"
# 
################################################################

"All" : "Debug" "Release"

"Debug" : "Debug Double" "Debug Double Multithread" "Debug Fixed" "Debug Fixed Multithread" "Debug Float" "Debug Float Multithread"

"Release" : "Release Double" "Release Double Multithread" "Release Fixed" "Release Fixed Multithread" "Release Float" "Release Float Multithread"

################################################################

"Clean" :
    @echo Removing all intermediary directories...
    @if exist "Debug Double" erase /Q "Debug Double"
    @if exist "Debug Double" rmdir "Debug Double"
    @if exist "Debug Double Multithread" erase /Q "Debug Double Multithread"
    @if exist "Debug Double Multithread" rmdir "Debug Double Multithread"
    @if exist "Debug Fixed" erase /Q "Debug Fixed"
    @if exist "Debug Fixed" rmdir "Debug Fixed"
    @if exist "Debug Fixed Multithread" erase /Q "Debug Fixed Multithread"
    @if exist "Debug Fixed Multithread" rmdir "Debug Fixed Multithread"
    @if exist "Debug Float" erase /Q "Debug Float"
    @if exist "Debug Float" rmdir "Debug Float"
    @if exist "Debug Float Multithread" erase /Q "Debug Float Multithread"
    @if exist "Debug Float Multithread" rmdir "Debug Float Multithread"
    @if exist "Release Double" erase /Q "Release Double"
    @if exist "Release Double" rmdir "Release Double"
    @if exist "Release Double Multithread" erase /Q "Release Double Multithread"
    @if exist "Release Double Multithread" rmdir "Release Double Multithread"
    @if exist "Release Fixed" erase /Q "Release Fixed"
    @if exist "Release Fixed" rmdir "Release Fixed"
    @if exist "Release Fixed Multithread" erase /Q "Release Fixed Multithread"
    @if exist "Release Fixed Multithread" rmdir "Release Fixed Multithread"
    @if exist "Release Float" erase /Q "Release Float"
    @if exist "Release Float" rmdir "Release Float"
    @if exist "Release Float Multithread" erase /Q "Release Float Multithread"
    @if exist "Release Float Multithread" rmdir "Release Float Multithread"

################################################################

SOURCE = "../src/fann.c" "../src/fann_error.c" "../src/fann_io.c" "../src/fann_cascade.c" "../src/fann_train.c" "../src/fann_train_data.c"

################################################################
# "Debug Double" - fanndoubled.dll

DDBLOBJ = "Debug Double/fann.obj" "Debug Double/fann_error.obj" "Debug Double/fann_io.obj" "Debug Double/fann_cascade.obj" "Debug Double/fann_train.obj" "Debug Double/fann_train_data.obj"

"Debug Double Compile" :
    @echo Compiling Debug Double...
    @if not exist "Debug Double" mkdir "Debug Double"
    @cl @<<
    /Od /I "../src/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /Gm /RTC1 /ML /Fo"Debug Double/" /Fd"Debug Double/vc70.pdb" /W3 /nologo /c /ZI /TC /FI "doublefann.h" $(SOURCE)
<<NOKEEP

"Debug Double Link" : "Debug Double Compile"
    @echo Linking Debug Double...
    @link @<<
    /OUT:"Debug Double/fanndoubled.dll" /INCREMENTAL /NOLOGO /DLL /DEBUG /PDB:"Debug Double/fanndoubled.pdb" /SUBSYSTEM:WINDOWS /IMPLIB:"Debug Double/fanndoubled.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DDBLOBJ)
<<NOKEEP

"Debug Double" : "Debug Double Link"
    @echo Copying Debug Double to bin...
    @if not exist bin mkdir bin
    @copy "Debug Double\fanndoubled.dll" "bin\fanndoubled.dll"
    @copy "Debug Double\fanndoubled.pdb" "bin\fanndoubled.pdb"
    @copy "Debug Double\fanndoubled.lib" "bin\fanndoubled.lib"

################################################################
# "Debug Double Multithread" - fanndoubleMTd.dll

DDBLMTOBJ = "Debug Double Multithread/fann.obj" "Debug Double Multithread/fann_error.obj" "Debug Double Multithread/fann_io.obj" "Debug Double Multithread/fann_cascade.obj" "Debug Double Multithread/fann_train.obj" "Debug Double Multithread/fann_train_data.obj"

"Debug Double Multithread Compile" :
    @echo Compiling Debug Double Multithread...
    @if not exist "Debug Double Multithread" mkdir "Debug Double Multithread"
    @cl @<<
    /Od /I "../src/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /Gm /RTC1 /MTd /Fo"Debug Double Multithread/" /Fd"Debug Double Multithread/vc70.pdb" /W3 /nologo /c /ZI /TC /FI "doublefann.h" $(SOURCE)
<<NOKEEP

"Debug Double Multithread Link" : "Debug Double Multithread Compile"
    @echo Linking Debug Double Multithread...
    @link @<<
    /OUT:"Debug Double Multithread/fanndoubleMTd.dll" /INCREMENTAL /NOLOGO /DLL /DEBUG /PDB:"Debug Double Multithread/fanndoubleMTd.pdb" /SUBSYSTEM:WINDOWS /IMPLIB:"Debug Double Multithread/fanndoubleMTd.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DDBLMTOBJ)
<<NOKEEP

"Debug Double Multithread" : "Debug Double Multithread Link"
    @echo Copying Debug Double Multithread to bin...
    @if not exist bin mkdir bin
    @copy "Debug Double Multithread\fanndoubleMTd.dll" "bin\fanndoubleMTd.dll"
    @copy "Debug Double Multithread\fanndoubleMTd.pdb" "bin\fanndoubleMTd.pdb"
    @copy "Debug Double Multithread\fanndoubleMTd.lib" "bin\fanndoubleMTd.lib"

################################################################
# "Debug Fixed" - fannfixedd.dll

DFXDOBJ = "Debug Fixed/fann.obj" "Debug Fixed/fann_error.obj" "Debug Fixed/fann_io.obj" "Debug Fixed/fann_cascade.obj" "Debug Fixed/fann_train.obj" "Debug Fixed/fann_train_data.obj"

"Debug Fixed Compile" :
    @echo Compiling Debug Fixed...
    @if not exist "Debug Fixed" mkdir "Debug Fixed"
    @cl @<<
    /Od /I "../src/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /Gm /RTC1 /ML /Fo"Debug Fixed/" /Fd"Debug Fixed/vc70.pdb" /W3 /nologo /c /ZI /TC /FI "fixedfann.h" $(SOURCE)
<<NOKEEP

"Debug Fixed Link" : "Debug Fixed Compile"
    @echo Linking Debug Fixed...
    @link @<<
    /OUT:"Debug Fixed/fannfixedd.dll" /INCREMENTAL /NOLOGO /DLL /DEBUG /PDB:"Debug Fixed/fannfixedd.pdb" /SUBSYSTEM:WINDOWS /IMPLIB:"Debug Fixed/fannfixedd.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DFXDOBJ)
<<NOKEEP

"Debug Fixed" : "Debug Fixed Link"
    @echo Copying Debug Fixed to bin...
    @if not exist bin mkdir bin
    @copy "Debug Fixed\fannfixedd.dll" "bin\fannfixedd.dll"
    @copy "Debug Fixed\fannfixedd.pdb" "bin\fannfixedd.pdb"
    @copy "Debug Fixed\fannfixedd.lib" "bin\fannfixedd.lib"

################################################################
# "Debug Fixed Multithread" - fannfixedMTd.dll

DFXDMTOBJ = "Debug Fixed Multithread/fann.obj" "Debug Fixed Multithread/fann_error.obj" "Debug Fixed Multithread/fann_io.obj" "Debug Fixed Multithread/fann_cascade.obj" "Debug Fixed Multithread/fann_train.obj" "Debug Fixed Multithread/fann_train_data.obj"

"Debug Fixed Multithread Compile" :
    @echo Compiling Debug Fixed Multithread...
    @if not exist "Debug Fixed Multithread" mkdir "Debug Fixed Multithread"
    @cl @<<
    /Od /I "../src/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /Gm /RTC1 /MTd /Fo"Debug Fixed Multithread/" /Fd"Debug Fixed Multithread/vc70.pdb" /W3 /nologo /c /ZI /TC /FI "fixedfann.h" $(SOURCE)
<<NOKEEP

"Debug Fixed Multithread Link" : "Debug Fixed Multithread Compile"
    @echo Linking Debug Fixed Multithread...
    @link @<<
    /OUT:"Debug Fixed Multithread/fannfixedMTd.dll" /INCREMENTAL /NOLOGO /DLL /DEBUG /PDB:"Debug Fixed Multithread/fannfixedMTd.pdb" /SUBSYSTEM:WINDOWS /IMPLIB:"Debug Fixed Multithread/fannfixedMTd.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DFXDMTOBJ)
<<NOKEEP

"Debug Fixed Multithread" : "Debug Fixed Multithread Link"
    @echo Copying Debug Fixed Multithread to bin...
    @if not exist bin mkdir bin
    @copy "Debug Fixed Multithread\fannfixedMTd.dll" "bin\fannfixedMTd.dll"
    @copy "Debug Fixed Multithread\fannfixedMTd.pdb" "bin\fannfixedMTd.pdb"
    @copy "Debug Fixed Multithread\fannfixedMTd.lib" "bin\fannfixedMTd.lib"

################################################################
# "Debug Float" - fannfloatd.dll

DFLTOBJ = "Debug Float/fann.obj" "Debug Float/fann_error.obj" "Debug Float/fann_io.obj" "Debug Float/fann_cascade.obj" "Debug Float/fann_train.obj" "Debug Float/fann_train_data.obj"

"Debug Float Compile" :
    @echo Compiling Debug Float...
    @if not exist "Debug Float" mkdir "Debug Float"
    @cl @<<
    /Od /I "../src/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /Gm /RTC1 /ML /Fo"Debug Float/" /Fd"Debug Float/vc70.pdb" /W3 /nologo /c /ZI /TC /FI "floatfann.h" $(SOURCE)
<<NOKEEP

"Debug Float Link" : "Debug Float Compile"
    @echo Linking Debug Float...
    @link @<<
    /OUT:"Debug Float/fannfloatd.dll" /INCREMENTAL /NOLOGO /DLL /DEBUG /PDB:"Debug Float/fannfloatd.pdb" /SUBSYSTEM:WINDOWS /IMPLIB:"Debug Float/fannfloatd.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DFLTOBJ)
<<NOKEEP

"Debug Float" : "Debug Float Link"
    @echo Copying Debug Float to bin...
    @if not exist bin mkdir bin
    @copy "Debug Float\fannfloatd.dll" "bin\fannfloatd.dll"
    @copy "Debug Float\fannfloatd.pdb" "bin\fannfloatd.pdb"
    @copy "Debug Float\fannfloatd.lib" "bin\fannfloatd.lib"
    @if exist examples\bin copy "Debug Float\fannfloatd.dll" "examples\bin\fannfloatd.dll"
    @if exist examples\bin copy "Debug Float\fannfloatd.pdb" "examples\bin\fannfloatd.pdb"

################################################################
# "Debug Float Multithread" - fannfloatMTd.dll

DFLTMTOBJ = "Debug Float Multithread/fann.obj" "Debug Float Multithread/fann_error.obj" "Debug Float Multithread/fann_io.obj" "Debug Float Multithread/fann_cascade.obj" "Debug Float Multithread/fann_train.obj" "Debug Float Multithread/fann_train_data.obj"

"Debug Float Multithread Compile" :
    @echo Compiling Debug Float Multithread...
    @if not exist "Debug Float Multithread" mkdir "Debug Float Multithread"
    @cl @<<
    /Od /I "../src/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /Gm /RTC1 /MTd /Fo"Debug Float Multithread/" /Fd"Debug Float Multithread/vc70.pdb" /W3 /nologo /c /ZI /TC /FI "floatfann.h" $(SOURCE)
<<NOKEEP

"Debug Float Multithread Link" : "Debug Float Multithread Compile"
    @echo Linking Debug Float Multithread...
    @link @<<
    /OUT:"Debug Float Multithread/fannfloatMTd.dll" /INCREMENTAL /NOLOGO /DLL /DEBUG /PDB:"Debug Float Multithread/fannfloatMTd.pdb" /SUBSYSTEM:WINDOWS /IMPLIB:"Debug Float Multithread/fannfloatMTd.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DFLTMTOBJ)
<<NOKEEP

"Debug Float Multithread" : "Debug Float Multithread Link"
    @echo Copying Debug Float Multithread to bin...
    @if not exist bin mkdir bin
    @copy "Debug Float Multithread\fannfloatMTd.dll" "bin\fannfloatMTd.dll"
    @copy "Debug Float Multithread\fannfloatMTd.pdb" "bin\fannfloatMTd.pdb"
    @copy "Debug Float Multithread\fannfloatMTd.lib" "bin\fannfloatMTd.lib"

################################################################
# "Release Double" - fanndouble.dll

RDBLOBJ = "Release Double/fann.obj" "Release Double/fann_error.obj" "Release Double/fann_io.obj" "Release Double/fann_cascade.obj" "Release Double/fann_train.obj" "Release Double/fann_train_data.obj"

"Release Double Compile" :
    @echo Compiling Release Double...
    @if not exist "Release Double" mkdir "Release Double"
    @cl @<<
    /O2 /Ot /GL /I "../src/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /FD /ML /Fo"Release Double/" /Fd"Release Double/vc70.pdb" /W3 /nologo /c /Zi /TC /FI "doublefann.h" $(SOURCE)
<<NOKEEP

"Release Double Link" : "Release Double Compile"
    @echo Linking Release Double...
    @link @<<
    /OUT:"Release Double/fanndouble.dll" /INCREMENTAL:NO /NOLOGO /DLL /DEBUG /PDB:"Release Double/fanndouble.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /IMPLIB:"Release Double/fanndouble.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(RDBLOBJ)
<<NOKEEP

"Release Double" : "Release Double Link"
    @echo Copying Release Double to bin...
    @if not exist bin mkdir bin
    @copy "Release Double\fanndouble.dll" "bin\fanndouble.dll"
    @copy "Release Double\fanndouble.lib" "bin\fanndouble.lib"

################################################################
# "Release Double Multithread" - fanndoubleMT.dll

RDBLMTOBJ = "Release Double Multithread/fann.obj" "Release Double Multithread/fann_error.obj" "Release Double Multithread/fann_io.obj" "Release Double Multithread/fann_cascade.obj" "Release Double Multithread/fann_train.obj" "Release Double Multithread/fann_train_data.obj"

"Release Double Multithread Compile" :
    @echo Compiling Release Double Multithread...
    @if not exist "Release Double Multithread" mkdir "Release Double Multithread"
    @cl @<<
    /O2 /Ot /GL /I "../src/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /FD /MT /Fo"Release Double Multithread/" /Fd"Release Double Multithread/vc70.pdb" /W3 /nologo /c /Zi /TC /FI "doublefann.h" $(SOURCE)
<<NOKEEP

"Release Double Multithread Link" : "Release Double Multithread Compile"
    @echo Linking Release Double Multithread...
    @link @<<
    /OUT:"Release Double Multithread/fanndoubleMT.dll" /INCREMENTAL:NO /NOLOGO /DLL /DEBUG /PDB:"Release Double Multithread/fanndoubleMT.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /IMPLIB:"Release Double Multithread/fanndoubleMT.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(RDBLMTOBJ)
<<NOKEEP

"Release Double Multithread" : "Release Double Multithread Link"
    @echo Copying Release Double Multithread to bin...
    @if not exist bin mkdir bin
    @copy "Release Double Multithread\fanndoubleMT.dll" "bin\fanndoubleMT.dll"
    @copy "Release Double Multithread\fanndoubleMT.lib" "bin\fanndoubleMT.lib"

################################################################
# "Release Fixed" - fannfixed.dll

RFXDOBJ = "Release Fixed/fann.obj" "Release Fixed/fann_error.obj" "Release Fixed/fann_io.obj" "Release Fixed/fann_cascade.obj" "Release Fixed/fann_train.obj" "Release Fixed/fann_train_data.obj"

"Release Fixed Compile" :
    @echo Compiling Release Fixed...
    @if not exist "Release Fixed" mkdir "Release Fixed"
    @cl @<<
    /O2 /Ot /GL /I "../src/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /FD /ML /Fo"Release Fixed/" /Fd"Release Fixed/vc70.pdb" /W3 /nologo /c /Zi /TC /FI "fixedfann.h" $(SOURCE)
<<NOKEEP

"Release Fixed Link" : "Release Fixed Compile"
    @echo Linking Release Fixed...
    @link @<<
    /OUT:"Release Fixed/fannfixed.dll" /INCREMENTAL:NO /NOLOGO /DLL /DEBUG /PDB:"Release Fixed/fannfixed.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /IMPLIB:"Release Fixed/fannfixed.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(RFXDOBJ)
<<NOKEEP

"Release Fixed" : "Release Fixed Link"
    @echo Copying Release Fixed to bin...
    @if not exist bin mkdir bin
    @copy "Release Fixed\fannfixed.dll" "bin\fannfixed.dll"
    @copy "Release Fixed\fannfixed.lib" "bin\fannfixed.lib"

################################################################
# "Release Fixed Multithread" - fannfixedMT.dll

RFXDMTOBJ = "Release Fixed Multithread/fann.obj" "Release Fixed Multithread/fann_error.obj" "Release Fixed Multithread/fann_io.obj" "Release Fixed Multithread/fann_cascade.obj" "Release Fixed Multithread/fann_train.obj" "Release Fixed Multithread/fann_train_data.obj"

"Release Fixed Multithread Compile" :
    @echo Compiling Release Fixed Multithread...
    @if not exist "Release Fixed Multithread" mkdir "Release Fixed Multithread"
    @cl @<<
    /O2 /Ot /GL /I "../src/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /FD /MT /Fo"Release Fixed Multithread/" /Fd"Release Fixed Multithread/vc70.pdb" /W3 /nologo /c /Zi /TC /FI "fixedfann.h" $(SOURCE)
<<NOKEEP

"Release Fixed Multithread Link" : "Release Fixed Multithread Compile"
    @echo Linking Release Fixed Multithread...
    @link @<<
    /OUT:"Release Fixed Multithread/fannfixedMT.dll" /INCREMENTAL:NO /NOLOGO /DLL /DEBUG /PDB:"Release Fixed Multithread/fannfixedMT.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /IMPLIB:"Release Fixed Multithread/fannfixedMT.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(RFXDMTOBJ)
<<NOKEEP

"Release Fixed Multithread" : "Release Fixed Multithread Link"
    @echo Copying Release Fixed Multithread to bin...
    @if not exist bin mkdir bin
    @copy "Release Fixed Multithread\fannfixedMT.dll" "bin\fannfixedMT.dll"
    @copy "Release Fixed Multithread\fannfixedMT.lib" "bin\fannfixedMT.lib"

################################################################
# "Release Float" - fannfloat.dll

RFLTOBJ = "Release Float/fann.obj" "Release Float/fann_error.obj" "Release Float/fann_io.obj" "Release Float/fann_cascade.obj" "Release Float/fann_train.obj" "Release Float/fann_train_data.obj"

"Release Float Compile" :
    @echo Compiling Release Float...
    @if not exist "Release Float" mkdir "Release Float"
    @cl @<<
    /O2 /Ot /GL /I "../src/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /FD /ML /Fo"Release Float/" /Fd"Release Float/vc70.pdb" /W3 /nologo /c /Zi /TC /FI "floatfann.h" $(SOURCE)
<<NOKEEP

"Release Float Link" : "Release Float Compile"
    @echo Linking Release Float...
    @link @<<
    /OUT:"Release Float/fannfloat.dll" /INCREMENTAL:NO /NOLOGO /DLL /DEBUG /PDB:"Release Float/fannfloat.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /IMPLIB:"Release Float/fannfloat.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(RFLTOBJ)
<<NOKEEP

"Release Float" : "Release Float Link"
    @echo Copying Release Float to bin...
    @if not exist bin mkdir bin
    @copy "Release Float\fannfloat.dll" "bin\fannfloat.dll"
    @copy "Release Float\fannfloat.lib" "bin\fannfloat.lib"
    @if exist examples\bin copy "Release Float\fannfloat.dll" "examples\bin\fannfloat.dll"

################################################################
# "Release Float Multithread" - fannfloatMT.dll

RFLTMTOBJ = "Release Float Multithread/fann.obj" "Release Float Multithread/fann_error.obj" "Release Float Multithread/fann_io.obj" "Release Float Multithread/fann_cascade.obj" "Release Float Multithread/fann_train.obj" "Release Float Multithread/fann_train_data.obj"

"Release Float Multithread Compile" :
    @echo Compiling Release Float Multithread...
    @if not exist "Release Float Multithread" mkdir "Release Float Multithread"
    @cl @<<
    /O2 /Ot /GL /I "../src/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "FANN_DLL_EXPORTS" /D "_WINDLL" /D "_MBCS" /FD /MT /Fo"Release Float Multithread/" /Fd"Release Float Multithread/vc70.pdb" /W3 /nologo /c /Zi /TC /FI "floatfann.h" $(SOURCE)
<<NOKEEP

"Release Float Multithread Link" : "Release Float Multithread Compile"
    @echo Linking Release Float Multithread...
    @link @<<
    /OUT:"Release Float Multithread/fannfloatMT.dll" /INCREMENTAL:NO /NOLOGO /DLL /DEBUG /PDB:"Release Float Multithread/fannfloatMT.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /IMPLIB:"Release Float Multithread/fannfloatMT.lib" /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(RFLTMTOBJ)
<<NOKEEP

"Release Float Multithread" : "Release Float Multithread Link"
    @echo Copying Release Float Multithread to bin...
    @if not exist bin mkdir bin
    @copy "Release Float Multithread\fannfloatMT.dll" "bin\fannfloatMT.dll"
    @copy "Release Float Multithread\fannfloatMT.lib" "bin\fannfloatMT.lib"

################################################################
