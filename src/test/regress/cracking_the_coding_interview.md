## Outstanding Questions
========================

### Arrays and Strings
----------------------
* 1.1 Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?
	* My solution: sort the array first, then traverse the array => o(n^2) or o(n*lg n)
	* Best solution: use 256 bits or even less if string contains only 'a' to 'Z', o(n), **<<, & and |** operators
	* If no extra space allowed, naive way is to use two loops o(n^2)
	* Or if we are allowed to destroy the string, we can sort the string using quick sort(o(n*lg n)), and then use a loop to check neiboring; extra space for several bytes;
* 1.3 Remove the duplicate characters in a string without using any additional buffer NOTE: One or two additional variables are fine. An extra copy of the array is not
	* My solution: 1, naive loop method and use the tail element to fill in the detected duplicate postion: o(n^2); 2, quick sort first, then loop the string to detect duplicate and move at the same time, using two temp pointers, o(n*lg n)
	* For linked lists, we have to use the naive method, or use a hash table if extra space is allowed
* 1.5 Write a method to replace all spaces in a string with ‘%20’
	* My solution: naive method, loop and move => o(n^2)
	* Best solution: count the number of spaces in the first time, then move chars from the end to the begining;
	* Generally, for this kind of moving cases, consider move from end to the begining;
* 1.6 Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
	* My solution: use a matrix to record whether each element has been visited, use this for loop; and each time do a four-way swap;
	* Best solution: transform round by round, to alleviate the extra matrix for status recording;
	* For matrix transformation problems, transform round by round
* 1.8 Assume you have a method isSubstring which checks if one word is a substring of another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring (i e, “waterbottle” is a rotation of “erbottlewat”)
	* My solution: write a strcmp function and loop the cut position and check if the rearranged s1 equals to s2;
	* Best solution: 1, check the length; 2, concatenate s1 with itself, then check if s2 is the substring of the concatenated s1;

### Linked Lists
----------------
* 2.2 Implement an algorithm to find the nth to last element of a singly linked list
	* Naive solution: traverse the list twice;
	* Best solution: traverse only once, use two pointers
* 2.3 Implement an algorithm to delete a node in the middle of a single linked list, given only access to that node; EXAMPLE: Input: the node ‘c’ from the linked list a->b->c->d->e; Result: nothing is returned, but the new linked list looks like a->b->d->e
	* Solution: copy the data from the next node into this node and then delete the next node; note that, this problem can not be solved if the node to be deleted is the last node in the linked list
* 2.4 You have two numbers represented by a linked list, where each node contains a single digit. The digits are stored in reverse order, such that the 1’s digit is at the head of the list. Write a function that adds the two numbers and returns the sum as a linked list; example: Input: (3 -> 1 -> 5), (5 -> 9 -> 2), output: 8 -> 0 -> 8
	* My solution: convert the linked list to integer would have a problem of overflow, so this is like the adding of big integers, we have to do it one by one
* 2.5 Given a circular linked list, implement an algorithm which returns node at the begin- ning of the loop; example: Input: A -> B -> C -> D -> E -> C [the same C as earlier], Output: C
	* Solution: one with speed 1 and another with speed 2, the meeting point is k nodes from start of the loop, so is the head; this can be proved mathematically
	
### Stacks and Queues
---------------------
* 3.1 Describe how you could use a single array to implement three stacks
	* Naive solution: equally divide array into 3 parts;
	* Best solution: implement each element of the array to be a struct, and the struct has a field indicating the index of the previous element; **to reuse the holes in the array**, each time we push an element, we should check from the begining of the array to the last used elements to see if there is any 'freed' element; or we use a freelist to track the 'freed' elements each time we do a pop;
* 3.2 How would you design a stack which, in addition to push and pop, also has a function min which returns the minimum element? Push, pop and min should all operate in O(1) time
	* At first glance, we would like to use an integer to record the min value of the stack, this works fine for push, but if there are pops, we cannot maintain the correctness of the min value; so the information contained in the min value is not enough, we have to save more info; the solution is to let each node in the stack keep track of the min beneath itself;
