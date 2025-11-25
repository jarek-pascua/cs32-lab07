#include "WordCount.h"
#include "tddFuncs.h"

#include <sstream>
#include <string>
#include <iostream>

int main() {

  {
    WordCount wc;
    wc.addAllWords("TT UCSB is the best TT");

    ASSERT_EQUALS(6, wc.getTotalWords());
    ASSERT_EQUALS(5, wc.getNumUniqueWords());
    ASSERT_EQUALS(2, wc.getWordCount("TT"));
    ASSERT_EQUALS(2, wc.getWordCount("tt"));
    ASSERT_EQUALS(1, wc.getWordCount("is"));
    ASSERT_EQUALS(1, wc.getWordCount("the"));
  }

  {
    WordCount wc;
    wc.addAllWords("TT UCSB is the best TT");

    std::stringstream ss;
    wc.dumpWordsSortedByWord(ss);

    std::string expected = "best 1\nis 1\nthe 1\ntt 2\nucsb 1\n";
    ASSERT_EQUALS(expected, ss.str());
  }

   {
    WordCount wc;
    wc.addAllWords("TT UCSB is the best best TT");

    std::stringstream ss;
    wc.dumpWordsSortedByOccurence(ss);

    std::string expected = "is 1\nthe 1\nucsb 1\nbest 2\ntt 2\n";
    ASSERT_EQUALS(expected, ss.str());
  }

  {
    WordCount wc;
    wc.addAllWords("67cHUngUs1-$ L1t saranghae~! C++ 'boo-yah-");

    ASSERT_EQUALS(1, wc.getWordCount("chungus"));
    ASSERT_EQUALS(1, wc.getWordCount("lt"));
    ASSERT_EQUALS(1, wc.getWordCount("saranghae"));
    ASSERT_EQUALS(1, wc.getWordCount("c"));
    ASSERT_EQUALS(1, wc.getWordCount("boo-yah"));
  }

  std::cout << "All Lab07 tests finished.\n";
  return 0;
}
