@echo off

REM errors.txt is where the output errors from the compiler get stored
REM so that cim can ream them later

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl  -MT -nologo -Od -Oi -EHsc -Z7 ..\source\launch.cpp 2> CompilationErrors.txt
popd
