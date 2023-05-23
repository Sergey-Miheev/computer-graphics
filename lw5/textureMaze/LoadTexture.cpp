#include "LoadTexture.h"
// единый стиль именования переменных
const bool LoadTexture(LPCWSTR filename, unsigned int num_tex)
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
	bool musor = ReadFile(FileHandle, &bfh, sizeof(bfh), &nBytesRead, NULL); //считываем первый заголовок, вообще то  он не нужен
	musor = ReadFile(FileHandle, &bih, sizeof(bih), &nBytesRead, NULL); //считываем второй заголовок
	// записываем размер рисунка
	width = bih.biWidth;
	height = bih.biHeight;

	int size = width * height * 3;//
	// использовать вектор вместо new 
	buf = new unsigned char[size];      // выделяем память для исходного рисунка
	TxBits = new unsigned char[size];   // выделяем память для получаемого рисунка
	musor = ReadFile(FileHandle, buf, (size), &nBytesRead, NULL); //считываем данные о цветах пикселей
	// использовать первый буфер
	// в этом цикле  меняем структуру цвета, т.к. BMP файл имеет структуру BGR, а нам нужен RGB
	for (int i = 0; i < (size); i += 3)
	{
		//переписываем массив цветов
		TxBits[i] = buf[i + 2];
		TxBits[i + 1] = buf[i + 1];
		TxBits[i + 2] = buf[i];
	}
	// перенести в onInit
	glewInit();

	// тут инициализируется текстура
	glBindTexture(GL_TEXTURE_2D, num_tex);

	// когда картинка будет увеличиваться(нет большей Мипмапы), используем LINEAR фильтрацию
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// когда уменьшается — берем две ближних мипмапы и лиейно смешиваем цвета
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,     // размер текстуры
		0, GL_RGB, GL_UNSIGNED_BYTE, TxBits);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	CloseHandle(FileHandle); // закрываем файл
	// освобождаем памяти
	delete[] TxBits;
	delete[] buf;
	return TRUE; // возвражаем TRUE если все успешно
}