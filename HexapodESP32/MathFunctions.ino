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


FLOAT3 RotatePoint(float point[3],float pivot[3], float thetaRad)
{
  float px = (point[0] - pivot[0]) * cos(thetaRad) - (point[1] - pivot[1]) * sin(thetaRad) + pivot[0];  // applying a rotation matrix across z and centering to pivot over 'start': R(pos - pivot) + pivot
  float py = (point[0] - pivot[0]) * sin(thetaRad) + (point[1] - pivot[1]) * cos(thetaRad) + pivot[1];
  float pz = point[2];

  FLOAT3 newPoint = {px, py, pz};
  return newPoint;
}



















  
