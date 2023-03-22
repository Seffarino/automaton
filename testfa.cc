
#include "gtest/gtest.h"

#include "Automaton.h"

// -- PARTIE VALID : --
TEST(AutomatonValid, noState)
{
    fa::Automaton fa;
    fa.addSymbol('z');
    EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonValid, noState2)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonValid, noSymbol)
{
    fa::Automaton fa;
    fa.addState(0);
    EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonValid, noSymbol2)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonValid, Default)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.isValid());
    fa.addSymbol('z');
    fa.addState(0);
    EXPECT_TRUE(fa.isValid());
}
// -- PARTIE SYMBOLE : --
TEST(addSymbol, isNotGraph)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.addSymbol('\b'));
    EXPECT_EQ(fa.countSymbols(),(size_t) 0);
    EXPECT_FALSE(fa.hasSymbol('\b'));
}
TEST(addSymbol, isGraph)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_EQ(fa.countSymbols(),(size_t)1);
    EXPECT_TRUE(fa.hasSymbol('z'));
}


TEST(addSymbol, epsilon)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
    EXPECT_EQ(fa.countSymbols(),(size_t)0);

}

TEST(addSymbol, Default)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_FALSE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.hasSymbol('z'));
    EXPECT_EQ((size_t)1, fa.countSymbols());
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('B'));
    EXPECT_TRUE(fa.addSymbol('2'));
    EXPECT_TRUE(fa.addSymbol('3'));
    EXPECT_TRUE(fa.addSymbol('-'));
    EXPECT_FALSE(fa.addSymbol(' '));
    EXPECT_FALSE(fa.addSymbol('\t'));
    EXPECT_FALSE(fa.addSymbol('\n'));
}

TEST(removeSymbol, Default)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.removeSymbol('z'));
    EXPECT_FALSE(fa::Epsilon);
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_EQ(fa.countSymbols(), (size_t)1);
    EXPECT_TRUE(fa.removeSymbol('z'));
    EXPECT_EQ(fa.countSymbols(), (size_t)0);
}
TEST(removeSymbol, oneSymbol)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.removeSymbol('z'));
}
TEST(removeSymbol, twoSymbols)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.addSymbol('r'));
    EXPECT_EQ(fa.countSymbols(),(size_t)2);
    EXPECT_TRUE(fa.hasSymbol('z'));
    EXPECT_TRUE(fa.hasSymbol('r'));
    EXPECT_TRUE(fa.removeSymbol('z'));
    EXPECT_TRUE(fa.removeSymbol('r'));
    EXPECT_EQ(fa.countSymbols(),(size_t)0);

}
TEST(removeSymbol, twoSymbolsIdentical)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.removeSymbol('z'));
    EXPECT_FALSE(fa.removeSymbol('z'));
}
TEST(removeSymbol, symbolInTransition)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addTransition(0, 'z', 0));
    EXPECT_TRUE(fa.hasTransition(0, 'z', 0));
    EXPECT_TRUE(fa.removeSymbol('z'));
    EXPECT_FALSE(fa.hasTransition(0, 'z', 0));
    EXPECT_FALSE(fa.removeSymbol('z'));
}
TEST(removeSymbolTransition, Default)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('e'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addTransition(0, 'z', 1));
    EXPECT_TRUE(fa.addTransition(0, 'a', 1));
    EXPECT_TRUE(fa.addTransition(0, 'e', 1));
    EXPECT_EQ((size_t)3, fa.countSymbols());
    EXPECT_EQ((size_t)3, fa.countTransitions());
    EXPECT_EQ((size_t)2, fa.countStates());
    EXPECT_TRUE(fa.hasTransition(0, 'z', 1));
    EXPECT_TRUE(fa.removeSymbol('z'));
    EXPECT_FALSE(fa.hasTransition(0, 'z', 1));
    EXPECT_FALSE(fa.removeSymbol('z'));
    EXPECT_EQ((size_t)2, fa.countSymbols());
    EXPECT_EQ((size_t)2, fa.countTransitions());
}
TEST(hasSymbol, Default)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.hasSymbol('z'));
    EXPECT_FALSE(fa.hasSymbol('a'));
    EXPECT_FALSE(fa.hasSymbol(fa::Epsilon));
}
TEST(countSymbol, Default)
{
    fa::Automaton fa;
    EXPECT_EQ((size_t)0, fa.countSymbols());
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.addSymbol('d');
    EXPECT_EQ((size_t)4, fa.countSymbols());
    fa.removeSymbol('a');
    EXPECT_EQ((size_t)3, fa.countSymbols());
    fa.removeSymbol('a');
    EXPECT_EQ((size_t)3, fa.countSymbols());
    fa.removeSymbol('a');
    fa.removeSymbol(fa::Epsilon);
    EXPECT_EQ((size_t)3, fa.countSymbols());
}
// PARTIE STATE
TEST(addState, negative)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.addState(-1));
}

TEST(addState, alreadyPresent)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(1));
    EXPECT_FALSE(fa.addState(1));
}

TEST(addState, True)
{
    fa::Automaton fa;
    for (size_t i = 0; i < 10000; i++)
    {
        EXPECT_TRUE(fa.addState(i));
    }
    EXPECT_EQ((size_t)10000, fa.countStates());
    for (size_t i = 0; i < 10000; i++)
    {
        EXPECT_FALSE(fa.addState(i));
    }
    EXPECT_EQ((size_t)10000, fa.countStates());
}

TEST(removeState, Default)
{
    fa::Automaton fa;
    EXPECT_EQ((size_t)0, fa.countStates());
    for (size_t i = 0; i < 10000; i++)
    {
        EXPECT_FALSE(fa.removeState(i));
    }
    EXPECT_EQ((size_t)0, fa.countStates());
    for (size_t i = 0; i < 10000; i++)
    {
        EXPECT_TRUE(fa.addState(i));
    }
    EXPECT_EQ((size_t)10000, fa.countStates());
    for (size_t i = 0; i < 10000; i++)
    {
        EXPECT_TRUE(fa.removeState(i));
    }
    EXPECT_EQ((size_t)0, fa.countStates());
}

TEST(removeState, OriginInTransition)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addTransition(1, 'a', 0));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 0));
    EXPECT_TRUE(fa.removeState(0));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 0));
}

TEST(removeState, DestinationInTransition)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addTransition(1, 'a', 0));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 0));
    EXPECT_TRUE(fa.removeState(1));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 0));
}
TEST(removeStateTransition, Default)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('e'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addTransition(0, 'z', 1));
    EXPECT_TRUE(fa.addTransition(0, 'a', 1));
    EXPECT_TRUE(fa.addTransition(0, 'e', 1));
    EXPECT_TRUE(fa.removeState(0));
    EXPECT_FALSE(fa.removeState(0));
    EXPECT_EQ((size_t)0, fa.countTransitions());
    EXPECT_TRUE(fa.addState(0));
    EXPECT_FALSE(fa.hasTransition(0, 'e', 1));
    EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
    EXPECT_FALSE(fa.hasTransition(0, 'z', 1));
    EXPECT_TRUE(fa.addTransition(0, 'z', 1));
    EXPECT_TRUE(fa.addTransition(0, 'a', 1));
    EXPECT_TRUE(fa.addTransition(0, 'e', 1));
    EXPECT_TRUE(fa.addTransition(1, 'e', 1));
    EXPECT_TRUE(fa.removeState(0));
    EXPECT_TRUE(fa.hasTransition(1, 'e', 1));
    EXPECT_EQ((size_t)1, fa.countTransitions());
    EXPECT_TRUE(fa.removeState(1));
    EXPECT_EQ((size_t)0, fa.countTransitions());
    EXPECT_FALSE(fa.hasTransition(1, 'e', 1));
}

TEST(countState, Default)
{
    fa::Automaton fa;
    EXPECT_EQ((size_t)0, fa.countStates());
    for (size_t i = 0; i < 1000; i++)
    {
        fa.addState(i);
        EXPECT_EQ((size_t)i + 1, fa.countStates());
    }
    for (size_t j = 0; j < 1000; j++)
    {
        fa.removeState(j);
        EXPECT_EQ((size_t)1000 - (j + 1), fa.countStates());
    }
}

TEST(setStateInitial, Default)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.setStateFinal(3);
    EXPECT_FALSE(fa.isStateInitial(3));
    EXPECT_FALSE(fa.isStateInitial(0));
    fa.addState(0);
    EXPECT_FALSE(fa.isStateInitial(0));
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.isStateInitial(0));
    fa.addState(1);
    fa.setStateFinal(1);
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isStateInitial(1));
    EXPECT_TRUE(fa.isStateFinal(1));
    fa.removeState(1);
    EXPECT_FALSE(fa.isStateInitial(1));
    EXPECT_FALSE(fa.isStateInitial(1));
}
TEST(setStateInitial, readStringEmpty)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(5));
    EXPECT_TRUE(fa.addState(7));
    EXPECT_TRUE(fa.addSymbol('a'));
    (fa.setStateInitial(7));
    (fa.setStateInitial(5));
    (fa.setStateInitial(0));

    std::set<int> res = fa.readString("");
    std::set<int> shouldBeRes = {0, 5, 7};
    EXPECT_EQ(res, shouldBeRes);
}

TEST(readString, deadEndNoTransition)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    std::set<int> shouldBeRes = {};

    EXPECT_EQ(fa.readString("aaaaaa"),shouldBeRes);



    

}
TEST(setStateFinal, Default)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.setStateInitial(3);
    EXPECT_FALSE(fa.isStateFinal(3));
    EXPECT_FALSE(fa.isStateFinal(0));
    fa.addState(0);
    EXPECT_FALSE(fa.isStateFinal(0));
    fa.setStateFinal(0);
    EXPECT_TRUE(fa.isStateFinal(0));
    fa.addState(1);
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.isStateInitial(1));
    EXPECT_TRUE(fa.isStateFinal(1));
    fa.removeState(1);
    EXPECT_FALSE(fa.isStateFinal(1));
    fa.addState(1);
    EXPECT_FALSE(fa.isStateFinal(1));
}

