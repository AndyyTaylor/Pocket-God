################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Math/Matrix.cpp 

OBJS += \
./Source/Math/Matrix.o 

CPP_DEPS += \
./Source/Math/Matrix.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Math/%.o: ../Source/Math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -framework Opengl -std=c++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


