# Description

Data takes the form of CPU temperature data in a txt file. All data points are whitespace delimited.
The temperature readings and generate for each core (4 core total) :

  * A piecewise linear interpolation.
  * A global linear least squares approximation.

# Requirements

  * g++ v5.x or newer
  * Make

# Compilation

The code can be compiled with the provided makefile using the standard `make`
command.

If compiling the code manually, or integrating into a larger program, include
the following flags:

```
FLAGS=-std=c++17 -fsanitize=address -fuse-ld=gold -Wall -MMD \
      -fext-numeric-literals -lquadmath #-O3
```

Note that flag `-fuse-ld=gold` is only required on certain Ubuntu systems due
to a know bug with g++ 5.x.


# Sample Execution & Output

If run without command line arguments, using

```
./tempParser ./test-data/sensors-label.txt
```

the following usage message will be displayed.

```
Usage: ./tempParser input_file_name.txt
```

If run using 

```
./tempParser ./test-data/sensors-label.txt
```

Expected Input text file should look *similar* to this **without labels**

```
85.0 82.0 71.0 80.0
70.0 65.0 58.0 65.0
70.0 72.0 55.0 63.0

```

or this **with labels**

```
+85.0Â°C +82.0Â°C +71.0Â°C +80.0Â°C
+70.0Â°C +65.0Â°C +58.0Â°C +65.0Â°C
+70.0Â°C +72.0Â°C +55.0Â°C +63.0Â°C
+91.0Â°C +86.0Â°C +76.0Â°C +85.0Â°C
```


All calculated output is written to text files (one file pre core) *simliar* to

```
    0     <= x <=     30; y_0 =     85 +         -0.5x;      Piecewise Linear Interpolation
    30    <= x <=     60; y_1 =     70 +            0x;      Piecewise Linear Interpolation
    60    <= x <=     90; y_2 =     28 +          0.7x;      Piecewise Linear Interpolation
    90    <= x <=    120; y_3 =    103 +    -0.133333x;      Piecewise Linear Interpolation
    0     <= x <=  18870; y = -0.000585607x +  81.9489;         Least Squares Approximation
```

will  be displayed. Note that the precision estimates will vary by
architecture/system.
