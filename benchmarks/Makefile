# The jneural library (http://voltar-confed.org/jneural/) and lwneuralnet library (http://sourceforge.net/projects/lwneuralnet/) needs to be installed in order to run the benchmarks

GCC = gcc
G++ = g++

TARGETS = quality quality_fixed performance performance_fixed shuffle parity two-spirals

CFLAGS = -O3 -finline-functions -funroll-loops -Werror

LFLAGS = -lm

JNEURALDIR = ../../libraries/jneural/

LWNNDIR = ../../libraries/lwneuralnet-0.8/source/

all: $(TARGETS)

quality: quality.cc
	$(G++) $(CFLAGS) $(LFLAGS) -I$(JNEURALDIR)include/ -L$(JNEURALDIR) -I$(LWNNDIR) -L$(LWNNDIR) $< -o $@ -lfloatfann -llwneuralnet -ljneural -lfl

quality_fixed: quality_fixed.c
	$(GCC) $(CFLAGS) $(LFLAGS) $< -o $@ -lfixedfann

quality_fixed_debug: quality_fixed.c
	$(GCC) -ggdb -lm -DDEBUG -Wall -ansi -I../src/ -I../src/include/ ../src/fixedfann.c $< -o $@

performance: performance.cc
	$(G++) $(CFLAGS) $(LFLAGS) -I$(JNEURALDIR)include/ -L$(JNEURALDIR) -I$(LWNNDIR) -L$(LWNNDIR) $< -o $@ -lfloatfann -llwneuralnet -ljneural -lfl

performance_fixed: performance.cc
	$(G++) $(CFLAGS) $(LFLAGS) -DFIXEDFANN $< -o $@ -lfixedfann

shuffle: shuffle.c
	$(GCC) $(CFLAGS) $(LFLAGS) $< -o $@ -lfloatfann

two-spirals: two-spirals.c
	$(GCC) $(CFLAGS) $(LFLAGS) $< -o $@

parity: parity.c
	$(GCC) $(CFLAGS) $(LFLAGS) $< -o $@

clean: 
	rm -rf -- $(TARGETS) *~

distclean: clean
	rm -rf *.ps *.out *.net *fixed_test* *fixed_train*
