//
// Created by Rajendra Hathwar on 2020-01-18.
//

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <stdlib.h>
#include "gtest/gtest.h"
#include "stopwatch.h"
#include "filter.h"
#include "integrator.h"
#include "derivative.h"
#include "limits.h"
#include <vector>


using std::string;
using std::vector;
using namespace elma;
using namespace std::chrono;

#define EPSILON DBL_EPSILON*10.0 // double tolerance
#define DBL_PRECISION 0.0001
#define Q1POINTS 100.0
#define Q2POINTS 100.0
#define Q3POINTS 100.0
#define Q4POINTS 100.0
#define NUM_QUESTIONS 4 // overestimated number of questions
#define GTEST_COUT_GRADE std::cerr       << "[    GRADE ] "

/*
 * This is the base test class for all of the methods.
 *
 * All other tests inherit from this base class. It
 * contains several methods for building vector matrices,
 * random matrices, etc. for testing purposes.
 *
 * You can also see some file creation stuff that is relevant for
 * the homework.
 */
class BaseTest : public ::testing::Test {
protected:

    /*!
     * Compare two doubles, with relaxed tolerances
     * @param a
     * @param b
     * @return
     */
    bool compare_dbl(double a, double b) {
        if (fabs(a - b) < EPSILON) {
            return true;
        }
        return false;
    }

    /*!
     * Creates a random double.
     *
     * @param min
     * @param max
     * @return
     */
    double random_dbl(double min, double max) {
        double range = (max - min);
        double div = RAND_MAX / range;
        return min + (rand() / div);
    }

    /*!
     * Random integer between min and max
     * @param min
     * @param max
     * @return
     */
    int random_int(int min, int max) {
        if (max == 0) {
            return 0;
        }
        return rand() % max + min;
    }

    /*!
     * Creates a random double vector.
     *
     * @param size number of doubles in the vector
     * @param min minimum double
     * @param max maximum double
     * @return vector of doubles
     */
     vector<int> int_vector(int size, int min, int max) {
         vector<int> v;
         v.resize(size);
         for (int i = 0; i < size; i++) {
             v[i] = random_int(min, max);
         }
         return v;
     }

    /*!
     * Creates a random int vector.
     *
     * @param size number of doubles in the vector
     * @param min minimum double
     * @param max maximum double
     * @return vector of doubles
     */
    vector<double> dbl_vector(int size, double min, double max) {
        vector<double> v;
        v.resize(size);
        for (int i = 0; i < size; i++) {
            v[i] = random_dbl(min, max);
        }
        return v;
    }

     /*!
    * Create a random vector<vector<double>> matrix of doubles.
    *
    * @param r
    * @param c
    * @param mn
    * @param mx
    * @returnFc
    */
    vector<vector<double>> dbl_matrix(int r, int c, double mn, double mx) {
        vector<vector<double>> x;
        x.resize(r);
        for (int i = 0; i < r; i++) {
            x[i] = dbl_vector(c, mn, mx);
        }
        return x;
    }

     /*!
    * Create a random vector<vector<int>> matrix of ints.
    *
    * @param r
    * @param c
    * @param mn
    * @param mx
    * @return
    */
    vector<vector<int>> int_matrix(int r, int c, int mn, int mx) {
        vector<vector<int>> x;
        x.resize(r);
        for (int i = 0; i < r; i++) {
            x[i] = int_vector(c, mn, mx);
        }
        return x;
    }

     /*!
      * Print double vector contents
      */
      void print_vector(vector<double> &v) {
          std::cout << "[ ";
          vector<double>::iterator i;
          for (i = v.begin(); i != v.end(); i++) {
              std::cout << (*i) << " ";
          }
          std::cout << "]" << std::endl;
      }

      /*!
      * Print double vector contents
      */
      void print_vector(vector<int> &v) {
          std::cout << "[ ";
          vector<int>::iterator i;
          for (i = v.begin(); i != v.end(); i++) {
              std::cout << (*i) << " ";
          }
          std::cout << "]" << std::endl;
      }

