#include <Windows.h>
#include "S_PhysicsMath.h"
#include <iostream>
#include <chrono>

// CONST GAME VARIABLES
const int sScrW = 90;
const int sScrH = 32;
const size_t ScreenSize_InBytes = sScrW * sScrH * sizeof(wchar_t);

namespace Game_Vairables
{
	// Game Varibles
	float fSlider_SpeedMag = 45.50;
	double fBallSpeedMag = 40.0;
	const float fSlider_AccelMag = 0.5f;
	const float fBall_AccelMag = 1.5f;

	// Upper Boundary
	Physic::Plane2D UpperBoundary(1.0f, Physic::Plane2D::Center, {45, 5}, 60, 2);
	const wchar_t UpperBound_Symbol = L'U';

	// Lower Boundary
	Physic::Plane2D LowerBoundary(1.0f, Physic::Plane2D::Center, {45, 30}, 60, 2);
	const wchar_t LowerBound_Symbol = L'L';

	// Ball
	Physic::Neutral_Particles Ball(1.0f, {40, 20}, {sScrW, sScrH});
	const wchar_t Ball_Symbol = L'O';
	Vector2D v2dBall_Velocity{rand() % 6 * 1.1f, rand() % 6 * 1.1f};

	// Player's Silder
	Physic::Plane2D Player_Silder(1.0f, Physic::Plane2D::Center, {14, 20}, 2, 5);
	const wchar_t PlayerSymbol = L'P';
	Vector2D v2dPlayer_Silder_Velocity;
	bool bPlayerSilderLimit = false;
	M_Keys Up, Down;

	// Computer's Silder
	Physic::Plane2D Computer_Silder(1.0f, Physic::Plane2D::Center, {76, 20}, 2, 5);
	const wchar_t ComputerSymbol = L'C';
	Vector2D v2dComputerSilder_Velocity;
	bool bCompSilderLimit = false;

	// Imaginary Line
	Position ImgLine{50, 0};

	// Imaginary Ball
	Vector2D v2dImgBall_Velocity;
	Physic::Neutral_Particles ImgBall;

	// Events Triggering
	bool bBallEnterCompRegion = false;

	// Game-Timings
	Physic::Time GameTime(0, 1, 0);

	// Loop Time
	std::chrono::duration<float, std::ratio<1, 1>> SecPassed;
	std::chrono::time_point<std::chrono::system_clock> StartTick, EndTick;
	bool Startit = false;
}

void GameModule_Inialization(wchar_t *Screen);

void CollisionDetection(wchar_t *Screen, Physic::Neutral_Particles &Object, Vector2D &ObjectVelocity);

