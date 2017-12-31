//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iostream>


//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified. LOL wrong lab
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//


/*

  - projectile embeds where it collides, so return the destX and destY of the impact site
  - for obtuse angle, destY=0, destX=0. if angle=90 degrees, destY=h, destX=0
  - maybe use g=9.81 if not precise enough (use 9.8 first tho)

  - do invalid parameter checks
  - b>=0 (2nd building is never behind the first)
  - b is the distance to the left edge of the building where the target is
  - d is the distance to the target (doesn't matter for this week?)
  - w is the width of the building where the target is
  - height of target building can be negative, but height of firing building >=0
  - a test case where it will hit the wall: 
      
      h,  b,  t,  w,  m, v,    theta
      50, 30, 60, 20, 1, 18.4, 17.89


*/


const float g = -9.8;


bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) 
{
  // Your code here ...

  if (h<0 || v<0 || theta<-90 || theta>270 || m<0 || b<0 || d<0 || w<0)
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

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....

  float h = 50;
  float v = 18.4;
  float m = 1;
  float theta = 120;//17.89;        // Angle in degrees; will need to be converted by function
  float d = 10; // doesnt matter rn
  float t = 60;
  float b = 30;
  float w = 20;

  float hitsAtX;
  float hitsAtY;

  if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
    cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
  else
    cout << "Unable to calculate where projectile hits." << endl;
  return 0;
}

#endif
