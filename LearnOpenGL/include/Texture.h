#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

class Texture
{
public:
	unsigned int Id;
	int Width, Height, NrChannels;
	Texture(std::string filePath);
	~Texture();
};

#endif // !TEXTURE_H_
