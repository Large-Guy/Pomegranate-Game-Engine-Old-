### [...](engine.md)
# Teascript
## About
Teascript is a scripting language created by RevengerWizard. The source code can be found here: https://github.com/RevengerWizard/teascript
> A nice and calm dynamically typed programming language. It tries to mix the familiarity of Javascript, the simplicity of Python and the ease of use of Lua's C API.

Documentation will be provided for both Pomegranate Engine and standalone execution.

# Basics

## Hello World

### Pomegranate Engine
```javascript
debug.print("Hello, World!"); 
```
### Standalone
```javascript
print("Hello, World!");
```

Semicolons are optional.

# Variables

Variables are defined with the **var** keyword. The language is dynamically typed.

### Pomegranate Engine

```javascript
var A = 5  
var B = 4  
var C = A*B  
var String = string(C)  
debug.print(String) 
```

### Standalone

```javascript
var A = 5  
var B = 4  
var C = A*B  
var String = string(C)  
print(String) 
```

# Ranges

Ranges create a list of numbers from a to b.

### Pomegranate Engine

```javascript
debug.print(string(0..10)) //prints range from 0 to 10
```

### Standalone

```javascript
print(0..10) //prints range from 0 to 10
```

# Arrays

Arrays store a list of values.

### Pomegranate Engine

```javascript
var arr = [1,2,3]
debug.print(string(arr))
```

### Standalone

```javascript
var arr = [1,2,3]
print(arr)
```
## Array.add

### Parameters: (any) value

### Pomegranate Engine

```javascript
var arr = [1,2]
debug.print(string(arr))
arr.add(3)
debug.print(string(arr))
```

### Standalone Engine

```javascript
var arr = [1,2]
print(arr)
arr.add(3)
print(arr)
```

## Array.remove

### Parameters: (any) value

### Pomegranate Engine

```javascript
var arr = [1,2,3,4]
debug.print(string(arr))
arr.remove(arr[3])
debug.print(string(arr))
```

### Standalone Engine

```javascript
var arr = [1,2,3,4]
print(arr)
arr.remove(arr[3])
print(arr)
```

# Conditionals

## If Statements

```javascript
if(a == true)  
{  
    debug.print("A is true.");  
}  
else  
{  
    debug.print("A is false.");  
}  
```
## Switch Statements

# Loops

## For

### Pomegranate Engine

```javascript 
for(var i in 0..100)  
{  
    debug.print(string(i));  
}
```
### Standalone

```javascript
for(var i in 0..100)  
{  
    print(string(i));  
}
```

## While

### Pomegranate Engine

```javascript
var i = 0;  
while(i < 100)  
{  
    debug.print(string(i))  
    i += 1;  
}
```

### Standalone

```javascript
var i = 0;  
while(i < 100)  
{  
    print(string(i))  
    i += 1;  
}
```