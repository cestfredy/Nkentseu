#pragma once 

#include <cmath> 
#include <limits> 
#include <cstdint> 
#include <cstring> 
#include <vector>
#include <bitset>

#include "NKLogger/NkLog.h"
#include "NKContainers/String/NkStringUtils.h"

namespace NkMath { 
 
    constexpr double kEps  = 1e-9;
    constexpr float  kFEps = 1e-6f;
    
    // Vérifie que la valeur est finie (ni NaN, ni Inf)
    inline bool isFiniteValid(double x) { return std::isfinite(x); } 
    inline bool isFiniteValid(float  x) { return std::isfinite(x); } 
    
    // Teste si une valeur est proche de zéro selon une tolérance
    inline bool nearlyZero(double x, double eps = kEps)  { return std::abs(x) < eps; } 
    inline bool nearlyZero(float  x, float  eps = kFEps) { return std::abs(x) < eps; } 
    
    // Comparaison avec tolérance relative (robuste aux grandes magnitudes)
    inline bool approxEq(double a, double b, double eps = kEps) { 
        if(a == b) return true; 
        double maxAB = std::max(std::abs(a), std::abs(b)); 
        return std::abs(a - b) <= eps * std::max(1.0, maxAB); 
    } 

    // Sommation compensée pour limiter les erreurs d'arrondi
    float kahanSum(std::vector<float>& data){
        float sum  = 0.0f; 
        float comp = 0.0f;
    
        for(int i = 0; i < data.size(); i++) { 
            float y = data[i] - comp;
            float t = sum + y;
            comp    = (t - sum) - y;
            sum     = t; 
        } 
        return sum; 
    }

    // Même algorithme appliqué à un vecteur de double
    float kahanSum(std::vector<double>& data){
        float sum  = 0.0f; 
        float comp = 0.0f;
    
        for(int i = 0; i < data.size(); i++) { 
            float y = data[i] - comp;
            float t = sum + y;
            comp    = (t - sum) - y;
            sum     = t; 
        } 
        return sum; 
    }

    // Décomposition binaire IEEE 754 d'un float (signe, exposant, mantisse)
    void inspectFloat(float x){
        uint32_t bits;
        std::memcpy(&bits, &x, sizeof(bits));
        
        uint32_t sign = (bits >> 31) & 0x1;
        uint32_t exponent = (bits >> 23) & 0xFF;
        uint32_t mantissa = bits & 0x7FFFFF;
        
        logger.Info("Float {0} en format binaire IEEE 754:\n- Signe    : {1}\n- Exposant : {2}\n- Mantisse : {3}",
            x,
            sign,
            std::bitset<8>(exponent).to_string().c_str(),
            std::bitset<23>(mantissa).to_string().c_str()
        );
    }

    // Décomposition binaire IEEE 754 d'un double
    void inspectDouble(double x){
        uint64_t bits;
        std::memcpy(&bits, &x, sizeof(bits));

        uint64_t sign = (bits >> 63) & 0x1;
        uint64_t exponent = (bits >> 52) & 0x7FF;
        uint64_t mantissa = bits & 0xFFFFFFFFFFFFF;
        
        logger.Info("Double {0} en format binaire IEEE 754:\n- Signe    : {1}\n- Exposant : {2}\n- Mantisse : {3}",
            x,
            sign,        
            std::bitset<11>(exponent).to_string().c_str(),
            std::bitset<52>(mantissa).to_string().c_str()
        );
    }

    // Calcul naïf de la variance (peut être instable numériquement)
    float varianceNaive(const std::vector<float>& data){
        float sum = 0.0f, sumSq = 0.0f;

        for (float x : data) {
            sum += x;
            sumSq += x * x;
        }

        float mean = sum / data.size();
        return (sumSq / data.size()) - (mean * mean);
    }

    // Algorithme de Welford : plus stable pour le calcul de variance
    float varianceWelford(const std::vector<float>& data){
        float mean = 0.0f;
        float M2 = 0.0f;
        int n = 0;

        for (float x : data) {
            n++;
            float delta = x - mean;
            mean += delta / n;
            float delta2 = x - mean;
            M2 += delta * delta2;
        }

        return M2 / n;
    }

    // Calcule epsilon machine pour le type float
    float epsilonMachine(){
        float eps = 1.0f;

        while ((1.0f + eps / 2.0f) > 1.0f) {
            eps /= 2.0f;
        }

        return eps;
    }

}