* 3.3 Imagine a (literal) stack of plates. If the stack gets too high, it might topple. Therefore, in real life, we would likely start a new stack when the previous stack exceeds some threshold. Implement a data structure SetOfStacks that mimics this. SetOfStacks should be composed of several stacks, and should create a new stack once the previous one exceeds capacity. SetOfStacks push() and SetOfStacks pop() should behave identically to a single stack (that is, pop() should return the same values as it would if there were just a single stack); FOLLOW UP: Implement a function popAt(int index) which performs a pop operation on a specific sub-stack
	* For the follow up question, if we pop an element from stack 1, we need to remove the bottom of stack 2 and push it onto stack 1. We then need to rollover from stack 3 to stack 2, stack 4 to stack 3, etc; NOTE: we could make an argument that, rather than “rolling over,” we should be OK with some stacks not being at full capacity. This would improve the time complexity, but it might get us into tricky situations later on if someone assumes that all stacks (other than the last) operate at full capacity. **To efficiently handle the "rolling over", we should implement the stack in a double-linked list(recording bottom and top), instead of regular array, to avoid shifting of elements when removing bottom element**.
* 3.4 Towers of Hanoi
	* My solution: use stacks with push constraint to monitor towers, and use back trace method to explore the paths;
	* Best solution: recursive method
	* Some regular ways of thinking: start from simple examples, like say, size of 1 or 2, then use induction; or try recursion
* 3.5 Implement a MyQueue class which implements a queue using two stacks
	* Naive solution: for push, push to s1, for top and pop, we transfer everything in s1 to s2, and then transfer everything in s2 back to s1;
	* Best solution: for push, push to s1; for the first top or pop, transfer everything in s1 to s2, but do not transfer them back to s1 after finishing top and pop; for next push, push to s1, for next top and pop, pop from s2, if s2 is empty then, transfer everything in s1 to s2 again;
* 3.6 Write a program to sort a stack in ascending order. You should not make any assumptions about how the stack is implemented. The following are the only functions that should be used to write this program: push | pop | peek | isEmpty
	* The question is not clear, in extrem cases, we can pop everything out of the stack and sort them in an array, then push them back;
	* The intention of this question is to use another stack to do the sorting; we can start from simple, like say, we have 2 elements, we can easily sort this stack with the help of another stack; if we have 3 elements, we can sort the top 2 elements first, and then pop the third one, and push the top 2 back, while comparing them with the third one at the same time; ... so we can sort the n elements stack recursively, i.e, sort the top 2 first, then top 3, then... the method is quite like Towers of Hanoi### Trees and Graphs
--------------------
* 4.1 Implement a function to check if a tree is balanced. For the purposes of this question, a balanced tree is defined to be a tree such that no two leaf nodes differ in distance from the root by more than one
	* Naive solution: DFS or BFS to traverse the tree, and for each leaf node, check whether we should update the min and max distance value; finally, check whether max is more than 1 larger than min;
	* Best solution: recursion; the problem itself is hard to be divided into recursive steps, that is to say, to guarantee a tree is balanced, we not only should make sure left tree and right tree are balanced, but the min/max of left should not differ from min/max of right by more than one, which is hard to implement; the solution is to recursively find out the min and max distance of leaf nodes, i.e, transform the naive method to its recursive version;
* 4.5 Write an algorithm to find the ‘next’ node (e.g, in-order successor) of a given node in a binary search tree where each node has a link to its parent
	* My solution: if the node has right child, then the most left leaf node of the right subtree if the successor; if the node has no right child, then we find the successor in the upper level; if the node is the left child of its parent P, then P is the successor; if the node is the right child of its parent P, then we have to go up further until we find the an ancestor which has the node in its left subtree, then that is the successor; or return NULL if we find the root node of tree, which means the node has no successor; the key of this problem is being careful;
