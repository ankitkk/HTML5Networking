### Websocket Networking plugin for Unreal Engine 4. 

- provides websocket transport layer for unreal engine 4. 
- uses [libwebsockets](http://libwebsocket.org) for the server side and client side for non html5 clients.  
- html5 clients use emscripten's sockets abstraction. 

#### How to. 

- clone this in Engine\Plugins\Experimental directory. 


BaseEngine.ini changes. 

Add the following section

[/Script/HTML5Networking.WebSocketNetDriver]
AllowPeerConnections=False
AllowPeerVoice=False
ConnectionTimeout=6000.0
InitialConnectTimeout=6000.0
AckTimeout=10.0
KeepAliveTime=20.2
MaxClientRate=15000
MaxInternetClientRate=10000
RelevantTimeout=5.0
SpawnPrioritySeconds=1.0
ServerTravelPause=4.0
NetServerMaxTickRate=30
LanServerMaxTickRate=35
WebSocketPort=8889
NetConnectionClassName="/Script/HTML5Networking.WebSocketConnection"
MaxPortCountToTry=512

In section [/Script/Engine.Engine] disable comment out NetDriverDefinitions and add 

NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/HTML5Networking.WebSocketNetDriver",DriverClassNameFallback="/Script/HTML5Networking.IpNetDriver")

To enable this Net Driver. 

Build! 

Copyright 2015 Epic Games. 
