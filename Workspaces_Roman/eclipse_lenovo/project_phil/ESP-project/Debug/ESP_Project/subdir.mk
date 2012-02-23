################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ESP_Project/database.cpp \
../ESP_Project/develop_main.cpp \
../ESP_Project/driver.cpp \
../ESP_Project/monitor.cpp \
../ESP_Project/packets.cpp \
../ESP_Project/scoreboard.cpp \
../ESP_Project/stimulator.cpp 

OBJS += \
./ESP_Project/database.o \
./ESP_Project/develop_main.o \
./ESP_Project/driver.o \
./ESP_Project/monitor.o \
./ESP_Project/packets.o \
./ESP_Project/scoreboard.o \
./ESP_Project/stimulator.o 

CPP_DEPS += \
./ESP_Project/database.d \
./ESP_Project/develop_main.d \
./ESP_Project/driver.d \
./ESP_Project/monitor.d \
./ESP_Project/packets.d \
./ESP_Project/scoreboard.d \
./ESP_Project/stimulator.d 


# Each subdirectory must supply rules for building sources it contributes
ESP_Project/%.o: ../ESP_Project/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -IC:/cygwin/usr/local/scv_debug/include -IC:/cygwin/usr/local/systemc_debug/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


