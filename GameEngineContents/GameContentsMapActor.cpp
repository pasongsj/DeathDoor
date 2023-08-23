#include "PreCompileHeader.h"
#include "GameContentsMapActor.h"

GameContentsMapActor::GameContentsMapActor()
{
}

GameContentsMapActor::~GameContentsMapActor()
{
}
void GameContentsMapActor::Update(float _DeltaTime)
{
	if (true == Flickoption)
	{
		FlickDuration -= _DeltaTime;//5.0f
		FlickInterval -= _DeltaTime;//1.0f
		if (FlickDuration < 0.0f)
		{
			Renderer->On();
			Flickoption = false;
			return;
		}
		if (FlickInterval > 0.25)// 0.5~1.0f
		{
			Renderer->Off();
		}
		else if (FlickInterval > 0.0f)//0~ 0.5
		{
			Renderer->On();
		}
		else//0.0 
		{
			FlickInterval = 0.5;
		}
	}
}
