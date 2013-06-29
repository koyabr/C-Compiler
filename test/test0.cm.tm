* Begin prelude
  0:     LD  6,0(0) 	load from location 0
  1:     ST  0,0(0) 	clear location 0
  2:    LDA  4,0(6) 	allocate for global variables
* End of prelude
* Jump to main()
* Begin input()
  9:     IN  1,0,0 	read input into ax
 10:    LDA  4,1(4) 	pop prepare
 11:     LD  7,-1(4) 	pop return addr
* End input()
* Begin output()
 12:     LD  1,1(4) 	load param into ax
 13:    OUT  1,0,0 	output using ax
 14:    LDA  4,1(4) 	pop prepare
 15:     LD  7,-1(4) 	pop return addr
* End output()
* -> function:
 16:    LDA  4,-1(4) 	push prepare
 17:     ST  5,0(4) 	push old bp
 18:    LDA  5,0(4) 	let bp == sp
 19:    LDA  4,-3(4) 	allocate for local variables
* -> compound
* -> assign
* -> variable
 20:    LDA  2,-1(5) 	get local address
* <- variable
 21:    LDA  4,-1(4) 	push prepare
 22:     ST  2,0(4) 	protect bx
* -> number
 23:    LDC  1,3(0) 	store number
* <- number
 24:    LDA  4,1(4) 	pop prepare
 25:     LD  2,-1(4) 	recover bx
 26:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> variable
 27:    LDA  2,-2(5) 	get local address
* <- variable
 28:    LDA  4,-1(4) 	push prepare
 29:     ST  2,0(4) 	protect bx
* -> number
 30:    LDC  1,2(0) 	store number
* <- number
 31:    LDA  4,1(4) 	pop prepare
 32:     LD  2,-1(4) 	recover bx
 33:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> variable
 34:    LDA  2,-3(5) 	get local address
* <- variable
 35:    LDA  4,-1(4) 	push prepare
 36:     ST  2,0(4) 	protect bx
* -> number
 37:    LDC  1,1(0) 	store number
* <- number
 38:    LDA  4,1(4) 	pop prepare
 39:     LD  2,-1(4) 	recover bx
 40:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> variable
 41:    LDA  2,-3(5) 	get local address
* <- variable
 42:    LDA  4,-1(4) 	push prepare
 43:     ST  2,0(4) 	protect bx
* -> op
* -> op
* -> variable
 44:    LDA  2,-2(5) 	get local address
 45:     LD  1,0(2) 	get variable value
* <- variable
 46:    LDA  4,-1(4) 	push prepare
 47:     ST  1,0(4) 	op: protect left
* -> op
* -> op
* -> variable
 48:    LDA  2,-3(5) 	get local address
 49:     LD  1,0(2) 	get variable value
* <- variable
 50:    LDA  4,-1(4) 	push prepare
 51:     ST  1,0(4) 	op: protect left
* -> variable
 52:    LDA  2,-1(5) 	get local address
 53:     LD  1,0(2) 	get variable value
* <- variable
 54:    LDA  4,1(4) 	pop prepare
 55:     LD  2,-1(4) 	op: recover left
 56:    MUL  1,2,1 	op *
* <- op
 57:    LDA  4,-1(4) 	push prepare
 58:     ST  1,0(4) 	op: protect left
* -> variable
 59:    LDA  2,-2(5) 	get local address
 60:     LD  1,0(2) 	get variable value
* <- variable
 61:    LDA  4,1(4) 	pop prepare
 62:     LD  2,-1(4) 	op: recover left
 63:    DIV  1,2,1 	op /
* <- op
 64:    LDA  4,1(4) 	pop prepare
 65:     LD  2,-1(4) 	op: recover left
 66:    ADD  1,2,1 	op +
* <- op
 67:    LDA  4,-1(4) 	push prepare
 68:     ST  1,0(4) 	op: protect left
* -> variable
 69:    LDA  2,-3(5) 	get local address
 70:     LD  1,0(2) 	get variable value
* <- variable
 71:    LDA  4,1(4) 	pop prepare
 72:     LD  2,-1(4) 	op: recover left
 73:    SUB  1,2,1 	op -
* <- op
 74:    LDA  4,1(4) 	pop prepare
 75:     LD  2,-1(4) 	recover bx
 76:     ST  1,0(2) 	assign: store
* <- assign
* -> call
* -> variable
 77:    LDA  2,-3(5) 	get local address
 78:     LD  1,0(2) 	get variable value
* <- variable
 79:    LDA  4,-1(4) 	push prepare
 80:     ST  1,0(4) 	push parameters
 81:    LDA  1,3(7) 	store returned PC
 82:    LDA  4,-1(4) 	push prepare
 83:     ST  1,0(4) 	push returned PC
 84:    LDC  7,12(0) 	jump to function
 85:    LDA  4,1(4) 	release parameters
* <- call
* -> return
* -> number
 86:    LDC  1,1(0) 	store number
* <- number
 87:    LDA  4,0(5) 	let sp == bp
 88:    LDA  4,2(4) 	pop prepare
 89:     LD  5,-2(4) 	pop old bp
 90:     LD  7,-1(4) 	pop return addr
* <- return
* <- compound
* <- function
  3:    LDA  1,3(7) 	store returned PC
  4:    LDA  4,-1(4) 	push prepare
  5:     ST  1,0(4) 	push returned PC
  6:    LDC  7,16(0) 	jump to function
  7:    LDA  4,0(4) 	release parameters
  8:   HALT  0,0,0 	END OF PROGRAM
