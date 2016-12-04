// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

float WinWid = 400.0;
float WinHei = 400.0;
unsigned int textures[3];
float z = -20.0;

float points[45][45][3]; // массив точек сетки нашей "волны"
int wiggle_count = 0;        // счетчик для контроля быстроты развевания флага 
float hold = 0.0;                // временно содержит число с плавающей запятой
float	xrot = 45.0;				// X Rotation ( NEW )
float	yrot = 45.0;				// Y Rotation ( NEW )
float	zrot;				// Z Rotation ( NEW )

#include "functions.h" // различные функции

int main(int argc, char** argv) {


	//инициализация сетки
	for (int x = 0; x < 45; x++) // пройдемся по плоскости X
	{

		for (int y = 0; y < 45; y++) // пройдемся по плоскости Y
		{
			// применим волну к нашей сетке
			points[x][y][0] = float((x / 5.0f) - 4.5f);
			points[x][y][1] = float((y / 5.0f) - 4.5f);
			points[x][y][2] = float(sin((((x / 5.0f)*40.0f) / 360.0f)*3.141592654*2.0f));
		}
	}


	//инициализация
	glutInit(&argc, argv); // глобальная инициализация
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// инициализация мода дисплея(как рисуем)
	glutInitWindowSize(WinWid, WinHei); // инициализация размеров дисплея/окна
	glutInitWindowPosition(500, 100); // инициализация позиции окна
	glutCreateWindow("Super <openGL> balalaika"); //создание окна



	glutTimerFunc(33, Timer, 0); // регистрация функции анимации(функция таймера)
	glutSpecialFunc(SKeyboard);// регистрация функций клавиатуры 2 для особых клавиш
	glutKeyboardFunc(Keyboard); // регистрация функций клавиатуры 1

							   //регистрация
	glutDisplayFunc(Draw); //регистрация функции рисования
	Initialize(); //регистрация функции инициализация
	glutMainLoop(); //запуск главного цикла(стандартная функция GLUT)


	_getch();
	return 0;
}

