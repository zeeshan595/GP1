#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common.h"
#include "Entity.h"
//This class was taken from bobby

class Texture: public Module
{
private:
	GLuint GLTextureID;
	GLuint aTextureInfo;
	GLsizei textureWidth;
	GLsizei textureHeight;
	ILuint ilTextureID;
	ILubyte *txData;

public:
	vec2 textCords[4];

	Texture();
	Texture(LPCSTR theFilename);
	~Texture();

	void Update();
	bool createTexture(LPCSTR theFilename);		// create the texture for use.
	GLuint getTexture();						// return the texture.
	GLsizei getTWidth();						// Return width of texture;
	GLsizei getTHeight();						// Return height of texture;
};

#endif