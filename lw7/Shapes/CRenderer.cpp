#include "CRenderer.h"
#include <boost/interprocess/detail/atomic.hpp>

using namespace boost::interprocess::ipcdetail;
using boost::mutex;

bool CRenderer::IsRendering()const
{
	return atomic_read32(
		const_cast<volatile boost::uint32_t*>(&m_rendering)) != 0;
}

bool CRenderer::IsStopping()const
{
	return atomic_read32(
		const_cast<volatile boost::uint32_t*>(&m_stopping)) != 0;
}

bool CRenderer::SetRendering(bool rendering)
{
	bool wasRendering =
		atomic_cas32(&m_rendering, rendering, !rendering) != 0;

	return wasRendering != rendering;
}

bool CRenderer::SetStopping(bool stopping)
{
	bool wasStopping =
		atomic_cas32(&m_stopping, stopping, !stopping) != 0;

	return wasStopping != stopping;
}

bool CRenderer::GetProgress(
	unsigned& renderedChunks, unsigned& totalChunks)const
{
	// «ахватываем мьютекс на врем€ работы данного метода
	mutex::scoped_lock lock(m_mutex);

	renderedChunks = atomic_read32(
		const_cast<volatile boost::uint32_t*>(&m_renderedChunks));

	totalChunks = atomic_read32(
		const_cast<volatile boost::uint32_t*>(&m_totalChunks));;

	// —ообщаем, все ли блоки изображени€ были обработаны
	return (totalChunks > 0) && (renderedChunks == totalChunks);
}

bool CRenderer::Render(CFrameBuffer& frameBuffer)
{
	if (!SetRendering(true))	// (1)
	{
		return false;
	}

	mutex::scoped_lock lock(m_mutex);	// (2)

	frameBuffer.Clear();

	atomic_write32(&m_totalChunks, 0);
	atomic_write32(&m_renderedChunks, 0);

	if (SetStopping(false))	// (3)
	{
		SetRendering(false);
		return false;
	}

	m_thread = boost::thread(	// (4)
		&CRenderer::RenderFrame, this, boost::ref(frameBuffer));

	return true;
}

void CRenderer::RenderFrame(CFrameBuffer& frameBuffer)
{
	const int width = frameBuffer.GetWidth();	// (1)
	const int height = frameBuffer.GetHeight();

	atomic_write32(&m_totalChunks, height);

#ifdef _OPENMP	// (2)
#pragma omp parallel for schedule(dynamic)
#endif
	for (int y = 0; y < height; ++y)
	{
		boost::uint32_t* rowPixels = frameBuffer.GetPixels(y);

		if (!IsStopping())	// (3)
		{
			for (int x = 0; x < width; ++x)	// (4)
			{
				rowPixels[size_t(x)] = CalculatePixelColor(x, y, width, height);
			}

			atomic_inc32(&m_renderedChunks);	// (5)
		}
	}

	SetStopping(false);	// (6)
	SetRendering(false);
}

boost::uint32_t CRenderer::CalculatePixelColor(
	int x, int y, unsigned frameWidth, unsigned frameHeight)const
{
	double x0 = 2.0 * x / frameWidth - 1.5;
	double y0 = 2.0 * y / frameHeight - 1.0;

	double rho = sqrt((x0 - 0.25) * (x0 - 0.25) + y0 * y0);
	double theta = atan2(y0, x0 - 0.25);
	double rhoC = 0.5 - 0.5 * cos(theta);
	if (rho <= rhoC)
	{
		return 0x000000;
	}

	double re = 0, im = 0;

	int iterCount = 10000;
	while ((iterCount > 0) && (re * re + im * im < 1e18))
	{
		double re1 = re * re - im * im + x0;
		im = 2 * re * im + y0;
		re = re1;
		--iterCount;
	}

	boost::uint8_t r = static_cast<boost::uint8_t>((iterCount / 3) & 0xff);
	boost::uint8_t g = static_cast<boost::uint8_t>(iterCount & 0xff);
	boost::uint8_t b = static_cast<boost::uint8_t>((iterCount / 2) & 0xff);
	boost::uint8_t a = 0xff;
	return (a << 24) | (r << 16) | (g << 8) | b;
}

void CRenderer::Stop()
{
	// ≈сли происходит построение изображени€
	if (IsRendering())
	{
		// —ообщаем потоку, выполн€ющему построение изображени€,
		// о необходимости завершить работу
		SetStopping(true);

		// ƒожидаемс€ окончани€ работы рабочего потока
		m_thread.join();

		// —брасываем флаг остановки, если поток завершил свою
		// работу до вызова SetStopping(true)
		SetStopping(false);
	}
}

CRenderer::CRenderer(void)
	:m_rendering(0)	// »значальное состо€ние: "не рисуем"
	, m_stopping(0)	// Ќе останавливаемс€
	, m_totalChunks(0)	// ќбщее количество обрабатываемых блоков изображени€
	, m_renderedChunks(0)	//  оличество обработанных блоков изображени€
{
}

CRenderer::~CRenderer(void)
{
	// ќстанавливаем работу фонового потока, если он еще не закончилс€
	Stop();
}