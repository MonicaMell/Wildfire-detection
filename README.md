# Wildfire-detection

## Overview

This repository contains the source code for a fire detection system designed to optimize manufacturing processes across various industries. The system leverages image processing techniques to detect potential fire incidents early, ensuring the safety and stability of manufacturing operations.

## Features
### Image Resizing
The system resizes input images for efficient processing while maintaining essential details.
### Fire Pixel Counting
Utilizes algorithms to count red and orange pixels, identifying potential fire areas.
### Ascii Representation
Generates an ASCII representation of the resized image, highlighting potential fire regions.
### Threshold-Based Detection
Implements a threshold for claiming fire detection, providing flexibility for different scenarios.

## Getting Started
### Prerequisites
● C Compiler: Ensure you have a C compiler (you can use [GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection)) installed to build the C code.
● stb_image Library: The project uses the stb_image library. Include the necessary header file and link to the library during compilation, like this:
$ git clone https://github.com/nothings/stb.git


### Build Instructions
To compile and run the digital manufacturing solution with the modified code, follow these
guidelines:
● You can use the GCC for compilation. Include the -lm flag to link the math library as
the stb_image library may have inner references to math functions.
$ gcc your_modified_file_name.c -o output_executable_name -lm
● Run the compiled executable.
$ ./output_executable_name

## Documentation and Code Explanation
The code is organized into functions for clarity and modularity. Each function serves a specific purpose, and detailed comments are provided for code comprehension. Refer to [My Final Report](https://docs.google.com/document/d/171K09LcY5VhjJzDmWiwnCKwa28t-QAAvMmW3-kocr-w/edit?usp=sharing) for an in-depth explanation.

## Conclusion
The fire detection system demonstrates significant achievements in optimizing manufacturing processes, particularly in industries such as timber processing, paper and pulp manufacturing, smart city development, agriculture, forestry and logging, raw material supply chain, and textile and apparel manufacturing. The project contributes to supply chain stability, resource protection, and early intervention capabilities.


