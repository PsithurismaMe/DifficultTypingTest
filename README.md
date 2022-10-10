# A Difficult Typing Test











## Compiling
Dependencies:
 - ncurses 
 - A C++ compiler supporting C++11 or newer

To install all dependencies on Arch Linux Based Distros:
```
sudo pacman -S ncurses gcc
```


For Debian Based Distros:
```
sudo apt install libncurses-dev g++
```
### Compiling Step

If on a unix based OS, assuming your using g++
```
g++ main.cpp -lncurses -o typeTest
```

If using LLVM/clang
```
clang++ main.cpp -lncurses -o typeTest
```


If using windows, have fun figuring this out. The developer of this doesn't use windows.