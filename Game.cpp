	#pragma once
	#include "Game.h"
	#include <iostream>
	#include <vector>
	#include <conio.h>
	#include <windows.h>
	#include <ranges>

	SnakeGame::SnakeGame(){
		gameOver = false;
		snake.push_back({ WIDTH / 2, HEIGHT / 2 });
		fruit.first = rand() % WIDTH;
		fruit.second = rand() % HEIGHT;
		score = 0;
		dir = STOP;
	}

	void SnakeGame::Draw() {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		// 上边界
		for (int i = 0; i < WIDTH + 2; i++) {
			std::cout << "#";
		}
		std::cout << std::endl;

		// 中间区域
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == 0) std::cout << "#"; // 左边界

				if (i == snake[0].second && j == snake[0].first) std::cout << "@"; // 蛇头
				else if (i == fruit.second && j == fruit.first) std::cout << "$"; // 水果
				else {
					bool isBody = false;
					for (const auto& pos : snake | std::views::drop(1)) {
						if (i == pos.second && j == pos.first ) {
							std::cout << "o";
							isBody = true;
							break;
						}
					}
					if (!isBody) std::cout << " ";
				}
				if (j == WIDTH - 1) std::cout << "#"; // 右边界
			}
			std::cout << std::endl;
		}
		// 下边界
		for (int i = 0; i < WIDTH + 2; i++) {
			std::cout << "#";
		}
		std::cout << std::endl;
		std::cout << "Score: " << score << "  Length: " << snake.size() << std::endl;
		std::cout << "Use W/A/S/D to move" << std::endl;
	}

	void SnakeGame::input() {
		if (_kbhit()) {
			switch (_getch()) {
			case 'a':if(dir != RIGHT) dir = LEFT; break;
			case 'd':if(dir != LEFT) dir = RIGHT; break;
			case 'w':if(dir != DOWN) dir = UP; break;
			case 's':if(dir != UP) dir = DOWN; break;
			case 'x': gameOver = true; break;
			}
		}
	}

	void SnakeGame::Logic() {
		if (dir == STOP) return;

		int newX = snake[0].first;
		int newY = snake[0].second;

		switch (dir) {
		case LEFT: newX--; break;
		case RIGHT: newX++; break;
		case UP: newY--; break;
		case DOWN: newY++; break;
		default: break;
		}

		// 出界判定
		if (newX >= WIDTH || newY >= HEIGHT || newX < 0 || newY < 0) {
			gameOver = true;
		}

		// 撞到尾巴
		for (const auto& pos : snake) {
			if (pos.first == newX && pos.second == newY) {
				gameOver = true;
				return;
			}
		}
		// 更新头部
		snake.insert(snake.begin(), { newX, newY });
		// 吃水果
		if (newX == fruit.first && newY == fruit.second) {
			score += 10;
			fruit.first = rand() % WIDTH;
			fruit.second = rand() % HEIGHT;
		}
		else {
			snake.pop_back();
		}
	}

	void SnakeGame::run() {
		system("cls");
		while (!gameOver) {
			Draw();
			input();
			Logic();
			Sleep(100);
		}
	}