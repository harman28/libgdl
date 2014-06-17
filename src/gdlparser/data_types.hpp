/**
 * @file data_types.hpp
 * @author Sumedh Ghaisas
 *
 * Declaration of data types used by driver.
 */
#ifndef __GDLPARSER_TOKEN_TYPES_H
#define __GDLPARSER_TOKEN_TYPES_H

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include <gdlparser/parser/token_value.hpp>

#include <gdlparser/parser/kif_parser.tab.hh>

namespace gdlparser
{
/**
 * Represents argument of fact or clause.
 * Can be relation, function or variable depending on type.
 * Stored as command and arguments.
 *
 * @see KIFDriver
 */
struct Argument
{
    //! enum type
    enum Type { Relation, Function, Var };

    //! empty constructor
    Argument() {}
    //! constucts argument from given token
    Argument(const TokenValue& tok);

    //! comparison operator
    //! checks value and arguments(recursively check)
    //! for 'or' if given argument matches any argument to 'or' true is returned
    bool operator==(const Argument& arg) const;
    bool operator!=(const Argument& arg) const { return !(*this == arg); }

    //! return true if given argument is there in arguments
    bool HasAsArgument(const Argument& arg) const;

    //! returns if current argument is ground
    bool IsGround() const;

    //! returns if current argument is a variable
    bool IsVariable() const { if(t == Var) return true; else return false; }

    //! equivalent to comparison operator but 'or' conditions is removed in this
    bool IsEqualTo(const Argument& arg) const;

    //! adds argument to this command
    void AddArgument(const TokenValue& tok);

    //! type of this argument
    Type t;
    //! command value
    std::string val;
    //! vector of arguments
    std::vector<Argument*> args;

    //! used by GDLReasoner
    mutable const Argument* sub;
};

/**
 * Represents a fact.
 * Fact is stored as command and its arguments.
 * Text representation is also stored for easy printing.
 *
 * @see KIFDriver
 */
struct Fact
{
    //! empty constructor
    Fact() {}

    //! constructs a fact with given command name and text
    Fact(const TokenValue& tok)
            : text(tok.Value()), arg(tok) {}

    //! Adds argument to this fact
    void AddArgument(const TokenValue& tok) { arg.AddArgument(tok); }

    const std::string& Command() const { return arg.val; }

    const std::vector<Argument*>& Arguments() const { return arg.args; }

    //! comparison operators
    bool operator==(const Fact& fact) const;
    bool operator!=(const Fact& fact) const { return !(*this == fact); }

    //! the original text of the fact
    std::string  text;
    //! fact as argument
    Argument arg;
};

/**
 * Represents a Clause.
 * Clause is stored as Head and its arguments(body).
 * Text representation is also stored for easy printing.
 *
 * @see KIFDriver
 */
struct Clause
{
    Clause(const TokenValue& tok, const size_t id);

    Argument* ConstructArgument(const TokenValue& tok, std::map<std::string, Argument*>& v_map);

    //! text representation
    std::string text;

    //! Head of the clause
    Argument* head;
    //! body
    std::vector<Argument*> premisses;
    //! to assign unique id
    size_t id;
};

/**
 * Represents dependency graph node.
 * Graph is stored as adjecency list. Each Node stores out degree.
 * Edge also carries extra information like edge type, location and index
 * of the rule where this dependency is observed.
 * Carries extra variables for Targan's algorithm for obtaining
 * strongly connected components.
 *
 * @see KIFDriver
 */
struct DGraphNode
{
    typedef parser::yy::KIFParser::location_type location_type;

    DGraphNode(const std::string& name) : name(name), index(-1), low_link(-1) {}

    //! represents command name of this node
    std::string name;
    //! out edges from this node
    std::vector<DGraphNode*> out;
    //! clause number associated out edge
    std::vector<size_t> c_index;
    //! argument
    std::vector<Argument> arg;
    //! location of the rule associated with every out edge
    std::vector<location_type> out_loc;
    //! edge type associated with every out edge
    //! If true then its a negative dependency
    std::vector<bool> isNot;

    //! extra variables for Tarjan's algorithm
    int index;
    int low_link;
};

}; // namespace gdlparser

/// operator<< for above defined types
std::ostream& operator<< (std::ostream& o, const gdlparser::Argument& arg);
std::ostream& operator<< (std::ostream& o, const gdlparser::Argument::Type& t);
std::ostream& operator<< (std::ostream& o, const gdlparser::Fact& fact);
std::ostream& operator<< (std::ostream& o, const gdlparser::Clause& clause);

#endif
