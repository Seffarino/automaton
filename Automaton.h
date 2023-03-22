#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <algorithm>

namespace fa
{
  /* Epsilon */
  constexpr char Epsilon = '\0';

  
  /* Etat Class */
  class Etat
  {
  private:
    int etat;
    int type; // 0 : ni final ni initial // 1 : inital // 2 : final // 3 : inital/final
    std::multimap<char, int> transitions;

  public:
    Etat(int state)
    {
      etat = state;
      type = 0;
    }

    int get_etat() const
    {
      return etat;
    }

    int get_type() const
    {
      return type;
    }

    void set_type(int new_type)
    {
      type = new_type;
    }

    /* Erase every transitions from a state */
    void transitionsReset()
    {
      transitions.clear();
    }

    std::multimap<char, int> get_transitions() const
    {
      return transitions;
    }
    /* True if a transition with the alpha symbol exist */
    bool has_transition(char alpha) const
    {
      for (auto it = transitions.begin(); it != transitions.end(); it++)
      {
        if (it->first == alpha)
        {
          return true;
        }
      }
      return false;
    }
    /* True if a transition pointing to the "to" state with the alpha symbol exist */
    bool has_transition(char alpha, int to) const
    {
      for (auto it = transitions.begin(); it != transitions.end(); it++)
      {
        if (it->first == alpha && it->second == to)
        {
          return true;
        }
      }
      return false;
    }
    size_t get_transitions_size() const
    {
      return transitions.size();
    }
    void transition_insert(char alpha, int to)
    {
      transitions.insert(std::pair<char, int>(alpha, to));
    }

    void transition_delete(int to)
    {
      for (auto it = transitions.begin(); it != transitions.end();)
      {
        if (it->second == to)
        {
          it = transitions.erase(it);
        }
        else
        {
          ++it;
        }
      }
    }
    void transition_delete(char alpha)
    {
      transitions.erase(alpha);
    }
    void transition_delete(char alpha, int to)
    {
      for (auto it = transitions.begin(); it != transitions.end();)
      {
        if (it->first == alpha && it->second == to)
        {
          it = transitions.erase(it);
        }
        else
        {
          ++it;
        }
      }
    }
  };
  /* Automaton class */
  class Automaton
  {
  public:
    std::vector<char> alphabet;
    std::vector<Etat> etats;
    int addTrashState()
    {
      srand((unsigned)time(0));
      int random_state = rand() % INT32_MAX;
      while (hasState(random_state))
      {
        random_state = rand() % 10000;
      }
      addState(random_state);
      return random_state;
    }
    std::set<int> readLetter(char letter,std::set<int> states) const
    {
      std::set<int> res;
      for (size_t i = 0; i < countStates(); i++)
      {
        for (auto state : states)
        {
          if(state == etats[i].get_etat())
          {
            auto transitions = etats[i].get_transitions();
            for(auto transition : transitions)
            {
              if(transition.first == letter)res.insert(transition.second);
            }
          }
        }
        
      }
      return res;
    }
    //only work with deterministic and complete
    int readLetter (char letter,int state) const
    {
      assert(isDeterministic() && isComplete() && isValid());
      for (size_t i = 0; i < countStates(); i++)
      {
        if(state == etats[i].get_etat())
          {
            auto transitions = etats[i].get_transitions();
            for(auto transition : transitions)
            {
              if(transition.first == letter)return transition.second;
            }
          }
      }
    }
    /* Add every symbol from index -> end of the Alphabet a transition to the trash state*/
    void addTransitionsTrash(int index, Etat &etat, int trash_state)
    {
      for (size_t i = index; i < alphabet.size(); i++)
      {
        etat.transition_insert(alphabet[i], trash_state);
      }
    }
    void deleteAllTransitions()
    {
      for (size_t i = 0; i < etats.size(); i++)
      {
        etats[i].transitionsReset();
      }
    }
    /* Return a single state that is initial */
    int getInitialState() const
    {
      for (size_t i = 0; i < countStates(); i++)
      {
        if(etats[i].get_type() % 2 == 1)return etats[i].get_etat();
      }
      return -1;
    }
  /* Retrun a range of initial states or an empty array if no state is initial */
    std::set<int> getInitialStates() const
    {
      std::set<int> res;
      for (size_t i = 0; i < countStates(); i++)
      {
        if(etats[i].get_type() % 2 == 1)res.insert(etats[i].get_etat());
      }
      return res;
    }
     std::set<int> getFinalStates() const
    {
      std::set<int> res;
      for (size_t i = 0; i < countStates(); i++)
      {
        if(etats[i].get_type() == 3 || etats[i].get_type() == 2 )res.insert(etats[i].get_etat());
      }
      return res;
    }
   
