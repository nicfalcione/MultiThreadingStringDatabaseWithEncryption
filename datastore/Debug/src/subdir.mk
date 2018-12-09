################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data_store.cpp \
../src/data_store_file.cpp \
../src/string_data.cpp 

OBJS += \
./src/data_store.o \
./src/data_store_file.o \
./src/string_data.o 

CPP_DEPS += \
./src/data_store.d \
./src/data_store_file.d \
./src/string_data.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


