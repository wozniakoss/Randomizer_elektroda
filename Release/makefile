################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Randomizer_elektroda.lss \

FLASH_IMAGE += \
Randomizer_elektroda.hex \

EEPROM_IMAGE += \
Randomizer_elektroda.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Randomizer_elektroda.elf secondary-outputs

# Tool invocations
Randomizer_elektroda.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Randomizer_elektroda.map -mmcu=attiny2313 -o"Randomizer_elektroda.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Randomizer_elektroda.lss: Randomizer_elektroda.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Randomizer_elektroda.elf  >"Randomizer_elektroda.lss"
	@echo 'Finished building: $@'
	@echo ' '

Randomizer_elektroda.hex: Randomizer_elektroda.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Randomizer_elektroda.elf  "Randomizer_elektroda.hex"
	@echo 'Finished building: $@'
	@echo ' '

Randomizer_elektroda.eep: Randomizer_elektroda.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Randomizer_elektroda.elf  "Randomizer_elektroda.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Randomizer_elektroda.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 Randomizer_elektroda.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Randomizer_elektroda.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
