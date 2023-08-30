### [...](engine.md)
# Debug Module

The debug module is for debugging your game.

```javascript
import debug
```

## debug.print
### Parameters: (string) text
Prints to the console.
```javascript
debug.print("Hello, World!")
```
## debug.begin
Begins drawing.
```javascript
debug.begin()
```
## debug.end
Ends drawing.
```javascript
debug.end()
```
## debug.line
### Parameters: (vec3) a (vec3) b
Draws a line.
```javascript
debug.line([0.0,0.0,0.0],[0.0,1.0,0.0])
```
## debug.sphere
### Parameters: (vec3) point (float) radius
Draws a sphere.
```javascript
debug.sphere([0.0,0.0,0.0],1.0)
```
## debug.point
### Parameters: (vec3) position
Draws a point.
```javascript
debug.point([0.0,0.0,0.0])
```
## debug.set_color
### Parameters: (vec3) color
Sets the drawing color. Can only be called before begin drawing.
```javascript
debug.print([1.0,0.0,1.0])
```