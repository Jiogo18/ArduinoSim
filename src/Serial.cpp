#include "Serial.h"

SerialLib::SerialLib() : adresse(0) {}

void SerialLib::begin(int adresse)
{
    this->adresse = adresse;
}

void SerialLib::println(const char* line) { std::cout << charsToOem(line) << std::endl; }
void SerialLib::println(int v) { std::cout << v << std::endl; }
void SerialLib::println(double v) { std::cout << v << std::endl; }
void SerialLib::println(bool v) { std::cout << v << std::endl; }

void SerialLib::print(const char* line) { std::cout << charsToOem(line); }
void SerialLib::print(int v) { std::cout << v; }
void SerialLib::print(double v) { std::cout << v; }
void SerialLib::print(bool v) { std::cout << v; }

int SerialLib::charToOem(int c)
{
    switch(c) {
    case -64: return 183; // À
    case -63: return 181; // Á
    case -62: return 182; // Â
    case -61: return 199; // Ã
    case -60: return 142; // Ä
    case -59: return 143; // Å

    case -58: return 146; // Æ
    case -57: return 128; // Ç

    case -56: return 212; // È
    case -55: return 144; // É
    case -54: return 210; // Ê
    case -53: return 211; // Ë

    case -52: return 222; // Ì
    case -51: return 214; // Í
    case -50: return 215; // Î
    case -49: return 216; // Ï

    case -47: return 165; // Ñ

    case -46: return 227; // Ò
    case -45: return 224; // Ó
    case -44: return 226; // Ô
    case -43: return 229; // Õ
    case -42: return 153; // Ö

    case -39: return 235; // Ù
    case -38: return 233; // Ú
    case -37: return 234; // Û
    case -36: return 154; // Ü

    case -32: return 133; // à
    case -31: return 160; // á
    case -30: return 131; // â
    case -29: return 198; // ã
    case -28: return 132; // ä

    case -26: return 145; // æ
    case -25: return 135; // ç

    case -24: return 138; // è
    case -23: return 130; // é
    case -22: return 136; // ê
    case -21: return 137; // ë

    case -20: return 141; // ì
    case -19: return 161; // í
    case -18: return 140; // î
    case -17: return 139; // ï

    case -15: return 164; // ñ

    case -14: return 149; // ò
    case -13: return 162; // ó
    case -12: return 147; // ô
    case -10: return 148; // ö
    case -11: return 228; // õ

    case -7: return 151; // ù
    case -6: return 163; // ú
    case -5: return 150; // û
    case -4: return 129; // ü

    case -1: return 152; // ÿ

    default: return c;
    }
}

std::string SerialLib::charsToOem(const char *line)
{
    std::string output = std::string(std::strlen(line), ' ');
    for(size_t i = 0; i < std::strlen(line); i++) {
        output[i] = charToOem(line[i]);
    }
    return output;
}
