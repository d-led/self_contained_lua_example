# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug32
endif
export config

PROJECTS := bundle self_contained_lua_example

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

bundle: 
	@echo "==== Building bundle ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f bundle.make

self_contained_lua_example: bundle
	@echo "==== Building self_contained_lua_example ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f self_contained_lua_example.make

clean:
	@${MAKE} --no-print-directory -C . -f bundle.make clean
	@${MAKE} --no-print-directory -C . -f self_contained_lua_example.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug32"
	@echo "   release32"
	@echo "   debug64"
	@echo "   release64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   bundle"
	@echo "   self_contained_lua_example"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
