################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/yali/git/yali_noam/cpp/HW_2/Date.cpp \
C:/Users/yali/git/yali_noam/cpp/HW_2/Delivery.cpp \
../Main.cpp 

OBJS += \
./Date.o \
./Delivery.o \
./Main.o 

CPP_DEPS += \
./Date.d \
./Delivery.d \
./Main.d 


# Each subdirectory must supply rules for building sources it contributes
Date.o: C:/Users/yali/git/yali_noam/cpp/HW_2/Date.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Delivery.o: C:/Users/yali/git/yali_noam/cpp/HW_2/Delivery.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


