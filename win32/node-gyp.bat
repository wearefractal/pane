@echo off
@rem Check for nodejs build location variable
if not defined NODE_ROOT goto nodebuild-not-found
if not exist "%NODE_ROOT%\src\node.h" goto nodebuild-not-found
if not exist "%NODE_ROOT%\deps\v8\include\v8.h" goto nodebuild-not-found
if not exist "%NODE_ROOT%\deps\uv\include\uv.h" goto nodebuild-not-found
if not exist "%NODE_ROOT%\tools\gyp\gyp" goto gyp-not-found

@rem detect the location of the node.lib file
set node_lib_folder=
if exist "%NODE_ROOT%\Release\node.lib" set node_lib_folder=Release
if not defined node_lib_folder if exist "%NODE_ROOT%\Debug\node.lib" set node_lib_folder=Debug
if not defined node_lib_folder goto nodebuild-not-found

@rem Try to locate the gyp file
set gypfile=
@rem if the user has specified the file, this is the one we will use
if exist %1 set gypfile=%1
@rem otherwise try to locate the module.gyp file
if not defined gypfile if exist "%CD%\module.gyp" set gypfile=module.gyp
if not defined gypfile goto gyp-file-missing
@rem Generate visual studio solution
python %NODE_ROOT%\tools\gyp\gyp -f msvs -G msvs_version=2010 %gypfile% --depth=. -DNODE_ROOT=%NODE_ROOT% -Dnode_lib_folder=%node_lib_folder%
if errorlevel 1 goto exit-error
echo Finished
goto exit
:msbuild-not-found
echo Visual studio tools were not found! Please check the VS100COMNTOOLS path variable
goto exit
:gyp-not-found
echo GYP was not found. Please check that gyp is located in %NODE_ROOT%/tools/gyp/ 
goto exit
:nodebuild-not-found
echo Node build path not found! Please check the NODE_ROOT path variable exists and that it points to the root of the git repo where you have build 
goto exit
:gyp-file-missing
echo Could not locate a gyp file. No module.gyp file found and you haven't specified any existing gyp file as an argument
goto exit
:exit-error
echo An error occured. Please check the above output
:exit
@rem clear local variables
set node_lib_folder=
set gypfile=
