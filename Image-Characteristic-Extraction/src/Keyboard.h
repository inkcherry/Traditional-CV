
#pragma once

class KeyboardServer;

class KeyboardClient
{
public:
	KeyboardClient( const KeyboardServer& kServer );
	bool UpIsPressed() const;
	bool DownIsPressed() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool SpaceIsPressed() const;
	bool EnterIsPressed() const;
private:
	const KeyboardServer& server;
};

class KeyboardServer
{
	friend KeyboardClient;
public:
	KeyboardServer();

	void OnUpPressed();
	void OnDownPressed();
	void OnLeftPressed();
	void OnRightPressed();
	void OnSpacePressed();
	void OnEnterPressed();

	void OnUpReleased();
	void OnDownReleased();
	void OnLeftReleased();
	void OnRightReleased();
	void OnSpaceReleased();
	void OnEnterReleased();
private:
	bool upIsPressed;
	bool downIsPressed;
	bool leftIsPressed;
	bool rightIsPressed;
	bool spaceIsPressed;
	bool enterIsPressed;
};