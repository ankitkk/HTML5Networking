// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
//
// libwebsocket client wrapper. 
//
// Server maintains an array of FWebSockets.  
// Client just has one FWebSocket connect to the server

#include "HTML5NetworkingPCH.h"

class FWebSocket
{

public: 

	// Client Socket. 
	FWebSocket(const FInternetAddr& ServerAddress);
	// Server Socket. 
	FWebSocket(WebSocketInternalContext* InContext, WebSocketInternal* Wsi);

	~FWebSocket();

	void SetConnectedCallBack(FWebsocketInfoCallBack CallBack);
	void SetErrorCallBack(FWebsocketInfoCallBack CallBack);
	void SetRecieveCallBack(FWebsocketPacketRecievedCallBack CallBack);

	bool Send(uint8* Data, uint32 Size);

	// Service libwebsockets. 
	void Tick();

	FString RemoteEndPoint();
	FString LocalEndPoint(); 

private:

	void OnRawRecieve(void* Data, uint32 Size);
	void OnRawWebSocketWritable(WebSocketInternal* wsi);

	WebSocketInternalContext* Context;
	WebSocketInternal* Wsi;

	FWebsocketPacketRecievedCallBack  RecievedCallBack; 
	FWebsocketInfoCallBack ConnectedCallBack;
	FWebsocketInfoCallBack ErrorCallBack;

	TArray<uint8> RecievedBuffer;
	TArray<TArray<uint8>> OutgoingBuffer;

	bool IsServerSide; 

	struct libwebsocket_protocols* Protocols;

#if !PLATFORM_HTML5
	static int unreal_networking_server(struct libwebsocket_context *, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);
	static int unreal_networking_client(struct libwebsocket_context *, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);
#endif 

	friend class FWebSocketServer;

	int SockFd;
};


