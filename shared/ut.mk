
PROJECT_HOME=$(HOME)/project/trans-dsl
event-src=../../event/src

include $(PROJECT_HOME)/shared/defs.mk

TEST_GENERATOR=$(PYTHON) $(TESTNGPP_ROOT)/testngpp/generator/testngppgen.pyc 
TEST_SUITE_GENERATOR=$(PYTHON) $(TESTNGPP_ROOT)/testngpp/generator/testng-suite-gen.pyc 

testngpp-include-path=$(TESTNGPP_ROOT)/include
mockcpp-include-path=$(MOCKCPP_ROOT)/include

testngpp-lib-path=$(TESTNGPP_ROOT)/lib
mockcpp-lib-path=$(MOCKCPP_ROOT)/lib

all-tests-files=$(shell ls $(PWD)/Test*.h)
all-tests-srcs=$(subst .h,.cc,$(all-tests-files))
suite-name=$(notdir $(PWD))
project-home=$(PWD)/../..
extra-srcs=

#CC=g++ -std=c++0x -fpermissive
CC=g++-4.8 -std=c++0x -g  -O2 -Wall -Wunused-variable -Wno-unused-result -Wunused-function
LINK=$(CC) -g -fPIC -shared -Wl,--no-undefined -Wno-invalid-offsetof
LD=$(CC) -g -Wl,--no-undefined -Wno-invalid-offsetof

TESTSUITE=$(suite-name)Test

.PHONY: all clean clean-all build-only

all : build-only
	@$(testngpp-runner) $(TESTSUITE).so -L$(TESTNGPP_ROOT)/testngpp/listener -l"testngppstdoutlistener -v -c -s " $(test-filter) $(tags)

nocolor-all : build-only
	@$(testngpp-runner) $(TESTSUITE).so -L$(TESTNGPP_ROOT)/testngpp/listener -l"testngppstdoutlistener -s " -s $(test-filter) $(tags)

bin : $(TESTSUITE)
	@./$(TESTSUITE) -L$(TESTNGPP_ROOT)/testngpp/listener -l"testngppstdoutlistener -v -c -s "  $(test-filter) $(tags)

build-only: $(TESTSUITE).so

clean : 
	@rm -f $(TESTSUITE) $(TESTSUITE).so $(PWD)/*.cc 

