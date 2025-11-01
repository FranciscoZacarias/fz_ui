@echo off
setlocal

set compiler=cl
set entry=..\src\main.c
set cl_default_flags=/Isrc /nologo /FC /Zi
set external_include=/I"..\src\fz_std"
set build_dir=build

REM Args
set arg=%1
if "%arg%"==""       set arg=ui
if /I "%arg%"=="all" goto build_all
if /I "%arg%"=="ui"  goto build_ui
if /I "%arg%"=="hph" goto build_hephaestus
if /I "%arg%"=="hph_fz_std"  goto build_hephaestus_fz_std
goto end

REM Targets
:build_all
call "%~f0" hph
call "%~f0" ui
goto end

:build_hephaestus
echo Running Hephaestus on ../../../src/ui.hph ...
src\fz_std\bin\hephaestus.exe --input "../../../src/ui.hph"
goto end

:build_hephaestus_fz_std
echo Running Hephaestus on ../base/math/math.hph ...
src\fz_std\bin\hephaestus.exe --input "../base/math/math.hph"
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
