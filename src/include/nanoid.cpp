#include "./nanoid.hpp"
/**
 * Contains a set of useful alphabets
 */
namespace nanoid {
namespace alphabets {
/**
 * Default alphabet
 */
string_alphabet DEFAULT_ALPHABET =
    "_-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**
 * Only numbers (0 to 9)
 */
string_alphabet NUMBERS = "0123456789";

/**
 * Uppercase english letters
 */
string_alphabet UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**
 * Lowercase english letters
 */
string_alphabet LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

/**
 * Numbers and english alphabet without lookalikes: 1, l, I, 0, O, o, u, v, 5,
 * S, s
 */
string_alphabet NO_LOOK_ALIKES =
    "2346789ABCDEFGHJKLMNPQRTUVWXYZabcdefghijkmnpqrtwxyz";
} // namespace alphabets
} // namespace nanoid
