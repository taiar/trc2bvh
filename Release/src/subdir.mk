################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/bvh.cpp \
../src/geom.cpp \
../src/trc.cpp \
../src/trcRead.cpp 

OBJS += \
./src/bvh.o \
./src/geom.o \
./src/trc.o \
./src/trcRead.o 

CPP_DEPS += \
./src/bvh.d \
./src/geom.d \
./src/trc.d \
./src/trcRead.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


