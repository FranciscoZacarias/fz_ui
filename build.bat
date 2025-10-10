@echo off
setlocal

set compiler=cl
set entry=..\src\main.c
set cl_default_flags=/Isrc /nologo /FC /Zi
set external_include=/I"..\src\fz_std"
set build_dir=build

REM Parse args
set arg=%1

if "%arg%"==""    goto build_all
if "%arg%"=="hph" goto build_hephaestus
if "%arg%"=="ui"  goto build_ui
goto end

:build_all
call "%~f0" hph
call "%~f0" ui
goto end

:build_hephaestus
echo Running Hephaestus...
bin\hephaestus.exe --input "../src/ui.hph"
goto end

:build_ui
if not exist %build_dir% mkdir %build_dir%
pushd %build_dir%
echo Compiling %entry%
%compiler% %entry% %cl_default_flags% %external_include% /Fe"fz_ui.exe"
popd
goto end

:end
endlocal
