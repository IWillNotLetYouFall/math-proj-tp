#include <iostream>
#include <stdlib.h>
#include <string>
#include "Vector3D.h"
#include "Particule.h"
#include "Laser.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <math.h>
#include <vector>
#include <cstdlib>
#include "PhysicWorld.h"
#include "SpringParticles.h"
#include "ParticleRod.h"
#include "ParticleGravity.h"
#include "SpringBungee.h"
#include "SpringFixed.h"
#include "SpringParticles.h"
//using namespace sf;
//using namespace std;


#include "olcConsoleGameEngine.h"
using namespace std;

struct triangle
{
	Vector3D p[3];

	wchar_t sym;
	short color;
};

struct mesh
{
	vector<triangle> tris;

	void newCube() {
		tris = {
			// SUD
			{ Vector3D(0,0,0), Vector3D(0,1,0), Vector3D(1,1,0) },
			{ Vector3D(0,0,0), Vector3D(1,1,0), Vector3D(1,0,0) },

			// EST
			{ Vector3D(1,0,0), Vector3D(1,1,0), Vector3D(1,1,1) },
			{ Vector3D(1,0,0), Vector3D(1,1,1), Vector3D(1,0,1) },

			// NORD
			{ Vector3D(1,0,1), Vector3D(1,1,1), Vector3D(0,1,1) },
			{ Vector3D(1,0,1), Vector3D(0,1,1), Vector3D(0,0,1) },

			// OUEST
			{ Vector3D(0,0,1), Vector3D(0,1,1), Vector3D(0,1,0) },
			{ Vector3D(0,0,1), Vector3D(0,1,0), Vector3D(0,0,0) },

			// TOP
			{ Vector3D(0,1,0), Vector3D(0,1,1), Vector3D(1,1,1) },
			{ Vector3D(0,1,0), Vector3D(1,1,1), Vector3D(1,1,0) },

			// BAS
			{ Vector3D(1,0,1), Vector3D(0,0,1), Vector3D(0,0,0) },
			{ Vector3D(1,0,1), Vector3D(0,0,0), Vector3D(1,0,0) },

		};
	}
};

struct mat4x4
{
	float m[4][4] = { 0 };
};

class olcEngine3D : public olcConsoleGameEngine
{
public:
	olcEngine3D()
	{
		m_sAppName = L"TP3 Math";
	}


private:
	mesh meshCube;

	mat4x4 matProj;

	Vector3D posCamera;

	float fTheta;
	float distFov = 3.f;

	void MultiplyMatrixVector(Vector3D& i, Vector3D& o, mat4x4& m)
	{
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
	}

public:
	bool OnUserCreate() override
	{
		meshCube.newCube(); //Generate Cube

		// Projection Matrix
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		float sWidth = ScreenWidth();
		float sHeight = ScreenHeight();
		//Register Keys
		if (GetKey(L'Q').bHeld) //Mouv Haut
			distFov += 8.f * fElapsedTime;
		if (GetKey(L'E').bHeld) //Mouv Bas
			distFov -= 8.0f * fElapsedTime;

		// Clear Screen
		Fill(0, 0, sWidth, sHeight, PIXEL_SOLID, FG_BLACK);

		// Set up rotation matrices
		fTheta += 1.0f * fElapsedTime;

		// Rotation Z
		mat4x4 matRotZ = getRotationZ(fTheta);
		// Rotation X
		mat4x4 matRotX = getRotationX(fTheta);

		// Draw Triangles
		for (auto tri : meshCube.tris)
			DrawTri(tri, matRotX, matRotZ);

		return true;
	}
	void DrawTri(triangle tri, mat4x4 matRotX, mat4x4 matRotZ) {
		float sWidth = ScreenWidth();
		float sHeight = ScreenHeight();

		triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

		for (int i = 0; i < 3; i++)
		{
			MultiplyMatrixVector(tri.p[i], triRotatedZ.p[i], matRotZ); 	// Rotate in Z-Axis

			MultiplyMatrixVector(triRotatedZ.p[i], triRotatedZX.p[i], matRotX); // Rotate in X-Axis

			triTranslated.p[i] = triRotatedZX.p[i];
			triTranslated.p[i].z = triRotatedZX.p[i].z + distFov; 	// Offset into the screen
		}

		Vector3D line1 = triTranslated.p[1] - triTranslated.p[0];
		Vector3D line2 = triTranslated.p[2] - triTranslated.p[0];
		Vector3D normal = (line1.VectorialProduct(line2).Normalize());

		Vector3D angleCam = triTranslated.p[0] - posCamera;
		if (normal.ScalarProduct(angleCam) < 0) {
			Vector3D light_direction = { 0.0f, 0.0f, -1.0f };
			float dp = light_direction.ScalarProduct(normal);

			//Set Colour
			CHAR_INFO c = GetColour(dp);
			triTranslated.color = c.Attributes;
			triTranslated.sym = c.Char.UnicodeChar;

			for (int i = 0; i < 3; i++)
			{
				MultiplyMatrixVector(triTranslated.p[i], triProjected.p[i], matProj); // Project triangles from 3D --> 2D
				triTranslated.color = c.Attributes;
				triTranslated.sym = c.Char.UnicodeChar;

				triProjected.p[i] += Vector3D(1, 1); // Scaling pour affichage
				triProjected.p[i].Product(Vector3D(0.5f * sWidth, 0.5f * sHeight, 1.f)); // Scaling et placement pour affichage
			}

			triProjected.color = triTranslated.color;
			triProjected.sym = triTranslated.sym;

			// Affichage rasterisee triangle
			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				triProjected.sym, triProjected.color);
		}
	}

	mat4x4 getRotationX(float fTheta) {
		mat4x4 matRotX;
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;
		return matRotX;
	}

	mat4x4 getRotationY(float fAngleRad) {
		mat4x4 matRotZ;
		matRotZ.m[0][0] = cosf(fAngleRad);
		matRotZ.m[0][1] = sinf(fAngleRad);
		matRotZ.m[1][0] = -sinf(fAngleRad);
		matRotZ.m[1][1] = 1;
		matRotZ.m[2][2] = cosf(fAngleRad);
		matRotZ.m[3][3] = 1;
		return matRotZ;
	}

	mat4x4 getRotationZ(float fTheta) {
		mat4x4 matRotZ;
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;
		return matRotZ;
	}

	// Taken From Command Line Webcam Video
	CHAR_INFO GetColour(float lum)
	{
		short bg_col, fg_col;
		wchar_t sym;
		int pixel_bw = (int)(13.0f * lum);
		switch (pixel_bw)
		{
		case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

		case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
		case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
		case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
		case 4: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

		case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
		case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
		case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
		case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;

		case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
		case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
		case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
		case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
		default:
			bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID;
		}

		CHAR_INFO c;
		c.Attributes = bg_col | fg_col;
		c.Char.UnicodeChar = sym;
		return c;
	}
};

int oldmain()
{
	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 4, 4))
		demo.Start();
	return 0;
}