#pragma once 
#include "Mat3d.h" 
#include <cmath> 
 
namespace NkMath { 
    
    struct Quat { 
        // Quaternion : w = partie réelle, (x,y,z) = partie vectorielle
        double w, x, y, z;
    
        Quat() : w(1), x(0), y(0), z(0) {}
        Quat(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {} 
    
        double Norm2() const { return w*w + x*x + y*y + z*z; } 
        double Norm()  const { return std::sqrt(Norm2()); } 

        static Quat Identity() { return {1, 0, 0, 0}; }
    
        // Normalisation pour obtenir un quaternion unitaire (rotation valide)
        Quat Normalized() const { 
            double n = Norm(); 
            assert(!nearlyZero(n)); 
            return {w/n, x/n, y/n, z/n}; 
        } 
    
        // Conjugué : inverse la composante vectorielle
        Quat Conjugate() const { return {w, -x, -y, -z}; } 
    
        // Inverse général (équivalent au conjugué si unitaire)
        Quat Inverse() const { 
            double n2 = Norm2(); 
            assert(!nearlyZero(n2)); 
            return {w/n2, -x/n2, -y/n2, -z/n2}; 
        } 
    
        // Produit de Hamilton (composition de rotations)
        Quat operator*(const Quat& o) const { 
            return { 
                w*o.w - x*o.x - y*o.y - z*o.z, 
                w*o.x + x*o.w + y*o.z - z*o.y, 
                w*o.y - x*o.z + y*o.w + z*o.x, 
                w*o.z + x*o.y - y*o.x + z*o.w 
            }; 
        } 
    }; 
    
    // Comparaison de quaternions via produit scalaire (invariant au signe)
    inline bool ApproxQuat(const Quat& q1, const Quat& q2, double eps = kEps) {
        double dot = q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z;
        return std::fabs(dot) > 1.0 - eps;
    }
        
    // Conversion axe-angle → quaternion
    inline Quat FromAxisAngle(const Vec3d& axis, double angleRad) { 
        Vec3d n  = axis.Normalized(); 
        double s = std::sin(angleRad / 2.0); 
        double c = std::cos(angleRad / 2.0); 
        return {c, n.x*s, n.y*s, n.z*s}; 
    } 
    
    // Rotation d'un vecteur par quaternion (forme optimisée)
    inline Vec3d Rotate(const Quat& q, const Vec3d& v) { 
        Vec3d qVec  = {q.x, q.y, q.z}; 
        Vec3d uv    = Cross(qVec, v); 
        Vec3d uuv   = Cross(qVec, uv); 
        return v + (uv * (2.0 * q.w)) + (uuv * 2.0); 
    } 
 
    // SLERP : interpolation sphérique entre deux rotations
    inline Quat Slerp(Quat a, Quat b, double t) { 
        // Angle entre quaternions via produit scalaire
        double cosAngle = a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z; 
    
        // Correction pour suivre le chemin le plus court
            b.w = -b.w; b.x = -b.x; b.y = -b.y; b.z = -b.z; 
            cosAngle = -cosAngle; 
        } 
    
        double k0, k1; 
        if(cosAngle > 0.9999) { 
            // Cas quasi identique : fallback vers LERP
            k0 = 1.0 - t; 
            k1 = t; 
        } else Near-identity: fallback to linear interpolation to avoid numerical instability
            k0 = 1.0 - t; 
            k1 = t; 
        } else { 
            // Interpolation sphérique
            k0 = std::sin((1.0-t) * angle) / sinAngle; 
            k1 = std::sin(t       * angle) / sinAngle; 
        } 
    
        return Quat { 
            k0*a.w + k1*b.w, 
            k0*a.x + k1*b.x, 
            k0*a.y + k1*b.y, 
            k0*a.z + k1*b.z 
        }.Normalized(); 
    }

    // Interpolation linéaire simple (moins précise que SLERP)
    Quat Lerp(Quat a, Quat b, double t){
        return Quat(
            a.w + t*(b.w-a.w),
            a.x + t*(b.x-a.x),
            a.y + t*(b.y-a.y),
            a.z + t*(b.z-a.z)
        ).Normalized();
    }

    // Conversion quaternion → matrice de rotation 3x3
    Mat3d ToMat3(const Quat& q) { 
        double xx=q.x*q.x, yy=q.y*q.y, zz=q.z*q.z; 
       Convert quaternion to 3x3 rotation matrix for shader upload
        double wx=q.w*q.x, wy=q.w*q.y, wz=q.w*q.z; 
        
        Mat3d R; 
        R(0,0) = 1 - 2 * (yy + zz); 
        R(0,1) = 2 * (xy - wz); 
        R(0,2) = 2 * (xz + wy); 
        R(1,0) = 2 * (xy + wz); 
        R(1,1) = 1 - 2 * (xx + zz); 
        R(1,2) = 2 * (yz - wx); 
        R(2,0) = 2 * (xz - wy); 
        R(2,1) = 2 * (yz + wx); 
        R(2,2) = 1 - 2 * (xx + yy); 
        return R; 
    } 
    
    // Conversion matrice → quaternion (méthode stable)
    Quat FromMat3(const Mat3d& R) { 
       Convert 3x3 rotation matrix to quaternion using Shepperd's numerically stable method
        Quat q; 
        if(trace > 0) { 
            double s = 0.5 / std::sqrt(trace + 1.0); 
            q.w = 0.25 / s; 
            q.x = (R(2,1) - R(1,2)) * s; 
            q.y = (R(0,2) - R(2,0)) * s; 
            q.z = (R(1,0) - R(0,1)) * s; 
        } else if(R(0,0) > R(1,1) && R(0,0) > R(2,2)) { 
            double s = 2.0 * std::sqrt(1.0 + R(0,0) - R(1,1) - R(2,2)); 
            q.wDominant x component of matrix1,2)) / s; 
            q.x = 0.25 * s; 
            q.y = (R(0,1) + R(1,0)) / s; 
            q.z = (R(0,2) + R(2,0)) / s; 
        } 
        else if (R(1,1) > R(2,2)) { 
            double s = 2.0 * std::sqrt(1.0 + R(1,1) - R(0,0) - R(2,2)); 
            q.w = (R(0,2) - R(2,0)) / s; 
            q.x = (R(0,1) + R(1,0)) / s; 
            q.y = 0.25 * s; 
            q.z = (R(1,2) + R(2,1)) / s; 
        } else { 
            double s = 2.0 * std::sqrt(1.0 + R(2,2) - R(0,0) - R(1,1)); 
            q.w = (R(1,0) - R(0,1)) / s; 
            q.x = (R(0,2) + R(2,0)) / s; 
            q.y = (R(1,2) + R(2,1)) / s; 
            q.z = 0.25 * s; 
        }
        return q.Normalized(); 
    }

} // namespace NkMath