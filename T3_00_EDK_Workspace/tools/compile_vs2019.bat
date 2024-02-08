@ECHO off
cls
.\Premake5\Premake5.exe vs2019

xcopy /s /d /Y .\..\assets .\..\bin\debug\x32
xcopy /s /d /Y .\..\assets .\..\bin\release\x32

xcopy /s /d /Y .\..\assets .\..\build\PR03_00_Template\vs2019
xcopy /s /d /Y .\..\assets .\..\build\PR03_01_Demo\vs2019
xcopy /s /d /Y .\..\assets .\..\build\PR03_02_FirstScene\vs2019

pause
