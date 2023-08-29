### [...](engine.md)
# Input Module
## input.down
### Parameters: (char) key or (int) key
```c++
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
```c++
if(input.up('Z'))
{
    debug.print("Z not pressed.");
}
if(input.up(90)) //Z ascii value
{
    debug.print("Z not pressed.");
}
```