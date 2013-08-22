################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fca/easy/fca.c \
../src/fca/easy/measurement.c 

OBJS += \
./src/fca/easy/fca.o \
./src/fca/easy/measurement.o 

C_DEPS += \
./src/fca/easy/fca.d \
./src/fca/easy/measurement.d 


# Each subdirectory must supply rules for building sources it contributes
src/fca/easy/%.o: ../src/fca/easy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -D_GNU_SOURCE -O0 -g3 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


