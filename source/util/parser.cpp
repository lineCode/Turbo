#include "util/parser.h"

namespace TURBO
{
    namespace UTIL
    {
        // [\n | \t | ' ']
        bool Parser::isWhitespaceChar(char c)
        {
            return c == 0x0A || c == 0x09 || Parser::isSpaceChar(c);
        }

        // ' '
        bool Parser::isSpaceChar(char c)
        {
            return c == 0x20;
        }

        // !
        bool Parser::isExclamationChar(char c)
        {
            return c == 0x21;
        }

        // "
        bool Parser::isQuoteChar(char c)
        {
            return c == 0x22;
        }

        // +
        bool Parser::isPlusChar(char c)
        {
            return c == 0x2B;
        }

        // ,
        bool Parser::isCommaChar(char c)
        {
            return c == 0x2C;
        }

        // -
        bool Parser::isMinusChar(char c)
        {
            return c == 0x2D;
        }

        // /
        bool Parser::isSlashChar(char c)
        {
            return c == 0x2F;
        }

        // [0-9]
        bool Parser::isNumericChar(char c)
        {
            return (c >= 0x30 && c <= 0x39);
        }

        // :
        bool Parser::isColonChar(char c)
        {
            return c == 0x3A;
        }

        // ;
        bool Parser::isSemicolonChar(char c)
        {
            return c == 0x3B;
        }

        // <
        bool Parser::isLTChar(char c)
        {
            return c == 0x3C;
        }

        // =
        bool Parser::isEqualChar(char c)
        {
            return c == 0x3D;
        }

        // >
        bool Parser::isGTChar(char c)
        {
            return c == 0x3E;
        }

        // ?
        bool Parser::isQuestionChar(char c)
        {
            return c == 0x3F;
        }

        // [A-Z | a-z]
        bool Parser::isAlphabeticChar(char c)
        {
            return (c >= 0x41 && c <= 0x5A) || (c >= 0x61 && c <= 0x7A);
        }

        // [_ | A-Z | a-z]
        bool Parser::isIdentifierChar(char c)
        {
            return c == 0x5F || Parser::isAlphabeticChar(c);
        }

        // [
        bool Parser::isSquareBracketOpenChar(char c)
        {
            return c == 0x5B;
        }

        // ]
        bool Parser::isSquareBracketCloseChar(char c)
        {
            return c == 0x5D;
        }

        // {
        bool Parser::isCurlyBracketOpenChar(char c)
        {
            return c == 0x7B;
        }

        // }
        bool Parser::isCurlyBracketCloseChar(char c)
        {
            return c == 0x7D;
        }
    }
}