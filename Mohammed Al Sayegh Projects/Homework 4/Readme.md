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
Mohammed H. Al-Sayegh


Code for Homework 4:
-------------------------------------------------

Product8 PROC

	PUSH {r4-r9, lr}
	MOV r4, r0
	LDR r5, [sp, #20]
	LDR r5, [sp, #24]
	LDR r5, [sp, #28]
	LDR r5, [sp, #32]
	MUL r9, r4, r1
	MUL r9, r4, r1
	MUL r9, r4, r1
	MUL r9, r4, r1
	MUL r9, r4, r1
	MUL r9, r4, r1
	MUL r9, r4, r1
	MUL r9, r4, r1
	POP {r4-r9, pc}
	
	ENDP
	END

