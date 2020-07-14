# raytracer
Implementation by Trevor Du

## Instructions
```
make dirs
make
cd bin/
./main PATH/TO/CFG/FILE
```

## Setting up a Configuration
Information about a raytraced scene is specified in a .cfg file. The configuration files sets the width, height, and FOV of a frame, as well as each object and light source in the scene.

1. Window Settings

    These should be at the start of the .cfg file.
    ```
    width=<WIDTH IN PIXELS>
    height=<HEIGHT IN PIXELS>
    fov=<HORIZONTAL FIELD OF VIEW IN DEGREES>
    ```

2. Describing Objects & Light Sources

    To begin describing the properties of an object or light source in a scene, a sort of "type specifier" is needed for the type of object or light source.

    A specifier begins with a "#" character and is immediately followed by the name of the type. *Specifiers cannot have any whitespace and are case-sensitive.*

    1. Sphere

        ```
        #Sphere
        center=[x,y,z]
        radius=<SOME NUMBER>
        colour=[r,g,b]
        ```
    
    2. Point Light Source

        ```
        #PointLightSource
        pos=[x,y,z]
        colour=[r,g,b]
        intensity=<POWER IN WATTS>
        ```

    3. Directional Light Source

        ```
        #PointLightSource
        radius=<SOME NUMBER>
        pos=[x,y,z]
        dir=[i,j,k]
        colour=[r,g,b]
        intensity=<POWER IN WATTS>
        ```