#pragma once
#include <Protocol\TransferredData.h>
#include <Protocol\BaseHeader.h>
#include <memory>


class NetworkStrategy
{
public:
	virtual bool Connect(const std::string& Address, unsigned short port) = 0;

	virtual bool Ready() = 0;
	virtual BaseHeader* GetPacket() = 0;

	virtual bool Send(const TransferredData& Data) = 0;

	virtual ~NetworkStrategy() {};
};

