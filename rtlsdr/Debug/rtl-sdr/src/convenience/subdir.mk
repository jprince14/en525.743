################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtl-sdr/src/convenience/convenience.c 

OBJS += \
./rtl-sdr/src/convenience/convenience.o 

C_DEPS += \
./rtl-sdr/src/convenience/convenience.d 


# Each subdirectory must supply rules for building sources it contributes
rtl-sdr/src/convenience/%.o: ../rtl-sdr/src/convenience/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/libusb-1.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


