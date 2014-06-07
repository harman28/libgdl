/**
 * @file kif_scanner.hpp
 * @author Sumedh Ghaisas
 *
 * Declaration scanner class for Game Description Language.
 */
#ifndef _GDLPARSER_PARSER_KIF_SCANNER_HPP_INCLUDED
#define _GDLPARSER_PARSER_KIF_SCANNER_HPP_INCLUDED

#include "kif_parser.tab.hh"

#include <iostream>
#include <sstream>
#include <fstream>

#include "token_value.hpp"

namespace gdlparser
{
namespace parser
{
//! forward declaration of class KIFParser
class KIFDriver;

/**
 * This class implements tokenizer for Game Description Language. Implements yylex
 * method used by KIFParser which returns next token. Scanner can handle multiple
 * files and returns location along with token for errors and warnings.
 *
 */
class KIFScanner
{
    //! some useful typedefs
    typedef gdlparser::parser::yy::KIFParser::token token;
    typedef gdlparser::parser::yy::KIFParser::symbol_type symbol_type;
    typedef gdlparser::parser::yy::KIFParser::location_type location_type;

    //! to store state of the scanner
    enum State { NoState, InCommentFromToken, InComment, InToken, InClauseCommand, HaveNextToken};

public:

    //! Constructor
    //! Reference to the calling parser class is stored for error and warning logging
    KIFScanner(const KIFDriver& driver)
        : driver(driver), stream(NULL), file_index(0) { state = NoState; lineNo = 0; charNo = 0; isError = false; }

    //! Add file to be scanned
    void AddFile(const std::string& filename) { files.push_back(filename); }

    //! yylex function needed by parser.
    //! returns the next token if any along with its location
    symbol_type yylex();

    //! current location of the scanner
    int LineNo() { return lineNo + 1; }
    int CharNo() { return charNo; }
    std::string CurrentFile() { return files[file_index]; }

private:
    //! reference of the calling driver object
    const KIFDriver& driver;

    //! current scanning stream
    std::ifstream* stream;

    //! store next token to be returned
    std::string nextTokenValue;

    //! current state of the scanner
    State state;

    //! to track the location of the token
    int lineNo;
    int charNo;

    //! files to be scanned
    std::vector<std::string> files;

    //! current file index
    size_t file_index;

    //! to store error history
    bool isError;
};

} // namespace parser
} // namespace gdlparser


#endif // _GDLPARSER_PARSER_KIF_SCANNER_HPP_INCLUDED