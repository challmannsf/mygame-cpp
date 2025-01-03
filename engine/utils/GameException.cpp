#include "GameException.h"


const char* GameException::what() {
    return message;
}



GameException::exception_category_levels GameException::get_exception_category() const {
    return static_cast<exception_category_levels>(exception_category);
}