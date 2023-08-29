### [...](engine.md)
# Debug Module

## debug.print
### Parameters: (string) text
Prints to the console.
```c++
debug.print("Hello, World!")
```
## debug.begin
Begins drawing.
```c++
debug.begin()
```
## debug.end
Ends drawing.
```c++
debug.end()
```
## debug.line
### Parameters: (vec3) a (vec3) b
Draws a line.
```c++
debug.line([0.0,0.0,0.0],[0.0,1.0,0.0])
```
## debug.sphere
### Parameters: (vec3) point (float) radius
Draws a sphere.
```c++
debug.sphere([0.0,0.0,0.0],1.0)
```
## debug.point
### Parameters: (vec3) position
Draws a point.
```c++
debug.point([0.0,0.0,0.0])
```
## debug.set_color
### Parameters: (vec3) color
Sets the drawing color. Can only be called before begin drawing.
```c++
debug.print([1.0,0.0,1.0])
```