* 4.6 Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree. Avoid storing additional nodes in a data structure NOTE: This is not necessarily a binary search tree
	* Several methods: 1) traverse the tree, and add special edges to point to each node's parent, then we can find out two paths from target nodes to root node, then compare these two paths from tail to the head, the parent of the first different node is the first common ancestor; 2) if this node covers both targets, while left and right subtree covers separetely, then this node is the first common ancestor; we can use recursive way to implement the cover function: use bitmap or we can simply calculate the covered nodes number; **pay attention the special cases, where one target is the first common ancestor**;
* 4.7 You have two very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1
	* Subgraph isomorphism is cost expensive (NP-Hard), but binary tree match is not that bad;
	* if T2's pre-order traverse string is T1's substring, and T2's in-order traverse string is T1's substring as well, then T2 is T1's subtree; pay attention to the memory needed
	* Normal approach: o(n*m)
* 4.8 You are given a binary tree in which each node contains a value. Design an algorithm to print all paths which sum up to that value. Note that it can be any path in the tree - it does not have to start at the root
	* Recursive method; **WARNING**: the value can be less than 0, so we cannot terminate the diving even if we find the sum, we have to dive into the bottom of the tree for each root node;
* balance a binary search tree?
	* solution: first, get a sorted list from the BST by in-order traverse of the tree; then pick the middle item as the new root and build balanced binary search tree recursively.

### Bit Manipunation
--------------------
* 5.2 Given a (decimal - e.g, 3.72) number that is passed in as a string, print the binary representation; If the number can not be represented accurately in binary, print “ERROR”
	* **WARNING** binary representation means float in binary or int part and decimal part in binary form respectively?
* 5.3 Given an integer, print the next smallest and next largest number that have the same number of 1 bits in their binary representation
	* Naive approach: count the number of 1s, then check the subsequence numbers;
	* Best approach: bit manipulation;
* 5.4 ((n & (n-1)) == 0) checks if n is a power of 2 (or 0); n can only have one 1 bit;

### Recursion
-------------
* 8.3 Write a method that returns all subsets of a set
	* Best approach: We should first have some reasonable expectations of our time and space complexity. How many subsets of a set are there? We can compute this by realizing that when we generate a subset, each element has the “choice” of either being in there or not. That is, for the first element, there are 2 choices. For the second,there are two,etc So,doing 2*2*...*2 n times gives us 2^n subsets. We will not be able to do better than this in time or space complexity; so the solution is to use recursion: given a set S, we can do the following recursively: (1) Let first = S[0] Let smallerSet = S[1, , n]; (2) Compute all subsets of smallerSet and put them in allsubsets; (3) For each subset in allsubsets, clone it and add first to the subset;
* 8.4 Write a method to compute all permutations of a string
	* To permute set S, we can select the first character, A1, permute the remainder of the string to get a new list Then, with that new list, we can “push” A1 into each possible position; complexity is o(n!); NOTE THAT, this is true only if string does not contain duplicate characters;
* 8.5 Implement an algorithm to print all valid (e.g, properly opened and closed) combinations of n-pairs of parentheses
	* Best approach: treat it as a string, each position must have a left or right paren; When can we use left, and when can we use a right paren? (1) Left: As long as we haven’t used up all the left parentheses, we can always insert a left paren; (2)Right: We can insert a right paren as long as it won’t lead to a syntax error When will we get a syntax error? We will get a syntax error if there are more right parentheses than left
* 8.7 Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents) and pennies (1 cent), write code to calculate the number of ways of representing n cents
	* Best approach: start from simple, if we can only use 1 cent, write code of divide_1_cent(n); then if we can use 5 cents, divide_5_cents(n) can be computed by using 0 5_cents, using 1 5_cents, etc; then divide_10_cents(n), then divide_25_cents(n);
* 8.8 Write an algorithm to print all ways of arranging eight queens on a chess board so that none of them share the same row, column or diagonal
	* key is understanding "diagonal"

### Sorting and searching
-------------------------
* several common sorting methods
	* bubble sort
	* merge sort
	* quick sort
	* bucket sort
