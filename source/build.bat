@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl  -MT -nologo -Od -Oi -EHsc -Z7 ..\source\launch.cpp
popd
