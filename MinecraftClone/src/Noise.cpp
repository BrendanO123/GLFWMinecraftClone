

#include "Noise.h"

using namespace noise;

float Noise :: SinglePerlin(int seed, float x, float y){

    int xi = FastFloor(x); //floor x
    int yi = FastFloor(y); //floor y

    float xf0 = (float)(x - xi); //fract x, distance from left wall
    float yf0 = (float)(y - yi); //fract y, distance from ceiling
    float xf_1 = xf0 - 1; //distance from right wall
    float yf_1 = yf0 - 1; //distance from floor

    float xs = InterpQuintic(xf0); //interp
    float ys = InterpQuintic(yf0); //interp

    xi *= PrimeX; //Hashing for left two grad vectors
    yi *= PrimeY; //Hashing for upper two left grad vectors
    int xi_1 = xi + PrimeX; //Hashing for right two grad vectors
    int yi_1 = yi + PrimeY; //Hashing for bottom two grad vectors

    float upper = Lerp(GradCoord(seed, xi, yi, xf0, yf0), GradCoord(seed, xi_1, yi, xf_1, yf0), xs); //lerp between values from upper vecs
    float lower = Lerp(GradCoord(seed, xi, yi_1, xf0, yf_1), GradCoord(seed, xi_1, yi_1, xf_1, yf_1), xs); //lerp between values from lower vecs

    return Lerp(upper, lower, ys) * 1.4247691104677813f; //lerp between upper and lower and *=(num>=sqrt(2))
        //1/sqrt(2) is theoretical maximum for perlin noise before multiplication
        //to make maximum 1, multiply by sqrt(2). 
        //However, if the perfect conditions for 1/sqrt(2) are not possible with your set of grad vector directions
            //(pi/4 multiples are needed), 
        //your grad vecs are slightly shorter than normalized,
        //or the psuedo-rand num generator doesn't allow the grad and displacement vectors to be parrellel

        //then the max will be below 1/sqrt(2) and the factor (seen above at the end of the return) should be > sqrt(2)
}

glm :: vec3 Noise :: analyticalPerlin(int seed, float x, float y){
    int xi = FastFloor(x); //floor x
    int yi = FastFloor(y); //floor y

    float xf0 = (float)(x - xi); //fract x, distance from left wall
    float yf0 = (float)(y - yi); //fract y, distance from ceiling
    float xf_1 = xf0 - 1; //distance from right wall
    float yf_1 = yf0 - 1; //distance from floor

    float xs = InterpQuintic(xf0); //interp
    float ys = InterpQuintic(yf0); //interp

    float dx = d_dxInterp(xf0);
    float dy = d_dxInterp(yf0);

    xi *= PrimeX; //Hashing for left two grad vectors
    yi *= PrimeY; //Hashing for upper two left grad vectors
    int xi1 = xi + PrimeX; //Hashing for right two grad vectors
    int yi1 = yi + PrimeY; //Hashing for bottom two grad vectors

    int hash = Hash(seed, xi, yi); glm :: vec2 g00 = glm :: vec2(Gradients2D[hash], Gradients2D[hash | 1]); //grad vec a (0, 0)
    hash = Hash(seed, xi1, yi); glm :: vec2 g10 = glm :: vec2(Gradients2D[hash], Gradients2D[hash | 1]); //grad vec b (1, 0)
    hash = Hash(seed, xi, yi1); glm :: vec2 g01 = glm :: vec2(Gradients2D[hash], Gradients2D[hash | 1]); //grad vec c (0, 1)
    hash = Hash(seed, xi1, yi1); glm :: vec2 g11 = glm :: vec2(Gradients2D[hash], Gradients2D[hash | 1]); // grad vec d (1, 1)

    float d_dx =    g00.x * (1 - xs - ys + (xs * ys)) + (xf0 * g00.x + yf0 * g00.y) * (dx * (ys - 1)) + //a
                    g10.x * (xs * (1 - ys)) + (xf_1 * g10.x + yf0 * g10.y) * (dx * (1 - ys)) + //b
                    g01.x * (ys * (1 - xs)) + (xf0 * g01.x + xf_1 * g01.y) * (xs * (-dx)) + //c
                    g11.x * (xs * ys) + (xf_1 * g11.x + yf_1 * g11.y) * (dx * ys); //d

    float d_dy =    g00.y * (1 - xs - ys + (xs * ys)) + (xf0 * g00.x + yf0 * g00.y) * (dy * (xs - 1)) + //a
                    g10.y * (xs * (1 - ys)) + (xf_1 * g10.x + yf0 * g10.y) * (-xs * dy) + //b
                    g01.y * (ys * (1 - xs)) + (xf0 * g01.x + xf_1 * g01.y) * (dy * (1 - xs)) + //c
                    g11.y * (xs * ys) + (xf_1 * g11.x + yf_1 * g11.y) * (dy * xs); //d

    return glm :: vec3(
        Lerp(
            Lerp(g00.x * xf0 + g00.y * yf0, g10.x * xf_1 + g10.y * yf0, xs),
            Lerp(g01.x * xf0 + g01.y * yf_1, g11.x * xf_1 + g11.y * yf_1, xs),
            ys
        ) * 1.4247691104677813f, dx, dy);
}