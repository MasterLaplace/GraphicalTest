# GraphicalTest

This project demonstrates how to test C++ OpenGL/GLFW applications using a **lightweight mocking strategy** based on `__attribute__((weak))`.
This allows you to **override specific functions like `glfwCreateWindow` in your test target** without modifying the production source code.
By separating implementation (`createWindow()`) from the main application logic, tests can inject mocked behavior and validate expected flows safely, even for graphical contexts.

## Building

```
git clone https://github.com/MasterLaplace/GraphicalTest.git
cd GraphicalTest

xmake build -y
```

## Running

```
xmake run app
```

## Testing

```
xmake run test
```
