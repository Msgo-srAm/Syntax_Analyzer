/**
 * @file State.hpp
 * @brief 状态枚举定义
 * @author srAm-dev
 * @version 0.1
 * @date 2025-12-11
 * @copyright Copyright (c) 2025 srAm-dev
 * SPDX-License-Identifier: WTFPL
 * Licensed under the WTFPL.
 */
#ifndef STATE_HPP
#define STATE_HPP

/**
 * @brief 状态枚举定义
 *
 * 该枚举定义了语法分析器中的所有状态,
 * 用于表示LALR分析表中的状态编号,对应Parser.output中的状态。
 *
 * @note 其中S_error表示错误状态。
 */
enum State {
    S_error = -1,
    S0 = 0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    S10,
    S11,
    S12,
    S13,
    S14,
    S15,
    S16,
    S17,
    S18,
    S19,
    S20,
    S21,
    S22,
    S23,
    S24,
    S25,
    S26,
    S27,
    S28,
    S29,
    S30,
    S31,
    S32,
    S33,
    S34,
    S35,
    S36,
    S37,
    S38,
    S39,
    S40,
    S41,
    S42,
    S43,
    S44,
    S45,
    S46,
    S47,
    S48,
    S49,
    S50,
    S51,
    S52,
    S53,
    S54,
    S55,
    S56,
    S57,
    S58,
    S59,
    S60,
    S61,
    S62,
    S63,
    S64,
    S65
};

#endif // STATE_HPP