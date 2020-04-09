calculator: calc.o token.o mystack.o
	gcc -o calculator calc.o token.o mystack.o

calc.o: calc.c calc.h token.h mystack.h
	gcc -c calc.c

token.o: token.c calc.h token.h mystack.h
	gcc -c token.c

mystack.o: mystack.c mystack.h
	gcc -c mystack.c
