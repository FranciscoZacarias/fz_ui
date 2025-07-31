@echo off

set compiler_and_entry=cl ..\src\main.c
set cl_default_flags=/Isrc /nologo /FC /Zi
set external_include=/I"..\src\fz_std"

if not exist build mkdir build
pushd build
%compiler_and_entry% %cl_default_flags% %external_include% /Fe"turtle.exe"
popd