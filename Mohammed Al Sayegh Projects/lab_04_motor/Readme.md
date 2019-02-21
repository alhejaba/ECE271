%
% Spring 2015
% Lab Assignment 
% ECE 271 Microcomputer Architecture and Applications
% Instructor: Prof. Yifeng Zhu
% Electrical and Computer Engineering
% University of Maine
% https://gitlab.eece.maine.edu/
%

Student Name
-------------------------------------------------
Mohammed Hashem Al-Sayegh

Lab Status Summary
-------------------------------------------------
The code read the input and write the digit in the first three digit of LCD when press '#' it will clear the last writen
digit. When 'A' pressed it will rotate stepper motor clockwise. When 'B' pressed it will rotate stepper motor anticlockwise.

Something Cool Implemented in This Lab
-------------------------------------------------
It is read the degree or rotation it will rotate by factor of full sequnce "60 degree {4 steps}".


Sugguestions for This Lab
-------------------------------------------------
Add a line in the examble code refering of importaing to turn off the stepper motor and dont let it stock in the last of 
posation which cause heating in the winding of motor and unnessary drian of the battery.


Typos, Errors, or Comments of The Textbook
-------------------------------------------------
Example 16-3:typo ochange to 8 in the array + change 96 to 12 becaue the inside loop will move motor 8 steps
(3.75x8)=30 while the big loop will complete the sequince by repate the exact sequnce 12x30 to complete full rotation


Lab Credit
-------------------------------------------------
Did you received any help from someone other than 
Professor Zhu and lab assistants?

Pre-Lab Question
-------------------------------------------------
1.  How to change the rotation speed of a stepper motor? 
delying the shifting process will change the rotation speed

2.  How to reverse the rotation direction? 
Change the sequnce insade (A->A' to A'->A) and instade (B->B' to B'->B)

Post-lab Assignments 
-------------------------------------------------
1.  Last year, one group of students used the stepper motors used in this lab to build a 
robotic car. However, they found that the motors did not have enough torque to 
move the car. What solution you could have?  

Change to larger motor or put gear box to increase the torqe of the motor

2.  The Darlington array has only 500-mA rated collector current. If you need a larger 
current, what option you can have to replace the Darlington array.  

Using H-Bridge of MOSFET or any power transester and isolate the power circuit from contol circuit + put diode parrale to each
transister for freewheeling the current left in the winding.

Academic Dishonesty
-------------------------------------------------
Academic dishonesty includes cheating, plagiarism
and all forms of misrepresentation in academic work, 
and is unacceptable at The University of Maine. As 
stated in the University of Maine's online 
undergraduate "Student Handbook," plagiarism 
(the submission of another's work without appropriate 
attribution) and cheating are violations of The 
University of Maine Student Conduct Code. An 
instructor who has probable cause or reason to 
believe a student has cheated may act upon such evidence, 
and should report the case to the supervising faculty 
member or the Department Chair for appropriate action.

