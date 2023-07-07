#pragma once
#include "Entity.h"

class State // класс состояний
{
private:

protected:
	RenderWindow* window; // окно
	map <string, Texture> textures; // текстуры
	stack<State*>* states; // указатель на стек состояний

	bool isEnd; // флаг окончание состояния
	bool paused;

	Vector2i mousePosScreen; // абсолютная позиция мыши
	Vector2f mousePosView; // позиция мыши относительно камеры
public:
	//конструктор / деструктор
	State(RenderWindow* window, stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const; // проверка об окончании состояния

	void endState(); // закончить состояние
	void pauseState();
	void unpauseState();
	//обновление
	virtual void updateMousePosition(); 
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	//рендер
	virtual void render(RenderTarget* target = nullptr) = 0;
};