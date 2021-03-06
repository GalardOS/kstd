# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  kstd_config = debug

else ifeq ($(config),release)
  kstd_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := kstd

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

kstd:
ifneq (,$(kstd_config))
	@echo "==== Building kstd ($(kstd_config)) ===="
	@${MAKE} --no-print-directory -C . -f kstd.make config=$(kstd_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f kstd.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   kstd"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"