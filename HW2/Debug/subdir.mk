################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BoogieLever.cpp \
../Clerk.cpp \
../Date.cpp \
../Delivery.cpp \
../Edge.cpp \
../EdgeCargo.cpp \
../EdgeTime.cpp \
../Main.cpp \
../Port.cpp 

OBJS += \
./BoogieLever.o \
./Clerk.o \
./Date.o \
./Delivery.o \
./Edge.o \
./EdgeCargo.o \
./EdgeTime.o \
./Main.o \
./Port.o 

CPP_DEPS += \
./BoogieLever.d \
./Clerk.d \
./Date.d \
./Delivery.d \
./Edge.d \
./EdgeCargo.d \
./EdgeTime.d \
./Main.d \
./Port.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


