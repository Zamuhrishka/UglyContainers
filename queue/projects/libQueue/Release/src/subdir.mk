################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/sasha/study/stm32/develop/containers/fwContainers/queue/static/src/queue.c 

OBJS += \
./src/queue.o 

C_DEPS += \
./src/queue.d 


# Each subdirectory must supply rules for building sources it contributes
src/queue.o: D:/sasha/study/stm32/develop/containers/fwContainers/queue/static/src/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/static/inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

