# Spinning Donut

A 3D spinning donut animation rendered in ASCII art, written in C.

## Description

This program renders a 3D spinning torus (donut) using ASCII characters in the terminal. The animation is created by calculating the 3D geometry of the torus and projecting it onto a 2D plane, then mapping different ASCII characters to represent different lighting intensities.

## How It Works

The program uses mathematical formulas to:
1. Create a 3D torus
2. Apply rotation transformations
3. Project the 3D points onto a 2D plane
4. Calculate lighting based on surface normals
5. Map lighting values to ASCII characters
6. Render the output to the terminal

For a detailed mathematical explanation, see [EXPLANATION.md](EXPLANATION.md).

## Requirements

- C compiler (gcc recommended)
- math library (libm)
- POSIX-compliant system (for usleep)

## Compilation

```bash
make
```

Or manually compile individual versions:

```bash
# Basic version
gcc -Wall -Wextra -O2 -o donut donut.c -lm

# Commented version
gcc -Wall -Wextra -O2 -o donut_commented donut_commented.c -lm

# Customizable version
gcc -Wall -Wextra -O2 -o donut_customizable donut_customizable.c -lm
```

## Running the Program

### Basic Version
```bash
./donut
```

### Commented Version
```bash
./donut_commented
```

### Customizable Version
```bash
./donut_customizable [options]
```

Options for customizable version:
- `-R <value>`: Major radius (default: 2.0)
- `-r <value>`: Minor radius (default: 1.0)
- `-K1 <value>`: Projection constant 1 (default: 30.0)
- `-K2 <value>`: Projection constant 2 (default: 5.0)
- `-A <value>`: Rotation speed A (default: 0.04)
- `-B <value>`: Rotation speed B (default: 0.02)
- `-d <value>`: Delay in microseconds (default: 30000)
- `-h`: Display help message

Example:
```bash
./donut_customizable -R 3.0 -K1 40.0 -A 0.03
```

Press Ctrl+C to exit any version of the program.

## Versions

1. **donut.c**: Basic implementation of the spinning donut
2. **donut_commented.c**: Same implementation but with detailed comments explaining the math and logic
3. **donut_customizable.c**: Version with command-line parameters to customize the donut's appearance and animation

## License

This project is licensed under the MIT License - see the LICENSE file for details.
