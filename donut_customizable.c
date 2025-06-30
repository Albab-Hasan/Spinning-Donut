#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

// Default parameters
#define DEFAULT_R 2.0        // Major radius
#define DEFAULT_r 1.0        // Minor radius
#define DEFAULT_K1 30.0      // Projection constant 1
#define DEFAULT_K2 5.0       // Projection constant 2
#define DEFAULT_SPEED_A 0.04 // Rotation speed A
#define DEFAULT_SPEED_B 0.02 // Rotation speed B
#define DEFAULT_DELAY 30000  // Delay in microseconds

void printUsage(char *programName)
{
  printf("Usage: %s [options]\n", programName);
  printf("Options:\n");
  printf("  -R <value>  Major radius (default: %.1f)\n", DEFAULT_R);
  printf("  -r <value>  Minor radius (default: %.1f)\n", DEFAULT_r);
  printf("  -K1 <value> Projection constant 1 (default: %.1f)\n", DEFAULT_K1);
  printf("  -K2 <value> Projection constant 2 (default: %.1f)\n", DEFAULT_K2);
  printf("  -A <value>  Rotation speed A (default: %.2f)\n", DEFAULT_SPEED_A);
  printf("  -B <value>  Rotation speed B (default: %.2f)\n", DEFAULT_SPEED_B);
  printf("  -d <value>  Delay in microseconds (default: %d)\n", DEFAULT_DELAY);
  printf("  -h          Display this help message\n");
}

int main(int argc, char **argv)
{
  // Default parameters
  float R = DEFAULT_R;
  float r = DEFAULT_r;
  float K1 = DEFAULT_K1;
  float K2 = DEFAULT_K2;
  float speedA = DEFAULT_SPEED_A;
  float speedB = DEFAULT_SPEED_B;
  int delay = DEFAULT_DELAY;

  // Parse command-line arguments
  int arg_index = 1;
  while (arg_index < argc)
  {
    if (argv[arg_index][0] == '-')
    {
      switch (argv[arg_index][1])
      {
      case 'R':
        if (arg_index + 1 < argc)
          R = atof(argv[++arg_index]);
        break;
      case 'r':
        if (arg_index + 1 < argc)
          r = atof(argv[++arg_index]);
        break;
      case 'K':
        if (argv[arg_index][2] == '1' && arg_index + 1 < argc)
          K1 = atof(argv[++arg_index]);
        else if (argv[arg_index][2] == '2' && arg_index + 1 < argc)
          K2 = atof(argv[++arg_index]);
        break;
      case 'A':
        if (arg_index + 1 < argc)
          speedA = atof(argv[++arg_index]);
        break;
      case 'B':
        if (arg_index + 1 < argc)
          speedB = atof(argv[++arg_index]);
        break;
      case 'd':
        if (arg_index + 1 < argc)
          delay = atoi(argv[++arg_index]);
        break;
      case 'h':
        printUsage(argv[0]);
        return 0;
      default:
        fprintf(stderr, "Unknown option: %s\n", argv[arg_index]);
        printUsage(argv[0]);
        return 1;
      }
    }
    arg_index++;
  }

  // Rotation angles
  float A = 0, B = 0;
  float theta, phi;
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

    // Loop through angles phi and theta
    for (phi = 0; phi < 6.28; phi += 0.07)
    {
      for (theta = 0; theta < 6.28; theta += 0.02)
      {
        // Calculate 3D coordinates and apply rotation
        float c = sin(theta);
        float d = cos(phi);
        float e = sin(A);
        float f = sin(phi);
        float g = cos(A);
        float h = d + R;                        // Use customizable major radius
        float D = 1 / (c * h * e + f * g + K2); // Use customizable K2
        float l = cos(theta);
        float m = cos(B);
        float n = sin(B);
        float t = c * h * g - f * e;

        // Project 3D coordinates to 2D screen space
        // Use customizable K1
        int x = 40 + K1 * D * (l * h * m - t * n);
        int y = 12 + K1 / 2 * D * (l * h * n + t * m);

        int o = x + 80 * y;

        // Calculate luminance using the surface normal and minor radius
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

        // Only render if point is within screen bounds and is closer than
        // any previously rendered point at this position
        if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
        {
          z[o] = D;
          b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
        }
      }
    }

    // Move cursor to top-left corner using ANSI escape sequence
    printf("\x1b[H");

    // Print the buffer to screen
    for (k = 0; k < 1761; k++)
    {
      putchar(k % 80 ? b[k] : 10);
    }

    // Update rotation angles for next frame using customizable speeds
    A += speedA;
    B += speedB;

    // Sleep for customizable delay to control animation speed
    usleep(delay);
  }

  return 0;
}
