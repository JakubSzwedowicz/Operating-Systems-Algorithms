# Operating-Systems-Algorithms
Project contains algorithms that find usage in low level mechanisms of operating system.
They are written in Java and CPP+17 without any particular order.

# Projects
1. CPU Scheduler,
2. Disk Scheduling algorithms
3. Paging Algorithms

## CPU Scheduler

The program simulates algorithms of scheduling access to the CPU for upcoming processes.
It tests and calculates average waiting time for different scheduling algorithms:
* First Come First Serve,
* Shortest Job First ([preemptive](https://en.wikipedia.org/wiki/Preemption_(computing)) and not)
* Round Robin (with the possibility of choosing the time slot)

The algorithm also mimics the real time environment by loading couple of proceesses beforehand and then adds at random moments randomly generated processes.

**Additional info**
1. *Java 11*


## Disk Scheduling Algorithms

It's a simulation of various disk scheduling algorithms such as:
* FCFS
* SSTF
* SCAN
* C-SCAN

The environment within the project takes under the consideration the way the hard drive is built, operates and behaves, which includes:
* physical construction (blocks, tracks, plates, heads) and its requirenments such as for example:
	* plausible size of blocks,
	* number of blocks per plate.
* interface with OS (addressing of blocks)
	* which also stands for the fact that OS should percive hard drive as if it was continuos memory space.
* real world parameters, such as:
	* current disk rotation in degrees,
	* the tracks and addresses the heads are pointing to,
	*  time of the rotation of the disk,
	*  time for the head to switch track
* and more

Moreover, project compares all these algorithms, the overall time it takes for them to process the whole priority queue of prepared orders and those added dynamicly (run-time).

**Additional Info** 
1. *C++17*,
2. *CMake 3.16*,
3. *[gtest](https://github.com/google/googletest) 1.10*

## Page Replacement algorithms

The program simulates behaviour of different paging algorithms that resolve issues with page errors when accessing page that was moved to the virtual memory.
ALgorithms put into testing are:  
* FIFO  
* OPT (Optimal - the removing page is the one that is not going to be used for the longest time. Comparision algorithm with others)  
* LRU  
* Estimated LRU
* RAND (For the comparison as a bare minimum of effectivness)

The simulation involves such components as:
* The size of virtual memory (and the way it's split into pages),
* The size of physical memory (same as above), 
* Segments Table,
* Usage of logic addresses that get converted into physical ones by segments table

Moreover because of how the real orders to the Memory are made, there are at least two rules that must be preserved:
* Locality of reference,
* Symmetry of the sequence.

**Additional Info**
1. *C++17*
2. *CMake 3.16*