* 9.3 Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm that finds an element in the array. You may assume that the array was originally sorted in increasing order.
	* modification of binary search;
	* What about duplicates? You may observe that the above function doesn’t give you an efficient result in case of duplicate elements. However, if your array has duplicate entries then we can’t do better than O(n) which is as good as linear search. For example, if the array is [2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,2], there is no way to find element 3 until you do a linear search.
* 9.6 Given a matrix in which each row and each column is sorted, write a method to find an element in it.
	* Naive approach: o(N * M), not utilizing the sorting information;
	* Best approach: recursion; assump that rows are sorted left to right in ascending order, and columns are sorted top to bottom in ascending order, so for each element `elem` in matrix, if `elem < x`, all the elements in the upper left corner are eliminated; if `elem > x`, then all the elements in the down right corner are eliminated; so if we start from upper right corner of the matrix, if `elem < x`, then the first line of the matrix is removed, and the issue is turned into a smaller recursive problem; if the `elem > x`, then the last column is removed from the matrix, and again, it turns into a smaller recursive problem; the complexity is o(n + m) in the worst case;
* 9.7 A circus is designing a tower routine consisting of people standing atop one another’s shoulders. For practical and aesthetic reasons, each person must be both shorter and lighter than the person below him or her. Given the heights and weights of each person in the circus, write a method to compute the largest possible number of people in such a tower
	* My approach(answer seems to be incorrect): first, sort the whole set; second, find the reverse pairs(in sequence); third, start from number L(size of whole circus), check if the sequence works; if not, decrease to L-1, that is to say, remove one element in the first pair, check if it works, and so on; wrap the remove procedure into a **recursive method**, the input is the reverse pairs, and the number of elements we can remove, the output is whether we can resolve all reverse pairs given the elements to remove;

### System design and memory
----------------------------
* 12.3 Given an input file with four billion integers, provide an algorithm to generate an integer which is not contained in the file. Assume you have 1 GB of memory. What if you have only 10 MB of memory?
	* bit map for 1GB memory; for 10MB, divide into blocks and count;

### Low level
-------------
* 16.10 Write a function called my2DAlloc which allocates a two dimensional array. Minimize the number of calls to malloc and make sure that the memory is accessible by the notation arr[i][j].
	* the core idea is to combine the malloc of each row to a single one;

### Network
-----------
* 17.5 What are the differences between TCP and UDP? Explain how TCP handles reliable delivery (explain ACK mechanism), flow control (explain TCP sender’s / receiver’s window) and congestion control.
	* ssthresh is decreased to the half of the current send window size;

### Lock and threads
--------------------
* 18.1 differences between processes and threads
	* process has stack memory, each thread still has its own registers and its own stack, but these threads can read and write the process stack memory.
* 18.2 How can you measure the time spent in a context switch?
	* Tricky question, no answer;
	* if we can modify kernel code, it's easy, adding some debugging code in scheduler code;
	* if we must do it in user space, serveral challenges:
		* basic approach is to record the timestamp of the last instruction of scheduled out process, and the timestamp of the first instruction of scheduled in process;
		* how to get the timestamp? we have to use system call, which is expensive compared with the time we are going to measure;
		* when we should get the timestamp? how do we know which instructions are on the border?
		* where to record these timestamps? memory? no, too expensive, we have to record it in registers;
		* there are so many tasks running in the system, we cannot guarantee OS would schedule in the process we wish;
* 18.3 Singleton class constructor?
	* `static` would be best, and `synchronized` method would be expensive;
	* double-checked locking:
		* not working in JAVA;
		* be careful in C, use `barrier` to prevent reordering;

## Questions of OS
==================
* padding and size of structures
	* First, for this kind of question, the answer depends on platforms and compilers(and `#pragma pack` pre-compiling instruction would affect this as well), the best answer is to write a code to test it; while there are some basic conventions we should keep in mind;
	* The C compiler will add padding for alignment requirements, it may align fields in your structure for easier accessing; Further, it may pad the bottom of the structure;
	* reasons for padding: performance (e.g, read start from even address)