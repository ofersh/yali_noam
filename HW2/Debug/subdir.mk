################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/git/yali_noam/cpp/HW_2/Date.cpp \
/git/yali_noam/cpp/HW_2/Delivery.cpp \
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
Date.o: /git/yali_noam/cpp/HW_2/Date.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Delivery.o: /git/yali_noam/cpp/HW_2/Delivery.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


