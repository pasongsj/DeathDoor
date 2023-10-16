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

    Hall_Crow_1 = CreateComponent<ContentFBXRenderer>();
    Hall_Crow_1->SetFBXMesh("Hall_Crow_1_MESH.fbx", "ContentAniMeshDeffered");
    Hall_Crow_1->GetTransform()->SetLocalPosition({ -16.0f, 3.5f, -14.0f });
    Hall_Crow_1->GetTransform()->SetLocalRotation({ 0.0f, -120.0f, 0.0f });
    Hall_Crow_1->GetTransform()->SetLocalScale(float4::ONE * 3.0f);
    
    Hall_Crow_1->CreateFBXAnimation("Armature|Idle_sat_typing", "Hall_Crow_1_Typing_Anim.fbx");
    Hall_Crow_1->ChangeAnimation("Armature|Idle_sat_typing");
    
    Hall_Crow_2 = CreateComponent<ContentFBXRenderer>();
    Hall_Crow_2->SetFBXMesh("Hall_Crow_1_MESH.fbx", "ContentAniMeshDeffered");
    Hall_Crow_2->GetTransform()->SetLocalPosition({ 11.0f, 3.5f, 10.0f });
    Hall_Crow_2->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 0.0f });
    Hall_Crow_2->GetTransform()->SetLocalScale(float4::ONE * 3.0f);
              
    Hall_Crow_2->CreateFBXAnimation("Armature|Idle_sat_typing", "Hall_Crow_1_Typing_Anim.fbx");
    Hall_Crow_2->ChangeAnimation("Armature|Idle_sat_typing");
    
    //Hall_Crow_3 = CreateComponent<ContentFBXRenderer>();
    //Hall_Crow_3->SetFBXMesh("Hall_Crow_3_MESH.fbx", "ContentAniMeshDeffered");
    //Hall_Crow_3->GetTransform()->SetLocalPosition({ 0.0f, -1.0f, 0.0f });
    //Hall_Crow_3->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 0.0f });
    ////
    //auto Units = Hall_Crow_3->GetAllRenderUnit();
    //
    //Units[4][0]->Color.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
    //Units[5][0]->Color.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
    ////
    //Hall_Crow_3->CreateFBXAnimation("Crow_Player_Sat_Bored", "Hall_Crow_3_Bored_Anim.fbx");
    //Hall_Crow_3->ChangeAnimation("Crow_Player_Sat_Bored");
    //
    Hall_Banker = CreateComponent<ContentFBXRenderer>();
    Hall_Banker->SetFBXMesh("BANKER_MESH.fbx", "ContentAniMeshDeffered");
    Hall_Banker->GetTransform()->SetLocalRotation({ 0.0f, 135.0f, 0.0f });
    Hall_Banker->GetTransform()->SetLocalPosition({ -16.5f, 5.0f, 9.5f });
    Hall_Banker->GetTransform()->SetLocalScale(float4::ONE * 3.0f);
    
    //Hall_Banker->CreateFBXAnimation("BANKER_IDLE", "BANKER_IDLE.fbx");
    //Hall_Banker->CreateFBXAnimation("BANKER_WRITE_PAUSEDLOOP", "BANKER_WRITE_PAUSEDLOOP.fbx");
    //Hall_Banker->CreateFBXAnimation("BANKER_WRITE_RESUME", "BANKER_WRITE_RESUME.fbx");
    Hall_Banker->CreateFBXAnimation("BANKER_WRITELOOP", "BANKER_WRITELOOP.fbx");
    //Hall_Banker->CreateFBXAnimation("BANKER_WRITEPAUSE", "BANKER_WRITEPAUSE.fbx");

    Hall_Banker->ChangeAnimation("BANKER_WRITELOOP");
    
    Book = CreateComponent<ContentFBXRenderer>();
    Book->SetFBXMesh("Book.fbx", "ContentMeshDeffered");
    Book->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    Book->GetTransform()->SetLocalPosition({ -14.5f, 5.0f, 7.5f });
}

void Start_BackGround::Update(float _DeltaTime)
{
    MoveCamera(_DeltaTime);
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