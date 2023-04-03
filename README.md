# graph_charact
1. As part of the project, I implemented a program that aims to check selected properties of a directed graph. Properties include:
• Check whether the directed graph is connected,
• Provide the center of the graph,
• Provide its radius,
• Provide the girth,
• Provide the gcd of cycle lengths,
• Regularity of the graph,
• Degree of the graph.
The program will be able to compile on the Linux system and will be written in the C language.

2. Input data - I will use the formats contained in the "nauty.h" library documentation for reading and writing.
3. Output data - The following properties will be provided on the output:
• In the first line, whether the graph is connected or not,
• If it is connected, then the indices of the vertices that are the center of the graph will be printed in the second line; otherwise, it will be empty,
• The radius of the graph will be given in the third line,
• The girth of the graph will be printed on the fourth line,
• The gcd of cycle lengths will be provided on the fifth line,
• In the sixth line, the program will indicate whether the graph is regular; otherwise, this line will be empty,
• The degrees of the vertices will be printed in the last line.
4. Connectivity - the program will check if the directed graph is connected using the undirected version of the graph. I will check connectivity using the method associated with filling the stack with successive vertices. If I can pass through all the vertices, then the directed graph is connected.
5. Center of the graph - another functionality of this program will be to print the center of the graph. First, I need to make sure that this graph is connected, and then find all such vertices.
6. Radius of the graph - the program will calculate and print the radius of the graph. If there is more than one center, the program will print the vertex index along with its radius.
7. Girth of the graph - the program will print the girth of the directed graph, which is the length of the shortest cycle.
8. Gcd of cycle lengths - the program will first calculate the length of each cycle, if any, and write it to the list. Then it will calculate the greatest common divisor of all cycle lengths.
9. Regularity of the graph - the program will check if the graph is regular,
10. Degree of the graph - the program will calculate the degree of individual vertices,
11. Using the library - I will use the "nauty.h" library in my project, which will be compatible with the program. The data format used in this project will be via dreadnaut.

`short description and compilation`   
$ make  
$ ./main <graph vertex file with .dre extension (*)>  

The program uses libraries:  
Nauty ():  
 - nauty.h  
 - naututil.h  
 - gutils.h  


(*) .dre file format  
For example:  
0: 1;  
1: 2;  
2: 3;  
3: 0.  
which means that 0->1 is a directed edge from vertex 0 to vertex 1, and so on.  
