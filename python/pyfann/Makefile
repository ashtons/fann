# This makefile was written to compile a distribution of pyfann for
# GNU platforms (cygwin included.)

TARGETS = _libfann.so

PYTHON=python2.3
FANN_DIR="../.."
LIBS=-L. -L/usr/local/lib -L/usr/bin -l$(PYTHON) $(FANN_DIR)/src/fann*.o

all: $(TARGETS)
	
_%.so: pyfann_wrap.o fann_helper.o
	gcc $(LIBS) -fPIC -shared -dll $^ -o $@

%.o: %.c 
	gcc -fPIC -shared -c $< -I/usr/include/$(PYTHON)/ -I$(FANN_DIR)/src/include/

pyfann_wrap.cpp: pyfann.i 
	swig -c++ -python $<

clean:
	rm -f $(TARGETS) *_wrap.* *.py{c,o} *.so libfann.*
