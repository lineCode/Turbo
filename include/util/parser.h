#ifndef TURBO_PARSER_H
#define TURBO_PARSER_H

#include "util/util_def.h"

namespace TURBO
{
    namespace UTIL
    {
        const int BUFFER_SIZE = 4096;
        const int BUFFER_REFILL_SIZE = 250;

        class Parser
        {
        public:
            static bool isNumericChar(char c);
            static bool isAlphabeticChar(char c);
            static bool isIdentifierChar(char c);
            static bool isSpaceChar(char c);
            static bool isWhitespaceChar(char c);
            static bool isLTChar(char c);
            static bool isGTChar(char c);
            static bool isEqualChar(char c);
            static bool isQuoteChar(char c);
            static bool isSlashChar(char c);
            static bool isMinusChar(char c);
            static bool isPlusChar(char c);
            static bool isCommaChar(char c);
            static bool isColonChar(char c);
            static bool isSemicolonChar(char c);
            static bool isExclamationChar(char c);
            static bool isQuestionChar(char c);
            static bool isSquareBracketOpenChar(char c);
            static bool isSquareBracketCloseChar(char c);
            static bool isCurlyBracketOpenChar(char c);
            static bool isCurlyBracketCloseChar(char c);
        };
    }
}

#endif //TURBO_PARSER_H