// -- PARTIE SYMBOLE : --
TEST(AutomatonSymbol, Default)
{
    fa::Automaton fa;
    // Remove sur un tableau vide
    EXPECT_FALSE(fa.removeSymbol('z'));
    // Addsymbol
    EXPECT_TRUE(fa.addSymbol('z'));
    EXPECT_FALSE(fa.addSymbol('z'));

    EXPECT_TRUE(fa.hasSymbol('z'));
    EXPECT_FALSE(fa.hasSymbol('a'));
    EXPECT_TRUE(fa.removeSymbol('z'));
    EXPECT_FALSE(fa.hasSymbol('z'));
    fa.addSymbol('z');
    EXPECT_EQ((size_t)1, fa.countSymbols());
    fa.addSymbol('e');
    EXPECT_EQ((size_t)2, fa.countSymbols());
    fa.removeSymbol('e');
    EXPECT_EQ((size_t)1, fa.countSymbols());
}
// -- PARTIE ETAT : --
TEST(AutomatonState, Default)
{
    fa::Automaton fa;
    EXPECT_FALSE(fa.hasState(0));
    EXPECT_EQ((size_t)0, fa.countStates());
    fa.addState(0);
    EXPECT_TRUE(fa.hasState(0));
    EXPECT_EQ((size_t)1, fa.countStates());
    fa.removeState(0);
    EXPECT_EQ((size_t)0, fa.countStates());
    EXPECT_FALSE(fa.hasState(0));
    fa.addState(0);
    EXPECT_FALSE(fa.isStateInitial(0));
    EXPECT_FALSE(fa.isStateFinal(0));
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.isStateInitial(0));
    fa.setStateFinal(0);
    EXPECT_TRUE(fa.isStateFinal(0));
}
TEST(AutomatonAddTransition, OneTransition)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('0'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_TRUE(fa.addTransition(0, 'z', 1));
    EXPECT_TRUE(fa.hasTransition(0, 'z', 1));
}
TEST(AutomatonAddTransition, SameOriginAndLetter)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('0'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_TRUE(fa.addTransition(0, '0', 1));
    EXPECT_TRUE(fa.hasTransition(0, '0', 1));
}
TEST(AutomatonAddTransition, SameOriginAndDestination)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('1'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_TRUE(fa.addTransition(0, '1', 1));
    EXPECT_TRUE(fa.hasTransition(0, '1', 1));
}
TEST(AutomatonAddTransition, TwoIdenticalTransitions)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('1'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_TRUE(fa.addTransition(0, '1', 1));
    EXPECT_FALSE(fa.addTransition(0, '1', 1));
    EXPECT_TRUE(fa.hasTransition(0, '1', 1));
}
TEST(AutomatonAddTransition, UnknownOrigin)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('1'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_FALSE(fa.addTransition(6, '1', 1));
    EXPECT_FALSE(fa.hasTransition(6, '1', 1));
}
TEST(AutomatonAddTransition, UnknownTarget)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('1'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_FALSE(fa.addTransition(0, '1', 21));
    EXPECT_FALSE(fa.hasTransition(0, '1', 21));
}
TEST(AutomatonAddTransition, UnknownSymbol)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('1'));
    EXPECT_TRUE(fa.addSymbol('z'));
    fa.addState(0);
    fa.addState(1);
    EXPECT_FALSE(fa.addTransition(0, '4', 1));
    EXPECT_FALSE(fa.hasTransition(0, '4', 1));
}
TEST(AutomatonTransition, Default)
{
    fa::Automaton fa;
    // automate vide
    EXPECT_EQ((size_t)0, fa.countTransitions());
    EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
    EXPECT_FALSE(fa.removeTransition(2, 'a', 1));
    // TEST D'AJOUTER DES TRANSITIONS INVALIDE CAR PAS DE SYMBOLE ET/OU D'ETAT:
    // AUCUN
    EXPECT_FALSE(fa.addTransition(0, 'z', 1));
    fa.addSymbol('z');
    // PAS D'ETAT INITIAL ET FINAL
    EXPECT_FALSE(fa.addTransition(0, 'z', 1));
    fa.addState(0);
    // PAS D'ETAT FINAL
    EXPECT_FALSE(fa.addTransition(0, 'z', 1));
    fa.addState(1);
    // TRANSITION VALIDE ----
    EXPECT_TRUE(fa.addTransition(0, 'z', 1));
    EXPECT_TRUE(fa.hasTransition(0, 'z', 1));
    EXPECT_EQ((size_t)1, fa.countTransitions());
    // REMOVE
    EXPECT_FALSE(fa.removeTransition(1, 'z', 0));
    EXPECT_TRUE(fa.removeTransition(0, 'z', 1));
    EXPECT_EQ((size_t)0, fa.countTransitions());
    EXPECT_FALSE(fa.hasTransition(0, 'z', 1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addTransition(0, 'z', 1));
    EXPECT_TRUE(fa.addTransition(0, 'z', 2));
    EXPECT_TRUE(fa.addTransition(0, 'z', 0));
    EXPECT_EQ((size_t)3, fa.countTransitions());
    EXPECT_TRUE(fa.hasTransition(0, 'z', 1));
    EXPECT_TRUE(fa.removeTransition(0, 'z', 0));
    EXPECT_FALSE(fa.hasTransition(0, 'z', 0));
    EXPECT_EQ((size_t)2, fa.countTransitions());
}
TEST(AutomatonPrint, Default)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(0);
    fa.addState(3);
    fa.addState(2);
    fa.addState(4);
    fa.setStateInitial(0);
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(4);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(0, 'a', 1);
    fa.addTransition(0, 'a', 2);
    fa.addTransition(0, 'a', 3);
    fa.addTransition(1, 'b', 3);
    fa.addTransition(2, 'b', 4);
    fa.addTransition(2, 'a', 3);
    fa.addTransition(3, 'a', 3);
    fa.addTransition(3, 'b', 4);
    fa.addTransition(4, 'a', 4);
}
TEST(hasEpsilonTransition, WithoutEpsilon)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addSymbol('a');
    EXPECT_FALSE(fa.hasEpsilonTransition());
    EXPECT_EQ((size_t)0,fa.countTransitions());
}
TEST(hasEpsilonTransition, WithEpsilon)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addSymbol('a');
    fa.addTransition(0,fa::Epsilon,0);
    EXPECT_TRUE(fa.hasEpsilonTransition());
    EXPECT_EQ((size_t)1,fa.countTransitions());

}
TEST(hasEpsilonTransition, Twice)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addTransition(0,fa::Epsilon,0);
    fa.addTransition(2,fa::Epsilon,0);
    EXPECT_TRUE(fa.hasEpsilonTransition());
    EXPECT_EQ((size_t)2,fa.countTransitions());

}

TEST(hasEpsilonTransition, addAndRemove)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addTransition(0,fa::Epsilon,0);
    fa.addTransition(2,fa::Epsilon,0);
    EXPECT_TRUE(fa.hasEpsilonTransition());
    EXPECT_EQ((size_t)2,fa.countTransitions());
    EXPECT_TRUE(fa.removeTransition(0,fa::Epsilon,0));
    EXPECT_TRUE(fa.removeTransition(2,fa::Epsilon,0));
    EXPECT_EQ((size_t)0,fa.countTransitions());
}
TEST(hasEpsilonTransition, Default)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addSymbol('a');
    fa.addTransition(0, 'a', 1);
    EXPECT_FALSE(fa.hasEpsilonTransition());
    fa.addTransition(0, fa::Epsilon, 1);
    EXPECT_TRUE(fa.hasEpsilonTransition());
    fa.removeTransition(0, fa::Epsilon, 1);
    EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(isDeterministic, true)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addSymbol('a');
    fa.setStateInitial(0);
    fa.addTransition(0, 'a', 1);
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(isDeterministic, false)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addTransition(0, 'a', 1);
    EXPECT_FALSE(fa.isDeterministic());
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.isDeterministic());
    fa.addTransition(0, 'a', 2);
    EXPECT_FALSE(fa.isDeterministic());
}
TEST(isDeterministic, trueNotComplete)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('z');
    fa.setStateInitial(0);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(0, 'z', 1);
    fa.addTransition(1, 'a', 1);

    EXPECT_TRUE(fa.isDeterministic());
}

TEST(isDeterministic, twoInitialStates)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('z');
    fa.setStateInitial(0);
    fa.setStateInitial(1);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1,'a',1);
    EXPECT_FALSE(fa.isDeterministic());
}
TEST(isDeterministic, noInitialStates)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 1);
    fa.addTransition(1,'a',1);
    EXPECT_FALSE(fa.isDeterministic());
}
TEST(isDeterministic, noTransitions)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(0);
    fa.addSymbol('a');
    fa.addSymbol('z');
    EXPECT_TRUE(fa.isDeterministic());
}
TEST(isDeterministic, good)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.setStateInitial(0);
    fa.addSymbol('a');
    fa.addSymbol('z');
    EXPECT_TRUE(fa.isDeterministic());
    fa.setStateInitial(2);
    EXPECT_FALSE(fa.isDeterministic());
    fa.removeState(2);
    EXPECT_TRUE(fa.isDeterministic());
    fa.addTransition(0,'a',0);
    fa.addTransition(0,'z',0);
    EXPECT_TRUE(fa.isDeterministic());
    fa.addTransition(0,'z',1);
    EXPECT_FALSE(fa.isDeterministic());
    fa.removeState(1);
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(isComplete, falseTransitions)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);

    EXPECT_FALSE(fa.isComplete());
}
TEST(isComplete, falseRemoveState)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    fa.removeState(2);
    EXPECT_FALSE(fa.isComplete());
}
TEST(isComplete, trueRemoveState)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(0, 'a', 1);
    fa.addTransition(0, 'b', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(2, 'a', 2);
    fa.addTransition(2, 'b', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);
    EXPECT_TRUE(fa.isComplete());
    fa.removeState(2);
    EXPECT_TRUE(fa.isComplete());
}
TEST(isComplete, falseRemoveTransition)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    fa.removeTransition(2, 'a', 1);
    EXPECT_FALSE(fa.isComplete());
}
TEST(isComplete, trueRemoveSymbol)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    fa.removeSymbol('z');
    EXPECT_TRUE(fa.isComplete());
}

TEST(isComplete, true)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    EXPECT_TRUE(fa.isComplete());
}
TEST(isComplete, CompleteNotDeterministic)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(0, 'a', 1);
    fa.addTransition(0, 'a', 0);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'b', 1);
    fa.addTransition(0, 'b', 0);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    EXPECT_TRUE(fa.isComplete());
    
}
TEST(CreateComplete, AlreadyComplete)
{
    fa::Automaton fa;
    fa::Automaton complete;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    complete = fa::Automaton::createComplete(fa);
   EXPECT_TRUE(fa.isComplete());
   EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(fa.isIncludedIn(complete));
   EXPECT_TRUE(fa.isValid());
   EXPECT_FALSE(fa.match(""));
   EXPECT_FALSE(complete.match(""));
    EXPECT_TRUE(complete.isValid());

}