      /*!
      * Print double vector contents
      */
      void print_vector(vector<string> &v) {
          std::cout << "[ ";
          vector<string>::iterator i;
          for (i = v.begin(); i != v.end(); i++) {
              std::cout << (*i) << " ";
          }
          std::cout << "]" << std::endl;
      }
};

/*
 * Define the base test classes for each of the questions.
 *
 * Each question should inherit from the main Question base,
 * which holds three static vectors (number of tests, number of
 * passing tests, total point value). Each inherited class
 * should get its own unique integer id. To get the number of tests,
 * number of passing tests, or total point values for a question,
 * just access the static vectors with the corresponding unique
 * int id.
 *
 * The individual weights for each question can be adjusted via
 * the "totals" static vector. The number of tests and number
 * of passing tests are computed automatically.
 *
 * To get the total grade, call "grade()". To get a grade break down
 * of each question, call "question_grades()".
 */

class Question : public BaseTest {
public:
    static vector<int> num_tests;
    static vector<int> num_passed;
    static vector<double> totals;

protected:
    int total_points;
    int id = -1;

    Question() {
        num_tests.resize(NUM_QUESTIONS);
        num_passed.resize(NUM_QUESTIONS);
        totals.resize(NUM_QUESTIONS);
    }

    virtual vector<double> question_grades() {
        vector<double> grade;
        grade.resize(NUM_QUESTIONS);
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (totals[i] > 0) {
                grade[i] = (double) num_passed[i]/num_tests[i] * totals[i];
            }
        }
        return grade;
    }

    virtual double grade() {

        double t, v;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (totals[i] > 0) {
                v += (double) num_passed[i]/num_tests[i] * totals[i];
                t += totals[i];
            }
        }
        return v/t;
    }

    void print_grade() {
        vector<double> q = question_grades();
        GTEST_COUT_GRADE << grade() * 100.0 << "%" << std::endl;
        GTEST_COUT_GRADE << "Question breakdown: " << std::endl;
        std::cout << grade() * 100.0 << std::endl;
        std::cout << "Question breakdown: " << std::endl;
        print_vector(q);
    }

    virtual void TearDown() {
        if (!HasFailure()) {
            num_passed[id]++;
        }
        print_grade();
    }
};

vector<int> Question::num_tests;
vector<int> Question::num_passed;
vector<double> Question::totals;
// get number of questions

class Question1 : public Question {
protected:
    Question1() {
        id = 0;
        totals[id] = Q1POINTS;
        num_tests[id]++;
    }
};

class Question2 : public Question {
protected:
    Question2() {
        id = 1;
        totals[id] = Q2POINTS;
        num_tests[id]++;
    }
};

class Question3 : public Question {
protected:
    Question3() {
        id = 2;
        totals[id] = Q3POINTS;
        num_tests[id]++;
    }
};

class Question4 : public Question {
protected:
    Question4() {
        id = 3;
        totals[id] = Q4POINTS;
        num_tests[id]++;
    }
};

/*
 * Question 1: stopwatch *************************************************
 */

class StopwatchTests : public Question1,
                    public ::testing::WithParamInterface<int> {
};

#define SLEEP_THREAD(_a) std::this_thread::sleep_for(std::chrono::milliseconds(_a))
#define NANO_PRECISION  10000000
#define MILLI_PRECISION 20
#define SEC_PRECISION   0.1
#define MIN_PRECISION   0.001


TEST_P(StopwatchTests, BasicTest) {
    int x = GetParam();

    Stopwatch w; // should set the stopwatch to 0 seconds
    w.start();
    SLEEP_THREAD(x);
    w.stop();
    ASSERT_NEAR(w.get_seconds(), x/1000.0, SEC_PRECISION); //about x

    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_seconds(), x/1000.0, SEC_PRECISION); //about x

    w.start();
    SLEEP_THREAD(x);
    w.stop();
    ASSERT_NEAR(w.get_seconds(), 2*x/1000.0, SEC_PRECISION); //about 2x

    w.reset();
    ASSERT_NEAR(w.get_seconds(), 0.0, SEC_PRECISION); //about 2x
}

