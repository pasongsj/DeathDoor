#include "PreCompileHeader.h"
#include "PhysXTestLevel.h"

#include <ctype.h>
#include "PhysXTestActor.h"


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
}

void PhysXTestLevel::LevelChangeEnd()
{
}

void PhysXTestLevel::Update(float _DeltaTime)
{
	Simulate(true);
}


// 초기화
void PhysXTestLevel::Initialize()
{
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);

	//m_pPvd = PxCreatePvd(*m_pFoundation);
	//physx::PxPvdTransport* pTransport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 54321, 1000);
	//m_pPvd->connect(*pTransport, physx::PxPvdInstrumentationFlag::eALL);

	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, physx::PxTolerancesScale(), true);

	physx::PxSceneDesc SceneDesc(m_pPhysics->getTolerancesScale());
	SceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	m_pDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	SceneDesc.cpuDispatcher = m_pDispatcher;
	SceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	m_pScene = m_pPhysics->createScene(SceneDesc);

	//physx::PxPvdSceneClient* pPvdClient = m_pScene->getScenePvdClient();
	//if (pPvdClient)
	//{
	//	pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
	//	pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
	//	pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	//}

	//m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.5f);

	//physx::PxRigidStatic* pGroundPlane = PxCreatePlane(*m_pPhysics, physx::PxPlane(0, 1, 0, 10000), *m_pMaterial);
	//m_pScene->addActor(*pGroundPlane);

	CreateActor<PhysXTestActor>();
}


// 물리연산
void PhysXTestLevel::Simulate(bool _Value)
{
	m_pScene->simulate(1.0f / 60.0f);
	m_pScene->fetchResults(_Value);
}

// 메모리 해제
void PhysXTestLevel::Release()
{
	PX_RELEASE(m_pScene);
	PX_RELEASE(m_pDispatcher);
	PX_RELEASE(m_pPhysics);
	//if (m_pPvd)
	//{
	//	physx::PxPvdTransport* pTransport = m_pPvd->getTransport();
	//	m_pPvd->release();	
	//	m_pPvd = nullptr;
	//	PX_RELEASE(pTransport);
	//}
	PX_RELEASE(m_pFoundation);
}
