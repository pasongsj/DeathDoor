#include "PreCompileHeader.h"
#include "PhysXTestLevel.h"

#include <ctype.h>
#include "PhysXTestActor.h"
#include "PhysXTestPlane.h"


#include <PhysXSDKSnippets/SnippetUtils.h>
#include <PhysXSDKSnippets/SnippetPrint.h>
#include <PhysXSDKSnippets/SnippetPVD.h>

PhysXTestLevel::PhysXTestLevel() 
{
}

PhysXTestLevel::~PhysXTestLevel() 
{
	Release();
}

void PhysXTestLevel::Start()
{
}

void PhysXTestLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	Initialize();

	CreateActor<PhysXTestActor>();
	CreateActor<PhysXTestPlane>();

	std::shared_ptr<PhysXTestPlane> pWallPlane = CreateActor<PhysXTestPlane>();
}

void PhysXTestLevel::LevelChangeEnd()
{
	Release();
	AllActorDestroy();
}

void PhysXTestLevel::Update(float _DeltaTime)
{
	Simulate(_DeltaTime,true);
}


// 초기화
void PhysXTestLevel::Initialize()
{
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);

	if (!m_pFoundation)
	{
		MsgAssert("PxFoundation failed!");
	}

	m_pPvd = PxCreatePvd(*m_pFoundation);

	if (!m_pPvd)
	{
		MsgAssert("PxPvd failed!");
	}

	physx::PxPvdTransport* pTransport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);

	if (!pTransport)
	{
		MsgAssert("Transport failed!");
	}

	bool bConnect = m_pPvd->connect(*pTransport, physx::PxPvdInstrumentationFlag::eALL);

	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, physx::PxTolerancesScale(), true, m_pPvd);

	if (!m_pPhysics)
	{
		MsgAssert("PxPhysics failed!");
	}

	physx::PxSceneDesc SceneDesc(m_pPhysics->getTolerancesScale());
	SceneDesc.gravity = physx::PxVec3(0.f, -98.1f, 0.0f);
	m_pDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	SceneDesc.cpuDispatcher = m_pDispatcher;
	SceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	m_pScene = m_pPhysics->createScene(SceneDesc);

	if (!m_pScene)
	{
		MsgAssert("PxScene failed!");
	}


	physx::PxPvdSceneClient* pPvdClient = m_pScene->getScenePvdClient();
	if (pPvdClient)
	{
		pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	m_pCooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_pFoundation, physx::PxCookingParams(m_pPhysics->getTolerancesScale()));
	if (!m_pCooking)
	{
		MsgAssert("PxCreateCooking failed!");
	}
}


// 물리연산
void PhysXTestLevel::Simulate(float _Deltatime,bool _Value)
{
	m_pScene->simulate(_Deltatime);
	m_pScene->fetchResults(_Value);
}

// 메모리 해제
void PhysXTestLevel::Release()
{
	PX_RELEASE(m_pScene);
	PX_RELEASE(m_pDispatcher);
	PX_RELEASE(m_pPhysics);
	PX_RELEASE(m_pCooking);
	if (m_pPvd)
	{
		physx::PxPvdTransport* pTransport = m_pPvd->getTransport();
		m_pPvd->release();	
		m_pPvd = nullptr;
		PX_RELEASE(pTransport);
	}
	PX_RELEASE(m_pFoundation);
}
