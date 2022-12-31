//
//  PG/UnitTests/TableTest.cpp
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#include "g/Table.h"
#include "gtest/gtest.h"

TEST(Table, BugTableTest) {
    Table<size_t, unsigned> table(1); // BUG -  no default constructor available

    EXPECT_TRUE(true);
}

TEST(Table, TableTest) {
    Table<size_t, unsigned> table(4);   // 4 columns

    table[0][0] = 0;
    table[1][1] = 1;
    table[2][2] = 2;
    table[3][3] = 3;

    EXPECT_TRUE(table[0][0] == 0);
    EXPECT_TRUE(table[1][1] == 1);
    EXPECT_TRUE(table[2][2] == 2);
    EXPECT_TRUE(table[3][3] == 3);

    EXPECT_TRUE(table[0][1] == 0);
    EXPECT_TRUE(table[0][2] == 0);
    EXPECT_TRUE(table[0][3] == 0);
}

TEST(Table, CompressedTableTest) {
    Table<size_t, unsigned> table(4);   // 4 columns

    table[0][0] = 0;
    table[0][1] = 1;
    table[0][2] = 2;
    table[0][3] = 3;

    table[1][0] = 1;
    table[1][1] = 2;
    table[1][2] = 3;
    table[1][3] = 4;

    table[2][0] = 0;
    table[2][1] = 1;
    table[2][2] = 2;
    table[2][3] = 3;

    table[3][0] = 1;
    table[3][1] = 2;
    table[3][2] = 3;
    table[3][3] = 4;

    CompressedTable<size_t, unsigned> compressedTable(&table);

    EXPECT_TRUE(compressedTable[0][0] == 0);
    EXPECT_TRUE(compressedTable[0][1] == 1);
    EXPECT_TRUE(compressedTable[0][2] == 2);
    EXPECT_TRUE(compressedTable[0][3] == 3);

    EXPECT_TRUE(compressedTable[1][0] == 1);
    EXPECT_TRUE(compressedTable[1][1] == 2);
    EXPECT_TRUE(compressedTable[1][2] == 3);
    EXPECT_TRUE(compressedTable[1][3] == 4);

    EXPECT_TRUE(compressedTable[2][0] == 0);
    EXPECT_TRUE(compressedTable[2][1] == 1);
    EXPECT_TRUE(compressedTable[2][2] == 2);
    EXPECT_TRUE(compressedTable[2][3] == 3);

    EXPECT_TRUE(compressedTable[3][0] == 1);
    EXPECT_TRUE(compressedTable[3][1] == 2);
    EXPECT_TRUE(compressedTable[3][2] == 3);
    EXPECT_TRUE(compressedTable[3][3] == 4);

    EXPECT_TRUE(compressedTable.getNumberOfRows() == 4);
    EXPECT_TRUE(compressedTable.getNumberOfCompressedRows() == 2);
}


struct Action {
    enum Function : unsigned {
        Shift,
        Reduce,
        Accept,
        Error
    };

    Action() : action(Error), value(0) {}
    Action(Function action, size_t value) : action(action), value(value) {}
    Action(Function action) : action(action), value(0) {}

    Function action : 2;
    unsigned int value : 30;

    friend bool operator == (const Action& lhs, const Action& rhs) {
        return lhs.action == rhs.action && lhs.value == rhs.value;
    }
    friend bool operator != (const Action& lhs, const Action& rhs) {
        return !(lhs == rhs);
    }
    std::string toString() const {
        std::stringstream ss;
        switch (action) {
        case Shift:
            ss << "s" << std::to_string(value);
            break;
        case Reduce:
            ss << "r" << std::to_string(value);
            break;
        case Accept:
            ss << "a";
            break;
        case Error:
            ss << "-";
            break;
        }
        return ss.str();
    }
    std::string toCXXString() const {
        std::stringstream ss;
        switch (action) {
        case Shift:
            ss << "{Action::Function::Shift, " << std::to_string(value) << "}";
            break;
        case Reduce:
            ss << "{Action::Function::Reduce, " << std::to_string(value) << "}";
            break;
        case Accept:
            ss << "{Action::Function::Accept}";
            break;
        case Error:
            ss << "{Action::Function::Error}";
            break;
        }
        return ss.str();
    }
};

inline std::string AsString(Action value) {
    std::string s = value.toString();
    return s;
}

inline std::string AsCXXString(Action value) {
    std::string s = value.toCXXString();
    return s;
}

TEST(Table, ClassBasedCompressedTableTest) {
    Table<size_t, Action> table(4);   // 4 columns

    table[0][0] = Action(Action::Function::Shift, 1);
    table[0][1] = Action(Action::Function::Reduce, 2);
    table[0][2] = Action(Action::Function::Accept);
    table[0][3] = Action(Action::Function::Error);

    table[1][0] = Action(Action::Function::Accept);
    table[1][1] = Action(Action::Function::Error);
    table[1][2] = Action(Action::Function::Error);
    table[1][3] = Action(Action::Function::Error);

    table[2][0] = Action(Action::Function::Shift, 1);
    table[2][1] = Action(Action::Function::Reduce, 2);
    table[2][2] = Action(Action::Function::Accept);
    table[2][3] = Action(Action::Function::Error);

    table[3][0] = Action(Action::Function::Shift, 2);
    table[3][1] = Action(Action::Function::Reduce, 3);
    table[3][2] = Action(Action::Function::Accept);
    table[3][3] = Action(Action::Function::Error);

    CompressedTable<size_t, Action> compressedTable(&table);

    std::cout << table.toString() << std::endl;
    std::cout << std::endl;
    std::cout << compressedTable.toString() << std::endl;

    EXPECT_TRUE(compressedTable[0][0] == Action(Action::Function::Shift, 1));
    EXPECT_TRUE(compressedTable[0][1] == Action(Action::Function::Reduce, 2));
    EXPECT_TRUE(compressedTable[0][2] == Action(Action::Function::Accept));
    EXPECT_TRUE(compressedTable[0][3] == Action(Action::Function::Error));

    EXPECT_TRUE(compressedTable[1][0] == Action(Action::Function::Accept));
    EXPECT_TRUE(compressedTable[1][1] == Action(Action::Function::Error));
    EXPECT_TRUE(compressedTable[1][2] == Action(Action::Function::Error));
    EXPECT_TRUE(compressedTable[1][3] == Action(Action::Function::Error));

    EXPECT_TRUE(compressedTable[2][0] == Action(Action::Function::Shift, 1));
    EXPECT_TRUE(compressedTable[2][1] == Action(Action::Function::Reduce, 2));
    EXPECT_TRUE(compressedTable[2][2] == Action(Action::Function::Accept));
    EXPECT_TRUE(compressedTable[2][3] == Action(Action::Function::Error));

    EXPECT_TRUE(compressedTable[3][0] == Action(Action::Function::Shift, 2));
    EXPECT_TRUE(compressedTable[3][1] == Action(Action::Function::Reduce, 3));
    EXPECT_TRUE(compressedTable[3][2] == Action(Action::Function::Accept));
    EXPECT_TRUE(compressedTable[3][3] == Action(Action::Function::Error));

    EXPECT_TRUE(compressedTable.getNumberOfRows() == 4);
    EXPECT_TRUE(compressedTable.getNumberOfCompressedRows() == 3);
}
