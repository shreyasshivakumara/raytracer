## Ray Tracer

This is a simple ray tracer implemented in C++ based on the book "Ray Tracing in One Weekend" by Peter Shirley.  The technical details of the ray tracer are given below. The code is structured to support easy extension and experimentation with new materials and objects.To run the script, simply run the bash script `build.sh` in the terminal as shown below. The script will compile the code and run the executable. The output image will be in the output directory as `.ppm` file. Use [magick](https://imagemagick.org/script/command-line-processing.php) or similar application to change the format to `.png` or `.jpg`.

Execute the following command in the terminal to run the ray tracer:

```bash
./build.sh
```

### High-Level Components Implemented in this Ray Tracer

1. **Vector Class (`vec3`)**
   - **Purpose**: Handles fundamental 3D vector operations.
   - **Operations**: Addition, subtraction, multiplication, division, normalization, and length computation.

2. **Ray Class**
   - **Purpose**: Represents rays with origin and direction.
   - **Operations**: Computes points along the ray.

3. **Material Classes**
   - **Purpose**: Handle various material properties and interactions with rays.
   - **Types**:
     - **Lambertian**: Diffuse surfaces scatter rays in random directions.
     - **Metal**: Reflective surfaces with optional fuzziness.
     - **Dielectric**: Transparent materials handle refraction and reflection.
     - **Emissive**: Light-emitting materials.
   - **Technical Details**: Each material class implements scattering behavior and potentially emissive properties, crucial for simulating realistic light interactions.

4. **Hitable Classes**
   - **Purpose**: Define geometric objects for ray intersections.
   - **Types**:
     - **Sphere**: Spherical objects.
     - **Plane**: Infinite planes.
   - **Technical Details**: Implement intersection logic and surface normals for accurate rendering.

5. **Hitable List**
   - **Purpose**: Manages multiple hitable objects for efficient intersection testing.
   - **Operations**: Aggregates intersection tests across objects.

6. **Camera Class**
   - **Purpose**: Defines the viewpoint and generates rays through the image plane.
   - **Operations**: Computes rays based on camera parameters.
     
7. **Color Function**
   - **Purpose**: Implements recursive ray tracing and shading.
   - **Operations**: Computes color by tracing rays and handling reflections, refractions, and lighting.
   - **Technical Details**: Includes recursive ray tracing, Russian Roulette termination, and emissive handling.

8. **Main Rendering Loop**
   - **Purpose**: Sets up the scene, renders the image, and outputs the result.
   - **Operations**: Iterates over pixels, generates rays, and accumulates colors using Monte Carlo integration.

### Sampling Techniques

1. **Monte Carlo Integration**
   - **Purpose**: Approximates light contributions using random sampling.
   - **Technical Details**: Reduces noise and captures accurate lighting.

2. **Russian Roulette Termination**
   - **Purpose**: Controls recursion depth and improves performance.
   - **Technical Details**: Balances accuracy and performance with probabilistic termination.

3. **Cosine-Weighted Hemisphere Sampling**
   - **Purpose**: Improves sampling efficiency for diffuse reflections.
   - **Technical Details**: Reduces variance and noise by distributing rays more densely.

### Optimization Techniques

1. **Recursive Depth Control**
   - **Purpose**: Prevents excessive recursion.
   - **Technical Details**: Sets maximum depth and probabilistically limits recursion.

2. **Gamma Correction**
   - **Purpose**: Adjusts rendered colors for display.
   - **Technical Details**: Applies a gamma curve for accurate visualization.

3. **Importance Sampling**
   - **Purpose**: Focuses sampling on significant parts of the integrand.
   - **Technical Details**: Reduces variance by sampling likely contributing directions.
