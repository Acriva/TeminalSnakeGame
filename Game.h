#pragma once
#include <vector>

// 定义地图长宽
const int WIDTH = 20;
const int HEIGHT = 20;


class SnakeGame {
private:
	bool gameOver;
	std::vector<std::pair<int, int>> snake; // 蛇坐标
	std::pair<int, int> fruit; // 水果坐标
	int score;

	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;


public:
	SnakeGame();
	void Draw();
	void input();
	void Logic();
	void run();
};

