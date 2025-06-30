#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main()
{
  // Rotation angles
  float A = 0, B = 0;
  float i, j;
  int k;

  // z-buffer to store depth information
  float z[1760];
  // Output buffer for ASCII characters
  char b[1760];

  // Clear the screen using ANSI escape sequence
  printf("\x1b[2J");

  // Infinite loop for animation
  for (;;)
  {
    // Clear the buffers
    memset(b, 32, 1760); // Fill with spaces (ASCII 32)
    memset(z, 0, 7040);  // Clear z-buffer (7040 = 1760*4 bytes for float)

    // Loop through angles phi (j) and theta (i)
    // These represent the parametric coordinates on the torus
    for (j = 0; j < 6.28; j += 0.07)
    { // 6.28 ≈ 2π
      for (i = 0; i < 6.28; i += 0.02)
      {
        // Calculate 3D coordinates and apply rotation

        // sin(theta)
        float c = sin(i);
        // cos(phi)
        float d = cos(j);
        // sin(A) - rotation around X axis
        float e = sin(A);
        // sin(phi)
        float f = sin(j);
        // cos(A) - rotation around X axis
        float g = cos(A);
        // Distance from center of tube to center of torus (R + r*cos(theta))
        float h = d + 2; // 2 is the major radius R

        // Calculate depth (1/z) after rotation
        // This is a simplified perspective projection formula
        float D = 1 / (c * h * e + f * g + 5); // 5 is the distance from viewer

        // cos(theta)
        float l = cos(i);
        // cos(B) - rotation around Y axis
        float m = cos(B);
        // sin(B) - rotation around Y axis
        float n = sin(B);

        // Calculate x, y coordinates after rotation
        float t = c * h * g - f * e;

        // Project 3D coordinates to 2D screen space
        // 40, 30 are scaling factors, 12, 15 are offsets
        int x = 40 + 30 * D * (l * h * m - t * n);
        int y = 12 + 15 * D * (l * h * n + t * m);

        // Calculate buffer position (x, y to 1D array index)
        int o = x + 80 * y;

        // Calculate luminance using the surface normal
        // N ranges from -8 to 8 based on the angle between
        // the surface normal and the light direction
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

        // Only render if point is within screen bounds and is closer than
        // any previously rendered point at this position
        if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
        {
          // Update z-buffer with new depth
          z[o] = D;
          // Map luminance value to ASCII character
          // Characters with more "ink" represent surfaces facing the light
          b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
        }
      }
    }

    // Move cursor to top-left corner using ANSI escape sequence
    printf("\x1b[H");

    // Print the buffer to screen
    for (k = 0; k < 1761; k++)
    {
      // Print character or newline every 80 characters
      putchar(k % 80 ? b[k] : 10); // 10 is ASCII for newline
    }

    // Update rotation angles for next frame
    A += 0.04;
    B += 0.02;

    // Sleep for 30 milliseconds to control animation speed
    usleep(30000);
  }
  return 0;
}
