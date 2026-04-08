#pragma once 
#include <cmath> 
#include <cassert> 
#include <cstdio> 
#include "Vec2d.h" 
 
namespace NkMath { 
    
    struct Vec3d { 
        double x, y, z; 
    
        // Constructeurs
        Vec3d() : x(0.0), y(0.0), z(0.0) {} 
        Vec3d(double x, double y, double z) : x(x), y(y), z(z) {} 
        Vec3d(const Vec2d& v, double z) : x(v.x), y(v.y), z(z) {} 
        explicit Vec3d(double s) : x(s), y(s), z(s) {}  // Initialise les 3 composantes à la même valeur
    
        // Accès indexé avec vérification des bornes
        double& operator[](int i) { 
            assert(i >= 0 && i < 3 && "Vec3d index out of bounds"); 
            return (&x)[i];  // x, y, z sont contigus en mémoire
        } 
        const double& operator[](int i) const { 
            assert(i >= 0 && i < 3 && "Vec3d index out of bounds"); 
            return (&x)[i]; 
        } 
    
        // Opérateurs arithmétiques
        Vec3d operator+(const Vec3d& o) const { return {x+o.x, y+o.y, z+o.z}; } 
        Vec3d operator-(const Vec3d& o) const { return {x-o.x, y-o.y, z-o.z}; } 
        Vec3d operator*(double s)        const { return {x*s, y*s, z*s}; } 
        Vec3d operator/(double s)        const { assert(!nearlyZero(s)); return {x/s, y/s, z/s}; } 
        Vec3d operator-()                const { return {-x, -y, -z}; } 
    
        // Opérateurs composés
        Vec3d& operator+=(const Vec3d& o) { x+=o.x; y+=o.y; z+=o.z; return *this; } 
        Vec3d& operator-=(const Vec3d& o) { x-=o.x; y-=o.y; z-=o.z; return *this; } 
        Vec3d& operator*=(double s)       { x*=s; y*=s; z*=s; return *this; } 
    
        // Norme euclidienne et normalisation
        double Norm2() const { return x*x + y*y + z*z; } 
        double Norm()  const { return std::sqrt(Norm2()); } 
    
        Vec3d Normalized() const { 
            double n = Norm(); 
            if(nearlyZero(n)) return Vec3d(0.0);  // Évite une division par zéro
            return {x/n, y/n, z/n}; 
        } 
    
        // Vérifie si le vecteur est unitaire
        bool IsNormalized(double eps = kEps) const { 
            return approxEq(Norm2(), 1.0, eps); 
        } 
    
        void Print() const { printf("Vec3d(%.6f, %.6f, %.6f)\n", x, y, z); } 
    }; 
    
    // Produit scalaire : projection et mesure d'alignement
    inline double Dot(const Vec3d& a, const Vec3d& b) { 
        return a.x*b.x + a.y*b.y + a.z*b.z; 
    } 
    
    // Produit vectoriel : vecteur perpendiculaire à a et b
    inline Vec3d Cross(const Vec3d& a, const Vec3d& b) { 
        return { 
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
        }; 
    } 
    
    // Interpolation linéaire entre deux vecteurs
    inline Vec3d Lerp(const Vec3d& a, const Vec3d& b, double t) { 
        return {a.x + (b.x-a.x)*t, a.y + (b.y-a.y)*t, a.z + (b.z-a.z)*t}; 
    } 
    
    // Multiplication scalaire avec le scalaire à gauche
    inline Vec3d operator*(double s, const Vec3d& v) { return v * s; } 

    // Comparaison composante par composante avec tolérance
    inline bool ApproxVec(const Vec3d& a, const Vec3d& b, double eps = kEps) {
        return approxEq(a.x, b.x, eps) &&
            approxEq(a.y, b.y, eps) &&
            approxEq(a.z, b.z, eps);
    }

    // Projection de a sur la direction de b
    inline Vec3d Project(const Vec3d& a, const Vec3d& b) { 
        double b2 = b.Norm2(); 
        assert(!nearlyZero(b2) && "Cannot project onto zero vector"); 
        return b * (Dot(a, b) / b2); 
    } 
    
    // Composante de a orthogonale à b
    inline Vec3d Reject(const Vec3d& a, const Vec3d& b) { 
        return a - Project(a, b); 
    } 
    
    // Garantit un layout mémoire simple et prévisible
    static_assert(sizeof(Vec3d) == 24, "Vec3d must be 24 bytes (3 doubles)"); 
    static_assert(offsetof(Vec3d, x) == 0, "x must be first"); 
    static_assert(offsetof(Vec3d, y) == 8, "y must be at offset 8"); 
    static_assert(offsetof(Vec3d, z) == 16, "z must be at offset 16"); 
 
}