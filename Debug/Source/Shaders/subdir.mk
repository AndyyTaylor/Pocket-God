################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Shaders/Shader_Loader.cpp \
../Source/Shaders/Shader_Program.cpp 

OBJS += \
./Source/Shaders/Shader_Loader.o \
./Source/Shaders/Shader_Program.o 

CPP_DEPS += \
./Source/Shaders/Shader_Loader.d \
./Source/Shaders/Shader_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Shaders/%.o: ../Source/Shaders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -framework Opengl -std=c++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


