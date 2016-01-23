#pragma once
#include <SDL/SDL.h>
#include <cmath>
#include "Block.h"
#include "GridClass.h"

//rotation direction
#define counterClockwise -1
#define clockwise 1

enum reason {
	falling,
	moving,
	spawning,
	rotating
};

struct WallKickData
{
	WallKickData(int (&_clockwiseData)[4][5][2], int (&_counterClockwiseData)[4][5][2]);
	WallKickData();
	const static unsigned int states = 4;
	const static unsigned int tests = 5;
	const static unsigned int positions = 2;
	int (*clockwiseData)[states][tests][positions];
	int (*counterClockwiseData)[states][tests][positions];
};

//here is a list of tetrominos I, J, L, O, S, T, Z
class Tetromino
{
public:
	Tetromino(int h, int w, int(&shape)[4][4][4], int _color, WallKickData &_WallKickData);
	Tetromino();
	~Tetromino();

	//places the arrary being pasted into _shape
	//void defineShape(int(&shape)[4][4][4]);
	//this will draw the tetromino
	virtual void draw(SDL_Renderer* renderer);
	void drawShape(SDL_Renderer* renderer);
	void fall(GridClass* grid);
	void move(GridClass* grid, int velocity);
	void rotate(GridClass* grid, int direction);
	void hardDrop(GridClass * grid, Tetromino *Hint);	//pieces drop instantly but not lock
	void changeFallSpeed(int fallSpeed);
	bool detectCollision(GridClass* grid, reason theReason);	//this detects if the tetromino is inside one another
	int returnRotation() { return rotation; }
	int returnColor() { return color; }
	int returnShapeSize() { return shapeSize; }
	//void changeVelocity(unsigned int index, int value);
	bool returnIsLocked();
	bool returnHasLanded();
	void land(GridClass* grid, Uint32 timeToLock, Uint32 currentTime);
	int y = 3;
	int x = 3;
	int(*shape)[4][4][4];		//please don't ever change this value while in-game
private:
	bool wallKick(GridClass * grid, int direction);
	//places the tetromino onto the grid
	void lock(GridClass* grid);
	int _h;
	int _w;
	int gridx;
	int gridy;
	int color;
	//int blockSize;
	int _fallSpeed;		//changes when to fall
	bool isLocked = false;
	bool hasLanded = false;
	WallKickData *WallKick_Data;
	bool canFloorKick;
protected:
	int shapeSize;
	int rotation;
	int velocity[2];
};

class GhostTetromino :
	public Tetromino
{
public:
	GhostTetromino();
	~GhostTetromino();
	virtual void draw(Tetromino T, SDL_Renderer * renderer);
	void update(GridClass* grid, Tetromino T);
};