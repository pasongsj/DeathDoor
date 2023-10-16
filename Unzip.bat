@echo off


powershell expand-archive -force GameEngineCore\ThirdParty\FBX\lib\x64\Debug\libfbxsdk-md.zip GameEngineCore\ThirdParty\FBX\lib\x64\Debug\ 


powershell expand-archive -force GameEngineCore\ThirdParty\FBX\lib\x64\Debug\libfbxsdk-mt.zip GameEngineCore\ThirdParty\FBX\lib\x64\Debug\



powershell expand-archive -force GameEngineCore\ThirdParty\FBX\lib\x64\Release\libfbxsdk-md.zip GameEngineCore\ThirdParty\FBX\lib\x64\Release\


powershell expand-archive -force GameEngineCore\ThirdParty\FBX\lib\x64\Release\libfbxsdk-mt.zip GameEngineCore\ThirdParty\FBX\lib\x64\Release\


powershell expand-archive -force ContentResources\Zip\UIBackGroundMap.zip ContentResources\Mesh\Static\Map\Office


powershell expand-archive -force ContentResources\Zip\Cube14.zip ContentResources\Mesh\Static\Map\Office


powershell expand-archive -force ContentResources\Zip\Map_Office.zip ContentResources\Mesh\Static\Map\Office
