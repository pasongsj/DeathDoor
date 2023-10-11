#include "PrecompileHeader.h"
#include "Start_BackGround.h"
#include "ContentFBXRenderer.h"

Start_BackGround::Start_BackGround()
{
}

Start_BackGround::~Start_BackGround()
{
}

void Start_BackGround::Start()
{
	BakcGround = CreateComponent<ContentFBXRenderer>();
	BakcGround->SetFBXMesh("UIBackGroundMap.fbx","ContentMeshDeffered");
    BakcGround->GetTransform()->SetLocalRotation({ 0, 180.0f, 0 });

    auto AllUnit = BakcGround->GetAllRenderUnit();
	auto Unit = BakcGround->GetUnTexturedUnit();

	AllUnit[4][0]->UVdata = { 0.03f, 0.03f, 0.0f, 0.0f };
	AllUnit[5][0]->Color = { {0.0f, 0.0f, 0.0f, 0.0f}, {0.6f, 0.6f, 0.6f, 1.0f} };

    //Hall_Crow_1 = CreateComponent<ContentFBXRenderer>();
    //Hall_Crow_1->SetFBXMesh("Hall_Crow_1.fbx", "ContentAniMesh");
    //Hall_Crow_1->GetTransform()->SetLocalPosition({ -16.0f, 3.5f, -14.0f });
    //Hall_Crow_1->GetTransform()->SetLocalRotation({ 0.0f, -30.0f, 0.0f });
    //
    //Hall_Crow_1->CreateFBXAnimation("Armature|Idle_sat_typing", "Hall_Crow_1.fbx");
    //Hall_Crow_1->ChangeAnimation("Armature|Idle_sat_typing");
    //
    //Hall_Crow_2 = CreateComponent<ContentFBXRenderer>();
    //Hall_Crow_2->SetFBXMesh("Hall_Crow_2.fbx", "ContentAniMesh");
    //Hall_Crow_2->GetTransform()->SetLocalPosition({ 11.0f, 3.5f, 10.0f });
    //Hall_Crow_2->GetTransform()->SetLocalRotation({ 0.0f, 75.0f, 0.0f });
    //          
    //Hall_Crow_2->CreateFBXAnimation("Armature|Idle_sat_typing", "Hall_Crow_2.fbx");
    //Hall_Crow_2->ChangeAnimation("Armature|Idle_sat_typing");
    //
    //Hall_Crow_3 = CreateComponent<ContentFBXRenderer>();
    //Hall_Crow_3->SetFBXMesh("Hall_Crow_3.fbx", "ContentMesh");
    //Hall_Crow_3->GetTransform()->SetLocalPosition({ 0.0f, -1.0f, 0.0f });
    //Hall_Crow_3->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 0.0f });
    //
    //auto Units = Hall_Crow_3->GetAllRenderUnit();
    //
    //Units[4][0]->Color.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
    //Units[5][0]->Color.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
    //
    ////Hall_Crow_3->CreateFBXAnimation("Crow_Player_Sat_Bored", "Hall_Crow_3.fbx");
    ////Hall_Crow_3->ChangeAnimation("Crow_Player_Sat_Bored");
    //
    //Hall_Banker = CreateComponent<ContentFBXRenderer>();
    //Hall_Banker->SetFBXMesh("banker.fbx", "ContentAniMesh");
    //Hall_Banker->GetTransform()->SetLocalScale({ 2.0f, 2.0f, 2.0f });
    //Hall_Banker->GetTransform()->SetLocalRotation({ 270.0f, 225.0f, 270.0f });
    //Hall_Banker->GetTransform()->SetLocalPosition({ -16.5f, 6.0f, 9.5f });
    //
    //Hall_Banker->CreateFBXAnimation("Banker_WriteLoop", "banker.fbx");
    //Hall_Banker->ChangeAnimation("Banker_WriteLoop");
    //
    //Book = CreateComponent<ContentFBXRenderer>();
    //Book->SetFBXMesh("Book.fbx", "ContentMesh");
    //Book->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    //Book->GetTransform()->SetLocalPosition({ -14.5f, 5.0f, 7.5f });
    //
    //std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> BankerUnit = Hall_Banker->GetAllRenderUnit();
    //
    //for (int i = 0; i < BankerUnit.size(); i++)
    //{
    //    for (int j = 0; j < BankerUnit[i].size(); j++)
    //    {
    //        BankerUnit[i][j]->ShaderResHelper.SetTexture("DiffuseTexture", "BankerTexture.png");
    //    }
    //}
}

void Start_BackGround::Update(float _DeltaTime)
{
    MoveCamera(_DeltaTime);

    //float4 Scale = Bg2->GetMeshScale();
    ////Bg2->GetTransform()->SetLocalPosition({ 0, -1.0f, -1.0f });
    //
	//DirectX::XMMATRIX viewMatrix = GetLevel()->GetMainCamera()->GetView();
	//DirectX::XMVECTOR cameraDirection = DirectX::XMVectorNegate(viewMatrix.r[2]);
    //
	//DirectX::XMVECTOR actorPosition = Bg->GetTransform()->GetWorldPosition(); // 액터의 위치
	//DirectX::XMVECTOR directionToCamera = DirectX::XMVectorSubtract(cameraDirection, actorPosition);
	//DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionRotationNormal(directionToCamera, DirectX::XM_PI)); 
    //
    //DirectX::XMFLOAT3 eulerAngle;
    //
    //DirectX::XMMATRIX rotation = rotationMatrix;
    //
    //float sy = sqrt(rotationMatrix.r[0].m128_f32[0] * rotationMatrix.r[0].m128_f32[0] + rotationMatrix.r[1].m128_f32[0] * rotationMatrix.r[1].m128_f32[0]);
    //
    //bool singular = sy < 1e-6;
    //
    //if (!singular)
    //{
    //    eulerAngle.x = atan2(rotationMatrix.r[2].m128_f32[1], rotationMatrix.r[2].m128_f32[2]);
    //    eulerAngle.y = atan2(-rotationMatrix.r[2].m128_f32[0], sy);
    //    eulerAngle.z = atan2(rotationMatrix.r[1].m128_f32[0], rotationMatrix.r[0].m128_f32[0]);
    //}
    //else
    //{
    //    eulerAngle.x = atan2(-rotationMatrix.r[1].m128_f32[2], rotationMatrix.r[1].m128_f32[1]);
    //    eulerAngle.y = atan2(-rotationMatrix.r[2].m128_f32[0], sy);
    //    eulerAngle.z = 0;
    //}
    //
    //// 라디안을 60분법으로 변환
    //eulerAngle.x = DirectX::XMConvertToDegrees(eulerAngle.x);
    //eulerAngle.y = DirectX::XMConvertToDegrees(eulerAngle.y);
    //eulerAngle.z = DirectX::XMConvertToDegrees(eulerAngle.z);
    //
    //float4 RotAngle = { eulerAngle.x, eulerAngle.y + 180.0f, eulerAngle.z };
    //Bg2->GetTransform()->SetLocalRotation(RotAngle);
    //
    //int a = 0;
}

void Start_BackGround::MoveCamera(float _DeltaTime)
{
    Angle += 0.2f * _DeltaTime;

    if (Angle >= 180.0f)
    {
        Angle -= 180.0f;
    }

    float4 CamRot = { 28.0f, -37.0f + 15.0f * sin(Angle), 0.0f};
    
    GetLevel()->GetMainCamera()->GetTransform()->SetLocalRotation(CamRot);
}