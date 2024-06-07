//https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem?isFullScreen=true

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {

  string isValid(string s) {
    vector<int> freqVec(26, 0);
    for (char ch : s) {
      freqVec[ch - 'a']++;
    }

    std::unordered_map<int, int> itemsCountMap;
    for (const int& item : freqVec) {
      if (item != 0)
        itemsCountMap[item]++;
    }

    bool valid;
    if (itemsCountMap.size() == 1) {
      valid = true;
    } else if (itemsCountMap.size() == 2) {
      auto it1 = itemsCountMap.begin();
      auto it2 = next(it1);
      int count1 = it1->second;
      int count2 = it2->second;
      if (count1 == 1 && (it1->first == 1 || (it1->first - it2->first == 1))) {
        valid = true;
      } else if (count2 == 1 && (it2->first == 1 || (it1->first - it2->first == -1))) {
        valid = true;
      } else {
        valid = false;
      }
    } else {
      valid = false;
    }

    return valid ? "YES" : "NO";
  }



  void check(const string& s, string expected) {
    auto result = isValid(s);
    if (result != expected) {
      println("Error with string = {}, result = {}, expected = {}", s, result, expected);
      throw exception("Error!");
    }
  }
}



void demo_SherlockAndTheValidString() {
  try {
    println("demo_SherlockAndTheValidString started ...\n");

    check("aabbc", "YES");
    check("aabbcd", "NO");
    check("aaaabbcc", "NO");
    check("abcdefghhgfedecba", "YES");
    check("ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd", "YES");


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}