TEST(CreateComplete, AlreadyCompleteWithTrashState)
{
    fa::Automaton fa;
    fa::Automaton complete;
    fa::Automaton complete2;

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addSymbol('z');
    fa.addTransition(0, 'a', 2);
    fa.addTransition(1, 'a', 1);
    fa.addTransition(0, 'b', 2);
    fa.addTransition(0, 'z', 2);
    fa.addTransition(1, 'z', 1);
    fa.addTransition(1, 'b', 1);
    fa.addTransition(2, 'z', 1);
    fa.addTransition(2, 'b', 1);
    fa.addTransition(2, 'a', 1);
    complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    complete2 = fa::Automaton::createComplete(complete);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(complete2.isComplete());
    EXPECT_TRUE(fa.isIncludedIn(complete));
    EXPECT_TRUE(fa.isIncludedIn(complete2));
EXPECT_FALSE(fa.match(""));
   EXPECT_FALSE(complete.match(""));
    EXPECT_TRUE(complete.isValid());

}

TEST(CreateComplete, notComplete)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.addSymbol('a');
    fa.addTransition(0, 'b', 2);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    EXPECT_FALSE(fa.isComplete());
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(fa.isIncludedIn(complete));
    EXPECT_FALSE(fa.match(""));
   EXPECT_FALSE(complete.match(""));
    EXPECT_TRUE(complete.isValid());

}

TEST(CreateComplete, deleteState)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.addSymbol('a');
    fa.addTransition(0, 'b', 2);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    EXPECT_FALSE(fa.isComplete());
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_FALSE(fa.match(""));
   EXPECT_FALSE(complete.match(""));
    EXPECT_TRUE(complete.isValid());

}

TEST(CreateComplete, deleteSymbol)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.addSymbol('a');
    fa.addTransition(0, 'b', 2);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    EXPECT_FALSE(fa.isComplete());
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    complete.removeSymbol('a');
    EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(complete.isValid());

}

TEST(CreateComplete, noTransitionsState)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.addSymbol('a');
    fa.addTransition(0, 'b', 2);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    EXPECT_FALSE(fa.isComplete());
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(complete.isValid());

}
TEST(CreateComplete, onlyTrashState)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(0, 'a', 0);
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(complete.isValid());

}
TEST(CreateComplete, initialAndFinal)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(0, 'a', 1);
    EXPECT_FALSE(fa.isComplete());
    EXPECT_TRUE(fa.match("a"));
    EXPECT_FALSE(fa.match("aa"));
    EXPECT_FALSE(fa.match("aab"));
    EXPECT_FALSE(fa.match("b"));
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_TRUE(complete.match("a"));
    EXPECT_FALSE(complete.match("aa"));
    EXPECT_FALSE(complete.match("aab"));
    EXPECT_FALSE(complete.match("b"));
    EXPECT_TRUE(complete.isValid());

}
TEST(CreateComplete, initalNoFinal)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.setStateInitial(0);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(0, 'a', 1);
    EXPECT_FALSE(fa.isComplete());
    EXPECT_FALSE(fa.match("a"));
    EXPECT_FALSE(fa.match("aa"));
    EXPECT_FALSE(fa.match("aab"));
    EXPECT_FALSE(fa.match("b"));
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    EXPECT_TRUE(complete.isComplete());
    EXPECT_FALSE(complete.match("a"));
    EXPECT_FALSE(complete.match("aa"));
    EXPECT_FALSE(complete.match("aab"));
    EXPECT_FALSE(complete.match("b"));
    EXPECT_TRUE(complete.isValid());

}

TEST(CreateMirror, Empty)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addSymbol('b');
    fa::Automaton mirror = fa::Automaton::createMirror(fa);
    EXPECT_EQ(fa.countTransitions(), mirror.countTransitions());
    EXPECT_EQ(fa.countSymbols(), mirror.countSymbols());
    EXPECT_EQ(fa.countStates(), mirror.countStates());
    EXPECT_TRUE(fa.isLanguageEmpty());
    EXPECT_TRUE(mirror.isLanguageEmpty());
    EXPECT_TRUE(mirror.isValid());


}

TEST(CreateMirror, Unit)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addSymbol('b');
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa::Automaton mirror = fa::Automaton::createMirror(fa);
    EXPECT_TRUE(fa.match(""));
    EXPECT_FALSE(fa.isLanguageEmpty());
    EXPECT_FALSE(mirror.isLanguageEmpty());
    EXPECT_TRUE(mirror.isValid());


}
TEST(CreateMirror, EmptyTransitions)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa::Automaton mirror = fa::Automaton::createMirror(fa);
    EXPECT_EQ(fa.countTransitions(), mirror.countTransitions());
    EXPECT_EQ(fa.countSymbols(), mirror.countSymbols());
    EXPECT_EQ(fa.countStates(), mirror.countStates());
        EXPECT_TRUE(fa.isLanguageEmpty());
    EXPECT_TRUE(mirror.isLanguageEmpty());
    EXPECT_TRUE(mirror.isValid());

}

TEST(createMirror, completeAutomaton)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addSymbol('b');
    fa.addSymbol('c');
    fa.addSymbol('a');
    fa.addTransition(0, 'b', 2);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    fa::Automaton complete = fa::Automaton::createComplete(fa);
    fa::Automaton mirror = fa::Automaton::createMirror(complete);
    EXPECT_TRUE(mirror.isValid());

}
TEST(CreateMiror, Default)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'b', 3);
    fa.addTransition(3, 'b', 1);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa::Automaton mirror = fa::Automaton::createMirror(fa);
    EXPECT_EQ(fa.countTransitions(), mirror.countTransitions());
    EXPECT_EQ(fa.countSymbols(), mirror.countSymbols());
    EXPECT_EQ(fa.countStates(), mirror.countStates());
    EXPECT_TRUE(mirror.isValid());

}
TEST(CreateMiror, simple)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa::Automaton mirror = fa::Automaton::createMirror(fa);
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_FALSE(fa.match("ba"));
EXPECT_TRUE(mirror.match("ba"));
    EXPECT_FALSE(mirror.match("ab"));
}
TEST(isEmpty, unitLanguage)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addSymbol('a');
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    EXPECT_FALSE(fa.isLanguageEmpty());
}
TEST(isEmpty, twoParts)
{
    fa::Automaton fa;
    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.setStateInitial(0);
    fa.setStateFinal(4);
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'b',2);
    fa.addTransition(3,'a',4);
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(isEmpty, noInitialState)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'b', 3);
    fa.addTransition(3, 'b', 1);
    fa.setStateFinal(3);
    EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(isLanguageEmpty, stateInitialFinale)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addSymbol('b');
    fa.setStateInitial(3);
    fa.setStateFinal(3);
    EXPECT_FALSE(fa.isLanguageEmpty());
}
TEST(isLanguageEmpty, trueNoFinalStateLoop)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'a', 1);
    EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(isLanguageEmpty, trueNoFinalStateUnlinked)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'b', 2);
    fa.addTransition(2, 'a', 2);
    EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(isLanguageEmpty, trueMultipleInitialState)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.setStateInitial(1);
    fa.setStateInitial(2);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'a', 1);
    EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(isLanguageEmpty, falseMultipleInitialState)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateInitial(1);
    fa.setStateInitial(3);
    fa.setStateFinal(4);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'b', 2);
    fa.addTransition(3, 'a', 4);
    EXPECT_FALSE(fa.isLanguageEmpty());
}
TEST(isLanguageEmpty, trueMultipleFinalState)
{
    fa::Automaton fa;
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);
    fa.addState(4);
    fa.setStateFinal(4);
    fa.setStateFinal(3);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'a', 1);
    fa.addTransition(3, 'a', 4);

    EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(isLanguageEmpty, false)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'b', 3);
    fa.addTransition(3, 'b', 1);
    fa.setStateInitial(2);
    fa.setStateFinal(3);
    EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(removeNonAccessibleStates, noInitialState)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.setStateFinal(3);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'b', 3);
    fa.addTransition(3, 'b', 1);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(), (size_t)1);
    EXPECT_EQ(fa.countTransitions(), (size_t)0);
    EXPECT_TRUE(fa.isValid());

}
TEST(removeNonAccessibleStates, multipleInitialState)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(1);
    fa.setStateInitial(2);
    fa.setStateInitial(3);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 4);
    fa.addTransition(2, 'a', 5);
    fa.addTransition(3, 'a', 6);
    fa.removeNonAccessibleStates();
    EXPECT_EQ((size_t)6, fa.countStates());
    EXPECT_TRUE(fa.isValid());

}
TEST(removeNonAccessibleStates, loop)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addSymbol('a');
    fa.addTransition(3, 'a', 3);
    fa.removeNonAccessibleStates();
    EXPECT_TRUE(fa.isValid());

}

