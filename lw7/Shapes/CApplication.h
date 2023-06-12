#pragma once
#include <SDL.h>
#include <boost/interprocess/detail/atomic.hpp>
#include "CFrameBuffer.h"
#include "CRenderer.h"

using namespace boost::interprocess::ipcdetail;

class CApplication
{
public:
	CApplication()
		:m_frameBuffer(800, 600)
		, m_pMainWindow(NULL)
		, m_timerId(NULL)
		, m_mainSurfaceUpdated(0)
	{
		// Инициализация SDL (таймер и видео)
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

		// Создаем главное окно приложения и сохраняем указатель
		// на поверхность, связанную с ним
		m_pMainWindow = SDL_CreateWindow("Raytracing example",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
			

			//SDL_SWSURFACE | SDL_DOUBLEBUF);
	}

	~CApplication()
	{
		// Завершаем работу всех подсистем SDL
		SDL_Quit();
	}
	void MainLoop()
	{
		// Инициализация приложения
		Initialize();	// (1)

		// Обновляем изначальное содержимое окна
		UpdateMainSurface();	// (2)

		// Цикл обработки сообщений, продолжающийся пока не будет
		// получен запрос на завершение работы
		SDL_Event evt;	// (3)
		while (SDL_WaitEvent(&evt) && evt.type != SDL_QUIT)
		{
			switch (evt.type)
			{
			case SDL_VIDEOEXPOSE:
				// Обновляем содержимое главного окна,
				// если оно нуждается в перерисовке
				UpdateMainSurface();	// (3.а)
				break;
			}
		}

		// Деинициализация приложения
		Uninitialize();	// (4)
	}

	// Обработчик таймера SDL объекта CApplication
	Uint32 OnTimer(Uint32 interval)
	{
		unsigned renderedChunks = 0;
		unsigned totalChunks = 0;
		if (m_renderer.GetProgress(renderedChunks, totalChunks))	// (2)
		{
			interval = 0;	// (2.a)
		}

		InvalidateMainSurface();	// (2.b)
		return interval;
	}

	// Пометка содержимого окна, как нуждающейся в перерисовке
	void InvalidateMainSurface()
	{
		bool redrawIsNeeded =
			atomic_read32(&m_mainSurfaceUpdated) == 1;	// (3)

		if (redrawIsNeeded)	// (3.a)
		{
			atomic_write32(&m_mainSurfaceUpdated, 0);	// (3.b)

			SDL_Event evt = SDL_Event();	// (3.c)
			evt.type = SDL_VIDEOEXPOSE;
			SDL_PushEvent(&evt);
		}
	}

private:
	void Initialize()
	{
		// Запускаем построение изображения и таймер обновления экрана
		m_renderer.Render(m_frameBuffer);	// (1.а)
		m_timerId = SDL_AddTimer(500, &TimerCallback, this);
	}

	void Uninitialize()
	{
		// Останавливаем таймер обновления экрана и построение изображения
		SDL_RemoveTimer(m_timerId);	// (4.а)
		m_renderer.Stop();
	}

	// Обновление содержимого окна приложения
	void UpdateMainSurface()
	{
		CopyFrameBufferToSDLSurface();	// (1)
		SDL_Flip(m_pMainSurface);	// (2)

		atomic_write32(&m_mainSurfaceUpdated, 1);	// (3)
	}

	// Копирование буфера кадра в область главного окна
	void CopyFrameBufferToSDLSurface()
	{
		SDL_LockSurface(m_pMainSurface);	// (1.a)
		const SDL_PixelFormat* pixelFormat = m_pMainSurface->format;

		if (pixelFormat->BitsPerPixel == 32)	// (1.b)
		{
			const Uint8 rShift = pixelFormat->Rshift;	// (1.c)
			const Uint8 gShift = pixelFormat->Gshift;
			const Uint8 bShift = pixelFormat->Bshift;
			const Uint8 aShift = pixelFormat->Ashift;
			const Uint32 aMask = pixelFormat->Amask;	// (1.d)

			const unsigned h = m_frameBuffer.GetHeight();
			const unsigned w = m_frameBuffer.GetWidth();

			// (1.e)
			Uint8* pixels = reinterpret_cast<Uint8*>(m_pMainSurface->pixels);
			for (unsigned y = 0; y < h; ++y, pixels += m_pMainSurface->pitch)
			{
				// (1.f)
				boost::uint32_t const* srcLine = m_frameBuffer.GetPixels(y);
				Uint32* dstLine = reinterpret_cast<Uint32*>(pixels);

				if (bShift == 0 && gShift == 8 && rShift == 16)	// (1.g)
				{
					memcpy(dstLine, srcLine, w * sizeof(Uint32));
				}
				else
				{
					for (unsigned x = 0; x < w; ++x)	// (1.h)
					{
						boost::uint32_t srcColor = srcLine[x];
						Uint32 dstColor =
							((srcColor & 0xff) << bShift) |
							(((srcColor >> 8) & 0xff) << gShift) |
							(((srcColor >> 16) & 0xff) << rShift) |
							((((srcColor >> 24)) << aShift) & aMask);
						dstLine[x] = dstColor;
					}
				}
			}
		}

		SDL_UnlockSurface(m_pMainSurface);	// (11)

	}
	// Обработчик таймера, вызываемый SDL
	static Uint32 SDLCALL TimerCallback(Uint32 interval, void* param)
	{
		CApplication* pMyApp = reinterpret_cast<CApplication*>(param);	// (1)
		return pMyApp->OnTimer(interval);
	}

private:
	// Буфер кадра
	CFrameBuffer m_frameBuffer;
	// Визуализатор
	CRenderer m_renderer;
	// Поверхность окна приложения
	SDL_Window* m_pMainWindow;
	// Идентификатор SDL-таймера
	SDL_TimerID m_timerId;
	// Обновлена ли поверхность окна приложения (1 - да, 0 - нет)
	boost::uint32_t m_mainSurfaceUpdated;
};
