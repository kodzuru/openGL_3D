// Nehe_04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
float WinWid = 800.0;
float WinHei = 800.0;
unsigned int textures[3]; //массив количества текстур
int quads[2];
int xrot, yrot;
float boxcol[5][3] = { { 1.0f,0.0f,0.0f },
						{ 1.0f,0.5f,0.0f },
						{ 1.0f,1.0f,0.0f },
						{ 0.0f,1.0f,0.0f },
						{ 0.0f,1.0f,1.0f } };

float topcol[5][3] = { { .5f,0.0f,0.0f },
						{ 0.5f,0.25f,0.0f },
						{ 0.5f,0.5f,0.0f },
						{ 0.0f,0.5f,0.0f },
						{ 0.0f,0.5f,0.5f } };
#include "functions.h" // различные функции

int main(int argc, char** argv){
	srand(time(NULL));

	//инициализация
	glutInit(&argc, argv); // глобальная инициализация
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// инициализация мода дисплея(как рисуем)
	glutInitWindowSize(WinWid, WinHei); // инициализация размеров дисплея/окна
	glutInitWindowPosition(500, 100); // инициализация позиции окна
	glutCreateWindow("Super <openGL> balalaika"); //создание окна



	glutTimerFunc(33, Timer, 0); // регистрация функции анимации(функция таймера)
	glutSpecialFunc(SKeyboard);// регистрация функций клавиатуры 2 для особых клавиш
	//glutKeyboardFunc(Keyboard); // регистрация функций клавиатуры 1

	//регистрация
	glutDisplayFunc(Draw); //регистрация функции рисования
	Initialize(); //регистрация функции инициализация

	glutMainLoop(); //запуск главного цикла(стандартная функция GLUT)
	_getch();
    return 0;
}

