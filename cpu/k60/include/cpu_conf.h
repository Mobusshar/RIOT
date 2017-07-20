/*
 * Copyright (C) 2015 Eistec AB
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @defgroup        cpu_k60 Freescale Kinetis K60
 * @ingroup         cpu
 * @brief           CPU specific implementations for the Freescale Kinetis K60
 * @{
 *
 * @file
 * @brief           Implementation specific CPU configuration options
 *
 * @author          Joakim Nohlgård <joakim.nohlgard@eistec.se>
 */

#ifndef CPU_CONF_H
#define CPU_CONF_H

#include "cpu_conf_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#if defined(CPU_MODEL_MK60DN512VLL10) || defined(CPU_MODEL_MK60DN256VLL10)
#include "vendor/MK60D10.h"

/* K60 rev 2.x replaced the RNG module in 1.x by the RNGA PRNG module */
#define KINETIS_RNGA            (RNG)
#else
#error Unknown CPU model. Update Makefile.include in the board directory.
#endif

/**
 * @brief This CPU provides an additional ADC clock divider as CFG1[ADICLK]=1
 */
#define KINETIS_HAVE_ADICLK_BUS_DIV_2 1

/**
 * @brief   ARM Cortex-M specific CPU configuration
 * @{
 */
#define CPU_DEFAULT_IRQ_PRIO            (1U)
#define CPU_IRQ_NUMOF                   (104U)
#define CPU_FLASH_BASE                  (0x00000000)
/** @} */

/**
 * @name GPIO pin mux function numbers
 */
/** @{ */
#define PIN_MUX_FUNCTION_ANALOG 0
#define PIN_MUX_FUNCTION_GPIO 1
/** @} */
/**
 * @name GPIO interrupt flank settings
 */
/** @{ */
#define PIN_INTERRUPT_RISING 0b1001
#define PIN_INTERRUPT_FALLING 0b1010
#define PIN_INTERRUPT_EDGE 0b1011
/** @} */

/**
 * @name Timer hardware information
 */
/** @{ */
#define LPTMR_CLKEN()  (bit_set32(&SIM->SCGC5, SIM_SCGC5_LPTMR_SHIFT)) /**< Enable LPTMR0 clock gate */
#define PIT_CLKEN()    (bit_set32(&SIM->SCGC6, SIM_SCGC6_PIT_SHIFT)) /**< Enable PIT clock gate */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* CPU_CONF_H */
/** @} */
