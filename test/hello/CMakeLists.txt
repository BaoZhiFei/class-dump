message("Current ${PROJECT_NAME}")
set(HELLO_SOURCE "
#import <Foundation/Foundation.h>
@interface Hello : NSObject
@end
@implementation Hello
@end
")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/hello.m ${HELLO_SOURCE})

add_test(NAME hello-setup COMMAND clang -c ${CMAKE_CURRENT_BINARY_DIR}/hello.m -o ${CMAKE_CURRENT_BINARY_DIR}/hello.o)
add_test(NAME hello-test COMMAND class-dump ${CMAKE_CURRENT_BINARY_DIR}/hello.o)