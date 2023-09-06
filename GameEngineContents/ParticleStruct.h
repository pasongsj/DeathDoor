#pragma once
#include "PreCompileHeader.h"

struct StaticParticleSetter
{
	/*파티클 정보의 범위(일단은 z축 없이 x, y만)

	Example :

		Standard는 기준값
		X : StandardDir.x - RangeDir.x ~ StandardDir.x + RangeDir.x
		Y : StandardDir.y - RangeDir.y ~ StandardDir.y + RangeDir.y
		Z : StandardDir.z - RangeDir.z ~ StandardDir.z + RangeDir.z

		---------------------------------------------------------------

		MaxParticle : 파티클의 최대개수
		EmitInterTime : 파티클 생성주기
		MaxLiveTime : 파티클이 살아있는 시간 (값이 0.5f라면, 0.5초 후에 사라짐)

	*/

	float4 StandardDir = { 0.0f, 0.0f, 0.0f };
	float4 RangeDir = { 0.0f, 0.0f, 0.0f };

	float4 StandardScale = { 0.0f, 0.0f, 0.0f };
	float4 RangeScale = { 0.0f, 0.0f, 0.0f };

	float4 StandardPosition = { 0.0f, 0.0f, 0.0f };
	float4 RangePosition = { 0.0f, 0.0f, 0.0f };

	float StandardSpeed = 0.0f;
	float range_Speed = 0.0f;

	int MaxParticle = 0;
	float EmitInterTime = 0.0f;
	float MaxLiveTime = 0.0f;
};

struct DynamicParticleSetter
{
	float4 StandardDir = { 0.0f, 0.0f, 0.0f };
	float4 RangeDir = { 0.0f, 0.0f, 0.0f };

	float4 StandardScale = { 0.0f, 0.0f, 0.0f };
	float4 RangeScale = { 0.0f, 0.0f, 0.0f };

	const TransformData* StandardPosition;

	float StandardSpeed = 0.0f;
	float range_Speed = 0.0f;

	int MaxParticle = 0;
	float EmitInterTime = 0.0f;
	float MaxLiveTime = 0.0f;
};