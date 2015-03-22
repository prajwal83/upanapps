/* automatically generated from ./regs.dat - do not edit */

#ifndef _REGS_H_
#define _REGS_H_

/*
 * Special values for expr->type. ASSUMPTION MADE HERE: the number
 * of distinct register names (i.e. possible "type" fields for an
 * expr structure) does not exceed 124 (EXPR_REG_START through
 * EXPR_REG_END).
 */
#define EXPR_REG_START 1
#define EXPR_REG_END 124
#define EXPR_UNKNOWN 125L       /* for forward references */
#define EXPR_SIMPLE 126L
#define EXPR_WRT 127L
#define EXPR_SEGBASE 128L


enum reg_enum {
    R_AH = EXPR_REG_START,
    R_AL,
    R_AX,
    R_BH,
    R_BL,
    R_BP,
    R_BX,
    R_CH,
    R_CL,
    R_CR0,
    R_CR1,
    R_CR2,
    R_CR3,
    R_CR4,
    R_CR5,
    R_CR6,
    R_CR7,
    R_CS,
    R_CX,
    R_DH,
    R_DI,
    R_DL,
    R_DR0,
    R_DR1,
    R_DR2,
    R_DR3,
    R_DR4,
    R_DR5,
    R_DR6,
    R_DR7,
    R_DS,
    R_DX,
    R_EAX,
    R_EBP,
    R_EBX,
    R_ECX,
    R_EDI,
    R_EDX,
    R_ES,
    R_ESI,
    R_ESP,
    R_FS,
    R_GS,
    R_MM0,
    R_MM1,
    R_MM2,
    R_MM3,
    R_MM4,
    R_MM5,
    R_MM6,
    R_MM7,
    R_SEGR6,
    R_SEGR7,
    R_SI,
    R_SP,
    R_SS,
    R_ST0,
    R_ST1,
    R_ST2,
    R_ST3,
    R_ST4,
    R_ST5,
    R_ST6,
    R_ST7,
    R_TR0,
    R_TR1,
    R_TR2,
    R_TR3,
    R_TR4,
    R_TR5,
    R_TR6,
    R_TR7,
    R_XMM0,
    R_XMM1,
    R_XMM2,
    R_XMM3,
    R_XMM4,
    R_XMM5,
    R_XMM6,
    R_XMM7,
    REG_ENUM_LIMIT
};

#endif
