###############################################################################
# collect build config from template variables
###############################################################################

# define output target file and additional variants
build_path:={BUILD_PATH}
output_name:={OUTPUT_NAME}
output_variants:={OUTPUT_VARIANTS}

primary_output:=$(build_path)/$(output_name)
ifeq ($(output_variants),)
build_targets:=$(primary_output)
else
build_targets:=$(foreach variant,$(output_variants),$(build_path)/$(output_name).$(variant))
endif

$(info primary output: $(primary_output))
$(info build target(s): $(build_targets))

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

inc_dirs:={INC_DIRS}

# define intermediate files
c_objs:=$(addsuffix .o,$(addprefix $(build_path)/, $(c_input_files)))
cxx_objs:=$(addsuffix .o,$(addprefix $(build_path)/, $(cxx_input_files)))
as_objs:=$(addsuffix .o,$(addprefix $(build_path)/, $(as_input_files)))

# define compiler/linker flags
c_flags:={C_FLAGS} $(inc_dirs)
cxx_flags:={CXX_FLAGS} $(inc_dirs)
as_flags:={AS_FLAGS} $(inc_dirs)
ld_flags:={LD_FLAGS} $(inc_dirs)

# define dependency-related flags, files
dep_flags=-MT $@ -MMD -MP -MF $(patsubst %.o, %.d, $@)
dep_files:=$(patsubst %.o, %.d, $(c_objs) $(cxx_objs))

# assign default target to override included makefiles
default:build

# include additional variables and makefiles
{MAKE_VARS}

{MAKE_INCLUDES}

###############################################################################
# define rules for building targets
###############################################################################

# default target
default:build


# dependencies rules
$(dep_files):

include $(wildcard $(dep_files))


# build output targets
build:$(build_targets)
	@echo "Done."


# output variant rules
$(build_path)/$(output_name).hex:$(primary_output)
	@mkdir -p $(@D)
	@echo 
	@echo generating hex file
	$(objcopy_cmd) -O ihex $^ $@

$(build_path)/$(output_name).bin:$(primary_output)
	@mkdir -p $(@D)
	@echo 
	@echo generating bin file
	$(objcopy_cmd) -O binary $^ $@

$(build_path)/$(output_name).elf:$(primary_output)
	@mkdir -p $(@D)
	@echo 
	@echo generating elf file
	$(objcopy_cmd) -O elf32-littlearm $^ $@

$(build_path)/$(output_name).map:$(primary_output)
	@mkdir -p $(@D)
	@echo 
	@echo generating map file
	$(objdump_cmd) -S $^ > $@


# primary build target
$(primary_output):$(c_objs) $(cxx_objs) $(as_objs)
	@mkdir -p $(@D)
	@echo 
	@echo linking $@
	$(ld_cmd) $^ $(ld_flags) -o $@
	

# c compile rules
$(build_path)/%.c.o:%.c
	@mkdir -p $(@D)
	@echo 
	@echo compiling $<
	$(c_cmd) $(c_flags) $(dep_flags) -c -o $@ $<


# c++ compile rules
$(build_path)/%.cc.o:%.cc
	@mkdir -p $(@D)
	@echo 
	@echo compiling $<
	$(cxx_cmd) $(cxx_flags) $(dep_flags) -c -o $@ $<

$(build_path)/%.cpp.o:%.cpp
	@mkdir -p $(@D)
	@echo 
	@echo compiling $<
	$(cxx_cmd) $(cxx_flags) $(dep_flags) -c -o $@ $<


# asm compile rules
$(build_path)/%.S.o:%.S
	@mkdir -p $(@D)
	@echo 
	@echo assembling $<
	$(as_cmd) $(as_flags) -c -o $@ $<

$(build_path)/%.s.o:%.s
	@mkdir -p $(@D)
	@echo 
	@echo assembling $<
	$(as_cmd) $(as_flags) -c -o $@ $<