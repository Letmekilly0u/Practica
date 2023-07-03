#include <iostream>
#include <FreeImage.h>
#include <string>
#include <algorithm>
#include <fstream>

const std::string c_strIFreeImage = "IFreeImage";

int GlobalWidth = 0;
int GlobaHeigth = 0;

class FreeImageLibHolder
{
  public:
    FreeImageLibHolder()
    {
      FreeImage_Initialise();
      std::cout << "Lib is initialise.\n";
    }
    ~FreeImageLibHolder()
    {
      FreeImage_DeInitialise();
      std::cout << "Lib is deInitialise.\n";
    }
};

class ImageClass{
private:
	FIBITMAP* image;
  FREE_IMAGE_FORMAT free_img_format;
	const char *fileName;
  FIMEMORY *fiBuffer;
public:
	ImageClass(const char *filename);

	~ImageClass();

  int LoadImageFromMemory(unsigned char *memory, size_t fileSize);
	int encodeToJPEG();
  int getFileType();
  int rotateImage(double angle);
  int resizeImage(int dst_width, int dst_height);
  int resizeImage(int anMaxWidth, int anMaxHeight, int anQuality);
  int getImageSizeParam();
};

std::string MakeName(std::string str);
std::vector<uint8_t> LoadImageToMemory(std::string nameFile);