TEST(removeNonAccessibleStates, default)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.addState(7);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.addSymbol('c');
    fa.addSymbol('d');
    fa.addSymbol('e');
    fa.setStateFinal(6);
    fa.setStateInitial(1);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    fa.addTransition(2, 'c', 5);
    fa.addTransition(2, 'd', 5);
    fa.addTransition(5, 'e', 6);
    fa.addTransition(5, 'c', 4);
    fa.addTransition(5, 'd', 4);
    fa.addTransition(3, 'b', 4);
    fa.addTransition(3, 'b', 6);
    fa.addTransition(7, 'b', 6);
    fa.removeNonAccessibleStates();
    EXPECT_FALSE(fa.hasState(3));
    EXPECT_FALSE(fa.hasState(7));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(4));
    EXPECT_TRUE(fa.hasState(5));
    EXPECT_TRUE(fa.hasState(6));
    EXPECT_TRUE(fa.isValid());

}
TEST(removeNonCoAccessibleStates, noInitialState)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.setStateFinal(3);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(1, 'a', 3);
    fa.addTransition(2, 'b', 3);
    fa.addTransition(3, 'b', 3);
    fa.addTransition(3, 'b', 1);
    fa.removeNonAccessibleStates();
    EXPECT_EQ(fa.countStates(), (size_t)1);
    EXPECT_EQ(fa.countTransitions(), (size_t)0);
    EXPECT_TRUE(fa.isValid());
}
TEST(removeNonCoAccessibleStates, noFinalTest)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.setStateInitial(1);
    fa.setStateInitial(2);
    fa.setStateInitial(3);
    fa.addSymbol('a');
    fa.addSymbol('b');
    fa.addTransition(1, 'a', 4);
    fa.addTransition(2, 'a', 5);
    fa.addTransition(3, 'a', 6);
    fa.removeNonCoAccessibleStates();
    EXPECT_EQ((size_t)1, fa.countStates());
    EXPECT_TRUE(fa.isValid());
}
TEST(removeNonCoAccessibleStates, default)
{
    fa::Automaton fa;
    fa.addState(3);
    fa.addState(1);
    fa.addState(2);
    fa.addState(4);
    fa.addState(5);
    fa.addState(6);
    fa.addState(7);
    fa.addSymbol('b');
    fa.addSymbol('a');
    fa.addSymbol('c');
    fa.addSymbol('d');
    fa.addSymbol('e');
    fa.setStateFinal(6);
    fa.setStateInitial(1);
    fa.addTransition(1, 'a', 2);
    fa.addTransition(2, 'a', 2);
    fa.addTransition(2, 'c', 5);
    fa.addTransition(2, 'd', 5);
    fa.addTransition(5, 'e', 6);
    fa.addTransition(5, 'c', 4);
    fa.addTransition(5, 'd', 4);
    fa.addTransition(3, 'b', 4);
    fa.addTransition(3, 'b', 6);
    fa.addTransition(7, 'b', 6);
    fa.removeNonCoAccessibleStates();
    EXPECT_TRUE(fa.hasState(3));
    EXPECT_TRUE(fa.hasState(7));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_FALSE(fa.hasState(4));
    EXPECT_TRUE(fa.hasState(5));
    EXPECT_TRUE(fa.hasState(6));
    EXPECT_TRUE(fa.isValid());
}
TEST(createProduct, Different)
{
    fa::Automaton fa; // commence par a
    fa::Automaton fa2; // finit par b
    fa::Automaton product; // les 2
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'b',1));
    EXPECT_TRUE(fa.match("aaab"));
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("aabab"));
    EXPECT_TRUE(fa.match("abbaabb"));
    EXPECT_TRUE(fa.match("aabab"));
    EXPECT_FALSE(fa.match("baaa"));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.addSymbol('b'));
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa2.addTransition(0,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'a',0));
    EXPECT_TRUE(fa2.addTransition(0,'a',0));
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("abbbb"));
    EXPECT_TRUE(fa2.match("aaaaaaab"));
    EXPECT_TRUE(fa2.match("abababab"));
    EXPECT_TRUE(fa2.match("b"));
    EXPECT_FALSE(fa2.match("abaa"));
    product = fa::Automaton::createProduct(fa, fa2); //commence par a finit par b
    EXPECT_TRUE(product.match("ab"));
    EXPECT_TRUE(product.match("abab"));
    EXPECT_TRUE(product.match("abbbbb"));
    EXPECT_TRUE(product.match("aaaaaab"));
    EXPECT_TRUE(product.match("ab"));
    EXPECT_FALSE(product.match("baabab"));
    EXPECT_FALSE(product.match("abbbaa"));
    EXPECT_FALSE(product.match("abbbaa"));
    EXPECT_FALSE(product.match("abbbaa"));
        EXPECT_TRUE(product.isValid());
    EXPECT_FALSE(product.isLanguageEmpty());
}
TEST(createProduct, same)
{
    fa::Automaton fa; // commence par a
    fa::Automaton fa2; // finit par b
    fa::Automaton product; // les 2
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'b',1));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.addSymbol('b'));
    EXPECT_TRUE(fa2.addTransition(0,'a',1));
    EXPECT_TRUE(fa2.addTransition(1,'a',1));
    EXPECT_TRUE(fa2.addTransition(1,'b',1));
        EXPECT_TRUE(fa.match("aaab"));
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("aabab"));
    EXPECT_TRUE(fa.match("abbaabb"));
    EXPECT_TRUE(fa.match("aabab"));
    EXPECT_FALSE(fa.match("baaa"));
        EXPECT_TRUE(fa2.match("aaab"));
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("aabab"));
    EXPECT_TRUE(fa2.match("abbaabb"));
    EXPECT_TRUE(fa2.match("aabab"));
    EXPECT_FALSE(fa2.match("baaa"));
    product = fa::Automaton::createProduct(fa, fa2); //commence par a finit par b
EXPECT_TRUE(product.match("aaab"));
    EXPECT_TRUE(product.match("ab"));
    EXPECT_TRUE(product.match("aabab"));
    EXPECT_TRUE(product.match("abbaabb"));
    EXPECT_TRUE(product.match("aabab"));
    EXPECT_FALSE(product.match("baaa"));
    EXPECT_TRUE(fa.isIncludedIn(product));
    EXPECT_TRUE(fa2.isIncludedIn(product));
    EXPECT_TRUE(product.isValid());
    EXPECT_FALSE(product.isLanguageEmpty());
}
TEST(createProduct, manyInitialStates)
{
    fa::Automaton fa; // commence par b 
    fa::Automaton fa2; //finit par b
    fa::Automaton product;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.addSymbol('b'));
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa2.addTransition(0,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'a',0));
    EXPECT_TRUE(fa2.addTransition(0,'a',0));
    product = fa::Automaton::createProduct(fa, fa2); //commence par b finit par b
    EXPECT_TRUE(fa.match("baaaaab"));
    EXPECT_TRUE(fa.match("baa"));
    EXPECT_TRUE(fa.match("baba"));
    EXPECT_FALSE(fa.match("abaa"));
EXPECT_TRUE(fa2.match("baaaaab"));
    EXPECT_TRUE(fa2.match("baab"));
    EXPECT_TRUE(fa2.match("babab"));
    EXPECT_FALSE(fa2.match("abaa"));
    EXPECT_TRUE(product.match("baaaaab"));
    EXPECT_TRUE(product.match("baab"));
    EXPECT_TRUE(product.match("babab"));
    EXPECT_FALSE(product.match("abaa"));
    EXPECT_FALSE(product.match("abaa"));
    EXPECT_TRUE(product.isValid());
    EXPECT_FALSE(product.isLanguageEmpty());

}
TEST(createProduct, withEmpty)
{
    fa::Automaton fa;
    fa::Automaton fa2;
    fa::Automaton product;
        EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
        EXPECT_TRUE(fa.match("baaaaab"));
    EXPECT_TRUE(fa.match("baa"));
    EXPECT_TRUE(fa.match("baba"));
    EXPECT_FALSE(fa.match("abaa"));
    EXPECT_TRUE(fa2.addState(1));
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isLanguageEmpty());
    product = fa::Automaton::createProduct(fa, fa2);
    EXPECT_TRUE(product.isValid());
    EXPECT_TRUE(product.isLanguageEmpty());
}
TEST(createProduct, differentSymbols)
{
    fa::Automaton fa;
    fa::Automaton fa2;
    fa::Automaton product;
            EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa2.addState(1));
    fa2.setStateInitial(1);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa2.addSymbol('c'));
    EXPECT_TRUE(fa2.addTransition(1,'c',1));
    product = fa::Automaton::createProduct(fa, fa2);
    EXPECT_TRUE(product.isValid());
    EXPECT_TRUE(product.isLanguageEmpty());

}
TEST(createProduct, isNull)
{
    fa::Automaton fa;
    fa::Automaton fa2;
    fa::Automaton product;

    fa.addState(1);
    fa.addState(2);
    fa.addSymbol('a');
    fa.addTransition(1, 'a', 2);

    fa2.addState(1);
    fa2.addSymbol('b');
    fa2.addTransition(1, 'b', 1);
    product = fa::Automaton::createProduct(fa, fa2);
    EXPECT_TRUE(product.isValid());
    EXPECT_TRUE(product.isLanguageEmpty());
    product = fa::Automaton::createProduct(fa, fa2);

}
TEST(HasEmptyIntersectionWith, NotEmpty)
{
    fa::Automaton fa;
    fa::Automaton fa2;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'b',1));
    EXPECT_TRUE(fa.match("aaab"));
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("aabab"));
    EXPECT_TRUE(fa.match("abbaabb"));
    EXPECT_TRUE(fa.match("aabab"));
    EXPECT_FALSE(fa.match("baaa"));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.addSymbol('b'));
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa2.addTransition(0,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'a',0));
    EXPECT_TRUE(fa2.addTransition(0,'a',0));
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("abbbb"));
    EXPECT_TRUE(fa2.match("aaaaaaab"));
    EXPECT_TRUE(fa2.match("abababab"));
    EXPECT_TRUE(fa2.match("b"));
    EXPECT_FALSE(fa2.match("abaa"));
    EXPECT_FALSE(fa.hasEmptyIntersectionWith(fa2));

}
TEST(HasEmptyIntersectionWith, Empty)
{
    fa::Automaton fa;
    fa::Automaton fa2;
        EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateInitial(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
        EXPECT_TRUE(fa.match("baaaaab"));
    EXPECT_TRUE(fa.match("baa"));
    EXPECT_TRUE(fa.match("baba"));
    EXPECT_FALSE(fa.match("abaa"));
    EXPECT_TRUE(fa2.addState(1));
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isLanguageEmpty());
    EXPECT_TRUE(fa.hasEmptyIntersectionWith(fa2));
}
TEST(createDeterminstic, exCours2){
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(4);
    EXPECT_TRUE(fa.addTransition(0,'a',3));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(0,'a',2));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',4));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(2,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));

    EXPECT_TRUE(fa.isValid());
    EXPECT_FALSE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("abb"));
    EXPECT_TRUE(fa.match("aa"));
    EXPECT_TRUE(fa.match("bbaaaabbbb"));
    EXPECT_TRUE(fa.match("baa"));
    EXPECT_TRUE(fa.match("baababbab"));
    EXPECT_TRUE(fa.match("aaa"));
    EXPECT_TRUE(fa.match("aaababbabaaa"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_FALSE(fa.match("ab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("aba"));
    fa::Automaton fa2 = fa::Automaton::createDeterministic(fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("abb"));
    EXPECT_TRUE(fa2.match("aa"));
    EXPECT_TRUE(fa2.match("bbaaaabbbb"));
    EXPECT_TRUE(fa2.match("baa"));
    EXPECT_TRUE(fa2.match("baababbab"));
    EXPECT_TRUE(fa2.match("aaa"));
    EXPECT_TRUE(fa2.match("aaababbabaaa"));
EXPECT_FALSE(fa2.match(""));
EXPECT_FALSE(fa2.match("ab"));
EXPECT_FALSE(fa2.match("aba"));
EXPECT_FALSE(fa2.match("aba"));
}
TEST(createDeterministic, noInitalState)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.isValid());

}
TEST(createComplement, simple)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.addTransition(0,'a',0));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(1,'a',0));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa.isValid());
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("aba"));
    EXPECT_FALSE(fa.match("bb"));
    EXPECT_FALSE(fa.match("abb"));
    EXPECT_FALSE(fa.match("bbaa"));
    fa::Automaton complement;
    complement = fa::Automaton::createComplement(fa);
    EXPECT_TRUE(fa.hasEmptyIntersectionWith(complement));
    EXPECT_FALSE(complement.match("aba"));
    EXPECT_TRUE(complement.match("bb"));
    EXPECT_TRUE(complement.match("abb"));
    EXPECT_TRUE(complement.match("bbaa"));
}
TEST(createComplement, nonDeterministic)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.addTransition(0,'a',0));
    EXPECT_TRUE(fa.addTransition(0,'a',2));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(1,'a',0));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa.isValid());
    EXPECT_TRUE(fa.isComplete());
    EXPECT_FALSE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("aba"));
    EXPECT_FALSE(fa.match("bb"));
    EXPECT_FALSE(fa.match("abb"));
    EXPECT_FALSE(fa.match("bbaa"));
    fa::Automaton complement;
    complement = fa::Automaton::createComplement(fa);
    EXPECT_TRUE(fa.hasEmptyIntersectionWith(complement));
    EXPECT_FALSE(fa.isIncludedIn(complement));
}
TEST(createComplement, notComplete)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.addTransition(0,'a',0));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(1,'a',0));
    EXPECT_TRUE(fa.isValid());
    EXPECT_FALSE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("aaab"));
    EXPECT_TRUE(fa.match("aaabaaaa"));
    EXPECT_FALSE(fa.match("bb"));
    EXPECT_FALSE(fa.match("abb"));
    EXPECT_FALSE(fa.match("bbaa"));
    fa::Automaton complement;
    complement = fa::Automaton::createComplement(fa);
    EXPECT_FALSE(complement.match("aaab"));
    EXPECT_FALSE(complement.match("aaabaaaa"));
    EXPECT_TRUE(complement.match("bb"));
    EXPECT_TRUE(complement.match("abb"));
    EXPECT_TRUE(complement.match("bbaa"));
    EXPECT_TRUE(fa.hasEmptyIntersectionWith(complement));
    EXPECT_FALSE(fa.isIncludedIn(complement));
}

