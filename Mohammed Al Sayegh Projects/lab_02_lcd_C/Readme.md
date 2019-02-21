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

Lab Status Summary
-------------------------------------------------


Something Cool Implemented in This Lab
-------------------------------------------------


Sugguestions for This Lab
-------------------------------------------------


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



1.Suppose  the  duty  ratio  of  a  LCD  display  is  ¼  and  it  has  a  total  of  120  display  segments  
(pixels).  How  many  pins  are  required  to  drive  this  LCD?  

35 pin

2.Figure  2  the  alternative  function selection  of  a  GPIO  pin.  Does  a  GPIO  pin  can  perform  all functions  listed  in Figure  2?

Yes

3.Figure  3  shows  the  basic  diagram  of  LCD  driver.  Is  this  driver  built  in  within  the  processor chip?  What  is  the  function  of  the  COM  driver  
and  SEG  driver?

Yes,

4.How  many  pixels  does  the  STM32L  processor  LCD  driver  can  drive?  How  large  is  the LCD_RAM  in  terms  of  bits?  (Read  STM32L  Reference  Manual)

around 512 pixels, The size of the memory is 32x16bit.


5.How  many  pixels  on  the  LCD  installed  on  the  STM32L  discovery  kit?  Explain  why  many LCD_RAM  registers (such  as  LCD_RAM[1],  LCD_RAM[3],  LCD_RAM[5])  are  not  used  for  
STM32L  discovery  kit.

96 pixels , to sign the value of each pixle 