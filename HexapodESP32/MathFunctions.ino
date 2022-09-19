#include "StructsAndFuncts.h"

void MatMul(float B[4][4], float A[4][4], float C[4][4]) 
{ 
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
 
  C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0] + A[0][3]*B[3][0];
  C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1] + A[0][3]*B[3][1];
  C[0][2] = A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2] + A[0][3]*B[3][2];
  C[0][3] = A[0][0]*B[0][3] + A[0][1]*B[1][3] + A[0][2]*B[2][3] + A[0][3]*B[3][3];
  
  C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0] + A[1][3]*B[3][0];
  C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1] + A[1][3]*B[3][1];
  C[1][2] = A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2] + A[1][3]*B[3][2];
  C[1][3] = A[1][0]*B[0][3] + A[1][1]*B[1][3] + A[1][2]*B[2][3] + A[1][3]*B[3][3];
  
  C[2][0] = A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0] + A[2][3]*B[3][0];
  C[2][1] = A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1] + A[2][3]*B[3][1];
  C[2][2] = A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2] + A[2][3]*B[3][2];
  C[2][3] = A[2][0]*B[0][3] + A[2][1]*B[1][3] + A[2][2]*B[2][3] + A[2][3]*B[3][3];
  
  C[3][0] = A[3][0]*B[0][0] + A[3][1]*B[1][0] + A[3][2]*B[2][0] + A[3][3]*B[3][0];
  C[3][1] = A[3][0]*B[0][1] + A[3][1]*B[1][1] + A[3][2]*B[2][1] + A[3][3]*B[3][1];
  C[3][2] = A[3][0]*B[0][2] + A[3][1]*B[1][2] + A[3][2]*B[2][2] + A[3][3]*B[3][2];
  C[3][3] = A[3][0]*B[0][3] + A[3][1]*B[1][3] + A[3][2]*B[2][3] + A[3][3]*B[3][3];
}

void PrintMat(float mat[4][4])
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0  ; j < 4; j++) 
    {
      Serial.print(mat[i][j]);
      Serial.print("   ");
    }
    Serial.println("");
  }
  Serial.println("");
}

FLOAT3 RotatePoint(float point[3],float pivot[3], float thetaRad)
{
  float px = (point[0] - pivot[0]) * cos(thetaRad) - (point[1] - pivot[1]) * sin(thetaRad) + pivot[0];  // applying a rotation matrix across z and centering to pivot over 'start': R(pos - pivot) + pivot
  float py = (point[0] - pivot[0]) * sin(thetaRad) + (point[1] - pivot[1]) * cos(thetaRad) + pivot[1];
  float pz = point[2];

  FLOAT3 newPoint = {px, py, pz};
  return newPoint;
}



















  
