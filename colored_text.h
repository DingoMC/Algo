#ifndef COLORED_TEXT_H
#define COLORED_TEXT_H
#include <string>
#include <vector>
#include <random>
#include <windows.h>
// Namespace of Colored Text
namespace ct {
    // Handle to Console
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // CT Color Executor
    const char Executor = '&';
    // Color Palette
    enum Color {BLACK = 0, DARK_BLUE = 1, DARK_GREEN = 2, CYAN = 3, DARK_RED = 4, PURPLE = 5, ORANGE = 6, GRAY = 7, DARK_GRAY = 8,
                BLUE = 9, GREEN = 10, AQUA = 11, RED = 12, PINK = 13, YELLOW = 14, WHITE = 15};
    // CT Modifiers List
    const std::vector <char> Modifiers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // Rainbow Sequence Colors List
    const std::vector <WORD> RainbowSequence = {0x04, 0x0c, 0x06, 0x0e, 0x0a, 0x02, 0x03, 0x0b, 0x09, 0x05};
    // Rainbow Sequence Colors List (with inverted background)
    const std::vector <WORD> BgRainbowSequence = {0xb4, 0x3c, 0x96, 0x1e, 0x5a, 0xd2, 0xc3, 0x4b, 0x69, 0xa5};
}
// Colored Text Class
class ctext {
    public:
        // Displays colored text
        static void text (const std::string &CT_text) {
            for (unsigned int i = 0; i < CT_text.length(); i++) {
                if (CheckCTExecutor(CT_text, i)) {
                    SetConsoleTextAttribute(ct::ConsoleHandle, ConvertModifierToColor(CT_text.at(i+1)));
                    i++;
                }
                else std::cout<<CT_text.at(i);
            }
        }
        // Displays single-colored text (Color passed by argument)
        static void text (const std::string &text, ct::Color text_color) {
            SetConsoleTextAttribute(ct::ConsoleHandle, text_color);
            std::cout<<text;
        }
        // Displays colored text + background
        static void bgtext (const std::string &CTB_text) {
            for (unsigned int i = 0; i < CTB_text.length(); i++) {
                if (CheckCTBExecutor(CTB_text, i)) {
                    SetConsoleTextAttribute(ct::ConsoleHandle, ConvertModifierToColor(CTB_text.at(i+1), CTB_text.at(i+2)));
                    i+=2;
                }
                else std::cout<<CTB_text.at(i);
            }
        }
        // Displays single-colored text + background (Colors passed by argument)
        static void bgtext (const std::string &text, ct::Color backgd_color, ct::Color text_color) {
            SetConsoleTextAttribute(ct::ConsoleHandle, backgd_color*16+text_color);
            std::cout<<text;
        }
        // Displays rainbow cycling text
        static void rainbow_text (const std::string &text) {
            // Rainbow Index Sequencer
            std::vector <int> Sequencer;
            unsigned int size = text.length() > 10 ? 10 : text.length();
            if (text.at(text.length()-1) == '\n' && text.length() > 1 && text.length() <= 10) size--;
            Sequencer.resize(size);
            SetRainbowSequencer(Sequencer, size);
            for (unsigned int i = 0; i < text.length(); i++) {
                SetConsoleTextAttribute(ct::ConsoleHandle, ct::RainbowSequence[Sequencer[i%size]]);
                std::cout<<text.at(i);
            }
        }
        // Displays rainbow cycling text (with inverted background)
        static void rainbow_bgtext (const std::string &text) {
            // Rainbow Index Sequencer
            std::vector <int> Sequencer;
            unsigned int size = text.length() > 10 ? 10 : text.length();
            if (text.at(text.length()-1) == '\n' && text.length() > 1 && text.length() <= 10) size--;
            Sequencer.resize(size);
            SetRainbowSequencer(Sequencer, size);
            for (unsigned int i = 0; i < text.length(); i++) {
                SetConsoleTextAttribute(ct::ConsoleHandle, ct::BgRainbowSequence[Sequencer[i%size]]);
                std::cout<<text.at(i);
            }
        }
    private:
        // Checks if there is a modifier after executor sign
        static bool CheckCTExecutor (const std::string &CT_text, unsigned int iter_at) {
            if (CT_text.at(iter_at) != ct::Executor) return false;
            if (iter_at >= CT_text.length() - 1) return false;
            for (unsigned int i = 0; i < 16; i++) if (CT_text.at(iter_at+1) == ct::Modifiers[i]) return true;
            return false;
        }
        // Checks if there are 2 modifiers after executor sign
        static bool CheckCTBExecutor (const std::string &CTB_text, unsigned int iter_at) {
            if (CTB_text.at(iter_at) != ct::Executor) return false;
            if (iter_at >= CTB_text.length() - 2) return false;
            bool t_modifier_ok = false;
            for (unsigned int i = 0; i < 16; i++) {
                if (CTB_text.at(iter_at+1) == ct::Modifiers[i]) {
                    t_modifier_ok = true;
                    break;
                }
            }
            if (t_modifier_ok) for (unsigned int i = 0; i < 16; i++) if (CTB_text.at(iter_at+2) == ct::Modifiers[i]) return true;
            return false;
        }
        // Converts Modfier to Text Color
        static WORD ConvertModifierToColor (char t_modifier) {
            if (t_modifier >= 48 && t_modifier <= 57) return (int) t_modifier - 48;
            if (t_modifier >= 97 && t_modifier <= 102) return (int) t_modifier - 87;
            return 0x00;
        }
        // Converts Modifiers to Background Color + Text Color
        static WORD ConvertModifierToColor (char b_modifier, char t_modifier) {
            WORD value = 0x00;
            if (b_modifier >= 48 && b_modifier <= 57) value += 16 * ((int) b_modifier - 48);
            if (b_modifier >= 97 && b_modifier <= 102) value += 16 * ((int) b_modifier - 87);
            if (t_modifier >= 48 && t_modifier <= 57) value += (int) t_modifier - 48;
            if (t_modifier >= 97 && t_modifier <= 102) value += (int) t_modifier - 87;
            return value;
        }
        // Set rainbow sequencer
        static void SetRainbowSequencer (std::vector <int> &Sequencer, unsigned int size) {
            switch (size) {
                case 1: {Sequencer = {0}; break;}
                case 2: {Sequencer = {0, 9}; break;}
                case 3: {Sequencer = {0, 5, 9}; break;}
                case 4: {Sequencer = {0, 3, 6, 9}; break;}
                case 5: {Sequencer = {0, 2, 4, 6, 9}; break;}
                case 6: {Sequencer = {0, 2, 4, 6, 7, 9}; break;}
                case 7: {Sequencer = {0, 1, 2, 4, 6, 7, 9}; break;}
                case 8: {Sequencer = {0, 1, 2, 4, 5, 6, 7, 9}; break;}
                case 9: {Sequencer = {0, 1, 2, 3, 4, 5, 6, 7, 9}; break;}
                default: {Sequencer = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; break;}
            }
        }
};
#endif // !COLORED_TEXT_H