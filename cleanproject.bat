@echo off

call :rxdir ".vs"
call :rxdir "bin"
call :rxfdir "App"
call :rxfdir "Console"
call :rxfdir "Downloader"
call :rxfdir "Library"
call :rxfdir "Test"
EXIT /B %ERRORLEVEL%

:rxfdir
call :rxdir "%~1\bin"
call :rxdir "%~1\Release"
call :rxdir "%~1\Debug"
call :rxdir "%~1\x64"
EXIT/B 0

:rxdir
if exist %~1\ (
  echo deleted %~1
  rmdir /S /Q %~1\
)
EXIT/B 0