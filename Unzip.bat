@echo off


IF NOT EXIST "%~dp0%GameEngineCore\ThirdParty\FBX\lib\x64\Debug\libfbxsdk-md.lib" (
    powershell expand-archive GameEngineCore\ThirdParty\FBX\lib\x64\Debug\libfbxsdk-md.zip GameEngineCore\ThirdParty\FBX\lib\x64\Debug\
)

IF NOT EXIST "%~dp0%GameEngineCore\ThirdParty\FBX\lib\x64\Debug\libfbxsdk-mt.lib" (
    powershell expand-archive GameEngineCore\ThirdParty\FBX\lib\x64\Debug\libfbxsdk-mt.zip GameEngineCore\ThirdParty\FBX\lib\x64\Debug\
)


IF NOT EXIST "%~dp0%GameEngineCore\ThirdParty\FBX\lib\x64\Release\libfbxsdk-md.lib" (
    powershell expand-archive GameEngineCore\ThirdParty\FBX\lib\x64\Release\libfbxsdk-md.zip GameEngineCore\ThirdParty\FBX\lib\x64\Release\
)

IF NOT EXIST "%~dp0%GameEngineCore\ThirdParty\FBX\lib\x64\Release\libfbxsdk-mt.lib" (
    powershell expand-archive GameEngineCore\ThirdParty\FBX\lib\x64\Release\libfbxsdk-mt.zip GameEngineCore\ThirdParty\FBX\lib\x64\Release\
)

IF NOT EXIST "%~dp0%ContentResources\Mesh\Map\UIBackGroundMap.fbx" (
    powershell expand-archive ContentResources\Zip\UIBackGroundMap.zip ContentResources\Mesh\Map
)

IF NOT EXIST "%~dp0%ContentResources\Mesh\Map\Cube14.fbx" (
    powershell expand-archive ContentResources\Zip\Cube14.zip ContentResources\Mesh\Map
)

IF NOT EXIST "%~dp0%ContentResources\Mesh\Map\Map_Office.fbx" (
    powershell expand-archive ContentResources\Zip\Map_Office.zip ContentResources\Mesh\Map
)
