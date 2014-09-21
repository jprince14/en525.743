################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/librtlsdr.c \
../src/rtl_adsb.c \
../src/rtl_eeprom.c \
../src/rtl_fm.c \
../src/rtl_power.c \
../src/rtl_sdr.c \
../src/rtl_tcp.c \
../src/rtl_test.c \
../src/tuner_e4k.c \
../src/tuner_fc0012.c \
../src/tuner_fc0013.c \
../src/tuner_fc2580.c \
../src/tuner_r82xx.c 

OBJS += \
./src/librtlsdr.o \
./src/rtl_adsb.o \
./src/rtl_eeprom.o \
./src/rtl_fm.o \
./src/rtl_power.o \
./src/rtl_sdr.o \
./src/rtl_tcp.o \
./src/rtl_test.o \
./src/tuner_e4k.o \
./src/tuner_fc0012.o \
./src/tuner_fc0013.o \
./src/tuner_fc2580.o \
./src/tuner_r82xx.o 

C_DEPS += \
./src/librtlsdr.d \
./src/rtl_adsb.d \
./src/rtl_eeprom.d \
./src/rtl_fm.d \
./src/rtl_power.d \
./src/rtl_sdr.d \
./src/rtl_tcp.d \
./src/rtl_test.d \
./src/tuner_e4k.d \
./src/tuner_fc0012.d \
./src/tuner_fc0013.d \
./src/tuner_fc2580.d \
./src/tuner_r82xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/libusb-1.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


