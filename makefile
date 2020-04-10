calculator: calc.o token.o mystack.o
	gcc -o calculator calc.o token.o mystack.o -lm

calc.o: calc.c calc.h token.h mystack.h
	gcc -c calc.c -lm

token.o: token.c calc.h token.h mystack.h
	gcc -c token.c -lm

mystack.o: mystack.c mystack.h
	gcc -c mystack.c -lm
