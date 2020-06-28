
include $(HOME)/project/cpp/transaction-dsl/shared/defs.mk

all-suites-paths=$(notdir $(patsubst %/, %, $(dir $(shell find . -name Makefile))))
all-suites=$(shell find . -name *Test.so)
all-clean-targets=$(addprefix clean_, $(all-suites-paths))

.PHONY: all clean $(all-suites-paths) $(all-clean-targets)


all : $(all-suites-paths)
	@echo "running $(all-suites) ... "
	@$(testngpp-runner) $(all-suites) -L$(testngpp-listener-path) -l"testngppstdoutlistener -c -v -s -l3"

nocolor-all : $(all-suites-paths)
	@echo "running $(all-suites) ... "
	@$(testngpp-runner) $(all-suites) -L$(testngpp-listener-path) -l"testngppstdoutlistener -l3" -s 

clean : 
	@for dir in $(all-suites-paths); do \
		cd $$dir && $(MAKE) -f Makefile clean-all; cd ..;\
	done

clean_% : 
	@echo "cleaning $* ... "
	@cd %* && make -f Makefile clean

$(all-suites-paths) :
	@cd $@ && make -f Makefile build-only
