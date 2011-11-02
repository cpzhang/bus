#ifndef _Matrix4_
#define _Matrix4_
/* http://www.songho.ca/opengl/gl_transform.html */
/*
 Class encapsulating a standard 4x4 homogeneous matrix.
 @remarks
 OGRE uses column vectors when applying matrix multiplications,
 This means a vector is represented as a single column, 4-row
 matrix. This has the effect that the transformations implemented
 by the matrices happens right-to-left e.g. if vector V is to be
 transformed by M1 then M2 then M3, the calculation would be
 M3 * M2 * M1 * V. The order that matrices are concatenated is
 vital since matrix multiplication is not commutative, i.e. you
 can get a different result if you concatenate in the wrong order.
 @par
 The generic form M * V which shows the layout of the matrix 
 entries is shown below:
 [ m[0][0]  m[0][1]  m[0][2]  m[0][3] ]   {x}
 | m[1][0]  m[1][1]  m[1][2]  m[1][3] | * {y}
 | m[2][0]  m[2][1]  m[2][2]  m[2][3] |   {z}
 [ m[3][0]  m[3][1]  m[3][2]  m[3][3] ]   {1}
 */
#include "Vector3.h"
#include <cmath>
class Matrix4
{
public:
    union
    {
        float m[4][4];
        float _m[16];
    };
    
    Matrix4();
    inline Matrix4(
                   Real m00, Real m01, Real m02, Real m03,
                   Real m10, Real m11, Real m12, Real m13,
                   Real m20, Real m21, Real m22, Real m23,
                   Real m30, Real m31, Real m32, Real m33 )
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }
    ~Matrix4();
    
    
    /** Extracts the translation transformation part of the matrix.
     */
    inline Vector3 getTrans() const
    {
        return Vector3(m[0][3], m[1][3], m[2][3]);
    }
    
    /** Builds a translation matrix
     */
    inline void makeTrans( const Vector3& v )
    {
        m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = v.x;
        m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = v.y;
        m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = v.z;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
    }
    
    inline void makeTrans( Real tx, Real ty, Real tz )
    {
        m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = tx;
        m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = ty;
        m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = tz;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
    }
    /*
     -----------------------------------------------------------------------
     Scale Transformation
     -----------------------------------------------------------------------
     */
    /** Sets the scale part of the matrix.
     */
    inline Vector3 getScale() const
    {
        return Vector3(m[0][0], m[1][1], m[2][2]);
    }
    inline void makeScale( const Vector3& v )
    {
        m[0][0] = v.x; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
        m[1][0] = 0.0; m[1][1] = v.y; m[1][2] = 0.0; m[1][3] = 0.0;
        m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = v.z; m[2][3] = 0.0;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
    }
    
    inline void makeRotateZ(Real angle)
    {
        Real c = cos(angle);
        Real s = sin(angle);
        m[0][0] = c;   m[0][1] = -s;  m[0][2] = 0.0; m[0][3] = 0.0;
        m[1][0] = s;   m[1][1] = c;   m[1][2] = 0.0; m[1][3] = 0.0;
        m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = 0.0;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
    }
    
    // near ,far should be positive distance
    // others can be negative
    /*
     E 0  A 0
     0 F  B 0
     0 0  C D
     0 0 -1 0
     */ 
    inline void makeFrustum(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        float A = (right + left) / (right - left);
        float B = (top + bottom) / (top - bottom);
        float C = - (zFar + zNear) / (zFar - zNear);
        float D = - (2 * zFar * zNear) / (zFar - zNear);
        float E = 2 * zNear / (right - left);
        float F = 2 * zNear / (top - bottom);
        
        m[0][0] = E;   m[0][1] = 0.0; m[0][2] = A; m[0][3] = 0.0;
        m[1][0] = 0.0; m[1][1] = F;   m[1][2] = B; m[1][3] = 0.0;
        m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = C; m[2][3] = D;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = -1;m[3][3] = 1.0;
    }
    
    inline void makeOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        float A = 2.0 / (right - left);
        float B = 2.0 / (top - bottom);
        float C = -2.0 / (zFar - zNear);
        float D = -(right + left) / (right - left);
        float E = -(top + bottom) / (top - bottom);
        float F = -(zFar + zNear) / (zFar - zNear);
        
        m[0][0] = A;   m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = D;
        m[1][0] = 0.0; m[1][1] = B;   m[1][2] = 0.0; m[1][3] = E;
        m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = C;   m[2][3] = F;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
    }
    static const Matrix4 ZERO;
    static const Matrix4 ZEROAFFINE;
    static const Matrix4 IDENTITY;
};
#endif
