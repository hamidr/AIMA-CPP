AIMA-CPP
========

C++(1y) implementation of algorithms from Norvig And Russell's "Artificial Intelligence - A Modern Approach 3rd Edition."

### typename COPYRIGHT = MIT

 I really want others to contribute over this ( at least the examples are so few ) :)
 
 It would be great if someone try to to solve the questions in the book by this little library.

### TODO

- I'd like to write a little GUI (with Qt) to show how these algorithms work.
- Trying to compile everything on windows with VC++; I used almost no feature of c++1y so it's possible to port this to windows.

- Currently I'm just implementing step by step while I read the book :)

  Let's hope I'll do the rest or someone else would do it.

### Examples

  For now there are only there way to define a problem:
  -  use Macros ```MAKE_PROBLEM``` and ``` END_PROBLEM ``` to make a problem with a goal and a generator for each state:
    - You have to generate successors for each state.

  -  Use function ``` makeProblem``` to make problem for using the generated tree/graph to find the defined goal.
    - There'll be no generator for this problem.
    - The graph will get expanded only by the leafs of each state in the graph/tree.

  -  Inherit from Problem<T> :
    - Override ```void watch(const T &state) const;``` to watch what state is getting tested.
    - Override ```bool isGoal(const T &state) const;``` to say which state is the goal of the problem.
    - Override ```leafs_list successors( const node_ptr &state) const;``` to generate/expand the successors of the current state.


  Take a look at Test.hpp and Test.cpp to see what I mean :P .
  There will be a separated directory for examples in close future.


### Compiled ON/BY:

```
Linux debian 3.2.0-4-amd64 #1 SMP Debian 3.2.46-1 x86_64 GNU/Linux
gcc version 4.8.1 (GCC)
clang version 3.3 (tags/RELEASE_33/final)
```
