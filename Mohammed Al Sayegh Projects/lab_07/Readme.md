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

Mohammed H Al-Sayegh



Lab Status Summary

-------------------------------------------------



The sensor ulterisonic connect send trigger and recive differnt time of the echo and display it in the LCD screen

Something Cool Implemented in This Lab

-------------------------------------------------
Display distance in the LCD screen.




Sugguestions for This Lab

-------------------------------------------------



Add more refferance to the GPIO configuration to the Timer 2 channel 3. I had to go through several hour to relize it differnt than Timer 4 and 3 channel 1 and 2 from the book. The AFR is not 10.

Typos, Errors, or Comments of The Textbook

-------------------------------------------------






Lab Credit

-------------------------------------------------



Did you received any help from someone other than 
Professor Zhu and lab assistants?



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



1. Does the timer counter count up or down in your lab ? If counting up, how did you handle the counter overflow?
(If counting down, how did you handle the counter underflow ? )
countdown, tranlate the assamble code in page 340 to C language-> (check SR and set it with value of CC1F page 334)

2.What is the accuracy when measuring the period of 1Hz square wave ?
tolerance of 5 percent from orginal signial code be cause by wiring

3.What is the accuracy of the distance you have measured?
0.3 ~ 0.6 cm

4.What is the most challenge issue you had in this lab?
There is no much referance to ARR sitting for different timer. I made mistake in code take me several days to relize that channel 3 with timer 2 have different value configuration to sit alternative function.

5. Do you have any suggestions or comments of this lab?
You should add the table for different timer to sit in alternive kfunction for different pin, different channel and how they connect to differnt timer. It is no clear not in the book. Add the value of AFR sitting or the page to different timer.

6.Do you have any comments of the textbook?
Sit examble for PWM using timer wich help to understand the sitting rather than understand the sitting for only one timer.