TEST(createComplement, empty)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.isLanguageEmpty());
    EXPECT_FALSE(fa.match(""));
    EXPECT_FALSE(fa.match("aa"));
    EXPECT_FALSE(fa.match("aaaaa"));
    EXPECT_FALSE(fa.match("a"));
    fa::Automaton complement = fa::Automaton::createComplement(fa);
    EXPECT_TRUE(fa.hasEmptyIntersectionWith(complement));
    EXPECT_TRUE(complement.match(""));
    EXPECT_TRUE(complement.match("aa"));
    EXPECT_TRUE(complement.match("aaaaa"));
    EXPECT_TRUE(complement.match("a"));
}
TEST(isIncludedIn, differentSymbols)
{
   fa::Automaton fa;
   fa::Automaton fa2;
   EXPECT_TRUE(fa.addSymbol('e'));
   EXPECT_TRUE(fa.addSymbol('f'));
   EXPECT_TRUE(fa2.addSymbol('b'));
   EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa.addTransition(0,'e',1));
    EXPECT_TRUE(fa.addTransition(1,'f',1));
    EXPECT_TRUE(fa2.addTransition(0,'b',1));
    EXPECT_TRUE(fa2.addTransition(1,'a',1));
    EXPECT_TRUE(fa.match("effff"));
    EXPECT_TRUE(fa2.match("baaaaa"));
    EXPECT_FALSE(fa.isIncludedIn(fa2));
    EXPECT_FALSE(fa2.isIncludedIn(fa));
}
TEST(isIncludedIn, differentSymbols2)
{
   fa::Automaton fa;
   fa::Automaton fa2;
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
   EXPECT_TRUE(fa2.addSymbol('b'));
   EXPECT_TRUE(fa2.addSymbol('a'));
   EXPECT_TRUE(fa2.addSymbol('c'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
   EXPECT_TRUE(fa.addTransition(0,'a',1));
   EXPECT_TRUE(fa.addTransition(0,'b',1));
   EXPECT_TRUE(fa.addTransition(1,'b',1));
   EXPECT_TRUE(fa.match("abbbbb"));
   EXPECT_TRUE(fa.match("bbbbbb"));
   EXPECT_FALSE(fa.match("aaa"));
   EXPECT_FALSE(fa.match("aab"));

   EXPECT_TRUE(fa2.addTransition(0,'a',1));
   EXPECT_TRUE(fa2.addTransition(0,'c',1));
   EXPECT_TRUE(fa2.addTransition(0,'b',1));
   EXPECT_TRUE(fa2.addTransition(1,'b',1));
   EXPECT_TRUE(fa2.addTransition(1,'a',1));
   EXPECT_TRUE(fa2.addTransition(1,'c',1));
       EXPECT_TRUE(fa2.match("abbbbb"));
   EXPECT_TRUE(fa2.match("bbbbbb"));
   EXPECT_TRUE(fa2.match("aaa"));
   EXPECT_TRUE(fa2.match("aaab"));
   EXPECT_TRUE(fa2.match("ccaaab"));
   EXPECT_TRUE(fa.isIncludedIn(fa2));
   EXPECT_FALSE(fa2.isIncludedIn(fa));

}
TEST(isIncludedIn, emptyInEmpty)
{
    fa::Automaton fa;
    fa::Automaton fa2;
   EXPECT_TRUE(fa.addSymbol('e'));
   EXPECT_TRUE(fa2.addSymbol('e'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa.isLanguageEmpty());
    EXPECT_TRUE(fa2.isLanguageEmpty());
    EXPECT_TRUE(fa.isIncludedIn(fa2));
}
TEST(isIncludedIn, emptyInNotEmpty)
{
    fa::Automaton fa;
    fa::Automaton fa2;
   EXPECT_TRUE(fa.addSymbol('e'));
   EXPECT_TRUE(fa2.addSymbol('e'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa2.addState(0));
    fa2.setStateInitial(0);
    fa2.setStateFinal(0);
    EXPECT_TRUE(fa.addTransition(0,'e',0));
    EXPECT_TRUE(fa.isLanguageEmpty());
    EXPECT_FALSE(fa2.isLanguageEmpty());
    EXPECT_TRUE(fa.isIncludedIn(fa2));
    EXPECT_FALSE(fa2.isIncludedIn(fa));

}
TEST(isIncludedIn, differentSymbols3)
{
   fa::Automaton fa;
   fa::Automaton fa2;
   EXPECT_TRUE(fa.addSymbol('e'));
   EXPECT_TRUE(fa.addSymbol('f'));
   EXPECT_TRUE(fa.addSymbol('g'));
   EXPECT_TRUE(fa.addSymbol('h'));
   EXPECT_TRUE(fa2.addSymbol('g'));
   EXPECT_TRUE(fa2.addSymbol('a'));
   EXPECT_TRUE(fa2.addSymbol('z'));
   EXPECT_TRUE(fa2.addSymbol('n'));

    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa.setStateInitial(0);
    fa.setStateFinal(1);
    fa2.setStateInitial(0);
    fa2.setStateFinal(1);
    EXPECT_TRUE(fa.addTransition(0,'e',1));
    EXPECT_TRUE(fa.addTransition(0,'g',1));
    EXPECT_TRUE(fa.addTransition(1,'g',1));
    EXPECT_TRUE(fa.addTransition(1,'h',1));
    EXPECT_TRUE(fa.addTransition(1,'f',1));
    EXPECT_TRUE(fa2.addTransition(0,'g',1));
    EXPECT_TRUE(fa.match("effff"));
    EXPECT_TRUE(fa.match("g"));
    EXPECT_TRUE(fa2.match("g"));
    EXPECT_FALSE(fa2.match("ga"));

    EXPECT_FALSE(fa.isIncludedIn(fa2));
    EXPECT_TRUE(fa2.isIncludedIn(fa));
}
TEST(isIncludedIn, sameSymbolsFalse)
{
    fa::Automaton fa;
    fa::Automaton fa2;
    fa::Automaton fa3;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    fa.setStateFinal(1);
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addSymbol('c'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.match("a"));
    EXPECT_FALSE(fa.match("b"));
    EXPECT_FALSE(fa.match("c"));
    EXPECT_TRUE(fa::Automaton::createComplement(fa).match("b"));
    EXPECT_TRUE(fa::Automaton::createComplement(fa).match("c"));

    EXPECT_FALSE(fa.match("abcca"));
EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa2.setStateFinal(1);
    fa2.setStateInitial(0);
    EXPECT_TRUE(fa2.addSymbol('a'));
    EXPECT_TRUE(fa2.addSymbol('b'));
    EXPECT_TRUE(fa2.addSymbol('c'));
    EXPECT_TRUE(fa2.addTransition(0,'b',1));
    EXPECT_TRUE(fa2.match("b"));
    EXPECT_FALSE(fa2.match("a"));
    EXPECT_FALSE(fa2.match("c"));
    EXPECT_FALSE(fa2.match("abcca"));

    EXPECT_TRUE(fa3.addState(0));
    EXPECT_TRUE(fa3.addState(1));
    fa3.setStateFinal(1);
    fa3.setStateInitial(0);
    EXPECT_TRUE(fa3.addSymbol('a'));
    EXPECT_TRUE(fa3.addSymbol('b'));
    EXPECT_TRUE(fa3.addSymbol('c'));
    EXPECT_TRUE(fa3.addTransition(0,'c',1));
    EXPECT_TRUE(fa3.match("c"));
    EXPECT_FALSE(fa3.match("a"));
    EXPECT_FALSE(fa3.match("b"));
    EXPECT_FALSE(fa3.match("abcca"));
    EXPECT_FALSE(fa.isLanguageEmpty());
    EXPECT_FALSE(fa2.isLanguageEmpty());
    EXPECT_FALSE(fa3.isLanguageEmpty());
    EXPECT_FALSE(fa.isIncludedIn(fa2));
    EXPECT_FALSE(fa.isIncludedIn(fa3));
    EXPECT_FALSE(fa2.isIncludedIn(fa3));
    EXPECT_FALSE(fa2.isIncludedIn(fa));
    EXPECT_FALSE(fa3.isIncludedIn(fa2));
    EXPECT_FALSE(fa3.isIncludedIn(fa));

}
TEST(isIncludedIn, differentSymbol5)
{   
    fa::Automaton fa;
    fa::Automaton fa2;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    fa.setStateFinal(1);
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));

    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa2.setStateFinal(1);
    fa2.setStateInitial(0);
    EXPECT_TRUE(fa2.addSymbol('z'));
    EXPECT_TRUE(fa2.addSymbol('b'));
    EXPECT_TRUE(fa2.addTransition(0,'z',1));
    EXPECT_FALSE(fa.isIncludedIn(fa2));
    EXPECT_FALSE(fa2.isIncludedIn(fa));
    
}


TEST(isIncludedIn, differentSymbolEmpty)
{   
    fa::Automaton fa;
    fa::Automaton fa2;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    fa.setStateFinal(1);
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(0,'a',1));

    EXPECT_TRUE(fa2.addState(0));
    EXPECT_TRUE(fa2.addState(1));
    fa2.setStateInitial(0);
    EXPECT_TRUE(fa2.addSymbol('z'));
    EXPECT_TRUE(fa2.addSymbol('e'));
    EXPECT_TRUE(fa2.addTransition(0,'z',1));
    EXPECT_TRUE(fa2.isLanguageEmpty());
    EXPECT_FALSE(fa.isIncludedIn(fa2));
    EXPECT_TRUE(fa2.isIncludedIn(fa));
    
}
TEST(removeNonAccessibleStates, etatPuitAccessibleNonCoAccessible)
{
   fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(0);
    fa.setStateFinal(3);
    fa.setStateFinal(4);
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',3));
    EXPECT_TRUE(fa.addTransition(2,'a',1));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(3,'b',5));
    EXPECT_TRUE(fa.addTransition(4,'a',3));
    EXPECT_TRUE(fa.addTransition(4,'b',5));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',5));
    fa.removeNonAccessibleStates();
    EXPECT_TRUE(fa.hasState(5));
}
TEST(createMinimalMoore, AlreadyMinimal)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(5));
   EXPECT_TRUE(fa.addState(9));
   EXPECT_TRUE(fa.addState(2));
   fa.setStateFinal(5);
   fa.setStateInitial(5);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',9));
    EXPECT_TRUE(fa.addTransition(9,'a',9));
    EXPECT_TRUE(fa.addTransition(9,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',5));
    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa.match("abbb"));
    EXPECT_TRUE(fa.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa.match("abbaaaa"));
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_EQ(fa.countStates(), (size_t)3);
    EXPECT_EQ(fa.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
   fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
       EXPECT_EQ(fa2.countStates(), (size_t)3);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
   EXPECT_TRUE(fa2.match("a"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa2.match("abbb"));
    EXPECT_TRUE(fa2.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa2.match("abbaaaa"));
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
}
TEST(createMinimalMoore, empty)
{
    fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addSymbol('a'));
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isLanguageEmpty());
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_EQ(fa2.countStates(),(size_t)1);
}
TEST(createMinimalMoore, empty2)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateFinal(1);
    fa.setStateFinal(5);
    EXPECT_TRUE(fa.addTransition(1,'a',3));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',4));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(3,'a',5));
    EXPECT_TRUE(fa.addTransition(3,'b',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));
    EXPECT_TRUE(fa.addTransition(5,'a',3));
    EXPECT_TRUE(fa.addTransition(5,'b',2));
    EXPECT_TRUE(fa.isComplete());
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_EQ(fa2.countStates(), (size_t)1);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
}
TEST(createMinimalMoore, nonAccessibleStates)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    EXPECT_TRUE(fa.addState(6));
    EXPECT_TRUE(fa.addState(12));
    EXPECT_TRUE(fa.addState(10));

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',5));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'b',2));
    EXPECT_TRUE(fa.addTransition(4,'b',3));
    EXPECT_TRUE(fa.addTransition(4,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'a',4));
    EXPECT_TRUE(fa.addTransition(5,'b',6));
    EXPECT_TRUE(fa.addTransition(6,'a',6));
    EXPECT_TRUE(fa.addTransition(6,'b',1));
    EXPECT_TRUE(fa.addTransition(10,'a',12));
    EXPECT_TRUE(fa.addTransition(10,'b',12));
    EXPECT_TRUE(fa.addTransition(12,'a',10));
    EXPECT_TRUE(fa.addTransition(12,'b',10));

    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa.match("abbb"));
    EXPECT_TRUE(fa.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa.match("abbaaaa"));

    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_EQ(fa2.countStates(), (size_t)3);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match("a"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa2.match("abbb"));
    EXPECT_TRUE(fa2.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa2.match("abbaaaa"));

}
TEST(createMinimalMoore, OnlyFinalStates)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa.setStateFinal(1);
    fa.setStateFinal(2);
    fa.setStateFinal(3);
    fa.setStateFinal(4);
    fa.setStateFinal(5);

    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',3));
    EXPECT_TRUE(fa.addTransition(2,'a',1));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(3,'b',5));
    EXPECT_TRUE(fa.addTransition(4,'a',3));
    EXPECT_TRUE(fa.addTransition(4,'b',5));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',5));
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_EQ(fa2.countStates(),(size_t)1);
    EXPECT_FALSE(fa2.isLanguageEmpty());


}
TEST(createMinimalMoore, AlreadyMinimal2)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addState(1));
   EXPECT_TRUE(fa.addState(2));
   EXPECT_TRUE(fa.addState(3));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
   EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(1,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',3));
    EXPECT_TRUE(fa.addTransition(3,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'b',3));
    fa.setStateFinal(2);
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("baaaab"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("baaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_TRUE(fa.match("aaaaaabaaaaaaaa"));
    EXPECT_FALSE(fa.match("aaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa.match("b"));
    EXPECT_FALSE(fa.match("abbbb"));
    EXPECT_FALSE(fa.match("bbbbbbbbb"));
    EXPECT_FALSE(fa.match("bbb"));
    EXPECT_FALSE(fa.match("bbbaaaa"));
    EXPECT_FALSE(fa.match("bbab"));
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("baaaab"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("baaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa2.match(""));
    EXPECT_TRUE(fa2.match("aaaaaabaaaaaaaa"));
    EXPECT_FALSE(fa2.match("aaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa2.match("b"));
    EXPECT_FALSE(fa2.match("abbbb"));
    EXPECT_FALSE(fa2.match("bbbbbbbbb"));
    EXPECT_FALSE(fa2.match("bbb"));
    EXPECT_FALSE(fa2.match("bbbaaaa"));
    EXPECT_FALSE(fa2.match("bbab"));

}
TEST(createMinimalMoore, exCours)
{
   fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(0);
    fa.setStateFinal(3);
    fa.setStateFinal(4);
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',3));
    EXPECT_TRUE(fa.addTransition(2,'a',1));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(3,'b',5));
    EXPECT_TRUE(fa.addTransition(4,'a',3));
    EXPECT_TRUE(fa.addTransition(4,'b',5));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',5));

    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_EQ(fa2.countStates(),(size_t) 4);
    EXPECT_EQ(fa2.countSymbols(),(size_t) 2);
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("abaa"));
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("bab"));
    EXPECT_FALSE(fa.match("aaaa"));
    EXPECT_FALSE(fa.match("bbb"));
    EXPECT_FALSE(fa.match("bbbaaa"));
    EXPECT_FALSE(fa.match("bbab"));
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("abaa"));
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("bab"));
    EXPECT_FALSE(fa2.match("aaaa"));
    EXPECT_FALSE(fa2.match("bbb"));
    EXPECT_FALSE(fa2.match("bbbaaa"));
    EXPECT_FALSE(fa2.match("bbab"));


}
TEST(createMinimalMoore, exCours2)
{
   fa::Automaton fa;
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    EXPECT_TRUE(fa.addState(6));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',5));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'b',2));
    EXPECT_TRUE(fa.addTransition(4,'b',3));
    EXPECT_TRUE(fa.addTransition(4,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'a',4));
    EXPECT_TRUE(fa.addTransition(5,'b',6));
    EXPECT_TRUE(fa.addTransition(6,'a',6));
    EXPECT_TRUE(fa.addTransition(6,'b',1));
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa.match("abbb"));
    EXPECT_TRUE(fa.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa.match("abbaaaa"));

    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_EQ(fa2.countStates(), (size_t)3);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match("a"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa2.match("abbb"));
    EXPECT_TRUE(fa2.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa2.match("abbaaaa"));

}
TEST(createMinimalMoore, notMinimal)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(5);
    EXPECT_TRUE(fa.addTransition(1,'a',3));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',4));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(3,'a',5));
    EXPECT_TRUE(fa.addTransition(3,'b',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));
    EXPECT_TRUE(fa.addTransition(5,'a',3));
    EXPECT_TRUE(fa.addTransition(5,'b',2));
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match(""));
    EXPECT_TRUE(fa.match("aaaa"));
    EXPECT_TRUE(fa.match("aaaabbbb"));
    EXPECT_TRUE(fa.match("aabbbbaaaa"));
    EXPECT_FALSE(fa.match("aabbbaaa"));
    EXPECT_FALSE(fa.match("aaabbaabbaabba"));
    EXPECT_FALSE(fa.match("aaaabbbaabbbab"));


    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_EQ(fa2.countStates(), (size_t)4);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match(""));
    EXPECT_TRUE(fa2.match("aaaa"));
    EXPECT_TRUE(fa2.match("aaaabbbb"));
    EXPECT_TRUE(fa2.match("aabbbbaaaa"));
    EXPECT_FALSE(fa2.match("aabbbbaaa"));
    EXPECT_FALSE(fa2.match("aaabbaabbaabba"));
    EXPECT_FALSE(fa2.match("aaaabbbaabbbab"));
}