    size_t getEtat(int etat) const
    {
      for (size_t i = 0; i < etats.size(); i++)
      {
        if (etats[i].get_etat() == etat)
          return i;
      }
        return -1;
    }
    /* Takes a refined groupOfState and replace transitions dest by the number in the group */
  std::multimap<char,int> getRefinedTransition(std::vector<std::set<int>> groupedStates,int state) const
  {
    std::multimap<char,int> res;
    for(auto etat : etats){
      if(etat.get_etat() == state){
        res = etat.get_transitions();
        break;
      }
    }
    for(auto& transition : res){
      int initialTransitionDest = transition.second;
      for (size_t i = 0; i < groupedStates.size(); i++)
      {
        for(auto etat : groupedStates[i]){
          if(etat == transition.second){
            transition.second = i;
            break;
          }
        }
        if(transition.second != initialTransitionDest)break;
      }
    }
    return res;
  }
    /**
     * Build an empty automaton (no state, no transition).
     */
    Automaton();

    /**
     * Tell if an automaton is valid.
     *
     * A valid automaton has a non-empty set of states and a non-empty set of symbols
     */
    bool isValid() const;

    /**
     * Add a symbol to the automaton
     *
     * Epsilon is not a valid symbol.
     * Returns true if the symbol was effectively added
     */
    bool addSymbol(char symbol);

    /**
     * Remove a symbol from the automaton
     *
     * Returns true if the symbol was effectively removed
     */
    bool removeSymbol(char symbol);

    /**
     * Tell if the symbol is present in the automaton
     */
    bool hasSymbol(char symbol) const;

    /**
     * Count the number of symbols
     */
    std::size_t countSymbols() const;

    /**
     * Add a state to the automaton.
     *
     * By default, a newly added state is not initial and not final.
     * Returns true if the state was effectively added and false otherwise.
     */
    bool addState(int state);

    /**
     * Remove a state from the automaton.
     *
     * The transitions involving the state are also removed.
     * Returns true if the state was effectively removed and false otherwise.
     */
    bool removeState(int state);

    /**
     * Tell if the state is present in the automaton.
     */
    bool hasState(int state) const;

    /**
     * Compute the number of states.
     */
    std::size_t countStates() const;

    /**
     * Set the state initial.
     */
    void setStateInitial(int state);

    /**
     * Tell if the state is initial.
     */
    bool isStateInitial(int state) const;

    /**
     * Set the state final.
     */
    void setStateFinal(int state);

    /**
     * Tell if the state is final.
     */
    bool isStateFinal(int state) const;

    /**
     * Add a transition
     *
     * Returns true if the transition was effectively added and false otherwise.
     * If one of the state or the symbol does not exists, the transition is not added.
     */
    bool addTransition(int from, char alpha, int to);

    /**
     * Remove a transition
     *
     * Returns true if the transition was effectively removed and false otherwise.
     */
    bool removeTransition(int from, char alpha, int to);

    /**
     * Tell if a transition is present.
     */
    bool hasTransition(int from, char alpha, int to) const;

    /**
     * Compute the number of transitions.
     */
    std::size_t countTransitions() const;

    /**
     * Print the automaton in a friendly way
     */
    void prettyPrint(std::ostream &os) const;

    /**
     * Print the automaton with respect to the DOT specification
     */
    // void dotPrint(std::ostream& os) const;

    /**
     * Tell if the automaton has one or more epsilon-transition
     */
    bool hasEpsilonTransition() const;

    /**
     * Tell if the automaton is deterministic
     */
    bool isDeterministic() const;

    /**
     * Tell if the automaton is complete
     */
    bool isComplete() const;

    /**
     * Remove non-accessible states
     */
    void removeNonAccessibleStates();

    /**
     * Remove non-co-accessible states
     */
    void removeNonCoAccessibleStates();

    /**
     * Tell if the intersection with another automaton is empty
     */
    bool hasEmptyIntersectionWith(const Automaton &other) const;

