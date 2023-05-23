#include "LoadTexture.h"
// ������ ����� ���������� ����������
const bool LoadTexture(LPCWSTR filename, unsigned int num_tex)
//filename - ��� �����, num_tex - ����� ��������
{
	BITMAPFILEHEADER bfh; //��������� BMP �����
	BITMAPINFOHEADER bih; //��������� BMP �����
	unsigned char* TxBits, * buf; // ������� ��� ������
	DWORD nBytesRead;        // ������� ������ �������� � �����
	HANDLE FileHandle; // �����, ������������ ��� ������, �����
	int width, height;   // ������ � ������ �����

	// ��������� ���� ��� ������
	FileHandle = CreateFile(filename,                 // ��� ����� 
		GENERIC_READ,               // ������ ��� ������ 
		0,                              // ����������� ������������� ��� 
		NULL,                           // ������ �� ��������� 
		OPEN_EXISTING,              // ������ ������������ ���� 
		FILE_ATTRIBUTE_NORMAL,  // �������� �������� ����� 
		NULL);                  // ������� ��������� ��� 

	if (FileHandle == INVALID_HANDLE_VALUE) // ���� ������ ��� �������� �� ��������
	{
		MessageBox(NULL, L"���� �����������!", L"������", MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}
	bool musor = ReadFile(FileHandle, &bfh, sizeof(bfh), &nBytesRead, NULL); //��������� ������ ���������, ������ ��  �� �� �����
	musor = ReadFile(FileHandle, &bih, sizeof(bih), &nBytesRead, NULL); //��������� ������ ���������
	// ���������� ������ �������
	width = bih.biWidth;
	height = bih.biHeight;

	int size = width * height * 3;//
	// ������������ ������ ������ new 
	buf = new unsigned char[size];      // �������� ������ ��� ��������� �������
	TxBits = new unsigned char[size];   // �������� ������ ��� ����������� �������
	musor = ReadFile(FileHandle, buf, (size), &nBytesRead, NULL); //��������� ������ � ������ ��������
	// ������������ ������ �����
	// � ���� �����  ������ ��������� �����, �.�. BMP ���� ����� ��������� BGR, � ��� ����� RGB
	for (int i = 0; i < (size); i += 3)
	{
		//������������ ������ ������
		TxBits[i] = buf[i + 2];
		TxBits[i + 1] = buf[i + 1];
		TxBits[i + 2] = buf[i];
	}
	// ��������� � onInit
	glewInit();

	// ��� ���������������� ��������
	glBindTexture(GL_TEXTURE_2D, num_tex);

	// ����� �������� ����� �������������(��� ������� �������), ���������� LINEAR ����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ����� ����������� � ����� ��� ������� ������� � ������ ��������� �����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,     // ������ ��������
		0, GL_RGB, GL_UNSIGNED_BYTE, TxBits);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	CloseHandle(FileHandle); // ��������� ����
	// ����������� ������
	delete[] TxBits;
	delete[] buf;
	return TRUE; // ���������� TRUE ���� ��� �������
}