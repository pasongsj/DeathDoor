#include "PrecompileHeader.h"
#include "GameEngineNet.h"
#include "GameEngineSerializer.h"
#include "GameEnginePacket.h"

GameEngineNet::GameEngineNet()
{
}

GameEngineNet::~GameEngineNet()
{
	IsNetValue = false;
}

void GameEngineNet::RecvThreadFunction(SOCKET _Socket, GameEngineNet* _Net)
{
	char Data[1024] = { 0 };

	GameEngineSerializer Serializer;
	int PacketType = -1;
	int PacketSize = -1;

	while (true == _Net->IsNet())
	{
		// 상대가 보내온 패킷의 양.
		int Result = recv(_Socket, Data, sizeof(Data), 0);

		// 접속 끊김
		if (-1 == Result)
		{
			return;
		}

		// 접속 끊김
		if (SOCKET_ERROR == _Socket || INVALID_SOCKET == _Socket)
		{
			return;
		}
		Serializer.Write(Data, Result);

		if (8 > Serializer.GetWriteOffSet())
		{
			continue;
		}

		// 8바이트 이상 받은 상태
		if (-1 == PacketType)
		{
			// 패킷타입 알아낸다.
			{
				unsigned char* TypePivotPtr = &Serializer.GetDataPtr()[0];
				int* ConvertPtr = reinterpret_cast<int*>(TypePivotPtr);
				PacketType = *ConvertPtr;
			}

			// 사이즈 알아내고
			{
				unsigned char* SizePivotPtr = &Serializer.GetDataPtr()[4];
				int* ConvertPtr = reinterpret_cast<int*>(SizePivotPtr);
				PacketSize = *ConvertPtr;
			}
		}

		if (-1 == PacketSize)
		{
			return;
		}

		// 8바이트 이상 받았지만
		// 그걸 통해서 알아낸 패킷의 크기보다는 덜온 상태 체크.
		if (static_cast<unsigned int>(PacketSize) > Serializer.GetWriteOffSet())
		{
			continue;
		}

		while (true)
		{
			// ConnectIDPacket
			std::shared_ptr<GameEnginePacket> Packet = _Net->Dispatcher.ConvertPacket(PacketType, Serializer);

			_Net->Dispatcher.ProcessPacket(Packet);

		}
	}
}



void GameEngineNet::SendPacket(std::shared_ptr<GameEnginePacket> _Packet)
{
	GameEngineSerializer Ser;
	_Packet->SerializePacket(Ser);
	Send(reinterpret_cast<const char*>(Ser.GetDataPtr()), Ser.GetWriteOffSet());

}

void GameEngineNet::Send(SOCKET _Socket, const char* Data, unsigned int _Size)
{
	send(_Socket, Data, _Size, 0);
}