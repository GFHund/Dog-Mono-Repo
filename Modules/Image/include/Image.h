#ifndef __image_h__
#define __image_h__
#pragma once

//#include <CoreEngine/vector2d.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <stdint.h>
#include <memory>

//eventuell noch eine Klasse f�r die Farbwerte
namespace DogGE
{
	namespace Image{
		class Image
		{
		public:
			//enum colorChannel{R8_G8_B8_A8,R8_G8_B8,R16_G16_B16};
			enum colorChannel
			{
				//RGBA_4BIT = 0, RGB_4BIT = 1,
				RGBA_8BIT = 0, RGB_8BIT = 1,
				RGBA_16BIT = 2,/*RGB_16BIT = 5,
				RGBA_32BIT = 6,RGB_32BIT = 7,*/
			};
			private:
				uint8_t* m_pPixels;//size = width*height*(3 or 4(with or without alpha channel))
				unsigned int mPixelsSize;
				unsigned int m_width, m_height;
				int m_Channel;

			public:
				unsigned int m_Id;

				int getWidth();
				int getHeight();
				int getChannel();

				Image(unsigned int width,unsigned int height,int channel);
				Image(uint8_t* pixels, unsigned int width, unsigned int height, int channel);
				~Image();
				uint8_t* getPixels();
				int getPixelSize();
				//uint8_t* getPixles(colorChannel channel);//todo implentieren

				uint8_t* getPixels(int x, int y, int width, int height);
				uint8_t* getPixels(colorChannel channel, int x, int y, int width, int height);

				uint8_t* getPixel(int x, int y);
				Math::Vector3 getPixelVec(int x,int y);
				Math::Vector4 getPixelVecWithAlpha(int x,int y);
				Math::Vector2 getSize();
				
				void setPixelVec4(int x,int y,Math::Vector4 color);
				void setPixelVec3(int x,int y,Math::Vector3 color);
				
				std::shared_ptr<Image> convertTo(int channel);
				
				bool hasAlpha();

				void setId(unsigned int id);
				unsigned int getId();
		};
	}
	
}
#endif
