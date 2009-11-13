SUBDIRS = src

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = fann.pc

EXTRA_DIST = benchmarks examples MicrosoftVisualC++6.0 MicrosoftVisualC++.Net \
	MicrosoftWindowsDll BorlandC++Builder6.0 src/include/config.h \
	debian/changelog debian/compat debian/control debian/copyright \
	debian/docs debian/libfann2-dev.dirs debian/libfann2-dev.examples \
	debian/libfann2-dev.files debian/libfann2-dev.install \
	debian/libfann2.dirs debian/libfann2.files debian/libfann2.install \
	debian/libfann2-py.dirs  debian/libfann2-py.files \
	debian/libfann2-py.install debian/rules \
	doc/advancedusage.txt doc/gettingstarted.txt doc/theory.txt \
	doc/fixedpointusage.txt doc/installation.txt doc/fann_en.pdf \
	python

dist-hook:
	rm -rf `find $(distdir) -name "*~" -o -name ".#*" -o -name "CVS"`
	(cd $(distdir)/examples && make clean)
	(cd $(distdir)/python && make clean)
	(cd $(distdir)/benchmarks && make clean)
	zip -9 -r $(distdir).zip $(distdir)
	tar chojf $(distdir).tar.bz2 $(distdir)
