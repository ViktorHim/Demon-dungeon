#pragma once
#include "Entity.h"

class State // ����� ���������
{
private:

protected:
	RenderWindow* window; // ����
	map <string, Texture> textures; // ��������
	stack<State*>* states; // ��������� �� ���� ���������

	bool isEnd; // ���� ��������� ���������
	bool paused;

	Vector2i mousePosScreen; // ���������� ������� ����
	Vector2f mousePosView; // ������� ���� ������������ ������
public:
	//����������� / ����������
	State(RenderWindow* window, stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const; // �������� �� ��������� ���������

	void endState(); // ��������� ���������
	void pauseState();
	void unpauseState();
	//����������
	virtual void updateMousePosition(); 
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	//������
	virtual void render(RenderTarget* target = nullptr) = 0;
};