cmake_minimum_required(VERSION 4.0)
project(JitVM)

set(CMAKE_CXX_STANDARD 20)

ENABLE_TESTING()

add_executable(JitVM
        src/lexer/lexer.c
        src/typedefs/TokenType.h
        src/typedefs/bool.h
        src/typedefs/khash.h
        src/typedefs/Array.h
        src/lexer/lexer.h
        src/parser/parser.h
        src/parser/parser.c
        src/typedefs/ast.h
        src/bytecode_comp/bc.c
        src/bytecode_comp/common.h
        src/bytecode_comp/debug.h
        src/bytecode_comp/debug.c
        src/vm/vm.h
        src/vm/vm.c
)

add_subdirectory(src/bytecode_comp)
add_subdirectory(src/vm)

add_test(test
        test/lexerTest.c
)
target_sources(JitVM PRIVATE
        src/parser/parser.c

)


