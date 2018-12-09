################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HexHelper.cpp \
../src/crypto.cpp \
../src/crypto_AES.cpp 

OBJS += \
./src/HexHelper.o \
./src/crypto.o \
./src/crypto_AES.o 

CPP_DEPS += \
./src/HexHelper.d \
./src/crypto.d \
./src/crypto_AES.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


