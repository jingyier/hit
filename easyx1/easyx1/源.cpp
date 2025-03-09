#include<stdio.h>
#include<easyx.h>
#include<conio.h>
#include<time.h>
#define NodeWidth 40
typedef struct {
	int x;
	int y;
}Node;

void paintGrid() {
	for (int y = 0; y <= 600; y += NodeWidth) {
		line(0, y, 800, y);
	}
	for (int x = 0; x <= 800; x += NodeWidth) {
		line(x, 0, x, 600);
	}
}

void paintSnake(Node* snake, int n) {
	int left, top, right, bottom;
	for (int i = 0; i < n; i++) {
		left = snake[i].x * NodeWidth;
		top = snake[i].y * NodeWidth;
		right = (snake[i].x + 1) * NodeWidth;
		bottom = (snake[i].y + 1)* NodeWidth;
		solidrectangle(left, top, right, bottom);
	}
}

enum direction {
	eUp,
	eDown,
	eLeft,
	eRight
};

void changeDirection(enum direction* pD) {
	if (_kbhit() != 0) {
		char c = _getch();
		switch (c)//蛇头不可以向相反方向或者正在移动的方向移动，这里要进行判断
		{
		case 1:
			if (*pD != eDown)
				*pD = eUp;
			break;
		case 2:
			if (*pD != eUp)
				*pD = eDown;
			break;
		case 3:
			if (*pD != eRight)
				*pD = eLeft;
			break;
		case 4:
			if (*pD != eLeft)
				*pD = eRight;
			break;
		}
	}
}

Node snakeMove(Node* snake, int length, int direction) {
	Node tail = snake[length - 1];
	for (int i = length - 1; i > 0; i--) {
		snake[i] = snake[i - 1];
	}
	Node NewHead;
	NewHead = snake[0];
	if (direction == eUp) {
		NewHead.y--;
	}
	else if (direction == eDown) {
		NewHead.y++;
	}
	else if (direction == eLeft) {
		NewHead.x--;
	}
	else if (direction == eRight) {
		NewHead.x++;
	}
	snake[0] = NewHead;
	return tail;
}

Node createFood(Node* snake, int length) {
	Node food;

	while (1) {
		food.x = rand() % (800 / NodeWidth);
		food.y = rand() % (600 / NodeWidth);
		int i;
		for (i = 0; i < length; i++) {
			if ((food.x == snake[i].x) && (food.y == snake[i].y)) {
				break;
			}
		}
		if (i < length) {
			continue;
		}
		else
			break;
	}
	return food;
}

void paintFood(Node food) {
	int left, right, top, bottom;
	left = food.x * NodeWidth;
	top = food.y * NodeWidth;
	right = (food.x + 1) * NodeWidth;
	bottom = (food.y + 1) * NodeWidth;
	setfillcolor(YELLOW);
	solidrectangle(left, top, right, bottom);
	setfillcolor(WHITE);
}

bool IsGameOver(Node* snake, int length) {
	if (snake[0].x<0 || snake[0].x>(800 / NodeWidth))
		return true;
	if (snake[0].x<0 || snake[0].x>(800 / NodeWidth))
		return true;
	for (int i = 1; i < length; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return true;
	}
	return false;
}

void reset(Node* snake, int* length, enum direction* d) {
	snake[0] = Node{ 5,7 };
	snake[1] = Node{ 4,7 };
	snake[2] = Node{ 3,7 };
	snake[3] = Node{ 2,7 };
	snake[4] = Node{ 1,7 };
	*length = 5;
	*d = eRight;
}

int main() {               //创建一个窗口
	initgraph(800, 600);
	setbkcolor(RGB(166, 220, 222));
	cleardevice();
	paintGrid();

	Node snake[100] = { {5,7},{4,7}, {3,7},{2,7},{1,7}};
	int length = 5;
	enum direction d = eRight;
	srand(unsigned int(time(NULL)));
	Node food = createFood(snake, length);

	while (1)
	{
		cleardevice();
		paintGrid();
		paintSnake(snake, length);
		paintFood(food);
		Sleep(500);
		changeDirection(&d);
		Node lastTail = snakeMove(snake, length, d);
		if (snake[0].x == food.x && snake[0].y == food.y)
		{
			if (length < 100) {
				snake[length] = lastTail;
				length++;
			}
			food = createFood(snake, length);
		}
		if (IsGameOver(snake, length) == true) {
			reset(snake, &length, &d);
			food = createFood(snake, length);
		}
	}
	closegraph();
	return 0;
}