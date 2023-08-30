### [...](engine.md)
# Window Module
The window module is for drawing custom editor windows.

```javascript
import window
```

## window.begin()

### Parameters: (string)name

```javascript
window.begin("Teascript Window")
```

## window.end()

```javascript
window.end()
```

## window.button()

### Parameters: (string)text
### Return: (bool) is_pressed
```javascript
if(window.button("Say Hello"))
{
    print("Hello!")
}
```