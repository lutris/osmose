/*
 * Copyright 2001-2011 Vedder Bruno.
 *	
 * This file is part of Osmose, a Sega Master System/Game Gear software 
 * emulator.
 *
 * Osmose is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Osmose is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Osmose.  If not, see <http://www.gnu.org/licenses/>.
 *	
 *
 * File : QGLImage.cpp
 *
 * Description : This Object is used to display image on an OpenGL
 * textured quad . If the QGLImage size changes, the texture will be stretched
 * to fit the Quad. The texture dimension can be changed, but should not
 * be done every frame, for performances reasons. Note that texture
 * format is fixed to 32 bits RGBA.
 *
 * The textureBuffer is protected by a mutex because blit() or 
 * resolutionChanged slot may be called during paintEvent. The blit() method
 * expect the source buffer to be of the current texture resolution.
 * 
 * The texture is refreshed using the blit() method, which call update().
 * Author : B.Vedder
 *
 * Date : Wed May 19 17:55:00 2010
 *
 */

#include "QGLImage.h"
#include <iostream>

using namespace std;

/**
 * Constructor.
 * 
 * Param1 : Parent QWidget.
 *
 * Param2 : texture Width.
 *
 * Param3 : texture Height.
 *
 */
QGLImage::QGLImage(QWidget *parent, int w, int h, QGL::FormatOptions f) : QGLWidget(QGLFormat(f), parent)
{
	textureBuffer = NULL;
	viewPortWidth = 1;
	viewPortHeight = 1;	
	adjustTextureDimension(w, h);
	bilinearFiltering = false;
}


/**
 * Destructor.
 */
QGLImage::~QGLImage()
{
}


/**
 * This slot is called when an object signals a resolution of the
 * textureBuffer change. Note that the depth is FIXED an cannot be changed.
 * 
 * Return : None.
 */
void QGLImage::resolutionChanged(int newWidth, int newHeight)
{
	//cout << "New resolution :" << newWidth << "x" << newHeight << endl;
	adjustTextureDimension(newWidth, newHeight);
}

/**
 * This method is called on resize event.
 * 
 * Return : None.
 */
void QGLImage::resizeGL(int width, int height)
{
	viewPortWidth = width;
	viewPortHeight = height;
	setupViewport(viewPortWidth, viewPortHeight);
}

/**
 * This method is called on paint event.
 * 
 * Return : None.
 */
void QGLImage::paintGL()
{
	QMutexLocker locker(& textureBufferMutex);
	
	setupViewport(viewPortWidth, viewPortHeight);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureName[0]);

    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, adjustedTextureWidth, adjustedTextureHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, textureBuffer);
    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2i(0, 0);

    glTexCoord2f(glTextCoordX,0);
    glVertex2i(viewPortWidth, 0);

    glTexCoord2f(glTextCoordX, glTextCoordY);
    glVertex2i(viewPortWidth, viewPortHeight);

    glTexCoord2f(0, glTextCoordY);
    glVertex2i(0, viewPortHeight);
    glEnd();
}


/**
 * This method is when opengl initialisation is needed by QT.
 * 
 * Return : None.
 */
void QGLImage::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    
    /* Delete previous texture if any. OGL ignores free on non alloc. textures */
    glDeleteTextures(1, textureName);
    glGenTextures(1,textureName);
    glBindTexture(GL_TEXTURE_2D, textureName[0]);
    if (bilinearFiltering == true)
    {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);            
}


/**
 * This method setup viewport in order to get  0,0 coord into upper
 * left corner, and width, height in bottom right with a given 
 * dimension width, height.
 * 
 * Param 1: openGL viewPort width.
 *
 * Param 2: openGL viewPort height.
 * 
 * Return : None.
 */
void QGLImage::setupViewport(int width, int height)
{
	if (height==0)	height=1;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,width,height,0.0f,-1.0f,1.0f);				
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}


/**
 * This method compute texture dimension and coordinate to fit the widget
 * dimension despite OpenGL texture constraints (size power of two).
 * Note that textureBuffer is allocated, with the adjusted texture size.
 * Before drawing, the original picture must be blitted into the 
 * adjusted texture.
 *
 * Param 1: image source width.
 * 
 * Param 2: image source height.
 *
 * Return : None.
 */
void QGLImage::adjustTextureDimension(int w, int h)
{
	QMutexLocker locker(& textureBufferMutex);
	textureWidth = w;
	textureHeight = h;

	delete [] textureBuffer; 	// Legal also if textureBuffer is NULL.
	adjustedTextureWidth  = getNearestGreaterPowerOfTwo(textureWidth);
	adjustedTextureHeight = getNearestGreaterPowerOfTwo(textureHeight);
	glTextCoordX = ((float)textureWidth / (float)adjustedTextureWidth);
	glTextCoordY = ((float)textureHeight / (float)adjustedTextureHeight);
	textureBuffer = new unsigned int[adjustedTextureWidth * adjustedTextureHeight];

	/*
	cout << "texture width = "<< textureWidth << " adjusted width = " << adjustedTextureWidth << endl;
	cout << "texture height = "<< textureHeight << " adjusted height = " << adjustedTextureHeight << endl;
	cout << "glTextCoordX = "<< glTextCoordX << endl;
	cout << "glTextCoordY = "<< glTextCoordY << endl;
	*/
}


/**
 * This image blit original pixel buffer to the size adjusted openGL
 * texture.
 * 
 * Param 1: image source pixel data (RGBA 32bits).
 * 
 * Return : None.
 */

void QGLImage::blit(unsigned int *source)
{
	QMutexLocker locker(& textureBufferMutex);
	unsigned int *scaledTexture = textureBuffer;
	int sizeLine = textureWidth * sizeof(unsigned int);

	for (int i = 0; i < textureHeight; i++)
	{
		memcpy(scaledTexture, source, sizeLine);
		source += textureWidth;
		scaledTexture += adjustedTextureWidth;
	}
	
	// Ask for refresh !
	update();
}


/**
 * OpenGL texture only accepts power of two size.
 * The QGLImage object will not have such limitation, and will hide a
 * work around to use any texture size as image source. This is done
 * by allocation the next bigger size which is a power of two, and 
 * adjust texture coordinate accodingly, to fill the object surface.
 *
 * This method calculate the nearest greater power of two texture size
 * for the given image size. e.g : image size is 259 pixel, the texture
 * size allocated will be 512.
 * 
 * Param 1: Original image resolution.
 * 
 * Return : The nearest greater size power of two.
 */ 
int QGLImage::getNearestGreaterPowerOfTwo(int size)
{
	if (size <= 2) return 2;
	if (size <= 4) return 4;
	if (size <= 8) return 8;
	if (size <= 16) return 16;
	if (size <= 32) return 32;
	if (size <= 64) return 64;
	if (size <= 128) return 128;
	if (size <= 256) return 256;
	if (size <= 512) return 512;
	if (size <= 1024) return 1024;
	if (size <= 2048) return 2048;
	return 4096;
}

/**
 * This slot is called when an bilinear filtering is turned ON.
 * 
 * Return : None.
 */
void QGLImage::bilinearFilteringOn()
{
	if (bilinearFiltering != true)
	{
		bilinearFiltering = true;
		initializeGL();
	}
}

/**
 * This slot is called when an bilinear filtering is turned OFF.
 * 
 * Return : None.
 */
void QGLImage::nearestNeighboorFilteringOn()
{
	if (bilinearFiltering == true)
	{
		bilinearFiltering = false;
		initializeGL();
	}
}

