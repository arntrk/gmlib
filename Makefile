
INCLUDE = -I Include
TEST = -I Test
FLAGS = -Wall -std=c++14
LIBS = -lGL -lGLEW -lglfw
EXEC=spline
TESTEXEC=tests
OUTDIR=bin
OBJDIR=obj
OBJFILES = $(patsubst %, $(OBJDIR)/%,$^)

all: spline

spline: main.o windowbase.o mywindow.o
	g++ $(OBJFILES) -o $(OUTDIR)/$(EXEC) $(LIBS) && ./$(OUTDIR)/$(EXEC)

main.o: main.cpp
	g++ $(FLAGS) $(INCLUDE) -o $(OBJDIR)/$@ -g -c main.cpp

windowbase.o: src/WindowBaseClass.cpp
	g++ $(FLAGS) $(INCLUDE) -o $(OBJDIR)/$@ -g -c $^

mywindow.o: src/myWindowClass.cpp
	g++ $(FLAGS) $(INCLUDE) -o $(OBJDIR)/$@ -g -c $^

test: catch.o test.o
	g++ $(OBJFILES) -o $(OUTDIR)/$(TESTEXEC) && ./$(OUTDIR)/$(TESTEXEC)

catch.o: catch.cpp
	g++ $(FLAGS) $(TEST) -o $(OBJDIR)/$@ -c $^

test.o: test.cpp
	g++ $(FLAGS) $(INCLUDE) $(TEST) -o $(OBJDIR)/$@ -c test.cpp

clean:
	rm -rf $(OBJDIR)/*o $(OUTDIR)/$(TESTEXEC) $(OUTDIR)/$(EXEC)

