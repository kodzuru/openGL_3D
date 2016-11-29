// NEHE_00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <glut.h>
#include <GLAux.h>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <cstdlib>



float WinWid = 800.0;
float WinHei = 800.0;
int rot = 0;
int axis[2];
#include "functions.h" // различные функции


using namespace std;
int main(int argc, char** argv) {

	//инициализация
	glutInit(&argc, argv); // глобальная инициализация
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// инициализация мода дисплея(как рисуем)
	glutInitWindowSize(WinWid, WinHei); // инициализация размеров дисплея/окна
	glutInitWindowPosition(500, 100); // инициализация позиции окна
	glutCreateWindow("Super <openGL> balalaika"); //создание окна


	glutTimerFunc(33, Timer, 0); // регистрация функции анимации(функция таймера)
	glutSpecialFunc(SKeyboard);// регистрация функций клавиатуры 2 для особых клавиш

	//регистрация
	glutDisplayFunc(Draw); //регистрация функции рисования
	Initialize(); //регистрация функции инициализация

	glutMainLoop(); //запуск главного цикла(стандартная функция GLUT)
	_getch();
	return 1;
}