    /**
     * Read the string and compute the state set after traversing the automaton
     */
    std::set<int> readString(const std::string &word) const;

    /**
     * Tell if the word is in the language accepted by the automaton
     */
    bool match(const std::string &word) const;

    /**
     * Tell if the langage accepted by the automaton is included in the
     * language accepted by the other automaton
     */
    bool isIncludedIn(const Automaton &other) const;

    /**
     * Create a mirror automaton
     */
    static Automaton createMirror(const Automaton &automaton);

    /**
     * Create a complete automaton, if not already complete
     */
    static Automaton createComplete(const Automaton &automaton);
    /**
     * Check if the language of the automaton is empty
     */
    bool isLanguageEmpty() const;
    /**
     * Create a complement automaton
     */
    static Automaton createComplement(const Automaton &automaton);

    /**
     * Create the product of two automata
     *
     * The product of two automata accept the intersection of the two languages.
     */
    static Automaton createProduct(const Automaton &lhs, const Automaton &rhs);
    /**
     * Create a deterministic automaton, if not already deterministic
     */
    static Automaton createDeterministic(const Automaton &other);

    /**
     * Create an equivalent minimal automaton with the Moore algorithm
     */
    static Automaton createMinimalMoore(const Automaton &other);
    /**
     * Create an equivalent minimal automaton with the Brzozowski algorithm
     */
    static Automaton createMinimalBrzozowski(const Automaton &other);

    static Automaton createMinimalHopcroft(const Automaton &other)
    {
      other.getFinalStates();
      Automaton res;
      res.addState(0);
      res.addSymbol('a');
      return res;
    }

    static Automaton createWithoutEspilon(const Automaton &other)
    {
      other.getFinalStates();
      Automaton res;
      res.addState(0);
      res.addSymbol('a');
      return res;
    }
  private:
  };
  struct Vertex
  {
    bool is_final;
    bool is_visited = false;
    bool is_co_accessible = false;
    std::vector<int> adjacents;
    Vertex(bool is_final, std::vector<int> adjacents)
    {
      this->is_final = is_final;
      this->adjacents = adjacents;
    }
  };

  class Graph
  {
  public:
    std::map<int, struct Vertex> vertices;
    Graph()
    {
    }
    void printGraph()
    {
      for(auto it = vertices.begin();it != vertices.end();++it)
      {
        std::cout << "Etat : " << it->first << "\n";
        std::cout << " final ? "<< it->second.is_final << "\n";
        std::cout << " visited ? "<< it->second.is_visited << "\n";
        std::cout << "Transition vers : ";
        for(u_long i = 0;i < it->second.adjacents.size();++i)
        {
          std::cout << it->second.adjacents[i] << " "  ;
        }
        std::cout << " \n \n";
      }
      std::cout << "\n";
    }
    void addVertex(int state,Vertex vertex)
    {
      vertices.insert(std::pair<int, Vertex>(state,vertex));
    }
    static Graph createGraph(const Automaton &automaton)
    {
      fa::Graph res;
      for (size_t i = 0; i < automaton.countStates(); i++)
      {
        std::vector<int> adjacents;
        auto transitions = automaton.etats[i].get_transitions();
        for (auto it = transitions.begin(); it != transitions.end(); ++it)
        {
          adjacents.insert(adjacents.begin(),it->second);
        }
        bool is_final = (automaton.etats[i].get_type() == 2 || automaton.etats[i].get_type() == 3);
        Vertex new_vertex(is_final,adjacents);
        res.addVertex(automaton.etats[i].get_etat(),new_vertex);
      }
      return res;
    }

/* Depth first search on a graph return true is there is a path to the final state */
    bool DepthFirstSearch(int vertex)
    {
      bool res = true;
      auto current_vertex = vertices.find(vertex);
      if(current_vertex->second.is_final){
        current_vertex->second.is_co_accessible = true;
        res = false;
      }
      if(current_vertex->second.is_co_accessible)res = false;
      if(current_vertex->second.is_visited == true)
      {
        return res;
      }
      current_vertex->second.is_visited = true;
      
      for(const auto &i : current_vertex->second.adjacents)
      {
        if(!DepthFirstSearch(i) )
        {
          res = false;
          current_vertex->second.is_co_accessible = true;
        }
      }
      return res;
    }
  };

}

#endif // AUTOMATON_H