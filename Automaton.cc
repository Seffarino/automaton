#include "Automaton.h"

using namespace std;
namespace fa
{

  Automaton::Automaton()
  {
  }

  bool Automaton::isValid() const
  {
    return (alphabet.size() > 0 && etats.size() > 0);
  }

  // -------------------
  // --PARTIE SYMBOLES--
  // -------------------

  bool Automaton::addSymbol(char symbol)
  {
    if (!isgraph(symbol) || hasSymbol(symbol) || symbol == fa::Epsilon)
      return false;
    /* Je garde l'alphabet trié complexité de n dans l'insertion mais reduit la complexité
    plus tard */
    alphabet.insert(std::lower_bound(alphabet.begin(), alphabet.end(), symbol), symbol);
    return true;
  }

  bool Automaton::removeSymbol(char symbol)
  {
    if (symbol == fa::Epsilon)
      return false;
    for (size_t i = 0; i < alphabet.size(); i++)
    {
      if (alphabet[i] == symbol)
      {
        for (size_t j = 0; j < etats.size(); j++)
        {
          etats[j].transition_delete(symbol);
        }
        alphabet.erase(alphabet.begin() + i);
        return true;
      }
    }
    return false;
  }

  bool Automaton::hasSymbol(char symbol) const
  {
    if (symbol == fa::Epsilon)
      return false;
    for (size_t i = 0; i < alphabet.size(); i++)
    {
      if (alphabet[i] == symbol)
        return true;
    }
    return false;
  }

