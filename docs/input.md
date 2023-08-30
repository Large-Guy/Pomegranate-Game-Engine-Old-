### [...](engine.md)
# Input Module
The input module is for detecting input in your game.

```javascript
import input
```
## input.down
### Parameters: (char) key or (int) key
### Return: (bool) is_pressed
```javascript
if(input.down('Z'))
{
    debug.print("Z pressed");
}
if(input.down(90)) //Z ascii value
{
    debug.print("Z pressed");
}
```
## input.up
### Parameters: (char) key or (int) key
### Return: (bool) is_not_pressed
```javascript
if(input.up('Z'))
{
    debug.print("Z not pressed.");
}
if(input.up(90)) //Z ascii value
{
    debug.print("Z not pressed.");
}
```

## input.axis
### Parameters: (char) negative_key or (int) negative_key, (char) positive_key or (int) positive_key
### Return: (float) axis_value
```javascript
var direction = input.axis('A','D')
if(direction < 0)
{
    //Move left
}
else if(direction > 0)
{
    //Move right
}
```