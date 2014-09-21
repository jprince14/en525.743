################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/convenience/convenience.c 

OBJS += \
./src/convenience/convenience.o 

C_DEPS += \
./src/convenience/convenience.d 


# Each subdirectory must supply rules for building sources it contributes
src/convenience/%.o: ../src/convenience/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/libusb-1.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


