################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Date.cpp \
../Delivery.cpp \
../Edge.cpp \
../Main.cpp \
../Port.cpp 

OBJS += \
./Date.o \
./Delivery.o \
./Edge.o \
./Main.o \
./Port.o 

CPP_DEPS += \
./Date.d \
./Delivery.d \
./Edge.d \
./Main.d \
./Port.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


