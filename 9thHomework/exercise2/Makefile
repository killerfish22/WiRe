exercise2: exercise2.c liblapack_pocket.a 
	gcc -o $@ $^ -lblas -lm -lgfortran

liblapack_pocket.a: dgeev.o
	ar crs $@ $<

dgeev.o: dgeev.f
	gfortran -c $<