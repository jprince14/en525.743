################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtl-sdr/src/librtlsdr.c \
../rtl-sdr/src/rtl_adsb.c \
../rtl-sdr/src/rtl_eeprom.c \
../rtl-sdr/src/rtl_fm.c \
../rtl-sdr/src/rtl_power.c \
../rtl-sdr/src/rtl_sdr.c \
../rtl-sdr/src/rtl_tcp.c \
../rtl-sdr/src/rtl_test.c \
../rtl-sdr/src/tuner_e4k.c \
../rtl-sdr/src/tuner_fc0012.c \
../rtl-sdr/src/tuner_fc0013.c \
../rtl-sdr/src/tuner_fc2580.c \
../rtl-sdr/src/tuner_r82xx.c 

OBJS += \
./rtl-sdr/src/librtlsdr.o \
./rtl-sdr/src/rtl_adsb.o \
./rtl-sdr/src/rtl_eeprom.o \
./rtl-sdr/src/rtl_fm.o \
./rtl-sdr/src/rtl_power.o \
./rtl-sdr/src/rtl_sdr.o \
./rtl-sdr/src/rtl_tcp.o \
./rtl-sdr/src/rtl_test.o \
./rtl-sdr/src/tuner_e4k.o \
./rtl-sdr/src/tuner_fc0012.o \
./rtl-sdr/src/tuner_fc0013.o \
./rtl-sdr/src/tuner_fc2580.o \
./rtl-sdr/src/tuner_r82xx.o 

C_DEPS += \
./rtl-sdr/src/librtlsdr.d \
./rtl-sdr/src/rtl_adsb.d \
./rtl-sdr/src/rtl_eeprom.d \
./rtl-sdr/src/rtl_fm.d \
./rtl-sdr/src/rtl_power.d \
./rtl-sdr/src/rtl_sdr.d \
./rtl-sdr/src/rtl_tcp.d \
./rtl-sdr/src/rtl_test.d \
./rtl-sdr/src/tuner_e4k.d \
./rtl-sdr/src/tuner_fc0012.d \
./rtl-sdr/src/tuner_fc0013.d \
./rtl-sdr/src/tuner_fc2580.d \
./rtl-sdr/src/tuner_r82xx.d 


# Each subdirectory must supply rules for building sources it contributes
rtl-sdr/src/%.o: ../rtl-sdr/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/libusb-1.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


