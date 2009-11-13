FANN >= 1.1.0 includes a Microsoft Visual C++ 6.0 project file, which can be used to compile FANN for Windows.  To build the library and examples with MSVC++ 6.0.

First, navigate to the MicrosoftVisualC++6.0 directory in the FANN distribution and open the all.dsw workspace.  In the Visual Studio menu bar, choose "Build" -> "Batch build...", select the project configurations that you would like to build (by default, all are selected), and press "rebuild all"

When the build process is complete, the library and examples can be found in the MicrosoftVisualC++6.0\Debug directorie and the examples are automatically copied into the examples where they are supposed to be run. If all of the examples are not copied to the correct location, please compile them separately.
