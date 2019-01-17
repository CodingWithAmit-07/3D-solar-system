#include <malloc.h>
#include <math.h>
#include <fstream>
#include <string>
#include <assert.h>

#include<stdio.h>
#include<iostream>

#include<stdlib.h>
#include<GL\glut.h>

using namespace std;
using std::fstream;
using std::ios;
using std::string;
using std:: endl;


// ********** mRGBA class **********
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class mRGBA { // the name RGBA is already used by Windows

public : 
	
	unsigned char r, g, b, a;
    mRGBA() { r=g=b=0; a=255; }
    mRGBA(mRGBA &p) { r=p.r; g=p.g; b=p.b; a=p.a; }
    mRGBA(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
				   { r=rr; g=gg; b=bb; a=aa; }

    void set(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
                      { r=rr; g=gg; b=bb; a=aa; }

};

/********** RGBPixmap class ************/


//helper function
unsigned short getShort(FILE *fp)
{
	// BMP format uses little-endian integer types
	// get a 2-byte integer stored in little-endian form

	char ic;
	unsigned short ip;
	
	ic = fgetc( fp );
	ip = ic;			//first byte is little one 
	
	ic = fgetc( fp );
	ip |= ( (unsigned short) ic << 8 );	// or in high order byte
	
	return ip;

}



//helper function
unsigned long getLong(FILE *fp)
{  
	//BMP format uses little-endian integer types
	// get a 4-byte integer stored in little-endian form

	unsigned long ip = 0;
	char ic = 0;
	unsigned char uc = ic;

	ic = fgetc( fp );
	uc = ic; ip = uc;
	
	ic = fgetc( fp );
	uc = ic; 
	ip |=( (unsigned long) uc << 8 );
	
	ic = fgetc( fp );
	uc = ic; 
	ip |=( (unsigned long) uc << 16 );
	
	ic = fgetc( fp );
	uc = ic; 
	ip |=( (unsigned long) uc << 24 );
	
	return ip;

}



void fskip(FILE *fp, int num_bytes)
{

	int i;

	for( i = 0; i < num_bytes; i++ )
		fgetc( fp );

}




float fx(float x, float a0, float a1)
{

	float y, t;

	t = x / a1;

	y = a0 * exp( -( t * t ) );

	return y;

}


class RGBApixmap
{
	private:
                mRGBA *pixel;  // array of pixels

	public:
            int nRows, nCols;                       // dimensions of pixel map
	     	 RGBApixmap() { nRows = nCols = 0; pixel = 0; }
			
			 
			 RGBApixmap(int rows, int cols) 
			 {
                 nRows = rows;
                nCols = cols;
                 pixel = new mRGBA[rows * cols];
              }
		       void freeIt()
			  {
                       delete []pixel;
                        nRows = nCols = 0;
               }
               
                // *** draw this pixel map at current position

			   int getWidth() {
				   return nCols;
			   }

			   int getHeight() {
				   return nRows;
			   }

			   void display() {
				   printf("row = %d, col = %d\n", nRows, nCols);
			   }
            void mDraw() 
			{
                if (nRows == 0 || nCols == 0) 
                return;
				
				// tell OpenGL: don't align pixels with 4-byte boundaries in memory
                glPixelStorei(GL_UNPACK_ALIGNMENT,1);
                glDrawPixels(nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
				//glutSwapBuffers();
            }

		// *** read a rectangule of pixels into this pixmap

		int mRead(int x, int y, int wid, int ht)
		{
			nRows = ht;
			nCols = wid;
			pixel = new mRGBA[nRows*nCols];
			if ( !pixel ) return -1;
		// tell OpenGL: don't align pixels with 4-byte boundaries in memory
			glPixelStorei(GL_UNPACK_ALIGNMENT,1);
			glReadPixels(x, y, nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
			return 0;
			}
    

        // *** setPixel 

            void setPixel(int x, int y, mRGBA color) {

                        if ( x>=0 && x<nCols && y>=0 && y<nRows)

                                    pixel[nCols*y + x] = color;

            }

            // *** get pixel

            mRGBA getPixel(int x, int y)
			{

                        mRGBA bad(255, 255, 255, 255);

                        assert(x>=0 && x<nCols);

                        assert(y>=0 && y<nRows);

                        return pixel[nCols*y+x];

            }

			mRGBA* getPixmap(void) const
			{
				return this->pixel;
			}

		// *** read BMP file into this pixel map (see RGBpixmap.cpp)
		int readBMPFile(string fname);
		void setTexture(GLuint textureID);
		void setChromaKey(mRGBA c);
	 	void setChromaKey(int r,int g, int b);
		void makeAvgImg(RGBApixmap S, RGBApixmap D);
		void setOpacity(float opacity);
		void makeAvg2Img(RGBApixmap A, RGBApixmap B, RGBApixmap C);
		void blend(RGBApixmap S, RGBApixmap D);
		RGBApixmap makeCompositeImg(RGBApixmap A, RGBApixmap B, RGBApixmap C, float f);
		void tweening(RGBApixmap A, RGBApixmap B, RGBApixmap C);

		RGBApixmap& rotateImage(void );
		int writeBMPFile(string fname); // write this pixmap to a BMP file
		
		
}; // class RGBApixmap

 


int getAlpha(int row, int col, int nRows,int nCols,float (*p)(float, float, float), float a1) 
{

  int   rowCenter, colCenter, alpha;

  float dx, dy, dist=0.0;

 

  rowCenter = (float)nRows/2.0;

  colCenter = (float)nCols/2.0;

  dx        = row - rowCenter;

  dy        = col - colCenter;

  dist      = sqrt(dx * dx + dy * dy);

  alpha     = (int)(*p)(dist, 255.0, a1);

  return alpha;

}


void RGBApixmap::setTexture(GLuint textureID)
{

	//  glBindTexture(GL_TEXTURE_2D, textureID);
	//
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->nCols, this->nRows, 0, GL_RGBA,
	//	           GL_UNSIGNED_BYTE, this->pixel);


	glBindTexture(GL_TEXTURE_2D, textureID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, this->nCols, this->nRows, GL_RGBA, GL_UNSIGNED_BYTE, this->getPixmap());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST) ;
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST) ;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}
 

// *** Read into memory an mRGB image from an uncompressed BMP file

// return 0 on fail, 1 for Ok

int RGBApixmap::readBMPFile(string fname) 
{
   FILE *fp;

	//  long index;
	int row, col, numPadBytes, nBytesInRow;


	unsigned long fileSize;
	unsigned short reserved1;		// always 0
	unsigned short reserved2;		// always 0 
	unsigned long offBits;			// offset to image - unreliable
	unsigned long headerSize;		// always 40
	unsigned long numCols;			// number of columns in image
	unsigned long numRows;			// number of rows in image
	unsigned short planes;			// always 1 
	unsigned short bitsPerPixel;    // 8 or 24; allow 24 here
	unsigned long compression;      // must be 0 for uncompressed 
	unsigned long imageSize;		// total bytes in image 
	unsigned long xPels;			// always 0 
	unsigned long yPels;			// always 0 
	unsigned long numLUTentries;    // 256 for 8 bit, otherwise 0 
	unsigned long impColors;		// always 0 
	
	long count = 0;



	/* open the file */
	if( ( fp = fopen( fname.c_str(), "rb" ) ) == NULL )
	{
		printf( "Error opening file %s.\n", fname );
		exit( 1 );
	}



	/* check to see if it is a valid bitmap file */
	if( fgetc( fp ) != 'B' || fgetc( fp ) != 'M' )
	{
		fclose( fp );
		printf( "%s is not a bitmap file.\n", fname );
		exit( 1 );
	}



    fileSize		= getLong( fp );	
	reserved1		= getShort( fp );	// always 0
	reserved2		= getShort( fp );	// always 0 
	offBits			= getLong( fp );	// offset to image - unreliable
	headerSize		= getLong( fp );	// always 40
	numCols			= getLong( fp );	// number of columns in image
	numRows			= getLong( fp );	// number of rows in image
	planes			= getShort( fp );	// always 1 
	bitsPerPixel	= getShort( fp );	//8 or 24; allow 24 here
	compression		= getLong( fp );	// must be 0 for uncompressed 
	imageSize		= getLong( fp );	// total bytes in image 
	xPels			= getLong( fp );	// always 0 
	yPels			= getLong( fp );	// always 0 
	numLUTentries	= getLong( fp );	// 256 for 8 bit, otherwise 0 
	impColors		= getLong( fp );	// always 0 



	if( bitsPerPixel != 24 ) 
	{
		
		// error - must be a 24 bit uncompressed image
		printf( "Error bitsperpixel not 24\n" );
		exit( 1 );

	}



	// add bytes at end of each row so total # is a multiple of 4
	// round up 3 * numCols to next mult. of 4

	nBytesInRow = ( ( 3 * numCols + 3 ) / 4 ) * 4;
	numPadBytes = nBytesInRow - 3 * numCols;		// need this many



	this->nRows = numRows;		// set class's data members
	this->nCols = numCols;
	this->pixel = new mRGBA [ nRows * nCols ];	// make space for array
	
	if( !this->pixel ) return 0; // out of memory!
		count = 0;
	


	//dum;
	for( row = 0; row < numRows; row++ ) // read pixel values
	{
		for( col = 0; col < numCols; col++ )
		{
			int r, g, b;
			b = fgetc( fp );
			g = fgetc( fp );
			r = fgetc( fp );			// read bytes
			

			pixel[count].r = r;	// place them in colors
			pixel[count].g = g;
			pixel[count].b = b;
			
			pixel[count++].a = 255;

		}

		fskip( fp, numPadBytes );
	}


	fclose( fp ); 


	return 1;

} // end of readBMPFile


void RGBApixmap::setChromaKey(int r, int g, int b)
{	
	long count = 0;
	
	for(int row = 0; row <this->nCols ; row++)
		for(int col = 0; col < this->nRows; col++)
		{
			mRGBA p = pixel[count];
			

			if(p.r == r && p.g == g && p.b == b) 
				pixel[ count++ ].a = 0;
			else 
				pixel[ count++ ].a = 255;
	
		}
}


/* ******************************************************************************* */



void RGBApixmap::setOpacity(float opacity)
{

	long count = 0;
	int i, j, c;

	//this->nRows = this->nCols = D.nRows;
	//this->pixel = (mRGBA*) malloc(4 * this->nRows * this->nCols);

	for (i = 0; i < this->nRows; i++)
		for (j = 0; j < this->nCols; j++)
		{

			//this->pixel[count].r = 255;
			//this->pixel[count].g = 128;
			//this->pixel[count++].b = 2555;
			this->pixel[count++].a = 128;
		}

}

void RGBApixmap::makeAvgImg(RGBApixmap S, RGBApixmap D)
{
	long count = 0;
	int i, j, c;

	float a;

	this->nRows = this->nCols = D.nRows;
	this->pixel = (mRGBA*)malloc(4 * this->nRows * this->nCols);

	for (i = 0; i < this->nRows; i++)
		for (j = 0; j < this->nCols; j++)
		{
			float temp = (float)S.pixel[count].a;
			if (temp >= 0) {
				a = temp / 255;

			//	cout << a << endl;

				D.pixel[count].r = (unsigned char)((a * S.pixel[count].r) + ((1 - a)*D.pixel[count].r));
				D.pixel[count].g = (unsigned char)((a * S.pixel[count].g) + ((1 - a)*D.pixel[count].g));
				D.pixel[count++].b = (unsigned char)((a * S.pixel[count].b) + ((1 - a)*D.pixel[count].b));
			}
				

		}
}

void RGBApixmap::blend(RGBApixmap S, RGBApixmap D)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	makeAvgImg(S, D);
	D.mDraw();
}

void RGBApixmap::setChromaKey(mRGBA c)
{


	long count = 0;
	int i, j;

	for (i = 0; i < this->nRows; i++)
		for (j = 0; j < this->nCols; j++)
		{
			mRGBA p = this->pixel[count];
			if (p.r == c.r && p.g == c.g && p.b == c.b)
			{
			//	cout << " i m in" << endl;
				this->pixel[count++].a = 0;
			//	cout << p.r << p.g << p.b << endl;



			}
			else
			{
				this->pixel[count++].a = 255;
				//cout<<" i m out" << endl;
			}
		}

}
void RGBApixmap::makeAvg2Img(RGBApixmap A, RGBApixmap B, RGBApixmap C)
{
	long count = 0;
	int i, j, c;

	this->nRows = this->nCols = A.nRows;
	this->pixel = (mRGBA *)malloc(4 * this->nRows * this->nCols);

	for (i = 0; i < this->nRows; i++)
		for (j = 0; j < this->nCols; j++)
		{

			this->pixel[count].r = (A.pixel[count].r + B.pixel[count].r) / 2;
			this->pixel[count].g = (A.pixel[count].g + B.pixel[count].g) / 2;
			this->pixel[count++].b = (A.pixel[count].b + B.pixel[count].b) / 2;

		}
}


RGBApixmap RGBApixmap::makeCompositeImg(RGBApixmap A, RGBApixmap B, RGBApixmap C, float f)
{
	long count = 0;
	int i, j, c;

	this->nRows = this->nCols = A.nRows;
	this->pixel = (mRGBA *)malloc(4 * this->nRows * this->nCols);

	for (i = 0; i < this->nRows; i++)
		for (j = 0; j < this->nCols; j++)
		{
			//printf("VAL = %d\n", (((1 - f)* (float)A.pixel[count].r) + (f *(float)B.pixel[count].r)));
			C.pixel[count].r = (unsigned char)(((1 - f)* (float)A.pixel[count].r) + (f *(float)B.pixel[count].r));
			C.pixel[count].g = (unsigned char)(((1 - f)* (float)A.pixel[count].g) + (f *(float)B.pixel[count].g));
			C.pixel[count++].b = (unsigned char)(((1 - f)* (float)A.pixel[count].b) + (f * (float)B.pixel[count].b));

		}
	return C;
}


void RGBApixmap::tweening(RGBApixmap A, RGBApixmap B, RGBApixmap C) {
	
	for (double f = 0; f < 0.8; f+= 0.001)
	{
		makeCompositeImg(A, B, C, f);
		C.mDraw();
	//	glFlush();
		glutSwapBuffers();
	}
	//glutSwapBuffers();

}

