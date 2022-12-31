//
//  g/Actions.h - Action class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <vector>
#include <map>

#include "nonstd/string.h"
#include "nonstd/vector.h"
#include "nonstd/File.h"

class Action {
public:
	Action(const Action& action) : index(action.index), action(action.action), line(action.line) {}
    Action(unsigned index, nonstd::string action, unsigned int line) : index(index), action(action), line(line) {}
    Action(unsigned index, const char* text, unsigned int line) : index(index), action(text), line(line) {}

    nonstd::string getAction() { return action; }
    unsigned int getLine() { return line; }
    unsigned getIndex() { return index; }

    void SubstituteAttributes(vector<std::string>& attributes, vector<std::string>& types, bool isUnion, std::string type, size_t rhs_size);
    std::string Generate() const;
	nonstd::string toSource() const;

    friend bool compare(const Action& lhs, const Action& rhs);
	friend bool operator == (const Action& lhs, const Action& rhs);

private:
    nonstd::string action;
    unsigned index;
    unsigned int line;
};

class Actions {
public:
    Actions(bool lineDirectives = true) : nextIndex(0), actions(), lineDirectives(lineDirectives) {}
    Actions(std::initializer_list<Action> il, bool lineDirectives = true) : nextIndex(0), actions(), lineDirectives(lineDirectives) {
        for (auto i : il)
            actions.push_back(new Action(i));
    }

    ~Actions() {
        for (auto action : actions)
            delete action;
    }

    void setLineDirectives(bool directives = true) { lineDirectives = directives; }

    Action* addAction(const char* text, unsigned int line) {
        Action *action = new Action(allocateIndex(), text, line);
        actions.push_back(action);
        return action;
    }
    Action* operator[](unsigned action) {
        return actions[action];
    }
    size_t size() {
        return actions.size();
    }

    unsigned allocateIndex() { return nextIndex++; }

    std::string Generate(int indent = 2) const;
	std::string toSource() const;
	void Dump(std::ostream &os, unsigned indent = 0) const;

    void SubstituteAttributes(Action* action, vector<std::string>& attributes, vector<std::string>& types, bool _union, std::string type, size_t rhs_size);
    void OutputActionsHXX(std::ostream &os, std::string className, std::string returnType = "void") const;
    void OutputActionsCXX(std::ostream &os, std::string className, FileName filename, std::string returnType = "void", bool lineDirectives = true) const;
    void OutputActionHXX(unsigned int action, std::ostream &os, std::string className, std::string returnType = "void") const;
    void OutputActionCXX(unsigned int number, Action* action, std::ostream &os, std::string className, FileName filename, std::string returnType = "void", bool lineDirectives = true) const;

    void OutputActionDispatcherCXX(std::ostream &os, std::string className) const;

	friend bool compare(const Actions& lhs, const Actions& rhs);
	friend bool operator == (const Actions& lhs, const Actions& rhs);

private:
    bool lineDirectives;
    unsigned nextIndex;
    vector<Action*> actions;
};

// End g/Actions.h
