/* 
 *  libpinyin
 *  Library to deal with pinyin.
 *  
 *  Copyright (C) 2016 Peng Wu <alexepico@gmail.com>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PINYIN_PHRASE3_H
#define PINYIN_PHRASE3_H

#include "novel_types.h"
#include "chewing_key.h"

namespace pinyin{

inline int pinyin_exact_compare2(const ChewingKey * key_lhs,
                                 const ChewingKey * key_rhs,
                                 int phrase_length){
    int i;
    int result;

    /* compare initial */
    for (i = 0; i < phrase_length; ++i) {
        result = key_lhs[i].m_initial - key_rhs[i].m_initial;
        if (0 != result)
            return result;
    }

    /* compare middle and final */
    for (i = 0; i < phrase_length; ++i) {
        result = key_lhs[i].m_middle - key_rhs[i].m_middle;
        if (0 != result)
            return result;
        result = key_lhs[i].m_final - key_rhs[i].m_final;
        if (0 != result)
            return result;
    }

    /* compare tone */
    for (i = 0; i < phrase_length; ++i) {
        result = key_lhs[i].m_tone - key_rhs[i].m_tone;
        if (0 != result)
            return result;
    }

    return 0;
}


template<size_t phrase_length>
struct PinyinIndexItem2{
    phrase_token_t m_token;
    ChewingKey m_keys[phrase_length];
public:
    PinyinIndexItem2<phrase_length> (const ChewingKey * keys,
                                     phrase_token_t token) {
        memmove(m_keys, keys, sizeof(ChewingKey) * phrase_length);
        m_token = token;
    }
};


/* for find the element in the phrase array */
template<size_t phrase_length>
inline int phrase_exact_compare2(const PinyinIndexItem2<phrase_length> &lhs,
                                 const PinyinIndexItem2<phrase_length> &rhs)
{
    ChewingKey * keys_lhs = (ChewingKey *) lhs.m_keys;
    ChewingKey * keys_rhs = (ChewingKey *) rhs.m_keys;
    return pinyin_exact_compare2(keys_lhs, keys_rhs, phrase_length);
}

template<size_t phrase_length>
inline bool phrase_exact_less_than2(const PinyinIndexItem2<phrase_length> &lhs,
                                    const PinyinIndexItem2<phrase_length> &rhs)
{
    return 0 > phrase_exact_compare2<phrase_length>(lhs, rhs);
}


};

#endif
