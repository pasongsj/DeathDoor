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
	unsigned int PacketType = -1;
	unsigned int PacketSize = -1;

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

			if (nullptr != Packet)
			{
				_Net->RecvPacketLock.lock();
				_Net->RecvPacket.push_back(Packet);
				_Net->RecvPacketLock.unlock();
			}
			else
			{
				int a = 0;
			}

			// Write가 증가할 것이다.
			// _Net->Dispatcher.ProcessPacket(Packet);

			// 12 바이트가 날아왔는데 12바이트가 처리됐다.
			if (Serializer.GetWriteOffSet() == Serializer.GetReadOffSet())
			{
				Serializer.Reset();
				PacketType = -1;
				PacketSize = -1;
				break;
			}
			else
			{
				unsigned int RemainSize = Serializer.GetWriteOffSet() - Serializer.GetReadOffSet();

				if (8 > RemainSize)
				{
					break;
				}

				{
					unsigned char* TypePivotPtr = &Serializer.GetDataPtr()[0];
					int* ConvertPtr = reinterpret_cast<int*>(TypePivotPtr);
					PacketType = *ConvertPtr;
				}

				{
					unsigned char* SizePivotPtr = &Serializer.GetDataPtr()[4];
					int* ConvertPtr = reinterpret_cast<int*>(SizePivotPtr);
					PacketSize = *ConvertPtr;
				}

				if (RemainSize < PacketSize)
				{
					// 남은 찌거기를 다 앞으로 밀어버린다.
					Serializer.ClearReadData();
					break;
				}
			}

		}
	}
}



void GameEngineNet::SendPacket(std::shared_ptr<GameEnginePacket> _Packet, int _IgnoreID)
{
	GameEngineSerializer Ser;
	_Packet->SerializePacket(Ser);
	Send(reinterpret_cast<const char*>(Ser.GetDataPtr()), Ser.GetWriteOffSet(), _IgnoreID);
}


void GameEngineNet::Send(SOCKET _Socket, const char* Data, unsigned int _Size)
{
	send(_Socket, Data, _Size, 0);
}

void GameEngineNet::UpdatePacket()
{
	RecvPacketLock.lock();

	if (0 >= RecvPacket.size())
	{
		RecvPacketLock.unlock();
		return;
	}

	ProcessPackets = RecvPacket;
	RecvPacket.clear();
	RecvPacketLock.unlock();

	for (std::shared_ptr<GameEnginePacket> Packet : ProcessPackets)
	{
		Dispatcher.ProcessPacket(Packet);
	}

	ProcessPackets.clear();
};