################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cfca.c \
../src/fca.c \
../src/fcaV.c \
../src/fcaVnextClosureX.c 

OBJS += \
./src/cfca.o \
./src/fca.o \
./src/fcaV.o \
./src/fcaVnextClosureX.o 

C_DEPS += \
./src/cfca.d \
./src/fca.d \
./src/fcaV.d \
./src/fcaVnextClosureX.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -D_GNU_SOURCE -O0 -g3 -pedantic -Wall -Wextra -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


