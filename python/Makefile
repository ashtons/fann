# This makefile was written to compile a distribution of pyfann for
# GNU platforms (cygwin included.)

ROOT=/
PYTHON=python

SOURCES = pyfann/*.i pyfann/*.h
all: build-stamp

linux:
	@(cd pyfann && make)

clean:
	@(cd pyfann && make clean)
	@rm -fr dist build setup.pyc
	@rm -fr examples/{nets,pyfann/}
	@rm -f build-stamp
	
msvc:
	@(cd pyfann && make -f makefile.msvc)

build:
build-stamp: ../src/doublefann.o $(SOURCES)
	@$(PYTHON) setup.py build
	@touch build-stamp

install: build-stamp
	@$(PYTHON) setup.py install --root $(ROOT)

../src/doublefann.o: ../Makefile
	@(cd .. && make )

../Makefile:
	@(cd .. && ./configure)

copy: build-stamp
	@- [ -d examples/nets ] || mkdir examples/nets
	@cp build/lib.*/pyfann/ -a examples
    
test: copy
	@cd examples && \
		$(PYTHON) simple_train.py && \
		$(PYTHON) mushroom.py &&\
		$(PYTHON) cascade_train.py
.PHONY: test install msvc clean linux all
