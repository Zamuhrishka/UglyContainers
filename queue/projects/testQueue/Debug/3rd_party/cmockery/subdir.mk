################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rd_party/cmockery/cmockery.c 

OBJS += \
./3rd_party/cmockery/cmockery.o 

C_DEPS += \
./3rd_party/cmockery/cmockery.d 


# Each subdirectory must supply rules for building sources it contributes
3rd_party/cmockery/cmockery.o: ../3rd_party/cmockery/cmockery.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"3rd_party/cmockery/cmockery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

