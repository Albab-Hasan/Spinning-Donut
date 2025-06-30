# Mathematical Explanation of the Spinning Donut

This document provides a detailed explanation of the mathematics behind the spinning donut animation.

## Torus Geometry

A torus is a 3D shape that resembles a donut. It can be defined parametrically using two angles:
- θ (theta): angle around the tube (0 to 2π)
- φ (phi): angle around the central axis (0 to 2π)

For a torus with major radius R (distance from center of tube to center of torus) and minor radius r (radius of the tube itself), the parametric equations are:

```
x = (R + r·cos(θ)) · cos(φ)
y = (R + r·cos(θ)) · sin(φ)
z = r·sin(θ)
```

In our code, we've simplified by using R=2 and r=1.

## Rotation

We apply two rotations to the torus:
1. Rotation around the X-axis by angle A
2. Rotation around the Y-axis by angle B

The rotation matrices are applied to transform the 3D coordinates.

## Projection

After rotation, we project the 3D points onto a 2D plane using a simple perspective projection:

```
x_projected = K1 * x / (K2 + z)
y_projected = K1 * y / (K2 + z)
```

Where K1 and K2 are constants that control the projection.

## Lighting

The lighting calculation is based on the surface normal of each point on the torus. The normal vector is calculated and then the dot product with the light direction gives us the lighting intensity.

The formula used is:
```
L = N·V
```
Where:
- L is the lighting intensity
- N is the surface normal vector
- V is the light direction vector

## ASCII Rendering

Finally, we map the calculated lighting intensity to ASCII characters. Characters with more "ink" represent surfaces facing the light source, while characters with less "ink" represent surfaces facing away from the light.

The character set used is: `.,-~:;=!*#$@`

## Code Implementation

In the code, these mathematical concepts are implemented in a compact way:

1. We iterate through the parametric angles θ and φ
2. Calculate the 3D coordinates of each point on the torus
3. Apply rotation transformations
4. Calculate the lighting using the surface normal
5. Project the 3D point to 2D screen coordinates
6. Map the lighting value to an ASCII character
7. Render to the screen
8. Increment the rotation angles and repeat

This creates the illusion of a spinning 3D donut in the terminal using only ASCII characters.
