#pragma once 
#include "Vec3d.h"

namespace NkMath { 

    // Base orthonormée (vecteurs unitaires et orthogonaux entre eux)
    struct OrthoBasis { 
        Vec3d u, v, w;
    }; 
    
    // Orthogonalisation de Gram-Schmidt
    // Transforme 3 vecteurs quelconques en une base orthonormée
    inline OrthoBasis GramSchmidt(Vec3d a, Vec3d b, Vec3d c) { 

        // 1. Normalisation du premier vecteur
        Vec3d u = a.Normalized(); 
        assert(!nearlyZero(u.Norm()) && "First vector is zero"); 
    
        // 2. Suppression de la projection de b sur u puis normalisation
        Vec3d v = (b - Project(b, u)).Normalized(); 
        assert(!nearlyZero(v.Norm()) && "Vectors are collinear"); 
    
        // 3. Suppression des projections sur u et v puis normalisation
        Vec3d w = (c - Project(c, u) - Project(c, v)).Normalized(); 
        assert(!nearlyZero(w.Norm()) && "Vectors are coplanar"); 
    
        return {u, v, w}; 
    }

}