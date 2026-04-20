#include <iostream>
#include "ui/ui.hpp"
#include "exceptions/exceptions.hpp"

int main() {
    try {
    open_ui();
    } catch(RangeError& e){
        std::cerr << "range error occured: " << e.what() << std::endl;
    } catch(InvalidArgumentError& e){
        std::cerr << "invalid argument error occured: " << e.what() << std::endl;
    } catch(FailedAllocationError& e){
        std::cerr << "failed allocation error occured: " << e.what() << std::endl;
    }
    return 0;
}