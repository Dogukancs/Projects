\# Multi-Level Linked List Dynamic Matrix Manager



An object-oriented C++ console application built entirely on dynamic heap memory without using the Standard Template Library (STL) or generic (`template`) structures. The program reads matrices from a file into multi-level linked lists, sorts them by their arithmetic mean, and provides an interactive console interface for matrix manipulation.



\## Features



\- \*\*Three-Tier Linked List Architecture:\*\* Matrix cells (`SayiDugumu`) and rows (`SatirDugumu`) are stored in singly linked lists, while the matrices themselves (`MatrisDugumu`) are managed in a doubly linked list.

\- \*\*File Persistence (`kayitlar.txt`):\*\* Reads initial matrix dimensions and elements from `kayitlar.txt` on startup and writes the updated list back to the file upon exit (`x`).

\- \*\*Arithmetic Mean Sorting:\*\* Sorts all matrices in ascending order based on the arithmetic mean of their elements using a pointer-based Merge Sort algorithm.

\- \*\*Paginated Console Interface:\*\* Displays up to 5 node boxes at a time (showing node memory address, arithmetic mean, and next node pointer) alongside the currently selected matrix.

\- \*\*Unique Random Matrix Insertion:\*\* Inserts a randomly sized square matrix populated with unique numbers (`0–99`) either before (`q`) or after (`e`) the selected node.

\- \*\*Matrix Manipulation Operations:\*\* Supports deleting rows, deleting columns, and swapping row-column elements (restricted to square matrices). Matrices with all rows or columns deleted are automatically removed from the main list upon returning to the navigation menu.



\## Directory Structure



```text

├── bin/          # Compiled executable (.exe)

├── doc/          # Project report

├── include/      # Class header files (.hpp)

├── lib/          # Compiled object files (.o)

├── src/          # Source files (.cpp)

├── benioku.txt   # Usage notes

├── kayitlar.txt  # Input/output matrix data file

└── makefile      # MinGW build rules

 # Build the project
mingw32-make

# Run the application (kayitlar.txt must be in the root directory)
bin\program.exe

# Clean build artifacts (.o and .exe)
mingw32-make clean

Controls
Main Menu (Node Navigation)
Key	Action
w / s	Navigate up and down through matrix nodes
q	Insert a random square matrix before (above) the selected node
e	Insert a random square matrix after (below) the selected node
f	Open the operations menu for the selected node
x	Save all changes to kayitlar.txt and exit
Node Operations Menu
Key	Action
1	Row Deletion Menu: Use w / s to select a row, d to delete it, and x to return to the main menu
2	Column Deletion Menu: Use a / d to select a column, f to delete it, and x to return to the main menu
3	Swap Row & Column: Swaps elements of a chosen row and column (valid for square matrices only)
x	Return to node navigation

