#ifndef TESTER_TEST_HARNESS_H
#define TESTER_TEST_HARNESS_H

#include "testharness/TestPair.h"
#include "testharness/TestResult.h"
#include "testharness/ResultManager.h"
#include "toolchain/ToolChain.h"

#include "json.hpp"

#include <string>
#include <vector>

// Convenience.
using JSON = nlohmann::json;

namespace tester {

// Test file typedefs.
typedef std::vector<TestPair> TestList;
typedef std::map<std::string, TestList> TestSet;
typedef std::map<std::string, TestSet> PackageSet;

// Class that manages finding tests and running them.
class TestHarness {
public:
  // No default constructor.
  TestHarness() = delete;

  // Construct the Tester with a parsed JSON file.
  TestHarness(const JSON &json, bool quiet);

  // Run the found tests.
  void runTests();

  // Get tests info.
  std::string getTestInfo() const;

private:
  // Runs a single test. True/false based on test pass.
  TestResult runTest(const TestPair &tp) const;

private:
  // The tool chain to compile something to test.
  ToolChain toolchain;

  // The list of tests to test.
  PackageSet tests;

  // The results of the tests.
  ResultManager results;

  // Should we print diffs?
  bool quiet;
};

} // End namespace tester

#endif //TESTER_TESTER_H
