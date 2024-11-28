[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Iy21DPoA)
<h2 align="center">CSCE 2211 Fall 2024 Applied Data Structures</h2>

<table border="0">
 <tr>
    <td><b style="font-size:20px">📋 Prerequisites for the Assignment</b></td>
    <td><b style="font-size:20px">🛠️ How It Works (Testing Cases)</b></td>
 </tr>
 <tr>
    <td>
    1. Create a <a href="https://account.jetbrains.com/login" target="_blank">JetBrains Account</a> & apply for the student pack. 🎓<br>    
    2. Download <a href="https://www.jetbrains.com/clion/download/#section=mac" target="_blank">CLion for Windows & Mac</a> and sign in with your account. 💻<br>    
    3. Sign in to the GitHub Desktop app on your PC. 🔗<br>  
    4. Clone this repository to start working on the assignment. 📂<br>
    5. Write your name and ID in a comment at the beginning of each file, then push your changes. 📝<br>
    </td>
    <td>
    1. Open the repo folder as a project in CLion IDE. 🚀<br> 
    2. Start writing your code in the <strong>Code_lib</strong> directory. 🖊️<br>
    3. After completing the required parts, go to <strong>Google_tests</strong> and run <strong>TestHanoi.cpp</strong> and <strong>TestCalculator.cpp</strong> to test your code. 🧪<br>
    4. The test suite files will show which tests have passed and which have failed. ✅❌<br>
    </td>
 </tr>
</table>

:warning: :warning: :warning: :warning: :warning: :warning: :warning:
```diff
- Your submission time affect the assignment grade; pay attention to your grades and submit on time.
- You have to commit and push your code to Github at the end of each change.
```
:warning: :warning: :warning: :warning: :warning: :warning: :warning:

## 🔍 Overview of the Assignment
You will be implementing two key problems using the Stack ADT:
1. **Towers of Hanoi** (50 points)
2. **A Simple Calculator Program** (50 points)

Use the [visualization tool](https://www.cs.usfca.edu/~galles/visualization/StackArray.html)
Implement the following programs using the Stack ADT:
***

## 🏰 Towers of Hanoi [Go to the code file](Code_lib/TowersOfHanoi.cpp)

The Towers of Hanoi is a classic problem that involves moving disks of different sizes from one peg to another, following certain rules:
- There are three pegs: A (source), B (auxiliary), and C (target).
- You must move all disks from peg A to peg C using peg B as needed.
- You can only move one disk at a time, and a larger disk cannot be placed on top of a smaller disk.

### Example Moves:
- **1 Disk**: Move disk 1 from A to C.
- **2 Disks** (top is 1, bottom is 2):
  1. Move disk 1 from A to B.
  2. Move disk 2 from A to C.
  3. Move disk 1 from B to C.
- **N Disks**:
  1. Move the top N-1 disks from A to B using C.
  2. Move disk N from A to C.
  3. Move the N-1 disks from B to C using A.

### Algorithm:
This is a recursive problem and can be solved using the following algorithm:

```cpp
Towers(N, Source, Target, Aux) {
    if (N == 1)
        move disk 1 from Source to Target directly;
    else {
        Call Towers to move N-1 disks from Source to Aux via Target;
        Move disk N from Source to Target directly;
        Call Towers to move N-1 disks from Aux to Target via Source;
    }
}
```

### An animation of the game:  
<p align="center">
  <img width="460" height="300" src="https://mathworld.wolfram.com/images/gifs/hanoi.gif">
</p>

<p align="center">
  <img width="460" height="300" src="https://mathworld.wolfram.com/images/eps-svg/TowersofHanoiSolution_700.svg">
</p>

## Required Implementations:
1. Implement an array-based stack template class called Stackt. Ensure you overload the assignment operator and include a copy constructor.
2. Develop a program using the above algorithm to simulate the Towers of Hanoi game:
- Number the disks from 1 to N in ascending order of their size.
- Use the Stackt class to represent the contents of each peg.
- Display the state of the pegs after each move to show the process.
- Display the total number of moves needed.

## 🧮 Simple Calculator Program [Go to the code file](Code_lib/SimpleCalculator.cpp)

Create a program that reads an infix expression from the user, converts it to postfix, and then evaluates the postfix expression.

### Specifications:
- Operands are single-digit integers.
- Supports parentheses ( and ), and the operators +, -, *, /, %.
- Follows C++ operator precedence rules.
- Use a character stack for infix-to-postfix conversion and a double stack for postfix evaluation.

### Output:
1. Show the input infix string.
2. Display the converted postfix string.
3. Print the result of the calculation.

### Example:
```
Type your infix expression: (5+3)*(6-4)/((4-2)*(3+1))
Postfix: 5 3 + 6 4 - * 4 2 - 3 1 + * /
Result: 2.0
```
### Bonus (3 Points):

Handle multiple-digit integers, e.g., 23+30*4/15.

### 🔧 Testing Your Code
- Run the Towers of Hanoi tests [Test your Towers of Hanoi code](Google_tests/TestHanoi.cpp).
- Run the Simple Calculator tests [Test your Simple Calculator code](Google_tests/TestCalculator.cpp).

Ensure that all test cases pass before submitting your assignment.

### 📬 Submission Instructions:
- Comment your code and document any assumptions you made.

***
📝 To-Do List
- [ ] Run all test cases successfully.
- [ ] Commit and push your code regularly to GitHub.
- [ ] Submit your final code before the deadline (September 12th, 2024, 11:59 CLT).

:white_check_mark: Use `git status` to list all new or modified files that haven't yet been committed.

<p align="center">
  <b>Created by</b><br>
  <b>Mohamed Ibrahim Hany</b>
</p>
