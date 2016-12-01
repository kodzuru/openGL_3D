#pragma once
void AXIS_LIST_INIT();
void LoadTextures();
void Initialize() {

	LoadTextures();

	glClearColor(0.0, 0.0, 0.0, 0.0);//каким цветом всё стереть | цвет очистки
	glMatrixMode(GL_PROJECTION);//тип матрицы который будет изменять в последующем GL_PROJECTION - матрица проекций
	glLoadIdentity(); //загружаем единичную матрицу
	//glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -WinHei / 2, WinHei / 2); //задаётся сетка координат(матрица проекции) относительно центра экрана
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //задаётся сетка координат(матрица проекции) относительно левого верхнего угла
	// Максимальное качество перспективной коррекции
	gluPerspective(45.0f, WinWid / WinHei , 0.1f, 100.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Функция смешивания для непрозрачности,



	//glEnable(GL_LIGHTING);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glEnable(GL_NORMALIZE); //делам нормали одинаковой величины во избежание артефактов
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();			// Reset The Modelview Matrix

	// Включаем плавную ракраску (интерполирование по вершинам)
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);   // Фоном будет черный цвет
	glClearDepth(1.0f);                     // Установки буфера глубины (Depth Buffer)


	
	AXIS_LIST_INIT();


}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины

	if (blend) {
		glEnable(GL_BLEND); // ВАЖНО НЕ ВЫКЛЮЧАТЬ СМЕШИВАНИЕ
	}
	//glEnable(GL_DEPTH_TEST); //включаем глубину
	glEnable(GL_TEXTURE_2D);	
	//if (light) {
		//glEnable(GL_LIGHT0);
	//}
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	//glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	// Position The Light
	//glNormal3f(0.0, 0.0, 5.0); // указываем направление лампы нормалей (это обязательно)

	glEnable(GL_TEXTURE_2D); //разрешение накладывать текстуру
	glBindTexture(GL_TEXTURE_2D, textures[0]); // переключаемся на первую текстуру
	for (loop = 0; loop<num; loop++)						// Loop Through All The Stars
	{
		glLoadIdentity();								// Reset The View Before We Draw Each Star
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, zoom);					// Zoom Into The Screen (Using The Value In 'zoom')
		glRotatef(tilt, 1.0f, 0.0f, 0.0f);					// Tilt The View (Using The Value In 'tilt')
		glRotatef(star[loop].angle, 0.0f, 1.0f, 0.0f);		// Rotate To The Current Stars Angle
		glTranslatef(star[loop].dist, 0.0f, 0.0f);		// Move Forward On The X Plane
		glRotatef(-star[loop].angle, 0.0f, 1.0f, 0.0f);	// Cancel The Current Stars Angle
		glRotatef(-tilt, 1.0f, 0.0f, 0.0f);				// Cancel The Screen Tilt

		if (twinkle)
		{
			glColor4ub(star[(num - loop) - 1].r, star[(num - loop) - 1].g, star[(num - loop) - 1].b, 150);
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			}glEnd();
		}

		glRotatef(spin, 0.0f, 0.0f, 1.0f);
		glColor4ub(star[loop].r, star[loop].g, star[loop].b, 150);
		glBegin(GL_QUADS); {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		}glEnd();

		spin += 0.01f;
		star[loop].angle += float(loop) / num;
		star[loop].dist -= 0.01f;
		if (star[loop].dist<0.0)
		{
			star[loop].dist += 5.0f;
			star[loop].r = rand() % 256;
			star[loop].g = rand() % 256;
			star[loop].b = rand() % 256;
		}
		glPopMatrix();

	}
	glDisable(GL_TEXTURE_2D);


	// рисуем кубик
	/*
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
		for (int i(90); i < 360; i += 180) {
			glPushMatrix(); {
				glRotatef(i, 1.0, 0.0, 0.0);
				glCallList(axis[1]); // вызываем нужный нам список по ID	
			}glPopMatrix();
		}
	}glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	*/

	//glDisable(GL_BLEND);
	//glDisable(GL_LIGHT0);
	//glDisable(GL_DEPTH_TEST); // выключаем глубину
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
		//light = true;
		twinkle = false;
		break;
	case 'k':
		light = false;
		break;
	case 'b':
		if (blend)
			blend = false;
		else
			blend = true;
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


	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Star.bmp"); //загружаем текстуру в RGB

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


	if (texture1) { // Если текстура существует
		if (texture1->data) {    // Если изображение текстуры существует
			delete[] texture1->data; // Освобождение памяти изображения текстуры
		}
		delete[] texture1;        // Освобождение памяти под структуру
	}
}