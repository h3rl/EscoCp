@echo off

call :rxdir "bin"
call :rxfdir "App"
call :rxfdir "Console"
call :rxfdir "Downloader"
call :rxfdir "Library"
call :rxfdir "Test"
EXIT /B %ERRORLEVEL%

:rxfdir
set s=%~1
call :rxdir "%s%\bin"
call :rxdir "%s%\Release"
call :rxdir "%s%\Debug"
call :rxdir "%s%\x64"
EXIT/B 0

:rxdir
set d=%~1\
if exist %d% (
  echo deleted %~1
  rmdir /S /Q %d%
)
EXIT/B 0