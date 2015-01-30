// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
//
// Read http://lucumr.pocoo.org/2012/9/24/websockets-101/ for a nice intro to web sockets. 
// libwebsocket client wrapper. 
//
// Server maintains an array of FWebSockets. 
// client just has one FWebSocket;

#include "HTML5NetworkingPCH.h"

class FWebSocketServer
{
public:
	FWebSocketServer(); 
	~FWebSocketServer();
		
	bool Init(uint32, FWebsocketClientConnectedCallBack);
	bool Tick();
	FString Info(); 

private: 
	FWebsocketClientConnectedCallBack  ConnectedCallBack;
	TArray<FWebSocket*> ConnectedClients; 

	WebSocketInternalContext* Context;
	struct libwebsocket_protocols* Protocols;

	friend class FWebSocket;

};


