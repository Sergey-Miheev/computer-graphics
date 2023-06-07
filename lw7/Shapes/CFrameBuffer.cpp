#include "CFrameBuffer.h"

CFrameBuffer::CFrameBuffer(unsigned width, unsigned height)
	:m_pixels(width* height)
	, m_width(width)
	, m_height(height)
{
}

void CFrameBuffer::Clear(boost::uint32_t color)
{
	std::fill(m_pixels.begin(), m_pixels.end(), color);
}

void CFrameBuffer::SetPixel(unsigned x, unsigned y, boost::uint32_t color) throw()
{
	assert(x < m_width);
	assert(y < m_height);
	m_pixels[size_t(y * m_width + x)] = color;
}
