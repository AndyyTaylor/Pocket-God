################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Application.cpp \
../Source/Display.cpp \
../Source/EventHandler.cpp \
../Source/Model.cpp \
../Source/Text.cpp 

OBJS += \
./Source/Application.o \
./Source/Display.o \
./Source/EventHandler.o \
./Source/Model.o \
./Source/Text.o 

CPP_DEPS += \
./Source/Application.d \
./Source/Display.d \
./Source/EventHandler.d \
./Source/Model.d \
./Source/Text.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -framework Opengl -std=c++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


