################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/demod.c \
../src/receivercode_c.c \
../src/tcpsocket.c 

OBJS += \
./src/demod.o \
./src/receivercode_c.o \
./src/tcpsocket.o 

C_DEPS += \
./src/demod.d \
./src/receivercode_c.d \
./src/tcpsocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