int main()
{
	// Screen Inailization
	wchar_t *wpScreen = new wchar_t[sScrW * sScrH];

	DWORD bytesWritten = 0;

	SMALL_RECT srWindowSize;
	srWindowSize.Top = 0;
	srWindowSize.Left = 0;
	srWindowSize.Right = sScrW - 1;
	srWindowSize.Bottom = sScrH - 1;

	CONSOLE_FONT_INFOEX cfiFont;
	cfiFont.cbSize = sizeof(cfiFont);
	cfiFont.dwFontSize.X = 26;
	cfiFont.dwFontSize.Y = 26;

	COORD cdBufferSize;
	cdBufferSize.X = sScrW;
	cdBufferSize.Y = sScrH;

	HANDLE OutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (OutHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error in getting Handle  \n\n";
		return 0;
	}
	SetConsoleActiveScreenBuffer(OutHandle);
	if (!SetConsoleWindowInfo(OutHandle, TRUE, &srWindowSize))
	{

		std::cout << "Window not Set   : \n\n";
		auto i = 0;
		std::cin >> i;
		return 0;
	}
	if (!SetConsoleScreenBufferSize(OutHandle, cdBufferSize))
	{
		std::cout << "Buffer size noy Set  :  \n\n";
		auto i = 0;
		std::cin >> i;
		return 0;
	}
	if (!SetCurrentConsoleFontEx(OutHandle, FALSE, &cfiFont))
	{
		std::cout << "Font Not Set   :  \n\n";
		auto i = 0;
		std::cin >> i;
		return 0;
	}

	for (int i = 0; i < sScrW * sScrH; i++)
		wpScreen[i] = L' ';
	// Screen Inialization Finish-------------------------------------------------------------------------

	bool PoitionGet = false;
	bool Reachedposition = false;

	int PlayerScore = 0;
	int ComputerScore = 0;

	int ix = 4, iy = 6;

	bool eh = false;
	swprintf(&wpScreen[30], ScreenSize_InBytes, L"WELCOME TO ");
	swprintf(&wpScreen[sScrW + sScrW + 23], ScreenSize_InBytes, L"DEFENDING BOUNDARIES GAME");
	swprintf(&wpScreen[sScrW * 4 + 2], ScreenSize_InBytes, L"Choose from the following option");
	swprintf(&wpScreen[sScrW * 6 + 12], ScreenSize_InBytes, L"Easy");
	swprintf(&wpScreen[sScrW * 10 + 12], ScreenSize_InBytes, L"Hard");
	swprintf(&wpScreen[sScrW * 14 + 2], ScreenSize_InBytes, L"Enter Space to continue");

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE))
			break;

		wpScreen[sScrW * iy + ix] = L' ';

		if (GetAsyncKeyState(VK_UP))
		{
			if (iy > 6)
				iy = iy - 1;
			eh = false;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (iy < 10)
				iy = iy + 1;
			eh = true;
		}
		wpScreen[sScrW * iy + ix] = L'o';

		WriteConsoleOutputCharacterW(OutHandle, wpScreen, sScrW * sScrH, {0, 0}, &bytesWritten);
	}

	swprintf(&wpScreen[sScrW * 20 + 2], ScreenSize_InBytes, L"You will be given 1 minute. Score maximium to win");
	swprintf(&wpScreen[sScrW * 22 + 2], ScreenSize_InBytes, L"Enter Delete key to continue");

	while (true)
	{
		if (GetAsyncKeyState(VK_DELETE))
			break;

		WriteConsoleOutputCharacterW(OutHandle, wpScreen, sScrW * sScrH, {0, 0}, &bytesWritten);
	}

	for (int i = 0; i < sScrW * sScrH; i++)
		wpScreen[i] = L' ';
	GameModule_Inialization(wpScreen);

	if (eh)
	{
		Game_Vairables::ImgLine.iX = 50;
	}
	else
	{
		Game_Vairables::ImgLine.iX = 65;
	}

	// PlaySoundW(L"My_Life_Is_Party.wav", NULL, SND_ASYNC | SND_FILENAME);

	while (!Game_Vairables::GameTime.IsTimeOver())
	{
		Game_Vairables::StartTick = std::chrono::system_clock::now();

		if (Game_Vairables::Startit)
			Game_Vairables::GameTime.SubtractFrom_FSeconds(Game_Vairables::SecPassed.count());

		// Player Movements
		Game_Vairables::Player_Silder.Draw(wpScreen, {sScrW, sScrH}, L' ');

		if (GetAsyncKeyState(VK_UP))
		{
			Game_Vairables::Up.KeyPressed = true;

			Game_Vairables::Player_Silder.Set_Velocity(Game_Vairables::fSlider_SpeedMag, {0, -1});

			if (Game_Vairables::Player_Silder.ParPos.fY - 4.5f <= Game_Vairables::UpperBoundary.ParPos.iY)
			{
				Game_Vairables::bPlayerSilderLimit = true;
			}

			if (Game_Vairables::Startit && !Game_Vairables::bPlayerSilderLimit)
				Game_Vairables::Player_Silder.Update_Position(Game_Vairables::SecPassed.count());
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			Game_Vairables::Down.KeyPressed = true;

			Game_Vairables::Player_Silder.Set_Velocity(Game_Vairables::fSlider_SpeedMag, {0, 1});
			Game_Vairables::bPlayerSilderLimit = false;
			if (Game_Vairables::Player_Silder.ParPos.fY + 5.0f >= Game_Vairables::LowerBoundary.ParPos.iY)
			{
				Game_Vairables::bPlayerSilderLimit = true;
			}

			if (Game_Vairables::Startit && !Game_Vairables::bPlayerSilderLimit)
				Game_Vairables::Player_Silder.Update_Position(Game_Vairables::SecPassed.count());
		}

		Game_Vairables::Player_Silder.Draw(wpScreen, {sScrW, sScrH}, Game_Vairables::PlayerSymbol);

		// Ball Movements ------ Draw ball on screen

		wpScreen[Game_Vairables::Ball.ParPos.iY * sScrW + Game_Vairables::Ball.ParPos.iX] = L' ';

		if (Game_Vairables::Startit)
			Game_Vairables::Ball.Update_Position(Game_Vairables::SecPassed.count());

		if (Game_Vairables::Ball.ParPos.iX > 80 || Game_Vairables::Ball.ParPos.iX < 10)
		{
			wpScreen[Game_Vairables::Ball.ParPos.iY * sScrW + Game_Vairables::Ball.ParPos.iX] = L' ';

			if (Game_Vairables::Ball.ParPos.iX >= 80)
			{
				PlayerScore++;
			}
			else if (Game_Vairables::Ball.ParPos.iX <= 10)
			{
				ComputerScore++;
			}

			int x = 40;
			int y = rand() % 10;
			Game_Vairables::Ball.ParPos.iX = x;
			Game_Vairables::Ball.ParPos.iY = y + 8;
			Game_Vairables::Ball.ParPos.fX = x;
			Game_Vairables::Ball.ParPos.fY = y + 8;
			wpScreen[Game_Vairables::Ball.ParPos.iY * sScrW + Game_Vairables::Ball.ParPos.iX] = Game_Vairables::Ball_Symbol;
		}
		// Collsion Detection ------- check after every another position And Update Positions

		CollisionDetection(wpScreen, Game_Vairables::Ball, Game_Vairables::v2dBall_Velocity);

		wpScreen[Game_Vairables::Ball.ParPos.iY * sScrW + Game_Vairables::Ball.ParPos.iX] = Game_Vairables::Ball_Symbol;

		// Computer Descsions-----Img Ball Code and other stuff

		Game_Vairables::Computer_Silder.Draw(wpScreen, {sScrW, sScrH}, L' ');
		Game_Vairables::v2dBall_Velocity.DegreesTo_Radians();
		if (Game_Vairables::Ball.ParPos.iX == Game_Vairables::ImgLine.iX && ((Game_Vairables::v2dBall_Velocity.GetDirection() >= 0.0 && Game_Vairables::v2dBall_Velocity.GetDirection() <= 1.5717) || (Game_Vairables::v2dBall_Velocity.GetDirection() >= 1.5714 * 3 && Game_Vairables::v2dBall_Velocity.GetDirection() < 1.5714 * 4)))
		{
			Game_Vairables::ImgBall = Game_Vairables::Ball;
			Game_Vairables::v2dImgBall_Velocity = Game_Vairables::v2dBall_Velocity;

			// Set something true

			while (Game_Vairables::ImgBall.ParPos.iX != Game_Vairables::Computer_Silder.ParPos.iX - 2)
			{
				wpScreen[Game_Vairables::ImgBall.ParPos.iX + sScrW * Game_Vairables::ImgBall.ParPos.iY] = L' ';
				Game_Vairables::ImgBall.Update_Position(Game_Vairables::SecPassed.count());
				CollisionDetection(wpScreen, Game_Vairables::ImgBall, Game_Vairables::v2dImgBall_Velocity);
			}

			PoitionGet = true;
			Reachedposition = false;
		}

		if (Game_Vairables::Computer_Silder.ParPos.iY < Game_Vairables::ImgBall.ParPos.iY)
		{ // Move Down       PoitionGet && !Reachedposition &&

			if (Game_Vairables::Computer_Silder.ParPos.fY + 5.0f >= Game_Vairables::LowerBoundary.ParPos.iY)
			{
				Game_Vairables::bCompSilderLimit = true;
				Reachedposition = true;
				PoitionGet = false;
				Game_Vairables::ImgBall.ParPos *= 0;
				Game_Vairables::v2dImgBall_Velocity *= 0;
			}

			if (!Game_Vairables::bCompSilderLimit && !Reachedposition)
			{
				Game_Vairables::Computer_Silder.Set_Velocity(Game_Vairables::fSlider_SpeedMag, {0, 1});
				Game_Vairables::Computer_Silder.Update_Position(Game_Vairables::SecPassed.count());
			}
		}
		else if (Game_Vairables::Computer_Silder.ParPos.iY > Game_Vairables::ImgBall.ParPos.iY)
		{ // Move Up

			if (Game_Vairables::Computer_Silder.ParPos.fY - 4.5f <= Game_Vairables::UpperBoundary.ParPos.iY)
			{
				Game_Vairables::bCompSilderLimit = true;
				Reachedposition = true;
				PoitionGet = false;
				Game_Vairables::ImgBall.ParPos *= 0;
				Game_Vairables::v2dImgBall_Velocity *= 0;
			}
			if (!Game_Vairables::bCompSilderLimit && !Reachedposition)
			{
				Game_Vairables::Computer_Silder.Set_Velocity(Game_Vairables::fSlider_SpeedMag, {0, -1});
				Game_Vairables::Computer_Silder.Update_Position(Game_Vairables::SecPassed.count());
			}
		}
		else
		{ // Acquire Position
			Reachedposition = true;
			PoitionGet = false;
			Game_Vairables::ImgBall.ParPos *= 0;
			Game_Vairables::v2dImgBall_Velocity *= 0;
		}

		Game_Vairables::Computer_Silder.Draw(wpScreen, {sScrW, sScrH}, Game_Vairables::ComputerSymbol);

		// Lower and Upper Boundaries Draw on Screen
		Game_Vairables::LowerBoundary.Draw(wpScreen, {sScrW, sScrH}, Game_Vairables::LowerBound_Symbol);
		Game_Vairables::UpperBoundary.Draw(wpScreen, {sScrW, sScrH}, Game_Vairables::UpperBound_Symbol);

		GameModule_Inialization(wpScreen);
		swprintf(&wpScreen[sScrW + 22], ScreenSize_InBytes, L" %i", PlayerScore);
		swprintf(&wpScreen[sScrW + 84], ScreenSize_InBytes, L"%i", ComputerScore);
		swprintf(&wpScreen[sScrW + 40], ScreenSize_InBytes, L"%i : %i ", Game_Vairables::GameTime.Get_Minutes(), Game_Vairables::GameTime.Get_Seconds());
		WriteConsoleOutputCharacterW(OutHandle, wpScreen, sScrW * sScrH, {0, 0}, &bytesWritten);

		Game_Vairables::EndTick = std::chrono::system_clock::now();
		Game_Vairables::Startit = true;
		Game_Vairables::SecPassed = Game_Vairables::EndTick - Game_Vairables::StartTick;

		Game_Vairables::bPlayerSilderLimit = false;
		Game_Vairables::bCompSilderLimit = false;

		Game_Vairables::Down.KeyPressed = false;
		Game_Vairables::Up.KeyPressed = false;
	}

	/*
	wpScreen[sScrW * Ball.ParPos.iY + Ball.ParPos.iX] = Ball_Symbol;
	Player_Silder.Draw(wpScreen, { sScrW,sScrH }, PlayerSymbol);
	Computer_Silder.Draw(wpScreen, { sScrW,sScrH }, ComputerSymbol);
	UpperBoundary.Draw(wpScreen, { sScrW,sScrH }, UpperBound_Symbol);
	LowerBoundary.Draw(wpScreen, { sScrW,sScrH }, LowerBound_Symbol);
	*/

	// delete[] wpScreen;
	return 0;
}

