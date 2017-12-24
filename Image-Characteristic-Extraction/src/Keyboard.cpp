
#include "Keyboard.h"


KeyboardClient::KeyboardClient( const KeyboardServer& kServer )
	: server( kServer )
{}

bool KeyboardClient::UpIsPressed() const
{
	return server.upIsPressed;
}
bool KeyboardClient::DownIsPressed() const
{
	return server.downIsPressed;
}
bool KeyboardClient::LeftIsPressed() const
{
	return server.leftIsPressed;
}
bool KeyboardClient::RightIsPressed() const
{
	return server.rightIsPressed;
}
bool KeyboardClient::SpaceIsPressed() const
{
	return server.spaceIsPressed;
}
bool KeyboardClient::EnterIsPressed() const
{
	return server.enterIsPressed;
}



KeyboardServer::KeyboardServer()
:	upIsPressed( false ),
	downIsPressed( false ),
	leftIsPressed( false ),
	rightIsPressed( false ),
	spaceIsPressed( false ),
	enterIsPressed( false )
{}

void KeyboardServer::OnUpPressed()
{
	upIsPressed = true;
}
void KeyboardServer::OnDownPressed()
{
	downIsPressed = true;
}
void KeyboardServer::OnLeftPressed()
{
	leftIsPressed = true;
}
void KeyboardServer::OnRightPressed()
{
	rightIsPressed = true;
}
void KeyboardServer::OnSpacePressed()
{
	spaceIsPressed = true;
}
void KeyboardServer::OnEnterPressed()
{
	enterIsPressed = true;
}

void KeyboardServer::OnUpReleased()
{
	upIsPressed = false;
}
void KeyboardServer::OnDownReleased()
{
	downIsPressed = false;
}
void KeyboardServer::OnLeftReleased()
{
	leftIsPressed = false;
}
void KeyboardServer::OnRightReleased()
{
	rightIsPressed = false;
}
void KeyboardServer::OnSpaceReleased()
{
	spaceIsPressed = false;
}
void KeyboardServer::OnEnterReleased()
{
	enterIsPressed = false;
}