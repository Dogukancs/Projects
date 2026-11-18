\# Hexagonal Priority Queue \& Binary Search Tree Engine



A high-performance, zero-dependency C++ simulation engine implementing custom \*\*Binary Search Trees (BST)\*\* embedded inside \*\*6-capacity Hexagonal Priority Queues\*\*\[cite: 12, 15]. Built strictly without Standard Template Library (STL) containers or C++ generics/templates, relying on raw pointers, manual memory management, and modular `.hpp`/`.cpp` architecture\[cite: 15].



\## Technical Highlights \& Constraints

\* \*\*Zero STL \& Zero Templates:\*\* All data structures (queues, trees, nodes, and linked structures) are engineered from scratch using raw pointers (`new`/`delete`) with strict memory-leak prevention\[cite: 15].

\* \*\*Modular OOP Architecture:\*\* Strictly separated header (`.hpp`) and implementation (`.cpp`) files with zero inline method definitions inside headers\[cite: 15].

\* \*\*High-Throughput Execution:\*\* Optimized to parse, construct, and simulate \*\*50,000+ lines\*\* of numeric input datasets (`Data.txt`) with real-time console rendering\[cite: 14, 15].



\## System Architecture \& Data Structures

1\. \*\*Binary Search Tree (`BST`):\*\*

&#x20;  \* Stores integer keys parsed left-to-right from each line of `Data.txt`\[cite: 14].

&#x20;  \* Duplicate values are deterministically inserted into the \*\*left subtree\*\*\[cite: 12].

&#x20;  \* Dynamically computes tree height to determine extraction priority\[cite: 12].

2\. \*\*Hexagonal Priority Queue (`HexQueue`):\*\*

&#x20;  \* Fixed capacity of \*\*6 BST elements\*\* per hexagonal node\[cite: 12].

&#x20;  \* \*\*Queue Metric Calculation:\*\* Computes the integer ratio between the root of the standard front tree (FIFO) and the root of the highest-priority tree (maximum height): `FrontRoot / MaxHeightRoot`\[cite: 12].

3\. \*\*Serpentine Ring Topology \& Turn Simulation:\*\*

&#x20;  \* Hexagonal queues are arranged in a 6-column serpentine grid where the tail wraps back to the head\[cite: 14, 15].

&#x20;  \* \*\*Odd Turns:\*\* Dequeues the standard front BST (FIFO) and transfers its nodes to the next hexagon\[cite: 15].

&#x20;  \* \*\*Even Turns:\*\* Dequeues the highest-priority BST (max tree height) and transfers its nodes to the next hexagon\[cite: 15].

&#x20;  \* \*\*Postorder Node Redistribution:\*\* The dequeued BST is dismantled via \*\*postorder traversal\*\* (deleting nodes as they are visited) and distributed one node at a time in round-robin order across the target hexagon's existing trees\[cite: 15].

