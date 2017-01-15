/*
*	Автор: Яковенко Виталий Владимирович
*	Новосибирск 2017
*	Факультет Автоматики и Вычислительной Техники Новосибирского Государственного Университета
*	Группа: АВТ-615
*	Задание: «Салют». Движущиеся шарики, увеличивающиеся в размере. Шарики «лопаются»,
*				создавая множество мелких, разлетающихся в разные стороны и исчезающих.
*	Замеченные недоработки: При разворачивании окна на весь экран и сворачивании обратно
*								программа аварийно завершает работу или зависает.
*							При изменении размеров окна программа аварийно завершает работу
*								или зависает.
*
*/


#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <list>

using namespace std;

GLint width = 800, height = 400;
long time0 = 0;
long time_fps = 0;
short iter = 0; // количество пересчетов
short count_of_dec = 0; // количество шаров на сцене
short delay = 5; // минимальная задержка по времени между пересчетами

struct decagon
{
	double velocity_x = 0;
	double velocity_y = 0;
	double acceleration_x = 0;
	double acceleration_y = -72;
	float x;
	float y;
	float r;
	char increasing = 1;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
list<decagon> lt; // основной список шаров


void drawCircle(float x, float y, float r, int amountSegments, unsigned char red, unsigned char green, unsigned char blue);
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (list<decagon>::iterator i = lt.begin(); i != lt.end(); i++)
	{
		if (i->r > 0)
			drawCircle(i->x, i->y, i->r, 10, i->red, i->green, i->blue);
	}
	glFlush();
}

void Initialize(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}
void drawCircle(float x, float y, float r, int amountSegments, unsigned char red, unsigned char green, unsigned char blue) // функция рисования многоугольников
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f((float) red / 255, (float) green / 255, (float) blue / 255);

	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}
	
	glEnd();
}

bool alteration()
{
	bool result = false;
	long time = clock();
	int temp;
	bool flag = false;
	for (list<decagon>::iterator i = lt.begin(); i != lt.end(); i++)
	{
		/*TODO: исправить баг с удалением объектов, добавить удаление объектов.*/
		/*UPD: баг неисправим, нужны более продуманные методы, отчистка добавлена в ежесекундное условие*/
		if (flag) 
		{
			i--;
			flag = false;
		}
		
		if ((i->x >= width + i->r) || (i->y >= height + i->r)) // пропуск элементов, ушедших за экран
		{
			continue;
		}
		if ((i->x <= 0 - i->r) || (i->y <= 0 - i->r))
		{
			continue;
		}

		if (i->increasing == 1 && i->r < 20) // увеличение радиуса шаров
		{
			i->r = 70 / i->velocity_y * 20; //вычисление радиуса с помощью пропорции
		}
		else if (i->increasing == -1) // уменьшение радиуса шаров для эффекта исчезновения
		{
			if (i->velocity_y < -200) // чтобы исчисления не производились дальше. здесь можно
				;					  // поставить значение поменьше, но я не стал трогать
			else if (i->velocity_y > 0) // когда шар летит вверх
				i->r = 3 + i->velocity_y / 90;
			else if (i->velocity_y < 0) // когда шар летит вниз
				i->r = 3 + i->velocity_y / 30;
		}
		if (i->acceleration_x != 0) // вычисление изменившейся скорости
		{
			i->velocity_x += i->acceleration_x*(time - time0) / 1000;
		}
		if (i->acceleration_y != 0)
		{
			i->velocity_y += i->acceleration_y*(time - time0) / 1000;
		}
		if (i->velocity_x != 0) // вычисление координаты
		{
			temp = i->x;
			i->x += i->velocity_x*(time - time0) / 1000;
			if ((int)i->x - temp)
			{
				result = true;
			}
		}
		if (i->velocity_y != 0)
		{
			temp = i->y;
			i->y += i->velocity_y*(time - time0) / 1000;
			if ((int)i->y - temp)
			{
				result = true;
			}
		}

		if (i->velocity_y <= 70 && i->increasing != -1) // условие взрыва для увеличивающихся шаров
		{
			short x = 20;
			for (int j = 0; j < 10; j++)// создание маленьких шаров
			{							// шары сощдаются справа налево
				decagon *a = new decagon;
				a->x = i->x + x;
				a->y = i->y;
				a->velocity_x = x + rand() % 10;
				a->velocity_y = 40 + rand() % 50;
				a->increasing = -1;
				a->r = 5;
				a->red = 64 + rand() % 192;
				a->green = 64 + rand() % 192;
				a->blue = 64 + rand() % 192;
				lt.push_back(*a);
				count_of_dec++;
				x -= 5;
			}
			lt.erase(i++); // удаление лопнувшего шарика. из очистки в этом цикле работало
			flag = true;   // только это. флаг нужен, чтобы вернуть итератор назад и не
			count_of_dec--;// пропустить элемент
		}
	}
	time0 = time;
	return result;
}

void Idle()
{		
	if (clock() - time0 < delay) // задержка установлена таким образом, чтобы наибольшее число
		return;					// перерисовок равнялось 200

	if (clock() - time_fps >= 1000) // выполняется каждую секунду
	{
		for (list<decagon>::iterator i = lt.begin(); i != lt.end();) // удаление ушедших шаров
		{
			if ((i->x >= width + i->r) || (i->y >= height + i->r) || (i->x <= 0 - i->r) || (i->y <= 0 - i->r)) // пропуск элементов, ушедших за экран
			{
				lt.erase(i++);
				count_of_dec--;
			}
			else i++;			
		}
		int n = 1 + rand() % 6; // создание нескольких шаров
		for (int i = 0; i < n; i++)
		{
			
			decagon *a = new decagon;
			a->y = 20;
			a->r = 10;
			a->x = 20 + rand() % 740;
			a->velocity_y = 215 + (-100 + rand() % 120);
			a->increasing = 1;
			a->red = 64 + rand() % 192;
			a->green = 64 + rand() % 192;
			a->blue = 64 + rand() % 192;
			
			lt.push_back(*a);
			
			count_of_dec++;
			delete a;
		}
		system("cls");
		cout << "Количество перерисовок за прошлую секунду: " << iter << endl;
		cout << "Количество объектов на сцене: " << count_of_dec << endl;
		time_fps = clock();
		iter = 0;
	}
	
	
	bool reshape = alteration(); // перерасчет координат
	if (reshape) // вызов перерисовки
	{
		iter++;
		glutPostRedisplay();
	}
}


int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	short x = 150;
	for (int i = 0; i < 7; i++)
	{
		decagon *a = new decagon;
		a->y = 20;
		a->r = 10;
		a->x = x;
		a->velocity_y = 215 + (-100 + rand() % 120);
		
		x += 80;
		a->red = 64 + rand() % 192;
		a->green = 64 + rand() % 192;
		a->blue = 64 + rand() % 192;
		
		lt.push_back(*a);
		count_of_dec++;
		delete a;
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Яковенко В.В. АВТ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	glutIdleFunc(Idle);

	time0 = clock();
	time_fps = time0;
	glutMainLoop();
	return 0;
}