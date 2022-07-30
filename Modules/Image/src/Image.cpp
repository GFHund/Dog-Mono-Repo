#include <Image.h>
#include <Exceptions/InvalidChannelException.h>
namespace DogGE
{
	namespace Image{
		/*
		enum colorChannel
			{
				RGBA_4BIT = 0, RGB_4BIT = 1,
				RGBA_8BIT = 2, RGB_8BIT = 3,
				RGBA_16BIT = 4,
			};
		*/
		struct sRGBA_8Bit
		{
			uint8_t red;
			uint8_t green;
			uint8_t blue;
			uint8_t alpha;
		};
		//--------------------------------
		struct sRGB_8Bit
		{
			uint8_t red;
			uint8_t green;
			uint8_t blue;
		};
		//--------------------------------
		struct sRGBA_16Bit
		{
			uint16_t red;
			uint16_t green;
			uint16_t blue;
			uint16_t alpha;
		};
		//--------------------------------
		Image::Image(unsigned int width,unsigned int height,int channel){
			int arrayLength = 0;
			switch(channel){
				case RGBA_8BIT:
					arrayLength = width * height * 4;
					break;
				case RGB_8BIT:
					arrayLength = width * height * 3;
					break;
				case RGBA_16BIT:
					arrayLength = width*height*8;
					break;
				default:
					throw InvalidChannelException(channel);
			}
			this->m_pPixels = new uint8_t[arrayLength];
			this->mPixelsSize = arrayLength;
			for(int i= 0;i<arrayLength;i++){
				this->m_pPixels[i] = 0;
			}
			
			this->m_Channel = channel;
			this->m_width = width;
			this->m_height = height;
		}
		//--------------------------------
		Image::Image(uint8_t* pixels, unsigned int width, unsigned int height, int channel)
		{
			this->m_pPixels = pixels;
			this->m_width = width;
			this->m_height = height;
			this->m_Channel = channel;
			this->m_Id = -1;
			int arrayLength = 0;
			switch(channel){
				case RGBA_8BIT:
					arrayLength = width * height * 4;
					break;
				case RGB_8BIT:
					arrayLength = width * height * 3;
					break;
				case RGBA_16BIT:
					arrayLength = width*height*8;
					break;
				default:
					throw InvalidChannelException(channel);
			}
			this->mPixelsSize = arrayLength;
		}
		//------------------------------------
		Image::~Image()
		{
			if (m_pPixels != nullptr)
			{
				delete[] m_pPixels;
				m_pPixels = nullptr;
			}
		}
		//------------------------------------
		uint8_t* Image::getPixels()
		{
			return this->m_pPixels;
		}
		//------------------------------------
		int Image::getPixelSize(){
			return this->mPixelsSize;
		}
		/*
		uint8_t* CImage::getPixles(colorChannel channel)
		{
			return this->m_pPixels;
		}
		*/
		//------------------------------------
		uint8_t* Image::getPixel(int x, int y)
		{
			uint8_t* color = new uint8_t[3];
			color[0] = this->m_pPixels[3 * (this->m_width*y + x)];
			color[1] = this->m_pPixels[3 * (this->m_width*y + x) + 1];
			color[2] = this->m_pPixels[3 * (this->m_width*y + x) + 2];
			
			return color;
		}
		//------------------------------------
		uint8_t* Image::getPixels(int x, int y, int width, int height)
		{
			uint8_t* pic = new uint8_t[height*width * 3];
			
			int pos=0;
			
			for (int i = 0; i< this->m_height * this->m_width * 3; i += 3)
			{
				int ix = i % (this->m_width * 3);
				int iy = i / (this->m_width * 3);
				if(ix >= x && ix < x + width && iy >= y && iy < height)
				{
					pic[pos] = this->m_pPixels[i];
					pic[pos + 1] = this->m_pPixels[i + 1];
					pic[pos + 2] = this->m_pPixels[i + 2];
					pos += 3;
				}
			}
			return pic;
		}
		//------------------------------------
		Math::Vector2 Image::getSize()
		{
			return Math::Vector2(this->m_width, this->m_height);
		}
		//------------------------------------
		/*
		only color information no alpha value if it ist there
		*/
		Math::Vector3 Image::getPixelVec(int x,int y)
		{
			Math::Vector3 ret;
			ret.setX(this->m_pPixels[3 * (this->m_width*y + x)]);
			ret.setY(this->m_pPixels[3 * (this->m_width*y + x) + 1]);
			ret.setZ(this->m_pPixels[3 * (this->m_width*y + x) + 2]);
			return ret;
		}
		//------------------------------------
		Math::Vector4 Image::getPixelVecWithAlpha(int x,int y)
		{
			Math::Vector4 ret;
			/*
			if(hasAlpha())
			{
				ret.setX(this->m_pPixels[4 * (this->m_width*y + x)]);
				ret.setY(this->m_pPixels[4 * (this->m_width*y + x) + 1]);
				ret.setZ(this->m_pPixels[4 * (this->m_width*y + x) + 2]);
				ret.setW(this->m_pPixels[4 * (this->m_width*y + x) + 4]);
			}
			else
			{
				ret.setX(this->m_pPixels[3 * (this->m_width*y + x)]);
				ret.setY(this->m_pPixels[3 * (this->m_width*y + x) + 1]);
				ret.setZ(this->m_pPixels[3 * (this->m_width*y + x) + 2]);
				ret.setW(255);
			}
			*/
			if (m_Channel == RGBA_8BIT)
			{
				sRGBA_8Bit* image = reinterpret_cast<sRGBA_8Bit*>(m_pPixels);
				sRGBA_8Bit pixel = image[this->m_width*y + x];
				ret.setX(pixel.red);
				ret.setY(pixel.green);
				ret.setZ(pixel.blue);
				ret.setW(pixel.alpha);
			}
			else if (m_Channel == RGB_8BIT)
			{
				sRGB_8Bit* image = reinterpret_cast<sRGB_8Bit*>(m_pPixels);
				sRGB_8Bit pixel = image[this->m_width*y + x];
				ret.setX(pixel.red);
				ret.setY(pixel.green);
				ret.setZ(pixel.blue);
				ret.setW(255);
			}
			else if (m_Channel == RGBA_16BIT)
			{
				sRGBA_16Bit* image = reinterpret_cast<sRGBA_16Bit*>(m_pPixels);
				sRGBA_16Bit pixel = image[this->m_width*y + x];
				ret.setX(pixel.red);
				ret.setY(pixel.green);
				ret.setZ(pixel.blue);
				ret.setW(pixel.alpha);
			}

			return ret;
		}
		//------------------------------------
		int Image::getWidth()
		{
			return this->m_width;
		}
		//------------------------------------
		int Image::getHeight()
		{
			return this->m_height;
		}
		//------------------------------------
		int Image::getChannel()
		{
			return m_Channel;
		}
		//------------------------------------
		/*
		the W Param is the alpha parameter. it will not be used if the image has no alpha channel
		*/
		void Image::setPixelVec4(int x,int y,Math::Vector4 color)
		{
			if(x < 0 || x > m_width || y < 0 ||y > m_height)
			{
				return;
			}
			
			if (m_Channel == RGBA_8BIT)
			{
				uint8_t r, g, b, a;
				r = static_cast<uint8_t>(color.getX());
				g = static_cast<uint8_t>(color.getY());
				b = static_cast<uint8_t>(color.getZ());
				a = static_cast<uint8_t>(color.getW());

				sRGBA_8Bit* image = reinterpret_cast<sRGBA_8Bit*>(m_pPixels);
				sRGBA_8Bit changeColor = {r,g,b,a};
				image[this->m_width*y + x] = changeColor;
			}
			else if (m_Channel == RGB_8BIT)
			{
				uint8_t r, g, b, a;
				r = static_cast<uint8_t>(color.getX());
				g = static_cast<uint8_t>(color.getY());
				b = static_cast<uint8_t>(color.getZ());
				a = static_cast<uint8_t>(color.getW());

				sRGB_8Bit* image = reinterpret_cast<sRGB_8Bit*>(m_pPixels);
				sRGB_8Bit changeColor = { r, g, b};
				image[this->m_width*y + x] = changeColor;
			}
			else if (m_Channel == RGBA_16BIT)
			{
				uint16_t r, g, b, a;
				r = static_cast<uint16_t>(color.getX());
				g = static_cast<uint16_t>(color.getY());
				b = static_cast<uint16_t>(color.getZ());
				a = static_cast<uint16_t>(color.getW());

				sRGBA_16Bit* image = reinterpret_cast<sRGBA_16Bit*>(m_pPixels);
				sRGBA_16Bit changeColor = { r, g, b, a };
				image[this->m_width*y + x] = changeColor;
			}

			/*
			int components = 3;
			if(hasAlpha())
			{
				components = 4;
				this->m_pPixels[components * (this->m_width*y + x) + 3] = a;
			}
			this->m_pPixels[components * (this->m_width*y + x)] = r;
			this->m_pPixels[components * (this->m_width*y + x) + 1] = g;
			this->m_pPixels[components * (this->m_width*y + x) + 2] = b;
			*/
		}
		//------------------------------------
		void Image::setPixelVec3(int x,int y,Math::Vector3 color)
		{
			if(x < 0 || x > m_width || y < 0 ||y > m_height)
			{
				return;
			}
			uint8_t r,g,b;
			r = static_cast<uint8_t>(color.getX());
			g = static_cast<uint8_t>(color.getY());
			b = static_cast<uint8_t>(color.getZ());
			int components = 3;
			if(hasAlpha())
			{
				components = 4;
				this->m_pPixels[components * (this->m_width*y + x) + 3] = 255;
			}
			this->m_pPixels[components * (this->m_width*y + x)] = r;
			this->m_pPixels[components * (this->m_width*y + x) + 1] = g;
			this->m_pPixels[components * (this->m_width*y + x) + 2] = b;
		}
		//------------------------------------
		bool Image::hasAlpha()
		{
			return m_Channel % 2  == 0;
		}
		//------------------------------------
		void Image::setId(unsigned int id)
		{
			m_Id = id;
		}
		//------------------------------------
		unsigned int Image::getId()
		{
			return m_Id;
		}
		//------------------------------------
		std::shared_ptr<Image> Image::convertTo(int channel)
		{
			//1----------
			if(this->m_Channel == RGBA_8BIT && channel == RGB_8BIT)
			{
				sRGB_8Bit* pixels = new sRGB_8Bit[m_width*m_height];
				sRGBA_8Bit* fromPixels = reinterpret_cast<sRGBA_8Bit*>(m_pPixels);
				for(int i = 0;i<m_width*m_height;i++)
				{
					pixels[i].red = fromPixels[i].red;
					pixels[i].green = fromPixels[i].green;
					pixels[i].blue = fromPixels[i].blue;
				}
				uint8_t* pixels8Bit = reinterpret_cast<uint8_t*>(pixels);
				std::shared_ptr<Image> ret(new Image(pixels8Bit,m_width,m_height,RGB_8BIT));
				return ret;
			}
			//2----------
			else if(this->m_Channel == RGB_8BIT && channel == RGBA_8BIT)
			{
				sRGBA_8Bit* pixels = new sRGBA_8Bit[m_width*m_height];
				sRGB_8Bit* fromPixels = reinterpret_cast<sRGB_8Bit*>(m_pPixels);
				for(int i = 0;i<m_width*m_height;i++)
				{
					pixels[i].red = fromPixels[i].red;
					pixels[i].green = fromPixels[i].green;
					pixels[i].blue = fromPixels[i].blue;
					pixels[i].alpha = 255;
				}
				uint8_t* pixels8Bit = reinterpret_cast<uint8_t*>(pixels);
				std::shared_ptr<Image> ret(new Image(pixels8Bit,m_width,m_height,RGBA_8BIT));
				return ret;
			}
			//3----------
			else if (this->m_Channel == RGBA_8BIT && channel == RGBA_16BIT)
			{
				sRGBA_16Bit* pixels = new sRGBA_16Bit[m_width*m_height];
				sRGBA_8Bit* fromPixels = reinterpret_cast<sRGBA_8Bit*>(m_pPixels);
				for (int i = 0; i<m_width*m_height; i++)
				{
					pixels[i].red = fromPixels[i].red * 256;
					pixels[i].green = fromPixels[i].green * 256;
					pixels[i].blue = fromPixels[i].blue * 256;
					pixels[i].alpha = fromPixels[i].alpha * 256;
				}
				uint8_t* pixels8Bit = reinterpret_cast<uint8_t*>(pixels);
				std::shared_ptr<Image> ret(new Image(pixels8Bit, m_width, m_height, RGBA_16BIT));
				return ret;
			}
			//4----------
			else if (this->m_Channel == RGBA_16BIT && channel == RGBA_8BIT)
			{
				sRGBA_8Bit* pixels = new sRGBA_8Bit[m_width*m_height];
				sRGBA_16Bit* fromPixels = reinterpret_cast<sRGBA_16Bit*>(m_pPixels);
				for (int i = 0; i<m_width*m_height; i++)
				{
					pixels[i].red = fromPixels[i].red / 256;
					pixels[i].green = fromPixels[i].green / 256;
					pixels[i].blue = fromPixels[i].blue / 256;
					pixels[i].alpha = fromPixels[i].alpha / 256;
				}
				uint8_t* pixels8Bit = reinterpret_cast<uint8_t*>(pixels);
				std::shared_ptr<Image> ret(new Image(pixels8Bit, m_width, m_height, channel));
				return ret;
			}
			//5----------
			else if (this->m_Channel == RGB_8BIT && channel == RGBA_16BIT)
			{
				sRGBA_16Bit* pixels = new sRGBA_16Bit[m_width*m_height];
				sRGB_8Bit* fromPixels = reinterpret_cast<sRGB_8Bit*>(m_pPixels);
				for (int i = 0; i<m_width*m_height; i++)
				{
					pixels[i].red = fromPixels[i].red * 256;
					pixels[i].green = fromPixels[i].green * 256;
					pixels[i].blue = fromPixels[i].blue * 256;
					pixels[i].alpha = (uint16_t)65536;
				}
				uint8_t* pixels8Bit = reinterpret_cast<uint8_t*>(pixels);
				std::shared_ptr<Image> ret(new Image(pixels8Bit, m_width, m_height, RGBA_16BIT));
				return ret;
			}
			//6----------
			else if (this->m_Channel == RGBA_16BIT && channel == RGB_8BIT)
			{
				sRGB_8Bit* pixels = new sRGB_8Bit[m_width*m_height];
				sRGBA_16Bit* fromPixels = reinterpret_cast<sRGBA_16Bit*>(m_pPixels);
				for (int i = 0; i<m_width*m_height; i++)
				{
					pixels[i].red = fromPixels[i].red / 256;
					pixels[i].green = fromPixels[i].green / 256;
					pixels[i].blue = fromPixels[i].blue / 256;
				}
				uint8_t* pixels8Bit = reinterpret_cast<uint8_t*>(pixels);
				std::shared_ptr<Image> ret(new Image(pixels8Bit, m_width, m_height, channel));
				return ret;
			} else{
				throw InvalidChannelException(channel);
			}
		}
	}
	
}