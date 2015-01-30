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
	// CallBack when data is ready to pushed upstream. 
	void SetRecieveCallBack(FWebsocketPacketRecievedCallBack CallBack);

	// Send data.
	bool Send(uint8* Data, uint32 Size);

	// Service libwebSocket. 
	void Tick();

	FString RemoteEndPoint();
	FString LocalEndPoint(); 

private:

	void OnRawRecieve(void* Data, uint32 Size);
	void OnRawWebSocketWritable(WebSocketInternal* wsi);


	// context. 
	WebSocketInternalContext* Context;
	// internal 
	WebSocketInternal* Wsi;

	FWebsocketPacketRecievedCallBack  RecievedCallBack; 
	FWebsocketInfoCallBack ConnectedCallBack;
	FWebsocketInfoCallBack ErrorCallBack;

	// data being received. 
	TArray<uint8> RecievedBuffer;
	// data being sent out. 
	TArray<TArray<uint8>> OutgoingBuffer;
	// Current Write Mode.
	uint32 CurrentTotalWritten;

	uint32 BytesNeedToBeRead; 

	bool IsServerSide; 

	struct libwebsocket_protocols* Protocols;

#if !PLATFORM_HTML5
	static int unreal_networking_server(struct libwebsocket_context *, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);
	static int unreal_networking_client(struct libwebsocket_context *, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);
#endif 

	friend class FWebSocketServer;

	int SockFd;
};


