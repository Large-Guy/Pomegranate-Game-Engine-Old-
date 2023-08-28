# Teascript
## About
Teascript is a scripting language created by RevengerWizard. The source code can be found here: https://github.com/RevengerWizard/teascript
> A nice and calm dynamically typed programming language. It tries to mix the familiarity of Javascript, the simplicity of Python and the ease of use of Lua's C API.

Documentation will be provided for both Pomegranate Engine and standalone execution.

# Basics

## Hello World

### Pomegranate Engine
```javascript
debug_console_print("Hello, World!"); 
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
debug_console_print(String) 
```

### Standalone

```javascript
var A = 5  
var B = 4  
var C = A*B  
var String = string(C)  
print(String) 
```

# Conditionals

## If Statements

```javascript
if(a == true)  
{  
    debug_console_print("A is true.");  
}  
else  
{  
    debug_console_print("A is false.");  
}  
```
## Switch Statements

# Loops

## For

### Pomegranate Engine

```javascript 
for(var i in 0..100)  
{  
    debug_console_print(string(i));  
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
    debug_console_print(string(i))  
    i += 1;  
}
```

### Standalone

```javascript
var i = 0;  
while(i < 100)  
{  
    debug_console_print(string(i))  
    i += 1;  
}
```