TEST(createMinimalMoore, notDeterministic)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(4);
    EXPECT_TRUE(fa.addTransition(0,'a',3));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(0,'a',2));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',4));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(2,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));

    EXPECT_TRUE(fa.isValid());
    EXPECT_FALSE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("abb"));
    EXPECT_TRUE(fa.match("aa"));
    EXPECT_TRUE(fa.match("bbaaaabbbb"));
    EXPECT_TRUE(fa.match("baa"));
    EXPECT_TRUE(fa.match("baababbab"));
    EXPECT_TRUE(fa.match("aaa"));
    EXPECT_TRUE(fa.match("aaababbabaaa"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_FALSE(fa.match("ab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("aba"));
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("abb"));
    EXPECT_TRUE(fa2.match("aa"));
    EXPECT_TRUE(fa2.match("bbaaaabbbb"));
    EXPECT_TRUE(fa2.match("baa"));
    EXPECT_TRUE(fa2.match("baababbab"));
    EXPECT_TRUE(fa2.match("aaa"));
    EXPECT_TRUE(fa2.match("aaababbabaaa"));
    EXPECT_FALSE(fa2.match(""));
    EXPECT_FALSE(fa2.match("ab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);
}
TEST(createMinimalMoore, 2trashStatesNotComplete)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addState(1));
   EXPECT_TRUE(fa.addState(2));
   EXPECT_TRUE(fa.addState(3));
   EXPECT_TRUE(fa.addState(9));
   EXPECT_TRUE(fa.addState(10));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.setStateFinal(3);
   EXPECT_TRUE(fa.addTransition(0,'a',1));
   EXPECT_TRUE(fa.addTransition(0,'b',9));
   EXPECT_TRUE(fa.addTransition(1,'a',2));
   EXPECT_TRUE(fa.addTransition(2,'a',3));
   EXPECT_TRUE(fa.addTransition(2,'b',3));
   EXPECT_TRUE(fa.addTransition(3,'a',2));
   EXPECT_TRUE(fa.addTransition(3,'b',2));
   EXPECT_TRUE(fa.addTransition(9,'a',10));
   EXPECT_TRUE(fa.addTransition(9,'b',10));
   EXPECT_TRUE(fa.addTransition(10,'a',9));
   EXPECT_TRUE(fa.addTransition(10,'b',9));
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_FALSE(fa.isComplete());
    EXPECT_TRUE(fa.match("aa"));
    EXPECT_TRUE(fa.match("aab"));
    EXPECT_TRUE(fa.match("aaab"));
    EXPECT_TRUE(fa.match("aababab"));
    EXPECT_FALSE(fa.match("bbba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("aba"));
    fa::Automaton fa2 = fa::Automaton::createMinimalMoore(fa);
        EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.match("aa"));
    EXPECT_TRUE(fa2.match("aab"));
    EXPECT_TRUE(fa2.match("aaab"));
    EXPECT_TRUE(fa2.match("aababab"));
    EXPECT_FALSE(fa2.match("bbba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);

}

TEST(createMinimalBrzozowski , AlreadyMinimal)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(5));
   EXPECT_TRUE(fa.addState(9));
   EXPECT_TRUE(fa.addState(2));
   fa.setStateFinal(5);
   fa.setStateInitial(5);
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',9));
    EXPECT_TRUE(fa.addTransition(9,'a',9));
    EXPECT_TRUE(fa.addTransition(9,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',5));
    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa.match("abbb"));
    EXPECT_TRUE(fa.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa.match("abbaaaa"));
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_EQ(fa.countStates(), (size_t)3);
    EXPECT_EQ(fa.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
   fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
       EXPECT_EQ(fa2.countStates(), (size_t)3);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
   EXPECT_TRUE(fa2.match("a"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa2.match("abbb"));
    EXPECT_TRUE(fa2.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa2.match("abbaaaa"));
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
}
TEST(createMinimalBrzozowski , empty)
{
    fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addSymbol('a'));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_TRUE(fa2.isLanguageEmpty());
    EXPECT_TRUE(fa2.isValid());
    EXPECT_EQ(fa2.countStates(),(size_t)1);
}
TEST(createMinimalBrzozowski , empty2)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateFinal(1);
    fa.setStateFinal(5);
    EXPECT_TRUE(fa.addTransition(1,'a',3));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',4));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(3,'a',5));
    EXPECT_TRUE(fa.addTransition(3,'b',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));
    EXPECT_TRUE(fa.addTransition(5,'a',3));
    EXPECT_TRUE(fa.addTransition(5,'b',2));
    EXPECT_TRUE(fa.isComplete());
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(), (size_t)1);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
}
TEST(createMinimalBrzozowski , nonAccessibleStates)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    EXPECT_TRUE(fa.addState(6));
    EXPECT_TRUE(fa.addState(12));
    EXPECT_TRUE(fa.addState(10));

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',5));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'b',2));
    EXPECT_TRUE(fa.addTransition(4,'b',3));
    EXPECT_TRUE(fa.addTransition(4,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'a',4));
    EXPECT_TRUE(fa.addTransition(5,'b',6));
    EXPECT_TRUE(fa.addTransition(6,'a',6));
    EXPECT_TRUE(fa.addTransition(6,'b',1));
    EXPECT_TRUE(fa.addTransition(10,'a',12));
    EXPECT_TRUE(fa.addTransition(10,'b',12));
    EXPECT_TRUE(fa.addTransition(12,'a',10));
    EXPECT_TRUE(fa.addTransition(12,'b',10));

    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa.match("abbb"));
    EXPECT_TRUE(fa.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa.match("abbaaaa"));

    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(), (size_t)3);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match("a"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa2.match("abbb"));
    EXPECT_TRUE(fa2.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa2.match("abbaaaa"));

}
TEST(createMinimalBrzozowski , OnlyFinalStates)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa.setStateFinal(1);
    fa.setStateFinal(2);
    fa.setStateFinal(3);
    fa.setStateFinal(4);
    fa.setStateFinal(5);

    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',3));
    EXPECT_TRUE(fa.addTransition(2,'a',1));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(3,'b',5));
    EXPECT_TRUE(fa.addTransition(4,'a',3));
    EXPECT_TRUE(fa.addTransition(4,'b',5));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',5));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_EQ(fa2.countStates(),(size_t)1);

}
TEST(createMinimalBrzozowski , AlreadyMinimal2)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addState(1));
   EXPECT_TRUE(fa.addState(2));
   EXPECT_TRUE(fa.addState(3));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
   EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(1,'a',1));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',3));
    EXPECT_TRUE(fa.addTransition(3,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'b',3));
    fa.setStateFinal(2);
    fa.setStateInitial(0);
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("baaaab"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("baaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_TRUE(fa.match("aaaaaabaaaaaaaa"));
    EXPECT_FALSE(fa.match("aaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa.match("b"));
    EXPECT_FALSE(fa.match("abbbb"));
    EXPECT_FALSE(fa.match("bbbbbbbbb"));
    EXPECT_FALSE(fa.match("bbb"));
    EXPECT_FALSE(fa.match("bbbaaaa"));
    EXPECT_FALSE(fa.match("bbab"));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("baaaab"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("baaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa2.match(""));
    EXPECT_TRUE(fa2.match("aaaaaabaaaaaaaa"));
    EXPECT_FALSE(fa2.match("aaaaaaaaaaaaaa"));
    EXPECT_FALSE(fa2.match("b"));
    EXPECT_FALSE(fa2.match("abbbb"));
    EXPECT_FALSE(fa2.match("bbbbbbbbb"));
    EXPECT_FALSE(fa2.match("bbb"));
    EXPECT_FALSE(fa2.match("bbbaaaa"));
    EXPECT_FALSE(fa2.match("bbab"));

}
TEST(createMinimalBrzozowski , exCours)
{
   fa::Automaton fa;
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(0);
    fa.setStateFinal(3);
    fa.setStateFinal(4);
    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',3));
    EXPECT_TRUE(fa.addTransition(2,'a',1));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(3,'b',5));
    EXPECT_TRUE(fa.addTransition(4,'a',3));
    EXPECT_TRUE(fa.addTransition(4,'b',5));
    EXPECT_TRUE(fa.addTransition(5,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'b',5));

    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(),(size_t) 4);
    EXPECT_EQ(fa2.countSymbols(),(size_t) 2);
    EXPECT_TRUE(fa.match("ab"));
    EXPECT_TRUE(fa.match("abaa"));
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("bab"));
    EXPECT_FALSE(fa.match("aaaa"));
    EXPECT_FALSE(fa.match("bbb"));
    EXPECT_FALSE(fa.match("bbbaaa"));
    EXPECT_FALSE(fa.match("bbab"));
    EXPECT_TRUE(fa2.match("ab"));
    EXPECT_TRUE(fa2.match("abaa"));
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("bab"));
    EXPECT_FALSE(fa2.match("aaaa"));
    EXPECT_FALSE(fa2.match("bbb"));
    EXPECT_FALSE(fa2.match("bbbaaa"));
    EXPECT_FALSE(fa2.match("bbab"));


}
TEST(createMinimalBrzozowski , exCours2)
{
   fa::Automaton fa;
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    EXPECT_TRUE(fa.addState(6));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(2);
    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',5));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',4));
    EXPECT_TRUE(fa.addTransition(3,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'b',2));
    EXPECT_TRUE(fa.addTransition(4,'b',3));
    EXPECT_TRUE(fa.addTransition(4,'a',5));
    EXPECT_TRUE(fa.addTransition(5,'a',4));
    EXPECT_TRUE(fa.addTransition(5,'b',6));
    EXPECT_TRUE(fa.addTransition(6,'a',6));
    EXPECT_TRUE(fa.addTransition(6,'b',1));
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("a"));
    EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa.match("abbb"));
    EXPECT_TRUE(fa.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("abab"));
    EXPECT_FALSE(fa.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa.match("abbaaaa"));

    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(), (size_t)3);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match("a"));
    EXPECT_TRUE(fa2.match("aaaaaaaaaaaa"));
    EXPECT_TRUE(fa2.match("abbb"));
    EXPECT_TRUE(fa2.match("abbaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaaabaaaaaaaaaaaaab"));
    EXPECT_TRUE(fa2.match("abaaabaaaaaaaaaaaaab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("abab"));
    EXPECT_FALSE(fa2.match("aaaaaaabaaaa"));
    EXPECT_FALSE(fa2.match("abbaaaa"));

}
TEST(createMinimalBrzozowski , notMinimal)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addState(5));
    fa.setStateInitial(1);
    fa.setStateFinal(1);
    fa.setStateFinal(5);
    EXPECT_TRUE(fa.addTransition(1,'a',3));
    EXPECT_TRUE(fa.addTransition(1,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'a',4));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(3,'a',5));
    EXPECT_TRUE(fa.addTransition(3,'b',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));
    EXPECT_TRUE(fa.addTransition(5,'a',3));
    EXPECT_TRUE(fa.addTransition(5,'b',2));
    EXPECT_TRUE(fa.isComplete());
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_TRUE(fa.match(""));
    EXPECT_TRUE(fa.match("aaaa"));
    EXPECT_TRUE(fa.match("aaaabbbb"));
    EXPECT_TRUE(fa.match("aabbbbaaaa"));
    EXPECT_FALSE(fa.match("aabbbaaa"));
    EXPECT_FALSE(fa.match("aaabbaabbaabba"));
    EXPECT_FALSE(fa.match("aaaabbbaabbbab"));


    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(), (size_t)4);
    EXPECT_EQ(fa2.countSymbols(), (size_t)2);
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match(""));
    EXPECT_TRUE(fa2.match("aaaa"));
    EXPECT_TRUE(fa2.match("aaaabbbb"));
    EXPECT_TRUE(fa2.match("aabbbbaaaa"));
    EXPECT_FALSE(fa2.match("aabbbbaaa"));
    EXPECT_FALSE(fa2.match("aaabbaabbaabba"));
    EXPECT_FALSE(fa2.match("aaaabbbaabbbab"));
}

