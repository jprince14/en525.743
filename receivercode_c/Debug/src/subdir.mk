################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/audio.c \
../src/demod.c \
../src/encoder.c \
../src/receivercode_c.c \
../src/tcpsocket.c \
../src/udpsocket.c 

OBJS += \
./src/audio.o \
./src/demod.o \
./src/encoder.o \
./src/receivercode_c.o \
./src/tcpsocket.o \
./src/udpsocket.o 

C_DEPS += \
./src/audio.d \
./src/demod.d \
./src/encoder.d \
./src/receivercode_c.d \
./src/tcpsocket.d \
./src/udpsocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


