/**
 * @file
 */

#pragma once

#include "network/AbstractServerNetwork.h"

namespace network {

class ServerNetwork : public AbstractServerNetwork {
private:
	using Super = AbstractServerNetwork;
public:
	ServerNetwork(const ProtocolHandlerRegistryPtr& protocolHandlerRegistry,
			const core::EventBusPtr& eventBus, const metric::MetricPtr& metric);

	bool packetReceived(ENetEvent& event) override;
};

typedef std::shared_ptr<ServerNetwork> ServerNetworkPtr;

}