  std::size_t Automaton::countSymbols() const
  {
    return alphabet.size();
  }
  // -----------------
  // -- PARTIE ETAT --
  // -----------------
  bool Automaton::hasState(int state) const
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == state)
        return true;
    }
    return false;
  }
  bool Automaton::addState(int state)
  {
    if (hasState(state) || state < 0)
      return false;
    etats.push_back(Etat(state));
    return true;
  }

  bool Automaton::removeState(int to)
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == to)
      {
        for (size_t j = 0; j < etats.size(); j++)
        {
          etats[j].transition_delete(to);
        }
        etats.erase(etats.begin() + i);
        return true;
      }
    }
    return false;
  }

  std::size_t Automaton::countStates() const
  {
    return etats.size();
  }

  void Automaton::setStateInitial(int state)
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == state)
      {
        (etats[i].get_type() == 2 || etats[i].get_type() == 3) ? etats[i].set_type(3) : etats[i].set_type(1);
      }
    }
  }

  bool Automaton::isStateInitial(int state) const
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == state)
        return (etats[i].get_type() == 1 || etats[i].get_type() == 3);
    }
    return false;
  }

  void Automaton::setStateFinal(int state)
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == state)
      {
        (etats[i].get_type() == 1 || etats[i].get_type() == 3) ? etats[i].set_type(3) : etats[i].set_type(2);
      }
    }
  }

  bool Automaton::isStateFinal(int state) const
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == state)
        return (etats[i].get_type() == 2 || etats[i].get_type() == 3);
    }
    return false;
  }

  // ------------------------
  // -- PARTIE TRANSITIONS --
  // ------------------------
  bool Automaton::hasTransition(int from, char alpha, int to) const
  {
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == from)
      {
        return etats[i].has_transition(alpha, to);
      }
    }
    // return pour la non présence de l'etat initial
    return false;
  }

  bool Automaton::addTransition(int from, char alpha, int to)
  {
    if (!hasState(from) || !hasState(to) || (!hasSymbol(alpha) && alpha != fa::Epsilon) || (hasTransition(from, alpha, to)))
      return false;
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == from)
      {
        etats[i].transition_insert(alpha, to);
        return true;
      }
    }
    return false;
  }
  /* Améliorer complexité */
  bool Automaton::removeTransition(int from, char alpha, int to)
  {
    if (!hasState(from) || !hasState(to) || (!hasSymbol(alpha) && alpha != fa::Epsilon) || !hasTransition(from, alpha, to))
      return false;
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_etat() == from)
      {
        etats[i].transition_delete(alpha, to);
        return true;
      }
    }
    // return pour la non présence de la transition
    return false;
  }

  std::size_t Automaton::countTransitions() const
  {
    size_t res = 0;
    for (size_t i = 0; i < etats.size(); i++)
    {
      res += etats[i].get_transitions_size();
    }
    return res;
  }

  void Automaton::prettyPrint(std::ostream &os) const
  {
    /* PRINT STATES */
    os << "Initial states:" << std::endl;
    os << "\t";
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_type() == 1 || etats[i].get_type() == 3)
        os << etats[i].get_etat() << " ";
    }
    os << std::endl;
    os << "Final states:" << std::endl;
    os << "\t";
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_type() == 2 || etats[i].get_type() == 3)
        os << etats[i].get_etat() << " ";
    }
    os << std::endl;
    os << "Transitions:" << std::endl;
    /* PRINT EVERY STATESs */
    for (size_t i = 0; i < etats.size(); i++)
    {
      os << "\tFor state " << etats[i].get_etat() << ":" << std::endl;
      for (size_t j = 0; j < alphabet.size(); j++)
      {
        os << "\t\t For letter " << alphabet[j] << ":";
        auto transition = etats[i].get_transitions();
        for (auto it = transition.begin(); it != transition.end(); ++it)
        {
          if (it->first == alphabet[j])
          {
            os << " " << it->second;
          }
        }
        os << std::endl;
      }
    }
    os << std::endl;
  }
  bool Automaton::hasEpsilonTransition() const
  {
    assert(isValid());
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].has_transition(fa::Epsilon))
        return true;
    }
    return false;
  }
  /* Retourne vrai si un automate est deterministe
    1 : à un et un seul etat initial
    2 : chaque transition d'un état possède une seul fois un symbole x
    Une multimap est trié de base donc complexité de n dans la recherche d'un doublon
    comparaison index n et index n + 1
    */
  bool Automaton::isDeterministic() const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    bool initialstate = false;
    for (size_t i = 0; i < etats.size(); i++)
    {
      if (etats[i].get_type() == 1 || etats[i].get_type() == 3)
      {
        if (initialstate)
          return false;
        initialstate = true;
      }
      auto transitions = etats[i].get_transitions();
      for (auto it = transitions.begin(); it != transitions.end()--; ++it)
      {
        auto next = std::next(it, 1);
        if (next->first == it->first)
          return false;
      }
    }
    return initialstate;
  }

  /*  complexité O(n) n = nombre de lettre * nombre de transitions de chaque etats
    Vu que les transitions sont ordonnées et que l'alphabet l'est aussi on peut comparé
    en incrémentant l'index de l'alphabet
  */
  bool Automaton::isComplete() const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    for (size_t i = 0; i < etats.size(); i++)
    {
      auto transitions = etats[i].get_transitions();
      size_t j = 0;
      for (auto it = transitions.begin(); it != transitions.end()--; ++it)
      {
        if (j == alphabet.size())
          break;
        if (alphabet[j] == it->first)
          j++;
      }
      if (j < alphabet.size())
        return false;
    }
    return true;
  }
  /* Puisque trié O(n) un parcours de : n = taille de l'alphabet * nombre de transitions  */
  Automaton Automaton::createComplete(const Automaton &automaton)
  {
    assert(automaton.isValid());
    fa::Automaton res = automaton;
    if (automaton.isComplete())
    {
      return res;
    }
    int trashState = res.addTrashState();
    for (size_t i = 0; i < res.etats.size(); i++)
    {
      auto transitions = res.etats[i].get_transitions();
      int j = 0;
      for (auto it = transitions.begin(); it != transitions.end(); ++it)
      {
        /* Tant que le symbole ne correspond pas on ajoute la transition poubelle
        et on increment l'index de l'alphabet je rappele que l'alphabet ainsi que les trans
        -itions sont trié donc si le symbole à l'index de l'alphabet n'est pas le meme que
        celui de la transition, c'est que le symbole de la transition se situe forcement à droite du courrant de l'alphabet */
        while ((size_t)j < res.alphabet.size() && it->first != res.alphabet[j])
        {
          res.etats[i].transition_insert(res.alphabet[j], trashState);
          j++;
        }
        if (it->first == res.alphabet[j])
        {
          j++;
        }
      } /* Si nous avons parcourus toute les transitions de l'etats (meme nulle) et qu'il manque
      des transition nous les ajoutons */
      if ((size_t)j < res.alphabet.size())
      {
        res.addTransitionsTrash(j, res.etats[i], trashState);
      }
    }
    return res;
  }
  Automaton Automaton::createMirror(const Automaton &automaton)
  {
    assert(automaton.isValid());
    fa::Automaton res = automaton;
    res.deleteAllTransitions();
    for (size_t i = 0; i < automaton.etats.size(); i++)
    {
      /* Swap the state type  */
      if (automaton.etats[i].get_type() == 1)
        res.etats[i].set_type(2);
      if (automaton.etats[i].get_type() == 2)
        res.etats[i].set_type(1);
      auto transitions = automaton.etats[i].get_transitions();
      for (auto it = transitions.begin(); it != transitions.end(); ++it)
      {

        int etat_index = it->second;
        res.addTransition(etat_index, it->first, automaton.etats[i].get_etat());
      }
    }
    return res;
  }

  void Automaton::removeNonAccessibleStates()
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    Graph graph = Graph::createGraph(*this);
    std::set<int> initial_states = getInitialStates();
    /* If there is no initialState */
    if (initial_states.empty())
    {
      /* No increment because countStates will decrement itself */
      for (size_t j = 0; j < countStates();)
      {
        removeState(etats[j].get_etat());
      }
      addState(1);
      setStateInitial(1);
      return;
    }
    for (auto i : initial_states)
    {
      graph.DepthFirstSearch(i);
    }

    for (auto it = graph.vertices.begin(); it != graph.vertices.end(); ++it)
    {
      if (!it->second.is_visited)
        removeState(it->first);
    }
  }

  void Automaton::removeNonCoAccessibleStates()
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    Graph graph = Graph::createGraph(*this);
    std::set<int> finalStates = getFinalStates();
    if (finalStates.empty())
    {
      /* No increment because countStates will decrement itself */
      for (size_t j = 0; j < countStates();)
      {
        removeState(etats[j].get_etat());
      }
      addState(1);
      setStateInitial(1);
      return;
    }
    for (auto &i : etats)
    {
      graph.DepthFirstSearch(i.get_etat());
    }

    for (auto it = graph.vertices.begin(); it != graph.vertices.end(); ++it)
    {
      if (!it->second.is_co_accessible && !it->second.is_final)
        removeState(it->first);
    }
  }

  bool Automaton::isLanguageEmpty() const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    Graph graph = Graph::createGraph(*this);
    std::set<int> initial_states = getInitialStates();
    /* If there is no initialState */
    for (auto &i : initial_states)
    {
      if (!graph.DepthFirstSearch(i))
        return false;
    }
    return true;
  }
  /* https://www.techiedelight.com/use-std-pair-key-std-map-cpp/ */
  Automaton Automaton::createProduct(const Automaton &lhs, const Automaton &rhs)
  {
    assert(lhs.isValid());
    assert(!lhs.hasEpsilonTransition());
    assert(rhs.isValid());
    assert(!rhs.hasEpsilonTransition());
    fa::Automaton res;
    std::map<int, pair<int, int>> stateMap;
    int index = 0;
    for (size_t i = 0; i < lhs.countStates(); i++)
    {
      for (size_t j = 0; j < rhs.countStates(); j++)
      {
        index++;
        stateMap.insert(make_pair(index, make_pair(lhs.etats[i].get_etat(), rhs.etats[j].get_etat())));
        res.addState(index);
        if (lhs.isStateInitial(lhs.etats[i].get_etat()) && rhs.isStateInitial(rhs.etats[j].get_etat()))
          res.setStateInitial(index);
        if (lhs.isStateFinal(lhs.etats[i].get_etat()) && rhs.isStateFinal(rhs.etats[j].get_etat()))
          res.setStateFinal(index);
      }
    }
    for (size_t w = 0; w < lhs.countSymbols(); w++)
    {
      for (size_t z = 0; z < rhs.countSymbols(); z++)
      {
        if (lhs.alphabet[w] == rhs.alphabet[z])
          res.addSymbol(lhs.alphabet[w]);
      }
    }

    for (auto it = stateMap.begin(); it != stateMap.end(); ++it)
    {

      for (size_t a = 0; a < res.countSymbols(); a++)
      {
        auto left_state = lhs.getEtat(it->second.first);
        auto right_state = rhs.getEtat(it->second.second);
        int left_to = -1;
        int right_to = -1;
        auto transition_left = lhs.etats[left_state].get_transitions();
        auto transition_right = rhs.etats[right_state].get_transitions();
        for (auto itLeft = transition_left.begin(); itLeft != transition_left.end(); ++itLeft)
        {
          if (itLeft->first == res.alphabet[a])
            left_to = itLeft->second;
          for (auto itRight = transition_right.begin(); itRight != transition_right.end(); ++itRight)
          {
            if (itRight->first == res.alphabet[a])
              right_to = itRight->second;
            if (left_to != -1 && right_to != -1)
            {
              for (auto it3 = stateMap.begin(); it != stateMap.end(); ++it3)
              {
                if (it3->second.first == left_to && it3->second.second == right_to)
                {
                  res.addTransition(it->first, res.alphabet[a], it3->first);
                  left_to = right_to = -1;
                  break;
                }
              }
            }
          }
        }
      }
    }
    if (res.countSymbols() == 0)
      res.addSymbol('h');
    if (res.countStates() == 0)
      res.addState(1);
    return res;
  }
  bool Automaton::hasEmptyIntersectionWith(const Automaton &other) const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    assert(other.isValid());
    assert(!other.hasEpsilonTransition());
    if (!this->isValid())
      return true;
    fa::Automaton product;
    product = createProduct(*this, other);
    if (product.isLanguageEmpty())
    {
      return true;
    }
    return false;
  }

  /**
   * Read the string and compute the state set after traversing the automaton
   */
  std::set<int> Automaton::readString(const std::string &word) const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    std::set<int> res = getInitialStates();
    if (word.size() == 0)
    {
      res = getInitialStates();
      return res;
    }
    size_t index = 0;
    bool run = true;
    while (index < word.size() && run)
    {
      if (readLetter(word[index], res).size() == 0)
        run = false;
      std::set<int> temp = res;
      res.clear();
      res.merge(readLetter(word[index], temp));
      index++;
    }
    return res;
  }

  /**
   * Tell if the word is in the language accepted by the automaton
   */
  bool Automaton::match(const std::string &word) const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    std::set<int> res = readString(word);
    for (auto r : res)
    {
      if (isStateFinal(r))
        return true;
    }
    return false;
  }

  /**
   * Tell if the langage accepted by the automaton is included in the
   * language accepted by the other automaton
   */
  bool Automaton::isIncludedIn(const Automaton &other) const
  {
    assert(isValid());
    assert(!hasEpsilonTransition());
    assert(other.isValid());
    assert(!other.hasEpsilonTransition());

    fa::Automaton complement = other;
    if (alphabet != other.alphabet)
    {
      for (auto letter : alphabet)
      {
        complement.addSymbol(letter);
      }
    }
    complement = fa::Automaton::createComplement(complement);
    return hasEmptyIntersectionWith(complement);
  }

  Automaton Automaton::createDeterministic(const Automaton &other)
  {
    assert(other.isValid());
    assert(!other.hasEpsilonTransition());
    Automaton res;
    if (other.isDeterministic())
    {
      return other;
    }
    for (auto letter : other.alphabet)
    {
      res.addSymbol(letter);
    }
    // 1 : get the initial states
    std::set<int> initialStates = other.getInitialStates();
    if (initialStates.empty())
    { // if initial state is empty we return a valid automaton
      res.addState(0);
      res.setStateInitial(0);
      return res;
    }
    //  The index of the state will be the new state value
    std::vector<std::set<int>> stateCorrespondance;
    stateCorrespondance.push_back(initialStates);
    // The index is the same as the stateCorrespondance
    std::vector<std::map<char, std::set<int>>> transitionCorrespondance;

    for (size_t i = 0; i < stateCorrespondance.size(); i++)
    {
      std::map<char, std::set<int>> transitionOfState;
      for (auto letter : other.alphabet)
      {
        // get the next states from the current state with all letter of alphabet
        auto nextStates = other.readLetter(letter, stateCorrespondance[i]);
        // if
        if (!nextStates.empty())
        {
          // loop though existing states to find if already present
          bool should_add = true;
          for (auto presentStates : stateCorrespondance)
          {
            if (presentStates == nextStates)
            {
              should_add = false;
            }
          }
          if (should_add)
          {
            stateCorrespondance.push_back(nextStates);
          }
        }
        // Adding the transitions to the transition map
        transitionOfState.insert(std::pair<char, std::set<int>>(letter, nextStates));
      }
      // Adding the transitions to the transition correspondance
      transitionCorrespondance.push_back(transitionOfState);
    }
    for (size_t i = 0; i < stateCorrespondance.size(); i++)
    {
      res.addState(i);
    }
    for (size_t i = 0; i < stateCorrespondance.size(); i++)
    {
      for (auto transi : transitionCorrespondance[i])
      {
        std::set<int> destTransi = transi.second;
        for (size_t j = 0; j < stateCorrespondance.size(); j++)
        {
          if (stateCorrespondance[j] == destTransi)
          {
            res.addTransition(i, transi.first, j);
          }
        }
      }
    }
    res.setStateInitial(0);
    std::set<int> finalStates = other.getFinalStates();
    for (size_t i = 0; i < stateCorrespondance.size(); i++)
    {
      for (auto state : stateCorrespondance[i])
      {
        if (other.isStateFinal(state))
        {
          res.setStateFinal(i);
        }
      }
    }
    return res;
  }
  Automaton Automaton::createComplement(const Automaton &other)
  {
    assert(other.isValid());
    assert(!other.hasEpsilonTransition());
    Automaton res;
    res = other;
    if (!res.isDeterministic())
    {
      res = fa::Automaton::createDeterministic(res);
    }
    if (!res.isComplete())
    {
      res = fa::Automaton::createComplete(res);
    }
    for (size_t i = 0; i < res.countStates(); i++)
    { // reset the states to be not initial or final
      if (res.isStateFinal(res.etats[i].get_etat()))
      {
        if (res.isStateInitial(res.etats[i].get_etat()))
        {
          res.etats[i].set_type(1);
        }
        else
        {
          res.etats[i].set_type(0);
        }
      }
      else
      {
        res.setStateFinal(res.etats[i].get_etat());
      }
    }
    return res;
  }
  Automaton Automaton::createMinimalBrzozowski(const Automaton &other)
  {
    assert(other.isValid());
    assert(!other.hasEpsilonTransition());
    Automaton res;
    if (other.isLanguageEmpty())
    { // If empty the minimal is an automaton with one state
      res.addState(0);
      res.setStateInitial(0);
      res.alphabet = other.alphabet;
      for(auto letter : res.alphabet){
        res.addTransition(0,letter,0);
      }
      return res;
    }
    res = other;
    res = createMirror(res);
    res = createDeterministic(res);
    res.removeNonAccessibleStates();
    res = createMirror(res);
    res = createDeterministic(res);
    res = createComplete(res);
    return res;
  }

  Automaton Automaton::createMinimalMoore(const Automaton &other)
  {
    assert(other.isValid());
    assert(!other.hasEpsilonTransition());
    Automaton res;
    Automaton minimal;
    if (other.isLanguageEmpty())
    { // If empty the minimal is an automaton with one state
      res.addState(0);
      res.setStateInitial(0);
      res.alphabet = other.alphabet;
      for(auto letter : res.alphabet){
        res.addTransition(0,letter,0);
      }
      return res;
    }
    res = createDeterministic(other);
    res.removeNonAccessibleStates();
    res = createComplete(res); // From here our automaton is deterministic complete and has every states accessible
    std::vector<set<int>> groupedStates;
    std::vector<set<int>> groupedStatesBis;
    std::set<int> notFinalStates;
    for (auto it : res.etats)
    {
      if (it.get_type() == 0 || it.get_type() == 1)
      {
        notFinalStates.insert(it.get_etat());
      }
    }
    if(notFinalStates.empty()){
      minimal.addState(0);
      minimal.setStateInitial(0);
      minimal.setStateFinal(0);
      minimal.alphabet = other.alphabet;
      for(auto it : minimal.alphabet){
        minimal.addTransition(0,it,0);
      }
      return minimal;
    }
    std::set<int> finalStates = res.getFinalStates();
    groupedStates.push_back(notFinalStates);
    groupedStates.push_back(finalStates);
    do
    {

      groupedStatesBis = groupedStates;
      for (size_t i = 0; i < groupedStatesBis.size(); i++)
      {                                            // Group refining |||| bis : the old grouped states that remain unchanged
        std::multimap<char, int> firstTransitions; // The first state's transition is the group transition
        for (auto stateBis : groupedStatesBis[i])
        {
          std::multimap<char, int> refinedTransition = res.getRefinedTransition(groupedStatesBis, stateBis);
          if (firstTransitions.empty())
            firstTransitions = refinedTransition;
          if (firstTransitions != refinedTransition)
          {
            std::set<int> newGroup;
            for (auto sameTransitionState : groupedStatesBis[i])
            { // check if someone else in the group has same transitions
              if (refinedTransition == res.getRefinedTransition(groupedStatesBis, sameTransitionState))
              {
                newGroup.insert(sameTransitionState);
              }
            }
            for (auto stateFromNewGroup : newGroup) // delete those who do not belongs here anymore
            {
              for (auto it = groupedStates[i].begin(); it != groupedStates[i].end(); it++)
              {
                if (*it == stateFromNewGroup)
                {
                  it = groupedStates[i].erase(it);
                  break;
                }
              }
            }
            if (std::find(groupedStates.begin(), groupedStates.end(), newGroup) == groupedStates.end())
            {
              groupedStates.push_back(newGroup);
            }
          }
        }
      }
    } while (groupedStatesBis != groupedStates); // refining the groupedStates until the nore more groups to refine
    minimal.alphabet = res.alphabet;
    for (size_t i = 0; i < groupedStates.size(); i++)
    {
      minimal.addState(i);
    }
    for (size_t i = 0; i < groupedStates.size(); i++)
    {
      auto firstStateOfGroup = groupedStates[i].begin();
      auto refinedTransion = res.getRefinedTransition(groupedStates, *firstStateOfGroup);
      for (auto transition : refinedTransion)
      {
        minimal.addTransition(i, transition.first, transition.second);
      }
    }
    for (size_t i = 0; i < groupedStates.size(); i++)
    {
      for (auto state : groupedStates[i])
      {
        if (res.isStateInitial(state))
        {
          minimal.setStateInitial(i);
        }
        if (res.isStateFinal(state))
        {
          minimal.setStateFinal(i);
        }
      }
    }
    if(!minimal.isValid()){
      minimal.addState(1);
      minimal.addSymbol('a');
      }
    return minimal;
  }
}
