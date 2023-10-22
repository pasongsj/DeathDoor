#include "PreCompileHeader.h"
#include "PhysXDefault.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTransform.h>
#include <math.h>

physx::PxAggregate* PhysXDefault::m_pAggregate = nullptr;

PhysXDefault::PhysXDefault() 
{
}

PhysXDefault::~PhysXDefault() 
{
}


float4 PhysXDefault::ToEulerAngles(const physx::PxQuat& q) {
	float4 angles;    //yaw pitch roll
	const float x = q.x;
	const float y = q.y;
	const float z = q.z;
	const float w = q.w;

	// roll (y-axis rotation)
	float sinr_cosp = 2 * (w * x + y * z);
    float cosr_cosp = 1 - 2 * (x * x + y * y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (x-axis rotation)
    float sinp = 2 * (w * y - z * x);
	if (std::abs(sinp) >= 1)
	{
		angles.y = std::copysign(GameEngineMath::PIE / 2, sinp); // use 90 degrees if out of range
	}

	else
	{
		angles.y = std::asin(sinp);
	}

	// yaw (z-axis rotation)
    float siny_cosp = 2 * (w * z + x * y);
    float cosy_cosp = 1 - 2 * (y * y + z * z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);
	return angles;
}

void PhysXDefault::SetWorldPosWithParent(float4 _Pos, float4 _Rot)
{
    if (nullptr != m_pRigidDynamic)
    {
        if (_Rot == float4::ZERONULL)
        {
            ParentActor.lock()->GetTransform()->SetWorldPosition(_Pos);
            m_pRigidDynamic->setGlobalPose(float4::PhysXTransformReturn(ParentActor.lock()->GetTransform()->GetWorldRotation(), _Pos));
        }
        else
        {

            ParentActor.lock()->GetTransform()->SetWorldPosition(_Pos);
            ParentActor.lock()->GetTransform()->SetWorldRotation(_Rot);
            m_pRigidDynamic->setGlobalPose(float4::PhysXTransformReturn(_Rot, _Pos));
        }
        return;
    }
    if (nullptr != m_pRigidStatic)
    {
        if (_Rot == float4::ZERONULL)
        {
            ParentActor.lock()->GetTransform()->SetWorldPosition(_Pos);
            m_pRigidStatic->setGlobalPose(float4::PhysXTransformReturn(ParentActor.lock()->GetTransform()->GetWorldRotation(), _Pos));
        }
        else
        {

            ParentActor.lock()->GetTransform()->SetWorldPosition(_Pos);
            ParentActor.lock()->GetTransform()->SetWorldRotation(_Rot);
            m_pRigidStatic->setGlobalPose(float4::PhysXTransformReturn(_Rot, _Pos));
        }
        return;
    }
}

float4 PhysXDefault::GetWorldPosition()
{
    
    if (m_pRigidDynamic != nullptr)
    {
        return float4(m_pRigidDynamic->getGlobalPose().p.x, m_pRigidDynamic->getGlobalPose().p.y, m_pRigidDynamic->getGlobalPose().p.z);
    }
    if (m_pRigidStatic != nullptr)
    {
        return float4(m_pRigidStatic->getGlobalPose().p.x, m_pRigidStatic->getGlobalPose().p.y, m_pRigidStatic->getGlobalPose().p.z);
    }
    else
    {
        return float4::ZERONULL;
    }    
}

float4 PhysXDefault::GetQuaternionEulerAngles(float4 rot)
{
    float4 q1 = rot;
    float sqw = q1.w * q1.w;
    float sqx = q1.x * q1.x;
    float sqy = q1.y * q1.y;
    float sqz = q1.z * q1.z;
    float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
    float test = q1.x * q1.w - q1.y * q1.z;
    float4 v;

    if (test > 0.4995f * unit)
    { // singularity at north pole
        v.y = 2.0f * std::atan2(q1.y, q1.x);
        v.x = GameEngineMath::PIE / 2.0f;
        v.z = 0;
        return NormalizeAngles(v);
    }
    if (test < -0.4995f * unit)
    { // singularity at south pole
        v.y = -2.0f * std::atan2(q1.y, q1.x);
        v.x = -GameEngineMath::PIE / 2;
        v.z = 0;
        return NormalizeAngles(v);
    }

    rot = float4(q1.w, q1.z, q1.x, q1.y);
    v.y = std::atan2(2.0f * rot.x * rot.w + 2.0f * rot.y * rot.z, 1 - 2.0f * (rot.z * rot.z + rot.w * rot.w));     // Yaw
    v.x = std::asin(2.0f * (rot.x * rot.z - rot.w * rot.y));                             // Pitch
    v.z = std::atan2(2.0f * rot.x * rot.y + 2.0f * rot.z * rot.w, 1 - 2.0f * (rot.y * rot.y + rot.z * rot.z));      // Roll
    return NormalizeAngles(v);
}

float4 PhysXDefault::GetQuaternionEulerAngles(physx::PxQuat rot)
{
    physx::PxQuat q1 = rot;
    float sqw = q1.w * q1.w;
    float sqx = q1.x * q1.x;
    float sqy = q1.y * q1.y;
    float sqz = q1.z * q1.z;
    float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
    float test = q1.x * q1.w - q1.y * q1.z;
    float4 v;

    if (test > 0.4995f * unit)
    { // singularity at north pole
        v.y = 2.0f * std::atan2(q1.y, q1.x);
        v.x = GameEngineMath::PIE / 2.0f;
        v.z = 0;
        return NormalizeAngles(v);
    }
    if (test < -0.4995f * unit)
    { // singularity at south pole
        v.y = -2.0f * std::atan2(q1.y, q1.x);
        v.x = -GameEngineMath::PIE / 2;
        v.z = 0;
        return NormalizeAngles(v);
    }

    rot = physx::PxQuat(q1.w, q1.z, q1.x, q1.y);
    v.y = std::atan2(2.0f * rot.x * rot.w + 2.0f * rot.y * rot.z, 1 - 2.0f * (rot.z * rot.z + rot.w * rot.w));     // Yaw
    v.x = std::asin(2.0f * (rot.x * rot.z - rot.w * rot.y));                             // Pitch
    v.z = std::atan2(2.0f * rot.x * rot.y + 2.0f * rot.z * rot.w, 1 - 2.0f * (rot.y * rot.y + rot.z * rot.z));      // Roll
    return NormalizeAngles(v);
}

float4 PhysXDefault::NormalizeAngles(float4 angles)
{
    angles.x = NormalizeAngle(angles.x);
    angles.y = NormalizeAngle(angles.y);
    angles.z = NormalizeAngle(angles.z);
    return angles;
}

float PhysXDefault::NormalizeAngle(float angle)
{
    while (angle > GameEngineMath::PIE * 2.0f)
        angle -= GameEngineMath::PIE * 2.0f;
    while (angle < 0)
        angle += GameEngineMath::PIE * 2.0f;
    return angle;
}

float4 PhysXDefault::RodriguesRotate(vector p, vector v, float a) 
{
    float ca = cos(a), sa = sin(a);
    float t = 1.f - ca;
    float x = v.x, y = v.y, z = v.z;
    matrix r = {
        {ca + x * x * t, x * y * t - z * sa, x * z * t + y * sa},
        {x * y * t + z * sa, ca + y * y * t, y * z * t - x * sa},
        {z * x * t - y * sa, z * y * t + x * sa, ca + z * z * t}
    };
    vector Result = matrixMultiply(r, p);
    return float4{ Result.x, Result.y, Result.z };
}

float PhysXDefault::dotProduct(vector v1, vector v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

PhysXDefault::vector PhysXDefault::matrixMultiply(matrix m, vector v)
{
    vector mm = { dotProduct(m.i, v), dotProduct(m.j, v), dotProduct(m.k, v) };
    return mm;
}

void PhysXDefault::DeathAndRelease()
{
    if (nullptr != m_pRigidDynamic && true == m_pRigidDynamic->isReleasable())
    {
        m_pShape->userData = nullptr;
        m_pRigidDynamic->release();
        m_pRigidDynamic = nullptr;
        ParentActor.lock()->Death();
    }
    if (nullptr != m_pRigidStatic && true == m_pRigidStatic->isReleasable())
    {
        m_pShape->userData = nullptr;
        m_pRigidStatic->release();
        m_pRigidStatic = nullptr;
        ParentActor.lock()->Death();
    }
}

void PhysXDefault::Release()
{
    if (m_pRigidDynamic != nullptr && m_pRigidDynamic->isReleasable())
    {
        m_pShape->userData = nullptr;
        m_pRigidDynamic->release();
        m_pRigidDynamic = nullptr;
    }
    if (m_pRigidStatic != nullptr && m_pRigidStatic->isReleasable())
    {
        m_pShape->userData = nullptr;
        m_pRigidStatic->release();
        m_pRigidStatic = nullptr;
    }
    if (m_pController != nullptr)
    {
        if (m_pScene->userData != nullptr)
        {
            m_pController->release();
        }

        m_pShape->userData = nullptr;
        m_pController = nullptr;
    }
}

void PhysXDefault::SetFilterData(PhysXFilterGroup _ThisFilter, PhysXFilterGroup _OtherFilter0, PhysXFilterGroup _OtherFilter1, PhysXFilterGroup _OtherFilter2)
{
    m_pShape->setSimulationFilterData
    (
        physx::PxFilterData
        (
            static_cast<physx::PxU32>(_ThisFilter),
            static_cast<physx::PxU32>(_OtherFilter0),
            static_cast<physx::PxU32>(_OtherFilter1),
            static_cast<physx::PxU32>(_OtherFilter2)
        )
    );
}

void PhysXDefault::SetRigidCollide(bool _Value)
{
    m_pShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, _Value);
}

void PhysXDefault::CreateShape(SubShapeType _Type, float4 _Scale, float4 _LocalPos)
{
	switch (_Type)
	{
	case SubShapeType::BOX:
	{
		//m_pSubShape =GetPhysics()->createShape(physx::PxBoxGeometry(_Scale.half().PhysXVec3Return()), *m_pMaterial);
		m_pSubShape = GetPhysics()->createShape(physx::PxBoxGeometry(_Scale.half().PhysXVec3Return()), *m_pMaterial);

		//m_pController->getActor()->attachShape(*m_pSubShape);

		m_pSubShape->setLocalPose(physx::PxTransform(_LocalPos.PhysXVec3Return()/*, physx::PxQuat(physx::PxHalfPi, float4(0, 0, 1).PhysXVec3Return())*/));

		m_pSubShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		m_pSubShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

		m_pSubShape->setSimulationFilterData
		(
			physx::PxFilterData
			(
				static_cast<physx::PxU32>(PhysXFilterGroup::MonsterSkill),
				0,
				0,
				0
			)
		);
	}
	break;
	case SubShapeType::SPHERE:
	{
		m_pSubShape = GetPhysics()->createShape(physx::PxSphereGeometry(_Scale.half().PhysXVec3Return().y), *m_pMaterial);


		m_pSubShape->setLocalPose(physx::PxTransform(_LocalPos.PhysXVec3Return(), physx::PxQuat(physx::PxHalfPi, float4(0, 0, 1).PhysXVec3Return())));

		m_pSubShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		m_pSubShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

		m_pSubShape->setSimulationFilterData
		(
			physx::PxFilterData
			(
				static_cast<physx::PxU32>(PhysXFilterGroup::MonsterSkill),
				0,
				0,
				0
			)
		);
	}
	break;
	default:
		break;

	}
}
