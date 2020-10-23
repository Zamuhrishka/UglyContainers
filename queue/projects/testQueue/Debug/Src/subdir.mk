################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/usart.c \
../Src/vector.c 

OBJS += \
./Src/dma.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/usart.o \
./Src/vector.o 

C_DEPS += \
./Src/dma.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/usart.d \
./Src/vector.d 


# Each subdirectory must supply rules for building sources it contributes
Src/dma.o: ../Src/dma.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/dma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/gpio.o: ../Src/gpio.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/stm32f4xx_hal_msp.o: ../Src/stm32f4xx_hal_msp.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32f4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/stm32f4xx_it.o: ../Src/stm32f4xx_it.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/system_stm32f4xx.o: ../Src/system_stm32f4xx.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/usart.o: ../Src/usart.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/vector.o: ../Src/vector.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -D__QUEUE_STATIC_MODE -DUNIT_TESTING -DSLRE_DEBUG -DDEBUG '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc/arch/arm" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/inc" -I../Inc -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/3rd_party/cmockery" -I"D:/sasha/study/stm32/develop/containers/fwContainers/queue/projects/testQueue/Middleware/Debug/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/vector.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

