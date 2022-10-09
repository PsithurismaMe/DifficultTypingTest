This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.














Dependencies:
    - ncurses 
    - A C++ compiler supporting C++11 or newer

To install all dependencies on Arch Linux Based Distros:
___________________________________________________________
sudo pacman -S ncurses gcc
___________________________________________________________


For Debian Based Distros:
___________________________________________________________
sudo apt install libncurses-dev g++
___________________________________________________________





COMPILATION INSTRUCTIONS:

If on a unix based OS, assuming your using g++
___________________________________________________________
g++ main.cpp -lncurses -o typeTest
___________________________________________________________

If using LLVM/clang
___________________________________________________________
clang++ main.cpp -lncurses -o typeTest
___________________________________________________________


If using windows, have fun figuring this out. The developer of this doesn't use windows.