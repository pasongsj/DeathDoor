#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapEditGlobalValue.h"

class MapEditorWindow : public GameEngineGUIWindow
{
public:
	static MapEditorWindow* EditorGUI;
	// constrcuter destructer
	MapEditorWindow() ;
	~MapEditorWindow();

	// delete Function
	MapEditorWindow(const MapEditorWindow& _Other) = delete;
	MapEditorWindow(MapEditorWindow&& _Other) noexcept = delete;
	MapEditorWindow& operator=(const MapEditorWindow& _Other) = delete;
	MapEditorWindow& operator=(MapEditorWindow&& _Other) noexcept = delete;

	void ReleaseMapEditor();

protected:
	void Start() override;
	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

private:

	GameEnginePath FilePath;

	bool ReadCSV = false;

	int lastindex = -1;
	int saveIndex = -1;

	std::shared_ptr<class GameEngineActor> CurActor = nullptr;


	std::string ActorType = "                    ";
	std::string FBXName = "                   ";
	std::string MeterialName = "MeshTexture";


	float4 CurRot = float4::ZERO;
	float4 CurPos = float4::ZERO;
	std::string recvUnit = "1000.000000";//1000.000000
	float UnitScale = 10.0f;

	std::string Ratio = "1.000000";

	std::string RevRotationX = "0000.000000";
	std::string RevRotationY = "0000.000000";
	std::string RevRotationZ = "0000.000000";
	
	std::string RevPositionX = "0000.000000";
	std::string RevPositionY = "0000.000000";
	std::string RevPositionZ = "0000.000000";

	void ResetValue();

	std::string SaveIndex = "                ";
	void SaveActors();

	void ReadActor(std::shared_ptr<class GameEngineLevel> Level);

	void ClearActors();
};