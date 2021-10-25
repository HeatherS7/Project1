cmake_minimum_required(VERSION 3.16.3)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(TestCases)

add_executable(Project1_Starter_Code
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        makefile
        Token.cpp
        Token.h
        CommaAutomaton.h
        CommaAutomaton.cpp
        PeriodAutomaton.cpp
        PeriodAutomaton.h Q_MarkAutomaton.cpp Q_MarkAutomaton.h Left_ParenAutomaton.cpp Left_ParenAutomaton.h Right_ParenAutomaton.cpp Right_ParenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h IdAutomaton.cpp IdAutomaton.h StringAutomaton.cpp StringAutomaton.h CommentAutomaton.cpp CommentAutomaton.h UndefinedAutomaton.cpp UndefinedAutomaton.h End_Of_FileAutomaton.h Parser.cpp Parser.h Parameter.cpp Parameter.h Predicate.cpp Predicate.h Rule.cpp Rule.h DatalogProgram.cpp DatalogProgram.h Tuple.h Header.h Relation.cpp Relation.h Database.cpp Database.h Tuple.cpp Header.cpp Interpreter.cpp Interpreter.h)
