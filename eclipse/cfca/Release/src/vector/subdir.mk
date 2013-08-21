################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/vector/fcaV.c \
../src/vector/fcaVnextClosureX.c 

OBJS += \
./src/vector/fcaV.o \
./src/vector/fcaVnextClosureX.o 

C_DEPS += \
./src/vector/fcaV.d \
./src/vector/fcaVnextClosureX.d 


# Each subdirectory must supply rules for building sources it contributes
src/vector/%.o: ../src/vector/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -D_GNU_SOURCE -O3 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