TEST(createMinimalBrzozowski , notDeterministic)
{
    fa::Automaton fa;
    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.addState(4));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(4);
    EXPECT_TRUE(fa.addTransition(0,'a',3));
    EXPECT_TRUE(fa.addTransition(0,'b',1));
    EXPECT_TRUE(fa.addTransition(0,'a',2));
    EXPECT_TRUE(fa.addTransition(0,'b',2));
    EXPECT_TRUE(fa.addTransition(1,'b',4));
    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'b',2));
    EXPECT_TRUE(fa.addTransition(2,'b',1));
    EXPECT_TRUE(fa.addTransition(2,'a',3));
    EXPECT_TRUE(fa.addTransition(3,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'a',4));
    EXPECT_TRUE(fa.addTransition(4,'b',4));

    EXPECT_TRUE(fa.isValid());
    EXPECT_FALSE(fa.isDeterministic());
    EXPECT_TRUE(fa.match("bb"));
    EXPECT_TRUE(fa.match("abb"));
    EXPECT_TRUE(fa.match("aa"));
    EXPECT_TRUE(fa.match("bbaaaabbbb"));
    EXPECT_TRUE(fa.match("baa"));
    EXPECT_TRUE(fa.match("baababbab"));
    EXPECT_TRUE(fa.match("aaa"));
    EXPECT_TRUE(fa.match("aaababbabaaa"));
    EXPECT_FALSE(fa.match(""));
    EXPECT_FALSE(fa.match("ab"));
    EXPECT_FALSE(fa.match("aba"));
    EXPECT_FALSE(fa.match("aba"));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_TRUE(fa2.isValid());
    EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.isComplete());
    EXPECT_TRUE(fa2.match("bb"));
    EXPECT_TRUE(fa2.match("abb"));
    EXPECT_TRUE(fa2.match("aa"));
    EXPECT_TRUE(fa2.match("bbaaaabbbb"));
    EXPECT_TRUE(fa2.match("baa"));
    EXPECT_TRUE(fa2.match("baababbab"));
    EXPECT_TRUE(fa2.match("aaa"));
    EXPECT_TRUE(fa2.match("aaababbabaaa"));
    EXPECT_FALSE(fa2.match(""));
    EXPECT_FALSE(fa2.match("ab"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);
}
TEST(createMinimalBrzozowski , 2trashStatesNotComplete)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addState(1));
   EXPECT_TRUE(fa.addState(2));
   EXPECT_TRUE(fa.addState(3));
   EXPECT_TRUE(fa.addState(9));
   EXPECT_TRUE(fa.addState(10));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    fa.setStateInitial(0);
    fa.setStateFinal(2);
    fa.setStateFinal(3);
   EXPECT_TRUE(fa.addTransition(0,'a',1));
   EXPECT_TRUE(fa.addTransition(0,'b',9));
   EXPECT_TRUE(fa.addTransition(1,'a',2));
   EXPECT_TRUE(fa.addTransition(2,'a',3));
   EXPECT_TRUE(fa.addTransition(2,'b',3));
   EXPECT_TRUE(fa.addTransition(3,'a',2));
   EXPECT_TRUE(fa.addTransition(3,'b',2));
   EXPECT_TRUE(fa.addTransition(9,'a',10));
   EXPECT_TRUE(fa.addTransition(9,'b',10));
   EXPECT_TRUE(fa.addTransition(10,'a',9));
   EXPECT_TRUE(fa.addTransition(10,'b',9));
    EXPECT_TRUE(fa.isDeterministic());
    EXPECT_FALSE(fa.isComplete());
    EXPECT_TRUE(fa.match("aa"));
    EXPECT_TRUE(fa.match("aab"));
    EXPECT_TRUE(fa.match("aaab"));
    EXPECT_TRUE(fa.match("aababab"));
    EXPECT_FALSE(fa.match("bbba"));
    EXPECT_FALSE(fa.match("abba"));
    EXPECT_FALSE(fa.match("aba"));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
        EXPECT_TRUE(fa2.isDeterministic());
    EXPECT_TRUE(fa2.match("aa"));
    EXPECT_TRUE(fa2.match("aab"));
    EXPECT_TRUE(fa2.match("aaab"));
    EXPECT_TRUE(fa2.match("aababab"));
    EXPECT_FALSE(fa2.match("bbba"));
    EXPECT_FALSE(fa2.match("abba"));
    EXPECT_FALSE(fa2.match("aba"));
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);

}