// Game Functions Definations

void GameModule_Inialization(wchar_t *Screen)
{
	swprintf(&Screen[sScrW + 1], ScreenSize_InBytes, L"Player's Score  : ");
	swprintf(&Screen[sScrW + 66], ScreenSize_InBytes, L"Computer's Score  : ");
	swprintf(&Screen[40], ScreenSize_InBytes, L"Time");

	for (int i = sScrW * 3; i < sScrW * 3 + sScrW; i++)
		Screen[i] = L'=';
}

void CollisionDetection(wchar_t *Screen, Physic::Neutral_Particles &Object, Vector2D &ObjectVelocity)
{

	switch (Screen[Object.ParPos.iX + Object.ParPos.iY * sScrW])
	{
	case Game_Vairables::UpperBound_Symbol:
	{
		ObjectVelocity = ObjectVelocity.ParallelogramAddition({0, 2.5});

		break;
	}

	case Game_Vairables::LowerBound_Symbol:
	{
		ObjectVelocity = ObjectVelocity.ParallelogramAddition({0, -2.0});

		break;
	}

	case Game_Vairables::PlayerSymbol:
	{
		if (!Game_Vairables::bPlayerSilderLimit && Game_Vairables::Up.KeyPressed)
		{
			ObjectVelocity = ObjectVelocity.ParallelogramAddition({3.0, -3.85});
		}
		else if (!Game_Vairables::bPlayerSilderLimit && Game_Vairables::Down.KeyPressed)
		{
			ObjectVelocity = ObjectVelocity.ParallelogramAddition({3.0, 3.85});
		}
		else
		{
			ObjectVelocity = ObjectVelocity.ParallelogramAddition({3.0, 0});
		}

		break;
		// else if (Object.iX == Game_Vairables::Player_Silder.ParPos.iX || Object.iX == Game_Vairables::Player_Silder.ParPos.iX - 1)
		//{
		//
		// }
	}

	case Game_Vairables::ComputerSymbol:
	{
		if (!Game_Vairables::bCompSilderLimit && false)
		{
			ObjectVelocity = ObjectVelocity.ParallelogramAddition({-3.0, 3.85});
		}
		else if (!Game_Vairables::bCompSilderLimit && false)
		{
			ObjectVelocity = ObjectVelocity.ParallelogramAddition({-3.0, -3.85});
		}
		else
		{
			ObjectVelocity = ObjectVelocity.ParallelogramAddition({-3.0, 0});
		}

		break;

		// else if (Object.iX == Game_Vairables::Computer_Silder.ParPos.iX || Object.iX == Game_Vairables::Computer_Silder.ParPos.iX + 1)
		//{
		//
		// }
	}
	default:
	{
		Object.Set_Velocity(Game_Vairables::fBallSpeedMag, ObjectVelocity);
		break;
	}
	}
}
