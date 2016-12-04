#pragma once

void LoadTextures();
void Initialize() {

	
	LoadTextures();
	glClearColor(0.0, 0.0, 0.0, 0.0);//каким цветом всё стереть | цвет очистки
	glMatrixMode(GL_PROJECTION);//тип матрицы который будет изменять в последующем GL_PROJECTION - матрица проекций
	glLoadIdentity(); //загружаем единичную матрицу
	//glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -WinHei / 2, WinHei / 2); //задаётся сетка координат(матрица проекции) относительно центра экрана
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //задаётся сетка координат(матрица проекции) относительно левого верхнего угла
	// Максимальное качество перспективной коррекции
	gluPerspective(45.0f, WinWid / WinHei, 0.1f, 100.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	/*
	Этот код просто означает, что мы хотим, чтобы полигоны нижней (задней) 
	стороны были зарисованы полностью и чтобы полигоны верхней (передней)
	стороны были лишь очерчены.
	*/
	glPolygonMode(GL_BACK, GL_FILL);       // нижняя (задняя) сторона заполнена
	glPolygonMode(GL_FRONT, GL_LINE);      // верхняя (передняя) сторона прорисована линиями


	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Функция смешивания для непрозрачности,
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины
	glEnable(GL_DEPTH_TEST);

	int x, y;
	float float_x, float_y, float_xb, float_yb;

	glEnable(GL_TEXTURE_2D);{
		glBindTexture(GL_TEXTURE_2D, textures[1]); // переключаемся на первую текстуру
		glPushMatrix();{
			glTranslatef(0.0, 0.0, z);
			glRotatef(xrot, 1.0, 0.0, 0.0);
			glRotatef(yrot, 0.0, 1.0, 0.0);
			glRotatef(zrot, 0.0, 0.0, 1.0);
			glBegin(GL_QUADS); {
				for (x = 0; x < 44; x++){
					for (y = 0; y < 44; y++){
						float_x = float(x) / 44.0f;
						float_y = float(y) / 44.0f;
						float_xb = float(x + 1) / 44.0f;
						float_yb = float(y + 1) / 44.0f;

						glTexCoord2f(float_x, float_y);
						glVertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);

						glTexCoord2f(float_x, float_yb);
						glVertex3f(points[x][y + 1][0], points[x][y + 1][1], points[x][y + 1][2]);

						glTexCoord2f(float_xb, float_yb);
						glVertex3f(points[x + 1][y + 1][0], points[x + 1][y + 1][1], points[x + 1][y + 1][2]);

						glTexCoord2f(float_xb, float_y);
						glVertex3f(points[x + 1][y][0], points[x + 1][y][1], points[x + 1][y][2]);
					}
				}
				
			}glEnd();
		}glPopMatrix();

	}glDisable(GL_TEXTURE_2D);

	if (wiggle_count == 2){
		for (y = 0; y < 45; y++){
			hold = points[0][y][2];
			for (x = 0; x < 44; x++){
				points[x][y][2] = points[x + 1][y][2];
			}
			points[44][y][2] = hold;
		}
		wiggle_count = 0;
	}
	wiggle_count++;


	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE
}
void Timer(int value)
{

	Draw();
	glutPostRedisplay(); //обновление всего экрана. того что нарисовали
	glutTimerFunc(33, Timer, 0); //обновления функции инициализации(функции таймера):типа рекурсия
}
void SKeyboard(int key, int x, int y)  //функция взаимодействия с клавиатурой 2 НЕ ASCII
{
	switch (key)
	{
	case GLUT_KEY_UP:
		xrot += 1;
		break;
	case GLUT_KEY_DOWN:
		xrot -= 1;
		break;
	case GLUT_KEY_RIGHT:
		yrot += 1;
		break;
	case GLUT_KEY_LEFT:
		yrot -= 1;
		break;
	case GLUT_KEY_PAGE_UP:
		zrot += 1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		zrot -= 1;
		break;
	}
}
void Keyboard(unsigned char key, int x, int y) //функция взаимодействия с клавиатурой 1 ASCII
{
	switch (key)
	{
	case 'w':
		z += 3;
		break;
	case 's':
		z -= 3;
		break;
	}
}

void LoadTextures() {


	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Tim.bmp"); //загружаем текстуру в RGB

	glGenTextures(3, &textures[0]); //загружаем текстуру n - размер массива текстур, указатель на массив текстур


									// Создание текстуры с фильтром по соседним пикселям
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // ( НОВОЕ )
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ( НОВОЕ )
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	// Создание текстуры с линейной фильтрацией
	glBindTexture(GL_TEXTURE_2D, textures[1]); //выбираем текстуру с которой будем работать и помещаем её в массив текстур
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// задаём параметры текстуре (параметры приобразования больше-меньше)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// задаём параметры текстуре (параметры приобразования больше-меньше)
																	 //1- тип текстуры, 2- , 3- количество цветов, 4- размер по Х, 5 - размер по У, 6 - нарисованая граница, 7 - формат цветов,
																	 // 8 - тип которым представляется текстура, 9 - сама текстура
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);


	// Создание Текстуры с Мип-Наложением
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture1->sizeX, texture1->sizeY,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);


	if (texture1) { // Если текстура существует
		if (texture1->data) {    // Если изображение текстуры существует
			delete[] texture1->data; // Освобождение памяти изображения текстуры
		}
		delete[] texture1;        // Освобождение памяти под структуру
	}
}