// Библиотеки
#include "iFreeImage.h"
//Тела функций класса
ImageClass::ImageClass(const char *filename)
{
  std::cout << "  Constuctor is used.\n";
  fileName = filename;
}


ImageClass::~ImageClass(){
  std::cout << "  Destructor is used.\n";
  FreeImage_Unload(image);
  std::cout << "  Close memory.\n";
}

int ImageClass::LoadImageFromMemory(unsigned char *memory, size_t fileSize)
{
  //Open memory
  fiBuffer = FreeImage_OpenMemory(memory, fileSize);
  if (fiBuffer == nullptr){
      std::cout << "LoadImage(): couldn't load image from ofBuffer, opening FreeImage memory failed.\n";
      return -1;
  }
  //Get file type from memory
  free_img_format = FreeImage_GetFileTypeFromMemory(fiBuffer);
  if (free_img_format == -1){
      std::cout << "LoadImage(): couldn't load image from ofBuffer, unable to guess image format from memory";
      return -1;
  }

  //Make the Image
  image = FreeImage_LoadFromMemory(free_img_format, fiBuffer, 0);
  FreeImage_CloseMemory(fiBuffer);
  if (fiBuffer != nullptr)
    return 0;
return 0;
}


int ImageClass::encodeToJPEG(){
  std::string str = MakeName(fileName);
  str = MakeName(str) + ".jpeg";
  const char* OutStr = str.c_str();
  FreeImage_Save(FIF_JPEG, image, OutStr, 0);
  return 0;
}


int ImageClass::getFileType()
{
  std::cout << "  File type: " << FreeImage_GetFormatFromFIF(FreeImage_GetFileType(fileName)) << ".\n";
  return 0;
}


int ImageClass::rotateImage(double angle)
{
  image = FreeImage_Rotate(image, angle);
  return 0;
}


int ImageClass::resizeImage(int dst_width, int dst_height)
{
  image = FreeImage_Rescale(image, dst_width, dst_height, FILTER_BOX);
  return 0;
}

//Param
int ImageClass::resizeImage(int anMaxWidth, int anMaxHeight, int anQuality)
{
  //image = FreeImage_Rescale(image, dst_width, dst_height, FILTER_BOX);
  if (!FreeImage_GetWidth(image) || !FreeImage_GetHeight(image)){
    return -4;}

  if(!anMaxWidth || !anMaxHeight) {
    std::cout << "Max width: " << anMaxWidth << "or max height: " << anMaxHeight << "can't be return!";
    return -3;}

  int nImageWidth = FreeImage_GetWidth(image);
  int nImageHeight = FreeImage_GetHeight(image);

  if(!nImageWidth || !nImageHeight) {
    std::cout << "Max width: " << anMaxWidth << "or max height: " << anMaxHeight << "can't be return!";
    return -2;}

  double dblFirst = (double)anMaxWidth / (double)anMaxHeight;
  double dblSecond = (double)nImageWidth / (double)nImageHeight;

  int nTransformType = 0;

  if(dblFirst < dblSecond)
  {
    nTransformType = 1;
  }
  else
  {
    nTransformType = 2;
  }

  if(nTransformType == 0) {
    return -1;}

  int nNewWidth = 0;
  int nNewHeigth = 0;

  if(nTransformType == 1)
  {
    nNewWidth = anMaxWidth;
    nNewHeigth = int(double(FreeImage_GetHeight(image)) * double(anMaxWidth) / double(FreeImage_GetWidth(image)));
  }
  else
  {
    nNewHeigth = anMaxHeight;
    nNewWidth = int(double(FreeImage_GetWidth(image)) * double(anMaxHeight) / double(FreeImage_GetHeight(image)));
  }

  GlobalWidth = nNewWidth;
  GlobaHeigth = nNewHeigth;
  return 0;
}


int ImageClass::getImageSizeParam()
{
  std::cout << "  Image width: " << FreeImage_GetWidth(image) << "\n";
  std::cout << "  Image height: " << FreeImage_GetHeight(image) << "\n";
  return 0;
}


//Внешние функции
std::string MakeName(std::string str)
{
  int index = str.find('.');
  if (index != std::string::npos) str.erase(index);
  return str;
}


std::vector<uint8_t> LoadImageToMemory(std::string nameFile)
{
  std::ifstream file(nameFile, std::ios::binary | std::ios::ate);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> buffer;
  buffer.resize(size);
  file.read(buffer.data(), size);
  std::vector<uint8_t> outVector;
  outVector.resize(size);

  for(int i = 0; i < outVector.size(); i++)
  {
    outVector[i] = buffer[i];
  }

  return outVector;
}

//Main section
int main(int argc, char **argv) {

  const char* value = "two.png";

  FreeImageLibHolder init = FreeImageLibHolder();
	ImageClass img = ImageClass(value);

  std::vector<uint8_t> memoryImg = LoadImageToMemory(value);
  img.LoadImageFromMemory(memoryImg.data(), memoryImg.size());
  img.getFileType();
  //img.rotateImage(110);
  img.getImageSizeParam();
  //img.resizeImage(150,150);
  img.resizeImage(350, 350, 0);
  img.resizeImage(GlobalWidth, GlobaHeigth);
  img.encodeToJPEG();

  return 0;
}
