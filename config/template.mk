###############################################################################
# collect build config from template variables
###############################################################################

# define output target file and additional variants
build_path:={BUILD_PATH}
output_name:={OUTPUT_NAME}
output_variants:={OUTPUT_VARIANTS}
ifeq ($(output_variants),)
build_targets:=$(build_path)/$(output_name)
else
build_targets:=$(foreach variant,$(output_name),$(build_path)/$(output_name).$(variant))
endif

# define key commands
c_cmd:={C_CMD}
cxx_cmd:={CXX_CMD}
as_cmd:={AS_CMD}
ld_cmd:={LD_CMD}
objcopy_cmd:={OBJCOPY_CMD}
objdump_cmd:={OBJDUMP_CMD}

# define input files
c_input_files:={C_INPUT_FILES}
cxx_input_files:={CXX_INPUT_FILES}
as_input_files:={AS_INPUT_FILES}
ld_input_files:={LD_INPUT_FILES}

# define intermediate files
c_objs:=$(addsuffix .o,$(addprefix $(build_path)/, $(c_input_files)))
cxx_objs:=$(addsuffix .o,$(addprefix $(build_path)/, $(cxx_input_files)))

# define compiler/linker flags
c_flags:={C_FLAGS}
cxx_flags:={CXX_FLAGS}
as_flags:={AS_FLAGS}
ld_flags:={LD_FLAGS}


###############################################################################
# define rules for building targets
###############################################################################

# c compile rules
$(build_path)/%.c.o:%.c
	@mkdir -p $(@D)
	$(c_cmd) $(c_flags) -c -o $@ $<


# c++ compile rules
$(build_path)/%.cc.o:%.cc
	@mkdir -p $(@D)
	$(cxx_cmd) $(cxx_flags) -c -o $@ $<

$(build_path)/%.cpp.o:%.cpp
	@mkdir -p $(@D)
	$(cxx_cmd) $(cxx_flags) -c -o $@ $<


# asm compile rules
$(build_path)/%.S.o:%.S
	@mkdir -p $(@D)
	$(as_cmd) $(as_flags) -c -o $@ $<

$(build_path)/%.s.o:%.s
	@mkdir -p $(@D)
	$(as_cmd) $(as_flags) -c -o $@ $<


# primary build target
$(build_path)/$(output_name):$(c_objs) $(cxx_objs)
	@mkdir -p $(@D)
	$(ld_cmd) $(ld_flags) -o $@ $^


# output variant rules
$(build_path)/$(output_name).hex:$(output_name)
	@mkdir -p $(@D)
	$(objcopy_cmd) -O ihex $^ $@

$(build_path)/$(output_name).bin:$(output_name)
	@mkdir -p $(@D)
	$(objcopy_cmd) -O binary $^ $@

$(build_path)/$(output_name).elf:$(output_name)
	@mkdir -p $(@D)
	$(objcopy_cmd) -O elf32-littlearm $^ $@


# build output targets
build:$(build_targets)
	@echo "Done."