TEST(createMinimalBrzozowski , nonAccessible)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addState(1));
   EXPECT_TRUE(fa.addState(2));
   EXPECT_TRUE(fa.addState(3));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
   EXPECT_TRUE(fa.addSymbol('c'));
   EXPECT_TRUE(fa.addSymbol('d'));
    fa.setStateInitial(0);
    fa.setStateFinal(0);
    fa.setStateFinal(1);
   EXPECT_TRUE(fa.addTransition(0,'a',0));
   EXPECT_TRUE(fa.addTransition(0,'b',0));
   EXPECT_TRUE(fa.addTransition(0,'c',0));

    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(),(size_t)2);
    EXPECT_EQ(fa2.countSymbols(),(size_t)4);
    EXPECT_TRUE(fa2.isComplete());

}

TEST(createMinimalBrzozowski , withNonAccessibleState)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(0));
   EXPECT_TRUE(fa.addState(1));
   EXPECT_TRUE(fa.addState(2));
   EXPECT_TRUE(fa.addState(3));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
   EXPECT_TRUE(fa.addSymbol('c'));
fa.setStateInitial(0);
fa.setStateFinal(1);
   EXPECT_TRUE(fa.addTransition(0,'a',0));
   EXPECT_TRUE(fa.addTransition(0,'b',1));
   EXPECT_TRUE(fa.addTransition(0,'c',3));
EXPECT_TRUE(fa.addTransition(1,'a',1));
   EXPECT_TRUE(fa.addTransition(1,'b',1));
   EXPECT_TRUE(fa.addTransition(1,'c',1));
   EXPECT_TRUE(fa.addTransition(2,'a',0));
   EXPECT_TRUE(fa.addTransition(2,'b',2));
   EXPECT_TRUE(fa.addTransition(2,'c',3));
   EXPECT_TRUE(fa.addTransition(3,'a',3));
   EXPECT_TRUE(fa.addTransition(3,'b',3));
   EXPECT_TRUE(fa.addTransition(3,'c',3));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(),(size_t)3);
    EXPECT_EQ(fa2.countSymbols(),(size_t)3);
    EXPECT_TRUE(fa2.isComplete());
}

TEST(createMinimalBrzozowski , agsacze)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(7));
   EXPECT_TRUE(fa.addState(10));
   EXPECT_TRUE(fa.addState(13));
   EXPECT_TRUE(fa.addState(16));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
   EXPECT_TRUE(fa.addSymbol('c'));
fa.setStateInitial(7);
fa.setStateFinal(10);
   EXPECT_TRUE(fa.addTransition(7,'a',10));
   EXPECT_TRUE(fa.addTransition(7,'b',10));
   EXPECT_TRUE(fa.addTransition(7,'c',16));
EXPECT_TRUE(fa.addTransition(10,'a',10));
   EXPECT_TRUE(fa.addTransition(10,'b',10));
   EXPECT_TRUE(fa.addTransition(10,'c',10));
   EXPECT_TRUE(fa.addTransition(13,'a',7));
   EXPECT_TRUE(fa.addTransition(13,'b',13));
   EXPECT_TRUE(fa.addTransition(13,'c',16));
   EXPECT_TRUE(fa.addTransition(16,'a',16));
   EXPECT_TRUE(fa.addTransition(16,'b',16));
   EXPECT_TRUE(fa.addTransition(16,'c',16));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(),(size_t)3);
    EXPECT_EQ(fa2.countSymbols(),(size_t)3);
    EXPECT_TRUE(fa2.isComplete());
}

TEST(createMinimalBrzozowski , LoenaeTest)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(10));
   EXPECT_TRUE(fa.addState(13));
   EXPECT_TRUE(fa.addState(16));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
fa.setStateInitial(10);
fa.setStateFinal(10);
fa.setStateFinal(13);
fa.setStateFinal(16);
   EXPECT_TRUE(fa.addTransition(13,'a',10));
   EXPECT_TRUE(fa.addTransition(13,'b',16));
   EXPECT_TRUE(fa.addTransition(16,'a',16));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(),(size_t)2);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);
    EXPECT_TRUE(fa2.isComplete());
}

TEST(createMinimalBrzozowski , empty3)
{
    fa::Automaton fa;
   EXPECT_TRUE(fa.addState(10));
    EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);
    EXPECT_TRUE(fa2.isComplete());
}

TEST(createMinimalBrzozowski , notMini4)
{
   fa::Automaton fa;
   EXPECT_TRUE(fa.addState(7));
   EXPECT_TRUE(fa.addState(10));
   EXPECT_TRUE(fa.addState(13));
   EXPECT_TRUE(fa.addState(16));
   EXPECT_TRUE(fa.addState(19));
   EXPECT_TRUE(fa.addState(22));
   EXPECT_TRUE(fa.addState(25));
   EXPECT_TRUE(fa.addSymbol('a'));
   EXPECT_TRUE(fa.addSymbol('b'));
fa.setStateInitial(7);
fa.setStateFinal(16);
fa.setStateFinal(19);
fa.setStateFinal(25);
   EXPECT_TRUE(fa.addTransition(7,'a',10));
   EXPECT_TRUE(fa.addTransition(7,'b',13));
      EXPECT_TRUE(fa.addTransition(10,'a',13));
   EXPECT_TRUE(fa.addTransition(10,'b',16));
      EXPECT_TRUE(fa.addTransition(16,'a',19));
   EXPECT_TRUE(fa.addTransition(16,'b',22));
   EXPECT_TRUE(fa.addTransition(19,'a',16));
   EXPECT_TRUE(fa.addTransition(19,'b',22));
   EXPECT_TRUE(fa.addTransition(22,'a',22));
   EXPECT_TRUE(fa.addTransition(22,'b',22));
   EXPECT_TRUE(fa.addTransition(25,'a',16));
   EXPECT_TRUE(fa.addTransition(25,'b',22));
    fa::Automaton fa2 = fa::Automaton::createMinimalBrzozowski (fa);
    EXPECT_EQ(fa2.countStates(),(size_t)4);
    EXPECT_EQ(fa2.countSymbols(),(size_t)2);
    EXPECT_TRUE(fa2.isComplete());
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}