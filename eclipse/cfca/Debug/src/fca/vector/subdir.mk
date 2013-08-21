################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fca/vector/fcaV.c \
../src/fca/vector/fcaVnextClosureX.c 

OBJS += \
./src/fca/vector/fcaV.o \
./src/fca/vector/fcaVnextClosureX.o 

C_DEPS += \
./src/fca/vector/fcaV.d \
./src/fca/vector/fcaVnextClosureX.d 


# Each subdirectory must supply rules for building sources it contributes
src/fca/vector/%.o: ../src/fca/vector/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -D_GNU_SOURCE -O0 -g3 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


