@echo off

REM Run Hephaestus
echo Running Hephaestus...
bin\hephaestus.exe --input "../src/ui.hph"

REM Build program
set compiler_and_entry=cl ..\src\main.c
set cl_default_flags=/Isrc /nologo /FC /Zi
set external_include=/I"..\src\fz_std"


if not exist build mkdir build
pushd build
echo Compiling...
%compiler_and_entry% %cl_default_flags% %external_include% /Fe"fz_ui.exe"
popd