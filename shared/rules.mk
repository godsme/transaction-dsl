
include-paths = $(project-home)/include \
                . \
                $(project-home)/../cub/include \
                $(project-home)/../event/include \
                $(mockcpp-include-path) \
                $(testngpp-include-path) \
                $(project-home)/tests/utils/include \
                /usr/local/3rdparty

INCLUDE=$(addprefix -I, $(abspath $(include-paths)))
           
LIBS += -L$(testngpp-lib-path) -ltestngpp -ltestngpp-user /usr/local/lib/libevent.a 

$(suite-name)Test.cc :
	@echo "generating $@ ..."
	@$(TEST_SUITE_GENERATOR) $*

Test%.cc:Test%.h
	@$(TEST_GENERATOR) -o $@ $^

full-path-extra-srcs=$(addprefix $(PWD)/../../src/, $(extra-srcs))

SRCS=$(abspath $(all-tests-srcs) $(full-path-extra-srcs))
OBJS=$(SRCS:.cc=.o)
DEPS=$(SRCS:.cc=.d)

$(suite-name)Test.so : $(suite-name)Test.cc $(OBJS)
	@echo "linking $@ ..."
	$(LINK) -O3 -o $@ $(LIBS) $^ $(INCLUDE)

$(suite-name)Test : $(suite-name)Test.cc $(OBJS)
	$(LD) -o $@ $^ $(INCLUDE) $(LIBS) -ltestngpp-static-runner-lib -ltestngpp-utils-shared -ldl

%.o : %.cc
	@echo "compiling $^ ..."
	@$(CC) -o $@ -c $^ $(INCLUDE)

%.d : %.cc
	@rm -f $@; \
	$(CC) -MM $(INCLUDE) $< > $@.$$$$; \
	sed 's,/($*/)/.o[ :]*,/1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

sinclude $(DEPS)

clean-all : clean
	@rm -f $(OBJS) $(DEPS)

