@echo off
msbuild D:\Coding\PUBG\NoRecoil\EscoLoader\EscoLib\EscoLib.vcxproj /p:Configuration=Release /p:Platform=x86
msbuild D:\Coding\PUBG\NoRecoil\EscoLoader\EscoLib\EscoLib.vcxproj /p:Configuration=Release /p:Platform=x64

copy "D:\Coding\PUBG\NoRecoil\EscoLoader\EscoIdentifier\Release\EscoLib.dll" "D:\Coding\PUBG\NoRecoil\EscoCp\Debug\"
copy "D:\Coding\PUBG\NoRecoil\EscoLoader\EscoIdentifier\Release\EscoLib.dll" "D:\Coding\PUBG\NoRecoil\EscoCp\Release\"
copy "D:\Coding\PUBG\NoRecoil\EscoLoader\EscoIdentifier\x64\Release\EscoLib.dll" "D:\Coding\PUBG\NoRecoil\EscoCp\x64\Debug\"
copy "D:\Coding\PUBG\NoRecoil\EscoLoader\EscoIdentifier\x64\Release\EscoLib.dll" "D:\Coding\PUBG\NoRecoil\EscoCp\x64\Release\"