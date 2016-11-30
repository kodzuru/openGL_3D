#pragma once
void AXIS_LIST_INIT();
void LoadTextures();
void Initialize() {

	LoadTextures();

	glClearColor(0.0, 0.0, 0.0, 0.0);//каким цветом всё стереть | цвет очистки
	glMatrixMode(GL_PROJECTION);//тип матрицы который будет изменять в последующем GL_PROJECTION - матрица проекций
	glLoadIdentity(); //загружаем единичную матрицу
	glOrtho(-WinWid/2, WinWid/2, -WinHei /2, WinHei/2, -WinHei/2, WinHei/2); //задаётся сетка координат(матрица проекции) относительно центра экрана
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //задаётся сетка координат(матрица проекции) относительно левого верхнего угла
	
	
	
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE); //делам нормали одинаковой величины во избежание артефактов
	glMatrixMode(GL_MODELVIEW);





	AXIS_LIST_INIT();
	

}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины
	
	if (blend) {
		glEnable(GL_BLEND);
	}	
	glEnable(GL_DEPTH_TEST); //включаем глубину

	// рисуем пирамидку
	/*
	glPushMatrix();
	glTranslatef(-100.0, 0.0, 0.0);
	glRotatef(rot, 1.0, 1.0, 0.0);
	for (int i(0); i < 4; i++) {
		glPushMatrix(); {
			glRotatef(i*90, 0.0, 1.0, 0.0);
			glCallList(axis[0]); // вызываем нужный нам список по ID	
		}glPopMatrix();
	}
	glPushMatrix(); {
		glBegin(GL_QUADS); {
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-50.0, -50.0, 50.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(-50.0, -50.0, -50.0);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(50.0, -50.0, -50.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(50.0, -50.0, 50.0);
		}glEnd();
	}glPopMatrix();
	glPopMatrix();
	*/

	// рисуем кубик
	glEnable(GL_TEXTURE_2D); //разрешение накладывать текстуру
	//включаем освещение(лампа_0)
	if (light) {
		glEnable(GL_LIGHT0);
	}	
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	// Position The Light
	glNormal3f(100.0, -50.0, 50.0); // указываем направление лампы нормалей (это обязательно)

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);   // Полная яркость, 50% альфа 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Функция смешивания для непрозрачности,
									   // базирующаяся на значении альфы
	
	glPushMatrix(); {
		glTranslatef(0.0, 0.0, dz);
		glScalef(3, 3, 3);		
		//glRotatef(rot, 1.0, 1.0, 0.0);
		glRotatef(rot_x, 1.0, 0.0, 0.0);
		glRotatef(rot_y, 0.0, 1.0, 0.0);
		for (int i(0); i < 4; i++) {
			glPushMatrix(); {
				glRotatef(i * 90, 0.0, 1.0, 0.0);
				glCallList(axis[1]); // вызываем нужный нам список по ID	
			}glPopMatrix();
		}
		for (int i(90); i < 360; i+=180) {
			glPushMatrix(); {
				glRotatef(i, 1.0, 0.0, 0.0);
				glCallList(axis[1]); // вызываем нужный нам список по ID	
			}glPopMatrix();
		}
	}glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST); // выключаем глубину
	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE

}


void Timer(int value)
{
	rot_x += dx;
	rot_y += dy;
	Draw();
	glutPostRedisplay(); //обновление всего экрана. того что нарисовали
	glutTimerFunc(33, Timer, 0); //обновления функции инициализации(функции таймера):типа рекурсия
}
void Keyboard(unsigned char key, int x, int y) //функция взаимодействия с клавиатурой 1 ASCII
{
	switch (key)
	{
	case 'w':
		dz += 20;
		break;
	case 's':
		dz -= 20;
		break;
	case 'l':
		light = true;
		break;
	case 'k':
		light = false;
		break;
	case 'b':
		blend = !blend;
		std::cout << 1;
		break;
	}
}
void SKeyboard(int key, int x, int y)  //функция взаимодействия с клавиатурой 2 НЕ ASCII
{
	switch (key)
	{
	case GLUT_KEY_UP:
		dx -= 1;
		break;
	case GLUT_KEY_DOWN:
		dx += 1;
		break;
	case GLUT_KEY_LEFT:
		dy -= 1;
		break;
	case GLUT_KEY_RIGHT:
		dy += 1;
		break;
	}
}

void AXIS_LIST_INIT()
{
	axis[0] = glGenLists(2); // ренерируем два новых список
	if (axis[0] == 0) {
		std::cout << "Error : AXIS_LIST_INIT" << std::endl;
		return;// генерация провалилась выходим
	}
	axis[1] = axis[0] + 1;


	glNewList(axis[0], GL_COMPILE); { //начинаем формировать список GL_COMPILE - будет ли список только сформирован
	 // или сразу отображён - GL_COMPILE_AND_EXECUTE

		glBegin(GL_TRIANGLES); {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 50.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(-50.0, -50.0, 50.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(50.0, -50.0, 50.0);
		}glEnd();

	}glEndList(); // завершаем создание списка


	glNewList(axis[1], GL_COMPILE); { //начинаем формировать список GL_COMPILE - будет ли список только сформирован
	// или сразу отображён - GL_COMPILE_AND_EXECUTE	
			glBindTexture(GL_TEXTURE_2D, textures[2]); // переключаемся на первую текстуру
			glBegin(GL_QUADS); {
			//glColor3f(1.0, 1.0, 1.0);
			glTexCoord2f(0.0, 0.0);		glVertex3f(-50.0, -50.0, 50.0);
			//glColor3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(-50.0, 50.0, 50.0);
			//glColor3f(1.0, 0.0, 1.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(50.0, 50.0, 50.0);
			//glColor3f(1.0, 0.0, 0.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f(50.0, -50.0, 50.0);
		}glEnd();
	}glEndList(); // завершаем создание списка

}

void LoadTextures() {

	
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Glass.bmp"); //загружаем текстуру в RGB

	glGenTextures(3, &textures[0]); //загружаем текстуру n - размер массива текстур, указатель на массив текстур
	// загрузка первой текстуры

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


	if (texture1){ // Если текстура существует
		if (texture1->data)	{    // Если изображение текстуры существует
			delete[] texture1->data; // Освобождение памяти изображения текстуры
		}
		delete[] texture1;        // Освобождение памяти под структуру
	}
}