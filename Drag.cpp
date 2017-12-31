//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
#include <cmath>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN() 
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
              const float d, const float step, const float k,
              const float t, const float b, const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

const float g = -9.8;


bool f1(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY, const float k) 
{
  // Your code here ...

  if (h<0 || v<0 || theta<-90 || theta>270 || m<0 || b<0 || d<0 || w<0 || k<0)
    return false;
  
  float angle = theta*3.14159265/180.0;

  if (theta>90)
  {
    float timesy0 = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g;
    destY=0;
    destX=v*timesy0*cos(angle);
    return true;
  }
  else if (theta==90 || v==0)
  {
    destY=h;
    destX=0;
    return true;
  }
  
  // three cases, t>0, t<0 and t==0

  if (t>0)
  {
    float timexb = b/(v*cos(angle));
    float sy = h+v*sin(angle)*timexb+(g/2)*timexb*timexb;
    if (0<sy && sy<=t)
    {
      // WILL land on left wall
      destY=sy;
      destX=b;
      return true;
    }
    if (sy<0)
    {
      // doesnt even make it to building; lands on left of building
      // so instead, calculate the time it takes to get sy=0
      // then calculate sx from that time
      float timesy0 = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g;
      destY=0;
      destX=v*timesy0*cos(angle);
      return true;
    }
    if (sy>t)
    {
      // time sy=t
      float timesyt = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*(h-t)))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*(h-t)))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*(h-t)))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*(h-t)))/g;
      float sx = v*timesyt*cos(angle);
      if (sx<=(b+w))
      {
        destY=t;
        destX=sx;
        return true;
      }
      else
      {
        float timesy0 = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g;
        destY=0;
        destX=v*timesy0*cos(angle);
        return true;
      }
    }
  }
  else if (t<0)
  {
    float timexbw = (b+w)/(v*cos(angle));
    float sy = h+v*sin(angle)*timexbw+(g/2)*timexbw*timexbw;
    if (sy>0)
    {
      float timesy0 = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g;
      destY=0;
      destX=v*timesy0*cos(angle);
      return true;
    }
    if (sy>=t && sy<0)
    {
      destY=h+v*timexbw*sin(angle)+(g/2)*timexbw*timexbw;
      destX=b+w;
      return true;
    }
    if (sy<t)
    {
      float timexb = b/(v*cos(angle));
      float sy = h+v*sin(angle)*timexb+(g/2)*timexb*timexb;

      if (sy<=0)
      {
        float timesy0 = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g;
        destY=0;
        destX=v*timesy0*cos(angle);
        return true;
      }
      if (sy>0)
      {
        destY=t-h;
        float timesyt = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*(2*h-t)))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*(2*h-t)))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*(2*h-t)))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*(2*h-t)))/g;
        destX = v*timesyt*cos(angle);
        return true;
      }
    }
  }
  else
  {
      float timesy0 = ( (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g > (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g ) ? (-v*sin(angle)+sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g: (-v*sin(angle)-sqrt((v*sin(angle))*(v*sin(angle))-2*g*h))/g;
      destY=0;
      destX=v*timesy0*cos(angle);
      return true;
  }
}

float f2(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w) 
{
  float x=0, y=0;
  if (f1(h,v,m,theta,d,t,b,w,x,y))
    return (d - x);
  else
    return std::numeric_limits<float>::quiet_NaN();
}

float bisectionHelper(const float left, const float right,
          const float precision, const int count, const float h, const float d, const float t, 
          const float b, const float w, const float theta)
{
                 
  float midpoint = (right + left)/2;    
  float currentPrecision = f2(h,midpoint,0,theta,d,t,b,w);
  //float currentInterval = right - left;
  
  if(currentPrecision < 0)
      currentPrecision *= -1;
  
  if(currentPrecision <= precision || count == 0)
      return midpoint;
  if((f2(h,midpoint,0,theta,d,t,b,w)*f2(h,right,0,theta,d,t,b,w)) < 0)
      return bisectionHelper(midpoint, right, precision, count-1,h,d,t,b,w,theta);
  else 
      return bisectionHelper(left, midpoint, precision, count-1,h,d,t,b,w,theta);                      
}

float bisection(const float left, const float right,
    const float precision, const float h, const float d, const float t, const float b, const float w, const float theta) 
{        
  
  float midpoint = (right + left)/2;

  if (left >= right)
      return std::numeric_limits<float>::quiet_NaN();
  // if((f2(h,midpoint,0,left,d,t,b,w) > 0 && f2(h,midpoint,0,right,d,t,b,w) > 0 ) || (f2(h,midpoint,0,right,d,t,b,w) < 0 && f2(h,midpoint,0,left,d,t,b,w) < 0))
  //     return std::numeric_limits<float>::quiet_NaN();
  if(precision < 0)
      return std::numeric_limits<float>::quiet_NaN();
  
  float retf = f2(h,midpoint,0,left,d,t,b,w); 
  if(retf != retf){ 
      return std::numeric_limits<float>::quiet_NaN(); 
  }
  else if (retf == 0) { 
      return left; 
  } 
  retf = f2(h,midpoint,0,right,d,t,b,w); 
  if(retf != retf){ 
      return std::numeric_limits<float>::quiet_NaN(); 
  } 
  else if (retf == 0) { 
    return right; 
  } 
  
  float mid = bisectionHelper(left, right, precision, 10000, h, d, t, b, w, theta);
  return mid;
}

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float step, const float k,
              const float t, const float b, const float w, float& v) 
{
  
  float v = 5;
  float destY = t-h;
  float destX = d;
  float Dy, Dx, vx, vy;

  float angle = theta*M_PI/180;


  if (k==0)
  {
    if (h<0 || theta<-90 || theta>270 || m<0 || b<0 || d<0 || w<0)
    return false;

    float left = 0; 
    float right = 100;
  
    float precision = 0.001;
  
    v = bisection(left,right,precision,h,d,t,b,w,theta);  
  
    return true;
  }
}
		

#ifndef MARMOSET_TESTING
int main() {
	
  // Some test driver code here ....
  float h = 50;
  float d = 60;
  float b = 40;
  float t = 30;
  float w = 30;
  float m = 1;
  float step = 0.01;
  float k = 0.5;
  float theta = 45; // Angle in degrees;
  float v = 25;	

  cout << endl << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity" << endl << endl;
  }
    
  return 0;
}
#endif
