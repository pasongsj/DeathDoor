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

	//한 번의 방출에 몇개씩 방출할건지.
	int EmitNum = 1;

	//파티클이 동시에 몇개까지 존재할 수 있는가 or Disposable이라면 몇개까지 생성할건가.
	int MaxParticle = 0;

	//방출 간격
	float EmitInterTime = 0.0f;

	//제거 간격, 이 시간에 따라 알파값 감소 시간이 변함 (1.0f / MaxLiveTime * Deltatime)
	float MaxLiveTime = 0.0f;
};

struct DynamicParticleSetter
{
	//플레이어의 위치에 따라, 벡터도 변하기 때문에 이 부분도 동적으로 변하게 해야 할 것 같긴 한데 일단은 고정
	float4 StandardDir = { 0.0f, 0.0f, 0.0f };
	float4 RangeDir = { 0.0f, 0.0f, 0.0f };

	float4 StandardScale = { 0.0f, 0.0f, 0.0f };
	float4 RangeScale = { 0.0f, 0.0f, 0.0f };

	//플레이어의 위치 등, 지속적으로 정보를 받아야 하기 때문에 포인터로 받음
	const TransformData* StandardPosition;
	float4 RangePosition = {0.0f, 0.0f, 0.0f };

	float StandardSpeed = 0.0f;
	float range_Speed = 0.0f;

	//한 번의 방출에 몇개씩 방출할건지.
	int EmitNum = 1;

	int MaxParticle = 0;
	float EmitInterTime = 0.0f;
	float MaxLiveTime = 0.0f;
};