//Param A name the test class, Param B good name for what the tests represent
TEST_P(StopwatchTests, IntermediateTest) {
    int x = GetParam();

    Stopwatch w;
    w.start();
    SLEEP_THREAD(x);
    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_minutes(), 2*x/60000.0, MIN_PRECISION); // about 2x
    ASSERT_NEAR(w.get_seconds(), 2*x/1000.0, SEC_PRECISION); // about 2x
    ASSERT_NEAR(w.get_milliseconds(), 2*x, MILLI_PRECISION); // about 2x
    ASSERT_NEAR(w.get_nanoseconds(), 2000000.0*x, NANO_PRECISION); // about 2x

    w.stop();
    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_minutes(), 2*x/60000.0, MIN_PRECISION); // about 2x
    ASSERT_NEAR(w.get_seconds(), 2*x/1000.0, SEC_PRECISION); // about 2x
    ASSERT_NEAR(w.get_milliseconds(), 2.0*x, MILLI_PRECISION); // about 2x
    ASSERT_NEAR(w.get_nanoseconds(), 2000000.0*x, NANO_PRECISION); // about 2x

    w.reset();
    ASSERT_NEAR(w.get_minutes(), 0.0, MIN_PRECISION); // 0

    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_milliseconds(), 0.0, MILLI_PRECISION); // 0
}

TEST_P(StopwatchTests, AdvancedTest) {
    int x = GetParam();

    Stopwatch w;
    w.start();
    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_minutes(), x/60000.0, MIN_PRECISION); // about x

    w.start();
    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_seconds(), x/1000.0, SEC_PRECISION); // about x

    SLEEP_THREAD(x);
    w.stop();
    ASSERT_NEAR(w.get_milliseconds(), 2.0*x, MILLI_PRECISION); // about 2x

    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_nanoseconds(), 2000000.0*x, NANO_PRECISION); // about 2x

    w.stop();
    SLEEP_THREAD(x);
    ASSERT_NEAR(w.get_seconds(), 2*x/1000.0, SEC_PRECISION); // about 2x

    w.start(); 
    SLEEP_THREAD(x);
    w.stop();
    ASSERT_NEAR(w.get_seconds(), 3*x/1000.0, SEC_PRECISION); // about 3x

    w.reset();
    ASSERT_NEAR(w.get_minutes(), 0.0, MIN_PRECISION); // 0
};


/*
 * parameterizes the StopwatchTests, TEST_P class above.
 */
INSTANTIATE_TEST_CASE_P(StopwatchTests,
        StopwatchTests,
        testing::Range(600, 1800, 300)
);

/*
 * Question 2: Running Average *************************************************
 */

class RunningAverageTests : public Question2,
                    public testing::WithParamInterface<std::tuple<high_resolution_clock::duration, double, double, double>> {
};

class RandomNumGen : public elma::Process {
  public:
    RandomNumGen(std::string name, double val, double step) : Process(name), _val(val), _step(step) {}

    void init() {}
    void start() {}
    void update() {
        if(_sent % 2 == 0) {
            channel("link").send(_val);
            //std::cout << "sending ==> " << _val <<" _sent ==> " << _sent << "\n";
        }
        else {
            channel("link").send(_val + _step);
            //std::cout << "sending ==> " << _val + _step <<" _sent ==> " << _sent << "\n";
        }

        _sent++;
    }
    void stop() {}

  private:
    int _sent = 0;
    double _val, _step;
};

