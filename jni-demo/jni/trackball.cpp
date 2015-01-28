#include "trackball.h"

#include <gtl/matrix4.hpp>

#ifdef WIN32
#include <gl/glut.h>
#elif defined(ES_ANDROID) || defined(__APPLE__)
#include <GLES/gl.h>
#endif

#include <math.h>

#define  INVSQRT2 1.0f/sqrt(2.0)  

void Trackball::mapToSphere(gtl::Vec3f &v)
{        
	float len2;         
	v.x() = ( 2 * v.x() ) / (float)( width - 1 )-1;        
	v.y() = 1 - ( 2 * v.y() ) / (float)( height - 1 );        
	v.z() = 0;        

	len2 = v.length();
	if( len2<INVSQRT2 )  
		v.z() = sqrt(1.0f-len2); // We are on the sphere        
	else                
		v.z() = 1.0f/(2*sqrt(len2)); // On the hyperbole 
}  

void Trackball::Tracking(int x, int y)
{        
	gtl::Quatf q;    
	gtl::Vec3f endVector(x, y, 0);       

	mapToSphere(endVector);        

	q.setValue(startVector, endVector); 
	orientation = q * startOrientation; 
	orientation.normalize();
} 

void Trackball::BeginTracking(int x, int y) 
{     
	startVector = gtl::Vec3f(x, y, 0); 
	startOrientation = orientation;        
	mapToSphere(startVector); 
} 

gtl::Matrix4f Trackball::To4x4RotationMatrix()
{        
	return orientation.getMatrix();
}  

void Trackball::toOpenGL()
{
	GLfloat matrix[16];
	gtl::Matrix4f mat = orientation.getMatrix();
	glMultMatrixf( mat.getData() );
} 
