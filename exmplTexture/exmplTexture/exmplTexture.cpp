#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <math.h>
#include <Windows.h> //для  BITMAPFILEHEADER BITMAPINFOHEADER
#pragma hdrstop

//---------------------------------------------------------------------------
bool load_texture(LPCWSTR filename, unsigned int num_tex)
//filename - имя файла, num_tex - номер текстуры
{
    BITMAPFILEHEADER bfh; //Заголовок BMP файла
    BITMAPINFOHEADER bih; //Заголовок BMP файла
    unsigned char* TxBits, * buf; // массивы для цветов
    DWORD nBytesRead;        // сколько данных прочтено с файла
    HANDLE FileHandle; // хендл, открываемого для чтения, файла
    int width, height;   // ширина и высота файла

    // открываем файл для чтения
    FileHandle = CreateFile(filename,                 // имя файла 
        GENERIC_READ,               // открыт для чтения 
        0,                              // совместного использования нет 
        NULL,                           // защита по умолчанию 
        OPEN_EXISTING,              // только существующий файл 
        FILE_ATTRIBUTE_NORMAL,  // атрибуты обычного файла 
        NULL);                  // шаблона атрибутов нет 

    if (FileHandle == INVALID_HANDLE_VALUE) // если ошибка при открытии то сообщаем
    {
        MessageBox(NULL, L"Файл отсутствует!", L"Ошибка", MB_OK | MB_ICONINFORMATION);
        return FALSE;
    }
    ReadFile(FileHandle, &bfh, sizeof(bfh), &nBytesRead, NULL); //считываем первый заголовок, вообще то  он не нужен
    ReadFile(FileHandle, &bih, sizeof(bih), &nBytesRead, NULL); //считываем второй заголовок
    // записываем размер рисунка
    width = bih.biWidth;
    height = bih.biHeight;

    int size = width * height * 3;//
    buf = new unsigned char[size];      // выделяем память для исходного рисунка
    TxBits = new unsigned char[size];   // выделяем память для получаемого рисунка
    ReadFile(FileHandle, buf, (size), &nBytesRead, NULL); //считываем данные о цветах пикселей

    // в этом цикле  меняем структуру цвета, т.к. BMP файл имеет структуру BGR, а нам нужен RGB
    for (int i = 0; i < (size); i += 3)
    {
        //переписываем массив цветов
        TxBits[i] = buf[i + 2];
        TxBits[i + 1] = buf[i + 1];
        TxBits[i + 2] = buf[i];
    }


    // тут инициализируется текстура
    glBindTexture(GL_TEXTURE_2D, num_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        width, height,     // размер текстуры
        0, GL_RGB, GL_UNSIGNED_BYTE, TxBits);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    CloseHandle(FileHandle); // закрываем файл
    // освобождаем памяти
    delete[] TxBits;
    delete[] buf;
    return TRUE; // возвражаем TRUE если все успешно

}
//---------------------------------------------------------------------------
GLfloat width = 700.;
GLfloat height = 700.;

//---------------------------------------------------------------------------
GLfloat    xrot;            // Вращение X
GLfloat    yrot;            // Y
GLfloat    zrot;            // Z
//----------------------------------------------------------------------------------
void Draw()  //строим куб накладываем текстуру
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);        // Вращение по оси X
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);        // Вращение по оси Y
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);        // Вращение по оси Z

    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    // Передняя грань
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);    // Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);    // Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);    // Верх лево
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 2);
    glBegin(GL_QUADS);
    // Задняя грань
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);    // Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);    // Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);    // Низ лево
    glEnd();


    glBindTexture(GL_TEXTURE_2D, 3);
    glBegin(GL_QUADS);
    // Верхняя грань
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);    // Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);    // Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);    // Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);    // Верх право
    glEnd();


    glBindTexture(GL_TEXTURE_2D, 4);
    glBegin(GL_QUADS);
    // Нижняя грань
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);    // Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);    // Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ право
    glEnd();


    glBindTexture(GL_TEXTURE_2D, 5);
    glBegin(GL_QUADS);
    // Правая грань
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);    // Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);    // Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);    // Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);    // Низ лево
    glEnd();


    glBindTexture(GL_TEXTURE_2D, 6);
    glBegin(GL_QUADS);
    // Левая грань
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);    // Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);    // Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);    // Верх лево

    glEnd();

    xrot += 0.3f;            // Ось вращения X
    yrot += 0.2f;            // Ось вращения Y
    zrot += 0.4f;            // Ось вращения Z
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Cube Texture");
    //для куба
    load_texture(L"lava2.bmp", 1);  // Загрузка текстур
    load_texture(L"lava2.bmp", 2);
    load_texture(L"lava2.bmp", 3);  // Загрузка текстур
    load_texture(L"lava2.bmp", 4);
    load_texture(L"lava2.bmp", 5);  // Загрузка текстур
    load_texture(L"lava2.bmp", 6);

    glEnable(GL_TEXTURE_2D);        // Разрешение наложение текстуры
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0);    //
    glDepthFunc(GL_LESS);  // фрагмент проходит тест если его значение глубины меньше хранимого в буфере
    glEnable(GL_DEPTH_TEST); // включить тест гдубины
    //glShadeModel(GL_SMOOTH);  // разрешить плавное цветовое сглаживание
    glViewport(0, 0, width, height); //
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, width / height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(Draw);
    glutMainLoop();


    return 0;
}