std::vector <std::tuple<high_resolution_clock::duration, double, double, double>> runningAvgTestVec =
    { {100_ms, 0.25, 0.5, 0.5} // dur, base, step, result
    , {100_ms, 0.5, 0.5, 0.75}
    , {0_ms, 0.25, 0.5, 0.0}
    , {150_ms, 1, 0.5, 1.25}
    , {50_ms, 0.25, 0.5, 0.5}
    , {150_ms, 0, 0.5, 0.25}
    , {60_ms, 1.25, 0.25, 1.375}
    , {70_ms, 0.75, 0.75, 1.125}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(RunningAverageTests, RunningAverage) {
    std::tuple<high_resolution_clock::duration, double, double, double> params = GetParam();
    high_resolution_clock::duration dur = std::get<0>(params);
    double base = std::get<1>(params);
    double step = std::get<2>(params);
    double result = std::get<3>(params);

    elma::Manager m;
    RandomNumGen r("random numbers", base, step);
    Filter f("filter");
    elma::Channel link("link");

    m.schedule(r, 1_ms)
     .schedule(f, 1_ms)
     .add_channel(link)
     .init()
     .run(dur);

    ASSERT_NEAR(f.value(), result, DBL_PRECISION);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(RunningAverageTests,
        RunningAverageTests,
        testing::ValuesIn(runningAvgTestVec)
);

/*
 * Question 3: Integrator *************************************************
 */

class IntegratorTests : public Question3,
                    public testing::WithParamInterface<std::tuple<high_resolution_clock::duration, double, double, double>> {
};

std::vector <std::tuple<high_resolution_clock::duration, double, double, double>> intgTestVec =
    { {100_ms, 0.25, 0.0, 25.0} // dur, base, step, result
    , {100_ms, 0.5, 0.0, 50.0}
    , {0_ms, 0.25, 0.0, 0.0}
    , {150_ms, 0.5, 0.0, 75.0}
    , {50_ms, 0.25, 0.0, 12.5}
    , {150_ms, 0, 0.0, 0.0}
    , {15_ms, 0.25, 0.0, 3.75}
    , {75_ms, 0.35, 0.0, 26.25}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(IntegratorTests, Integrate) {
    std::tuple<high_resolution_clock::duration, double, double, double> params = GetParam();
    high_resolution_clock::duration dur = std::get<0>(params);
    double base = std::get<1>(params);
    double step = std::get<2>(params);
    double result = std::get<3>(params);

    elma::Manager m;
    RandomNumGen r("random numbers", base, step);
    Integrator intg("Integrator");
    elma::Channel link("link");

    m.schedule(r, 1_ms)
     .schedule(intg, 1_ms)
     .add_channel(link)
     .init()
     .run(dur);

    ASSERT_NEAR(intg.value(), result, 1.5);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(IntegratorTests,
        IntegratorTests,
        testing::ValuesIn(intgTestVec)
);

/*
 * Question 4: Derivative *************************************************
 */

class DerivativeTests : public Question4,
                    public testing::WithParamInterface<std::tuple<high_resolution_clock::duration, double, double, double>> {
};

class RandomNumGenDerv : public elma::Process {
  public:
    RandomNumGenDerv(std::string name, double val, double step) : Process(name), _val(val), _step(step) {}

    void init() {}
    void start() {}
    void update() {
        channel("link").send(_val + _step);
        //std::cout << "sending ==> " << _val + _step << "\n";
    }
    void stop() {}

  private:
    double _val, _step;
};

std::vector <std::tuple<high_resolution_clock::duration, double, double, double>> dervTestVec =
    { {100_ms, 250.0, -1.0, -1.0} // dur, base, step, result
    , {100_ms, 50, -0.5, -0.5}
    , {0_ms, 0.25, 0.0, 0.0}
    , {25_ms, 35.0, 1.0, 1.0}
    , {50_ms, 0.25, 0.0, 0.0}
    , {150_ms, 3.0, 0.25, 0.25}
    , {15_ms, -6.0, -0.5, -0.5}
    , {75_ms, 5.0, 0.75, 0.75}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(DerivativeTests, Derivative) {
    std::tuple<high_resolution_clock::duration, double, double, double> params = GetParam();
    high_resolution_clock::duration dur = std::get<0>(params);
    double base = std::get<1>(params);
    double step = std::get<2>(params);
    double result = std::get<3>(params);

    elma::Manager m;
    RandomNumGenDerv r("random numbers", base, step);
    Derivative derv("Derivative");
    elma::Channel link("link");

    m.schedule(r, 1_ms)
     .schedule(derv, 1_ms)
     .add_channel(link)
     .init()
     .run(dur);

    ASSERT_NEAR(derv.value(), result, 1);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(DerivativeTests,
        DerivativeTests,
        testing::ValuesIn(dervTestVec)
);
