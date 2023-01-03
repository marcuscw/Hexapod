#include "StructsAndFuncts.h"


 /*  
 * This function will multiply two homogeneous matricies ('A' and 'B') and the product write onto a variable ('C')
 * It is hard coded as the matricies will be constant and it is more optimal than using loops
 * 
 *  --example--
 *  A = [[1,2],[3,4]]
 *  B = [[1,0],[0,1]]
 *  
 *  dotProduct = [[1,2][3,4]]
 *  
 *  --see also--
 *  https://www.mathsisfun.com/algebra/matrix-multiplying.html
 *  https://www.youtube.com/watch?v=dQw4w9WgXcQ  <-- This helped me the most out of everything
 */


FLOAT3 RotatePoint(FLOAT3 point, FLOAT3 pivot, float thetaRad)
{
  float px = (point.f[0] - pivot.f[0]) * cos(thetaRad) - (point.f[1] - pivot.f[1]) * sin(thetaRad) + pivot.f[0];  // applying a rotation matrix across z and centering to pivot over 'start': R(pos - pivot) + pivot
  float py = (point.f[0] - pivot.f[0]) * sin(thetaRad) + (point.f[1] - pivot.f[1]) * cos(thetaRad) + pivot.f[1];
  float pz = point.f[2];

  FLOAT3 newPoint = {px, py, pz};
  return newPoint;
}

FLOAT3 MeanO(FLOAT3 point1, FLOAT3 point2) 
{
  // returns the point directly inbetween 2 other points by finding their mean
  
  float px = (point1.f[0] + point2.f[0]) / 2;  // the average of the x positions
  float py = (point1.f[1] + point2.f[1]) / 2;  // the average of the x positions
  float pz = (point1.f[2] + point2.f[2]) / 2;

  FLOAT3 newPoint = {px, py, pz};
  return newPoint;
}



















  
