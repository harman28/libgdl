/**
 * @file primary_reasoner_tests.cpp
 * @author Sumedh Ghaisas
 *
 * Test file for GDLReasoner.
 */
#include <gdlreasoner/knowledgebase.hpp>
#include <gdlparser/kif.hpp>

#include <boost/test/unit_test.hpp>
#include "old_boost_test_definitions.hpp"
#include "libgdl_test.hpp"

#include <list>

BOOST_AUTO_TEST_SUITE(PrimaryReasonerTests);

using namespace std;
using namespace gdlparser;
using namespace gdlreasoner;

/**
 * Check knowledge base construction from KIF.
 */
BOOST_AUTO_TEST_CASE(NormalReasonerTest)
{
    MARK_START;
    OPEN_LOG;
	KIF kif(false, TEST_LOG);
	kif.AddFile("data/parser_tests/8puzzle.kif");
	kif.Parse();

	KnowledgeBase kb(kif);
	if(!kb.IsSatisfiable(Argument("(init ?x)"))) MARK_FAIL;
	MARK_END;
}

/**
 * Check knowledge base for normal question
 */
BOOST_AUTO_TEST_CASE(QuestionTest)
{
    MARK_START;
    OPEN_LOG;
	KnowledgeBase kb;
	kb.Tell("(<= (test ?x) (test2 ?x))");
	kb.Tell("(test2 1)");
	if(!kb.IsSatisfiable(Argument("(test ?x)"))) MARK_FAIL;
	MARK_END;
}

/**
 * Check knowledge base for 'or' question handling
 */
BOOST_AUTO_TEST_CASE(OrQuestionTest)
{
    MARK_START;
    OPEN_LOG;
	KnowledgeBase kb;
	kb.Tell("(<= (test ?x) (or (test2 ?x) (test3 ?x)))");
	kb.Tell("(test2 1)");
	kb.Tell("(test3 2)");
	std::list<Argument*> result;
	if((result = kb.Ask(Argument("(test ?x)"))).size() != 2) MARK_FAIL;
	for(std::list<Argument*>::iterator it = result.begin();it != result.end();it++)
        delete *it;
	MARK_END;
}

/**
 * Check knowledge base for 'not' question handling
 */
BOOST_AUTO_TEST_CASE(NotQuestionTest)
{
    MARK_START;
    OPEN_LOG;
	KnowledgeBase kb;
	kb.Tell("(<= (test ?x) (test2 ?x) (not (test3 ?x)))");
	kb.Tell("(test2 1)");
	kb.Tell("(test2 2)");
	kb.Tell("(test3 2)");
	std::list<Argument*> result;
	if((result = kb.Ask(Argument("(test ?x)"))).size() != 1) MARK_FAIL;
	for(std::list<Argument*>::iterator it = result.begin();it != result.end();it++)
        delete *it;
	MARK_END;
}

/**
 * Check knowledge base for 'distinct' question handling
 */
BOOST_AUTO_TEST_CASE(DistinctQuestionTest)
{
    MARK_START;
    OPEN_LOG;
	KnowledgeBase kb;
	kb.Tell("(<= (test ?x ?y) (test2 ?x) (test3 ?y) (distinct ?x ?y))");
	kb.Tell("(test2 1)");
	kb.Tell("(test3 1)");
	kb.Tell("(test3 2)");
	std::list<Argument*> result;
	if((result = kb.Ask(Argument("(test ?x ?y)"))).size() != 1) MARK_FAIL;
	for(std::list<Argument*>::iterator it = result.begin();it != result.end();it++)
        delete *it;
	MARK_END;
}

/**
 * Check knowledge base for infinite loop avoidance
 */
BOOST_AUTO_TEST_CASE(RecursiveDependencyTest)
{
    MARK_START;
    OPEN_LOG;
	KnowledgeBase kb;
	kb.Tell("(<= (test ?x) (test ?x))");
	kb.Tell("(test 1)");
	std::list<Argument*> result;
	if((result = kb.Ask(Argument("(test ?x)"))).size() != 1) MARK_FAIL;
	for(std::list<Argument*>::iterator it = result.begin();it != result.end();it++)
        delete *it;
	MARK_END;
}

BOOST_AUTO_TEST_SUITE_END();